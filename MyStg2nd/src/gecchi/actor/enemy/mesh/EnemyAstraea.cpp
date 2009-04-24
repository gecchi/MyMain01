#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyAstraea::EnemyAstraea(const char* prm_name) : DefaultMeshEnemyActor(prm_name, "X/Astraea") {
    _class_name = "EnemyAstraea";
}

void EnemyAstraea::initialize() {
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    _pChecker->setStatus(100, 1, 1, 1);

}

void EnemyAstraea::processBehavior() {
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
