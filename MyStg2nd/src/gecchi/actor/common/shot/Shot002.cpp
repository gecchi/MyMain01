#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot002::Shot002(const char* prm_name) : DefaultMeshSetActor(prm_name, "16/shot002") {
    _class_name = "Shot002";
}

void Shot002::initialize() {
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);
    setBumpable(true);
}

void Shot002::onActive() {
    _pMover->setMoveVelocity(10000*_RANK_);
    _pMover->setFaceAngleVelocity(AXIS_X, 6000*_RANK_);
}

void Shot002::processBehavior() {
    //À•W‚É”½‰f
    _pMover->behave();
}

void Shot002::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void Shot002::processOnHit(GgafActor* prm_pActor_Opponent) {
    inactivate();
}

Shot002::~Shot002() {
}
