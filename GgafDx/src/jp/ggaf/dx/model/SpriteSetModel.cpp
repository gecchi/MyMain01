#include "jp/ggaf/dx/model/SpriteSetModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/actor/SpriteSetActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/SpriteSetEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"

#define SPRITESETMODEL_MAX_DARW_SET_NUM 18

using namespace GgafDx;

DWORD SpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_TEX1);
SpriteSetModel::SpriteSetModel(const char* prm_model_id) : Model(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_model |= Obj_GgafDx_SpriteSetModel;
    _pVertexBuffer_data = nullptr;
    _pIndexBuffer_data = nullptr;

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _paIndexParam = nullptr;
    _max_draw_set_num = SPRITESETMODEL_MAX_DARW_SET_NUM;
}

HRESULT SpriteSetModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("SpriteSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _draw_set_num) {
        throwCriticalException(_model_id<<" �̕`��Z�b�g���I�[�o�[�B_draw_set_num="<<_draw_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    //�Ώ�Actor
    const SpriteSetActor* const pTargetActor = (SpriteSetActor*)prm_pActor_target;
    //�Ώ�SpriteSetActor�̃G�t�F�N�g���b�p
    SpriteSetEffect* const pSpriteSetEffect = (SpriteSetEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pSpriteSetEffect->_pID3DXEffect;

    HRESULT hr;
    //���f���������Ȃ�Β��_�o�b�t�@���A�̐ݒ�̓X�L�b�v�ł���
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(SpriteSetModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }
    Effect* pEffect_active = EffectManager::_pEffect_active;
    if (FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
        if (pEffect_active) {
            _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pSpriteSetEffect->_effect_name<<"("<<pSpriteSetEffect<<")");
        hr = pID3DXEffect->Begin( &_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pSpriteSetEffect->_begin) {
            throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pSpriteSetEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pSpriteSetEffect->_effect_name);
    const INDEXPARAM& idxparam = _paIndexParam[prm_draw_set_num - 1];
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                  idxparam.BaseVertexIndex,
                                  idxparam.MinIndex,
                                  idxparam.NumVertices,
                                  idxparam.StartIndex,
                                  idxparam.PrimitiveCount);
    if (_num_pass >= 2) { //�Q�p�X�ڈȍ~������
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");

        for (UINT pass = 1; pass < _num_pass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, pass+1<<"�p�X�� BeginPass("<<pass<<") �Ɏ��s���܂����B");
            pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                          idxparam.BaseVertexIndex,
                                          idxparam.MinIndex,
                                          idxparam.NumVertices,
                                          idxparam.StartIndex,
                                          idxparam.PrimitiveCount);
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
        }

        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "�P�p�X�� BeginPass(0) �Ɏ��s���܂����B");
    }

    //�O��`�惂�f���ێ�
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pSpriteSetEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
    return D3D_OK;
}

void SpriteSetModel::restore() {
    _TRACE3_("_model_id="<<_model_id);
    if (_pVertexBuffer_data == nullptr) {
        _papTextureConnection = nullptr;

        ModelManager* pModelManager = pGOD->_pModelManager;
        ModelManager::SpriteXFileFmt xdata;
        std::string model_def_file = std::string(_model_id) + ".sprx";
        std::string model_def_filepath = Model::getModelDefineFilePath(model_def_file);
        pModelManager->obtainSpriteModelInfo(&xdata, model_def_filepath);

        _model_width_px  = xdata.Width;
        _model_height_px = xdata.Height;
        _row_texture_split = xdata.TextureSplitRows;
        _col_texture_split = xdata.TextureSplitCols;
        _pa_texture_filenames = NEW std::string[1];
        _pa_texture_filenames[0] = std::string(xdata.TextureFile);
        _draw_set_num = xdata.DrawSetNum;

        if (_draw_set_num == 0 || _draw_set_num > _max_draw_set_num) {
            _TRACE_("SpriteSetModel::restore() "<<_model_id<<" �̓����`��Z�b�g���́A�ő�� "<<_max_draw_set_num<<" �ɍĒ�`����܂����B���R�F_draw_set_num="<<_draw_set_num);
            _draw_set_num = _max_draw_set_num;
        } else {
            _TRACE_("SpriteSetModel::restore() "<<_model_id<<" �̓����`��Z�b�g���� "<<_draw_set_num<<" �ł��B");
        }
        if (4*_draw_set_num > 65535) {
            throwCriticalException("SpriteSetModel::restore() ���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<getName()<<"  nVertices:4  �Z�b�g��:"<<(_draw_set_num));
        }
        if ( 2 * 3 * _draw_set_num > 65535) {
            throwCriticalException("SpriteSetModel::restore() ���_�C���f�b�N�X�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<getName()<<"  nFaces:2(*3)  �Z�b�g��:"<<(_draw_set_num));
        }

        //�o�b�t�@�쐬
        _size_vertices = sizeof(SpriteSetModel::VERTEX)*4;
        _size_vertex_unit = sizeof(SpriteSetModel::VERTEX);
        _pVertexBuffer_data = NEW SpriteSetModel::VERTEX[4 * _draw_set_num];

        double du = 0.0;
        double dv = 0.0;
        //���_�z��������f���ɕێ�������
        //UV�͍���̂P���i�A�j���p�^�[���O�j���f�t�H���g�Őݒ肷��B
        //�V�F�[�_�[���`�掞�ɃA�j���p�^�[���ԍ����݂�UV���W�����炷�d�l�Ƃ�����ƁB
        //x,y �� ��2 �Ƃ́A���f�����S�����[�J�����W�̌��_���S�Ƃ���������
        for (int i = 0; i < _draw_set_num; i++) {
            //����
            _pVertexBuffer_data[i*4 + 0].x = PX_DX(xdata.Width)  / -2.0;
            _pVertexBuffer_data[i*4 + 0].y = PX_DX(xdata.Height) /  2.0;
            _pVertexBuffer_data[i*4 + 0].z = 0.0f;
            _pVertexBuffer_data[i*4 + 0].nx = 0.0f;
            _pVertexBuffer_data[i*4 + 0].ny = 0.0f;
            _pVertexBuffer_data[i*4 + 0].nz = -1.0f;
            _pVertexBuffer_data[i*4 + 0].tu = (float)du;
            _pVertexBuffer_data[i*4 + 0].tv = (float)dv;
            _pVertexBuffer_data[i*4 + 0].index = (float)i;
            //�E��
            _pVertexBuffer_data[i*4 + 1].x = PX_DX(xdata.Width)  / 2.0;
            _pVertexBuffer_data[i*4 + 1].y = PX_DX(xdata.Height) / 2.0;
            _pVertexBuffer_data[i*4 + 1].z = 0.0f;
            _pVertexBuffer_data[i*4 + 1].nx = 0.0f;
            _pVertexBuffer_data[i*4 + 1].ny = 0.0f;
            _pVertexBuffer_data[i*4 + 1].nz = -1.0f;
            _pVertexBuffer_data[i*4 + 1].tu = (float)((1.0 / xdata.TextureSplitCols) - du);
            _pVertexBuffer_data[i*4 + 1].tv = (float)dv;
            _pVertexBuffer_data[i*4 + 1].index = (float)i;
            //����
            _pVertexBuffer_data[i*4 + 2].x = PX_DX(xdata.Width)  / -2.0;
            _pVertexBuffer_data[i*4 + 2].y = PX_DX(xdata.Height) / -2.0;
            _pVertexBuffer_data[i*4 + 2].z = 0.0f;
            _pVertexBuffer_data[i*4 + 2].nx = 0.0f;
            _pVertexBuffer_data[i*4 + 2].ny = 0.0f;
            _pVertexBuffer_data[i*4 + 2].nz = -1.0f;
            _pVertexBuffer_data[i*4 + 2].tu = (float)du;
            _pVertexBuffer_data[i*4 + 2].tv = (float)((1.0 / xdata.TextureSplitRows) - dv);
            _pVertexBuffer_data[i*4 + 2].index = (float)i;
            //�E��
            _pVertexBuffer_data[i*4 + 3].x = PX_DX(xdata.Width)  /  2.0;
            _pVertexBuffer_data[i*4 + 3].y = PX_DX(xdata.Height) / -2.0;
            _pVertexBuffer_data[i*4 + 3].z = 0.0f;
            _pVertexBuffer_data[i*4 + 3].nx = 0.0f;
            _pVertexBuffer_data[i*4 + 3].ny = 0.0f;
            _pVertexBuffer_data[i*4 + 3].nz = -1.0f;
            _pVertexBuffer_data[i*4 + 3].tu = (float)((1.0 / xdata.TextureSplitCols) - du);
            _pVertexBuffer_data[i*4 + 3].tv = (float)((1.0 / xdata.TextureSplitRows) - dv);
            _pVertexBuffer_data[i*4 + 3].index = (float)i;

        }

        //����
        FLOAT model_bounding_sphere_radius = (FLOAT)(sqrt(_pVertexBuffer_data[0].x * _pVertexBuffer_data[0].x +
                                                          _pVertexBuffer_data[0].y * _pVertexBuffer_data[0].y +
                                                          _pVertexBuffer_data[0].z * _pVertexBuffer_data[0].z));
        _bounding_sphere_radius = model_bounding_sphere_radius;
        //�C���f�b�N�X�o�b�t�@�f�[�^
        int nVertices = 4;
        int nFaces = 2;
        WORD* unit_paIdxBuffer = NEW WORD[(nFaces*3)];
        unit_paIdxBuffer[0] = 0;
        unit_paIdxBuffer[1] = 1;
        unit_paIdxBuffer[2] = 2;
        unit_paIdxBuffer[3] = 1;
        unit_paIdxBuffer[4] = 3;
        unit_paIdxBuffer[5] = 2;
        _pIndexBuffer_data = NEW WORD[(nFaces*3) * _draw_set_num];
        for (int i = 0; i < _draw_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                _pIndexBuffer_data[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer[j*3 + 0] + (nVertices*i);
                _pIndexBuffer_data[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer[j*3 + 1] + (nVertices*i);
                _pIndexBuffer_data[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer[j*3 + 2] + (nVertices*i);
            }
        }
        GGAF_DELETEARR(unit_paIdxBuffer);


        //�`�掞�p�����[�^�[
        SpriteSetModel::INDEXPARAM* paIndexParam = NEW SpriteSetModel::INDEXPARAM[_draw_set_num];
        for (int i = 0; i < _draw_set_num; i++) {
            paIndexParam[i].MaterialNo = 0;
            paIndexParam[i].BaseVertexIndex = 0;
            paIndexParam[i].MinIndex = 0;
            paIndexParam[i].NumVertices = nVertices*(i+1);
            paIndexParam[i].StartIndex = 0;
            paIndexParam[i].PrimitiveCount = nFaces*(i+1);
        }
        _paIndexParam = paIndexParam;

        _num_materials = 1;
        D3DMATERIAL9* paMaterial = NEW D3DMATERIAL9[_num_materials];
        for ( DWORD i = 0; i < _num_materials; i++) {
            //paMaterial[i] = paD3DMaterial9_tmp[i].MatD3D;
            paMaterial[i].Diffuse.r = 1.0f;
            paMaterial[i].Diffuse.g = 1.0f;
            paMaterial[i].Diffuse.b = 1.0f;
            paMaterial[i].Diffuse.a = 1.0f;
            paMaterial[i].Ambient.r = 1.0f;
            paMaterial[i].Ambient.g = 1.0f;
            paMaterial[i].Ambient.b = 1.0f;
            paMaterial[i].Ambient.a = 1.0f;
        }
        _paMaterial_default = paMaterial;
    }
    if (_pVertexBuffer == nullptr) {
        HRESULT hr;
        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices * _draw_set_num,
                D3DUSAGE_WRITEONLY,
                SpriteSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_p1ID3DDevice9->CreateVertexBuffer ���s model="<<(_model_id));
        //���_�o�b�t�@�쐬
        //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(
                               0,
                               _size_vertices * _draw_set_num,
                               (void**)&pVertexBuffer,
                               0
                           );
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_id);

        memcpy(
            pVertexBuffer,
            _pVertexBuffer_data,
            _size_vertices* _draw_set_num
        ); //pVertexBuffer �� _pVertexBuffer_data
        _pVertexBuffer->Unlock();

    }

    //�C���f�b�N�X�o�b�t�@�쐬
    if (_pIndexBuffer == nullptr) {
        HRESULT hr;
        int nVertices = 4;
        int nFaces = 2;
        hr = God::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3 * _draw_set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_id));

        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          _pIndexBuffer_data,
          sizeof(WORD) * nFaces * 3 * _draw_set_num
        );
        _pIndexBuffer->Unlock();
    }

    if (_papTextureConnection == nullptr) {
        //�e�N�X�`���擾�����f���ɕێ�������
        ModelManager* pModelManager = pGOD->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[1];
        _papTextureConnection[0] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
    }

    _TRACE3_("_model_id=" << _model_id << " end");
}

void SpriteSetModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void SpriteSetModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);

    _TRACE3_("_model_id=" << _model_id << " end");
}

SpriteSetModel::~SpriteSetModel() {
    GGAF_DELETEARR(_pVertexBuffer_data);
    GGAF_DELETEARR(_pIndexBuffer_data);
    GGAF_DELETEARR(_paIndexParam);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
}

