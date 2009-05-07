#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MorphTwoMeshEffect::GgafDx9MorphTwoMeshEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {

    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &GgafDx9Universe::_pCamera->_vMatrixProj );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MorphTwoMeshEffect SetMatrix() に失敗しました。");
    //ライト方向
    hr = _pID3DXEffect->SetValue("g_LightDirection", &(GgafDx9God::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshEffect::GgafDx9MorphTwoMeshEffect SetValue(g_LightDirection) に失敗しました。");
    //Diffuse反射
    hr = _pID3DXEffect->SetValue("g_LightDiffuse", &(GgafDx9God::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshEffect::GgafDx9MorphTwoMeshEffect SetValue(g_LightDiffuse) に失敗しました。");
    //Ambient反射
    hr = _pID3DXEffect->SetValue("g_LightAmbient", &(GgafDx9God::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    potentialDx9Exception(hr, D3D_OK, "GgafDx9MorphTwoMeshEffect::GgafDx9MorphTwoMeshEffect SetValue(g_LightAmbient) に失敗しました。");
    //シェーダーハンドル
    _hWeight = _pID3DXEffect->GetParameterByName( NULL, "g_weight" );
    _hMatView = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );
    _hMatWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _hMaterialDiffuse = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse" );
}


GgafDx9MorphTwoMeshEffect::~GgafDx9MorphTwoMeshEffect() {
}

