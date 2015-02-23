#include "FormationAllas001b.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Allas/EnemyAllas.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001b::FormationAllas001b(const char* prm_name) : FormationAllas001(prm_name) {
    _class_name = "FormationAllas001b";
}

void FormationAllas001b::onCallUpAllas(EnemyAllas* prm_pAllas) {
    prm_pAllas->pKurokoLeader_->adjustAxisYFlip();
    prm_pAllas->pKurokoLeader_->setAbsoluteBeginCoord();
}

FormationAllas001b::~FormationAllas001b() {
}
