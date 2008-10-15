#include "stdafx.h"

#define newState(H,X) do { H->e = new State*[X]; for (int i = 0; i < X; i++) {H->e[i] = new State(); } } while(0)
#define S_OPTION 0

//��2
#define ROOT2 1.41421356






MyShip::MyShip(string prm_name, string prm_xname) : DefaultMeshActor(prm_name, prm_xname) {
	GameGlobal::_pMyShip = this;
	/** �ړ��X�s�[�h���x�� */
	_lv_MoveSpeed = 1;
	/** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
	_iMoveSpeed = 1000;

	//CommonScene��new�̏ꍇ�ݒ�
	_iShotKind01 = 0;
	_iShotKind02 = 0;
	_iShotKind03 = 0;

	//�L���b�V�����[�h
	GgafDx9SeManager::get("laser001");

//	_angRXVelo_BeginMZ = 100;
//	_angRXAcce_MZ = 100;
//	_angRXTopVelo_MZ = 5000;
//	_angRXStop_MZ = 85000;
//
//	_iMvVelo_BeginMT = 5000;
//	_iMvAcce_MT = -100;
//	_iMvBtmVelo_MT = 1000;
//
//	_angRXVelo_BeginMZT = 10000;
//	_angRXAcce_MZT = -200;
//	_angRXBtmVelo_MZT = _angRXTopVelo_MZ;
//
//
//	_angRXTopVelo_MNZ = 2000;
//	_angRXAcce_MNZ = 100;

	_tmpX = _X;
	_tmpY = _Y;
	_tmpZ = _Z;

	_angRZVelo_BeginMY = 100;
	_angRZTopVelo_MY = 2000;
	_angRZAcce_MY = 300;
	_angRZStop_MY = 30000;

	_iMvBtmVelo_MT = 1000;
	_iMvVelo_BeginMT = 12000;
	_iMvAcce_MT = -500;

	_angRZVelo_BeginMYT = 30000;
	_angRZAcce_MYT = -1000;
	_angRZBtmVelo_MYT = 1000;

	_angRZTopVelo_MNY = 1000;
	_angRZAcce_MNY = 100;
	_iFrameNextTurboOut = 0;

}

void MyShip::initialize() {

	_iVB_turbo = 0;
	_pChecker -> _pHitArea2D = NEW HitArea2D(1, 0);
	_pChecker -> _pHitArea2D -> setRect(0, -10000, -10000, 10000, 10000);
	_pMover -> setXYMoveVelocity(0);
}

void MyShip::processBehavior() {

	_tmpX = _X;
	_tmpY = _Y;
	_tmpZ = _Z;

	//����O�ړ����߂�TURBO���ۂ�
	if (VB::arePushedDownAtOnce(VB_TURBO, VB_UP_STC))  {               //���A�n��
		_isMoveZX = true;
		beginTurboZX(VB_UP_STC);
	} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_DOWN_STC))  {      //��O�A�n��
		_isMoveZX = true;
		beginTurboZX(VB_DOWN_STC);
	} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_UP_LEFT_STC)) {    //���΂߉��A�n��
		_isMoveZX = true;
		beginTurboZX(VB_UP_LEFT_STC);
	} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_UP_RIGHT_STC)) {   //�E�΂߉��A�n��
		_isMoveZX = true;
		beginTurboZX(VB_UP_RIGHT_STC);
	} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_DOWN_LEFT_STC)) {  //���΂ߎ�O�A�n��
		_isMoveZX = true;
		beginTurboZX(VB_DOWN_LEFT_STC);
	} else if (VB::arePushedDownAtOnce(VB_TURBO, VB_DOWN_RIGHT_STC)) { //�E�΂ߎ�O�A�n��
		_isMoveZX = true;
		beginTurboZX(VB_DOWN_RIGHT_STC);
	} else {
		//�㉺���E�ړ����߂�TURBO���ۂ�
		if (VB::isPushedDown(VB_TURBO)) {
			if (VB::isBeingPressed(VB_UP_STC)) {                 //��A�n��
				beginTurboXY(VB_UP_STC);
			} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {    //�E��A�n��
				beginTurboXY(VB_UP_RIGHT_STC);
			} else if (VB::isBeingPressed(VB_RIGHT_STC)) {       //�E�A�n��
				beginTurboXY(VB_RIGHT_STC);
			} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {  //�E���A�n��
				beginTurboXY(VB_DOWN_RIGHT_STC);
			} else if (VB::isBeingPressed(VB_DOWN_STC)) {        //���A�n��
				beginTurboXY(VB_DOWN_STC);
			} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {   //�E���A�n��
				beginTurboXY(VB_DOWN_LEFT_STC);
			} else if (VB::isBeingPressed(VB_LEFT_STC)) {        //���A�n��
				beginTurboXY(VB_LEFT_STC);
			} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {     //����A�n��
				beginTurboXY(VB_UP_LEFT_STC);
			} else {

			}
		}
	}

	//�^�[�{�I������
	if (_isTurbo == true && _iFrameNextTurboOut == _dwFrame) {
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = true;
		_pMover -> setXYMoveVelocityRenge(0, 10000000);
		_isTurbo = false;
	}

	if (VB::isBeingPressed(VB_TURBO) && _isMoveZX) {
		//ZX�ʏ�ړ�
		if (VB::isBeingPressed(VB_UP_STC)) {
			if (VB::isPushedDown(VB_UP_STC)) {
				beginMoveZX(VB_UP_STC);
			}
			_Z += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			if (VB::isPushedDown(VB_UP_RIGHT_STC)) {
				beginMoveZX(VB_UP_RIGHT_STC);
			}
			_X += ROOT2*_iMoveSpeed;
			_Z += ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			if (VB::isPushedDown(VB_RIGHT_STC)) {
				beginMoveZX(VB_RIGHT_STC);
			}
			_X += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			if (VB::isPushedDown(VB_DOWN_RIGHT_STC)) {
				beginMoveZX(VB_DOWN_RIGHT_STC);
			}
			_X += ROOT2*_iMoveSpeed;
			_Z -= ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			if (VB::isPushedDown(VB_DOWN_STC)) {
				beginMoveZX(VB_DOWN_STC);
			}
			_Z -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			if (VB::isPushedDown(VB_DOWN_LEFT_STC)) {
				beginMoveZX(VB_DOWN_LEFT_STC);
			}
			_X -= ROOT2*_iMoveSpeed;
			_Z -= ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			if (VB::isPushedDown(VB_LEFT_STC)) {
				beginMoveZX(VB_LEFT_STC);
			}
			_X -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			if (VB::isPushedDown(VB_UP_LEFT_STC)) {
				beginMoveZX(VB_UP_LEFT_STC);
			}
			_X -= ROOT2*_iMoveSpeed;
			_Z += ROOT2*_iMoveSpeed;
		} else {

		}
	} else {
		//XY�ʏ�ړ�
		if (VB::isBeingPressed(VB_UP_STC)) {
			if (VB::isPushedDown(VB_UP_STC)) {
				beginMoveXY(VB_UP_STC);
			}
			_Y += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			if (VB::isPushedDown(VB_UP_RIGHT_STC)) {
				beginMoveXY(VB_UP_RIGHT_STC);
			}
			_X += ROOT2*_iMoveSpeed;
			_Y += ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			if (VB::isPushedDown(VB_RIGHT_STC)) {
				beginMoveXY(VB_RIGHT_STC);
			}
			_X += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			if (VB::isPushedDown(VB_DOWN_RIGHT_STC)) {
				beginMoveXY(VB_DOWN_RIGHT_STC);
			} else {
				_X += ROOT2*_iMoveSpeed;
				_Y -= ROOT2*_iMoveSpeed;
			}
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			if (VB::isPushedDown(VB_DOWN_STC)) {
				beginMoveXY(VB_DOWN_STC);
			}
			_Y -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			if (VB::isPushedDown(VB_DOWN_LEFT_STC)) {
				beginMoveXY(VB_DOWN_LEFT_STC);
			}
			_X -= ROOT2*_iMoveSpeed;
			_Y -= ROOT2*_iMoveSpeed;
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			if (VB::isPushedDown(VB_LEFT_STC)) {
				beginMoveXY(VB_LEFT_STC);
			}
			_X -= _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			if (VB::isPushedDown(VB_UP_LEFT_STC)) {
				beginMoveXY(VB_UP_LEFT_STC);
			}
			_X -= ROOT2*_iMoveSpeed;
			_Y += ROOT2*_iMoveSpeed;
		} else {

		}
	}










//	if (_isMoveZX && VB::isReleasedUp(VB_TURBO)) {
//		_isMoveZX = false;
//	}

	//�V���b�g�{�^��
	if (VB::isPushedDown(VB_SHOT1)) {
		MyShot001* pShot = (MyShot001*)GameGlobal::_pSceneCommon->_pMyShots001Rotation->obtain();
		if (pShot) {
			pShot->declarePlay();

			EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
			if (pExplo001) {
				pExplo001->declarePlay();
			}
		}
	}

	if (VB::isBeingPressed(VB_SHOT2)) {
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


	if (VB::isBeingPressed(VB_POWERUP)) {
		_SX -= 100;
		_SY -= 100;
		_SZ -= 100;
	}
	if (VB::isBeingPressed(VB_GUARD)) {
		_SX+= 100;
		_SY+= 100;
		_SZ+= 100;
	}



	//�p�A��p�����ɖ߂��t���O����
	if (!_isTurbo && !_isMoveZX && _pMover->_angAxisRot[AXIS_Z] != 0 &&
		!VB::isBeingPressed(VB_UP_STC) &&
		!VB::isBeingPressed(VB_UP_RIGHT_STC) &&
		!VB::isBeingPressed(VB_UP_LEFT_STC) &&
		!VB::isBeingPressed(VB_DOWN_STC) &&
		!VB::isBeingPressed(VB_DOWN_RIGHT_STC) &&
		!VB::isBeingPressed(VB_DOWN_LEFT_STC) )
	{
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MNY, _angRZTopVelo_MNY);
		int rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, 0, TURN_CLOSE_TO);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MNY);
		_pMover -> setTargetAxisRotAngle(AXIS_Z, 0);
	}

	//���W�ɔ��f
	_pMover -> behave();

}

//��ʉ���O�ړ����ߏ���
void MyShip::beginTurboZX(int prm_VB) {
	_isTurbo = true;
	switch(prm_VB) {

	case VB_UP_STC:
//		//?????
//		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
//		_pMover -> setZMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
//		_pMover -> setZMoveVelocity(_iMvVelo_BeginMT); //����
//		_pMover -> setZMoveAcceleration(_iMvAcce_MT);
//		//_pMover -> setXYMoveAngle(ANGLE90);
//
//		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXBtmVelo_MZT, 360000);
//		_pMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT);
//		_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);
		break;

	case VB_UP_RIGHT_STC:
		break;

	case VB_RIGHT_STC:
		beginTurboXY(VB_RIGHT_STC);
		break;

	case VB_DOWN_RIGHT_STC:
		break;

	case VB_DOWN_STC:
//		//?????
//		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
//		_pMover -> setZMoveVelocityRenge(-10000000, -1*_iMvBtmVelo_MT);
//		_pMover -> setZMoveVelocity(-1*_iMvVelo_BeginMT); //����
//		_pMover -> setZMoveAcceleration(-1*_iMvAcce_MT);
//		//_pMover -> setXYMoveAngle(ANGLE90);
//
//		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -360000, -1*_angRXBtmVelo_MZT);
//		_pMover -> setAxisRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT);
//		_pMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZT);
		break;

	case VB_DOWN_LEFT_STC:
		break;

	case VB_LEFT_STC:
		beginTurboXY(VB_LEFT_STC);
		break;

	case VB_UP_LEFT_STC:
		break;


	default:
		throw_GgafCriticalException("MyShip::beginTurboZX prm_VB="<<prm_VB<<"�͂��肦�܂���");
		break;
	}

}


void MyShip::beginTurboXY(int prm_VB) {
	_isTurbo = true;
	_iFrameNextTurboOut = _dwFrame + 20; //�^�[�{���Ԃ�20�t���[��

	switch(prm_VB) {

	case VB_UP_STC:

		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(ANGLE90);

		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3601000, _angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);

		break;

	case VB_UP_RIGHT_STC:
		break;

	case VB_RIGHT_STC:
		break;

	case VB_DOWN_RIGHT_STC:
		break;

	case VB_DOWN_STC:
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(-1*ANGLE90);

		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -360000, -1*_angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);

		break;

	case VB_DOWN_LEFT_STC:
		break;

	case VB_LEFT_STC:
		break;

	case VB_UP_LEFT_STC:
		break;

	default:
		throw_GgafCriticalException("MyShip::beginTurboXY prm_VB="<<prm_VB<<"�͂��肦�܂���");
		break;
	}

}


//��ʉ���O�ړ����ߏ���
void MyShip::beginMoveZX(int prm_VB) {
	_isTurbo = true;
	switch(prm_VB) {

	case VB_UP_STC:
	case VB_UP_LEFT_STC:
	case VB_UP_RIGHT_STC:
//		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //Z��]�p���x�͈����p������
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZ);
//		}
//		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, -1*_angRXTopVelo_MZ);
//		_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
//		_pMover -> setTargetAxisRotAngle(AXIS_X, _angRXStop_MZ);
		break;

	case VB_RIGHT_STC:
		beginTurboXY(VB_RIGHT_STC);
		break;


	case VB_DOWN_STC:
	case VB_DOWN_LEFT_STC:
	case VB_DOWN_RIGHT_STC:
//		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //Z��]�p���x�͈����p������
//			_pMover -> setAxisRotAngleVelocity(AXIS_X, -1.0*_angRXVelo_BeginMZ);
//		}
//		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, -1*_angRXTopVelo_MZ);
//		_pMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
//		_pMover -> setTargetAxisRotAngle(AXIS_X, -1*_angRXStop_MZ);
		break;

	case VB_LEFT_STC:
		beginTurboXY(VB_LEFT_STC);
		break;

	default:
		throw_GgafCriticalException("MyShip::beginMoveZX prm_VB="<<prm_VB<<"�͂��肦�܂���");
		break;
	}

}


//XY�O�ړ����ߏ���
void MyShip::beginMoveXY(int prm_VB) {
	int rd;
	switch(prm_VB) {

	case VB_UP_STC: //�p����
	case VB_UP_LEFT_STC:
	case VB_UP_RIGHT_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) { //���������Ȑ����Ő������ɉ���Ă��ꍇ
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, _angRZTopVelo_MY, ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY); //�t�����Ɋp����
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //���������Ȑ����ŕ������ɉ������ꍇ                                                   //�������ɉ���Ă�ꍇ
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY); //�������鐳�t�����Ɋp����
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, _angRZStop_MY, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //��~���Ă���ꍇ
				_pMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //����
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY); //�߂��ق��Ɋp����
		}
		_pMover -> setTargetAxisRotAngle(AXIS_Z, _angRZStop_MY);
		break;

	case VB_RIGHT_STC:
		break;

	case VB_DOWN_STC: //��p����
	case VB_DOWN_LEFT_STC:
	case VB_DOWN_RIGHT_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) { //���������Ȑ����Ő������ɉ�����ꍇ
			//�����Ȃ�
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY); //��������t�����Ɋp����
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //���������Ȑ����ŕ������ɉ������ꍇ                                                   //�������ɉ���Ă�ꍇ

			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, -1*ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY); //�t�����Ɋp����

		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, -1*_angRZStop_MY, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //��~���Ă���ꍇ
				_pMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //����
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY); //�߂��ق��Ɋp����
		}
		_pMover -> setTargetAxisRotAngle(AXIS_Z, -1*_angRZStop_MY);
		break;

	case VB_LEFT_STC:
		beginTurboXY(VB_LEFT_STC);
		break;

	default:
		throw_GgafCriticalException("MyShip::beginMoveXY prm_VB="<<prm_VB<<"�͂��肦�܂���");
		break;
	}

}







//��ʉ��ֈړ��I��X����]����
void MyShip::onMoveZFinish() {
	//�ڕWAngle0
	_pMover -> setTargetAxisRotAngle(AXIS_X, 0);
	//�p�x0�ɋ߂��ق���T��
	int rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, _pMover->_angTarget_AxisRot[AXIS_X], TURN_CLOSE_TO);
	_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MNZ, -1*_angRXTopVelo_MNZ);
	_pMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MNZ);
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
