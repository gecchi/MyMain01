#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VarietySylvia002::VarietySylvia002(const char* prm_name) :
        EnemySylvia(prm_name, "Sylvia", PX_C(2000), PX_C(800)) {
    _class_name = "VarietySylvia002";
    for (angle angPos1 = 0; angPos1 < D360ANG;  angPos1 += (D_ANG(20))) {
        for (angle angPos2 = 0; angPos2 < D360ANG;  angPos2 += (D_ANG(20))) {
            std::string name = "Remus(" + ITOS(angPos1) + "," + ITOS(angPos2) + ")";
            addSubFkOnSurface(NEW EnemyRemus(name.c_str()), angPos1, angPos2);
            Sleep(1);
        }
    }
}

void VarietySylvia002::initialize() {
    EnemySylvia::initialize();
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight+r1_+r2_;
    _Y = 0;
    _Z = MyShip::lim_zleft_;
    _pKurokoA->setRzRyMvAng(D180ANG, 0);
    _pKurokoA->setMvVelo(1000);
    _pKurokoA->setFaceAngVelo(AXIS_X, 10);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -50);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 30);
}

void VarietySylvia002::processBehavior() {
    EnemySylvia::processBehavior();
}


VarietySylvia002::~VarietySylvia002() {
}
