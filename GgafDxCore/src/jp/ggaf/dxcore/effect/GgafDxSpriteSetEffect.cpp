#include "jp/ggaf/dxcore/effect/GgafDxSpriteSetEffect.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSpriteSetEffect::GgafDxSpriteSetEffect(char* prm_effect_name) : GgafDxEffect(prm_effect_name) {
    GgafDxCamera* const pCam = P_GOD->getUniverse()->getCamera();
    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //射影変換行列
    hr = _pID3DXEffect->SetMatrix("g_matProj", pCam->getProjectionMatrix() );
    checkDxException(hr, D3D_OK, "GgafDxSpriteSetEffect::GgafDxSpriteSetEffect SetMatrix() に失敗しました。");

    hr = _pID3DXEffect->SetFloat("g_zf", pCam->getZFar());
    checkDxException(hr, D3D_OK, "GgafDxSpriteEffect::GgafDxSpriteEffect SetFloat(g_zf) に失敗しました。");


    //シェーダーハンドル
    _h_matView  = _pID3DXEffect->GetParameterByName( nullptr, "g_matView" );
    _ah_matWorld[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld001" );
    _ah_matWorld[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld002" );
    _ah_matWorld[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld003" );
    _ah_matWorld[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld004" );
    _ah_matWorld[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld005" );
    _ah_matWorld[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld006" );
    _ah_matWorld[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld007" );
    _ah_matWorld[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld008" );
    _ah_matWorld[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld009" );
    _ah_matWorld[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld010" );
    _ah_matWorld[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld011" );
    _ah_matWorld[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld012" );
    _ah_matWorld[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld013" );
    _ah_matWorld[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld014" );
    _ah_matWorld[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld015" );
    _ah_matWorld[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld016" );
    _ah_matWorld[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld017" );
    _ah_matWorld[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld018" );
//    _ah_matWorld[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld019" );
//    _ah_matWorld[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld020" );
//    _ah_matWorld[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld021" );
//    _ah_matWorld[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld022" );
//    _ah_matWorld[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld023" );
//    _ah_matWorld[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_matWorld024" );

    _ah_offset_u[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u001" );
    _ah_offset_u[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u002" );
    _ah_offset_u[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u003" );
    _ah_offset_u[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u004" );
    _ah_offset_u[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u005" );
    _ah_offset_u[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u006" );
    _ah_offset_u[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u007" );
    _ah_offset_u[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u008" );
    _ah_offset_u[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u009" );
    _ah_offset_u[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u010" );
    _ah_offset_u[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u011" );
    _ah_offset_u[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u012" );
    _ah_offset_u[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u013" );
    _ah_offset_u[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u014" );
    _ah_offset_u[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u015" );
    _ah_offset_u[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u016" );
    _ah_offset_u[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u017" );
    _ah_offset_u[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u018" );
//    _ah_offset_u[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u019" );
//    _ah_offset_u[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u020" );
//    _ah_offset_u[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u021" );
//    _ah_offset_u[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u022" );
//    _ah_offset_u[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u023" );
//    _ah_offset_u[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u024" );

    _ah_offset_v[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v001" );
    _ah_offset_v[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v002" );
    _ah_offset_v[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v003" );
    _ah_offset_v[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v004" );
    _ah_offset_v[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v005" );
    _ah_offset_v[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v006" );
    _ah_offset_v[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v007" );
    _ah_offset_v[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v008" );
    _ah_offset_v[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v009" );
    _ah_offset_v[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v010" );
    _ah_offset_v[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v011" );
    _ah_offset_v[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v012" );
    _ah_offset_v[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v013" );
    _ah_offset_v[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v014" );
    _ah_offset_v[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v015" );
    _ah_offset_v[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v016" );
    _ah_offset_v[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v017" );
    _ah_offset_v[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v018" );
//    _ah_offset_v[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v019" );
//    _ah_offset_v[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v020" );
//    _ah_offset_v[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v021" );
//    _ah_offset_v[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v022" );
//    _ah_offset_v[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v023" );
//    _ah_offset_v[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v024" );

    _ah_alpha[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha001" );
    _ah_alpha[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha002" );
    _ah_alpha[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha003" );
    _ah_alpha[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha004" );
    _ah_alpha[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha005" );
    _ah_alpha[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha006" );
    _ah_alpha[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha007" );
    _ah_alpha[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha008" );
    _ah_alpha[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha009" );
    _ah_alpha[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha010" );
    _ah_alpha[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha011" );
    _ah_alpha[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha012" );
    _ah_alpha[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha013" );
    _ah_alpha[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha014" );
    _ah_alpha[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha015" );
    _ah_alpha[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha016" );
    _ah_alpha[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha017" );
    _ah_alpha[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha018" );
//    _ah_alpha[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha019" );
//    _ah_alpha[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha020" );
//    _ah_alpha[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha021" );
//    _ah_alpha[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha022" );
//    _ah_alpha[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha023" );
//    _ah_alpha[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha024" );

    _ah_x[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_X001" );
    _ah_x[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_X002" );
    _ah_x[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_X003" );
    _ah_x[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_X004" );
    _ah_x[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_X005" );
    _ah_x[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_X006" );
    _ah_x[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_X007" );
    _ah_x[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_X008" );
    _ah_x[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_X009" );
    _ah_x[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_X010" );
    _ah_x[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_X011" );
    _ah_x[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_X012" );
    _ah_x[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_X013" );
    _ah_x[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_X014" );
    _ah_x[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_X015" );
    _ah_x[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_X016" );
    _ah_x[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_X017" );
    _ah_x[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_X018" );
//    _ah_x[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_X019" );
//    _ah_x[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_X020" );
//    _ah_x[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_X021" );
//    _ah_x[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_X022" );
//    _ah_x[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_X023" );
//    _ah_x[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_X024" );

    _ah_y[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y001" );
    _ah_y[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y002" );
    _ah_y[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y003" );
    _ah_y[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y004" );
    _ah_y[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y005" );
    _ah_y[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y006" );
    _ah_y[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y007" );
    _ah_y[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y008" );
    _ah_y[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y009" );
    _ah_y[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y010" );
    _ah_y[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y011" );
    _ah_y[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y012" );
    _ah_y[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y013" );
    _ah_y[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y014" );
    _ah_y[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y015" );
    _ah_y[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y016" );
    _ah_y[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y017" );
    _ah_y[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y018" );
//    _ah_y[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y019" );
//    _ah_y[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y020" );
//    _ah_y[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y021" );
//    _ah_y[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y022" );
//    _ah_y[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y023" );
//    _ah_y[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_Y024" );

    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
}

void GgafDxSpriteSetEffect::setParamPerFrame() {
    GgafDxCamera* const pCam = P_GOD->getUniverse()->getCamera();
    HRESULT hr = _pID3DXEffect->SetMatrix(_h_matView, pCam->getViewMatrix());
    checkDxException(hr, D3D_OK, "setParamPerFrame SetMatrix(_h_matView) に失敗しました。");
}

GgafDxSpriteSetEffect::~GgafDxSpriteSetEffect() {
}

