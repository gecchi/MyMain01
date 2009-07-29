#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshSetEffect::GgafDx9MeshSetEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {

    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &pCAM->_vMatrixProj );
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
    _ahMatWorld[0]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld001" );
    _ahMatWorld[1]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld002" );
    _ahMatWorld[2]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld003" );
    _ahMatWorld[3]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld004" );
    _ahMatWorld[4]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld005" );
    _ahMatWorld[5]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld006" );
    _ahMatWorld[6]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld007" );
    _ahMatWorld[7]  = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld008" );

    _ahMaterialDiffuse[0] = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse001" );
    _ahMaterialDiffuse[1] = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse002" );
    _ahMaterialDiffuse[2] = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse003" );
    _ahMaterialDiffuse[3] = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse004" );
    _ahMaterialDiffuse[4] = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse005" );
    _ahMaterialDiffuse[5] = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse006" );
    _ahMaterialDiffuse[6] = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse007" );
    _ahMaterialDiffuse[7] = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse008" );

    _h_nVertexs = _pID3DXEffect->GetParameterByName( NULL, "g_nVertexs" );

}


GgafDx9MeshSetEffect::~GgafDx9MeshSetEffect() {
}

