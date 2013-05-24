#include "stdafx.h"
#include "FormationPallas001b.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/EnemyPallas.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationPallas001b::FormationPallas001b(const char* prm_name) : FormationPallas001(prm_name) {
    _class_name = "FormationPallas001b";
}

void FormationPallas001b::onCallUpPallas(EnemyPallas* prm_pPallas) {
    prm_pPallas->pKurokoLeader_->adjustAxisYFlip();
    prm_pPallas->pKurokoLeader_->setAbsoluteBeginCoord();
    prm_pPallas->_pKurokoA->setMvVelo(velo_mv_);
}

FormationPallas001b::~FormationPallas001b() {
}
