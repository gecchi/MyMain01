#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteEffect::GgafDx9SpriteEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
//    //VIEW変換行列
//    hr = _pID3DXEffect->SetMatrix( "g_matView", &GgafDx9God::_vMatrixView );
//    checkDxException(hr, D3D_OK, "GgafDx9SpriteEffect::GgafDx9SpriteEffect SetMatrix(g_matView) に失敗しました。");
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", &P_CAM->_vMatrixProj );
    checkDxException(hr, D3D_OK, "GgafDx9SpriteEffect::GgafDx9SpriteEffect SetMatrix() に失敗しました。");

    hr = _pID3DXEffect->SetFloat("g_zf", P_CAM->_zf);
    checkDxException(hr, D3D_OK, "GgafDx9SpriteEffect::GgafDx9SpriteEffect SetFloat(g_zf) に失敗しました。");


    //シェーダーハンドル
    _h_matView  = _pID3DXEffect->GetParameterByName( NULL, "g_matView" );
    _h_matWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _hAlpha    = _pID3DXEffect->GetParameterByName( NULL, "g_hAlpha" );
    _hOffsetU  = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU" );
    _hOffsetV  = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_threshold" );
}

void GgafDx9SpriteEffect::setParamPerFrame() {
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, &P_CAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) に失敗しました。");
}

GgafDx9SpriteEffect::~GgafDx9SpriteEffect() {
}

