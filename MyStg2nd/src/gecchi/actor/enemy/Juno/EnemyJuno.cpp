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
    _pMover->setMoveVelocity(0);
    _pMover->setVzMoveVelocity(-40000);
    _pMover->setFaceAngleVelocity(AXIS_X, 5000);
    _pMover->setFaceAngle(AXIS_Y, 90000);

    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    _pStgChecker->setStatus(100, 1, 1, 1);
}

void EnemyJuno::processBehavior() {
    if (onChangeToActive()) {
        //出現時処理
        setBumpable(true);
        _X += FormationJuno001::_X_FormationWhole;
    }

    _X += FormationJuno001::_incX;
    //座標に反映
    _pMover->behave();
}

void EnemyJuno::processJudgement() {
    if (isOutOfGameSpace()) {
        setBumpable(false);
        adios();
    }
}

void EnemyJuno::processOnHit(GgafActor* prm_pActor_Opponent) {
    setBumpable(false);
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
