#include "FormationAllas001c.h"

#include "EnemyAllas.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001c::FormationAllas001c(const char* prm_name) : FormationAllas001(prm_name) {
    _class_name = "FormationAllas001c";
}

void FormationAllas001c::onCalledUpAllas(EnemyAllas* prm_pAllas) {
    prm_pAllas->pVehicleLeader_->adjustAxisZFlip();
    prm_pAllas->pVehicleLeader_->setAbsoluteBeginCoord();
}

FormationAllas001c::~FormationAllas001c() {
}
