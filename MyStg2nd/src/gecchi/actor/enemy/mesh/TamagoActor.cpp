#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

TamagoActor::TamagoActor(const char* prm_name) : DefaultD3DXMeshActor(prm_name, "tamago") {
    _class_name = "TamagoActor";
}

void TamagoActor::initialize() {
    //inactivateTree();
    setBumpable(true);
    //
//    _pMover->setRzMoveAngle(ANGLE180);
//    _pMover->setMoveVelocity(2000);
//    _pMover->_synchronize_RzFaceAngle_to_RzMoveAngle_flg = true;
//
    //	_pMover->setFaceAngle(AXIS_Z, ANGLE180*1000);
    //	_pMover->setMoveVelocity(2000);
    //


    //	_pMover->_topIncrementFaceAngle[AXIS_Z] = 60 * 1000;
    //
    //	_pMover->_synchronize_ZaxisFaceAngle_to_RzMoveAngle_Flg = true;
    //	_pMover->_iType_AutoXYMoveAngleTarget = TURN_COUNTERCLOCKWISE;

    //	_pStgChecker->useHitAreaBoxNum(1, 0);
    //	_pStgChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);

    _pStgChecker->useHitAreaBoxNum(2);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _pStgChecker->setHitAreaBox(1, 100000, 100000, 100000, 130000, 130000, 130000);
    _SX = _SY = _SZ = 10*1000;
    _frame_offset = 0;
    //_pMover->_iIncrementFaceAngle[AXIS_X] = -100*1000;

    //_rnd = (110 + (rand() % 90));
}

void TamagoActor::processBehavior() {

//    _frame_offset++;
//    if (_pMover->_angFace[AXIS_Z] < ANGLE180) {
//        _pMover->setFaceAngle(AXIS_X, ANGLE360 - _pMover->_angFace[AXIS_Z]);
//    } else {
//        _pMover->setFaceAngle(AXIS_X, _pMover->_angFace[AXIS_Z]);
//    }
//    //_pMover->setFaceAngleVelocity(AXIS_X, 5*1000);//１フレーム0.5度
//
//    if (_frame_offset % _rnd == 0) {
//        _rnd = (110 + (rand() % 90));
//
//        _pMover->setStopTarget_RzMoveAngleV(GameGlobal::_pMyShip->_X, GameGlobal::_pMyShip->_Y);
//        if (_pMover->getRzMoveAngleDistance(_pMover->_angTargetRzMove, TURN_CLOSE_TO) > 0) {
//            _pMover->setRzMoveAngleVelocity(2 * 1000);
//        } else {
//            _pMover->setRzMoveAngleVelocity(-2 * 1000);
//        }
//
//        _pMover->setMoveVeloRenge(ANGLE360, 2 * 1000);
//        _pMover->setMoveVelocity(10 * 1000); //初速10px
//        _pMover->setMoveVeloAcceleration(-80);
//        //		_pMover->setStopTarget_RzMoveAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
//    }

    //	if (_frame_offset == 10) {
    //		//_pMover->setStopTarget_RzMoveAngle(c);
    //		_pMover->setMoveVelocity(2000);
    //		_pMover->setStopTarget_RzMoveAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
    //	}
    //
    //	if (_frame_offset == 150) {
    //		_pMover->setMoveVelocity(6000);
    //		_pMover->setStopTarget_RzMoveAngle(ANGLE360*1000);
    //		//_pMover->setStopTarget_FaceAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
    //	}
    //
    //
    //	if (_frame_offset == 200) {
    //
    //		_pMover->setMoveVelocity(6000);
    //		_pMover->setStopTarget_RzMoveAngle(ANGLE90*1000);
    //		//_pMover->setStopTarget_FaceAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
    //	}
    //
    //	if (_frame_offset == 250) {
    //		_pMover->setMoveVelocity(6000);
    //		_pMover->setStopTarget_RzMoveAngle(0);
    //	}
    //	if (_frame_offset == 300) {
    //		_pMover->setMoveVelocity(6000);
    //		_pMover->setStopTarget_RzMoveAngle(2250*1000);
    //	}
    //	if (_frame_offset == 400) {
    //		_pMover->setMoveVelocity(6000);
    //		_pMover->setStopTarget_RzMoveAngle(ANGLE90*1000);
    //	}
    //
    //	if (_frame_offset == 500) {
    //		_pMover->setMoveVelocity(6000);
    //		_pMover->setStopTarget_RzMoveAngle(3150*1000);
    //	}
    //
    //	if (_frame_offset == 550) {
    //		_pMover->setMoveVelocity(6000);
    //		_pMover->setStopTarget_RzMoveAngle(ANGLE90*1000);
    //	}
    //	if (_frame_offset == 570) {
    //		_pMover->setMoveVelocity(6000);
    //		_pMover->setStopTarget_RzMoveAngle(2250*1000);
    //	}
    //
    //
    //	if (_frame_offset == 650) {
    //		_pMover->setMoveVelocity(1000);
    //		_pMover->_iIncrementXYMoveSpeed = 30;
    //		_pMover->_move_angle_target_Flg = false;
    //		_pMover->_face_angle_targeting_flg = false;
    //		_pMover->_face_angle_Flg = true;
    //		_pMover->_iIncrementXYMoveAngle =80*1000;
    //	}

    //座標に反映
    _pMover->behave();

}

void TamagoActor::processJudgement() {
}

void TamagoActor::processOnHit(GgafActor* prm_pActor_Opponent) {
    _TRACE_("TamagoActorヒットしました。("<<_X<<","<<_Y<<","<<_Z<<")");
}

TamagoActor::~TamagoActor() {
}
