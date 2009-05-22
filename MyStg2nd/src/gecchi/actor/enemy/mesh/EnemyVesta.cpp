#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyVesta::EnemyVesta(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "X/Vesta") {
    _class_name = "EnemyVesta";

    _iMovePatternNo = 0;
}

void EnemyVesta::initialize() {
    setBumpable(true);
    _X = _X_OffScreenRight + 100;
    _Y = 0;
    _Z = 0;
    _pMover->setMoveVelocityRenge(-8000, 8000);
    _pMover->setMoveVelocity(8000);
    _pMover->setMoveAcceleration(-500);
    _pMover->setRzMoveAngle(ANGLE90);

    _pMover->setRotAngleVelocityRenge(AXIS_X, 0, 5000);
    _pMover->setRotAngleVelocity(AXIS_X, 5000);
    _pMover->setRotAngleAcceleration(AXIS_X, 0);

    _pMover->setRotAngle(AXIS_Z, ANGLE180);

    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    _pStgChecker->setStatus(100, 1, 1, 1);
}

void EnemyVesta::processBehavior() {
    if (_pMover->_veloMove <= -8000) {
        _pMover->setMoveAcceleration(+500);
    } else if (_pMover->_veloMove >= +8000) {
        _pMover->setMoveAcceleration(-500);
    }
    _X -= 2000;

    //À•W‚É”½‰f
    _pMover->behave();
}

void EnemyVesta::processJudgement() {
    if (isOffScreen()) {
        adios();
    }
}

void EnemyVesta::processOnHit(GgafActor* prm_pActor_Opponent) {
    setBumpable(false);
    adios();
}

bool EnemyVesta::isOffScreen() {
    if (_Y < _Y_OffScreenBottom - 100000) {
        return true;
    } else {
        return false;
    }
}

EnemyVesta::~EnemyVesta() {
}
