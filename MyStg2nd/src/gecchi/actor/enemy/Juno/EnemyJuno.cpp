#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyJuno::EnemyJuno(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "Juno") {
    _class_name = "EnemyJuno";

    _iMovePatternNo = 0;
}

void EnemyJuno::initialize() {

    _Z = 5000000;
    _pMover->setMvVelo(0);
    _pMover->setVzMvVelo(-40000);
    _pMover->setFaceAngVelo(AXIS_X, 5000);
    _pMover->setFaceAng(AXIS_Y, 90000);

    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -10000, -10000, 10000, 10000);
}

void EnemyJuno::processBehavior() {
    if (onChangeToActive()) {
        //oŒ»Žžˆ—
        setHitAble(true);
        _X += FormationJuno001::_X_FormationWhole;
    }

    _X += FormationJuno001::_incX;
    //À•W‚É”½‰f
    _pMover->behave();
}

void EnemyJuno::processJudgement() {
    if (isOutOfGameSpace()) {
        setHitAble(false);
        adios();
    }
}

void EnemyJuno::onHit(GgafActor* prm_pOtherActor) {
    setHitAble(false);
    adios();
}

int EnemyJuno::isOutOfGameSpace() {
    if (_Z < -1000000) {
        return true;
    } else {
        return false;
    }
}

EnemyJuno::~EnemyJuno() {
}
