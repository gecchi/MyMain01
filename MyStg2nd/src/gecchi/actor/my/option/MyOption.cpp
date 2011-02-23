#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


/** �P�I�v�V����������̍ő�\���b�N�I���� */
int MyOption::_max_lockon_num = 7;
int MyOption::_lockon_num = 1;
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) : DefaultMorphMeshActor(prm_name, "4/Ceres") {
MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) : DefaultMeshSetActor(prm_name, "8/Astraea") {
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) : CubeMapMeshSetActor(prm_name, "4/Core4_cm") {


_TRACE_("MyOption::MyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyOption";
    _pMyOptionController = prm_pMyOptionController;
    _no = prm_no;
    _angveloMove = 0;//����ړ��p���x�i�ǂݏo����p�j

    _angPosition = 0;     //�~���㏉���ʒu�p�x�i���͊p�j�i�㏑�������ݒ�j
    _radiusPosition = 150000;     //�������a�����i�㏑�������ݒ�j
    _veloMv = 5000;     //����ړ����x�i�㏑�������ݒ�j
    _angExpanse = 0;      //�I�v�V�����̍L����p�̉�]�p�i�㏑�������ݒ�j

    _angPosition_base = _angPosition;
    _radiusPosition_base = _radiusPosition;
    _angExpanse_default = _angExpanse;
    _veloMv_base = _veloMv;

    _return_to_base_radiusPosition_seq = false;
    _return_to_base_angExpanse_seq = false;

    _angveloExpanseNomal = 3000;
    _angveloExpanseSlow = 1000;

    //���[�U�[���˃G�t�F�N�g
//    _pEffect_LaserIrradiate = NEW EffectLockon001_Main("OP_Eff_Ref");
//    _pEffect_LaserIrradiate->inactivateImmediately();
//    addSubGroup(_pEffect_LaserIrradiate);
    _pEffect_LaserIrradiate = NULL;


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

    //���b�N�I���R���g���[���[
    _pLockonController = NEW MyOptionLockonController("LockonController");
    addSubGroup(_pLockonController);

    //�t�H�g���R���g���[���[
    _pTorpedoController = NEW MyOptionTorpedoController("TorpedoController", this);
    addSubGroup(_pTorpedoController);


    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "laser001", GgafRepeatSeq::nextVal("CH_laser001"));
    _pSeTransmitter->set(1, "fire01", GgafRepeatSeq::nextVal("CH_fire01"));

    //prepareSe(0,"bse5", GgafRepeatSeq::nextVal("CH_bse5"));

}

void MyOption::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.3, 2.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(1.0);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 10, 1, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
}

void MyOption::initialize() {
    _SX=_SY=_SZ=100;
}

void MyOption::onReset() {
    _angveloMove = ((1.0f*_veloMv / _radiusPosition)*(double)ANGLE180)/PI;
    _pKuroko->setMvVelo(_veloMv);
    _pKuroko->setRzMvAng(_angPosition+ANGLE90);
    _pKuroko->setRyMvAng(-ANGLE90);
    _pKuroko->setRzMvAngVelo(_angveloMove);//�攼�a�q�����x�u�^�p���x��
    _pKuroko->setRyMvAngVelo(0);//�攼�a�q�����x�u�^�p���x��
    _Z = GgafDx9Util::COS[_angPosition/ANGLE_RATE]*_radiusPosition; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
    _Y = GgafDx9Util::SIN[_angPosition/ANGLE_RATE]*_radiusPosition; //X���̐��̕����������Ď��v���ɔz�u
                                                                    //���[���h�ϊ��́i����@�j��X����]�Ƃ͂Ƌt�̉�]�Ȃ̂Œ���
    _X = 0;
    _pKuroko->setFaceAngVelo(AXIS_X, 4000);
    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;
    //P_COMMON_SCENE->getLordActor()->addSubGroup(KIND_MY_SHOT_NOMAL, _pLaserChipDispatcher->extract());
    _angPosition = _pKuroko->_angRzMv;

    _adjust_angPos_seq_progress = 0;
    _adjust_angPos_seq_new_angPosition_base = _angPosition;
    _adjust_angPos_seq_spent_frame = 0;
    _adjust_angPos_seq_angPosition = 0;
}

void MyOption::onActive() {
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
    if (_radiusPosition < 30000) {
        radius = 30000; //�I�v�V�����Œᔼ�a����
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
    _pKuroko->setRzMvAng(GgafDx9Util::simplifyAng(angZY_ROTANG_X + ANGLE90));
    _angveloMove = ((1.0*_veloMv / _radiusPosition)*(double)ANGLE180)/PI;
    _pKuroko->setRzMvAngVelo(_angveloMove);
}


void MyOption::adjustAngPosition(angle prm_new_angPosition_base, frame prm_spent_frame) {
    _adjust_angPos_seq_progress = 1;
    _adjust_angPos_seq_new_angPosition_base = MyStgUtil::simplifyAng(prm_new_angPosition_base);
    _adjust_angPos_seq_spent_frame = prm_spent_frame + 1;
}



void MyOption::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    //�������C��
    _X = _Xorg;
    _Y = _Yorg;
    _Z = _Zorg;


    if (_return_to_base_radiusPosition_seq) {
        //�����߂�
        if (_radiusPosition > _radiusPosition_base) {
            addRadiusPosition(-10000);
        }
        if (_radiusPosition < _radiusPosition_base) {
            addRadiusPosition(10000);
        }
        if (-10000 < _radiusPosition_base-_radiusPosition && _radiusPosition_base-_radiusPosition < 10000) {
            setRadiusPosition(_radiusPosition_base);
            _return_to_base_radiusPosition_seq = false;
        }

    } else {

        //�I�v�V�����Ɨ��ړ����䎞
        if (VB_PLAY->isBeingPressed(VB_OPTION) && _pMyOptionController->_is_handle_move_mode) {
            //�I�v�V�����̍L����p���A�I�v�V�����ړ����x�ƁA���񔼌a�������x�Ƀx�N�g�������B
            //���̂����̐��񔼌a�������x�݂̂�ݒ�B
            addRadiusPosition(GgafDx9Util::SIN[_angExpanse/ ANGLE_RATE] * _pMyOptionController->_veloOptionsMv);
            //�I�v�V�����ړ����x�̏�����MyOption�N���X�ōs���B
        }
    }

    if (_return_to_base_angExpanse_seq) {

        //�����߂�
        if (_angExpanse > _angExpanse_default) {
            _angExpanse -= 3000;
        }
        if (_angExpanse < _angExpanse_default) {
            _angExpanse += 3000;
        }
        if (-3000 <= _angExpanse_default-_angExpanse && _angExpanse_default-_angExpanse <= 3000) {
            _angExpanse = _angExpanse_default;
            _return_to_base_angExpanse_seq = false;
        }
        _angExpanse = GgafDx9Util::simplifyAng(_angExpanse);
    } else {
        //�I�v�V�����L����ƌ�������
        if (VB_PLAY->isBeingPressed(VB_OPTION) && VB_PLAY->isBeingPressed(VB_TURBO)) {
//            if (P_VAM->_pos_camera == VAM_POS_RIGHT) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    _angExpanse += _angveloExpanseNomal;
                } else if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    _angExpanse -= _angveloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
                    //_angExpanse += _angveloExpanseSlow;
                } else if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
//            } else if (P_VAM->_pos_camera == VAM_POS_LEFT) {
//                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
//                    _angExpanse -= _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
//                    _angExpanse += _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_UP)) {
//                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
//                    //_angExpanse += _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
//                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
//                    //_angExpanse -= _angveloExpanseSlow;
//                }
//            } else if (P_VAM->_pos_camera == VAM_POS_TOP) {
//                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
//                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
//                    //_angExpanse += _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
//                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
//                    //_angExpanse -= _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_UP)) {
//                    _angExpanse += _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
//                    _angExpanse -= _angveloExpanseNomal;
//                }
//            } else if (P_VAM->_pos_camera == VAM_POS_BOTTOM) {
//                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
//                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
//                    //_angExpanse -= _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
//                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
//                    //_angExpanse += _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_UP)) {
//                    _angExpanse -= _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
//                    _angExpanse += _angveloExpanseNomal;
//                }
//            } else if (P_VAM->_pos_camera > VAM_POS_TO_BEHIND) {
//                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
//                    _angExpanse += _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
//                    _angExpanse -= _angveloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_UP)) {
//                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
//                    //_angExpanse += _angveloExpanseSlow;
//                }
//                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
//                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
//                    //_angExpanse -= _angveloExpanseSlow;
//                }
//            }
            _angExpanse = GgafDx9Util::simplifyAng(_angExpanse);
        }
    }


//    if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
//        addRadiusPosition(1000);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//        addRadiusPosition(-1000);
//    }

    if (_adjust_angPos_seq_progress > 0) {
        if (_adjust_angPos_seq_progress == 1) {
            //��������

            _adjust_angPos_seq_progress = 2;
        }


        if (_adjust_angPos_seq_progress == 2) {
            //�����̊p�x�ʒu�擾
            if (_radiusPosition > 0) {
                _adjust_angPos_seq_angPosition = MyStgUtil::getAngle2D(_Z, _Y);
            } else {
                _adjust_angPos_seq_angPosition = MyStgUtil::getAngle2D(-_Z, -_Y);
            }
            //���݂̊p����
            angle ang_diff = MyStgUtil::getAngDiff(_adjust_angPos_seq_angPosition, _adjust_angPos_seq_new_angPosition_base, sgn(_veloMv));
            //�c�t���[���Ǝc�ړ��p���K�v�Ȋp���x
            angvelo angvelo_need = ang_diff / (angvelo)_adjust_angPos_seq_spent_frame;
            //�K�v�Ȋp���x����
            angvelo angvelo_offset = angvelo_need - _angveloMove;
            //�K�v�Ȋp���x�����ɑΉ�����ړ����x�����߂�
            velo veloMv_offset =  (2.0*PI*_radiusPosition * angvelo_offset) / ANGLE360;
            //���x�ݒ�
            _pKuroko->setRzMvAngVelo(_angveloMove + angvelo_offset);
            _pKuroko->setMvVelo(_veloMv + veloMv_offset);
            _adjust_angPos_seq_spent_frame --;

            if (_adjust_angPos_seq_spent_frame == 0) {
                _angPosition_base = _adjust_angPos_seq_new_angPosition_base;
                //�덷�C���̂��ߗ��z�ʒu�ɍĐݒ�
                _angveloMove = ((1.0*_veloMv / _radiusPosition)*(double)ANGLE180)/PI;
                _pKuroko->setMvVelo(_veloMv);
                _pKuroko->setRzMvAng(GgafDx9Util::simplifyAng(_angPosition_base + ANGLE90));
                _pKuroko->setRzMvAngVelo(_angveloMove);//�攼�a�q�����x�u�^�p���x��
                _Z = GgafDx9Util::COS[_angPosition_base/ANGLE_RATE]*_radiusPosition; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
                _Y = GgafDx9Util::SIN[_angPosition_base/ANGLE_RATE]*_radiusPosition; //X���̐��̕����������Ď��v���ɔz�u
                _X = 0;
                _adjust_angPos_seq_progress = 0;
            }
        }
    } else {
         //�ʏ펞
        _pKuroko->setMvVelo(_veloMv);
    }
    _angPosition = GgafDx9Util::simplifyAng(_angPosition+_angveloMove);

    _pKuroko->behave();

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;

    //��������
    //�����܂łŁAGgafDx9Kuroko�̋@�\�݂̂ŁA
    //�ȉ��̂悤�ȏ�Ԃ܂ł����Ă����B
    //(100,0,0) ���猴�_�������C���[�W�A���͌��_
    //��y��  ��z��  �Ex���i�������O�A��O�����j
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

    float sinRZ = GgafDx9Util::SIN[_pMyOptionController->_pKuroko->_angFace[AXIS_Z] / ANGLE_RATE];
    float cosRZ = GgafDx9Util::COS[_pMyOptionController->_pKuroko->_angFace[AXIS_Z] / ANGLE_RATE];
    float sinRY = GgafDx9Util::SIN[_pMyOptionController->_pKuroko->_angFace[AXIS_Y] / ANGLE_RATE];
    float cosRY = GgafDx9Util::COS[_pMyOptionController->_pKuroko->_angFace[AXIS_Y] / ANGLE_RATE];
    //�S�I�v�V��������̉�Ƃ���OptionController�𒆐S��WORLD�ϊ��̂悤�Ȑ���
    _X = cosRY*cosRZ*_Xorg + cosRY*-sinRZ*_Yorg + sinRY*_Zorg;
    _Y = sinRZ*_Xorg + cosRZ*_Yorg;
    _Z = -sinRY*cosRZ*_Xorg + -sinRY*-sinRZ*_Yorg + cosRY*_Zorg;



    //�����d���̏Ǝˊp���L����悤�ȉ�]�iQuaternion�Ŏ����j
    float vX_axis = cosRY*cosRZ*_pKuroko->_vX + cosRY*-sinRZ*_pKuroko->_vY + sinRY*_pKuroko->_vZ;
    float vY_axis = sinRZ*_pKuroko->_vX + cosRZ*_pKuroko->_vY;
    float vZ_axis = -sinRY*cosRZ*_pKuroko->_vX + -sinRY*-sinRZ*_pKuroko->_vY + cosRY*_pKuroko->_vZ;
    float sinHalf = GgafDx9Util::SIN[_angExpanse/ANGLE_RATE/2]; //_angExpanse=��]���������p�x
    float cosHalf = GgafDx9Util::COS[_angExpanse/ANGLE_RATE/2];

    //�v�Z
    GgafDx9Quaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
//    _Q.set( cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    Q.mul(0,
           _pMyOptionController->_pKuroko->_vX,
           _pMyOptionController->_pKuroko->_vY,
           _pMyOptionController->_pKuroko->_vZ); //R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
    Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //Q._x, Q._y, Q._z ����]��̍��W�ƂȂ�
    //Z����]�AY����]�p�x���v�Z
    GgafDx9Util::getRzRyAng(
        Q._x, Q._y, Q._z,
        _RZ, _RY
     );

//    _RZ = GgafDx9Util::simplifyAng(_RZ);
//    _RY = GgafDx9Util::simplifyAng(_RY);
    _X += _pMyOptionController->_X;
    _Y += _pMyOptionController->_Y;
    _Z += _pMyOptionController->_Z;

    //TODO
    //�œK��
    _pKuroko->_veloVxMv = 0;
    _pKuroko->_veloVyMv = 0;
    _pKuroko->_veloVzMv = 0;
            //_TRACE_("_pVBMap_Active->_state="<<(vbsta)(VB_PLAY->_pVBMap_Active->_state));
    if (pMyShip->_is_shooting_laser && VB_PLAY->isBeingPressed(VB_SHOT1)) {


        MyCurveLaserChip001* pLaserChip = (MyCurveLaserChip001*)_pLaserChipDispatcher->employ();
        if (pLaserChip) {
            if (_pLaserChipDispatcher->_pEffectActor_Irradiate) {
                _pLaserChipDispatcher->_pEffectActor_Irradiate->setCoordinateBy(this);
            }
            pLaserChip->_pKuroko->_vX = Q._x;
            pLaserChip->_pKuroko->_vY = Q._y;
            pLaserChip->_pKuroko->_vZ = Q._z;
            pLaserChip->_pKuroko->_angRzMv = _RZ;
            pLaserChip->_pKuroko->_angRyMv = _RY;
//            pLaserChip->_pKuroko->_angFace[AXIS_X] = _pKuroko->_angFace[AXIS_X];
            pLaserChip->_pKuroko->_angFace[AXIS_Z] = _RZ;
            pLaserChip->_pKuroko->_angFace[AXIS_Y] = _RY;
            pLaserChip->_pKuroko->setVxMvVelo(Q._x*150000);
            pLaserChip->_pKuroko->setVyMvVelo(Q._y*150000);
            pLaserChip->_pKuroko->setVzMvVelo(Q._z*150000);
            pLaserChip->_pKuroko->setVxMvAcce(0);
            pLaserChip->_pKuroko->setVyMvAcce(0);
            pLaserChip->_pKuroko->setVzMvAcce(0);
            pLaserChip->_pKuroko->behave();
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
        _pLockonController->releaseAllLockon();
    }

//    if (_pLockonTarget) {
//        //if (_pLockonTarget->isOutOfView() || _pLockonTarget->isActiveActor() == false) { //��A�N�e�B�u�݂̂Ǝ���O�̓��b�N�I������
//        if (_pLockonTarget->isActiveActor() == false) {  //��A�N�e�B�u�̂݉����i����O�ł����b�N�I���ێ��j
//            _pLockonController->releaseLockon();
//            _pLockonTarget = NULL;
//        } else {
//            _pLockonController->lockon(_pLockonTarget);
//        }
//
//    } else {
//        _pLockonController->releaseLockon();
//        _pLockonTarget = NULL;
//    }

    if (pMyShip->_just_shot) {
        MyShot001* pShot = (MyShot001*)_pDispatcher_MyShots001->employ();
        if (pShot) {
            _pSeTransmitter->play3D(1);
            pShot->setCoordinateBy(this);
            pShot->_pKuroko->_angFace[AXIS_X] = _RX;
            pShot->_pKuroko->_angFace[AXIS_Z] = _RZ;
            pShot->_pKuroko->_angFace[AXIS_Y] = _RY;
            pShot->_pKuroko->setRzRyMvAng(_RZ, _RY);
            pShot->activate();
        }
    }

//    if (VB_PLAY->isPushedDown(VB_SHOT1)) {
//        MyShot001* pShot = (MyShot001*)_pDispatcher_MyShots001->employ();
//        if (pShot) {
//            _pSeTransmitter->play3D(1);
//            pShot->setCoordinate(this);
//            pShot->_pKuroko->_angFace[AXIS_X] = _RX;
//            pShot->_pKuroko->_angFace[AXIS_Z] = _RZ;
//            pShot->_pKuroko->_angFace[AXIS_Y] = _RY;
//            pShot->_pKuroko->setRzRyMvAng(_RZ, _RY);
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

void MyOption::processFinal() {
//    //���b�N�I�����̗͂������Ȃ�΁A���݂��Ă悤���؂�
//    if (_pLockonTarget) {
//        if (_pLockonTarget->_pStatus->get(STAT_Stamina) <= 0) {
//            _pLockonController->releaseLockon();
//            _pLockonTarget = NULL;
//        }
//    }
}
MyOption::~MyOption() {
}

