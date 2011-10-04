#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

VarietyTorus002::VarietyTorus002(const char* prm_name) : Torus(prm_name, "Torus", 2000*1000, 800*1000) {
    _class_name = "VarietyTorus002";
    for (int angPos1 = 0; angPos1 < ANGLE360;  angPos1 += (60*1000)) {
        for (int angPos2 = 0; angPos2 < ANGLE360;  angPos2 += (20*1000)) {
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
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight+_r1+_r2;
    _Y = 0;
    _Z = MyShip::_lim_zleft;
    _pKurokoA->setRzRyMvAng(ANGLE180, 0);
    _pKurokoA->setMvVelo(3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -200);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 100);
}

void VarietyTorus002::processBehavior() {
    //���W�ɔ��f
    _pKurokoA->behave();
}


VarietyTorus002::~VarietyTorus002() {
}
