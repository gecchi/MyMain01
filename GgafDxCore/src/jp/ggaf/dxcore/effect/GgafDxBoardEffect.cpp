#include "stdafx.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"

#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBoardEffect::GgafDxBoardEffect(char* prm_effect_name) : GgafDxEffect(prm_effect_name) {
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    static float game_buffer_width = (float)(PROPERTY::GAME_BUFFER_WIDTH);
    static float game_buffer_height = (float)(PROPERTY::GAME_BUFFER_HEIGHT);

    hr = _pID3DXEffect->SetFloat("g_game_buffer_width", game_buffer_width);
    checkDxException(hr, D3D_OK, "GgafDxBoardEffect::GgafDxBoardEffect SetFloat(g_game_buffer_width) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_game_buffer_height", game_buffer_height);
    checkDxException(hr, D3D_OK, "GgafDxBoardEffect::GgafDxBoardEffect SetFloat(g_game_buffer_height) に失敗しました。");

    //ハンドル
    _h_offset_u = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u" );
    _h_offset_v = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v" );
    _hTransformedX = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_x" );
    _hTransformedY = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_y" );

    _h_local_left_top_x = _pID3DXEffect->GetParameterByName( nullptr, "g_local_left_top_x" );
    _h_local_left_top_y = _pID3DXEffect->GetParameterByName( nullptr, "g_local_left_top_y" );

    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
    _hDepthZ = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_z" );
    _hSx = _pID3DXEffect->GetParameterByName( nullptr, "g_sx" );
    _hSy = _pID3DXEffect->GetParameterByName( nullptr, "g_sy" );
    _h_Rz = _pID3DXEffect->GetParameterByName( nullptr, "g_rz" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
}


GgafDxBoardEffect::~GgafDxBoardEffect() {
}

