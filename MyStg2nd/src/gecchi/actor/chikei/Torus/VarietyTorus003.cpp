#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

VarietyTorus003::VarietyTorus003(const char* prm_name) : Torus(prm_name, "Torus", 2000*1000, 800*1000) {
    _class_name = "VarietyTorus003";
    for (int angPos1 = 0; angPos1 < ANGLE360;  angPos1 += (60*1000)) {
        for (int angPos2 = 0; angPos2 < ANGLE360;  angPos2 += (20*1000)) {
            EnemyVesta* p = NEW EnemyVesta("pEV1");
            addSubBoneOnSurface(p, angPos1, angPos2);
        }
    }
}

void VarietyTorus003::initialize() {
    makeCollisionArea(16);
    setHitAble(true);
    setAlpha(1.00);
    _X = GgafDx9Core::GgafDx9Universe::_X_goneRight+_r1+_r2;
    _Y = 0;
    _Z = MyShip::_lim_zright;
    _pMvNavigator->setRzRyMvAng(ANGLE180, 0);
    _pMvNavigator->setMvVelo(3000);
    _pMvNavigator->setFaceAngVelo(AXIS_Z, -200);
    _pMvNavigator->setFaceAngVelo(AXIS_Y, 100);
}

void VarietyTorus003::processBehavior() {
    //À•W‚É”½‰f
    _pMvNavigator->behave();
}


VarietyTorus003::~VarietyTorus003() {
}
