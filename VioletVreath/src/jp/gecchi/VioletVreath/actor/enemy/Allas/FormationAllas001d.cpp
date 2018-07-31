#include "FormationAllas001d.h"

#include "EnemyAllas.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001d::FormationAllas001d(const char* prm_name) : FormationAllas001(prm_name) {
    _class_name = "FormationAllas001d";
}

void FormationAllas001d::onCallUpAllas(EnemyAllas* prm_pAllas) {
    prm_pAllas->pKurokoLeader_->adjustAxisYFlip();
    prm_pAllas->pKurokoLeader_->adjustAxisZFlip();
    prm_pAllas->pKurokoLeader_->setAbsoluteBeginCoord();
}

FormationAllas001d::~FormationAllas001d() {
}
