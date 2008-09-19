#include "stdafx.h"



#define VSP 3
//DIAGONAL = 1000 / √2
#define DIAGONAL_LEN_UNIT 707


MyShipActor::MyShipActor(string prm_name, string prm_xname) : DefaultMeshActor(prm_name, prm_xname) {
	GameGlobal::_pMyShipActor = this;
	_pMyShots001Rotation = NULL;
}

void MyShipActor::initialize() {
	_turboFlg = false;
	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pMover -> setXYMoveVelocity(0);
}

void MyShipActor::processBehavior() {

	if (VirtualButton::isBeingPressed(VB_UP_STC)) {
		_Y += LEN_UNIT*VSP;
	} else if (VirtualButton::isBeingPressed(VB_UP_RIGHT_STC)) {
		_X += DIAGONAL_LEN_UNIT*VSP;
		_Y += DIAGONAL_LEN_UNIT*VSP;
	} else if (VirtualButton::isBeingPressed(VB_RIGHT_STC)) {
		_X += LEN_UNIT*VSP;
	} else if (VirtualButton::isBeingPressed(VB_DOWN_RIGHT_STC)) {
		_X += DIAGONAL_LEN_UNIT*VSP;
		_Y -= DIAGONAL_LEN_UNIT*VSP;
	} else if (VirtualButton::isBeingPressed(VB_DOWN_STC)) {
		_Y -= LEN_UNIT*VSP;
	} else if (VirtualButton::isBeingPressed(VB_DOWN_LEFT_STC)) {
		_X -= DIAGONAL_LEN_UNIT*VSP;
		_Y -= DIAGONAL_LEN_UNIT*VSP;
	} else if (VirtualButton::isBeingPressed(VB_LEFT_STC)) {
		_X -= LEN_UNIT*VSP;
	} else if (VirtualButton::isBeingPressed(VB_UP_LEFT_STC)) {
		_X -= DIAGONAL_LEN_UNIT*VSP;
		_Y += DIAGONAL_LEN_UNIT*VSP;
	} else {

	}
	if (!_turboFlg && (VirtualButton::isNotBeingPressed(VB_UP) && VirtualButton::isNotBeingPressed(VB_DOWN))) {
		int rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, 0, TURN_CLOSE_TO);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, rd==0 ? 0 : rd/30);
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 1*1000, -1*1000);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);
	}
	if (!_turboFlg && VirtualButton::isPushedDown(VB_UP) ) {
		_pMover -> setTargetAxisRotAngle(AXIS_X, 85*1000);
		int rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, _pMover->_angTarget_AxisRot[AXIS_X], TURN_CLOSE_TO);
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 360*1000, 1*1000);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, rd/13);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, -700);

	} else if ( (!_turboFlg && VirtualButton::isPushedDown(VB_DOWN) && VirtualButton::isNotBeingPressed(VB_UP)) ||
	            (!_turboFlg && VirtualButton::isBeingPressed(VB_DOWN) && VirtualButton::isReleasedUp(VB_UP) )) {
		_pMover -> setTargetAxisRotAngle(AXIS_X, 275*1000);
		int rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, _pMover->_angTarget_AxisRot[AXIS_X], TURN_CLOSE_TO);
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*1000, -360*1000);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, rd/13);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, +700);
	}

	if (_turboFlg != true && VirtualButton::isPushedDown(VB_TURBO) && !VirtualButton::isBeingPressed(VB_NEUTRAL_STC)) {
		_turboFlg = true;
		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pMover -> setXYMoveVelocityRenge(100*1000, 1*1000);
		_pMover -> setXYMoveVelocity(12*1000); //初速15px
		_pMover -> setXYMoveAcceleration(-500); //毎フレーム初速0.5px減速

		if (VirtualButton::isBeingPressed(VB_UP_STC)) {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 360*1000, 1*1000);
			_pMover -> setAxisRotAngleVelocity(AXIS_X, 20*1000);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);
			_pMover -> setXYMoveAngle(ANGLE90);
		} else if (VirtualButton::isBeingPressed(VB_UP_RIGHT_STC)) {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 360*1000, 1*1000);
			_pMover -> setAxisRotAngleVelocity(AXIS_X, 20*1000);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, -500);
			_pMover -> setXYMoveAngle(ANGLE45);
		} else if (VirtualButton::isBeingPressed(VB_UP_LEFT_STC)) {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 360*1000, 1*1000);
			_pMover -> setAxisRotAngleVelocity(AXIS_X, 20*1000);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, -500);
			_pMover -> setXYMoveAngle(ANGLE135);
		} else if (VirtualButton::isBeingPressed(VB_DOWN_STC)) {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*1000, -360*1000);
			_pMover -> setAxisRotAngleVelocity(AXIS_X, -20*1000);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, +500);
			_pMover -> setXYMoveAngle(ANGLE270);
		} else if (VirtualButton::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*1000, -360*1000);
			_pMover -> setAxisRotAngleVelocity(AXIS_X, -20*1000);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, +500);
			_pMover -> setXYMoveAngle(ANGLE315);
		} else if (VirtualButton::isBeingPressed(VB_DOWN_LEFT_STC)) {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*1000, -360*1000);
			_pMover -> setAxisRotAngleVelocity(AXIS_X, -20*1000);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, +500);
			_pMover -> setXYMoveAngle(ANGLE225);
		} else if (VirtualButton::isBeingPressed(VB_LEFT_STC)) {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 0, 0);
			_pMover -> setAxisRotAngleVelocity(AXIS_X, 0);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);
			_pMover -> setXYMoveAngle(ANGLE180);
		} else if (VirtualButton::isBeingPressed(VB_RIGHT_STC)) {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 0, 0);
			_pMover -> setAxisRotAngleVelocity(AXIS_X, 0);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);
			_pMover -> setXYMoveAngle(0);
		}  else {
			_TRACE_("ぶおーん！");
		}
	}

	if (_turboFlg && _pMover ->_iVelocity_XYMove < 2*2000) {
		_turboFlg = false;
		_pMover -> setXYMoveVelocityRenge(100*1000, -100*1000);
		_pMover -> setXYMoveVelocity(0);
		_pMover -> setXYMoveAcceleration(0);

		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = true;
		if (sgn(_pMover->_angVelocity_AxisRotAngle[AXIS_X]) > 0) {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 360*1000, 1*1000);
			_pMover -> setAxisRotAngleVelocity(AXIS_X, 6*1000);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);
		} else if (sgn(_pMover->_angVelocity_AxisRotAngle[AXIS_X]) < 0) {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*1000, -360*1000);
			_pMover -> setAxisRotAngleVelocity(AXIS_X, -6*1000);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, 0);
		}
		if (VirtualButton::isBeingPressed(VB_UP)) {
			_pMover -> setTargetAxisRotAngle(AXIS_X, 85*1000);
		} else if (VirtualButton::isBeingPressed(VB_DOWN)) {
			_pMover -> setTargetAxisRotAngle(AXIS_X, 275*1000);
		}
	}


	//ショットボタン
	if (VirtualButton::arePushedDownAtOnce(VB_SHOT2, VB_SHOT3) || VirtualButton::isBeingPressed(VB_SHOT1)) {
		Shot001Actor* pShot = (Shot001Actor*)(_pMyShots001Rotation->get());
		if (pShot) {
			pShot->shotBegin();
		}
	}


	if (VirtualButton::isBeingPressed(VB_POWERUP)) {
		_SX -= 100;
		_SY -= 100;
		_SZ -= 100;
	}
	if (VirtualButton::isBeingPressed(VB_GUARD)) {
		_SX+= 100;
		_SY+= 100;
		_SZ+= 100;
	}

	//座標に反映
	_pMover -> behave();


}

void MyShipActor::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

/*
bool MyShipActor::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
	//TRACE("MyShipActor::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"ｘ"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
	return false;
}
*/

void MyShipActor::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareFinishLife();
}


MyShipActor::~MyShipActor() {
}
