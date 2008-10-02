#include "stdafx.h"

#define newState(H,X) do { H->e = new State*[X]; for (int i = 0; i < X; i++) {H->e[i] = new State(); } } while(0)
#define S_OPTION 0

#define VSP 3
//DIAGONAL = 1000 / ��2
#define DIAGONAL_LEN_UNIT 707

MyShip::MyShip(string prm_name, string prm_xname) : DefaultMeshActor(prm_name, prm_xname) {
	GameGlobal::_pMyShip = this;

	//CommonScene��new�̏ꍇ�ݒ�
	_iShotKind01 = 0;
	_iShotKind02 = 0;
	_iShotKind03 = 0;

	//�L���b�V�����[�h
	GgafDx9SeManager::get("laser001");


	//_state->e = new State[10];

}

void MyShip::initialize() {
	_turboFlg = false;
	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pMover -> setXYMoveVelocity(0);
}

void MyShip::processBehavior() {

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
		_pMover -> setXYMoveVelocity(12*1000); //����15px
		_pMover -> setXYMoveAcceleration(-500); //���t���[������0.5px����

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
			_TRACE_("�Ԃ��[��I");
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


	//�V���b�g�{�^��
	if (VirtualButton::isPushedDown(VB_SHOT1)) {
		MyShot001* pShot = (MyShot001*)GameGlobal::_pSceneCommon->_pMyShots001Rotation->obtain();
		if (pShot) {
			pShot->declarePlay();

			EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
			if (pExplo001) {
				pExplo001->declarePlay();
			}
		}
	}

	if (VirtualButton::isBeingPressed(VB_SHOT2)) {
		//RotationActor�̐�����A�����A�N�^�[�� play ���Ă��Ȃ���΁A�S�Ă̗v�f�� play ���Ă��Ȃ����ƂɂȂ�B
		RotationActor* pLasersStock = GameGlobal::_pSceneCommon->_pMyLaser001Rotation;
		MyLaser001* pLastLaser = (MyLaser001*)pLasersStock->getSubFirst()->getPrev();
		if (!pLastLaser->isPlaying() && !pLastLaser->_willPlayNextFrame) {
			MyLaser001* pLaser = (MyLaser001*)pLasersStock->obtain();
			if (pLaser) {
				MyLaser001::_pHeadMyLaser001 = pLaser;
				pLaser->declarePlay();
				GgafDx9SeManager::get("laser001")->play();
			}
		} else if (MyLaser001::_pHeadMyLaser001 != NULL) {
			MyLaser001* pLaser = (MyLaser001*)pLasersStock->obtain();
			if (pLaser) {
				pLaser->declarePlay();
			}
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

	//���W�ɔ��f
	_pMover -> behave();


}

void MyShip::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

/*
bool MyShip::processBumpChkLogic(GgafDx9UntransformedActor* prm_pActor_Opponent) {
	//TRACE("MyShip::processBumpChkLogic "+getPlatformScene()->getName()+"."+getName()+"��"+prm_pActor_Opponent->getPlatformScene()->getName()+"."+prm_pActor_Opponent->getName());
	return false;
}
*/

void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareFinishLife();
}


MyShip::~MyShip() {
}
