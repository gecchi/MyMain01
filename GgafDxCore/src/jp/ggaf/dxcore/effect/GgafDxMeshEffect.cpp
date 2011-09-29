#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMeshEffect::GgafDxMeshEffect(char* prm_effect_name) : GgafDxEffect(prm_effect_name) {

    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &P_CAM->_matProj );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::GgafDxMeshEffect SetMatrix() に失敗しました。");
    //ライト方向
    hr = _pID3DXEffect->SetValue("g_vecLightDirection", &(GgafDxGod::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::GgafDxMeshEffect SetValue(g_vecLightDirection) に失敗しました。");
    //Diffuse反射
    hr = _pID3DXEffect->SetValue("g_colLightDiffuse", &(GgafDxGod::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::GgafDxMeshEffect SetValue(g_colLightDiffuse) に失敗しました。");
    //Ambient反射
    hr = _pID3DXEffect->SetValue("g_colLightAmbient", &(GgafDxGod::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::GgafDxMeshEffect SetValue(g_colLightAmbient) に失敗しました。");

    hr = _pID3DXEffect->SetFloat("g_zf", P_CAM->_zf);
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::GgafDxSpriteEffect SetFloat(g_zf) に失敗しました。");
    //シェーダーハンドル
    _h_matView = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );
    _h_matWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_threshold" );
    _h_offset_u = _pID3DXEffect->GetParameterByName( NULL, "g_offset_u" );
    _h_offset_v = _pID3DXEffect->GetParameterByName( NULL, "g_offset_v" );
    _h_specular = _pID3DXEffect->GetParameterByName( NULL, "g_specular" );
    _h_specular_power = _pID3DXEffect->GetParameterByName( NULL, "g_specular_power" );
    _h_posCam = _pID3DXEffect->GetParameterByName( NULL, "g_posCam" );
}

void GgafDxMeshEffect::setParamPerFrame() {
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, &(P_CAM->_matView) );
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::setParamPerFrame SetMatrix(_h_matView) に失敗しました。_effect_name="<<_effect_name);
    hr = _pID3DXEffect->SetValue(_h_posCam, P_CAM->_pVecCamFromPoint, sizeof(D3DXVECTOR3) );
    checkDxException(hr, D3D_OK, "GgafDxMeshEffect::setParamPerFrame SetValue(_h_posCam) に失敗しました。_effect_name="<<_effect_name);
}

GgafDxMeshEffect::~GgafDxMeshEffect() {
}

