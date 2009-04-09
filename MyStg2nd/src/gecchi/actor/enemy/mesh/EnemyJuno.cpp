#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyJuno::EnemyJuno(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "X/Juno") {
    _class_name = "EnemyJuno";

    _iMovePatternNo = 0;
}

void EnemyJuno::initialize() {

    _Z = 5000000;
    _pGeoMover->setMoveVelocity(0);
    _pGeoMover->setVzMoveVelocity(-40000);
    _pGeoMover->setRotAngleVelocity(AXIS_X, 5000);
    _pGeoMover->setRotAngle(AXIS_Y, 90000);

    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    _pChecker->setStatus(100, 1, 1, 1);
}

void EnemyJuno::processBehavior() {
    if (switchedToActive()) {
        //oŒ»Žžˆ—
        setBumpableAlone(true);
        _X += FormationJuno001::_X_FormationWhole;
    }

    _X += FormationJuno001::_incX;
    //À•W‚É”½‰f
    _pGeoMover->behave();
}

void EnemyJuno::processJudgement() {
    if (isOffScreen()) {
        setBumpableAlone(false);
        arigatou_sayounara();
    }
}

void EnemyJuno::processOnHit(GgafActor* prm_pActor_Opponent) {
    setBumpableAlone(false);
    arigatou_sayounara();
}

bool EnemyJuno::isOffScreen() {
    if (_Z < -1000000) {
        return true;
    } else {
        return false;
    }
}

EnemyJuno::~EnemyJuno() {
}
