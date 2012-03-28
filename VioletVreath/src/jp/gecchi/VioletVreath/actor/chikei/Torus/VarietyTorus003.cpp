#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VarietyTorus003::VarietyTorus003(const char* prm_name) : Torus(prm_name, "Torus", PxC(2000), PxC(800)) {
    _class_name = "VarietyTorus003";
    for (angle angPos1 = D0ANG; angPos1 < D360ANG;  angPos1 += DEG2ANG(60)) {
        for (angle angPos2 = D0ANG; angPos2 < D360ANG;  angPos2 += DEG2ANG(20)) {
            EnemyVesta* p = NEW EnemyVesta("pEV1");
            addSubBoneOnSurface(p, angPos1, angPos2);
            Sleep(1);
        }
    }
}

void VarietyTorus003::initialize() {
    makeCollisionArea(16);
    setHitAble(true);
    setAlpha(1.00);
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight+r1_+r2_;
    _Y = 0;
    _Z = MyShip::lim_zright_;
    _pKurokoA->setRzRyMvAng(D180ANG, 0);
    _pKurokoA->setMvVelo(3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -200);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 100);
}

void VarietyTorus003::processBehavior() {
    //À•W‚É”½‰f
    _pKurokoA->behave();
}


VarietyTorus003::~VarietyTorus003() {
}
