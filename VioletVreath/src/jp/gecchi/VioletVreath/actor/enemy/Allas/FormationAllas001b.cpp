#include "FormationAllas001b.h"

#include "EnemyAllas.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001b::FormationAllas001b(const char* prm_name) : FormationAllas001(prm_name) {
    _class_name = "FormationAllas001b";
}

void FormationAllas001b::onSummonAllas(EnemyAllas* prm_pAllas) {
    prm_pAllas->pVehicleLeader_->adjustAxisYFlip();
    prm_pAllas->pVehicleLeader_->setAbsoluteBeginCoord();
}

FormationAllas001b::~FormationAllas001b() {
}
