#include "stdafx.h"

TamagoActor::TamagoActor(string prm_name, string prm_xname) : DefaultMeshActor(prm_name, prm_xname) {
}

void TamagoActor::initialize() {
	//declareStop();
	setBumpable(true);
//
	_pMover -> setMoveAngleRz(ANGLE180);
	_pMover -> setMoveVelocity(2000);
	_pMover -> _synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg = true;

//	_pMover -> setAxisRotAngle(AXIS_Z, ANGLE180*1000);
//	_pMover -> setMoveVelocity(2000);
//


//	_pMover -> _iTopIncrementAxisRotAngle[AXIS_Z] = 60 * 1000;
//
//	_pMover -> _synchronize_ZaxisAxisRotAngle_to_MoveAngleRz_Flg = true;
//	_pMover -> _iType_AutoXYMoveAngleTarget = TURN_COUNTERCLOCKWISE;

//	_pChecker -> useHitArea(1, 0);
//	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);

//	_pChecker -> useHitArea(0, 4);
//	_pChecker -> _pHitAreaBoxs -> setLine(0, -10000, -10000, 10000, -10000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(1, 10000, -10000, 10000, 10000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(2, 10000, 10000, -10000, 10000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(3, -10000, 10000, -10000, -10000, true);
//	_pChecker -> setStatus(100, 1, 2, 1);
	_dwFrameOffset = 0;
	//_pMover -> _iIncrementAxisRotAngle[AXIS_X] = -100*1000;

	_rnd = (110+(rand()%90));
}

void TamagoActor::processBehavior() {

	_dwFrameOffset ++;
	if (_pMover->_angAxisRot[AXIS_Z] < ANGLE180) {
		_pMover -> setAxisRotAngle(AXIS_X, ANGLE360-_pMover->_angAxisRot[AXIS_Z]);
	} else {
		_pMover -> setAxisRotAngle(AXIS_X, _pMover->_angAxisRot[AXIS_Z]);
	}
	//_pMover -> setAxisRotAngleVelocity(AXIS_X, 5*1000);//１フレーム0.5度

	if (_dwFrameOffset % _rnd == 0) {
		_rnd = (110+(rand()%90));

		_pMover -> setTargetMoveAngleRzV(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
		if (_pMover->getDistanceFromMoveAngleRzTo(_pMover->_angRzTarget_Move,TURN_CLOSE_TO) > 0) {
			_pMover -> setMoveAngleRzVelocity(2*1000);
		} else {
			_pMover -> setMoveAngleRzVelocity(-2*1000);
		}

		_pMover -> setMoveVelocityRenge(ANGLE360, 2*1000);
		_pMover -> setMoveVelocity(10*1000); //初速10px
		_pMover -> setMoveAcceleration(-80);
//		_pMover -> setTargetMoveAngleRz(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
	}

//	if (_dwFrameOffset == 10) {
//		//_pMover -> setTargetMoveAngleRz(c);
//		_pMover -> setMoveVelocity(2000);
//		_pMover -> setTargetMoveAngleRz(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
//	}
//
//	if (_dwFrameOffset == 150) {
//		_pMover -> setMoveVelocity(6000);
//		_pMover -> setTargetMoveAngleRz(ANGLE360*1000);
//		//_pMover -> setTargetAxisRotAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
//	}
//
//
//	if (_dwFrameOffset == 200) {
//
//		_pMover -> setMoveVelocity(6000);
//		_pMover -> setTargetMoveAngleRz(ANGLE90*1000);
//		//_pMover -> setTargetAxisRotAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
//	}
//
//	if (_dwFrameOffset == 250) {
//		_pMover -> setMoveVelocity(6000);
//		_pMover -> setTargetMoveAngleRz(0);
//	}
//	if (_dwFrameOffset == 300) {
//		_pMover -> setMoveVelocity(6000);
//		_pMover -> setTargetMoveAngleRz(2250*1000);
//	}
//	if (_dwFrameOffset == 400) {
//		_pMover -> setMoveVelocity(6000);
//		_pMover -> setTargetMoveAngleRz(ANGLE90*1000);
//	}
//
//	if (_dwFrameOffset == 500) {
//		_pMover -> setMoveVelocity(6000);
//		_pMover -> setTargetMoveAngleRz(3150*1000);
//	}
//
//	if (_dwFrameOffset == 550) {
//		_pMover -> setMoveVelocity(6000);
//		_pMover -> setTargetMoveAngleRz(ANGLE90*1000);
//	}
//	if (_dwFrameOffset == 570) {
//		_pMover -> setMoveVelocity(6000);
//		_pMover -> setTargetMoveAngleRz(2250*1000);
//	}
//
//
//	if (_dwFrameOffset == 650) {
//		_pMover -> setMoveVelocity(1000);
//		_pMover -> _iIncrementXYMoveSpeed = 30;
//		_pMover -> _auto_move_angle_target_Flg = false;
//		_pMover -> _auto_rot_angle_target_Flg = false;
//		_pMover -> _auto_rot_angle_Flg = true;
//		_pMover -> _iIncrementXYMoveAngle =80*1000;
//	}

	//座標に反映
	_pMover -> behave();

}

void TamagoActor::processJudgement() {
}

void TamagoActor::processOnHit(GgafActor* prm_pActor_Opponent) {
	_TRACE_("TamagoActorヒットしました。("<<_X<<","<<_Y<<")");
	setBumpable(false);
	declareFinishLife();
}


TamagoActor::~TamagoActor() {
}
