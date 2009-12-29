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
    _pScaler->setScaleRange(1000, 300);
    _pScaler->beat(30,5,10,-1);
    setBumpable(true);
}

void Shot001::onActive() {
    _pMover->setMoveVelocity(10000*_RANK_);             //ˆÚ“®‘¬“x
    _pMover->setFaceAngleVelocity(AXIS_X, 6000*_RANK_); //‚«‚è‚à‚Ý‹ï‡
}

void Shot001::processBehavior() {
    //À•W‚É”½‰f
    _pMover->behave();
    _pScaler->behave();
}

void Shot001::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void Shot001::processOnHit(GgafActor* prm_pActor_Opponent) {
    inactivate();
    setBumpable(false);
}

Shot001::~Shot001() {
}
