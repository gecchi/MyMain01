#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyVesta::EnemyVesta(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "Vesta") {
    _class_name = "EnemyVesta";

    _iMovePatternNo = 0;
}

void EnemyVesta::initialize() {
    setBumpable(true);
    _X = _X_ScreenRight + 100;
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

void EnemyVesta::processBehavior() {
    if (_pMover->_veloMove <= -8000) {
        _pMover->setMoveVeloAcceleration(+500);
    } else if (_pMover->_veloMove >= +8000) {
        _pMover->setMoveVeloAcceleration(-500);
    }
    _X -= 2000;

    //À•W‚É”½‰f
    _pMover->behave();
}

void EnemyVesta::processJudgement() {
    if (isOffscreen()) {
        adios();
    }
}

void EnemyVesta::processOnHit(GgafActor* prm_pActor_Opponent) {
    setBumpable(false);
    adios();
}

int EnemyVesta::wasGone() {
    if (_Y < _Y_ScreenBottom - 100000) {
        return true;
    } else {
        return false;
    }
}

EnemyVesta::~EnemyVesta() {
}
