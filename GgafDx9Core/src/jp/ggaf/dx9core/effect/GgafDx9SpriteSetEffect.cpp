#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteSetEffect::GgafDx9SpriteSetEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
//    //VIEW変換行列
//    hr = _pID3DXEffect->SetMatrix( "g_matView", &GgafDx9God::_vMatrixView );
//    checkDxException(hr, D3D_OK, "GgafDx9SpriteSetEffect::GgafDx9SpriteSetEffect SetMatrix(g_matView) に失敗しました。");
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &pCAM->_vMatrixProj );
    checkDxException(hr, D3D_OK, "GgafDx9SpriteSetEffect::GgafDx9SpriteSetEffect SetMatrix() に失敗しました。");
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
    _ahMatWorld[8] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld009" );
    _ahMatWorld[9] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld010" );
    _ahMatWorld[10] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld011" );
    _ahMatWorld[11] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld012" );
    _ahMatWorld[12] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld013" );
    _ahMatWorld[13] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld014" );
    _ahMatWorld[14] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld015" );
    _ahMatWorld[15] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld016" );
    _ahMatWorld[16] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld017" );
    _ahMatWorld[17] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld018" );
//    _ahMatWorld[18] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld019" );
//    _ahMatWorld[19] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld020" );
//    _ahMatWorld[20] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld021" );
//    _ahMatWorld[21] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld022" );
//    _ahMatWorld[22] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld023" );
//    _ahMatWorld[23] = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld024" );

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
//    _ahOffsetU[18] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU019" );
//    _ahOffsetU[19] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU020" );
//    _ahOffsetU[20] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU021" );
//    _ahOffsetU[21] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU022" );
//    _ahOffsetU[22] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU023" );
//    _ahOffsetU[23] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU024" );

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
//    _ahOffsetV[18] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV019" );
//    _ahOffsetV[19] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV020" );
//    _ahOffsetV[20] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV021" );
//    _ahOffsetV[21] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV022" );
//    _ahOffsetV[22] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV023" );
//    _ahOffsetV[23] = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV024" );

    _ahAlpha[0] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha001" );
    _ahAlpha[1] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha002" );
    _ahAlpha[2] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha003" );
    _ahAlpha[3] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha004" );
    _ahAlpha[4] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha005" );
    _ahAlpha[5] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha006" );
    _ahAlpha[6] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha007" );
    _ahAlpha[7] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha008" );
    _ahAlpha[8] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha009" );
    _ahAlpha[9] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha010" );
    _ahAlpha[10] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha011" );
    _ahAlpha[11] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha012" );
    _ahAlpha[12] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha013" );
    _ahAlpha[13] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha014" );
    _ahAlpha[14] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha015" );
    _ahAlpha[15] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha016" );
    _ahAlpha[16] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha017" );
    _ahAlpha[17] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha018" );
//    _ahAlpha[18] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha019" );
//    _ahAlpha[19] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha020" );
//    _ahAlpha[20] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha021" );
//    _ahAlpha[21] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha022" );
//    _ahAlpha[22] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha023" );
//    _ahAlpha[23] = _pID3DXEffect->GetParameterByName( NULL, "g_alpha024" );
}

GgafDx9SpriteSetEffect::~GgafDx9SpriteSetEffect() {
}

