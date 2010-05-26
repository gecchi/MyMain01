#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

VarietyTorus001::VarietyTorus001(const char* prm_name) : Torus(prm_name, "Torus") {
    _class_name = "VarietyTorus001";
    MyStgUtil::resetTorusStatus(_pStatus);
    _r1 = 2000*1000; //�g�[���X���a1
    _r2 = 800*1000;  //�g�[���X���a2

    for (int angPos1 = 0; angPos1 < ANGLE360;  angPos1 += (20*1000)) {
        for (int angPos2 = 0; angPos2 < ANGLE360;  angPos2 += (30*1000)) {
            EnemyVesta* p = NEW EnemyVesta("pEV1");
            addSubBoneOnSurface(p, angPos1, angPos2);
        }
    }
}

void VarietyTorus001::initialize() {
    setHitAble(true);
    int nSphere = 16;    //�����蔻�苅�̐�;
    angle* paAngRadial = NEW angle[nSphere];
    _pCollisionChecker->makeCollision(nSphere);
    GgafDx9Util::getRadialAngle2D(0, nSphere, paAngRadial);
    for (int i = 0; i < nSphere; i++) {
        _pCollisionChecker->setColliSphere(
                i,
                0 , GgafDx9Util::SIN[paAngRadial[i]/ANGLE_RATE] * _r1, GgafDx9Util::COS[paAngRadial[i]/ANGLE_RATE] * _r1,
                _r2*0.96,
                false, true, true
                );
    }
    DELETE_IMPOSSIBLE_NULL(paAngRadial);
    setAlpha(1.00);
    _X = GgafDx9Core::GgafDx9Universe::_X_goneRight+_r1+_r2;
    _Y = 0;
    _Z = 0;
    _pMover->setRzRyMvAng(ANGLE180, 0);
    _pMover->setMvVelo(3000);
    _pMover->setFaceAngVelo(AXIS_Z, 100);
    _pMover->setFaceAngVelo(AXIS_Y, 200);
}

void VarietyTorus001::onActive() {
    MyStgUtil::resetTorusStatus(_pStatus);
}

void VarietyTorus001::processBehavior() {
    //���W�ɔ��f
    _pMover->behave();
}

VarietyTorus001::~VarietyTorus001() {
}
