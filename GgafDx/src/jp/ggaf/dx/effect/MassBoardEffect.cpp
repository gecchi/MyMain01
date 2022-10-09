#include "jp/ggaf/dx/effect/MassBoardEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/exception/CriticalException.h"


using namespace GgafDx;

MassBoardEffect::MassBoardEffect(const char* prm_effect_name) : MassEffect(prm_effect_name) {
    _obj_class |= Obj_GgafDx_MassBoardEffect;
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    static float game_buffer_width = (float)(CONFIG::GAME_BUFFER_WIDTH);
    static float game_buffer_height = (float)(CONFIG::GAME_BUFFER_HEIGHT);
    static float inv_game_buffer_width = 1.0f / game_buffer_width;
    static float inv_game_buffer_height = 1.0f / game_buffer_height;
    hr = _pID3DXEffect->SetFloat("g_game_buffer_width", game_buffer_width);
    checkDxException(hr, D3D_OK, "SetFloat(g_game_buffer_width) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_game_buffer_height", game_buffer_height);
    checkDxException(hr, D3D_OK, "SetFloat(g_game_buffer_height) に失敗しました。");

    hr = _pID3DXEffect->SetFloat("g_inv_game_buffer_width", inv_game_buffer_width);
    checkDxException(hr, D3D_OK, "SetFloat(g_inv_game_buffer_width) に失敗しました。");
    hr = _pID3DXEffect->SetFloat("g_inv_game_buffer_height", inv_game_buffer_height);
    checkDxException(hr, D3D_OK, "SetFloat(g_inv_game_buffer_height) に失敗しました。");

    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
}

MassBoardEffect::~MassBoardEffect() {
}

