#include "jp/ggaf/dx/model/BoardModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/actor/BoardActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/BoardEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;

DWORD BoardModel::FVF = (D3DFVF_XYZ | D3DFVF_TEX1);

BoardModel::BoardModel(const char* prm_model_name) :
    Model(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _obj_model |= Obj_GgafDx_BoardModel;
}

HRESULT BoardModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("BoardModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    //�Ώ�Actor
    const BoardActor* const pTargetActor = (BoardActor*)prm_pActor_target;
    //�Ώ�BoardActor�̃G�t�F�N�g���b�p
    BoardEffect* const pBoardEffect = (BoardEffect*)prm_pActor_target->getEffect();
    //�ΏۃG�t�F�N�g
    ID3DXEffect* const pID3DXEffect = pBoardEffect->_pID3DXEffect;
    //����`���UV
    float u,v;
    pTargetActor->_pUvFlipper->getUV(u,v);
    HRESULT hr;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(BoardModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pBoardEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) �Ɏ��s���܂����B");
        hr = pID3DXEffect->SetFloat(pBoardEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) �Ɏ��s���܂����B");
    }
    hr = pID3DXEffect->SetFloat(pBoardEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(pBoardEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) �Ɏ��s���܂����B");
    Effect* pEffect_active = EffectManager::_pEffect_active;
    if (FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") �Ɏ��s���܂����B");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name);
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() �Ɏ��s���܂����B");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) �Ɏ��s���܂����B");

#ifdef MY_DEBUG
        if (pBoardEffect->_begin) {
            throwCriticalException("End ���Ă��܂��� "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pBoardEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() �Ɏ��s���܂����B");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardEffect->_effect_name<<"("<<pBoardEffect<<")");
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    //�O��`�惂�f���ێ�
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pBoardEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif

    return D3D_OK;
}

void BoardModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    HRESULT hr;
    ModelManager* pModelManager = pGOD->_pModelManager;
    std::string xfile_name = ModelManager::getSpriteFileName(_model_name, "sprx");
    ModelManager::SpriteXFileFmt xdata;
    pModelManager->obtainSpriteInfo(&xdata, xfile_name);
    _model_width_px  = xdata.width;
    _model_height_px = xdata.height;
    _row_texture_split = xdata.row_texture_split;
    _col_texture_split = xdata.col_texture_split;

    //�e�N�X�`���擾�����f���ɕێ�������
    _papTextureConnection = NEW TextureConnection*[1];
    _papTextureConnection[0] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(xdata.texture_file, this));

    BoardModel::VERTEX* paVertex = NEW BoardModel::VERTEX[4];
    _size_vertices = sizeof(BoardModel::VERTEX)*4;
    _size_vertex_unit = sizeof(BoardModel::VERTEX);

    //1px�������uv�̑傫�������߂�
//    float tex_width  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
//    float tex_height = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)
    double du = 0.0;
    double dv = 0.0;

    //����
    paVertex[0].x = 0.0f;
    paVertex[0].y = 0.0f;
    paVertex[0].z = 0.0f;
    paVertex[0].tu = (float)du;
    paVertex[0].tv = (float)dv;
    //�E��
    paVertex[1].x = xdata.width;
    paVertex[1].y = 0.0f;
    paVertex[1].z = 0.0f;
    paVertex[1].tu = (float)((1.0 / xdata.col_texture_split) - du);
    paVertex[1].tv = (float)dv;
    //����
    paVertex[2].x = 0.0f;
    paVertex[2].y = xdata.height;
    paVertex[2].z = 0.0f;
    paVertex[2].tu = (float)du;
    paVertex[2].tv = (float)((1.0 / xdata.row_texture_split) - dv);
    //�E��
    paVertex[3].x = xdata.width;
    paVertex[3].y = xdata.height;
    paVertex[3].z = 0.0f;
    paVertex[3].tu = (float)((1.0 / xdata.col_texture_split) - du);
    paVertex[3].tv = (float)((1.0 / xdata.row_texture_split) - dv);

    //�o�b�t�@�쐬
    if (_pVertexBuffer == nullptr) {

        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                BoardModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer ���s model="<<(_model_name));
    }
    //���_�o�b�t�@�쐬
    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
    checkDxException(hr, D3D_OK, "���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<_model_name);

    memcpy(pVertexBuffer, paVertex, _size_vertices); //pVertexBuffer �� paVertex
    _pVertexBuffer->Unlock();
    _num_materials = 1;
    D3DMATERIAL9* paMaterial;
    paMaterial = NEW D3DMATERIAL9[_num_materials];
    for ( DWORD i = 0; i < _num_materials; i++) {
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

    GGAF_DELETEARR(paVertex);
    _TRACE3_("_model_name=" << _model_name << " end");
}

void BoardModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    //�e�N�X�`�������
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_name=" << _model_name << " end");
}

void BoardModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

BoardModel::~BoardModel() {
    //release();
    //��ModelConnection::processReleaseResource(Model* prm_pResource) �ŌĂяo�����
}