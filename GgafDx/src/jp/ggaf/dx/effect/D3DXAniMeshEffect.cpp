#include "jp/ggaf/dx/effect/D3DXAniMeshEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

using namespace GgafDx;

D3DXAniMeshEffect::D3DXAniMeshEffect(const char* prm_effect_name) : World3DimEffect(prm_effect_name) {
    _obj_class |= Obj_GgafDx_D3DXAniMeshEffect;
    Camera* pCam = pCARETAKER->getSpacetime()->getCamera();
    D3DLIGHT9* pLight = &(pCARETAKER->_d3dlight9_default);
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //ライト方向
    hr = _pID3DXEffect->SetValue("g_vecLightFrom_World", &(pLight->Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "SetValue(g_vecLightFrom_World) に失敗しました。");
    //Diffuse反射
    hr = _pID3DXEffect->SetValue("g_colLightDiffuse", &(pLight->Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "SetValue(g_colLightDiffuse) に失敗しました。");
    //Ambient反射
    hr = _pID3DXEffect->SetValue("g_colLightAmbient", &(pLight->Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "SetValue(g_colLightAmbient) に失敗しました。");
    //シェーダーハンドル
    _h_matWorld = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
}


D3DXAniMeshEffect::~D3DXAniMeshEffect() {
}

