#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

VarietyTorus003::VarietyTorus003(const char* prm_name) : Torus(prm_name, "Torus") {
    _class_name = "VarietyTorus003";
    MyStgUtil::resetTorusStatus(_pStatus);
    _r1 = 2000*1000; //トーラス半径1
    _r2 = 800*1000;  //トーラス半径2
    for (int angPos1 = 0; angPos1 < ANGLE360;  angPos1 += (60*1000)) {
        for (int angPos2 = 0; angPos2 < ANGLE360;  angPos2 += (20*1000)) {
            EnemyVesta* p = NEW EnemyVesta("pEV1");
            addSubBoneOnSurface(p, angPos1, angPos2);
        }
    }
}

void VarietyTorus003::initialize() {
    setHitAble(true);
    int nSphere = 16;    //当たり判定球の数;
    angle* paAngRadial = NEW angle[nSphere];
    GgafDx9Util::getRadialAngle2D(0, nSphere, paAngRadial);
    _pCollisionChecker->makeCollision(nSphere);
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
    _Z = GgafDx9Core::GgafDx9Universe::_Z_goneNear+_r1+_r2+_r1+_r2;
    _pMover->setRzRyMvAng(ANGLE180, 0);
    _pMover->setMvVelo(3000);
    _pMover->setFaceAngVelo(AXIS_Z, -200);
    _pMover->setFaceAngVelo(AXIS_Y, 100);
}

void VarietyTorus003::onActive() {
    MyStgUtil::resetTorusStatus(_pStatus);
}

void VarietyTorus003::processBehavior() {
    //座標に反映
    _pMover->behave();
}


VarietyTorus003::~VarietyTorus003() {
}
