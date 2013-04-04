#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001a::FormationPallas001a(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001a";
}

void FormationPallas001a::onCallUpPallas(EnemyPallas* prm_pPallas)  {
    prm_pPallas->pKurokoStepper_->setAbsoluteBeginCoord();
    prm_pPallas->_pKurokoA->setMvVelo(velo_mv_);
}

FormationPallas001a::~FormationPallas001a() {
}
