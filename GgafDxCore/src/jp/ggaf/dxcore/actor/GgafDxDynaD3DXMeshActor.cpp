#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxDynaD3DXMeshActor::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDxDynaD3DXMeshActor::GgafDxDynaD3DXMeshActor(const char* prm_name,
                                                 const char* prm_model_id,
                                                 const char* prm_effect_id,
                                                 const char* prm_technique,
                                                 GgafStatus* prm_pStat,
                                                 GgafDxChecker* prm_pChecker) :

                                                     GgafDxDrawableActor(prm_name,
                                                                         prm_model_id,
                                                                         "d",
                                                                         prm_effect_id,
                                                                         "X",
                                                                         prm_technique,
                                                                         prm_pStat,
                                                                         prm_pChecker) {
    _obj_class |= Obj_GgafDxDynaD3DXMeshActor;
    _class_name = "GgafDxDynaD3DXMeshActor";

    _pD3DXMeshModel = (GgafDxD3DXMeshModel*)_pModel;
    _pMeshEffect = (GgafDxMeshEffect*)_pEffect;
    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
}

void GgafDxDynaD3DXMeshActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix( _pMeshEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDxDynaD3DXMeshActor::GgafDxMeshEffect SetMatrix(g_matView) に失敗しました。");
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxDynaD3DXMeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");

    // Zバッファを有効に
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Zバッファ書き込み可
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

    _pD3DXMeshModel->draw(this);

    // Zバッファを無効に
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Zバッファ書き込み不可
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
}

void GgafDxDynaD3DXMeshActor::setAlpha(float prm_alpha) {
    _alpha = prm_alpha;
    //GgafDxDynaD3DXMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pD3DXMeshModel->_num_materials; i++) {
        _paMaterial[i].Ambient.a = _alpha;
        _paMaterial[i].Diffuse.a = _alpha;
    }
}

void GgafDxDynaD3DXMeshActor::addAlpha(float prm_alpha) {
    _alpha += prm_alpha;
    //GgafDxDynaD3DXMeshActorはメッシュαも設定（シェーダーで参照するため）
    for (DWORD i = 0; i < _pD3DXMeshModel->_num_materials; i++) {
        _paMaterial[i].Ambient.a = _alpha;
        _paMaterial[i].Diffuse.a = _alpha;
    }
}

GgafDxDynaD3DXMeshActor::~GgafDxDynaD3DXMeshActor() {
}
