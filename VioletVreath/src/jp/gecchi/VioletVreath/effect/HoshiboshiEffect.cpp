#include "HoshiboshiEffect.h"

using namespace GgafLib;
using namespace VioletVreath;

HoshiboshiEffect::HoshiboshiEffect(const char* prm_effect_name) : GgafDx::PointSpriteEffect(prm_effect_name) {
    h_fX_MyShip_ = _pID3DXEffect->GetParameterByName( nullptr, "g_fX_MyShip" );
    h_fY_MyShip_ = _pID3DXEffect->GetParameterByName( nullptr, "g_fY_MyShip" );
    h_fZ_MyShip_ = _pID3DXEffect->GetParameterByName( nullptr, "g_fZ_MyShip" );
    h_far_rate_  = _pID3DXEffect->GetParameterByName( nullptr, "g_far_rate" );
}

HoshiboshiEffect::~HoshiboshiEffect() {
}

