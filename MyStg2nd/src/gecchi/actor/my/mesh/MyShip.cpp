#include "stdafx.h"

#define newState(H,X) do { H->e = new State*[X]; for (int i = 0; i < X; i++) {H->e[i] = new State(); } } while(0)
#define S_OPTION 0

//1/��2
#define NANAME 0.7






MyShip::MyShip(string prm_name, string prm_model) : DefaultMeshActor(prm_name, prm_model) {
	_class_name = "MyShip";
	GameGlobal::_pMyShip = this;
	/** �ړ��X�s�[�h���x�� */
	_lv_MoveSpeed = 2;
	/** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
	_iMoveSpeed = 4000;

	//CommonScene��new�̏ꍇ�ݒ�
	_iShotKind01 = 0;
	_iShotKind02 = 0;
	_iShotKind03 = 0;

	//�L���b�V�����[�h
	//GgafDx9SeManager::get("laser001");

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

	_iMvBtmVelo_MT = -1*_iMoveSpeed;		//TURBO�ړ����̈ړ����x�̍Œᑬ�x
	_iMvVelo_BeginMT = _iMoveSpeed*3;	//TURBO�ړ��J�n���̈ړ����x�̏����x
	_iMvAcce_MT = -100;					//TURBO�ړ����̈ړ����x�̉����x

	_iMvAcce_EOD_MT = 100;			//TURBO���ɋt�����ɓ��͂���鎖�ɂ�茸�����鑬�x

	_angRZVelo_BeginMYT = 13000;	//�㖔�͉���TURBO�ړ��J�n����Z����]�p���x�̏����x
	_angRZAcce_MYT = -200;			//�㖔�͉���TURBO�ړ�����Z����]�p���x�̊p�����x
	_angRZBtmVelo_MYT = 3000;		//�㖔�͉���TURBO�ړ�����Z����]�p���x�̍Œᑬ�x

	_angRZTopVelo_MNY = 2000;		//�㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ���Z����]�p���x�̏���p���x
	_angRZAcce_MNY = 100;			//�㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ��鎞��Z����]�p�����x(��������)

	_angRXVelo_BeginMZT = 15000;	//�����͎�O��TURBO�ړ��J�n����X����]�p���x�̏����x
	_angRXAcce_MZT = -300;			//�����͎�O��TURBO�ړ�����X����]�p���x�̊p�����x
	_angRXBtmVelo_MZT = 5000;		//�����͎�O��TURBO�ړ�����X����]�p���x�̍Œᑬ�x

	_angRXTopVelo_MNZ = 2000; 		//�����͎�O�ȊO�̒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ���X����]�p���x�̏���p���x
	_angRXAcce_MNZ = 100;			//�����͎�O�ȊO�̒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ��鎞��X����]�p�����x(��������)

	_angRXTopVelo_MZ = 4000;		//�����͎�O�ֈړ�����X����]�p���x�̏���p���x
	_angRXAcce_MZ = 200;			//�����͎�O�֒ʏ�ړ�����X����]�p���x�̊p�����x
	_angRXStop_MZ = 80000;			//�����͎�O�֒ʏ�Z�ړ�����X����]�p�̒�~�p�x
	_angRXVelo_BeginMZ = 500;		//�����͎�O�֒ʏ�ړ��J�n����X����]�p���x�̏����x

	_dwFrameNextXYTurboOut = 0;	//XY����^�[�{�I���t���[��
	_dwIntervalXYTurbo = 60;	//XY�^�[�{�I���t���[���Ԋu

	_dwFrameNextZXTurboOut = 0;	//Z����^�[�{�I���t���[��
	_dwIntervalZXTurbo = 60;		//Z�^�[�{�I���t���[���Ԋu

	_dwFrameTurboMove = 0;			//�^�[�{�o�߃t���[��
	_dwFrameNomalMove = 0;			//�ʏ�ړ��o�߃t���[��
	_isMoveZX = false;
	_wayTurbo = NONE;
	_dRate_TurboControl = 0.8; //�^�[�{���ړ�����ł��銄��
	_iTurboControl = 0;

	_pMyShots001Rotation = NEW RotationActor("RotShot001");
	addSubLast(_pMyShots001Rotation); //������
	MyShot001* pShot;
	for (int i = 0; i < 50; i++) { //���e�X�g�b�N
		pShot = NEW MyShot001("MY_S"+GgafUtil::itos(i), "moji2");
		pShot->stopImmediately();
		_pMyShots001Rotation->addSubLast(pShot);
	}

	_pMyWaves001Rotation = NEW RotationActor("RotWave001");
	addSubLast(_pMyWaves001Rotation);//������
	MyWave001* pWave;
	for (int i = 0; i < 50; i++) { //���e�X�g�b�N
		pWave = NEW MyWave001("MY_W"+GgafUtil::itos(i), "wave");
		pWave->stopImmediately();
		_pMyWaves001Rotation->addSubLast(pWave);
	}


	_pMyLaserChipRotation = NEW RotationActor("RotLaser001");
	addSubLast(_pMyLaserChipRotation);//������
	MyLaserChip* pChip;
	for (int i = 0; i < 30; i++) { //���[�U�[�X�g�b�N
		pChip = NEW MyLaserChip("MY_L"+GgafUtil::itos(i), "laserchip9");
		pChip->stopImmediately();
		_pMyLaserChipRotation->addSubLast(pChip);
	}

	for (int i = 0; i < EQ_MAX_OPTION; i++) {
		MyOption* pOption = NEW MyOption("MY_OPTION"+GgafUtil::itos(i), "ebi");
		pOption->_iMyNo = i;  //���Ք�
		pOption->stopImmediately();
		addSubLast(pOption);
	}


	//�g���[�X�p����
	_pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
	for (DWORD i = 0; i < 200; i++) {
		_pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
	}

}

void MyShip::initialize() {
	getLordActor()->accept(KIND_MY_SHOT_GU, _pMyShots001Rotation->tear());
	getLordActor()->accept(KIND_MY_SHOT_GU, _pMyWaves001Rotation->tear());
	getLordActor()->accept(KIND_MY_SHOT_GU, _pMyLaserChipRotation->tear());

	_pChecker -> useHitAreaBoxNum(1);
	_pChecker -> setHitAreaBox(0, -10000, -10000, 10000, 10000);
	_pGeoMover -> setMoveVelocity(0);
	//_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Y, -300000, -300000);
	//_pGeoMover -> setAxisRotAngleVelocity(AXIS_Y,1000);


}

void MyShip::processBehavior() {

	_pGeoMover -> setMoveVelocity(_iMoveSpeed);
	if (VB::isBeingPressed(VB_TURBO)) {

		//ZX�ʏ�ړ�
		if (VB::isBeingPressed(VB_UP_STC)) {
			_pGeoMover -> setMoveAngleRy(ANGLE270);
		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
			_pGeoMover -> setMoveAngleRy(ANGLE315);
		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
			_pGeoMover -> setMoveAngleRy(0);
		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
			_pGeoMover -> setMoveAngleRy(ANGLE45);
		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
			_pGeoMover -> setMoveAngleRy(ANGLE90);
		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
			_pGeoMover -> setMoveAngleRy(ANGLE135);
		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
			_pGeoMover -> setMoveAngleRy(ANGLE180);
		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
			_pGeoMover -> setMoveAngleRy(ANGLE225);
		} else {
		}
	} else {
//		//XY�ʏ�ړ�
//		if (VB::isBeingPressed(VB_UP_STC)) {
//			_pGeoMover -> setMoveAngleRz(ANGLE90);
//		} else if (VB::isBeingPressed(VB_UP_RIGHT_STC)) {
//			_pGeoMover -> setMoveAngleRz(ANGLE45);
//		} else if (VB::isBeingPressed(VB_RIGHT_STC)) {
//			_pGeoMover -> setMoveAngleRz(0);
//		} else if (VB::isBeingPressed(VB_DOWN_RIGHT_STC)) {
//			_pGeoMover -> setMoveAngleRz(ANGLE315);
//		} else if (VB::isBeingPressed(VB_DOWN_STC)) {
//			_pGeoMover -> setMoveAngleRz(ANGLE270);
//		} else if (VB::isBeingPressed(VB_DOWN_LEFT_STC)) {
//			_pGeoMover -> setMoveAngleRz(ANGLE225);
//		} else if (VB::isBeingPressed(VB_LEFT_STC)) {
//			_pGeoMover -> setMoveAngleRz(ANGLE180);
//		} else if (VB::isBeingPressed(VB_UP_LEFT_STC)) {
//			_pGeoMover -> setMoveAngleRz(ANGLE135);
//		} else {
//		}
	}


////////////////////////////////////////////////////

	//�V���b�g�֘A����
	//MyShip::transactShot(this);
	if (VB::isPushedDown(VB_SHOT1)) {
		MyShot001* pShot = (MyShot001*)_pMyShots001Rotation->obtain();
		if (pShot != NULL) {
			pShot->declarePlay();

			EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
			if (pExplo001 != NULL) {
				pExplo001->setGeometry(this);
				pExplo001->declarePlay();
			}
		}
	}

	if (VB::isBeingPressed(VB_SHOT2)) {
		//RotationActor�̐�����A�����A�N�^�[�� play ���Ă��Ȃ���΁A�S�Ă̗v�f�� play ���Ă��Ȃ����ƂɂȂ�B
		MyLaserChip* pLaser = (MyLaserChip*)_pMyLaserChipRotation->obtain();
		if (pLaser != NULL) {
			pLaser->setRadicalActor(this);
			pLaser->_dwFrame_switchedToPlay = _dwFrame;
			pLaser->declarePlay();
		}
	}

	//�V���b�g�{�^��
	if (VB::arePushedDownAtOnce(VB_SHOT1, VB_SHOT2)) {
		MyWave001* pWave = (MyWave001*)_pMyWaves001Rotation->obtain();
		if (pWave != NULL) {
			pWave->declarePlay();

			EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
			if (pExplo001 != NULL) {
				pExplo001->setGeometry(this);
				pExplo001->declarePlay();
			}
		}
	}


	if (VB::isPushedDown(VB_SHOT3)) {
		equipOption();
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


	//���W�ɔ��f
	_pGeoMover -> behave();
}

//��ʉ���O�ړ����ߏ���
void MyShip::beginTurboZX(int prm_VB) {
	beginMoveZX(prm_VB);

	_isMoveZX = true;
	_dwFrameNextZXTurboOut = _dwFrame + _dwIntervalZXTurbo; //�^�[�{����
	_dwFrameTurboMove = 0; //���Z�b�g
	_pGeoMover -> setMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
	_pGeoMover -> setMoveVelocity(_iMvVelo_BeginMT);
	_pGeoMover -> setMoveAcceleration(_iMvAcce_MT);

	switch(prm_VB) {

	case VB_UP_STC: //��
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE270);

	break;

	case VB_UP_RIGHT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE315);
		break;

	case VB_UP_LEFT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE225);
		break;

	case VB_RIGHT_STC:
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE0);
		break;

	case VB_LEFT_STC:
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE180);
		break;

	case VB_DOWN_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -3000000, -1*_angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE90);
		break;

	case VB_DOWN_RIGHT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE45);
		break;

	case VB_DOWN_LEFT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_X] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, 3000000, _angRXBtmVelo_MZT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZT);

		_pGeoMover -> setMoveAngleRzRy(0, ANGLE135);
		break;



	default:
		throw_GgafCriticalException("MyShip::beginTurboZX prm_VB="<<prm_VB<<"�͂��肦�܂���");
		break;
	}

}

//XY���W�^�[�{�n����
void MyShip::beginTurboXY(int prm_VB) {
	beginMoveXY(prm_VB);

	_isMoveZX = false;
	_dwFrameNextXYTurboOut = _dwFrame + _dwIntervalXYTurbo; //�^�[�{����
	_dwFrameTurboMove = 0; //���Z�b�g


	_pGeoMover -> setMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
	_pGeoMover -> setMoveVelocity(_iMvVelo_BeginMT);
	_pGeoMover -> setMoveAcceleration(_iMvAcce_MT);

	switch(prm_VB) {

	case VB_UP_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(ANGLE90, 0);
		break;

	case VB_UP_RIGHT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT*NANAME); //�΂߂Ȃ̂ŉ�]�͌�
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(ANGLE45, 0);
		break;

	case VB_UP_LEFT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, 3000000, _angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, _angRZVelo_BeginMYT*NANAME); //�΂߂Ȃ̂ŉ�]�͌�
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(ANGLE135, 0);
		break;

	case VB_LEFT_STC:
		_pGeoMover -> setMoveAngleRzRy(ANGLE180, 0);
		break;

	case VB_RIGHT_STC:
		_pGeoMover -> setMoveAngleRzRy(ANGLE0, 0);
		break;

	case VB_DOWN_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(-1*ANGLE90, 0);
		break;

	case VB_DOWN_RIGHT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(-1*ANGLE45, 0);
		break;

	case VB_DOWN_LEFT_STC:
		_pGeoMover -> _auto_rot_angle_target_Flg[AXIS_Z] = false;
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -300000, -1*_angRZBtmVelo_MYT);
		_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, -1*_angRZVelo_BeginMYT*NANAME);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MYT);
		_pGeoMover -> setMoveAngleRzRy(-1*ANGLE135, 0);
		break;

	default:
		throw_GgafCriticalException("MyShip::beginTurboXY prm_VB="<<prm_VB<<"�͂��肦�܂���");
		break;
	}

}


//��ʉ���O�ړ����ߏ���
void MyShip::beginMoveZX(int prm_VB) {
	_dwFrameNomalMove = 0;
	int rd;
	switch(prm_VB) {

	case VB_UP_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) {  //���������Ȑ����Ő�����(��)����ɉ���Ă��ꍇ
			//���X�ɂ��₩��
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2); //�p�����͕��ŏ��X�ɂ��₩��
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //���������Ȑ����ŕ�����(�t)����ɉ���Ă��ꍇ                                          //�������ɉ���Ă�ꍇ
			//�������ċt����
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*ANGLE180, _angRXTopVelo_MZ);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2); //�������鐳�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_X, _angRXStop_MZ, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //��~���Ă���ꍇ
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //����
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MZ); //�߂��ق��Ɋp����
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_X, _angRXStop_MZ, TURN_BOTH, _angRXBtmVelo_MZT);
		break;

	case VB_UP_LEFT_STC:
	case VB_UP_RIGHT_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) {  //���������Ȑ����Ő�����(��)����ɉ���Ă��ꍇ
			//���X�ɂ��₩��
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2*NANAME); //�p�����͕��ŏ��X�ɂ��₩��
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //���������Ȑ����ŕ�����(�t)����ɉ���Ă��ꍇ                                          //�������ɉ���Ă�ꍇ
			//�������ċt����
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*ANGLE180, _angRXTopVelo_MZ);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXTopVelo_MZ*2*NANAME); //�������鐳�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_X, _angRXStop_MZ*NANAME, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //��~���Ă���ꍇ
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //����
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXTopVelo_MZ*NANAME); //�߂��ق��Ɋp����
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_X, _angRXStop_MZ*NANAME, TURN_BOTH, _angRXBtmVelo_MZT);
		break;

	case VB_RIGHT_STC:
		beginMoveXY(VB_RIGHT_STC);
		break;


	case VB_DOWN_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) { //���������Ȑ����Ő�����(�t)����ɉ���Ă��ꍇ
			//�������ċt����
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, ANGLE180, -1*_angRXTopVelo_MZ);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2); //�������镉�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //���������Ȑ����ŕ�����(��)����ɉ���Ă��ꍇ                                           //�������ɉ���Ă�ꍇ
			//���X�ɂ��₩��
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, -1*ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2); //�p�����͐��ŏ��X�ɂ��₩��
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_X, -1*_angRXStop_MZ, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //��~���Ă���ꍇ
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //����
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MZ); //�߂��ق��Ɋp����
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_X, -1*_angRXStop_MZ, TURN_BOTH, _angRXBtmVelo_MZT);
		break;

	case VB_DOWN_LEFT_STC:
	case VB_DOWN_RIGHT_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] > _angRXTopVelo_MZ) {  //���������Ȑ����Ő�����(��)����ɉ���Ă��ꍇ
			//���X�ɂ��₩��
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, _angRXTopVelo_MZ, ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2*NANAME); //�p�����͕��ŏ��X�ɂ��₩��
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] < -1*_angRXTopVelo_MZ) { //���������Ȑ����ŕ�����(�t)����ɉ���Ă��ꍇ                                          //�������ɉ���Ă�ꍇ
			//�������ċt����
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*ANGLE180, _angRXTopVelo_MZ);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2*NANAME); //�������鐳�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_X, -1*_angRXTopVelo_MZ, _angRXTopVelo_MZ);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_X, _angRXStop_MZ*NANAME, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_X] == 0) { //��~���Ă���ꍇ
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_X, sgn(rd)*_angRXVelo_BeginMZ); //����
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(rd)*_angRXAcce_MZ*NANAME); //�߂��ق��Ɋp����
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_X, _angRZStop_MY*NANAME, TURN_BOTH, _angRXBtmVelo_MZT);
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
	_dwFrameNomalMove = 0;

	int rd;
	switch(prm_VB) {

	case VB_UP_STC: //�p�����i�����������蔭���j
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) {  //���������Ȑ����Ő�����(��)����ɉ���Ă��ꍇ
			//���X�ɂ��₩��
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, _angRZTopVelo_MY, ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2); //�p�����͕��ŏ��X�ɂ��₩��
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //���������Ȑ����ŕ�����(�t)����ɉ���Ă��ꍇ                                          //�������ɉ���Ă�ꍇ
			//�������ċt����
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*ANGLE180, _angRZTopVelo_MY);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2); //�������鐳�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_Z, _angRZStop_MY, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //��~���Ă���ꍇ
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //����
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY); //�߂��ق��Ɋp����
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_Z, _angRZStop_MY, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_UP_LEFT_STC:
	case VB_UP_RIGHT_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) {  //���������Ȑ����Ő�����(��)����ɉ���Ă��ꍇ
			//���X�ɂ��₩��
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, _angRZTopVelo_MY, ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2*NANAME); //�p�����͕��ŏ��X�ɂ��₩��
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //���������Ȑ����ŕ�����(�t)����ɉ���Ă��ꍇ                                          //�������ɉ���Ă�ꍇ
			//�������ċt����
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*ANGLE180, _angRZTopVelo_MY);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2*NANAME); //�������鐳�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_Z, _angRZStop_MY*NANAME, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //��~���Ă���ꍇ
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //����
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY*NANAME); //�߂��ق��Ɋp����
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_Z, _angRZStop_MY*NANAME, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_RIGHT_STC:
		break;

	case VB_DOWN_STC: //��p�����i�����������蔭���j
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) { //���������Ȑ����Ő�����(�t)����ɉ���Ă��ꍇ
			//�������ċt����
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, ANGLE180, -1*_angRZTopVelo_MY);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2); //�������镉�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //���������Ȑ����ŕ�����(��)����ɉ���Ă��ꍇ                                           //�������ɉ���Ă�ꍇ
			//���X�ɂ��₩��
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, -1*ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2); //�p�����͐��ŏ��X�ɂ��₩��
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_Z, -1*_angRZStop_MY, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //��~���Ă���ꍇ
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //����
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY); //�߂��ق��Ɋp����
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_Z, -1*_angRZStop_MY, TURN_BOTH, _angRZBtmVelo_MYT);
		break;

	case VB_DOWN_LEFT_STC:
	case VB_DOWN_RIGHT_STC:
		if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] > _angRZTopVelo_MY) { //���������Ȑ����Ő�����(�t)����ɉ���Ă��ꍇ
			//�������ċt����
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, ANGLE180, -1*_angRZTopVelo_MY);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, -1*_angRZAcce_MY*2*NANAME); //�������镉�����Ɋp�����A�ʏ�̂Q�{�p�����ł���
		} else if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] < -1*_angRZTopVelo_MY) { //���������Ȑ����ŕ�����(��)����ɉ���Ă��ꍇ                                           //�������ɉ���Ă�ꍇ
			//���X�ɂ��₩��
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, -1*ANGLE180);
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, _angRZAcce_MY*2*NANAME); //�p�����͐��ŏ��X�ɂ��₩��
		} else {
			_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MY, _angRZTopVelo_MY);
			rd = _pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_Z, -1*_angRZStop_MY*NANAME, TURN_CLOSE_TO);
			if (_pGeoMover ->_angVelocity_AxisRotAngle[AXIS_Z] == 0) { //��~���Ă���ꍇ
				_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z, sgn(rd)*_angRZVelo_BeginMY); //����
			}
			_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(rd)*_angRZAcce_MY*NANAME); //�߂��ق��Ɋp����
		}
		_pGeoMover -> setTargetAxisRotAngle(AXIS_Z, -1*_angRZStop_MY*NANAME, TURN_BOTH, _angRZBtmVelo_MYT);
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


void MyShip::transactShot(GgafDx9UntransformedActor* prm_pActor) {


}


void MyShip::equipOption() {

	if (_state.eq_option >= EQ_MAX_OPTION) {
		return;
	}
	MyOption* pOption = (MyOption*)_pSubFirst;
	for (int i = 0; i < _state.eq_option; i++) {
		pOption = (MyOption*)(pOption -> getNext());
	}
	if (_state.eq_option == 0) {
		pOption->setRadicalActor(this);
	} else {
		pOption->setRadicalActor((GgafDx9UntransformedActor*)pOption->getPrev());
	}





	_state.eq_option++;
	pOption->declarePlay();

}



MyShip::~MyShip() {
	RELEASE_POSSIBLE_NULL(MyLaserChip::_pIDirect3DVertexBuffer9_MyLaserChip);
	DELETE_POSSIBLE_NULL(MyLaserChip::_pTetra_EFGH);
	DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}


