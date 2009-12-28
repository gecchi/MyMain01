#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot001::Shot001(const char* prm_name) : DefaultMeshSetActor(prm_name, "16/shot001") {
    _class_name = "Shot001";
}

void Shot001::initialize() {
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    setBumpable(true);
}

void Shot001::onActive() {
    _pMover->setMoveVelocity(10000*_RANK_);
    _pMover->setFaceAngleVelocity(AXIS_X, 6000*_RANK_);
}

void Shot001::processBehavior() {
    //À•W‚É”½‰f
    _pMover->behave();
}

void Shot001::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void Shot001::processOnHit(GgafActor* prm_pActor_Opponent) {
    inactivate();
}

Shot001::~Shot001() {
}
