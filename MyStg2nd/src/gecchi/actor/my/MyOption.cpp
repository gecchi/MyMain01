#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionParent* prm_pMyOptionParent) : DefaultMorphMeshActor(prm_name, "4/Ceres") {
MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionParent* prm_pMyOptionParent) : DefaultMeshSetActor(prm_name, "Core4") {

_TRACE_("MyOption::MyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyOption";
    _pMyOptionParent = prm_pMyOptionParent;
    _no = prm_no;
    _angveloMove = 0;//����ړ��p���x�i�ǂݏo����p�j

    _angPosition = 0;     //�~���㏉���ʒu�p�x�i���͊p�j�i�㏑�������ݒ�j
    _radiusPosition = 150000;     //�������a�����i�㏑�������ݒ�j
    _veloMv = 5000;     //����ړ����x�i�㏑�������ݒ�j
    _angExpanse = 0;      //�I�v�V�����̍L����p�̉�]�p�i�㏑�������ݒ�j

    _angPosition_default = _angPosition;
    _radiusPosition_default = _radiusPosition;
    _angExpanse_default = _angExpanse;
    _veloMv_default = _veloMv;

    _return_to_default_radiusPosition_seq = false;
    _return_to_default_angExpanse_seq = false;

    _angveloExpanseNomal = 3000;
    _angveloExpanseSlow = 1000;

    _pEffect_LaserIrradiate = NEW EffectLaserRefraction001("OP_Eff_Ref");
    _pEffect_LaserIrradiate->inactivateImmediately();
    addSubGroup(_pEffect_LaserIrradiate);

    _pLaserChipDispatcher = NEW LaserChipDispatcher("ROTLaser");
    MyCurveLaserChip001* pChip;
    for (int i = 0; i < 90; i++) { //���[�U�[�X�g�b�N
        stringstream name;
        name <<  getName() << "'s MYS_LaserChip" << i;
        string name2 = name.str();
        pChip = NEW MyCurveLaserChip001(name2.c_str());
//        pChip->setSource(this);
//        pChip->_pSource_vX = &_Q._x;
//        pChip->_pSource_vY = &_Q._y;
//        pChip->_pSource_vZ = &_Q._z;
       // pChip->_pSeTransmitter->useSe(1);
       // pChip->_pSeTransmitter->set(0, "laser001", _no);
        //pChip->inactivateImmediately();
        _pLaserChipDispatcher->addSubLast(pChip);
    }
    _pLaserChipDispatcher->config(
                               90, 25, _pEffect_LaserIrradiate
                           );
    addSubGroup(_pLaserChipDispatcher);

    _pDispatcher_MyShots001 = NEW GgafActorDispatcher("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 25; i++) { //���e�X�g�b�N
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmediately();
        _pDispatcher_MyShots001->addSubLast(pShot);
    }
    addSubGroup(_pDispatcher_MyShots001);



    _pEffectLockOn = NEW EffectLockOn001("EffectLockOn001");
    _pEffectLockOn->inactivateImmediately();
    addSubGroup(_pEffectLockOn);
    _pEffectLockOn_Release = NEW EffectLockOn001_Release("EffectLockOn001_R", _pEffectLockOn);
    _pEffectLockOn_Release->inactivateImmediately();
    addSubGroup(_pEffectLockOn_Release);
    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "laser001", GgafRepeatSeq::nextVal("CH_laser001"));
    _pSeTransmitter->set(1, "fire01", GgafRepeatSeq::nextVal("CH_fire01"));

    //prepareSe(0,"bse5", GgafRepeatSeq::nextVal("CH_bse5"));
    _pLockOnTarget = NULL;
}

void MyOption::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.3, 2.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(1.0);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 10, 1, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
}

void MyOption::initialize() {
    _angveloMove = ((1.0f*_veloMv / _radiusPosition)*(float)ANGLE180)/PI;
    _pMover->setMvVelo(_veloMv);
    _pMover->setRzMvAng(_angPosition+ANGLE90);
    _pMover->setRyMvAng(-ANGLE90);
    _pMover->setRzMvAngVelo(_angveloMove);//�攼�a�q�����x�u�^�p���x��
    _pMover->setRyMvAngVelo(0);//�攼�a�q�����x�u�^�p���x��
    _Z = GgafDx9Util::COS[_angPosition/ANGLE_RATE]*_radiusPosition; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
    _Y = GgafDx9Util::SIN[_angPosition/ANGLE_RATE]*_radiusPosition; //X���̐��̕����������Ď��v���ɔz�u
                                                                    //���[���h�ϊ��́i����@�j��X����]�Ƃ͂Ƌt�̉�]�Ȃ̂Œ���
    _X = 0;
    _pMover->setFaceAngVelo(AXIS_X, 4000);
    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;
    //pCOMMONSCENE->getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pLaserChipDispatcher->extract());

    _SX=_SY=_SZ=100;
}

void MyOption::addRadiusPosition(int prm_radius_offset) {
    //    _X = _Xorg;
    //    _Y = _Yorg;
    //    _Z = _Zorg;
    //����
    //    _Xorg = _X;
    //    _Yorg = _Y;
    //    _Zorg = _Z;
    //���O
    //�ł����Ăяo���Ă͂����܂���B


//���̔��a�������ꍇ�͔@���̃��W�b�N�̃R�����g���O��
//    int radius;
//    if (_radiusPosition == -1 * prm_radius_offset) { //�������������0�ɂȂ�ꍇ
//        //���a��0�ɂ��Ă͂����Ȃ��B0����Z������邽��
//        if (_radiusPosition > 0) {
//            radius = -100;
//        } else {
//            radius = 100;
//        }
//    } else {
//        radius = _radiusPosition + prm_radius_offset;
//    }
//    setRadiusPosition(radius);

    int radius;
    radius = _radiusPosition + prm_radius_offset;
    if (_radiusPosition < 15000) {
        radius = 15000; //�I�v�V�����Œᔼ�a����
    }
    setRadiusPosition(radius);
}


void MyOption::setRadiusPosition(int prm_radius) {
//    _X = _Xorg;
//    _Y = _Yorg;
//    _Z = _Zorg;
//����
//    _Xorg = _X;
//    _Yorg = _Y;
//    _Zorg = _Z;
//���O
//�ł����Ăяo���Ă͂����܂���B

    if (_radiusPosition == -1 * prm_radius) {
        if (_radiusPosition > 0) {
            _radiusPosition = -100;
        } else {
            _radiusPosition = 100;
        }
    } else {
        _radiusPosition += prm_radius;
    }

    _radiusPosition = prm_radius;
    angle angZY_ROTANG_X;
    if (_radiusPosition > 0) {
        angZY_ROTANG_X = MyStgUtil::getAngle2D(_Z, _Y); //�����̈ʒu
        _Z = _radiusPosition * GgafDx9Util::COS[GgafDx9Util::simplifyAng(angZY_ROTANG_X)/ANGLE_RATE];
        _Y = _radiusPosition * GgafDx9Util::SIN[GgafDx9Util::simplifyAng(angZY_ROTANG_X)/ANGLE_RATE];
    } else {
        angZY_ROTANG_X = MyStgUtil::getAngle2D(-_Z, -_Y); //�����̈ʒu
        _Z = _radiusPosition * GgafDx9Util::COS[GgafDx9Util::simplifyAng(angZY_ROTANG_X)/ANGLE_RATE];
        _Y = _radiusPosition * GgafDx9Util::SIN[GgafDx9Util::simplifyAng(angZY_ROTANG_X)/ANGLE_RATE];
    }
    //����prm_len��0�̏ꍇ�A���_�I�ɂ͌��̈ʒu�ɖ߂�͂��Ȃ̂����A
    //�덷�ۂߍ��݂̂��߁A�����Ɉʒu���ς��B
    //����āA�ړ����p�A�ړ��p���x�����݂̈ʒu(_Z,_Y)�ōĐݒ肵�Ȃ���΃Y����B
    _pMover->setRzMvAng(GgafDx9Util::simplifyAng(angZY_ROTANG_X + ANGLE90));
    _angveloMove = ((1.0f*_veloMv / _radiusPosition)*(float)ANGLE180)/PI;
    _pMover->setRzMvAngVelo(_angveloMove);

}

void MyOption::processBehavior() {




    //�������C��
    _X = _Xorg;
    _Y = _Yorg;
    _Z = _Zorg;


    if (_return_to_default_radiusPosition_seq) {
        //�����߂�
        if (_radiusPosition > _radiusPosition_default) {
            addRadiusPosition(-10000);
        }
        if (_radiusPosition < _radiusPosition_default) {
            addRadiusPosition(10000);
        }
        if (-10000 < _radiusPosition_default-_radiusPosition && _radiusPosition_default-_radiusPosition < 10000) {
            setRadiusPosition(_radiusPosition_default);
            _return_to_default_radiusPosition_seq = false;
        }

    } else {

        //�I�v�V�����Ɨ��ړ����䎞
        if (VB_PLAY->isBeingPressed(VB_OPTION) && _pMyOptionParent->_is_handle_move_mode) {
            //�I�v�V�����̍L����p���A�I�v�V�����ړ����x�ƁA���񔼌a�������x�Ƀx�N�g�������B
            //���̂����̐��񔼌a�������x�݂̂�ݒ�B
            addRadiusPosition(GgafDx9Util::SIN[_angExpanse/ ANGLE_RATE] * _pMyOptionParent->_veloOptionsMv);
            //�I�v�V�����ړ����x�̏�����MyOption�N���X�ōs���B
        }
    }


    if (_return_to_default_angExpanse_seq) {
        //�����߂�
        if (_angExpanse > _angExpanse_default) {
            _angExpanse -= 3000;
        }
        if (_angExpanse < _angExpanse_default) {
            _angExpanse += 3000;
        }
        if (-3000 <= _angExpanse_default-_angExpanse && _angExpanse_default-_angExpanse <= 3000) {
            _angExpanse = _angExpanse_default;
            _return_to_default_angExpanse_seq = false;
        }
        _angExpanse = GgafDx9Util::simplifyAng(_angExpanse);
    } else {
        //�I�v�V�����L����ƌ�������
        if (VB_PLAY->isBeingPressed(VB_OPTION) && VB_PLAY->isBeingPressed(VB_TURBO)) {
            if (pCOMMONSCENE->_pos_camera == CAM_POS_RIGHT) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    _angExpanse += _angveloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    _angExpanse -= _angveloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(2000 * (_radiusPosition_default/60000));
                    //_angExpanse += _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-2000 * (_radiusPosition_default/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
            } else if (pCOMMONSCENE->_pos_camera == CAM_POS_LEFT) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    _angExpanse -= _angveloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    _angExpanse += _angveloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(2000 * (_radiusPosition_default/60000));
                    //_angExpanse += _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-2000 * (_radiusPosition_default/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
            } else if (pCOMMONSCENE->_pos_camera == CAM_POS_TOP) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(2000 * (_radiusPosition_default/60000));
                    //_angExpanse += _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(-2000 * (_radiusPosition_default/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    _angExpanse += _angveloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    _angExpanse -= _angveloExpanseNomal;
                }
            } else if (pCOMMONSCENE->_pos_camera == CAM_POS_BOTTOM) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(-2000 * (_radiusPosition_default/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(2000 * (_radiusPosition_default/60000));
                    //_angExpanse += _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    _angExpanse -= _angveloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    _angExpanse += _angveloExpanseNomal;
                }
            } else if (pCOMMONSCENE->_pos_camera > CAM_POS_TO_BEHIND) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    _angExpanse += _angveloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    _angExpanse -= _angveloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(2000 * (_radiusPosition_default/60000));
                    //_angExpanse += _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-2000 * (_radiusPosition_default/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
            }
            _angExpanse = GgafDx9Util::simplifyAng(_angExpanse);
        }
    }


//    if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
//        addRadiusPosition(1000);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//        addRadiusPosition(-1000);
//    }

    _pMover->setMvVelo(_veloMv);
    _pMover->behave();

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;

    //��������
    //�����܂łŁAGgafDx9GeometryMover�̋@�\�݂̂ŁA
    //�ȉ��̂悤�ȏ�Ԃ܂ł����Ă����B
    //(100,0,0) ���猴�_�������C���[�W�A���͌��_
    //��y��  ��z��  �Ex��
    //
    //
    //              YZ���ʂɕ��s�ł��邮�����Ă�B
    //        ����
    //
    //
    //                    ��
    //��        ��        ��
    //��     (0,0,0)      (-50000, 0, _radiusPosition)
    //
    //
    //          ����
    //          (-50000, -1*_radiusPosition, 0)
    //
    //�������܂��F�X�Ɖ�]���������߁B���Ƃ͕��ʂɌv�Z�i�͋Z�j�ŁA���W��]�A������]���s�Ȃ��B
    //�_�~�[�̃A�N�^�[��A�����悤�Ƃ��������낢�����AQuaternion ���g�킴��𓾂Ȃ��i�̂ł͂Ȃ����G�j�B
    //TODO:�œK�����ׂ��AQuaternion�͕֗��������������B�����ėp��

    static float sinRY, cosRY, sinRZ, cosRZ;

    sinRZ = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angFace[AXIS_Z] / ANGLE_RATE];
    cosRZ = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angFace[AXIS_Z] / ANGLE_RATE];
    sinRY = GgafDx9Util::SIN[_pMyOptionParent->_pMover->_angFace[AXIS_Y] / ANGLE_RATE];
    cosRY = GgafDx9Util::COS[_pMyOptionParent->_pMover->_angFace[AXIS_Y] / ANGLE_RATE];
    //�S�I�v�V��������̉�Ƃ���OptionParent�𒆐S��WORLD�ϊ��̂悤�Ȑ���
    _X = cosRY*cosRZ*_Xorg + cosRY*-sinRZ*_Yorg + sinRY*_Zorg;
    _Y = sinRZ*_Xorg + cosRZ*_Yorg;
    _Z = -sinRY*cosRZ*_Xorg + -sinRY*-sinRZ*_Yorg + cosRY*_Zorg;



    //�����d���̏Ǝˊp���L����悤�ȉ�]�iQuaternion�Ŏ����j
    static float vX_axis,vY_axis,vZ_axis; //��]�����������x�N�g��
    vX_axis = cosRY*cosRZ*_pMover->_vX + cosRY*-sinRZ*_pMover->_vY + sinRY*_pMover->_vZ;
    vY_axis = sinRZ*_pMover->_vX + cosRZ*_pMover->_vY;
    vZ_axis = -sinRY*cosRZ*_pMover->_vX + -sinRY*-sinRZ*_pMover->_vY + cosRY*_pMover->_vZ;
    static float sinHalf, cosHalf;

    sinHalf = GgafDx9Util::SIN[_angExpanse/ANGLE_RATE/2]; //_angExpanse=��]���������p�x
    cosHalf = GgafDx9Util::COS[_angExpanse/ANGLE_RATE/2];

    //�v�Z
    _Q.set( cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    _Q.mul(0,
           _pMyOptionParent->_pMover->_vX,
           _pMyOptionParent->_pMover->_vY,
           _pMyOptionParent->_pMover->_vZ); //R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
    _Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //_Q._x, _Q._y, _Q._z ����]��̍��W�ƂȂ�
    //Z����]�AY����]�p�x���v�Z
    GgafDx9Util::getRzRyAng(
        (float)_Q._x,
        (float)_Q._y,
        (float)_Q._z,
        _RZ,
        _RY
     );

    _RZ = GgafDx9Util::simplifyAng(_RZ);
    _RY = GgafDx9Util::simplifyAng(_RY);
    _X += _pMyOptionParent->_X;
    _Y += _pMyOptionParent->_Y;
    _Z += _pMyOptionParent->_Z;

    //TODO
    //�œK��
    _pMover->setVxMvVelo(0);
    _pMover->setVyMvVelo(0);
    _pMover->setVzMvVelo(0);
            //_TRACE_("_pVBMap_Active->_state="<<(vbsta)(VB_PLAY->_pVBMap_Active->_state));
    if (pMYSHIP->_is_shooting_laser && VB_PLAY->isBeingPressed(VB_SHOT1)) {


        MyCurveLaserChip001* pLaserChip = (MyCurveLaserChip001*)_pLaserChipDispatcher->employ();
        if (pLaserChip != NULL) {
            if (_pLaserChipDispatcher->_pEffectActor_Irradiate) {
                _pLaserChipDispatcher->_pEffectActor_Irradiate->setGeometry(this);
            }
            pLaserChip->_pMover->_vX = _Q._x;
            pLaserChip->_pMover->_vY = _Q._y;
            pLaserChip->_pMover->_vZ = _Q._z;
            pLaserChip->_pMover->_angRzMv = _RZ;
            pLaserChip->_pMover->_angRyMv = _RY;
//            pLaserChip->_pMover->_angFace[AXIS_X] = angWk;
            pLaserChip->_pMover->_angFace[AXIS_Z] = _RZ;
            pLaserChip->_pMover->_angFace[AXIS_Y] = _RY;
            pLaserChip->_pMover->setVxMvVelo(_Q._x*150000);
            pLaserChip->_pMover->setVyMvVelo(_Q._y*150000);
            pLaserChip->_pMover->setVzMvVelo(_Q._z*150000);
            pLaserChip->_pMover->setVxMvAcce(0);
            pLaserChip->_pMover->setVyMvAcce(0);
            pLaserChip->_pMover->setVzMvAcce(0);
            pLaserChip->_pMover->behave();
            pLaserChip->_X = _X;
            pLaserChip->_Y = _Y;
            pLaserChip->_Z = _Z;
            pLaserChip->_pOrg = this;
            pLaserChip->activate();
            if (pLaserChip->_pChip_front == NULL) {
                //pLaserChip->_pSeTransmitter->play3D(0);
                _pSeTransmitter->play3D(0);
                //playSe3D(0);
            }
        }
    } else {
        _pLockOnTarget = NULL;
    }

    if (_pLockOnTarget) {
        //if (_pLockOnTarget->isOffscreen() || _pLockOnTarget->isActive() == false) { //��A�N�e�B�u�݂̂Ǝ���O�̓��b�N�I������
        if (_pLockOnTarget->isActive() == false) {  //��A�N�e�B�u�̂݉����i����O�ł����b�N�I���ێ��j
            _pLockOnTarget = NULL;
        } else {
            _pEffectLockOn->setGeometry(_pLockOnTarget);
            _pEffectLockOn->activate();
        }

    } else {
        if (_pEffectLockOn->isActive()) {
            _pEffectLockOn_Release->setGeometry(_pEffectLockOn);
            _pEffectLockOn_Release->activate();
        }
       _pEffectLockOn->inactivate();
    }

    if (pMYSHIP->_just_shot) {
        MyShot001* pShot = (MyShot001*)_pDispatcher_MyShots001->employ();
        if (pShot != NULL) {
            _pSeTransmitter->play3D(1);
            pShot->setGeometry(this);
            pShot->_pMover->_angFace[AXIS_X] = _RX;
            pShot->_pMover->_angFace[AXIS_Z] = _RZ;
            pShot->_pMover->_angFace[AXIS_Y] = _RY;
            pShot->_pMover->setRzRyMvAng(_RZ, _RY);
            pShot->activate();
        }
    }

//    if (VB_PLAY->isPushedDown(VB_SHOT1)) {
//        MyShot001* pShot = (MyShot001*)_pDispatcher_MyShots001->employ();
//        if (pShot != NULL) {
//            _pSeTransmitter->play3D(1);
//            pShot->setGeometry(this);
//            pShot->_pMover->_angFace[AXIS_X] = _RX;
//            pShot->_pMover->_angFace[AXIS_Z] = _RZ;
//            pShot->_pMover->_angFace[AXIS_Y] = _RY;
//            pShot->_pMover->setRzRyMvAng(_RZ, _RY);
//            pShot->activate();
//        }
//    }


    _pSeTransmitter->behave();

}

void MyOption::processJudgement() {
}

void MyOption::onHit(GgafActor* prm_pOtherActor) {
    sayonara();
}


MyOption::~MyOption() {
}



