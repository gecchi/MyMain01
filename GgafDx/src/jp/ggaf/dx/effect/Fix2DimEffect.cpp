#include "jp/ggaf/dx/effect/Fix2DimEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


using namespace GgafDx;

Fix2DimEffect::Fix2DimEffect(const char* prm_effect_name) : Effect(prm_effect_name) {
    _obj_class |= Obj_GgafDx_Fix2DimEffect;

    static float game_buffer_width = (float)(CONFIG::GAME_BUFFER_WIDTH);
    static float game_buffer_height = (float)(CONFIG::GAME_BUFFER_HEIGHT);
    static float inv_game_buffer_width = 1.0f / game_buffer_width;
    static float inv_game_buffer_height = 1.0f / game_buffer_height;

    HRESULT hr;
    hr = _pID3DXEffect->SetFloat("g_game_buffer_width", game_buffer_width);
    checkDxException(hr, D3D_OK, "SetFloat(g_game_buffer_width) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    hr = _pID3DXEffect->SetFloat("g_game_buffer_height", game_buffer_height);
    checkDxException(hr, D3D_OK, "SetFloat(g_game_buffer_height) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    hr = _pID3DXEffect->SetFloat("g_inv_game_buffer_width", inv_game_buffer_width);
    checkDxException(hr, D3D_OK, "SetFloat(g_inv_game_buffer_width) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
    hr = _pID3DXEffect->SetFloat("g_inv_game_buffer_height", inv_game_buffer_height);
    checkDxException(hr, D3D_OK, "SetFloat(g_inv_game_buffer_height) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

}

Fix2DimEffect::~Fix2DimEffect() {
}

