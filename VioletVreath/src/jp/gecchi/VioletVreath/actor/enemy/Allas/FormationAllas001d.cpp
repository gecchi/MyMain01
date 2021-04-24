#include "FormationAllas001d.h"

#include "EnemyAllas.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001d::FormationAllas001d(const char* prm_name) : FormationAllas001(prm_name) {
    _class_name = "FormationAllas001d";
}

void FormationAllas001d::onCallUpAllas(EnemyAllas* prm_pAllas) {
    prm_pAllas->pDriverLeader_->adjustAxisYFlip();
    prm_pAllas->pDriverLeader_->adjustAxisZFlip();
    prm_pAllas->pDriverLeader_->setAbsoluteBeginCoord();
}

FormationAllas001d::~FormationAllas001d() {
}
