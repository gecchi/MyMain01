#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxD3DXMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
GgafDxD3DXMeshActor::GgafDxD3DXMeshActor(const char* prm_name,
                                                 const char* prm_model_id,
                                                 const char* prm_effect_id,
                                                 const char* prm_technique,
                                                 GgafStatus* prm_pStat,
                                                 GgafDxChecker* prm_pChecker) :

                                           GgafDxDrawableActor(prm_name,
                                                                prm_model_id,
                                                                "D",
                                                                prm_effect_id,
                                                                "X",
                                                                prm_technique,
                                                                prm_pStat,
                                                                prm_pChecker) {
    _obj_class |= Obj_GgafDxD3DXMeshActor;
    _class_name = "GgafDxD3DXMeshActor";
    _pD3DXMeshModel = (GgafDxD3DXMeshModel*)_pModel;
    _pMeshEffect = (GgafDxMeshEffect*)_pEffect;
    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
}

void GgafDxD3DXMeshActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //GgafDxD3DXMeshActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++) {
        _paMaterial[i].Ambient.a = _fAlpha;
        _paMaterial[i].Diffuse.a = _fAlpha;
    }
}

void GgafDxD3DXMeshActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //GgafDxD3DXMeshActor�̓��b�V�������ݒ�i�V�F�[�_�[�ŎQ�Ƃ��邽�߁j
    for (DWORD i = 0; i < _pD3DXMeshModel->_dwNumMaterials; i++) {
        _paMaterial[i].Ambient.a = _fAlpha;
        _paMaterial[i].Diffuse.a = _fAlpha;
    }
}

void GgafDxD3DXMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDxD3DXMeshActor::processDraw() SetMatrix(g_matView) �Ɏ��s���܂����B");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxD3DXMeshActor::processDraw() SetMatrix(g_matWorld) �Ɏ��s���܂����B");

    // Z�o�b�t�@��L����
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Z�o�b�t�@�������݉�
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

    _pD3DXMeshModel->draw(this);

    // Z�o�b�t�@�𖳌���
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Z�o�b�t�@�������ݕs��
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

}

GgafDxD3DXMeshActor::~GgafDxD3DXMeshActor() {
}
