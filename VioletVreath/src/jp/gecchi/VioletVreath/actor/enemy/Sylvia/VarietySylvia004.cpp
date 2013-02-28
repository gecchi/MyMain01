#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VarietySylvia004::VarietySylvia004(const char* prm_name) : EnemySylvia(prm_name, "Sylvia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietySylvia004";
    for (angle angPos1 = D0ANG; angPos1 < D360ANG;  angPos1 += D_ANG(20)) {
        for (angle angPos2 = D0ANG; angPos2 < D360ANG;  angPos2 += D_ANG(20)) {
            EnemyRomulus* p = NEW EnemyRomulus("pEV1");
            addSubGroupAsFkOnSurface(p, angPos1, angPos2);
            Sleep(1);
        }
    }
}

void VarietySylvia004::initialize() {
    EnemySylvia::initialize();
    _X = GgafDxCore::GgafDxUniverse::_X_gone_right+r1_+r2_;
    _Y = MyShip::lim_bottom_;
    _Z = 0;
    _pKurokoA->setRzRyMvAng(D180ANG, 0);
    _pKurokoA->setMvVelo(3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -20);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 10);
}

void VarietySylvia004::processBehavior() {
    EnemySylvia::processBehavior();
}

VarietySylvia004::~VarietySylvia004() {
}
