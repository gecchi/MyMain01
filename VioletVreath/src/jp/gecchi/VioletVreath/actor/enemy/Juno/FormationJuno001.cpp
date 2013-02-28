#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationJuno001::FormationJuno001(const char* prm_name) :
    FormationJuno(prm_name,
                  -800000, -400000, -1,
                   400000,  800000,  1,
                   GgafDxUniverse::_X_gone_right - 300000, 0, GgafDxUniverse::_Z_gone_far - 1000,
                   2000,
                   D0ANG, D180ANG,
                   30000,
                   D0ANG, D90ANG,
                   500,
                   6) {
    _class_name = "FormationJuno001";
}

void FormationJuno001::processJudgement() {
    if (_X < GgafDxUniverse::_X_gone_left) {
        _TRACE_("FormationJuno001::processJudgement() I—¹");
        sayonara();
    }
}

FormationJuno001::~FormationJuno001() {
}
