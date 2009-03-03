#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define S_OPTION 0

//1/��2
#define NANAME 0.7

MyShip::MyShip(const char* prm_name) : DefaultPrimitiveActor(prm_name, "X/cube22", "default") {
//MyShip::MyShip(const char* prm_name) : DefaultMeshActor(prm_name, "M/ebi2") {
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

    _angRZVelo_BeginMY = 100; //�㖔�͉��֒ʏ�ړ��J�n����Z����]�p���x�̏����x
    _angRZTopVelo_MY = 2000; //�㖔�͉��ֈړ�����Z����]�p���x�̏���p���x
    _angRZAcce_MY = 200; //�㖔�͉��֒ʏ�ړ�����Z����]�p���x�̊p�����x
    _angRZStop_MY = 30000; //�㖔�͉��֒ʏ�Z�ړ�����Z����]�p�̒�~�p�x

    _iMvBtmVelo_MT = 1000; //TURBO�ړ����̈ړ����x�̍Œᑬ�x
    _iMvVelo_BeginMT = _iMoveSpeed * 5; //TURBO�ړ��J�n���̈ړ����x�̏����x
    _iMvAcce_MT = -200; //TURBO�ړ����̈ړ����x�̉����x

    _iMvAcce_EOD_MT = -500; //TURBO���ɋt�����ɓ��͂���鎖�ɂ����Z�����i��������j���x

    _angRZVelo_BeginMYT = 13000; //�㖔�͉���TURBO�ړ��J�n����Z����]�p���x�̏����x
    _angRZAcce_MYT = -200; //�㖔�͉���TURBO�ړ�����Z����]�p���x�̊p�����x
    _angRZBtmVelo_MYT = 3000; //�㖔�͉���TURBO�ړ�����Z����]�p���x�̍Œᑬ�x

    _angRZTopVelo_MNY = 2000; //�㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ���Z����]�p���x�̏���p���x
    _angRZAcce_MNY = 100; //�㖔�͉��֒ʏ�ړ����A�����I��Angle0�ɖ߂낤�Ƃ��鎞��Z����]�p�����x(��������)

    _dwFrameNextXYTurboOut = 0; //XY����^�[�{�I���t���[��
    _dwIntervalXYTurbo = 60; //XY�^�[�{�I���t���[���Ԋu


    _dwFrameTurboMove = 0; //�^�[�{�o�߃t���[��
    _dwFrameXYTurboMove = 0; //�^�[�{�o�߃t���[��

    _dwIntervalFinshTurbo = 60;

    _angFaceTurnRange = 30000;//�U��������e�A���O��
    _angRotVelo_FaceTurn = 2000;

    _needTurnFaceNeutralXY = true;
    _needTurnFaceXYMove = false;

    _dwFrameNomalMove = 0; //�ʏ�ړ��o�߃t���[��
    _wayTurbo = WAY_NONE;
    _dRate_TurboControl = 0.8; //�^�[�{���ړ�����ł��銄��
    _iTurboControl = 0;

    _pMyShots001Rotation = NEW RotationActor("RotShot001");
    addSubLast(_pMyShots001Rotation); //������
    MyShot001* pShot;
    for (int i = 0; i < 50; i++) { //���e�X�g�b�N
        pShot = NEW MyShot001("MY_MyShot001", "S/moji2");
        pShot->inactImmediately();
        _pMyShots001Rotation->addSubLast(pShot);
    }

    _pMyWaves001Rotation = NEW RotationActor("RotWave001");
    addSubLast(_pMyWaves001Rotation);//������
    MyWave001* pWave;
    for (int i = 0; i < 50; i++) { //���e�X�g�b�N
        pWave = NEW MyWave001("MY_Wave001", "M/wave");
        pWave->inactImmediately();
        _pMyWaves001Rotation->addSubLast(pWave);
    }

    _pMyLaserChipRotation = NEW MyLaserChipRotationActor("ROTLaser");
    addSubLast(_pMyLaserChipRotation);
//    _pMyLaserChipRotation = NEW RotationActor("RotLaser001");
//    addSubLast(_pMyLaserChipRotation);//������
//    MyLaserChip2* pChip;
//    for (int i = 0; i < 100; i++) { //���[�U�[�X�g�b�N
//        pChip = NEW MyLaserChip2("MYS_MyLaserChip2", "m/laserchip9");
//        pChip->inactImmediately();
//        _pMyLaserChipRotation->addSubLast(pChip);
//    }

    for (int i = 0; i < EQ_MAX_OPTION; i++) {
        MyOption* pOption = NEW MyOption("MY_OPTION", "M/ebi");
        pOption->_iMyNo = i; //���Ք�
        pOption->inactImmediatelyAlone();
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

    //_pGeoMover->setRotAngleVelocityRenge(AXIS_Y, -300000, -300000);
	_pGeoMover->setRotAngleVelocity(AXIS_X,700);
    _pGeoMover->setRotAngleVelocity(AXIS_Y,1000);
    _pGeoMover->setRotAngleVelocity(AXIS_Z,1300);


}

void MyShip::processBehavior() {

    static int stc;
    if (VB::isPushedDown(VB_TURBO) != 0 && _dwFrameTurboMove > 2) {
        stc = VB::getBeingPressedStick();
        if (stc != 0) {
            //			_TRACE_("XY�^�[�{�n��");
            beginTurboXY(stc);
        } else {
            //			_TRACE_("�����^�[�{PushDown��������");
            doNotingMoveInput();
            turnFaceNeutralXY();
        }
    } else if (VB::isBeingPressed(VB_TURBO)) {
        //		_TRACE_("�����^�[�{�������ςȂ����Ă邾��");
        doNotingMoveInput();
        turnFaceNeutralXY();
    } else {
        stc = VB::getBeingPressedStick();
        if (stc != 0) {
            if (_wayTurbo == WAY_NONE) {
                //				_TRACE_("XY�ړ�����");
                moveXY(stc);
                turnFaceXYMove(stc);
            } else {
                //				_TRACE_("�^�[�{��XY����");
                controlTurboXY(stc);
            }
        } else {
            //�ȁ`��ɂ����ĂȂ�
            doNotingMoveInput();
            turnFaceNeutralXY();
        }
    }

    _dwFrameTurboMove++;
    _dwFrameXYTurboMove++;
    if (_dwFrameTurboMove > _dwIntervalFinshTurbo) {
        _wayTurbo = WAY_NONE;
        _pGeoMover->setMoveVelocityRenge(0, 10000000);
        _pGeoMover->setMoveVelocity(0);
    }

    ////////////////////////////////////////////////////

    //�V���b�g�֘A����
    //MyShip::transactShot(this);
    if (VB::isPushedDown(VB_SHOT1)) {
        MyShot001* pShot = (MyShot001*)_pMyShots001Rotation->obtain();
        if (pShot != NULL) {
            pShot->act();

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
            //pLaser->_dwFrame_switchedToActFlg = _dwFrame;
        }
    }

    //�V���b�g�{�^��
    if (VB::arePushedDownAtOnce(VB_SHOT1, VB_SHOT2)) {
        MyWave001* pWave = (MyWave001*)_pMyWaves001Rotation->obtain();
        if (pWave != NULL) {
            pWave->act();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
            if (pExplo001 != NULL) {
                pExplo001->setGeometry(this);
            }
        }
    }

    if (VB::isPushedDown(VB_SHOT3)) {
        equipOption();
    }

    if (VB::isBeingPressed(VB_POWERUP)) {
        _SX -= 1000;
        _SY -= 1000;
        _SZ -= 1000;
    }
    if (VB::isBeingPressed(VB_GUARD)) {
        _SX += 1000;
        _SY += 1000;
        _SZ += 1000;
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

void MyShip::beginTurboXY(int prm_VB) {
    _dwFrameTurboMove = 0;
    _dwFrameXYTurboMove = 0;
    _pGeoMover->setMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
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

    if (_needTurnFaceXYMove) {
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

        _needTurnFaceXYMove = false;
        _needTurnFaceNeutralXY = true;
    }
}

void MyShip::turnFaceNeutralXY() {
    //���[���i�p�A��p�j�����ɖ߂�
    if (_needTurnFaceNeutralXY) {
        _pGeoMover->setRotAngleVelocityRenge(AXIS_Z, -1 * _angRZTopVelo_MNY, _angRZTopVelo_MNY);
        _pGeoMover->setRotAngleAcceleration(AXIS_Z, sgn(_pGeoMover->getDistanceFromRotAngleTo(AXIS_Z, 0, TURN_CLOSE_TO)) * _angRZAcce_MNY);
        _pGeoMover->setAutoTargetRotAngle(AXIS_Z, 0, TURN_BOTH);
        _needTurnFaceNeutralXY = false;
        _needTurnFaceXYMove = true;
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
    pOption->actAlone();

}

MyShip::~MyShip() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}

