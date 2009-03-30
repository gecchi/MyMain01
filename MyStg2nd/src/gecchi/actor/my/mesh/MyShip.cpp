#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define S_OPTION 0

//1/��2
#define NANAME 0.7

MyShip::MyShip(const char* prm_name) : DefaultMeshActor(prm_name, "X/ceres") {
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


    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;

    _angRXVelo_BeginMZ = 1000; //�����͎�O�֒ʏ�Z�ʏ�ړ��J�n����X����]�p���x�̏����x
    _angRXAcce_MZ = 500; //�����͎�O�֒ʏ�Z�ړ�����X����]�p���x�̏��p�����x
    _angRXTopVelo_MZ = 1000; //�����͎�O�֒ʏ�Z�ړ�����X����]�p���x�̏���p���x
    _angRXStop_MZ = 90000; //�����͎�O�֒ʏ�Z�ړ�����X����]�p�̖ڕW��~�p�x

    _iMvBtmVelo_MT = 0; //Turbo�ړ����̈ړ����x�̍Œᑬ�x
    _iMvVelo_BeginMT = _iMoveSpeed * 3; //Turbo�ړ��J�n���̈ړ����x�̏����x
    _iMvAcce_MT = -200; //Turbo�ړ����̈ړ����x�̉����x

    _iMvAcce_EOD_MT = -500; //Turbo���ɋt�����ɓ��͂���鎖�ɂ����Z�����i��������j���x

    _angRZVelo_BeginMYT = 13000; //�㖔�͉���Turbo�ړ��J�n����Z����]�p���x�̏����x
    _angRZAcce_MYT = -200; //�㖔�͉���Turbo�ړ�����Z����]�p���x�̊p�����x
    _angRZBtmVelo_MYT = 3000; //�㖔�͉���Turbo�ړ�����Z����]�p���x�̍Œᑬ�x

    _angRZTopVelo_MNY = 2000; //�㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ���Z����]�p���x�̏���p���x
    _angRZAcce_MNY = 100; //�㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ��鎞��Z����]�p�����x(��������)

    _dwFrameNextXYTurboOut = 0; //XY����^�[�{�I���t���[��
    _dwIntervalXYTurbo = 60; //XY�^�[�{�I���t���[���Ԋu


    _dwFrameTurboMove = 0; //�^�[�{�o�߃t���[��
    _dwFrameXYTurboMove = 0; //�^�[�{�o�߃t���[��

    _dwIntervalFinshTurbo = 60;

    _angFaceTurnRange = 30000;//�U��������e�A���O��
    _angRotVelo_FaceTurn = 2000;

    _dwFrameNomalMove = 0; //�ʏ�ړ��o�߃t���[��
    _wayTurbo = WAY_NONE;
    _dRate_TurboControl = 0.8; //�^�[�{���ړ�����ł��銄��
    _iTurboControl = 0;

    _pMyShots001Rotation = NEW RotationActor("RotShot001");
    addSubLast(_pMyShots001Rotation); //������
    MyShot001* pShot;
    for (int i = 0; i < 50; i++) { //���e�X�g�b�N
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateNow();
        _pMyShots001Rotation->addSubLast(pShot);
    }

    _pMyWaves001Rotation = NEW RotationActor("RotWave001");
    addSubLast(_pMyWaves001Rotation);//������
    MyWave001* pWave;
    for (int i = 0; i < 50; i++) { //���e�X�g�b�N
        pWave = NEW MyWave001("MY_Wave001");
        pWave->inactivateNow();
        _pMyWaves001Rotation->addSubLast(pWave);
    }

    _pMyLaserChipRotation = NEW MyLaserChipRotationActor("ROTLaser");
    addSubLast(_pMyLaserChipRotation);
//    _pMyLaserChipRotation = NEW RotationActor("RotLaser001");
//    addSubLast(_pMyLaserChipRotation);//������
//    MyLaserChip2* pChip;
//    for (int i = 0; i < 100; i++) { //���[�U�[�X�g�b�N
//        pChip = NEW MyLaserChip2("MYS_MyLaserChip2", "m/laserchip9");
//        pChip->inactivateNow();
//        _pMyLaserChipRotation->addSubLast(pChip);
//    }

    for (int i = 0; i < EQ_MAX_OPTION; i++) {
        MyOption* pOption = NEW MyOption("MY_OPTION");
        pOption->_iMyNo = i; //���Ք�
        pOption->inactivateAloneNow();
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

    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    _pGeoMover->setMoveVelocity(0);

    _pGeoMover->setRotAngleVelocityRenge(AXIS_X, -10000, 10000);
	//_pGeoMover->setRotAngleVelocity(AXIS_X,700);
    //_pGeoMover->setRotAngleVelocity(AXIS_Y,500);
    //_pGeoMover->setRotAngleVelocity(AXIS_Z,300);

    _pTestBoard = NEW DefaultBoardActor("BOARD", "B/hoge");
    _pTestBoard->setPatternNo(6);
    _pTestBoard->_x = 50;
    _pTestBoard->_y = 50;
    _pTestBoard->_z = +0.99;
    getLordActor()->accept(KIND_EFFECT, _pTestBoard);

    DefaultBoardActor* pBoard11 = NEW DefaultBoardActor("BOARD", "B/hoge");
    pBoard11->setPatternNo(6);
    pBoard11->_x = 0;
    pBoard11->_y = 0;
    pBoard11->_z = +0.99;
    getLordActor()->accept(KIND_EFFECT, pBoard11);

    DefaultBoardActor* pBoard12 = NEW DefaultBoardActor("BOARD", "B/hoge");
    pBoard12->setPatternNo(7);
    pBoard12->_x = 0;
    pBoard12->_y = 33;
    pBoard12->_z = +0.99;
    getLordActor()->accept(KIND_EFFECT, pBoard12);

    DefaultBoardActor* pBoard13 = NEW DefaultBoardActor("BOARD", "B/hoge");
    pBoard13->setPatternNo(8);
    pBoard13->_x = 0;
    pBoard13->_y = 66;
    pBoard13->_z = +0.99;
    getLordActor()->accept(KIND_EFFECT, pBoard13);

    DefaultBoardActor* pBoard21 = NEW DefaultBoardActor("BOARD", "B/hoge");
    pBoard21->setPatternNo(9);
    pBoard21->_x = 33;
    pBoard21->_y = 0;
    pBoard21->_z = +0.99;
    getLordActor()->accept(KIND_EFFECT, pBoard21);

    DefaultBoardActor* pBoard22 = NEW DefaultBoardActor("BOARD", "B/hoge");
    pBoard22->setPatternNo(10);
    pBoard22->_x = 33;
    pBoard22->_y = 33;
    pBoard22->_z = +0.99;
    getLordActor()->accept(KIND_EFFECT, pBoard22);

    DefaultBoardActor* pBoard23 = NEW DefaultBoardActor("BOARD", "B/hoge");
    pBoard23->setPatternNo(11);
    pBoard23->_x = 33;
    pBoard23->_y = 66;
    pBoard23->_z = +0.99;
    getLordActor()->accept(KIND_EFFECT, pBoard23);

    DefaultBoardActor* pBoard31 = NEW DefaultBoardActor("BOARD", "B/hoge");
    pBoard31->setPatternNo(12);
    pBoard31->_x = 66;
    pBoard31->_y = 0;
    pBoard31->_z = +0.99;
    getLordActor()->accept(KIND_EFFECT, pBoard31);

    DefaultBoardActor* pBoard32 = NEW DefaultBoardActor("BOARD", "B/hoge");
    pBoard32->setPatternNo(13);
    pBoard32->_x = 66;
    pBoard32->_y = 33;
    pBoard32->_z = +0.99;
    getLordActor()->accept(KIND_EFFECT, pBoard32);

    DefaultBoardActor* pBoard33 = NEW DefaultBoardActor("BOARD", "B/hoge");
    pBoard33->setPatternNo(14);
    pBoard33->_x = 66;
    pBoard33->_y = 66;
    pBoard33->_z = +0.99;
    getLordActor()->accept(KIND_EFFECT, pBoard33);

}

void MyShip::processBehavior() {
    _pTestBoard->_x = _pTestBoard->_x + 1.0;
    _pTestBoard->_y = _pTestBoard->_y + 1.0;

    static int stc;

    stc = VB::getBeingPressedStick();
    if (stc != 0) {
        if (VB::isPushedDown(stc)) { //�����V���O���v�b�V��
            if (MyShip::isDoublePushedDown(stc)) { //�����_�u���v�b�V��
                if (VB::isBeingPressed(VB_ZMOVE)) {
                    turnFaceNeutralXY();
                    turnFaceXZMove(stc);
                    beginTurboXZ(stc);
                } else {
                    turnFaceNeutralXZ();
                    turnFaceXYMove(stc);
                    beginTurboXY(stc);
                }
            } else {
                //�����_�u���v�b�V���łȂ��������V���O���v�b�V��
                if (VB::isBeingPressed(VB_ZMOVE)) {
                    turnFaceNeutralXY();
                    turnFaceXZMove(stc);
                    moveXZ(stc);
                } else {
                    turnFaceNeutralXZ();
                    turnFaceXYMove(stc);
                    moveXY(stc);
                }
            }

        } else {

            //������������
            if (VB::isBeingPressed(VB_ZMOVE)) {
                turnFaceXZMove(stc);
                turnFaceXYMove(stc);
                moveXZ(stc);

            } else {
                turnFaceNeutralXZ();
                turnFaceXYMove(stc);
                moveXY(stc);

            }
        }
    } else {
        if (VB::isBeingPressed(VB_ZMOVE)) {
            //�j���[�g�����^�[�{
            doNotingMoveInput();
            turnFaceNeutralXY();
            turnFaceNeutralXZ();
        } else {
            doNotingMoveInput();
            turnFaceNeutralXY();
            turnFaceNeutralXZ();
        }
    }


    ////////////////////////////////////////////////////

    //�V���b�g�֘A����
    //MyShip::transactShot(this);
    if (VB::isPushedDown(VB_SHOT1)) {
        MyShot001* pShot = (MyShot001*)_pMyShots001Rotation->obtain();
        if (pShot != NULL) {
            pShot->activate();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
            if (pExplo001 != NULL) {
                pExplo001->setGeometry(this);
            }
        }
    }

    if (VB::isBeingPressed(VB_SHOT2)) {
        //RotationActor�̐�����A�����A�N�^�[�� play ���Ă��Ȃ���΁A�S�Ă̗v�f�� play ���Ă��Ȃ����ƂɂȂ�B
        MyLaserChip2* pLaser = (MyLaserChip2*)_pMyLaserChipRotation->obtain();
        if (pLaser != NULL) {
            pLaser->setRadicalActor(this);
            //pLaser->_dwFrame_switchedToActiveFlg = _dwFrame;
        }
    }

    //�V���b�g�{�^��
    if (VB::arePushedDownAtOnce(VB_SHOT1, VB_SHOT2)) {
        MyWave001* pWave = (MyWave001*)_pMyWaves001Rotation->obtain();
        if (pWave != NULL) {
            pWave->activate();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
            if (pExplo001 != NULL) {
                pExplo001->setGeometry(this);
            }
        }
    }

    if (VB::isBeingPressed(VB_SHOT3)) {
        setAlpha(getAlpha()-0.01);
        //equipOption();
    }

    if (VB::isBeingPressed(VB_POWERUP)) {
        _SX -= 300;
        _SY -= 300;
        _SZ -= 300;
    }
    if (VB::isBeingPressed(VB_GUARD)) {
        _SX += 300;
        _SY += 300;
        _SZ += 300;
    }

    //���W�ɔ��f
    _pGeoMover->behave();
}

void MyShip::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
    farewell();
}


void MyShip::beginTurboXZ(int prm_VB) {
    _dwFrameTurboMove = 0;
    _dwFrameXYTurboMove = 0;
    _pGeoMover->setMoveVelocityRenge(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    _pGeoMover->setMoveVelocity(_iMvVelo_BeginMT);
    _pGeoMover->setMoveAcceleration(_iMvAcce_MT);

    switch(prm_VB) {

        case VB_UP_STC: //��
            _wayTurbo = WAY_ZLEFT;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE270);
            break;

        case VB_UP_RIGHT_STC:
            _wayTurbo = WAY_ZLEFT_FRONT;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE315);
            break;

        case VB_UP_LEFT_STC:
            _wayTurbo = WAY_ZLEFT_BEHIND;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE225);
            break;

        case VB_RIGHT_STC:
            _wayTurbo = WAY_FRONT;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE0);
            break;

        case VB_LEFT_STC:
            _wayTurbo = WAY_BEHIND;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE180);
            break;

        case VB_DOWN_STC:
            _wayTurbo = WAY_ZRIGHT;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE90);
            break;

        case VB_DOWN_RIGHT_STC:
            _wayTurbo = WAY_ZRIGHT_FRONT;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE45);
            break;

        case VB_DOWN_LEFT_STC:
            _wayTurbo = WAY_ZRIGHT_BEHIND;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE135);
            break;
        default:
            break;
        }
}


void MyShip::beginTurboXY(int prm_VB) {
    _dwFrameTurboMove = 0;
    _dwFrameXYTurboMove = 0;
    _pGeoMover->setMoveVelocityRenge(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    _pGeoMover->setMoveVelocity(_iMvVelo_BeginMT);
    _pGeoMover->setMoveAcceleration(_iMvAcce_MT);

    switch (prm_VB) {
        case VB_UP_STC:
            _wayTurbo = WAY_UP;
            _pGeoMover->setRzRyMoveAngle(ANGLE90, 0);
            break;
        case VB_UP_RIGHT_STC:
            _wayTurbo = WAY_UP_FRONT;
            _pGeoMover->setRzRyMoveAngle(ANGLE45, 0);
            break;
        case VB_UP_LEFT_STC:
            _wayTurbo = WAY_UP_BEHIND;
            _pGeoMover->setRzRyMoveAngle(ANGLE135, 0);
            break;
        case VB_LEFT_STC:
            _wayTurbo = WAY_BEHIND;
            _pGeoMover->setRzRyMoveAngle(ANGLE180, 0);
            break;
        case VB_RIGHT_STC:
            _wayTurbo = WAY_FRONT;
            _pGeoMover->setRzRyMoveAngle(ANGLE0, 0);
            break;
        case VB_DOWN_STC:
            _wayTurbo = WAY_DOWN;
            _pGeoMover->setRzRyMoveAngle(ANGLE270, 0);
            break;
        case VB_DOWN_RIGHT_STC:
            _wayTurbo = WAY_DOWN_FRONT;
            _pGeoMover->setRzRyMoveAngle(ANGLE315, 0);
            break;
        case VB_DOWN_LEFT_STC:
            _wayTurbo = WAY_DOWN_BEHIND;
            _pGeoMover->setRzRyMoveAngle(ANGLE225, 0);
            break;
        default:
            break;
    }
}

void MyShip::moveXY(int prm_VB) {
    switch (prm_VB) {
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

void MyShip::moveXZ(int prm_VB) {
    angle distwk;
    switch (prm_VB) {
        case VB_UP_STC:
            _Z += _iMoveSpeed;
            distwk = _pGeoMover->getDistanceFromRotAngleTo(AXIS_X, _angRXStop_MZ, TURN_CLOCKWISE); //���v���̋���
            if (0 < distwk && distwk < ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            break;
        case VB_UP_RIGHT_STC:
            _Z += _iMoveSpeed * NANAME;
            _X += _iMoveSpeed * NANAME;

            distwk = _pGeoMover->getDistanceFromRotAngleTo(AXIS_X, _angRXStop_MZ, TURN_CLOCKWISE); //���v���̋���
            if (0 < distwk && distwk < ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            break;
        case VB_UP_LEFT_STC:
            _Z += _iMoveSpeed * NANAME;
            _X -= _iMoveSpeed * NANAME;

            distwk = _pGeoMover->getDistanceFromRotAngleTo(AXIS_X, _angRXStop_MZ, TURN_CLOCKWISE); //���v���̋���
            if (0 < distwk && distwk < ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);

            }
            break;
        case VB_LEFT_STC:
            _X -= _iMoveSpeed;
            break;
        case VB_RIGHT_STC:
            _X += _iMoveSpeed;
            break;
        case VB_DOWN_STC:
            _Z -= _iMoveSpeed;

            distwk = _pGeoMover->getDistanceFromRotAngleTo(AXIS_X, -1*_angRXStop_MZ, TURN_COUNTERCLOCKWISE); //�����v���̋���
            if (0 < distwk && distwk < ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            }
            break;
        case VB_DOWN_RIGHT_STC:
            _Z -= _iMoveSpeed * NANAME;
            _X += _iMoveSpeed * NANAME;
            distwk = _pGeoMover->getDistanceFromRotAngleTo(AXIS_X, -1*_angRXStop_MZ, TURN_COUNTERCLOCKWISE); //�����v���̋���
            if (0 < distwk && distwk < ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            }
            break;
        case VB_DOWN_LEFT_STC:
            _Z -= _iMoveSpeed * NANAME;
            _X -= _iMoveSpeed * NANAME;
            distwk = _pGeoMover->getDistanceFromRotAngleTo(AXIS_X, -1*_angRXStop_MZ, TURN_COUNTERCLOCKWISE); //�����v���̋���
            if (0 < distwk && distwk < ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            }
            break;
        default:
            break;
    }
}

void MyShip::controlTurboXY(int prm_VB) {
    switch (prm_VB) {

        case VB_UP_STC:
            if (_wayTurbo == WAY_DOWN) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y += _iMoveSpeed;
            }
            break;

        case VB_UP_RIGHT_STC:
            if (_wayTurbo == WAY_DOWN_BEHIND) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y += _iMoveSpeed * NANAME;
                _X += _iMoveSpeed * NANAME;
            }
            break;

        case VB_UP_LEFT_STC:
            if (_wayTurbo == WAY_DOWN_FRONT) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y += _iMoveSpeed * NANAME;
                _X -= _iMoveSpeed * NANAME;
            }
            break;

        case VB_LEFT_STC:
            if (_wayTurbo == WAY_FRONT) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _X -= _iMoveSpeed;
            }
            break;

        case VB_RIGHT_STC:
            if (_wayTurbo == WAY_BEHIND) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _X += _iMoveSpeed;
            }
            break;

        case VB_DOWN_STC:
            if (_wayTurbo == WAY_UP) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y -= _iMoveSpeed;
            }
            break;

        case VB_DOWN_RIGHT_STC:
            if (_wayTurbo == WAY_UP_BEHIND) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y -= _iMoveSpeed * NANAME;
                _X += _iMoveSpeed * NANAME;
            }
            break;

        case VB_DOWN_LEFT_STC:
            if (_wayTurbo == WAY_UP_FRONT) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y -= _iMoveSpeed * NANAME;
                _X -= _iMoveSpeed * NANAME;
            }
            break;

        default:
            break;
    }
}
void MyShip::turnFaceXYMove(int prm_VB) {

        switch (prm_VB) {

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
}

void MyShip::turnFaceXZMove(int prm_VB) {
}

void MyShip::turnFaceNeutralXY() {
}

void MyShip::turnFaceNeutralXZ() {

    angle distwk = _pGeoMover->getDistanceFromRotAngleTo(AXIS_X, 0, TURN_COUNTERCLOCKWISE); //�����v���̋���
    if (0 < distwk && distwk < ANGLE180) {
        _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
    } else if (ANGLE180 < distwk && distwk < ANGLE360) {
        _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
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
        pOption = (MyOption*)(pOption->getNext());
    }
    if (_state.eq_option == 0) {
        pOption->setRadicalActor(this);
    } else {
        pOption->setRadicalActor((GgafDx9UntransformedActor*)pOption->getPrev());
    }

    _state.eq_option++;
    pOption->activateAlone();

}

MyShip::~MyShip() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}


bool MyShip::isDoublePushedDown(int prm_VB) {
    //�ߋ��ɑk��Ȃ��猟��
    static VB::VBMap* pVBMap;
    DWORD dwFrameApply;
    DWORD dwFrameAgo = 1;
    pVBMap = VB::getPastVBMap(dwFrameAgo);
    //���O�͕K��������Ă��Ă͂͑ʖ�
    if (pVBMap->_state[prm_VB] == false) {

        dwFrameAgo++;
        //���̑O��5�t���[���ȓ��̂ǂ����ŉ����Ă��Ȃ���΂Ȃ�Ȃ�
        dwFrameApply = dwFrameAgo + 5;//���e�t���[��
        for ( ; dwFrameAgo < dwFrameApply; dwFrameAgo++) {
            pVBMap = VB::getPastVBMap(dwFrameAgo);
            if (pVBMap->_state[prm_VB]) {
                break;
            }
        }
        if (dwFrameAgo >= dwFrameApply) {
            //_TRACE_("�s���i1:dwFrameAgo="<<dwFrameAgo<<"/dwFrameApply="<<dwFrameApply);
            return false; //�s���i
        }
        //_TRACE_("�Ղꍇ�i2:dwFrameAgo="<<dwFrameAgo<<"/dwFrameApply="<<dwFrameApply);

        //����ɂ�������ȑO5�t���[���ȓ��̂ǂ����ŉ�����Ă��Ă͑ʖ�
        dwFrameApply = dwFrameAgo + 5;//���e�t���[��
        for ( ; dwFrameAgo < dwFrameApply; dwFrameAgo++) {
            pVBMap = VB::getPastVBMap(dwFrameAgo);
            if (pVBMap->_state[prm_VB] == false) {

                break;
            }
        }
        if (dwFrameAgo >= dwFrameApply) {
            //_TRACE_("�s���i2:dwFrameAgo="<<dwFrameAgo<<"/dwFrameApply="<<dwFrameApply);
            return false; //�s���i
        }
        //_TRACE_("���i!!!!:dwFrameAgo="<<dwFrameAgo<<"/dwFrameApply="<<dwFrameApply);
        return true;

    } else {
        //_TRACE_("�s���i3:dwFrameAgo="<<dwFrameAgo);
        return false;
    }

}

