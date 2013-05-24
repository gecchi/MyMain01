#include "stdafx.h"
#include "FormationPallas001d.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/EnemyPallas.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001d::FormationPallas001d(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001d";
}

void FormationPallas001d::onCallUpPallas(EnemyPallas* prm_pPallas) {
    prm_pPallas->pKurokoLeader_->adjustAxisYFlip();
    prm_pPallas->pKurokoLeader_->adjustAxisZFlip();
    prm_pPallas->pKurokoLeader_->setAbsoluteBeginCoord();
    prm_pPallas->_pKurokoA->setMvVelo(velo_mv_);
}

FormationPallas001d::~FormationPallas001d() {
}
