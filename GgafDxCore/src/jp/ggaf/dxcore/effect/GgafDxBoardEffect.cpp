#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBoardEffect::GgafDxBoardEffect(char* prm_effect_name) : GgafDxEffect(prm_effect_name) {
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    static float game_buffer_width = (float)(CFG_PROPERTY(GAME_BUFFER_WIDTH));
    static float game_buffer_height = (float)(CFG_PROPERTY(GAME_BUFFER_HEIGHT));

    hr = _pID3DXEffect->SetFloat("g_game_buffer_width", game_buffer_width);
    checkDxException(hr, D3D_OK, "GgafDxBoardEffect::GgafDxBoardEffect SetFloat(g_game_buffer_width) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_game_buffer_height", game_buffer_height);
    checkDxException(hr, D3D_OK, "GgafDxBoardEffect::GgafDxBoardEffect SetFloat(g_game_buffer_height) に失敗しました。");

    //ハンドル
    _hAlpha = _pID3DXEffect->GetParameterByName( NULL, "g_alpha" );
    _hOffsetU = _pID3DXEffect->GetParameterByName( NULL, "g_offsetU" );
    _hOffsetV = _pID3DXEffect->GetParameterByName( NULL, "g_offsetV" );
    _hTransformedX = _pID3DXEffect->GetParameterByName( NULL, "g_transformedX" );
    _hTransformedY = _pID3DXEffect->GetParameterByName( NULL, "g_transformedY" );
    _hDepthZ = _pID3DXEffect->GetParameterByName( NULL, "g_depthZ" );
    _hSx = _pID3DXEffect->GetParameterByName( NULL, "g_sx" );
    _hSy = _pID3DXEffect->GetParameterByName( NULL, "g_sy" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_threshold" );
}


GgafDxBoardEffect::~GgafDxBoardEffect() {
}

