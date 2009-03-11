#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BoardEffect::GgafDx9BoardEffect(char* prm_effect_name) : GgafDx9Effect(prm_effect_name) {
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    static float view_width_half = (float)(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)/2.0);
    static float view_height_half = (float)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)/2.0);

    hr = _pID3DXEffect->SetFloat("g_view_width_half", view_width_half);
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9BoardEffect::GgafDx9BoardEffect SetFloat(g_view_width_half) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_view_height_half", view_height_half);
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9BoardEffect::GgafDx9BoardEffect SetFloat(g_view_height_half) に失敗しました。");

    //ハンドル
    _hAlpha = _pID3DXEffect->GetParameterByName( NULL, "g_alpha" );
    _hOffsetU = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU" );
    _hOffsetV = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV" );

}


GgafDx9BoardEffect::~GgafDx9BoardEffect() {
    _TRACE_("GgafDx9BoardEffect::~GgafDx9BoardEffect() " << _effect_name << " start");
    _TRACE_("GgafDx9BoardEffect::~GgafDx9BoardEffect() " << _effect_name << " end");
}

