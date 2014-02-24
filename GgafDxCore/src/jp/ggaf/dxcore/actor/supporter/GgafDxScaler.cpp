#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

#include "jp/ggaf/core/util/GgafValueTransitioner.hpp"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"


using namespace GgafCore;
using namespace GgafDxCore;

GgafDxScaler::GgafDxScaler(GgafDxGeometricActor* prm_pActor) : GgafValueTransitioner<scale, 3 > (),
_pActor(prm_pActor) {
    _apActorScale[0] = &(prm_pActor->_sx);
    _apActorScale[1] = &(prm_pActor->_sy);
    _apActorScale[2] = &(prm_pActor->_sz);
    forceRange(0, MAX_SCALE);
}
void GgafDxScaler::reset() {
    GgafValueTransitioner<scale, 3 >::reset();
    forceRange(0, MAX_SCALE);
}
scale GgafDxScaler::getValue(int idx) {
    return (*(_apActorScale[idx]));
}
void GgafDxScaler::setValue(int idx, scale value) {
    (*(_apActorScale[idx])) = value;
}
GgafDxScaler::~GgafDxScaler() {
}
