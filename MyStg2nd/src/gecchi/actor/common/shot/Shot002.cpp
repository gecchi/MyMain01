#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot002::Shot002(const char* prm_name) : DefaultMeshSetActor(prm_name, "16/Flora") {
    _class_name = "Shot002";
    MyStgUtil::resetShot002Status(this);
    _my_frame = 0;
}

void Shot002::initialize() {
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -50000, -50000, -50000, 50000, 50000, 50000);
    useSe1("break_glass01");
}

void Shot002::onActive() {
    MyStgUtil::resetShot002Status(this);
    setBumpable(true);
    _pScaler->setScale(300);
    _pMover->relateRzRyFaceAngleToMoveAngle(true);
    _pMover->setMoveVelocity(8000*_RANK_);
    _pMover->setFaceAngleVelocity(AXIS_X, 1000*_RANK_);
    _my_frame = 0;
}

void Shot002::processBehavior() {



    if (_my_frame == 70) {
        _pMover->executeTagettingMoveAngleSequence(pMYSHIP,3000,TURN_CLOSE_TO);
    }

    if (_my_frame > 70 && _pMover->_move_angle_ry_target_flg == false && _pMover->_move_angle_rz_target_flg == false) {
        _pMover->executeTagettingMoveAngleSequence(
                    GameGlobal::_pMyShip,
                    100, TURN_CLOSE_TO);
    }
    //À•W‚É”½‰f
    _pMover->behave();
    _pScaler->behave();
    _my_frame++;
}

void Shot002::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void Shot002::processOnHit(GgafActor* prm_pOtherActor) {
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    playSe1();
    if (pExplo001 != NULL) {
        pExplo001->activate();
        pExplo001->setGeometry(this);
    }
    inactivate();
}

Shot002::~Shot002() {
}
