#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyPallas::EnemyPallas(const char* prm_name) : DefaultMeshSetActor(prm_name, "Pallas") {
    _class_name = "EnemyPallas";

    _iMovePatternNo = 0;
}

void EnemyPallas::initialize() {
    setHitAble(true);
    _X = GgafDx9Camera::_X_ScreenRight + 100;
    _Y = 0;
    _Z = 0;
    _pMover->forceMvVeloRange(-8000, 8000);
    _pMover->setMvVelo(8000);
    _pMover->setMvAcce(-500);
    _pMover->setRzMvAng(ANGLE90);

    _pMover->forceFaceAngVeloRange(AXIS_X, 0, 5000);
    _pMover->setFaceAngVelo(AXIS_X, 5000);
    _pMover->setFaceAngAcce(AXIS_X, 0);

    _pMover->setFaceAng(AXIS_Z, ANGLE180);

    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -10000, -10000, 10000, 10000);
}

void EnemyPallas::processBehavior() {
    if (_pMover->_veloMv <= -8000) {
        _pMover->setMvAcce(+500);
    } else if (_pMover->_veloMv >= +8000) {
        _pMover->setMvAcce(-500);
    }

    _X -= 2000;

    //À•W‚É”½‰f
    _pMover->behave();
}

void EnemyPallas::processJudgement() {
    if (isOutOfGameSpace()) {
        retire();
    }
}

void EnemyPallas::onHit(GgafActor* prm_pOtherActor) {
    setHitAble(false);
    retire();
}

bool EnemyPallas::isOutOfGameSpace() {
    if (_X < GgafDx9Camera::_X_ScreenLeft - 100000) {
        return true;
    } else {
        return false;
    }
}

EnemyPallas::~EnemyPallas() {
}
