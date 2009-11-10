#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyPallas::EnemyPallas(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "Pallas") {
    _class_name = "EnemyPallas";

    _iMovePatternNo = 0;
}

void EnemyPallas::initialize() {
    setBumpable(true);
    _X = GgafDx9Camera::_X_ScreenRight + 100;
    _Y = 0;
    _Z = 0;
    _pMover->setMoveVeloRenge(-8000, 8000);
    _pMover->setMoveVelocity(8000);
    _pMover->setMoveVeloAcceleration(-500);
    _pMover->setRzMoveAngle(ANGLE90);

    _pMover->setFaceAngleVeloRenge(AXIS_X, 0, 5000);
    _pMover->setFaceAngleVelocity(AXIS_X, 5000);
    _pMover->setFaceAngleVeloAcceleration(AXIS_X, 0);

    _pMover->setFaceAngle(AXIS_Z, ANGLE180);

    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    _pStgChecker->setStatus(100, 1, 1, 1);
}

void EnemyPallas::processBehavior() {
    if (_pMover->_veloMove <= -8000) {
        _pMover->setMoveVeloAcceleration(+500);
    } else if (_pMover->_veloMove >= +8000) {
        _pMover->setMoveVeloAcceleration(-500);
    }
    _X -= 2000;

    //À•W‚É”½‰f
    _pMover->behave();
}

void EnemyPallas::processJudgement() {
    if (wasGone()) {
        adios();
    }
}

void EnemyPallas::processOnHit(GgafActor* prm_pActor_Opponent) {
    setBumpable(false);
    adios();
}

int EnemyPallas::wasGone() {
    if (_X < GgafDx9Camera::_X_ScreenLeft - 100000) {
        return true;
    } else {
        return false;
    }
}

EnemyPallas::~EnemyPallas() {
}
