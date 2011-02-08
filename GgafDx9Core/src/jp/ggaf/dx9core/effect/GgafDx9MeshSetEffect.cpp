#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshSetEffect::GgafDx9MeshSetEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {

    //シェーダー共通のグローバル変数設定
    HRESULT hr;

    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &P_CAM->_vMatrixProj );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshSetEffect SetMatrix() に失敗しました。");
    //ライト方向
    hr = _pID3DXEffect->SetValue("g_vecLightDirection", &(GgafDx9God::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetEffect::GgafDx9MeshSetEffect SetValue(g_vecLightDirection) に失敗しました。");
    //Diffuse反射
    hr = _pID3DXEffect->SetValue("g_colLightDiffuse", &(GgafDx9God::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetEffect::GgafDx9MeshSetEffect SetValue(g_colLightDiffuse) に失敗しました。");
    //Ambient反射
    hr = _pID3DXEffect->SetValue("g_colLightAmbient", &(GgafDx9God::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetEffect::GgafDx9MeshSetEffect SetValue(g_colLightAmbient) に失敗しました。");

    hr = _pID3DXEffect->SetFloat("g_zf", P_CAM->_zf);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetEffect::GgafDx9SpriteEffect SetFloat(g_zf) に失敗しました。");

    //シェーダーハンドル
    _h_matView = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );
    _ah_matWorld[0]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld001" );
    _ah_matWorld[1]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld002" );
    _ah_matWorld[2]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld003" );
    _ah_matWorld[3]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld004" );
    _ah_matWorld[4]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld005" );
    _ah_matWorld[5]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld006" );
    _ah_matWorld[6]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld007" );
    _ah_matWorld[7]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld008" );
    _ah_matWorld[8]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld009" );
    _ah_matWorld[9]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld010" );
    _ah_matWorld[10]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld011" );
    _ah_matWorld[11]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld012" );
    _ah_matWorld[12]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld013" );
    _ah_matWorld[13]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld014" );
    _ah_matWorld[14]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld015" );
    _ah_matWorld[15]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld016" );
    _ah_matWorld[16]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld017" );
    _ah_matWorld[17]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld018" );
    _ah_matWorld[18]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld019" );
//    _ah_matWorld[19]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld020" );



    _ah_materialDiffuse[0] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse001" );
    _ah_materialDiffuse[1] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse002" );
    _ah_materialDiffuse[2] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse003" );
    _ah_materialDiffuse[3] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse004" );
    _ah_materialDiffuse[4] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse005" );
    _ah_materialDiffuse[5] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse006" );
    _ah_materialDiffuse[6] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse007" );
    _ah_materialDiffuse[7] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse008" );
    _ah_materialDiffuse[8] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse009" );
    _ah_materialDiffuse[9] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse010" );
    _ah_materialDiffuse[10] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse011" );
    _ah_materialDiffuse[11] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse012" );
    _ah_materialDiffuse[12] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse013" );
    _ah_materialDiffuse[13] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse014" );
    _ah_materialDiffuse[14] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse015" );
    _ah_materialDiffuse[15] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse016" );
    _ah_materialDiffuse[16] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse017" );
    _ah_materialDiffuse[17] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse018" );
    _ah_materialDiffuse[18] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse019" );
//    _ah_materialDiffuse[19] = _pID3DXEffect->GetParameterByName( NULL, "g_colMaterialDiffuse020" );


    _ahOffsetU[0] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU001" );
    _ahOffsetU[1] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU002" );
    _ahOffsetU[2] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU003" );
    _ahOffsetU[3] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU004" );
    _ahOffsetU[4] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU005" );
    _ahOffsetU[5] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU006" );
    _ahOffsetU[6] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU007" );
    _ahOffsetU[7] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU008" );
    _ahOffsetU[8] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU009" );
    _ahOffsetU[9] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU010" );
    _ahOffsetU[10] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU011" );
    _ahOffsetU[11] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU012" );
    _ahOffsetU[12] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU013" );
    _ahOffsetU[13] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU014" );
    _ahOffsetU[14] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU015" );
    _ahOffsetU[15] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU016" );
    _ahOffsetU[16] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU017" );
    _ahOffsetU[17] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU018" );
    _ahOffsetU[18] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU019" );
//    _ahOffsetU[19] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU020" );


    _ahOffsetV[0] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV001" );
    _ahOffsetV[1] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV002" );
    _ahOffsetV[2] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV003" );
    _ahOffsetV[3] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV004" );
    _ahOffsetV[4] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV005" );
    _ahOffsetV[5] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV006" );
    _ahOffsetV[6] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV007" );
    _ahOffsetV[7] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV008" );
    _ahOffsetV[8] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV009" );
    _ahOffsetV[9] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV010" );
    _ahOffsetV[10] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV011" );
    _ahOffsetV[11] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV012" );
    _ahOffsetV[12] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV013" );
    _ahOffsetV[13] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV014" );
    _ahOffsetV[14] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV015" );
    _ahOffsetV[15] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV016" );
    _ahOffsetV[16] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV017" );
    _ahOffsetV[17] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV018" );
    _ahOffsetV[18] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV019" );
//    _ahOffsetV[19] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV020" );


    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_threshold" );
}

void GgafDx9MeshSetEffect::setParamPerFrame() {
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, &P_CAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) に失敗しました。");
}

GgafDx9MeshSetEffect::~GgafDx9MeshSetEffect() {
}

