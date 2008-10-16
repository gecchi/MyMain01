#include "stdafx.h"

TamagoActor::TamagoActor(string prm_name, string prm_xname) : DefaultMeshActor(prm_name, prm_xname) {
}

void TamagoActor::initialize() {
	//declareStop();
	setBumpable(true);
//
	_pMover -> setXYMoveAngle(ANGLE180);
	_pMover -> setXYMoveVelocity(2000);
	_pMover -> _synchronize_ZAxisRotAngle_to_XYMoveAngle_Flg = true;

//	_pMover -> setAxisRotAngle(AXIS_Z, ANGLE180*1000);
//	_pMover -> setXYMoveVelocity(2000);
//


//	_pMover -> _iTopIncrementAxisRotAngle[AXIS_Z] = 60 * 1000;
//
//	_pMover -> _synchronize_ZaxisAxisRotAngle_to_XYMoveAngle_Flg = true;
//	_pMover -> _iType_AutoXYMoveAngleTarget = TURN_COUNTERCLOCKWISE;

//	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
//	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);

	_pChecker -> _pHitArea2D = NEW HitArea2D(0, 4);
	_pChecker -> _pHitArea2D -> setLine(0, -10000, -10000, 10000, -10000, true);
	_pChecker -> _pHitArea2D -> setLine(1, 10000, -10000, 10000, 10000, true);
	_pChecker -> _pHitArea2D -> setLine(2, 10000, 10000, -10000, 10000, true);
	_pChecker -> _pHitArea2D -> setLine(3, -10000, 10000, -10000, -10000, true);
	_pChecker -> setStatus(100, 1, 2, 1);
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

		_pMover -> setTargetXYMoveAngleV(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
		if (_pMover->getDistanceFromXYMoveAngleTo(_pMover->_angTarget_XYMove,TURN_CLOSE_TO) > 0) {
			_pMover -> setXYMoveAngleVelocity(2*1000);
		} else {
			_pMover -> setXYMoveAngleVelocity(-2*1000);
		}

		_pMover -> setXYMoveVelocityRenge(ANGLE360, 2*1000);
		_pMover -> setXYMoveVelocity(10*1000); //初速10px
		_pMover -> setXYMoveAcceleration(-80);
//		_pMover -> setTargetXYMoveAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
	}

//	if (_dwFrameOffset == 10) {
//		//_pMover -> setTargetXYMoveAngle(c);
//		_pMover -> setXYMoveVelocity(2000);
//		_pMover -> setTargetXYMoveAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
//	}
//
//	if (_dwFrameOffset == 150) {
//		_pMover -> setXYMoveVelocity(6000);
//		_pMover -> setTargetXYMoveAngle(ANGLE360*1000);
//		//_pMover -> setTargetAxisRotAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
//	}
//
//
//	if (_dwFrameOffset == 200) {
//
//		_pMover -> setXYMoveVelocity(6000);
//		_pMover -> setTargetXYMoveAngle(ANGLE90*1000);
//		//_pMover -> setTargetAxisRotAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
//	}
//
//	if (_dwFrameOffset == 250) {
//		_pMover -> setXYMoveVelocity(6000);
//		_pMover -> setTargetXYMoveAngle(0);
//	}
//	if (_dwFrameOffset == 300) {
//		_pMover -> setXYMoveVelocity(6000);
//		_pMover -> setTargetXYMoveAngle(2250*1000);
//	}
//	if (_dwFrameOffset == 400) {
//		_pMover -> setXYMoveVelocity(6000);
//		_pMover -> setTargetXYMoveAngle(ANGLE90*1000);
//	}
//
//	if (_dwFrameOffset == 500) {
//		_pMover -> setXYMoveVelocity(6000);
//		_pMover -> setTargetXYMoveAngle(3150*1000);
//	}
//
//	if (_dwFrameOffset == 550) {
//		_pMover -> setXYMoveVelocity(6000);
//		_pMover -> setTargetXYMoveAngle(ANGLE90*1000);
//	}
//	if (_dwFrameOffset == 570) {
//		_pMover -> setXYMoveVelocity(6000);
//		_pMover -> setTargetXYMoveAngle(2250*1000);
//	}
//
//
//	if (_dwFrameOffset == 650) {
//		_pMover -> setXYMoveVelocity(1000);
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
