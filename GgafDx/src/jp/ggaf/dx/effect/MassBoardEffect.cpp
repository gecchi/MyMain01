#include "jp/ggaf/dx/effect/MassBoardEffect.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/exception/CriticalException.h"


using namespace GgafDx;

MassBoardEffect::MassBoardEffect(const char* prm_effect_name) : Fix2DimEffect(prm_effect_name), IPlaneEffect(this) {
    _obj_class |= Obj_GgafDx_MassBoardEffect;
    _obj_class |= Obj_GgafDx_IPlaneEffect;
}

MassBoardEffect::~MassBoardEffect() {
}

