#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001b::FormationPallas001b(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001b";
}

void FormationPallas001b::onCallUpPallas(EnemyPallas* prm_pPallas) {
    prm_pPallas->pSplSeq_->adjustAxisYFlip();
    prm_pPallas->pSplSeq_->setAbsoluteBeginCoordinate();
    prm_pPallas->_pKurokoA->setMvVelo(velo_mv_);
}

FormationPallas001b::~FormationPallas001b() {
}
