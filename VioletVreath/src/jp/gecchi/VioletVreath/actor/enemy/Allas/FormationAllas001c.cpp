#include "FormationAllas001c.h"

#include "EnemyAllas.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"



using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001c::FormationAllas001c(const char* prm_name) : FormationAllas001(prm_name) {
    _class_name = "FormationAllas001c";
}

void FormationAllas001c::onCallUpAllas(EnemyAllas* prm_pAllas) {
    prm_pAllas->pRikishaLeader_->adjustAxisZFlip();
    prm_pAllas->pRikishaLeader_->setAbsoluteBeginCoord();
}

FormationAllas001c::~FormationAllas001c() {
}
