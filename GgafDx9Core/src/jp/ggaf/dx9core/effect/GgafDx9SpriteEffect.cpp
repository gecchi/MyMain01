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
    hr = _pID3DXEffect->SetMatrix("g_matProj", &GgafDx9God::_vMatrixProj );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9SpriteEffect::GgafDx9SpriteEffect SetMatrix() に失敗しました。");
    //シェーダーハンドル
    _hMatWorld = _pID3DXEffect->GetParameterByName( NULL, "g_matWorld" );
    _hAlpha = _pID3DXEffect->GetParameterByName( NULL, "g_hAlpha" );
    _hOffsetU = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU" );
    _hOffsetV = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV" );
}


GgafDx9SpriteEffect::~GgafDx9SpriteEffect() {
    TRACE3("GgafDx9SpriteEffect::~GgafDx9SpriteEffect() " << _effect_name << " start");
    TRACE3("GgafDx9SpriteEffect::~GgafDx9SpriteEffect() " << _effect_name << " end");
}

