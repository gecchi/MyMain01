#include "jp/ggaf/dx/actor/supporter/Scaler.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

Scaler::Scaler(GeometricActor* prm_pActor) : GgafCore::ValueTransitioner<scale, 3 > (),
_pActor(prm_pActor) {
    _apActorScale[0] = &(prm_pActor->_sx);
    _apActorScale[1] = &(prm_pActor->_sy);
    _apActorScale[2] = &(prm_pActor->_sz);
    setRange(0, MAX_SCALE);
}
void Scaler::reset() {
    GgafCore::ValueTransitioner<scale, 3 >::reset();
    setRange(0, MAX_SCALE);
}
scale Scaler::getValue(int idx) {
    return (*(_apActorScale[idx]));
}
void Scaler::setValue(int idx, scale value) {
    (*(_apActorScale[idx])) = value;
}
Scaler::~Scaler() {
}
