#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

VarietyTorus004::VarietyTorus004(const char* prm_name) : Torus(prm_name, "Torus", 2000*1000, 800*1000) {
    _class_name = "VarietyTorus004";
    for (int angPos1 = 0; angPos1 < ANGLE360;  angPos1 += (20*1000)) {
        for (int angPos2 = 0; angPos2 < ANGLE360;  angPos2 += (20*1000)) {
            EnemyVesta* p = NEW EnemyVesta("pEV1");
            addSubBoneOnSurface(p, angPos1, angPos2);
        }
    }
}

void VarietyTorus004::initialize() {
    makeCollisionArea(16);
    setHitAble(true);
    setAlpha(1.00);
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight+_r1+_r2;
    _Y = MyShip::_lim_bottom;
    _Z = 0;
    _pKurokoA->setRzRyMvAng(ANGLE180, 0);
    _pKurokoA->setMvVelo(3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -200);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 100);
}

void VarietyTorus004::processBehavior() {
    //À•W‚É”½‰f
    _pKurokoA->behave();
}

VarietyTorus004::~VarietyTorus004() {
}
