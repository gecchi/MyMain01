#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

VarietyTorus002::VarietyTorus002(const char* prm_name) :
        Torus(prm_name, "Torus", PXCO(2000), PXCO(800)) {
    _class_name = "VarietyTorus002";
    for (angle angPos1 = D0ANG; angPos1 < D360ANG;  angPos1 += DANG(60)) {
        for (angle angPos2 = D0ANG; angPos2 < D360ANG;  angPos2 += DANG(20)) {
            EnemyVesta* p = NEW EnemyVesta("pEV1");
            addSubBoneOnSurface(p, angPos1, angPos2);
            Sleep(1);
        }
    }
}

void VarietyTorus002::initialize() {
    makeCollisionArea(16);
    setHitAble(true);
    setAlpha(1.00);
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight+r1_+r2_;
    _Y = 0;
    _Z = MyShip::lim_zleft_;
    _pKurokoA->setRzRyMvAng(D180ANG, 0);
    _pKurokoA->setMvVelo(3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -200);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 100);
}

void VarietyTorus002::processBehavior() {
    //À•W‚É”½‰f
    _pKurokoA->behave();
}


VarietyTorus002::~VarietyTorus002() {
}
