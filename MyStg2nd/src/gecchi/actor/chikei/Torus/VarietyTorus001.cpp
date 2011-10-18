#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

VarietyTorus001::VarietyTorus001(const char* prm_name) :
        Torus(prm_name, "Torus", Px2Co(2000), Px2Co(800)) {

    _class_name = "VarietyTorus001";
    for (angle angPos1 = 0; angPos1 < D360ANG;  angPos1 += (Deg2Ang(20))) {
        for (angle angPos2 = 0; angPos2 < D360ANG;  angPos2 += (Deg2Ang(30))) {
            EnemyVesta* p = NEW EnemyVesta("pEV1");
            addSubBoneOnSurface(p, angPos1, angPos2);
            Sleep(1);
        }
    }
}

void VarietyTorus001::initialize() {
    makeCollisionArea(16);
    setHitAble(true);
    setAlpha(1.00);
    _X = GgafDxCore::GgafDxUniverse::_X_goneRight+_r1+_r2;
    _pKurokoA->setRzRyMvAng(D180ANG, 0);
    _pKurokoA->setMvVelo(3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 100);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 200);
}

void VarietyTorus001::processBehavior() {
    //���W�ɔ��f
    _pKurokoA->behave();
}

VarietyTorus001::~VarietyTorus001() {
}
