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
    _X = GgafDx9Camera::_X_ScreenRight + 120000;
    _Y = 0;
    _Z = 0;
    _pMover->setMoveVelocity(0);
    _pMover->setVxMoveVelocity(2000);
    _pMover->setFaceAngleVelocity(AXIS_Z, 1000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    _pStgChecker->setStatus(100, 1, 1, 1);
}

void EnemyVesta::processBehavior() {
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
    if (_Y < GgafDx9Camera::_Y_ScreenBottom - 100000) {
        return true;
    } else {
        return false;
    }
}

EnemyVesta::~EnemyVesta() {
}
