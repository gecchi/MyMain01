#include "FormationAllas001c.h"

#include "EnemyAllas.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001c::FormationAllas001c(const char* prm_name) : FormationAllas001(prm_name) {
    _class_name = "FormationAllas001c";
}

void FormationAllas001c::onCallUpAllas(EnemyAllas* prm_pAllas) {
    prm_pAllas->pDriverLeader_->adjustAxisZFlip();
    prm_pAllas->pDriverLeader_->setAbsoluteBeginCoord();
}

FormationAllas001c::~FormationAllas001c() {
}
