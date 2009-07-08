#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshSetEffect::GgafDx9MeshSetEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {

    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &GgafDx9Universe::_pCamera->_vMatrixProj );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshSetEffect SetMatrix() に失敗しました。");
    //ライト方向
    hr = _pID3DXEffect->SetValue("g_LightDirection", &(GgafDx9God::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetEffect::GgafDx9MeshSetEffect SetValue(g_LightDirection) に失敗しました。");
    //Diffuse反射
    hr = _pID3DXEffect->SetValue("g_LightDiffuse", &(GgafDx9God::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetEffect::GgafDx9MeshSetEffect SetValue(g_LightDiffuse) に失敗しました。");
    //Ambient反射
    hr = _pID3DXEffect->SetValue("g_LightAmbient", &(GgafDx9God::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
    mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetEffect::GgafDx9MeshSetEffect SetValue(g_LightAmbient) に失敗しました。");
    //シェーダーハンドル
    _hMatView = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );
    //_hMatWorld  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _ahMatWorld[0]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld001" );

    _ahMatWorld[1]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld002" );

    _ahMatWorld[2]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld003" );
    _ahMatWorld[3]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld004" );

    _ahMatWorld[4]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld005" );
    _ahMatWorld[5]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld006" );
    _ahMatWorld[6]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld007" );
    _ahMatWorld[7]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld008" );

    _ahMatWorld[8]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld009" );
    _ahMatWorld[9]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld010" );
    _ahMatWorld[10] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld011" );
    _ahMatWorld[11] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld012" );
    _ahMatWorld[12] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld013" );
    _ahMatWorld[13] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld014" );
    _ahMatWorld[14] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld015" );
    _ahMatWorld[15] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld016" );

    _hMaterialDiffuse = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse" );
    _h_nVertexs = _pID3DXEffect->GetParameterByName( NULL, "g_nVertexs" );

}


GgafDx9MeshSetEffect::~GgafDx9MeshSetEffect() {
}

