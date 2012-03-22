#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBoardEffect::GgafDxBoardEffect(char* prm_effect_name) : GgafDxEffect(prm_effect_name) {
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    static float game_buffer_width = (float)(GGAF_PROPERTY(GAME_BUFFER_WIDTH));
    static float game_buffer_height = (float)(GGAF_PROPERTY(GAME_BUFFER_HEIGHT));

    hr = _pID3DXEffect->SetFloat("g_game_buffer_width", game_buffer_width);
    checkDxException(hr, D3D_OK, "GgafDxBoardEffect::GgafDxBoardEffect SetFloat(g_game_buffer_width) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_game_buffer_height", game_buffer_height);
    checkDxException(hr, D3D_OK, "GgafDxBoardEffect::GgafDxBoardEffect SetFloat(g_game_buffer_height) に失敗しました。");

    //ハンドル
    _h_alpha = _pID3DXEffect->GetParameterByName( NULL, "g_alpha" );
    _h_offset_u = _pID3DXEffect->GetParameterByName( NULL, "g_offset_u" );
    _h_offset_v = _pID3DXEffect->GetParameterByName( NULL, "g_offset_v" );
    _hTransformedX = _pID3DXEffect->GetParameterByName( NULL, "g_transformed_X" );
    _hTransformedY = _pID3DXEffect->GetParameterByName( NULL, "g_transformed_Y" );
    _hDepthZ = _pID3DXEffect->GetParameterByName( NULL, "g_depth_Z" );
    _hSx = _pID3DXEffect->GetParameterByName( NULL, "g_sx" );
    _hSy = _pID3DXEffect->GetParameterByName( NULL, "g_sy" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( NULL, "g_tex_blink_threshold" );
}


GgafDxBoardEffect::~GgafDxBoardEffect() {
}

