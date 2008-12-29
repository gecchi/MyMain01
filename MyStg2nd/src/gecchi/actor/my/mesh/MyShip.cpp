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

	_iMvBtmVelo_MT = 1000;		//TURBO�ړ����̈ړ����x�̍Œᑬ�x
	_iMvVelo_BeginMT = _iMoveSpeed*5;	//TURBO�ړ��J�n���̈ړ����x�̏����x
	_iMvAcce_MT = -200;					//TURBO�ړ����̈ړ����x�̉����x

	_iMvAcce_EOD_MT = -500;			//TURBO���ɋt�����ɓ��͂���鎖�ɂ����Z�����i��������j���x

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
	_dwFrameXYTurboMove = 0;			//�^�[�{�o�߃t���[��
	_dwFrameZXTurboMove = 0;			//�^�[�{�o�߃t���[��

	_dwIntervalFinshTurbo = 60;

	_angFaceTurnRange = 30000;//�U��������e�A���O��
	_angRotVelo_FaceTurn = 2000;

	_needTurnFaceNeutralXY = true;
	_needTurnFaceNeutralZX = true;
	_needTurnFaceXYMove = false;
	_needTurnFaceZXMove = false;


	_dwFrameNomalMove = 0;			//�ʏ�ړ��o�߃t���[��
	_isMoveZX = false;
	_wayTurbo = WAY_NONE;
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
	MyLaserChip2* pChip;
	for (int i = 0; i < 30; i++) { //���[�U�[�X�g�b�N
		pChip = NEW MyLaserChip2("MYS_L"+GgafUtil::itos(i), "laserchip9");
		pChip->stopImmediately();
		_pMyLaserChipRotation->addSubLast(pChip);
	}

	for (int i = 0; i < EQ_MAX_OPTION; i++) {
		MyOption* pOption = NEW MyOption("MY_OPTION"+GgafUtil::itos(i), "ebi");
		pOption->_iMyNo = i;  //���Ք�
		pOption->stopAloneImmediately();
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
	_pGeoMover -> setAxisRotAngleVelocity(AXIS_Y,1000);
	_pGeoMover -> setAxisRotAngleVelocity(AXIS_Z,1300);


}

void MyShip::processBehavior() {

	static int stc;
	stc = VB::getPushedDownStickWith(VB_TURBO);
	if (stc != 0 && _dwFrameTurboMove > 2) {
//		_TRACE_("ZX�^�[�{�n��");
		beginTurboZX(stc);
		turnFaceNeutralXY();
	} else if (VB::isPushedDown(VB_TURBO) != 0 && _dwFrameTurboMove > 2) {
		stc = VB::getBeingPressedStick();
		if (stc != 0) {
//			_TRACE_("XY�^�[�{�n��");
			beginTurboXY(stc);
			turnFaceNeutralZX();
		} else {
//			_TRACE_("�����^�[�{PushDown��������");
			doNotingMoveInput();
			turnFaceNeutralXY();
			turnFaceNeutralZX();
		}
	} else if (VB::isBeingPressed(VB_TURBO)) {
		stc = VB::getBeingPressedStick();
		if (stc != 0) {
			if (_wayTurbo == WAY_NONE) {
//				_TRACE_("ZX�ړ�");
				moveZX(stc);
				turnFaceZXMove(stc);
				turnFaceNeutralXY();
			} else {
//				_TRACE_("�^�[�{��ZX����");
				controlTurboZX(stc);
				turnFaceNeutralXY();
			}
		} else {
//			_TRACE_("�����^�[�{�������ςȂ����Ă邾��");
			doNotingMoveInput();
			turnFaceNeutralXY();
			turnFaceNeutralZX();

		}
	} else {
		stc = VB::getBeingPressedStick();
		if (stc != 0) {
			if (_wayTurbo == WAY_NONE) {
//				_TRACE_("XY�ړ�����");
				moveXY(stc);
				turnFaceXYMove(stc);
				turnFaceNeutralZX();
			} else {
//				_TRACE_("�^�[�{��XY����");
				controlTurboXY(stc);
				turnFaceNeutralZX();
			}
		} else {
			//�ȁ`��ɂ����ĂȂ�
			doNotingMoveInput();
			turnFaceNeutralXY();
			turnFaceNeutralZX();
		}
	}

	_dwFrameTurboMove++;
	_dwFrameXYTurboMove++;
	_dwFrameZXTurboMove++;
	if (_dwFrameTurboMove > _dwIntervalFinshTurbo) {
		_wayTurbo = WAY_NONE;
		_pGeoMover -> setMoveVelocityRenge(0, 10000000);
		_pGeoMover -> setMoveVelocity(0);
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
		MyLaserChip2* pLaser = (MyLaserChip2*)_pMyLaserChipRotation->obtain();
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


void MyShip::processJudgement() {
	//TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}


void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
	declareFinishLife();
}


void MyShip::beginTurboXY(int prm_VB) {
	_dwFrameTurboMove = 0;
	_dwFrameXYTurboMove = 0;
	_pGeoMover -> setMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
	_pGeoMover -> setMoveVelocity(_iMvVelo_BeginMT);
	_pGeoMover -> setMoveAcceleration(_iMvAcce_MT);

	switch(prm_VB) {

	case VB_UP_STC:
		_wayTurbo = WAY_UP;
		_pGeoMover -> setMoveAngleRzRy(ANGLE90, 0);
		break;

	case VB_UP_RIGHT_STC:
		_wayTurbo = WAY_UP_FRONT;
		_pGeoMover -> setMoveAngleRzRy(ANGLE45, 0);
		break;

	case VB_UP_LEFT_STC:
		_wayTurbo = WAY_UP_BEHIND;
		_pGeoMover -> setMoveAngleRzRy(ANGLE135, 0);
		break;

	case VB_LEFT_STC:
		_wayTurbo = WAY_BEHIND;
		_pGeoMover -> setMoveAngleRzRy(ANGLE180, 0);
		break;

	case VB_RIGHT_STC:
		_wayTurbo = WAY_FRONT;
		_pGeoMover -> setMoveAngleRzRy(ANGLE0, 0);
		break;

	case VB_DOWN_STC:
		_wayTurbo = WAY_DOWN;
		_pGeoMover -> setMoveAngleRzRy(ANGLE270, 0);
		break;

	case VB_DOWN_RIGHT_STC:
		_wayTurbo = WAY_DOWN_FRONT;
		_pGeoMover -> setMoveAngleRzRy(ANGLE315, 0);
		break;

	case VB_DOWN_LEFT_STC:
		_wayTurbo = WAY_DOWN_BEHIND;
		_pGeoMover -> setMoveAngleRzRy(ANGLE225, 0);
		break;

	default:

		break;
	}

}

void MyShip::beginTurboZX(int prm_VB) {
	_dwFrameTurboMove = 0;
	_dwFrameZXTurboMove = 0;

	_pGeoMover -> setMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
	_pGeoMover -> setMoveVelocity(_iMvVelo_BeginMT);
	_pGeoMover -> setMoveAcceleration(_iMvAcce_MT);

	switch(prm_VB) {

	case VB_UP_STC: //��
		_wayTurbo = WAY_ZLEFT;
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE270);
		break;

	case VB_UP_RIGHT_STC:
		_wayTurbo = WAY_ZLEFT_FRONT;
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE315);
		break;

	case VB_UP_LEFT_STC:
		_wayTurbo = WAY_ZLEFT_BEHIND;
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE225);
		break;

	case VB_RIGHT_STC:
		_wayTurbo = WAY_FRONT;
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE0);
		break;

	case VB_LEFT_STC:
		_wayTurbo = WAY_BEHIND;
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE180);
		break;

	case VB_DOWN_STC:
		_wayTurbo = WAY_ZRIGHT;
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE90);
		break;

	case VB_DOWN_RIGHT_STC:
		_wayTurbo = WAY_ZRIGHT_FRONT;
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE45);
		break;

	case VB_DOWN_LEFT_STC:
		_wayTurbo = WAY_ZRIGHT_BEHIND;
		_pGeoMover -> setMoveAngleRzRy(0, ANGLE135);
		break;

	default:

		break;
	}

}

void MyShip::moveXY(int prm_VB) {
	switch(prm_VB) {

	case VB_UP_STC:
		_Y += _iMoveSpeed;
		break;

	case VB_UP_RIGHT_STC:
		_Y += _iMoveSpeed * NANAME;
		_X += _iMoveSpeed * NANAME;
		break;

	case VB_UP_LEFT_STC:
		_Y += _iMoveSpeed * NANAME;
		_X -= _iMoveSpeed * NANAME;
		break;

	case VB_LEFT_STC:
		_X -= _iMoveSpeed;
		break;

	case VB_RIGHT_STC:
		_X += _iMoveSpeed;
		break;

	case VB_DOWN_STC:
		_Y -= _iMoveSpeed;
		break;

	case VB_DOWN_RIGHT_STC:
		_Y -= _iMoveSpeed * NANAME;
		_X += _iMoveSpeed * NANAME;
		break;

	case VB_DOWN_LEFT_STC:
		_Y -= _iMoveSpeed * NANAME;
		_X -= _iMoveSpeed * NANAME;
		break;

	default:
		break;
	}
}

void MyShip::moveZX(int prm_VB) {
	switch(prm_VB) {

	case VB_UP_STC:
		_Z += _iMoveSpeed;
		break;

	case VB_UP_RIGHT_STC:
		_Z += _iMoveSpeed * NANAME;
		_X += _iMoveSpeed * NANAME;
		break;

	case VB_UP_LEFT_STC:
		_Z += _iMoveSpeed * NANAME;
		_X -= _iMoveSpeed * NANAME;
		break;

	case VB_LEFT_STC:
		_X -= _iMoveSpeed;
		break;

	case VB_RIGHT_STC:
		_X += _iMoveSpeed;
		break;

	case VB_DOWN_STC:
		_Z -= _iMoveSpeed;
		break;

	case VB_DOWN_RIGHT_STC:
		_Z -= _iMoveSpeed * NANAME;
		_X += _iMoveSpeed * NANAME;
		break;

	case VB_DOWN_LEFT_STC:
		_Z -= _iMoveSpeed * NANAME;
		_X -= _iMoveSpeed * NANAME;
		break;

	default:
		break;
	}
}

void MyShip::controlTurboXY(int prm_VB) {
	switch(prm_VB) {

	case VB_UP_STC:
		if (_wayTurbo == WAY_DOWN) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Y += _iMoveSpeed;
		}
		break;

	case VB_UP_RIGHT_STC:
		if (_wayTurbo == WAY_DOWN_BEHIND) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Y += _iMoveSpeed * NANAME;
			_X += _iMoveSpeed * NANAME;
		}
		break;

	case VB_UP_LEFT_STC:
		if (_wayTurbo == WAY_DOWN_FRONT) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Y += _iMoveSpeed * NANAME;
			_X -= _iMoveSpeed * NANAME;
		}
		break;

	case VB_LEFT_STC:
		if (_wayTurbo == WAY_FRONT) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_X -= _iMoveSpeed;
		}
		break;

	case VB_RIGHT_STC:
		if (_wayTurbo == WAY_BEHIND) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_X += _iMoveSpeed;
		}
		break;

	case VB_DOWN_STC:
		if (_wayTurbo == WAY_UP) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Y -= _iMoveSpeed;
		}
		break;

	case VB_DOWN_RIGHT_STC:
		if (_wayTurbo == WAY_UP_BEHIND) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Y -= _iMoveSpeed * NANAME;
			_X += _iMoveSpeed * NANAME;
		}
		break;

	case VB_DOWN_LEFT_STC:
		if (_wayTurbo == WAY_UP_FRONT) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Y -= _iMoveSpeed * NANAME;
			_X -= _iMoveSpeed * NANAME;
		}
		break;

	default:
		break;
	}
}

void MyShip::controlTurboZX(int prm_VB) {
	switch(prm_VB) {

	case VB_UP_STC:
		if (_wayTurbo == WAY_ZRIGHT) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Z += _iMoveSpeed;
		}
		break;

	case VB_UP_RIGHT_STC:
		if (_wayTurbo == WAY_ZRIGHT_BEHIND) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Z += _iMoveSpeed * NANAME;
			_X += _iMoveSpeed * NANAME;
		}
		break;

	case VB_UP_LEFT_STC:
		if (_wayTurbo == WAY_ZRIGHT_FRONT) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Z += _iMoveSpeed * NANAME;
			_X -= _iMoveSpeed * NANAME;
		}
		break;

	case VB_LEFT_STC:
		if (_wayTurbo == WAY_FRONT) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_X -= _iMoveSpeed;
		}
		break;

	case VB_RIGHT_STC:
		if (_wayTurbo == WAY_BEHIND) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_X += _iMoveSpeed;
		}
		break;

	case VB_DOWN_STC:
		if (_wayTurbo == WAY_ZLEFT) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Z -= _iMoveSpeed;
		}
		break;

	case VB_DOWN_RIGHT_STC:
		if (_wayTurbo == WAY_ZLEFT_BEHIND) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Z -= _iMoveSpeed * NANAME;
			_X += _iMoveSpeed * NANAME;
		}
		break;

	case VB_DOWN_LEFT_STC:
		if (_wayTurbo == WAY_ZLEFT_FRONT) {
			_pGeoMover -> setMoveVelocityRenge(-1*_iMoveSpeed, 10000000);
			_pGeoMover -> addMoveVelocity(_iMvAcce_EOD_MT);
		} else {
			_pGeoMover -> setMoveVelocityRenge(0, 10000000);
			_Z -= _iMoveSpeed * NANAME;
			_X -= _iMoveSpeed * NANAME;
		}
		break;

	default:
		break;
	}
}
void MyShip::turnFaceXYMove(int prm_VB) {

	if (_needTurnFaceXYMove) {
		switch(prm_VB) {

		case VB_UP_STC:
			break;

		case VB_UP_RIGHT_STC:
			break;

		case VB_UP_LEFT_STC:
			break;

		case VB_LEFT_STC:
			break;

		case VB_RIGHT_STC:
			break;

		case VB_DOWN_STC:
			break;

		case VB_DOWN_RIGHT_STC:
			break;

		case VB_DOWN_LEFT_STC:
			break;

		default:
			break;
		}

		_needTurnFaceXYMove = false;
		_needTurnFaceNeutralXY = true;
	}
}


void MyShip::turnFaceZXMove(int prm_VB) {
	if (_needTurnFaceZXMove) {
		switch(prm_VB) {

		case VB_UP_STC:
			break;

		case VB_UP_RIGHT_STC:
			break;

		case VB_UP_LEFT_STC:
			break;

		case VB_LEFT_STC:
			break;

		case VB_RIGHT_STC:
			break;

		case VB_DOWN_STC:
			break;

		case VB_DOWN_RIGHT_STC:
			break;

		case VB_DOWN_LEFT_STC:
			break;

		default:
			break;
		}
		_needTurnFaceZXMove = false;
		_needTurnFaceNeutralZX = true;
	}
}


void MyShip::turnFaceNeutralXY() {
	//���[���i�p�A��p�j�����ɖ߂�
	if (_needTurnFaceNeutralXY) {
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRZTopVelo_MNY, _angRZTopVelo_MNY);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_Z, sgn(_pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_Z, 0, TURN_CLOSE_TO))*_angRZAcce_MNY);
		_pGeoMover -> setTargetAxisRotAngle(AXIS_Z, 0, TURN_BOTH);
		_needTurnFaceNeutralXY = false;
		_needTurnFaceXYMove = true;
	}
}

void MyShip::turnFaceNeutralZX() {
	//���[�i����̌X���j�����ɖ߂�
	//TODO:
	//�s�b�`�i���E�̌X���j�����ɖ߂�
	if (_needTurnFaceNeutralZX) {
		_pGeoMover -> setAxisRotAngleVelocityRenge(AXIS_Z, -1*_angRXTopVelo_MNZ, _angRXTopVelo_MNZ);
		_pGeoMover -> setAxisRotAngleAcceleration(AXIS_X, sgn(_pGeoMover->getDistanceFromAxisRotAngleTo(AXIS_X, 0, TURN_CLOSE_TO))*_angRXAcce_MNZ);
		_pGeoMover -> setTargetAxisRotAngle(AXIS_X, 0, TURN_BOTH);
		_needTurnFaceNeutralZX = false;
		_needTurnFaceZXMove = true;
	}

}


void MyShip::doNotingMoveInput() {



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
	pOption->declarePlayAlone();


}



MyShip::~MyShip() {
	DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}


