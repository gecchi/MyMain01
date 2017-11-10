#include "jp/ggaf/dxcore/model/GgafDxFramedBoardModel.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxFramedBoardEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxFramedBoardActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"

#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxFramedBoardModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_TEX1);
GgafDxFramedBoardModel::GgafDxFramedBoardModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _model_frame_width_px = 32.0f;
    _model_frame_height_px = 32.0f;
    _row_frame_texture_split = 1;
    _col_frame_texture_split = 1;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _obj_model |= Obj_GgafDxFramedBoardModel;

//    std::string model_name = std::string(prm_model_name);
//    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
//    if (names.size() > 2) {
//        throwGgafCriticalException("prm_model_name �ɂ� \"xxxxxx\" or \"8/xxxxx\" �`�����w�肵�Ă��������B \n"
//                                   "���ۂ̈����́Aprm_idstr="<<prm_model_name);
//    }
    _set_num = 9;

    //�f�o�C�C�X���X�g�Ή��Ƌ��ʂɂ��邽�߁A�e�N�X�`���A���_�A�}�e���A���Ȃǂ̏�������
    //void GgafDxModelManager::restoreFramedBoardModel(GgafDxFramedBoardModel*)
    //�ōs���悤�ɂ����B�v�Q�ƁB
}

HRESULT GgafDxFramedBoardModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("GgafDxFramedBoardModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //�Ώ�Actor
    const GgafDxFramedBoardActor* const pTargetActor = (GgafDxFramedBoardActor*)prm_pActor_target;
    //�Ώ�FramedBoardActor�̃G�t�F�N�g���b�p
    GgafDxFramedBoardEffect* const pFramedBoardEffect = (GgafDxFramedBoardEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pFramedBoardEffect->_pID3DXEffect;

    HRESULT hr;
    //���f���������Ȃ�Β��_�o�b�t�@���A�̐ݒ�̓X�L�b�v�ł���
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxFramedBoardModel::FVF);
        pDevice->SetTexture(0, _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetTexture(1, _papTextureConnection[1]->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");

        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_center_width, _model_width_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_unit_width) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_center_height, _model_height_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_unit_height) �Ɏ��s���܂����B");

        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_frame_width, _model_frame_width_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_unit_width) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pFramedBoardEffect->_h_frame_height, _model_frame_height_px);
        checkDxException(hr, D3D_OK, "SetFloat(_h_unit_height) �Ɏ��s���܂����B");

    }
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
        if (pEffect_active) {
           _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() �Ɏ��s���܂����B");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "End() �Ɏ��s���܂����B");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwGgafCriticalException("begin ���Ă��܂��� "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pFramedBoardEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pFramedBoardEffect->_effect_name<<"("<<pFramedBoardEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pFramedBoardEffect->_begin) {
            throwGgafCriticalException("End ���Ă��܂��� "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pFramedBoardEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pFramedBoardEffect->_effect_name);
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                    _indexParam.BaseVertexIndex,
                                    _indexParam.MinIndex,
                                    _indexParam.NumVertices,
                                    _indexParam.StartIndex,
                                    _indexParam.PrimitiveCount);

    //�O��`�惂�f���ێ�
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pFramedBoardEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif

    return D3D_OK;
}

void GgafDxFramedBoardModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    _set_num = 9;
    _papTextureConnection = nullptr;
    HRESULT hr;

    std::string xfile_name = GgafDxModelManager::getSpriteFileName(_model_name);
    GgafDxModelManager::SpriteXFileFmt xdata;
    GgafDxModelManager::obtainSpriteInfo(&xdata, xfile_name);
    _model_width_px  = xdata.width;
    _model_height_px = xdata.height;
    _row_texture_split = xdata.row_texture_split;
    _col_texture_split = xdata.col_texture_split;

    std::string xfile_name_frame = GgafDxModelManager::getSpriteFileName(std::string(_model_name)+"_frame");
    GgafDxModelManager::SpriteXFileFmt xdata_frame;
    GgafDxModelManager::obtainSpriteInfo(&xdata_frame, xfile_name_frame);
    _model_frame_width_px  = xdata_frame.width;
    _model_frame_height_px = xdata_frame.height;
    _row_frame_texture_split = xdata_frame.row_texture_split;
    _col_frame_texture_split = xdata_frame.col_texture_split;



    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDxTextureConnection* model_pTextureConnection = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(xdata.texture_file, this));
    GgafDxTextureConnection* model_frame_pTextureConnection = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(xdata_frame.texture_file, this));

    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    _papTextureConnection = NEW GgafDxTextureConnection*[2];
    _papTextureConnection[0] = model_pTextureConnection;
    _papTextureConnection[1] = model_frame_pTextureConnection;

    if (_pVertexBuffer == nullptr) {

        _size_vertices = sizeof(GgafDxFramedBoardModel::VERTEX)*4;
        _size_vertex_unit = sizeof(GgafDxFramedBoardModel::VERTEX);
        GgafDxFramedBoardModel::VERTEX* paVertex = NEW GgafDxFramedBoardModel::VERTEX[4 * _set_num];
        //    ��������������
        //    ���O���P���Q��
        //    ��������������
        //    ���R���S���T��
        //    ��������������
        //    ���U���V���W��
        //    ��������������

        //1px�������uv�̑傫�������߂�
        double du = 0.0;
        double dv = 0.0;
        for (int i = 0; i < _set_num; i++) {
            if (i == 4) {
                //���S
                //����
                paVertex[i*4 + 0].x = 0.0f;
                paVertex[i*4 + 0].y = 0.0f;
                paVertex[i*4 + 0].z = 0.0f;
                paVertex[i*4 + 0].tu = (float)du;
                paVertex[i*4 + 0].tv = (float)dv;
                paVertex[i*4 + 0].index = (float)i;
                //�E��
                paVertex[i*4 + 1].x = xdata.width;
                paVertex[i*4 + 1].y = 0.0f;
                paVertex[i*4 + 1].z = 0.0f;
                paVertex[i*4 + 1].tu = (float)((1.0 / xdata.col_texture_split) - du);
                paVertex[i*4 + 1].tv = (float)dv;
                paVertex[i*4 + 1].index = (float)i;
                //����
                paVertex[i*4 + 2].x = 0.0f;
                paVertex[i*4 + 2].y = xdata.height;
                paVertex[i*4 + 2].z = 0.0f;
                paVertex[i*4 + 2].tu = (float)du;
                paVertex[i*4 + 2].tv = (float)((1.0 / xdata.row_texture_split) - dv);
                paVertex[i*4 + 2].index = (float)i;
                //�E��
                paVertex[i*4 + 3].x = xdata.width;
                paVertex[i*4 + 3].y = xdata.height;
                paVertex[i*4 + 3].z = 0.0f;
                paVertex[i*4 + 3].tu = (float)((1.0 / xdata.col_texture_split) - du);
                paVertex[i*4 + 3].tv = (float)((1.0 / xdata.row_texture_split) - dv);
                paVertex[i*4 + 3].index = (float)i;
            } else if (i == 0 || i == 2 || i == 6 || i == 8 ) {
                //�S�p
                //����
                paVertex[i*4 + 0].x = 0.0f;
                paVertex[i*4 + 0].y = 0.0f;
                paVertex[i*4 + 0].z = 0.0f;
                paVertex[i*4 + 0].tu = (float)du;
                paVertex[i*4 + 0].tv = (float)dv;
                paVertex[i*4 + 0].index = (float)i;
                //�E��
                paVertex[i*4 + 1].x = xdata_frame.width;
                paVertex[i*4 + 1].y = 0.0f;
                paVertex[i*4 + 1].z = 0.0f;
                paVertex[i*4 + 1].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 1].tv = (float)dv;
                paVertex[i*4 + 1].index = (float)i;
                //����
                paVertex[i*4 + 2].x = 0.0f;
                paVertex[i*4 + 2].y = xdata_frame.height;
                paVertex[i*4 + 2].z = 0.0f;
                paVertex[i*4 + 2].tu = (float)du;
                paVertex[i*4 + 2].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 2].index = (float)i;
                //�E��
                paVertex[i*4 + 3].x = xdata_frame.width;
                paVertex[i*4 + 3].y = xdata_frame.height;
                paVertex[i*4 + 3].z = 0.0f;
                paVertex[i*4 + 3].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 3].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 3].index = (float)i;
            } else if (i == 1 || i == 7) {
                //�c�̐^��
                //����
                paVertex[i*4 + 0].x = 0.0f;
                paVertex[i*4 + 0].y = 0.0f;
                paVertex[i*4 + 0].z = 0.0f;
                paVertex[i*4 + 0].tu = (float)du;
                paVertex[i*4 + 0].tv = (float)dv;
                paVertex[i*4 + 0].index = (float)i;
                //�E��
                paVertex[i*4 + 1].x = xdata.width;
                paVertex[i*4 + 1].y = 0.0f;
                paVertex[i*4 + 1].z = 0.0f;
                paVertex[i*4 + 1].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 1].tv = (float)dv;
                paVertex[i*4 + 1].index = (float)i;
                //����
                paVertex[i*4 + 2].x = 0.0f;
                paVertex[i*4 + 2].y = xdata_frame.height;
                paVertex[i*4 + 2].z = 0.0f;
                paVertex[i*4 + 2].tu = (float)du;
                paVertex[i*4 + 2].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 2].index = (float)i;
                //�E��
                paVertex[i*4 + 3].x = xdata.width;
                paVertex[i*4 + 3].y = xdata_frame.height;
                paVertex[i*4 + 3].z = 0.0f;
                paVertex[i*4 + 3].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 3].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 3].index = (float)i;
            } else if (i == 3 || i == 5) {
                //���̐^��
                //����
                paVertex[i*4 + 0].x = 0.0f;
                paVertex[i*4 + 0].y = 0.0f;
                paVertex[i*4 + 0].z = 0.0f;
                paVertex[i*4 + 0].tu = (float)du;
                paVertex[i*4 + 0].tv = (float)dv;
                paVertex[i*4 + 0].index = (float)i;
                //�E��
                paVertex[i*4 + 1].x = xdata_frame.width;
                paVertex[i*4 + 1].y = 0.0f;
                paVertex[i*4 + 1].z = 0.0f;
                paVertex[i*4 + 1].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 1].tv = (float)dv;
                paVertex[i*4 + 1].index = (float)i;
                //����
                paVertex[i*4 + 2].x = 0.0f;
                paVertex[i*4 + 2].y = xdata.height;
                paVertex[i*4 + 2].z = 0.0f;
                paVertex[i*4 + 2].tu = (float)du;
                paVertex[i*4 + 2].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 2].index = (float)i;
                //�E��
                paVertex[i*4 + 3].x = xdata_frame.width;
                paVertex[i*4 + 3].y = xdata.height;
                paVertex[i*4 + 3].z = 0.0f;
                paVertex[i*4 + 3].tu = (float)((1.0 / xdata_frame.col_texture_split) - du);
                paVertex[i*4 + 3].tv = (float)((1.0 / xdata_frame.row_texture_split) - dv);
                paVertex[i*4 + 3].index = (float)i;
            }
         }

        //�o�b�t�@�쐬
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices * _set_num,
                D3DUSAGE_WRITEONLY,
                GgafDxFramedBoardModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));
        //���_�o�b�t�@�쐬
        //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(
                                 0,
                                 _size_vertices * _set_num,
                                 (void**)&pVertexBuffer,
                                 0
                               );
        checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);

        memcpy(
          pVertexBuffer,
          paVertex,
          _size_vertices * _set_num
        ); //pVertexBuffer �� paVertex
        _pVertexBuffer->Unlock();

        GGAF_DELETEARR(paVertex);
    }


    //�C���f�b�N�X�o�b�t�@�쐬
    if (_pIndexBuffer == nullptr) {
        int nVertices = 4;
        int nFaces = 2;
        WORD* unit_paIdxBuffer = NEW WORD[(nFaces*3)];
        unit_paIdxBuffer[0] = 0;
        unit_paIdxBuffer[1] = 1;
        unit_paIdxBuffer[2] = 2;

        unit_paIdxBuffer[3] = 1;
        unit_paIdxBuffer[4] = 3;
        unit_paIdxBuffer[5] = 2;

        WORD* paIdxBufferSet = NEW WORD[(nFaces*3) * _set_num];
        for (int i = 0; i < _set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer[j*3 + 0] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer[j*3 + 1] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer[j*3 + 2] + (nVertices*i);
            }
        }

        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * nFaces * 3 * _set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer ���s model="<<(_model_name));

        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          paIdxBufferSet,
          sizeof(WORD) * nFaces * 3 * _set_num
        );
        _pIndexBuffer->Unlock();
        GGAF_DELETEARR(unit_paIdxBuffer);
        GGAF_DELETEARR(paIdxBufferSet);

        //�`�掞�p�����[�^�[
        _indexParam.MaterialNo = 0;
        _indexParam.BaseVertexIndex = 0;
        _indexParam.MinIndex = 0;
        _indexParam.NumVertices = nVertices*_set_num;
        _indexParam.StartIndex = 0;
        _indexParam.PrimitiveCount = nFaces*_set_num;
    }

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

void GgafDxFramedBoardModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxFramedBoardModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);
    //�e�N�X�`�������
    if (_papTextureConnection) {
        _papTextureConnection[0]->close();
        _papTextureConnection[1]->close(); //�t���[��
    }
    GGAF_DELETEARR(_papTextureConnection);
    //TODO:�e�N���X�����o��DELETE����̂͂�₫���Ȃ���
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_name=" << _model_name << " end");
}

GgafDxFramedBoardModel::~GgafDxFramedBoardModel() {
    //release();
    //��GgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) �ŌĂяo�����
}
