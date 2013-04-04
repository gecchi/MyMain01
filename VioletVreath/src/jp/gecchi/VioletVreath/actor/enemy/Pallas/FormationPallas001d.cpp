#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001d::FormationPallas001d(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001d";
}

void FormationPallas001d::onCallUpPallas(EnemyPallas* prm_pPallas) {
    prm_pPallas->pKurokoStepper_->adjustAxisYFlip();
    prm_pPallas->pKurokoStepper_->adjustAxisZFlip();
    prm_pPallas->pKurokoStepper_->setAbsoluteBeginCoord();
    prm_pPallas->_pKurokoA->setMvVelo(velo_mv_);
}

FormationPallas001d::~FormationPallas001d() {
}
