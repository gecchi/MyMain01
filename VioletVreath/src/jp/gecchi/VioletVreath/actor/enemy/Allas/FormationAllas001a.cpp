#include "FormationAllas001a.h"

#include "EnemyAllas.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationAllas001a::FormationAllas001a(const char* prm_name) : FormationAllas001(prm_name) {
    _class_name = "FormationAllas001a";
}

void FormationAllas001a::onCallUpAllas(EnemyAllas* prm_pAllas)  {
    prm_pAllas->pKurokoLeader_->setAbsoluteBeginCoord();
}

FormationAllas001a::~FormationAllas001a() {
}
