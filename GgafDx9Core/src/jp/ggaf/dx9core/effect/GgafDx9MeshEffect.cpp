#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshEffect::GgafDx9MeshEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {

    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &pCAM->_vMatrixProj );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix() に失敗しました。");
    //ライト方向
    hr = _pID3DXEffect->SetValue("g_LightDirection", &(GgafDx9God::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "GgafDx9MeshEffect::GgafDx9MeshEffect SetValue(g_LightDirection) に失敗しました。");
    //Diffuse反射
    hr = _pID3DXEffect->SetValue("g_LightDiffuse", &(GgafDx9God::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDx9MeshEffect::GgafDx9MeshEffect SetValue(g_LightDiffuse) に失敗しました。");
    //Ambient反射
    hr = _pID3DXEffect->SetValue("g_LightAmbient", &(GgafDx9God::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDx9MeshEffect::GgafDx9MeshEffect SetValue(g_LightAmbient) に失敗しました。");
    //シェーダーハンドル
    _hMatView = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );
    _hMatWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _hMaterialDiffuse = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse" );
    _hPowerBlink = _pID3DXEffect->GetParameterByName( NULL, "g_PowerBlink" );
    _hBlinkThreshold = _pID3DXEffect->GetParameterByName( NULL, "g_BlinkThreshold" );
    _h_offset_u = _pID3DXEffect->GetParameterByName( NULL, "g_offset_u" );
    _h_offset_v = _pID3DXEffect->GetParameterByName( NULL, "g_offset_v" );

}


GgafDx9MeshEffect::~GgafDx9MeshEffect() {
}

