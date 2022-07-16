#include "jp/ggaf/dx/model/BoardSetModel.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/effect/BoardSetEffect.h"
#include "jp/ggaf/dx/actor/BoardSetActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"

#define BOARDSETMODEL_MAX_DARW_SET_NUM 28

using namespace GgafDx;

DWORD BoardSetModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_TEX1);
BoardSetModel::BoardSetModel(const char* prm_model_id) : Model(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_model |= Obj_GgafDx_BoardSetModel;
    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _paVertexBuffer = nullptr;
    _paIndexBuffer = nullptr;
    _paVertexBuffer_data = nullptr;
    _paIndexBuffer_data = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _paIndexParam = nullptr;
    _max_draw_set_num = BOARDSETMODEL_MAX_DARW_SET_NUM;
}

HRESULT BoardSetModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("BoardSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _draw_set_num) {
        throwCriticalException(FUNC_NAME<<" "<<_model_id<<" �̕`��Z�b�g���I�[�o�[�B_draw_set_num="<<_draw_set_num<<" �ɑ΂��Aprm_draw_set_num="<<prm_draw_set_num<<"�ł����B");
    }
#endif
    IDirect3DDevice9* const pDevice = pGOD->_pID3DDevice9;
    //�Ώ�Actor
    const BoardSetActor* const pTargetActor = (BoardSetActor*)prm_pActor_target;
    //�Ώ�BoardSetActor�̃G�t�F�N�g���b�p
    BoardSetEffect* const pBoardSetEffect = (BoardSetEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pBoardSetEffect->_pID3DXEffect;

    HRESULT hr;
    //���f���������Ȃ�Β��_�o�b�t�@���A�̐ݒ�̓X�L�b�v�ł���
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _paVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(BoardSetModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetIndices(_paIndexBuffer);

        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_threshold, _blink_threshold);
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pBoardSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pBoardSetEffect->_effect_name<<"("<<pBoardSetEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pBoardSetEffect->_begin) {
            throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pBoardSetEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pBoardSetEffect->_effect_name);
    const INDEXPARAM& idxparam = _paIndexParam[prm_draw_set_num-1];
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                  idxparam.BaseVertexIndex,
                                  idxparam.MinIndex,
                                  idxparam.NumVertices,
                                  idxparam.StartIndex,
                                  idxparam.PrimitiveCount);

    //�O��`�惂�f���ێ�
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pBoardSetEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
    return D3D_OK;
}

void BoardSetModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVertexBuffer_data == nullptr) {
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
            _TRACE_("BoardSetModel::restore() "<<_model_id<<" �̓����`��Z�b�g���́A�ő�� "<<_max_draw_set_num<<" �ɍĒ�`����܂����B���R�F_draw_set_num="<<_draw_set_num);
            _draw_set_num = _max_draw_set_num;
        } else {
            _TRACE_("BoardSetModel::restore() "<<_model_id<<" �̓����`��Z�b�g���� "<<_draw_set_num<<" �ł��B");
        }
        if (4*_draw_set_num > 65535) {
            throwCriticalException("SpriteSetModel::restore() ���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<getName()<<"  nVertices:4  �Z�b�g��:"<<(_draw_set_num));
        }
        _size_vertices = sizeof(BoardSetModel::VERTEX)*4;
        _size_vertex_unit = sizeof(BoardSetModel::VERTEX);
        _paVertexBuffer_data = NEW BoardSetModel::VERTEX[4 * _draw_set_num];

        //1px�������uv�̑傫�������߂�
//        float tex_width  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
//        float tex_height = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)
        double du = 0.0; //1.0 / tex_width  / 100000.0; //�e�N�X�`���̕�1px��10000����1px
        double dv = 0.0; //1.0 / tex_height / 100000.0; //�e�N�X�`���̍���1px��10000����1px
        for (int i = 0; i < _draw_set_num; i++) {
            //����
            _paVertexBuffer_data[i*4 + 0].x = 0.0f;
            _paVertexBuffer_data[i*4 + 0].y = 0.0f;
            _paVertexBuffer_data[i*4 + 0].z = 0.0f;
            _paVertexBuffer_data[i*4 + 0].tu = (float)du;
            _paVertexBuffer_data[i*4 + 0].tv = (float)dv;
            _paVertexBuffer_data[i*4 + 0].index = (float)i;
            //�E��
            _paVertexBuffer_data[i*4 + 1].x = xdata.Width;
            _paVertexBuffer_data[i*4 + 1].y = 0.0f;
            _paVertexBuffer_data[i*4 + 1].z = 0.0f;
            _paVertexBuffer_data[i*4 + 1].tu = (float)((1.0 / xdata.TextureSplitCols) - du);
            _paVertexBuffer_data[i*4 + 1].tv = (float)dv;
            _paVertexBuffer_data[i*4 + 1].index = (float)i;
            //����
            _paVertexBuffer_data[i*4 + 2].x = 0.0f;
            _paVertexBuffer_data[i*4 + 2].y = xdata.Height;
            _paVertexBuffer_data[i*4 + 2].z = 0.0f;
            _paVertexBuffer_data[i*4 + 2].tu = (float)du;
            _paVertexBuffer_data[i*4 + 2].tv = (float)((1.0 / xdata.TextureSplitRows) - dv);
            _paVertexBuffer_data[i*4 + 2].index = (float)i;
            //�E��
            _paVertexBuffer_data[i*4 + 3].x = xdata.Width;
            _paVertexBuffer_data[i*4 + 3].y = xdata.Height;
            _paVertexBuffer_data[i*4 + 3].z = 0.0f;
            _paVertexBuffer_data[i*4 + 3].tu = (float)((1.0 / xdata.TextureSplitCols) - du);
            _paVertexBuffer_data[i*4 + 3].tv = (float)((1.0 / xdata.TextureSplitRows) - dv);
            _paVertexBuffer_data[i*4 + 3].index = (float)i;
        }

        //�`�掞�p�����[�^�[
        int nVertices = 4;
        int nFaces = 2;
        WORD* unit_paIdxBuffer = NEW WORD[(nFaces*3)];
        unit_paIdxBuffer[0] = 0;
        unit_paIdxBuffer[1] = 1;
        unit_paIdxBuffer[2] = 2;
        unit_paIdxBuffer[3] = 1;
        unit_paIdxBuffer[4] = 3;
        unit_paIdxBuffer[5] = 2;
        _paIndexBuffer_data = NEW WORD[(nFaces*3) * _draw_set_num];
        for (int i = 0; i < _draw_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                _paIndexBuffer_data[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer[j*3 + 0] + (nVertices*i);
                _paIndexBuffer_data[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer[j*3 + 1] + (nVertices*i);
                _paIndexBuffer_data[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer[j*3 + 2] + (nVertices*i);
            }
        }
        GGAF_DELETEARR(unit_paIdxBuffer);

        BoardSetModel::INDEXPARAM* paIndexParam = NEW BoardSetModel::INDEXPARAM[_draw_set_num];
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

    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        //�o�b�t�@�쐬
        hr = pGOD->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices * _draw_set_num,
                D3DUSAGE_WRITEONLY,
                BoardSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_paVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_id));
        //���_�o�b�t�@�쐬
        //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
        void *paVertexBuffer;
        hr = _paVertexBuffer->Lock(
                                 0,
                                 _size_vertices * _draw_set_num,
                                 (void**)&paVertexBuffer,
                                 0
                               );
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_id);
        memcpy(
          paVertexBuffer,
          _paVertexBuffer_data,
          _size_vertices * _draw_set_num
        ); //paVertexBuffer �� _paVertexBuffer_data
        _paVertexBuffer->Unlock();

    }


    //�C���f�b�N�X�o�b�t�@�쐬
    if (_paIndexBuffer == nullptr) {
        HRESULT hr;
        int nFaces = 2;
        hr = pGOD->_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * nFaces * 3 * _draw_set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_paIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_id));

        void* paIndexBuffer;
        _paIndexBuffer->Lock(0,0,(void**)&paIndexBuffer,0);
        memcpy(
          paIndexBuffer ,
          _paIndexBuffer_data,
          sizeof(WORD) * nFaces * 3 * _draw_set_num
        );
        _paIndexBuffer->Unlock();
    }

    if (_papTextureConnection == nullptr) {
        ModelManager* pModelManager = pGOD->_pModelManager;
        //�e�N�X�`���擾�����f���ɕێ�������
        _papTextureConnection = NEW TextureConnection*[1];
        _papTextureConnection[0] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
    }

}

void BoardSetModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void BoardSetModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    GGAF_RELEASE(_paVertexBuffer);
    GGAF_RELEASE(_paIndexBuffer);
    //�e�N�X�`�������
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���

    _TRACE3_("_model_id=" << _model_id << " end");
}

BoardSetModel::~BoardSetModel() {

    GGAF_DELETEARR(_paVertexBuffer_data);
    GGAF_DELETEARR(_paIndexBuffer_data);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    GGAF_DELETEARR(_paIndexParam);
    //release();
    //��ModelConnection::processReleaseResource(Model* prm_pResource) �ŌĂяo�����
}

