#include "jp/ggaf/lib/effect/MassWallEffect.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

MassWallEffect::MassWallEffect(const char* prm_effect_name) : GgafDxMassMeshEffect(prm_effect_name) {
    _h_distance_AlphaTarget = _pID3DXEffect->GetParameterByName( nullptr, "g_distance_AlphaTarget" );
    _h_wall_dep    = _pID3DXEffect->GetParameterByName( nullptr, "g_wall_dep" );
    _h_wall_height = _pID3DXEffect->GetParameterByName( nullptr, "g_wall_height" );
    _h_wall_width  = _pID3DXEffect->GetParameterByName( nullptr, "g_wall_width" );
    _h_ah_POS_ZX = _pID3DXEffect->GetParameterByName( nullptr, "g_ah_POS_ZX" );
    _h_fh_POS_ZX = _pID3DXEffect->GetParameterByName( nullptr, "g_fh_POS_ZX" );
    _h_ah_POS_YZ = _pID3DXEffect->GetParameterByName( nullptr, "g_ah_POS_YZ" );
    _h_fh_POS_YZ = _pID3DXEffect->GetParameterByName( nullptr, "g_fh_POS_YZ" );
    _h_ah_POS_XY = _pID3DXEffect->GetParameterByName( nullptr, "g_ah_POS_XY" );
    _h_fh_POS_XY = _pID3DXEffect->GetParameterByName( nullptr, "g_fh_POS_XY" );
    _h_reflectance = _pID3DXEffect->GetParameterByName(nullptr, "g_reflectance");
}

MassWallEffect::~MassWallEffect() {
}

