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
    setBumpableAlone(true);
    _X = _X_OffScreenRight + 100;
    _Y = 0;
    _Z = 0;
    _pGeoMover->setMoveVelocityRenge(-8000, 8000);
    _pGeoMover->setMoveVelocity(8000);
    _pGeoMover->setMoveAcceleration(-500);
    _pGeoMover->setRzMoveAngle(ANGLE90);

    _pGeoMover->setRotAngleVelocityRenge(AXIS_X, 0, 5000);
    _pGeoMover->setRotAngleVelocity(AXIS_X, 5000);
    _pGeoMover->setRotAngleAcceleration(AXIS_X, 0);

    _pGeoMover->setRotAngle(AXIS_Z, ANGLE180);

    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    _pChecker->setStatus(100, 1, 1, 1);
}

void EnemyVesta::processBehavior() {
    if (_pGeoMover->_veloMove <= -8000) {
        _pGeoMover->setMoveAcceleration(+500);
    } else if (_pGeoMover->_veloMove >= +8000) {
        _pGeoMover->setMoveAcceleration(-500);
    }
    _X -= 2000;

    //À•W‚É”½‰f
    _pGeoMover->behave();
}

void EnemyVesta::processJudgement() {
    if (isOffScreen()) {
        arigatou_sayounara();
    }
}

void EnemyVesta::processOnHit(GgafActor* prm_pActor_Opponent) {
    setBumpableAlone(false);
    arigatou_sayounara();
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
