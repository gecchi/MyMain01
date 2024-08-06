#include "FormationAllas001d.h"

#include "EnemyAllas.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001d::FormationAllas001d(const char* prm_name) : FormationAllas001(prm_name) {
    _class_name = "FormationAllas001d";
}

void FormationAllas001d::onCalledUpAllas(EnemyAllas* prm_pAllas) {
    prm_pAllas->pVehicleLeader_->adjustAxisYFlip();
    prm_pAllas->pVehicleLeader_->adjustAxisZFlip();
    prm_pAllas->pVehicleLeader_->setAbsoluteBeginCoord();
}

FormationAllas001d::~FormationAllas001d() {
}
