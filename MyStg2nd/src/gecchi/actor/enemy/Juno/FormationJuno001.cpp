#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

FormationJuno001::FormationJuno001(const char* prm_name) :
    FormationJuno(prm_name,
                  -800000, -800000, -1,
                   800000,  800000,  1,
                   GgafDx9Universe::_X_goneRight - 300000, 0, GgafDx9Universe::_Z_goneFar - 1000,
//                   0, 0, 0,
                   1000,
                   ANGLE0, ANGLE180,
                   60000,
                   ANGLE0, ANGLE90,
                   200,
                   5) {
    _class_name = "FormationJuno001";
}

void FormationJuno001::processJudgement() {
    if (_X < GgafDx9Universe::_X_goneLeft - 300000) {
        _TRACE_("FormationJuno001::processJudgement() ‚³‚æ‚È‚ç");
        sayonara();
    }
}

FormationJuno001::~FormationJuno001() {
}
