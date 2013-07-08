#include "stdafx.h"
#include "FormationGeria001.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationGeria001::FormationGeria001(const char* prm_name) :
    FormationGeria(prm_name,
                  -800000, -400000, -1,
                   400000,  800000,  1,
                   GgafDxUniverse::_X_gone_right - 300000, 0, GgafDxUniverse::_Z_gone_far - 1000,
                   2000,
                   D0ANG, D180ANG,
                   30000,
                   D0ANG, D90ANG,
                   500,
                   6) {
    _class_name = "FormationGeria001";
}

void FormationGeria001::processJudgement() {
    if (_X < GgafDxUniverse::_X_gone_left) {
        _TRACE_("FormationGeria001::processJudgement() I—¹");
        sayonara();
    }
}

FormationGeria001::~FormationGeria001() {
}
