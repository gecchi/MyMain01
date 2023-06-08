#include "jp/ggaf/dx/effect/BoardSetEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/exception/CriticalException.h"


using namespace GgafDx;

BoardSetEffect::BoardSetEffect(const char* prm_effect_name) : Fix2DimEffect(prm_effect_name), IPlaneEffect(this) {
    _obj_class |= Obj_GgafDx_BoardSetEffect;
    _obj_class |= Obj_GgafDx_IPlaneEffect;

    //シェーダー共通のグローバル変数設定
    HRESULT hr;
    //ハンドル
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
    _ah_alpha[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha019" );
    _ah_alpha[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha020" );
    _ah_alpha[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha021" );
    _ah_alpha[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha022" );
    _ah_alpha[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha023" );
    _ah_alpha[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha024" );
    _ah_alpha[24] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha025" );
    _ah_alpha[25] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha026" );
    _ah_alpha[26] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha027" );
    _ah_alpha[27] = _pID3DXEffect->GetParameterByName( nullptr, "g_alpha028" );

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
    _ah_offset_u[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u019" );
    _ah_offset_u[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u020" );
    _ah_offset_u[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u021" );
    _ah_offset_u[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u022" );
    _ah_offset_u[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u023" );
    _ah_offset_u[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u024" );
    _ah_offset_u[24] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u025" );
    _ah_offset_u[25] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u026" );
    _ah_offset_u[26] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u027" );
    _ah_offset_u[27] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_u028" );

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
    _ah_offset_v[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v019" );
    _ah_offset_v[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v020" );
    _ah_offset_v[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v021" );
    _ah_offset_v[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v022" );
    _ah_offset_v[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v023" );
    _ah_offset_v[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v024" );
    _ah_offset_v[24] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v025" );
    _ah_offset_v[25] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v026" );
    _ah_offset_v[26] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v027" );
    _ah_offset_v[27] = _pID3DXEffect->GetParameterByName( nullptr, "g_offset_v028" );

    _ah_transformed_x[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X001" );
    _ah_transformed_x[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X002" );
    _ah_transformed_x[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X003" );
    _ah_transformed_x[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X004" );
    _ah_transformed_x[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X005" );
    _ah_transformed_x[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X006" );
    _ah_transformed_x[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X007" );
    _ah_transformed_x[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X008" );
    _ah_transformed_x[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X009" );
    _ah_transformed_x[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X010" );
    _ah_transformed_x[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X011" );
    _ah_transformed_x[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X012" );
    _ah_transformed_x[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X013" );
    _ah_transformed_x[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X014" );
    _ah_transformed_x[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X015" );
    _ah_transformed_x[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X016" );
    _ah_transformed_x[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X017" );
    _ah_transformed_x[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X018" );
    _ah_transformed_x[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X019" );
    _ah_transformed_x[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X020" );
    _ah_transformed_x[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X021" );
    _ah_transformed_x[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X022" );
    _ah_transformed_x[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X023" );
    _ah_transformed_x[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X024" );
    _ah_transformed_x[24] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X025" );
    _ah_transformed_x[25] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X026" );
    _ah_transformed_x[26] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X027" );
    _ah_transformed_x[27] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_X028" );

    _ah_transformed_y[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y001" );
    _ah_transformed_y[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y002" );
    _ah_transformed_y[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y003" );
    _ah_transformed_y[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y004" );
    _ah_transformed_y[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y005" );
    _ah_transformed_y[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y006" );
    _ah_transformed_y[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y007" );
    _ah_transformed_y[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y008" );
    _ah_transformed_y[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y009" );
    _ah_transformed_y[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y010" );
    _ah_transformed_y[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y011" );
    _ah_transformed_y[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y012" );
    _ah_transformed_y[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y013" );
    _ah_transformed_y[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y014" );
    _ah_transformed_y[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y015" );
    _ah_transformed_y[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y016" );
    _ah_transformed_y[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y017" );
    _ah_transformed_y[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y018" );
    _ah_transformed_y[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y019" );
    _ah_transformed_y[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y020" );
    _ah_transformed_y[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y021" );
    _ah_transformed_y[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y022" );
    _ah_transformed_y[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y023" );
    _ah_transformed_y[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y024" );
    _ah_transformed_y[24] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y025" );
    _ah_transformed_y[25] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y026" );
    _ah_transformed_y[26] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y027" );
    _ah_transformed_y[27] = _pID3DXEffect->GetParameterByName( nullptr, "g_transformed_Y028" );

    _ah_depth_z[0] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z001" );
    _ah_depth_z[1] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z002" );
    _ah_depth_z[2] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z003" );
    _ah_depth_z[3] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z004" );
    _ah_depth_z[4] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z005" );
    _ah_depth_z[5] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z006" );
    _ah_depth_z[6] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z007" );
    _ah_depth_z[7] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z008" );
    _ah_depth_z[8] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z009" );
    _ah_depth_z[9] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z010" );
    _ah_depth_z[10] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z011" );
    _ah_depth_z[11] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z012" );
    _ah_depth_z[12] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z013" );
    _ah_depth_z[13] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z014" );
    _ah_depth_z[14] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z015" );
    _ah_depth_z[15] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z016" );
    _ah_depth_z[16] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z017" );
    _ah_depth_z[17] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z018" );
    _ah_depth_z[18] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z019" );
    _ah_depth_z[19] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z020" );
    _ah_depth_z[20] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z021" );
    _ah_depth_z[21] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z022" );
    _ah_depth_z[22] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z023" );
    _ah_depth_z[23] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z024" );
    _ah_depth_z[24] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z025" );
    _ah_depth_z[25] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z026" );
    _ah_depth_z[26] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z027" );
    _ah_depth_z[27] = _pID3DXEffect->GetParameterByName( nullptr, "g_depth_Z028" );

    _h_tex_blink_power = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_power" );
    _h_tex_blink_threshold = _pID3DXEffect->GetParameterByName( nullptr, "g_tex_blink_threshold" );
    _h_colMaterialDiffuse = _pID3DXEffect->GetParameterByName( nullptr, "g_colMaterialDiffuse" );
}

BoardSetEffect::~BoardSetEffect() {
}

