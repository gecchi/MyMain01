#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot002::Shot002(const char* prm_name) : DefaultMeshSetActor(prm_name, "16/donatu_0") {
    _class_name = "Shot002";
    _my_frame = 0;
}

void Shot002::initialize() {
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, 30000, 30000);

    setBumpable(true);
}

void Shot002::onActive() {
    _pMover->relateRzRyFaceAngleToMoveAngle(true);
    _pMover->setMoveVelocity(15000*_RANK_);
    _pMover->setFaceAngleVelocity(AXIS_X, 8000*_RANK_);
    _my_frame = 0;
}

void Shot002::processBehavior() {
    if (_my_frame == 80) {
        _pMover->executeTagettingMoveAngleSequence(pMYSHIP,5000,TURN_CLOSE_TO);
    }
    //À•W‚É”½‰f
    _pMover->behave();
    _my_frame++;
}

void Shot002::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void Shot002::processOnHit(GgafActor* prm_pActor_Opponent) {
    inactivate();
    setBumpable(false);
}

Shot002::~Shot002() {
}
