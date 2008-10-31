#include "stdafx.h"

#define newState(H,X) do { H->e = new State*[X]; for (int i = 0; i < X; i++) {H->e[i] = new State(); } } while(0)
#define S_OPTION 0

//1/��2
#define NANAME 0.7






MyShip::MyShip(string prm_name, string prm_xname) : DefaultMeshActor(prm_name, prm_xname) {
	GameGlobal::_pMyShip = this;
	/** �ړ��X�s�[�h���x�� */
	_lv_MoveSpeed = 2;
	/** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
	_iMoveSpeed = 2000;

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



	_angRZVelo_BeginMY = 100;	//�㖔�͉��֒ʏ�ړ��J�n����Z����]�p���x�̏����x
	_angRZTopVelo_MY = 2000;	//�㖔�͉��ֈړ�����Z����]�p���x�̏���p���x
	_angRZAcce_MY = 200;		//�㖔�͉��֒ʏ�ړ�����Z����]�p���x�̊p�����x
	_angRZStop_MY = 30000;		//�㖔�͉��֒ʏ�Z�ړ�����Z����]�p�̒�~�p�x

	_iMvBtmVelo_MT = _iMoveSpeed*3;		//TURBO�ړ����̈ړ����x�̍Œᑬ�x
	_iMvVelo_BeginMT = _iMoveSpeed*6;	//TURBO�ړ��J�n���̈ړ����x�̏����x
	_iMvAcce_MT = -300;					//TURBO�ړ����̈ړ����x�̉����x

	_angRZVelo_BeginMYT = 5000;		//�㖔�͉���TURBO�ړ��J�n����Z����]�p���x�̏����x
	_angRZAcce_MYT = -200;			//�㖔�͉���TURBO�ړ�����Z����]�p���x�̊p�����x
	_angRZBtmVelo_MYT = 3000;		//�㖔�͉���TURBO�ړ�����Z����]�p���x�̍Œᑬ�x

	_angRZTopVelo_MNY = 1000;		//�㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ���Z����]�p���x�̏���p���x
	_angRZAcce_MNY = 100;			//�㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ��鎞��Z����]�p�����x(��������)

	_angRXVelo_BeginMZT = 10000;	//�����͎�O��TURBO�ړ��J�n����X����]�p���x�̏����x
	_angRXAcce_MZT = -200;			//�����͎�O��TURBO�ړ�����X����]�p���x�̊p�����x
	_angRXBtmVelo_MZT = 4000;		//�����͎�O��TURBO�ړ�����X����]�p���x�̍Œᑬ�x

	_angRXTopVelo_MNZ = 1000; 		//�����͎�O�ȊO�̒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ���X����]�p���x�̏���p���x
	_angRXAcce_MNZ = 100;			//�����͎�O�ȊO�̒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ��鎞��X����]�p�����x(��������)

	_angRXTopVelo_MZ = 3000;		//�����͎�O�ֈړ�����X����]�p���x�̏���p���x
	_angRXAcce_MZ = 200;			//�����͎�O�֒ʏ�ړ�����X����]�p���x�̊p�����x
	_angRXStop_MZ = 80000;			//�����͎�O�֒ʏ�Z�ړ�����X����]�p�̒�~�p�x
	_angRXVelo_BeginMZ = 100;		//�����͎�O�֒ʏ�ړ��J�n����X����]�p���x�̏����x

	_dwFrameNextXYTurboOut = 0;	//XY����^�[�{�I���t���[��
	_dwIntervalXYTurbo = 60;	//XY�^�[�{�I���t���[���Ԋu

	_dwFrameNextZXTurboOut = 0;	//Z����^�[�{�I���t���[��
	_dwIntervalZXTurbo = 60;		//Z�^�[�{�I���t���[���Ԋu

	_dwFrameTurbo = 0;			//�^�[�{�o�߃t���[��
	_isMoveZX = false;
	_wayTurbo = NONE;
	_dRate_TurboControl = 0.8; //�^�[�{���ړ�����ł��銄��
	_iTurboControl = 0;
}

void MyShip::initialize() {
	_pChecker -> useHitArea(1);
	_pChecker -> setHitArea(0, -10000, -10000, 10000, 10000);
	_pMover -> setXYMoveVelocity(0);
	//_pMover -> setAxisRotAngleVelocityRenge(AXIS_Y, -300000, -300000);
	//_pMover -> setAxisRotAngleVelocity(AXIS_Y,2000);
	_RZ = ANGLE90;
	//setAlpha(0.2);
}

void MyShip::processBehavior() {
	_tmpX = _X;
	_tmpY = _Y;
	_tmpZ = _Z;
	_dwFrameTurbo++; // �^�[�{�o�߃t���[��

	//����O�ړ����߂�TURBO���ۂ�
	if (_dwFrameTurbo > 2 && VB::isBeingPressed(VB_TURBO)) {
		if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_UP_STC))  {               //���A�n��
			_wayTurbo = ZLEFT;
			beginTurboZX(VB_UP_STC);
		} else if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_DOWN_STC))  {      //��O�A�n��
			_wayTurbo = ZRIGHT;
			beginTurboZX(VB_DOWN_STC);
		} else if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_UP_LEFT_STC)) {    //���΂߉��A�n��
			_wayTurbo = ZLEFT_BEHIND;
			beginTurboZX(VB_UP_LEFT_STC);
		} else if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_UP_RIGHT_STC)) {   //�E�΂߉��A�n��
			_wayTurbo = ZLEFT_FRONT;
			beginTurboZX(VB_UP_RIGHT_STC);
		} else if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_DOWN_LEFT_STC)) {  //���΂ߎ�O�A�n��
			_wayTurbo = ZRIGHT_BEHIND;
			beginTurboZX(VB_DOWN_LEFT_STC);
		} else if (VB::areNotBeingPressedAfterPushedDownAtOnce(VB_TURBO, VB_DOWN_RIGHT_STC)) { //�E�΂ߎ�O�A�n��
			_wayTurbo = ZRIGHT_FRONT;
			beginTurboZX(VB_DOWN_RIGHT_STC);
		} else {
			//�㉺���E�ړ����߂�TURBO���ۂ�
			if (VB::isPushedDown(VB_TURBO)) {
				if (VB::isBeingPressed(VB_UP_STC)) {                 //��A�n��
					_wayTurbo = UP;
					beginTurboXY(VB_UP_STC);
				} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {    //�E��A�n��
					_wayTurbo = UP_FRONT;
					beginTurboXY(VB_UP_RIGHT_STC);
				} else if (VB::isBeingPressed(VB_RIGHT_STC)) {       //�E�A�n��
					_wayTurbo = FRONT;
					beginTurboXY(VB_RIGHT_STC);
				} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {  //�E���A�n��
					_wayTurbo = DOWN_FRONT;
					beginTurboXY(VB_DOWN_RIGHT_STC);
				} else if (VB::isBeingPressed(VB_DOWN_STC)) {        //���A�n��
					_wayTurbo = DOWN;
					beginTurboXY(VB_DOWN_STC);
				} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {   //�����A�n��
					_wayTurbo = DOWN_BEHIND;
					beginTurboXY(VB_DOWN_LEFT_STC);
				} else if (VB::isBeingPressed(VB_LEFT_STC)) {        //���A�n��
					_wayTurbo = BEHIND;
					beginTurboXY(VB_LEFT_STC);
				} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {     //����A�n��
					_wayTurbo = UP_BEHIND;
					beginTurboXY(VB_UP_LEFT_STC);
				} else {

				}
			}
		}
	}

	//�^�[�{�I������
	if (_dwFrameNextXYTurboOut == _dwFrame) {
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = true;
		_pMover -> setXYMoveVelocityRenge(0, 10000000);
		_wayTurbo = NONE;
	}
	if (_dwFrameNextZXTurboOut == _dwFrame) {
		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = true;
		_pMover -> setZMoveVelocityRenge(0, sgn(_pMover->_iVelocity_ZMove)*10000000);
		_wayTurbo = NONE;
	}

	if (_wayTurbo == FRONT ||
		_wayTurbo == BEHIND ||
		_wayTurbo == UP ||
		_wayTurbo == UP_FRONT ||
		_wayTurbo == UP_BEHIND ||
		_wayTurbo == DOWN ||
		_wayTurbo == DOWN_FRONT ||
		_wayTurbo == DOWN_BEHIND    )
	{
		//XY�^�[�{��
		_iTurboControl = _pMover->_iVelocity_XYMove*_dRate_TurboControl;
	} else if (_wayTurbo == ZLEFT ||
		_wayTurbo == ZLEFT_FRONT ||
		_wayTurbo == ZLEFT_BEHIND ||
		_wayTurbo == ZRIGHT ||
		_wayTurbo == ZRIGHT_FRONT ||
		_wayTurbo == ZRIGHT_BEHIND    )
	{
		//ZX�^�[�{��
		_iTurboControl = abs(_pMover->_iVelocity_ZMove*_dRate_TurboControl);
	} else {
		//NOT�^�[�{
		_iTurboControl = 0;
	}

	if (VB::isBeingPressed(VB_TURBO) && _isMoveZX) {
		//ZX�ʏ�ړ�
		if (VB::isBeingPressed(VB_UP_STC)) {
			if (VB::isPushedDown(VB_UP_STC)) {
				beginMoveZX(VB_UP_STC);
			}
			_Z += _iMoveSpeed + _iTurboControl;
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			if (VB::isPushedDown(VB_UP_RIGHT_STC)) {
				beginMoveZX(VB_UP_RIGHT_STC);
			}
			_X += NANAME * (_iMoveSpeed + _iTurboControl);
			_Z += NANAME * (_iMoveSpeed + _iTurboControl);
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			if (VB::isPushedDown(VB_RIGHT_STC)) {
				beginMoveZX(VB_RIGHT_STC);
			}
			_X += _iMoveSpeed;
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			if (VB::isPushedDown(VB_DOWN_RIGHT_STC)) {
				beginMoveZX(VB_DOWN_RIGHT_STC);
			}
			_X += NANAME * (_iMoveSpeed + _iTurboControl);
			_Z -= NANAME * (_iMoveSpeed + _iTurboControl);
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			if (VB::isPushedDown(VB_DOWN_STC)) {
				beginMoveZX(VB_DOWN_STC);
			}
			_Z -= _iMoveSpeed + _iTurboControl;
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			if (VB::isPushedDown(VB_DOWN_LEFT_STC)) {
				beginMoveZX(VB_DOWN_LEFT_STC);
			}
			_X -= NANAME * (_iMoveSpeed + _iTurboControl);
			_Z -= NANAME * (_iMoveSpeed + _iTurboControl);
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			if (VB::isPushedDown(VB_LEFT_STC)) {
				beginMoveZX(VB_LEFT_STC);
			}
			_X -= _iMoveSpeed + _iTurboControl;
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			if (VB::isPushedDown(VB_UP_LEFT_STC)) {
				beginMoveZX(VB_UP_LEFT_STC);
			}
			_X -= NANAME * (_iMoveSpeed + _iTurboControl);
			_Z += NANAME * (_iMoveSpeed + _iTurboControl);
		} else {

		}
	} else {
		_isMoveZX = false;
		//XY�ʏ�ړ�
		if (VB::isBeingPressed(VB_UP_STC)) {
			if (VB::isPushedDown(VB_UP_STC)) {
				beginMoveXY(VB_UP_STC);
			}

			_Y += _iMoveSpeed + _iTurboControl;
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			if (VB::isPushedDown(VB_UP_RIGHT_STC)) {
				beginMoveXY(VB_UP_RIGHT_STC);
			}
			_X += NANAME * (_iMoveSpeed + _iTurboControl);
			_Y += NANAME * (_iMoveSpeed + _iTurboControl);
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			if (VB::isPushedDown(VB_RIGHT_STC)) {
				beginMoveXY(VB_RIGHT_STC);
			}
			_X += _iMoveSpeed + _iTurboControl;
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			if (VB::isPushedDown(VB_DOWN_RIGHT_STC)) {
				beginMoveXY(VB_DOWN_RIGHT_STC);
			} else {
				_X += NANAME * (_iMoveSpeed + _iTurboControl);
				_Y -= NANAME * (_iMoveSpeed + _iTurboControl);
			}
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			if (VB::isPushedDown(VB_DOWN_STC)) {
				beginMoveXY(VB_DOWN_STC);
			}
			_Y -= _iMoveSpeed + _iTurboControl;
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			if (VB::isPushedDown(VB_DOWN_LEFT_STC)) {
				beginMoveXY(VB_DOWN_LEFT_STC);
			}
			_X -= NANAME * (_iMoveSpeed + _iTurboControl);
			_Y -= NANAME * (_iMoveSpeed + _iTurboControl);
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			if (VB::isPushedDown(VB_LEFT_STC)) {
				beginMoveXY(VB_LEFT_STC);
			}
			_X -= _iMoveSpeed + _iTurboControl;
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			if (VB::isPushedDown(VB_UP_LEFT_STC)) {
				beginMoveXY(VB_UP_LEFT_STC);
			}
			_X -= NANAME * (_iMoveSpeed + _iTurboControl);
			_Y += NANAME * (_iMoveSpeed + _iTurboControl);
		} else {

		}
	}


	//�V���b�g�{�^��
	if (VB::isPushedDown(VB_SHOT1)) {
		MyShot001* pShot = (MyShot001*)GameGlobal::_pSceneCommon->_pMyShots001Rotation->obtain();
		if (pShot) {
			pShot->declarePlay();

			EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
			if (pExplo001) {
				pExplo001->setGeometry(this);
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



	//���[���i�p�A��p�j�����ɖ߂��t���O����
	if (_wayTurbo != UP &&
		_wayTurbo != UP_FRONT &&
		_wayTurbo != UP_BEHIND &&
		_wayTurbo != DOWN &&
		_wayTurbo != DOWN_FRONT &&
		_wayTurbo != DOWN_BEHIND &&
		_pMover->_angAxisRot[AXIS_Z] != 0 &&
		!VB::isBeingPressed(VB_UP_STC) &&
		!VB::isBeingPressed(VB_UP_RIGHT_STC) &&
		!VB::isBeingPressed(VB_UP_LEFT_STC) &&
		!VB::isBeingPressed(VB_DOWN_STC) &&
		!VB::isBeingPressed(VB_DOWN_RIGHT_STC) &&
		!VB::isBeingPressed(VB_DOWN_LEFT_STC) )
	{
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MNY, _angRZTopVelo_MNY);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(_pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, 0, TURN_CLOSE_TO))*_angRZAcce_MNY);
		_pMover -> setTargetAxisRotAngle(AXIS_Z, 0, TURN_BOTH);
	}

	//�s�b�`�i���E�̌X���j�����ɖ߂��t���O����
	if (_wayTurbo != ZLEFT &&
		_wayTurbo != ZLEFT_FRONT &&
		_wayTurbo != ZLEFT_BEHIND &&
		_wayTurbo != ZRIGHT &&
		_wayTurbo != ZRIGHT_FRONT &&
		_wayTurbo != ZRIGHT_BEHIND &&
		_pMover->_angAxisRot[AXIS_X] != 0 &&
		!VB::isBeingPressed(VB_UP_STC) &&
		!VB::isBeingPressed(VB_UP_RIGHT_STC) &&
		!VB::isBeingPressed(VB_UP_LEFT_STC) &&
		!VB::isBeingPressed(VB_DOWN_STC) &&
		!VB::isBeingPressed(VB_DOWN_RIGHT_STC) &&
		!VB::isBeingPressed(VB_DOWN_LEFT_STC) )
	{
		int rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, 0, TURN_CLOSE_TO);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MNZ);
		_pMover -> setTargetAxisRotAngle(AXIS_X, 0, TURN_BOTH);
	}


	//���W�ɔ��f
	_pMover -> behave();
}

//��ʉ���O�ړ����ߏ���
void MyShip::beginTurboZX(int prm_VB) {
	switch(prm_VB) {

	case VB_UP_STC: //��
		_isMoveZX = true;
		_dwFrameNextZXTurboOut = _dwFrame + _dwIntervalZXTurbo; //�^�[�{����
		_dwFrameTurbo = 0; //���Z�b�g

		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pMover -> setZMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setZMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setZMoveAcceleration(_iMvAcce_MT);
		break;

	case VB_UP_RIGHT_STC:
		_isMoveZX = true;
		_dwFrameNextZXTurboOut = _dwFrame + _dwIntervalZXTurbo; //�^�[�{����
		_dwFrameTurbo = 0; //���Z�b�g

		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pMover -> setZMoveVelocityRenge(_iMvBtmVelo_MT*NANAME, 10000000);
		_pMover -> setZMoveVelocity(_iMvVelo_BeginMT*NANAME);
		_pMover -> setZMoveAcceleration(_iMvAcce_MT*NANAME);

		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT*NANAME, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT*NANAME);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT*NANAME);
		_pMover -> setXYMoveAngle(ANGLE0);
		break;

	case VB_UP_LEFT_STC:
		_isMoveZX = true;
		_dwFrameNextZXTurboOut = _dwFrame + _dwIntervalZXTurbo; //�^�[�{����
		_dwFrameTurbo = 0; //���Z�b�g

		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pMover -> setZMoveVelocityRenge(_iMvBtmVelo_MT*NANAME, 10000000);
		_pMover -> setZMoveVelocity(_iMvVelo_BeginMT*NANAME);
		_pMover -> setZMoveAcceleration(_iMvAcce_MT*NANAME);

		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT*NANAME, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT*NANAME);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT*NANAME);
		_pMover -> setXYMoveAngle(ANGLE180);
		break;

	case VB_RIGHT_STC:
		beginTurboXY(VB_RIGHT_STC);
		break;

	case VB_LEFT_STC:
		beginTurboXY(VB_LEFT_STC);
		break;

	case VB_DOWN_STC:
		_isMoveZX = true;
		_dwFrameNextZXTurboOut = _dwFrame + _dwIntervalZXTurbo; //�^�[�{����
		_dwFrameTurbo = 0; //���Z�b�g

		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -3000000, -1*_angRXBtmVelo_MZT);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZT);

		_pMover -> setZMoveVelocityRenge(-1*_iMvBtmVelo_MT, -1*10000000);
		_pMover -> setZMoveVelocity(-1*_iMvVelo_BeginMT);
		_pMover -> setZMoveAcceleration(-1*_iMvAcce_MT);
		break;

	case VB_DOWN_RIGHT_STC:
		_isMoveZX = true;
		_dwFrameNextZXTurboOut = _dwFrame + _dwIntervalZXTurbo; //�^�[�{����
		_dwFrameTurbo = 0; //���Z�b�g

		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pMover -> setZMoveVelocityRenge(-1*_iMvBtmVelo_MT*NANAME, -10000000);
		_pMover -> setZMoveVelocity(-1*_iMvVelo_BeginMT*NANAME);
		_pMover -> setZMoveAcceleration(-1*_iMvAcce_MT*NANAME);

		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT*NANAME, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT*NANAME);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT*NANAME);
		_pMover -> setXYMoveAngle(ANGLE0);
		break;

	case VB_DOWN_LEFT_STC:
		_isMoveZX = true;
		_dwFrameNextZXTurboOut = _dwFrame + _dwIntervalZXTurbo; //�^�[�{����
		_dwFrameTurbo = 0; //���Z�b�g

		_pMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pMover -> setZMoveVelocityRenge(-1*_iMvBtmVelo_MT*NANAME, -10000000);
		_pMover -> setZMoveVelocity(-1*_iMvVelo_BeginMT*NANAME);
		_pMover -> setZMoveAcceleration(-1*_iMvAcce_MT*NANAME);

		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT*NANAME, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT*NANAME);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT*NANAME);
		_pMover -> setXYMoveAngle(ANGLE180);
		break;



	default:
		throw_GgafCriticalException("MyShip::beginTurboZX prm_VB="<<prm_VB<<"�͂��肦�܂���");
		break;
	}

}

//XY���W�^�[�{�n����
void MyShip::beginTurboXY(int prm_VB) {

	_dwFrameNextXYTurboOut = _dwFrame + _dwIntervalXYTurbo; //�^�[�{����
	_dwFrameTurbo = 0; //���Z�b�g

	switch(prm_VB) {

	case VB_UP_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(ANGLE90);
		break;

	case VB_UP_RIGHT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT*NANAME); //�΂߂Ȃ̂ŉ�]�͌�
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(ANGLE45);
		break;

	case VB_UP_LEFT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT*NANAME); //�΂߂Ȃ̂ŉ�]�͌�
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(ANGLE135);
		break;

	case VB_LEFT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(ANGLE180);
		break;

	case VB_RIGHT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(0);
		break;

	case VB_DOWN_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(-1*ANGLE90);
		break;

	case VB_DOWN_RIGHT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT*NANAME);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(-1*ANGLE45);
		break;

	case VB_DOWN_LEFT_STC:
		_pMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT*NANAME);
		_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pMover -> setXYMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
		_pMover -> setXYMoveVelocity(_iMvVelo_BeginMT);
		_pMover -> setXYMoveAcceleration(_iMvAcce_MT);
		_pMover -> setXYMoveAngle(-1*ANGLE135);
		break;

	default:
		throw_GgafCriticalException("MyShip::beginTurboXY prm_VB="<<prm_VB<<"�͂��肦�܂���");
		break;
	}

}


//��ʉ���O�ړ����ߏ���
void MyShip::beginMoveZX(int prm_VB) {
	int rd;
	switch(prm_VB) {

	case VB_UP_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) {  //���������Ȑ����Ő�����(��)����ɉ���Ă��ꍇ
			//���X�ɂ��₩��
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2); //�p�����͕��ŏ��X�ɂ��₩��
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //���������Ȑ����ŕ�����(�t)����ɉ���Ă��ꍇ                                          //�������ɉ���Ă�ꍇ
			//�������ċt����
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*ANGLE180, _angRXTopVelo_MZ);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2); //�������鐳�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, _angRXStop_MZ, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //��~���Ă���ꍇ
				_pMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //����
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MZ); //�߂��ق��Ɋp����
		}
		_pMover -> setTargetAxisRotAngle(AXIS_X, _angRXStop_MZ, TURN_BOTH, _angRXBtmVelo_MZT);
		break;

	case VB_UP_LEFT_STC:
	case VB_UP_RIGHT_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) {  //���������Ȑ����Ő�����(��)����ɉ���Ă��ꍇ
			//���X�ɂ��₩��
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2*NANAME); //�p�����͕��ŏ��X�ɂ��₩��
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //���������Ȑ����ŕ�����(�t)����ɉ���Ă��ꍇ                                          //�������ɉ���Ă�ꍇ
			//�������ċt����
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*ANGLE180, _angRXTopVelo_MZ);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXTopVelo_MZ*2*NANAME); //�������鐳�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, _angRXStop_MZ*NANAME, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //��~���Ă���ꍇ
				_pMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //����
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXTopVelo_MZ*NANAME); //�߂��ق��Ɋp����
		}
		_pMover -> setTargetAxisRotAngle(AXIS_X, _angRXStop_MZ*NANAME, TURN_BOTH, _angRXBtmVelo_MZT);
		break;

	case VB_RIGHT_STC:
		beginMoveXY(VB_RIGHT_STC);
		break;


	case VB_DOWN_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) { //���������Ȑ����Ő�����(�t)����ɉ���Ă��ꍇ
			//�������ċt����
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, ANGLE180, -1*_angRXTopVelo_MZ);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2); //�������镉�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //���������Ȑ����ŕ�����(��)����ɉ���Ă��ꍇ                                           //�������ɉ���Ă�ꍇ
			//���X�ɂ��₩��
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, -1*ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2); //�p�����͐��ŏ��X�ɂ��₩��
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, -1*_angRXStop_MZ, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //��~���Ă���ꍇ
				_pMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //����
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MZ); //�߂��ق��Ɋp����
		}
		_pMover -> setTargetAxisRotAngle(AXIS_X, -1*_angRXStop_MZ, TURN_BOTH, _angRXBtmVelo_MZT);
		break;

	case VB_DOWN_LEFT_STC:
	case VB_DOWN_RIGHT_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) {  //���������Ȑ����Ő�����(��)����ɉ���Ă��ꍇ
			//���X�ɂ��₩��
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2*NANAME); //�p�����͕��ŏ��X�ɂ��₩��
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //���������Ȑ����ŕ�����(�t)����ɉ���Ă��ꍇ                                          //�������ɉ���Ă�ꍇ
			//�������ċt����
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*ANGLE180, _angRXTopVelo_MZ);
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2*NANAME); //�������鐳�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_X, _angRXStop_MZ*NANAME, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //��~���Ă���ꍇ
				_pMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //����
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MZ*NANAME); //�߂��ق��Ɋp����
		}
		_pMover -> setTargetAxisRotAngle(AXIS_X, _angRZStop_MY*NANAME, TURN_BOTH, _angRXBtmVelo_MZT);
		break;

	case VB_LEFT_STC:
		beginMoveXY(VB_LEFT_STC);
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

	case VB_UP_STC: //�p�����i�����������蔭���j
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) {  //���������Ȑ����Ő�����(��)����ɉ���Ă��ꍇ
			//���X�ɂ��₩��
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, _angRZTopVelo_MY, ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2); //�p�����͕��ŏ��X�ɂ��₩��
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //���������Ȑ����ŕ�����(�t)����ɉ���Ă��ꍇ                                          //�������ɉ���Ă�ꍇ
			//�������ċt����
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*ANGLE180, _angRZTopVelo_MY);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2); //�������鐳�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, _angRZStop_MY, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //��~���Ă���ꍇ
				_pMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //����
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY); //�߂��ق��Ɋp����
		}
		_pMover -> setTargetAxisRotAngle(AXIS_Z, _angRZStop_MY, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_UP_LEFT_STC:
	case VB_UP_RIGHT_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) {  //���������Ȑ����Ő�����(��)����ɉ���Ă��ꍇ
			//���X�ɂ��₩��
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, _angRZTopVelo_MY, ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2*NANAME); //�p�����͕��ŏ��X�ɂ��₩��
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //���������Ȑ����ŕ�����(�t)����ɉ���Ă��ꍇ                                          //�������ɉ���Ă�ꍇ
			//�������ċt����
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*ANGLE180, _angRZTopVelo_MY);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2*NANAME); //�������鐳�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, _angRZStop_MY*NANAME, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //��~���Ă���ꍇ
				_pMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //����
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY*NANAME); //�߂��ق��Ɋp����
		}
		_pMover -> setTargetAxisRotAngle(AXIS_Z, _angRZStop_MY*NANAME, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_RIGHT_STC:
		break;

	case VB_DOWN_STC: //��p�����i�����������蔭���j
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) { //���������Ȑ����Ő�����(�t)����ɉ���Ă��ꍇ
			//�������ċt����
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, ANGLE180, -1*_angRZTopVelo_MY);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2); //�������镉�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //���������Ȑ����ŕ�����(��)����ɉ���Ă��ꍇ                                           //�������ɉ���Ă�ꍇ
			//���X�ɂ��₩��
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, -1*ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2); //�p�����͐��ŏ��X�ɂ��₩��
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, -1*_angRZStop_MY, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //��~���Ă���ꍇ
				_pMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //����
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY); //�߂��ق��Ɋp����
		}
		_pMover -> setTargetAxisRotAngle(AXIS_Z, -1*_angRZStop_MY, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_DOWN_LEFT_STC:
	case VB_DOWN_RIGHT_STC:
		if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) { //���������Ȑ����Ő�����(�t)����ɉ���Ă��ꍇ
			//�������ċt����
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, ANGLE180, -1*_angRZTopVelo_MY);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2*NANAME); //�������镉�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //���������Ȑ����ŕ�����(��)����ɉ���Ă��ꍇ                                           //�������ɉ���Ă�ꍇ
			//���X�ɂ��₩��
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, -1*ANGLE180);
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2*NANAME); //�p�����͐��ŏ��X�ɂ��₩��
		} else {
			_pMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pMover->getDistanceFromAxisRotAngleTo(AXIS_Z, -1*_angRZStop_MY*NANAME, TURN_CLOSE_TO);
			if (_pMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //��~���Ă���ꍇ
				_pMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //����
			}
			_pMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY*NANAME); //�߂��ق��Ɋp����
		}
		_pMover -> setTargetAxisRotAngle(AXIS_Z, -1*_angRZStop_MY*NANAME, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_LEFT_STC:
		break;

	default:
		throw_GgafCriticalException("MyShip::beginMoveXY prm_VB="<<prm_VB<<"�͂��肦�܂���");
		break;
	}

}



void MyShip::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}


void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareFinishLife();
}


MyShip::~MyShip() {
}
