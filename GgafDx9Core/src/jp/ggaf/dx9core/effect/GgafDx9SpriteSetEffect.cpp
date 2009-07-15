#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteSetEffect::GgafDx9SpriteSetEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
//    //VIEW変換行列
//    hr = _pID3DXEffect->SetMatrix( "g_matView", &GgafDx9God::_vMatrixView );
//    mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetEffect::GgafDx9SpriteSetEffect SetMatrix(g_matView) に失敗しました。");
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &GgafDx9Universe::_pCamera->_vMatrixProj );
    mightDx9Exception(hr, D3D_OK, "GgafDx9SpriteSetEffect::GgafDx9SpriteSetEffect SetMatrix() に失敗しました。");
    //シェーダーハンドル
    _hMatView  = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );
    _ahMatWorld[0] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld001" );
    _ahMatWorld[1] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld002" );
    _ahMatWorld[2] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld003" );
    _ahMatWorld[3] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld004" );
    _ahMatWorld[4] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld005" );
    _ahMatWorld[5] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld006" );
    _ahMatWorld[6] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld007" );
    _ahMatWorld[7] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld008" );

    _ahOffsetU[0] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU001" );
    _ahOffsetU[1] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU002" );
    _ahOffsetU[2] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU003" );
    _ahOffsetU[3] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU004" );
    _ahOffsetU[4] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU005" );
    _ahOffsetU[5] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU006" );
    _ahOffsetU[6] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU007" );
    _ahOffsetU[7] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU008" );

    _ahOffsetV[0] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV001" );
    _ahOffsetV[1] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV002" );
    _ahOffsetV[2] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV003" );
    _ahOffsetV[3] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV004" );
    _ahOffsetV[4] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV005" );
    _ahOffsetV[5] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV006" );
    _ahOffsetV[6] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV007" );
    _ahOffsetV[7] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV008" );

    _ahAlpha[0] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha001" );
    _ahAlpha[1] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha002" );
    _ahAlpha[2] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha003" );
    _ahAlpha[3] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha004" );
    _ahAlpha[4] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha005" );
    _ahAlpha[5] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha006" );
    _ahAlpha[6] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha007" );
    _ahAlpha[7] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha008" );
}

GgafDx9SpriteSetEffect::~GgafDx9SpriteSetEffect() {
}

