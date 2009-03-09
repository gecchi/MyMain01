#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteEffect::GgafDx9SpriteEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //VIEW変換行列
    hr = _pID3DXEffect->SetMatrix( "g_matView", &GgafDx9God::_vMatrixView );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteEffect::GgafDx9SpriteEffect SetMatrix(g_matView) に失敗しました。");
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &GgafDx9God::_vMatrixProjrction );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteEffect::GgafDx9SpriteEffect SetMatrix() に失敗しました。");

    //ライト方向. スプライトに陰影はありません
    //hr = _pID3DXEffect->SetValue("g_LightDirection", &(GgafDx9God::_d3dlight9_default.Direction), sizeof(D3DVECTOR) );
    //whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteEffect::GgafDx9SpriteEffect SetValue(g_LightDirection) に失敗しました。");
    //Diffuse反射. スプライトに陰影はありません
    //hr = _pID3DXEffect->SetValue("g_LightDiffuse", &(GgafDx9God::_d3dlight9_default.Diffuse), sizeof(D3DCOLORVALUE));
    //whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9PrimitiveModel::GgafDx9SpriteEffect SetValue(g_LightDiffuse) に失敗しました。");

//    //Ambient反射
//    hr = _pID3DXEffect->SetValue("g_LightAmbient", &(GgafDx9God::_d3dlight9_default.Ambient), sizeof(D3DCOLORVALUE));
//    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteEffect::GgafDx9SpriteEffect SetValue(g_LightAmbient) に失敗しました。");

//    //テクスチャの列分割数
//    hr = _pID3DXEffect->SetValue("g_RowTexSplit", &(_pSpriteModel->_row_texture_split), sizeof(int));
//    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteEffect::GgafDx9SpriteEffect SetValue(g_RowTexSplit) に失敗しました。");
//    //テクスチャの行分割数
//    hr = _pID3DXEffect->SetValue("g_ColTexSplit", &(_pSpriteModel->_col_texture_split), sizeof(int));
//    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteEffect::GgafDx9SpriteEffect SetValue(g_ColTexSplit) に失敗しました。");
    //シェーダーハンドル
    _hMatWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _hAlpha = _pID3DXEffect->GetParameterByName( NULL, "g_hAlpha" );
    _hOffsetU = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU" );
    _hOffsetV = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV" );
    //_hMaterialDiffuse = _pID3DXEffect->GetParameterByName( NULL, "g_MaterialDiffuse" );

}


GgafDx9SpriteEffect::~GgafDx9SpriteEffect() {
    _TRACE_("GgafDx9SpriteEffect::~GgafDx9SpriteEffect() " << _effect_name << " start");
    _TRACE_("GgafDx9SpriteEffect::~GgafDx9SpriteEffect() " << _effect_name << " end");
}

