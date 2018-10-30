#include "jp/ggaf/dxcore/effect/GgafDxRegularPolygonBoardEffect.h"

#include "jp/ggaf/dxcore/GgafDxConfig.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxRegularPolygonBoardEffect::GgafDxRegularPolygonBoardEffect(const char* prm_effect_name) : GgafDxEffect(prm_effect_name) {
    _obj_effect |= Obj_GgafDxRegularPolygonBoardEffect;
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    static float game_buffer_width = (float)(CONFIG::GAME_BUFFER_WIDTH);
    static float game_buffer_height = (float)(CONFIG::GAME_BUFFER_HEIGHT);

    hr = _pID3DXEffect->SetFloat("g_game_buffer_width", game_buffer_width);
    checkDxException(hr, D3D_OK, "SetFloat(g_game_buffer_width) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_game_buffer_height", game_buffer_height);
    checkDxException(hr, D3D_OK, "SetFloat(g_game_buffer_height) に失敗しました。");

    //ハンドル
    _h_offset_u = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u" );
    _h_offset_v = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v" );
    _h_transformed_x = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_x" );
    _h_transformed_y = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_y" );

    _h_local_left_top_x = _pID3DXEffect->GetParameterByName( nullptr, "g_local_left_top_x" );
    _h_local_left_top_y = _pID3DXEffect->GetParameterByName( nullptr, "g_local_left_top_y" );

    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
    _h_depth_z = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_z" );
    _h_sx = _pID3DXEffect->GetParameterByName( nullptr, "g_sx" );
    _h_sy = _pID3DXEffect->GetParameterByName( nullptr, "g_sy" );
    _h_rz = _pID3DXEffect->GetParameterByName( nullptr, "g_rz" );
    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
    _h_sin_rz = _pID3DXEffect->GetParameterByName( nullptr, "g_sin_rz" );
    _h_cos_rz = _pID3DXEffect->GetParameterByName( nullptr, "g_cos_rz" );
    _h_x_center = _pID3DXEffect->GetParameterByName( nullptr, "g_x_center" );
    _h_y_center = _pID3DXEffect->GetParameterByName( nullptr, "g_y_center" );
    _h_u_center = _pID3DXEffect->GetParameterByName( nullptr, "g_u_center" );
    _h_v_center = _pID3DXEffect->GetParameterByName( nullptr, "g_v_center" );
}


GgafDxRegularPolygonBoardEffect::~GgafDxRegularPolygonBoardEffect() {
}

