#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "X/ebi2") {
    _class_name = "EnemyAstraea";
}

void EnemyAstraea::initialize() {
    _X = _X_OffScreenRight;
    _Y = 0;
    _Z = 300000;


    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pChecker->setStatus(100, 1, 1, 1);
    _pGeoMover->setMoveVelocity(0);

    _pGeoMover->setRyMoveAngleVelocityRenge(-2000, 2000);
    _pGeoMover->setRzMoveAngleVelocityRenge(-2000, 2000);


}

void EnemyAstraea::processBehavior() {

    _X = _X - 1000;
    if (_lifeframe == 120) {
        _TRACE_("TURNBEGIN!");
        _pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_flg = true;
        _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_flg = true;
        _pGeoMover->setAutoTargetMoveAngle(GameGlobal::_pMyShip);
    }

    if (_pGeoMover->_synchronize_YRotAngle_to_RyMoveAngle_flg &&
        _pGeoMover->_synchronize_ZRotAngle_to_RzMoveAngle_flg ) {

    } else {



    }


    _pGeoMover->behave();
}

void EnemyAstraea::processJudgement() {
    if (isOffScreen()) {
        arigatou_sayounara();
    }
}

void EnemyAstraea::processOnHit(GgafActor* prm_pActor_Opponent) {
}

bool EnemyAstraea::isOffScreen() {
    if (_X < _X_OffScreenLeft - 800000) {
        return true;
    } else {
        return false;
    }
}

EnemyAstraea::~EnemyAstraea() {
}
