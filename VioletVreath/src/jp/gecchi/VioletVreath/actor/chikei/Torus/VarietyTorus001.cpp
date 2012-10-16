#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VarietyTorus001::VarietyTorus001(const char* prm_name) :
        Torus(prm_name, "Torus", PX_C(2000), PX_C(800)) {

    _class_name = "VarietyTorus001";
    for (angle angPos1 = 0; angPos1 < D360ANG;  angPos1 += (D_ANG(60))) {
        for (angle angPos2 = 0; angPos2 < D360ANG;  angPos2 += (D_ANG(60))) {
            EnemyVesta* p = NEW EnemyVesta("pEV1");
            addSubFkOnSurface(p, angPos1, angPos2);
            p->inactivateImmed();
            p->activateDelay((120.0*angPos1/D360ANG));
            Sleep(1);
        }
    }
}

void VarietyTorus001::initialize() {
    makeCollisionArea(16);
    setHitAble(true);
    setAlpha(1.00);
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight+r1_+r2_;
    _pKurokoA->setRzRyMvAng(D180ANG, 0);
    _pKurokoA->setMvVelo(2000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 60);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 70);
}

void VarietyTorus001::processBehavior() {
    _pKurokoA->behave();
}

VarietyTorus001::~VarietyTorus001() {
}
