#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMeshSetEffect::GgafDxMeshSetEffect(char* prm_effect_name) : GgafDxEffect(prm_effect_name) {
    //シェーダー共通のグローバル変数設定
    HRESULT hr;

    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &P_CAM->_matProj );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::GgafDxMeshSetEffect SetMatrix() に失敗しました。");
    //ライト方向
    hr = _pID3DXEffect->SetValue("g_vecLightFrom_World", &(GgafDxGod::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "GgafDxMeshSetEffect::GgafDxMeshSetEffect SetValue(g_vecLightFrom_World) に失敗しました。");
    //Diffuse反射
    hr = _pID3DXEffect->SetValue("g_colLightDiffuse", &(GgafDxGod::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDxMeshSetEffect::GgafDxMeshSetEffect SetValue(g_colLightDiffuse) に失敗しました。");
    //Ambient反射
    hr = _pID3DXEffect->SetValue("g_colLightAmbient", &(GgafDxGod::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDxMeshSetEffect::GgafDxMeshSetEffect SetValue(g_colLightAmbient) に失敗しました。");

    hr = _pID3DXEffect->SetFloat("g_zf", P_CAM->_zf);
    checkDxException(hr, D3D_OK, "GgafDxMeshSetEffect::GgafDxSpriteEffect SetFloat(g_zf) に失敗しました。");

    //シェーダーハンドル
    _h_matView = _pID3DXEffect->GetParameterByName( nullptr, "g_matView" );
    _ah_matWorld[0]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld001" );
    _ah_matWorld[1]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld002" );
    _ah_matWorld[2]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld003" );
    _ah_matWorld[3]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld004" );
    _ah_matWorld[4]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld005" );
    _ah_matWorld[5]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld006" );
    _ah_matWorld[6]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld007" );
    _ah_matWorld[7]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld008" );
    _ah_matWorld[8]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld009" );
    _ah_matWorld[9]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld010" );
    _ah_matWorld[10]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld011" );
    _ah_matWorld[11]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld012" );
    _ah_matWorld[12]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld013" );
    _ah_matWorld[13]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld014" );
    _ah_matWorld[14]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld015" );
    _ah_matWorld[15]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld016" );
    _ah_matWorld[16]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld017" );
    _ah_matWorld[17]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld018" );
    _ah_matWorld[18]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld019" );
//    _ah_matWorld[19]  = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld020" );



    _ah_materialDiffuse[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse001" );
    _ah_materialDiffuse[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse002" );
    _ah_materialDiffuse[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse003" );
    _ah_materialDiffuse[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse004" );
    _ah_materialDiffuse[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse005" );
    _ah_materialDiffuse[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse006" );
    _ah_materialDiffuse[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse007" );
    _ah_materialDiffuse[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse008" );
    _ah_materialDiffuse[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse009" );
    _ah_materialDiffuse[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse010" );
    _ah_materialDiffuse[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse011" );
    _ah_materialDiffuse[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse012" );
    _ah_materialDiffuse[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse013" );
    _ah_materialDiffuse[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse014" );
    _ah_materialDiffuse[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse015" );
    _ah_materialDiffuse[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse016" );
    _ah_materialDiffuse[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse017" );
    _ah_materialDiffuse[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse018" );
    _ah_materialDiffuse[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse019" );
//    _ah_materialDiffuse[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse020" );


    _ah_offset_u[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u001" );
    _ah_offset_u[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u002" );
    _ah_offset_u[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u003" );
    _ah_offset_u[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u004" );
    _ah_offset_u[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u005" );
    _ah_offset_u[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u006" );
    _ah_offset_u[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u007" );
    _ah_offset_u[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u008" );
    _ah_offset_u[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u009" );
    _ah_offset_u[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u010" );
    _ah_offset_u[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u011" );
    _ah_offset_u[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u012" );
    _ah_offset_u[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u013" );
    _ah_offset_u[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u014" );
    _ah_offset_u[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u015" );
    _ah_offset_u[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u016" );
    _ah_offset_u[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u017" );
    _ah_offset_u[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u018" );
    _ah_offset_u[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u019" );
//    _ah_offset_u[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u020" );


    _ah_offset_v[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v001" );
    _ah_offset_v[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v002" );
    _ah_offset_v[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v003" );
    _ah_offset_v[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v004" );
    _ah_offset_v[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v005" );
    _ah_offset_v[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v006" );
    _ah_offset_v[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v007" );
    _ah_offset_v[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v008" );
    _ah_offset_v[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v009" );
    _ah_offset_v[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v010" );
    _ah_offset_v[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v011" );
    _ah_offset_v[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v012" );
    _ah_offset_v[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v013" );
    _ah_offset_v[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v014" );
    _ah_offset_v[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v015" );
    _ah_offset_v[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v016" );
    _ah_offset_v[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v017" );
    _ah_offset_v[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v018" );
    _ah_offset_v[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v019" );
//    _ah_offset_v[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v020" );


    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
    _h_specular = _pID3DXEffect->GetParameterByName( nullptr, "g_specular" );
    _h_specular_power = _pID3DXEffect->GetParameterByName( nullptr, "g_specular_power" );
    _h_posCam = _pID3DXEffect->GetParameterByName( nullptr, "g_posCam_World" );
}

void GgafDxMeshSetEffect::setParamPerFrame() {
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, &(P_CAM->_matView) );
    checkDxException(hr, D3D_OK, "GgafDxMeshSetEffect::setParamPerFrame SetMatrix(_h_matView) に失敗しました。_effect_name="<<_effect_name);
    hr = _pID3DXEffect->SetValue(_h_posCam, P_CAM->_pVecCamFromPoint, sizeof(D3DXVECTOR3) );
    checkDxException(hr, D3D_OK, "GgafDxMeshSetEffect::setParamPerFrame SetValue(_h_posCam) に失敗しました。_effect_name="<<_effect_name);
}

GgafDxMeshSetEffect::~GgafDxMeshSetEffect() {
}

