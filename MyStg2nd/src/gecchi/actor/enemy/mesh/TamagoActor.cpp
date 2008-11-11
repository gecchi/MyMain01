#include "stdafx.h"

TamagoActor::TamagoActor(string prm_name, string prm_model) : DefaultMeshActor(prm_name, prm_model) {
}

void TamagoActor::initialize() {
	//declareStop();
	setBumpable(true);
//
	_pGeoMover -> setMoveAngleRz(ANGLE180);
	_pGeoMover -> setMoveVelocity(2000);
	_pGeoMover -> _synchronize_ZAxisRotAngle_to_MoveAngleRz_Flg = true;

//	_pGeoMover -> setAxisRotAngle(AXIS_Z, ANGLE180*1000);
//	_pGeoMover -> setMoveVelocity(2000);
//


//	_pGeoMover -> _iTopIncrementAxisRotAngle[AXIS_Z] = 60 * 1000;
//
//	_pGeoMover -> _synchronize_ZaxisAxisRotAngle_to_MoveAngleRz_Flg = true;
//	_pGeoMover -> _iType_AutoXYMoveAngleTarget = TURN_COUNTERCLOCKWISE;

//	_pChecker -> useHitArea(1, 0);
//	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);

//	_pChecker -> useHitArea(0, 4);
//	_pChecker -> _pHitAreaBoxs -> setLine(0, -10000, -10000, 10000, -10000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(1, 10000, -10000, 10000, 10000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(2, 10000, 10000, -10000, 10000, true);
//	_pChecker -> _pHitAreaBoxs -> setLine(3, -10000, 10000, -10000, -10000, true);
//	_pChecker -> setStatus(100, 1, 2, 1);
	_dwFrameOffset = 0;
	//_pGeoMover -> _iIncrementAxisRotAngle[AXIS_X] = -100*1000;

	_rnd = (110+(rand()%90));
}

void TamagoActor::processBehavior() {

	_dwFrameOffset ++;
	if (_pGeoMover->_angAxisRot[AXIS_Z] < ANGLE180) {
		_pGeoMover -> setAxisRotAngle(AXIS_X, ANGLE360-_pGeoMover->_angAxisRot[AXIS_Z]);
	} else {
		_pGeoMover -> setAxisRotAngle(AXIS_X, _pGeoMover->_angAxisRot[AXIS_Z]);
	}
	//_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, 5*1000);//１フレーム0.5度

	if (_dwFrameOffset % _rnd == 0) {
		_rnd = (110+(rand()%90));

		_pGeoMover -> setTargetMoveAngleRzV(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
		if (_pGeoMover->getDistanceFromMoveAngleRzTo(_pGeoMover->_angRzTarget_Move,TURN_CLOSE_TO) > 0) {
			_pGeoMover -> setMoveAngleRzVelocity(2*1000);
		} else {
			_pGeoMover -> setMoveAngleRzVelocity(-2*1000);
		}

		_pGeoMover -> setMoveVelocityRenge(ANGLE360, 2*1000);
		_pGeoMover -> setMoveVelocity(10*1000); //初速10px
		_pGeoMover -> setMoveAcceleration(-80);
//		_pGeoMover -> setTargetMoveAngleRz(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
	}

//	if (_dwFrameOffset == 10) {
//		//_pGeoMover -> setTargetMoveAngleRz(c);
//		_pGeoMover -> setMoveVelocity(2000);
//		_pGeoMover -> setTargetMoveAngleRz(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
//	}
//
//	if (_dwFrameOffset == 150) {
//		_pGeoMover -> setMoveVelocity(6000);
//		_pGeoMover -> setTargetMoveAngleRz(ANGLE360*1000);
//		//_pGeoMover -> setTargetAxisRotAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
//	}
//
//
//	if (_dwFrameOffset == 200) {
//
//		_pGeoMover -> setMoveVelocity(6000);
//		_pGeoMover -> setTargetMoveAngleRz(ANGLE90*1000);
//		//_pGeoMover -> setTargetAxisRotAngle(GameGlobal::_pMyShip->_X,GameGlobal::_pMyShip->_Y);
//	}
//
//	if (_dwFrameOffset == 250) {
//		_pGeoMover -> setMoveVelocity(6000);
//		_pGeoMover -> setTargetMoveAngleRz(0);
//	}
//	if (_dwFrameOffset == 300) {
//		_pGeoMover -> setMoveVelocity(6000);
//		_pGeoMover -> setTargetMoveAngleRz(2250*1000);
//	}
//	if (_dwFrameOffset == 400) {
//		_pGeoMover -> setMoveVelocity(6000);
//		_pGeoMover -> setTargetMoveAngleRz(ANGLE90*1000);
//	}
//
//	if (_dwFrameOffset == 500) {
//		_pGeoMover -> setMoveVelocity(6000);
//		_pGeoMover -> setTargetMoveAngleRz(3150*1000);
//	}
//
//	if (_dwFrameOffset == 550) {
//		_pGeoMover -> setMoveVelocity(6000);
//		_pGeoMover -> setTargetMoveAngleRz(ANGLE90*1000);
//	}
//	if (_dwFrameOffset == 570) {
//		_pGeoMover -> setMoveVelocity(6000);
//		_pGeoMover -> setTargetMoveAngleRz(2250*1000);
//	}
//
//
//	if (_dwFrameOffset == 650) {
//		_pGeoMover -> setMoveVelocity(1000);
//		_pGeoMover -> _iIncrementXYMoveSpeed = 30;
//		_pGeoMover -> _auto_move_angle_target_Flg = false;
//		_pGeoMover -> _auto_rot_angle_target_Flg = false;
//		_pGeoMover -> _auto_rot_angle_Flg = true;
//		_pGeoMover -> _iIncrementXYMoveAngle =80*1000;
//	}

	//座標に反映
	_pGeoMover -> behave();

}

void TamagoActor::processJudgement() {
}

void TamagoActor::processOnHit(GgafActor* prm_pActor_Opponent) {
	//_TRACE_("TamagoActorヒットしました。("<<_X<<","<<_Y<<")");
	setBumpable(false);
	declareFinishLife();
}


TamagoActor::~TamagoActor() {
}
