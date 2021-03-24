#include "FormationAllas001a.h"

#include "EnemyAllas.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/spline/SplineLeader.h"

using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001a::FormationAllas001a(const char* prm_name) : FormationAllas001(prm_name) {
    _class_name = "FormationAllas001a";
}

void FormationAllas001a::onCallUpAllas(EnemyAllas* prm_pAllas)  {
    prm_pAllas->pVecDriverLeader_->setAbsoluteBeginCoord();
}

FormationAllas001a::~FormationAllas001a() {
}
