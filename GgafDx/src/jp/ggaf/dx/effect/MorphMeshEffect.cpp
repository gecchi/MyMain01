#include "jp/ggaf/dx/effect/MorphMeshEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

MorphMeshEffect::MorphMeshEffect(const char* prm_effect_name) : World3DimEffect(prm_effect_name) {
    _obj_class |= Obj_GgafDx_MorphMeshEffect;
    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
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
    _h_morph_target_num = _pID3DXEffect->GetParameterByName(nullptr, "g_morph_target_num");
    _ah_weight[1] = _pID3DXEffect->GetParameterByName(nullptr, "g_weight1");
    _ah_weight[2] = _pID3DXEffect->GetParameterByName(nullptr, "g_weight2");
    _ah_weight[3] = _pID3DXEffect->GetParameterByName(nullptr, "g_weight3");
    _ah_weight[4] = _pID3DXEffect->GetParameterByName(nullptr, "g_weight4");
    _ah_weight[5] = _pID3DXEffect->GetParameterByName(nullptr, "g_weight5");
    _ah_weight[6] = _pID3DXEffect->GetParameterByName(nullptr, "g_weight6");

    for (int i = 1; i <= MAX_MORPH_TARGET; i++) {
        hr = _pID3DXEffect->SetFloat(_ah_weight[i], 0.0f);
        checkDxException(hr, D3D_OK, "SetFloat(_ah_weight["<<i<<"]) に失敗しました。");
    }
    _h_matWorld = _pID3DXEffect->GetParameterByName(nullptr, "g_matWorld");
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName(nullptr, "g_colMaterialDiffuse");
    _h_specular = _pID3DXEffect->GetParameterByName( nullptr, "g_specular" );
    _h_specular_power = _pID3DXEffect->GetParameterByName( nullptr, "g_specular_power" );
    _h_posCam = _pID3DXEffect->GetParameterByName( nullptr, "g_posCam_World" );
}

void MorphMeshEffect::setParamPerFrame() {
    World3DimEffect::setParamPerFrame();
    Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    HRESULT hr = _pID3DXEffect->SetValue(_h_posCam, pCam->getVecCamFromPoint(), sizeof(D3DXVECTOR3) );
    checkDxException(hr, D3D_OK, "SetValue(_h_posCam) に失敗しました。");
}

MorphMeshEffect::~MorphMeshEffect() {
}

