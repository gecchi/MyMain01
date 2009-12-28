#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoActor::TamagoActor(const char* prm_name) : GroundMeshActor(prm_name, "straw") {
    _class_name = "TamagoActor";
}

void TamagoActor::initialize() {
    //inactivateTree();
    setBumpable(false);
    _X = _Y = _Z = 0;
    _Y = 0;
//    _pMover->setRzMoveAngle(ANGLE180);
//    _pMover->setMoveVelocity(2000);
//    _pMover->_relate_RzFaceAngle_to_RzMoveAngle_flg = true;
//
    //	_pMover->setFaceAngle(AXIS_Z, ANGLE180*1000);
    _pMover->setMoveVelocity(-500);
    //


    //	_pMover->_topIncrementFaceAngle[AXIS_Z] = 60 * 1000;
    //
    //	_pMover->_synchronize_ZaxisFaceAngle_to_RzMoveAngle_Flg = true;
    //	_pMover->_iType_AutoXYMoveAngleTarget = TURN_COUNTERCLOCKWISE;

    //	_pStgChecker->useHitAreaBoxNum(1, 0);
    //	_pStgChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    _pMover->setFaceAngle(AXIS_Z, -ANGLE90);
    //_pMover->setFaceAngleVelocity(AXIS_Y, 1000);
//    _pStgChecker->useHitAreaBoxNum(2);
//    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
//    _pStgChecker->setHitAreaBox(1, 100000, 100000, 100000, 130000, 130000, 130000);
    _pScaler->setScale(20000000);
    _frame_offset = 0;
    //_pMover->_iIncrementFaceAngle[AXIS_X] = -100*1000;
    setAlpha(0.99);
    //_rnd = (110 + (rand() % 90));
}

void TamagoActor::processBehavior() {

    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
        _pScaler->addScale(200000);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
        _pScaler->addScale(-200000);
    }
    //座標に反映
    _pMover->behave();
    _pScaler->behave();
}

void TamagoActor::processJudgement() {
}

void TamagoActor::processOnHit(GgafActor* prm_pActor_Opponent) {
    _TRACE_("TamagoActorヒットしました。("<<_X<<","<<_Y<<","<<_Z<<")");
}

TamagoActor::~TamagoActor() {
}
