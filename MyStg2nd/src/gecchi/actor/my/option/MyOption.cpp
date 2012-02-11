#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


/** �P�I�v�V����������̍ő�\���b�N�I���� */
int MyOption::_max_lockon_num = 9;
int MyOption::_lockon_num = 8;
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) : DefaultMorphMeshActor(prm_name, "4/Ceres") {
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) : CubeMapMeshSetActor(prm_name, "4/Core4_cm") {
MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) :
        DefaultMeshSetActor(prm_name, "8/CORE4", STATUS(MyOption)) {

    _TRACE_("MyOption::MyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyOption";
    _pMyOptionController = prm_pMyOptionController;
    _no = prm_no;
    _ang_veloMove = 0;//����ړ��p���x�i�ǂݏo����p�j

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

    _ang_veloExpanseNomal = 3000;
    _ang_veloExpanseSlow = 1000;

    _pEffect = NEW EffectMyOption("EffectMyOption", this);
//    _pEffect->inactivateImmed();
    addSubGroup(_pEffect);

    //���[�U�[���˃G�t�F�N�g
//    _pEffect_LaserIrradiate = NEW EffectLockon001_Main("OP_Eff_Ref");
//    _pEffect_LaserIrradiate->inactivateImmed();
//    addSubGroup(_pEffect_LaserIrradiate);
    _pEffect_LaserIrradiate = NULL;
    _pLaserChipDepo = NEW LaserChipDepository("ROTLaser");
    MyOptionWateringLaserChip001* pChip;
//    MyOptionStraightLaserChip001* pChip;
    for (int i = 0; i < 90; i++) { //���[�U�[�X�g�b�N
        stringstream name;
        name <<  getName() << "'s MYS_LaserChip" << i;
        string name2 = name.str();
        pChip = NEW MyOptionWateringLaserChip001(name2.c_str());
        //pChip = NEW MyOptionStraightLaserChip001(name2.c_str());
        //MyOptionStraightLaserChip001�̏ꍇ�ȉ����K�v
        //�X�g���[�g�p
//        pChip->setSource(this);
//        pChip->_pSource_vX = &_Q._x;
//        pChip->_pSource_vY = &_Q._y;
//        pChip->_pSource_vZ = &_Q._z;

        _pLaserChipDepo->addSubLast(pChip);
    }
    _pLaserChipDepo->config(
                               90, 25, _pEffect_LaserIrradiate
                           );
    addSubGroup(_pLaserChipDepo);

    _pDepo_MyShots001 = NEW GgafActorDepository("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 25; i++) { //���e�X�g�b�N
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmed();
        _pDepo_MyShots001->addSubLast(pShot);
    }
    addSubGroup(_pDepo_MyShots001);

    //���b�N�I���R���g���[���[
    _pLockonController = NEW MyOptionLockonController("LockonController");
    addSubGroup(_pLockonController);

    //�t�H�g���R���g���[���[
    _pTorpedoController = NEW MyOptionTorpedoController("TorpedoController", this);
    addSubGroup(_pTorpedoController);


    _X_on_free = _X;
    _Y_on_free = _Y;
    _Z_on_free = _Z;

    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "laser001", GgafRepeatSeq::nextVal("CH_laser001"));
    _pSeTransmitter->set(1, "fire01", GgafRepeatSeq::nextVal("CH_fire01"));

    //prepareSe(0,"bse5", GgafRepeatSeq::nextVal("CH_bse5"));
}

void MyOption::onCreateModel() {
//    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.3, 2.0);
//    _pModel->_pTextureBlinker->setBlink(1.0);
//    _pModel->_pTextureBlinker->beat(120, 10, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void MyOption::initialize() {
    _SX=_SY=_SZ=100;
}

void MyOption::onReset() {
    _ang_veloMove = ((1.0f*_veloMv / _radiusPosition)*(double)D180ANG)/PI;
    _pKurokoA->setMvVelo(_veloMv);
    _pKurokoA->setRzMvAng(_angPosition+D90ANG);
    _pKurokoA->setRyMvAng(-D90ANG);
    _pKurokoA->setRzMvAngVelo(_ang_veloMove);//�攼�a�q�����x�u�^�p���x��
    _pKurokoA->setRyMvAngVelo(0);//�攼�a�q�����x�u�^�p���x��
    _Z = GgafDxUtil::COS[_angPosition/SANG_RATE]*_radiusPosition; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
    _Y = GgafDxUtil::SIN[_angPosition/SANG_RATE]*_radiusPosition; //X���̐��̕����������Ď��v���ɔz�u
                                                                    //���[���h�ϊ��́i����@�j��X����]�Ƃ͂Ƌt�̉�]�Ȃ̂Œ���
    _X = 0;
    _pKurokoA->setFaceAngVelo(AXIS_X, 4000);
    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;
    //P_COMMON_SCENE->getDirector()->addSubGroup(KIND_MY_SHOT_NOMAL, _pLaserChipDepo->extract());
    _angPosition = _pKurokoA->_angRzMv;

    _adjust_angPos_seq_progress = 0;
    _adjust_angPos_seq_new_angPosition_base = _angPosition;
    _adjust_angPos_seq_spent_frame = 0;
    _adjust_angPos_seq_angPosition = 0;
}

void MyOption::onActive() {
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����T�u�ɂ��邽��
    //�ʂɌĂяo��
    _pLockonController->onActive();
    _pTorpedoController->onActive();
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
        _Z = _radiusPosition * GgafDxUtil::COS[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
        _Y = _radiusPosition * GgafDxUtil::SIN[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
    } else {
        angZY_ROTANG_X = MyStgUtil::getAngle2D(-_Z, -_Y); //�����̈ʒu
        _Z = _radiusPosition * GgafDxUtil::COS[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
        _Y = _radiusPosition * GgafDxUtil::SIN[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
    }
    //����prm_len��0�̏ꍇ�A���_�I�ɂ͌��̈ʒu�ɖ߂�͂��Ȃ̂����A
    //�덷�ۂߍ��݂̂��߁A�����Ɉʒu���ς��B
    //����āA�ړ����p�A�ړ��p���x�����݂̈ʒu(_Z,_Y)�ōĐݒ肵�Ȃ���΃Y����B
    _pKurokoA->setRzMvAng(GgafDxUtil::simplifyAng(angZY_ROTANG_X + D90ANG));
    _ang_veloMove = ((1.0*_veloMv / _radiusPosition)*(double)D180ANG)/PI;
    _pKurokoA->setRzMvAngVelo(_ang_veloMove);
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
            addRadiusPosition(GgafDxUtil::SIN[_angExpanse/ SANG_RATE] * _pMyOptionController->_veloOptionsMv);
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
        _angExpanse = GgafDxUtil::simplifyAng(_angExpanse);
    } else {
        //�I�v�V�����L����ƌ�������
        if (VB_PLAY->isBeingPressed(VB_OPTION) && VB_PLAY->isBeingPressed(VB_TURBO)) {
            int pos_camera = P_VAM->_pos_camera;
            if (pos_camera == VAM_POS_RIGHT) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    _angExpanse += _ang_veloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    _angExpanse -= _ang_veloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
                    //_angExpanse += _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
            } else if (pos_camera == VAM_POS_LEFT) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    _angExpanse -= _ang_veloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    _angExpanse += _ang_veloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
                    //_angExpanse += _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
            } else if (pos_camera == VAM_POS_TOP) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
                    //_angExpanse += _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    _angExpanse += _ang_veloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    _angExpanse -= _ang_veloExpanseNomal;
                }
            } else if (pos_camera == VAM_POS_BOTTOM) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
                    //_angExpanse += _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    _angExpanse -= _ang_veloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    _angExpanse += _ang_veloExpanseNomal;
                }
            } else if (pos_camera > VAM_POS_TO_BEHIND) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    _angExpanse += _ang_veloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    _angExpanse -= _ang_veloExpanseNomal;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
                    //_angExpanse += _angveloExpanseSlow;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
                    //_angExpanse -= _angveloExpanseSlow;
                }
            }















//
//                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
//                    _angExpanse += _ang_veloExpanseNomal;
//                } else if (VB_PLAY->isBeingPressed(VB_LEFT)) {
//                    _angExpanse -= _ang_veloExpanseNomal;
//                }
//                if (VB_PLAY->isBeingPressed(VB_UP)) {
//                    addRadiusPosition(2000 * (_radiusPosition_base/60000));
//                    //_angExpanse += _ang_veloExpanseSlow;
//                } else if (VB_PLAY->isBeingPressed(VB_DOWN)) {
//                    addRadiusPosition(-2000 * (_radiusPosition_base/60000));
//                    //_angExpanse -= _ang_veloExpanseSlow;
//                }








            _angExpanse = GgafDxUtil::simplifyAng(_angExpanse);
        }
    }

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
            ang_velo ang_velo_need = ang_diff / (ang_velo)_adjust_angPos_seq_spent_frame;
            //�K�v�Ȋp���x����
            ang_velo ang_velo_offset = ang_velo_need - _ang_veloMove;
            //�K�v�Ȋp���x�����ɑΉ�����ړ����x�����߂�
            velo veloMv_offset =  (2.0*PI*_radiusPosition * ang_velo_offset) / D360ANG;
            //���x�ݒ�
            _pKurokoA->setRzMvAngVelo(_ang_veloMove + ang_velo_offset);
            _pKurokoA->setMvVelo(_veloMv + veloMv_offset);
            _adjust_angPos_seq_spent_frame --;

            if (_adjust_angPos_seq_spent_frame == 0) {
                _angPosition_base = _adjust_angPos_seq_new_angPosition_base;
                //�덷�C���̂��ߗ��z�ʒu�ɍĐݒ�
                _ang_veloMove = ((1.0*_veloMv / _radiusPosition)*(double)D180ANG)/PI;
                _pKurokoA->setMvVelo(_veloMv);
                _pKurokoA->setRzMvAng(GgafDxUtil::simplifyAng(_angPosition_base + D90ANG));
                _pKurokoA->setRzMvAngVelo(_ang_veloMove);//�攼�a�q�����x�u�^�p���x��
                _Z = GgafDxUtil::COS[_angPosition_base/SANG_RATE]*_radiusPosition; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
                _Y = GgafDxUtil::SIN[_angPosition_base/SANG_RATE]*_radiusPosition; //X���̐��̕����������Ď��v���ɔz�u
                _X = 0;
                _adjust_angPos_seq_progress = 0;
            }
        }
    } else {
         //�ʏ펞
        _pKurokoA->setMvVelo(_veloMv);
    }
    _angPosition = GgafDxUtil::simplifyAng(_angPosition+_ang_veloMove);

    _pKurokoA->behave();
    //_pKurokoB->behave();

    _Xorg = _X;
    _Yorg = _Y;
    _Zorg = _Z;

    //��������
    //�����܂łŁAGgafDxKurokoA�̋@�\�݂̂ŁA
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

    float sinRZ = GgafDxUtil::SIN[_pMyOptionController->_pKurokoA->_angFace[AXIS_Z] / SANG_RATE];
    float cosRZ = GgafDxUtil::COS[_pMyOptionController->_pKurokoA->_angFace[AXIS_Z] / SANG_RATE];
    float sinRY = GgafDxUtil::SIN[_pMyOptionController->_pKurokoA->_angFace[AXIS_Y] / SANG_RATE];
    float cosRY = GgafDxUtil::COS[_pMyOptionController->_pKurokoA->_angFace[AXIS_Y] / SANG_RATE];
    //�S�I�v�V��������̉�Ƃ���OptionController�𒆐S��WORLD�ϊ��̂悤�Ȑ���
    _X = cosRY*cosRZ*_Xorg + cosRY*-sinRZ*_Yorg + sinRY*_Zorg;
    _Y = sinRZ*_Xorg + cosRZ*_Yorg;
    _Z = -sinRY*cosRZ*_Xorg + -sinRY*-sinRZ*_Yorg + cosRY*_Zorg;



    //�����d���̏Ǝˊp���L����悤�ȉ�]�iQuaternion�Ŏ����j
    float vX_axis = cosRY*cosRZ*_pKurokoA->_vX + cosRY*-sinRZ*_pKurokoA->_vY + sinRY*_pKurokoA->_vZ;
    float vY_axis = sinRZ*_pKurokoA->_vX + cosRZ*_pKurokoA->_vY;
    float vZ_axis = -sinRY*cosRZ*_pKurokoA->_vX + -sinRY*-sinRZ*_pKurokoA->_vY + cosRY*_pKurokoA->_vZ;
    float sinHalf = GgafDxUtil::SIN[_angExpanse/SANG_RATE/2]; //_angExpanse=��]���������p�x
    float cosHalf = GgafDxUtil::COS[_angExpanse/SANG_RATE/2];

    //�v�Z
    //������W(x, y, z)�ɂ����āA��]�̎���(��, ��, ��)�ŁA�Ɖ񂷉�]
    //P = (0; x, y, z)
    //Q = (cos(��/2); �� sin(��/2), �� sin(��/2), �� sin(��/2))
    //R = (cos(��/2); -�� sin(��/2), -�� sin(��/2), -�� sin(��/2))
    //
    //R P Q = (0; ����)
    //
    //��]�� ��(vX_axis, vY_axis, vZ_axis) ��]�p�� _angExpanse
    _Q.set(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    _Q.mul(0,
           _pMyOptionController->_pKurokoA->_vX,
           _pMyOptionController->_pKurokoA->_vY,
           _pMyOptionController->_pKurokoA->_vZ); //R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
    _Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //Q._x, Q._y, Q._z ����]��̍��W�ƂȂ�
    //Z����]�AY����]�p�x���v�Z
    GgafDxUtil::getRzRyAng(
            _Q._x, _Q._y, _Q._z,
        _RZ, _RY
     );

//    _RZ = GgafDxUtil::simplifyAng(_RZ);
//    _RY = GgafDxUtil::simplifyAng(_RY);


    if (_pMyOptionController->_is_free_from_myship_mode) {
        _X += (_pMyOptionController->_X + _X_on_free);
        _Y += (_pMyOptionController->_Y + _Y_on_free);
        _Z += (_pMyOptionController->_Z + _Z_on_free);
    } else {
        GgafDxGeoElem* pGeoMyShip = pMyShip->_pRing_GeoHistory->getPrev(20*(_no+1)); //���@�ɂ�����������ĒǏ]
        _X += pGeoMyShip->_X;
        _Y += pGeoMyShip->_Y;
        _Z += pGeoMyShip->_Z;
    }

    //TODO
    //�œK��
    //_pKurokoB->_veloVxMv = 0;
    //_pKurokoB->_veloVyMv = 0;
    //_pKurokoB->_veloVzMv = 0;
    if (pMyShip->_is_shooting_laser && VB_PLAY->isBeingPressed(VB_SHOT1)) {


        MyOptionWateringLaserChip001* pLaserChip = (MyOptionWateringLaserChip001*)_pLaserChipDepo->dispatch();
//        MyOptionStraightLaserChip001* pLaserChip = (MyOptionStraightLaserChip001*)_pLaserChipDepo->dispatch();

        if (pLaserChip) {


            if (_pLaserChipDepo->_pEffectActor_Irradiate) {
                _pLaserChipDepo->_pEffectActor_Irradiate->locateAs(this);
            }
            //�X�g���[�g�p
//            pLaserChip->_pKurokoA->behave();
//            pLaserChip->_pKurokoB->behave();
//            pLaserChip->_pOrg = this;
//            pLaserChip->activate();

              //�J�[�u�p
//            pLaserChip->_pKurokoA->_vX = _Q._x;
//            pLaserChip->_pKurokoA->_vY = _Q._y;
//            pLaserChip->_pKurokoA->_vZ = _Q._z;
//            pLaserChip->_pKurokoA->_angRzMv = _RZ;
//            pLaserChip->_pKurokoA->_angRyMv = _RY;
////            pLaserChip->_pKurokoA->_angFace[AXIS_X] = _pKurokoA->_angFace[AXIS_X];
//            pLaserChip->_pKurokoA->_angFace[AXIS_Z] = _RZ;
//            pLaserChip->_pKurokoA->_angFace[AXIS_Y] = _RY;

            pLaserChip->_pKurokoB->setVxMvVelo(_Q._x*pLaserChip->_max_velo_renge);
            pLaserChip->_pKurokoB->setVyMvVelo(_Q._y*pLaserChip->_max_velo_renge);
            pLaserChip->_pKurokoB->setVzMvVelo(_Q._z*pLaserChip->_max_velo_renge);
            pLaserChip->_pKurokoB->setVxMvAcce(_Q._x*pLaserChip->_max_velo_renge/pLaserChip->_r_max_acce);
            pLaserChip->_pKurokoB->setVyMvAcce(_Q._y*pLaserChip->_max_velo_renge/pLaserChip->_r_max_acce);
            pLaserChip->_pKurokoB->setVzMvAcce(_Q._z*pLaserChip->_max_velo_renge/pLaserChip->_r_max_acce);
//            pLaserChip->_pKurokoA->behave();
            pLaserChip->_pKurokoB->behave();
            pLaserChip->_X = _X;
            pLaserChip->_Y = _Y;
            pLaserChip->_Z = _Z;
            pLaserChip->_RZ = _RZ;
            pLaserChip->_RY = _RY;
            pLaserChip->_pOrg = this;

            if (pLaserChip->_pChip_front == NULL) {
                _pSeTransmitter->play3D(0);
            }
        }
    } else {
        _pLockonController->releaseAllLockon();
    }
    if (pMyShip->_just_shot) {
        MyShot001* pShot = (MyShot001*)_pDepo_MyShots001->dispatch();
        if (pShot) {
            _pSeTransmitter->play3D(1);
            pShot->locateAs(this);
            pShot->_pKurokoA->_angFace[AXIS_X] = _RX;
            pShot->_pKurokoA->_angFace[AXIS_Z] = _RZ;
            pShot->_pKurokoA->_angFace[AXIS_Y] = _RY;
            pShot->_pKurokoA->setRzRyMvAng(_RZ, _RY);
        }
    }

    _pSeTransmitter->behave();

}

void MyOption::processJudgement() {
}

void MyOption::onInactive() {
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����T�u�ɂ��邽��
    //�ʂɌĂяo��
    _pLockonController->onInactive();
    _pTorpedoController->onInactive();
    _pLaserChipDepo->reset();

}

void MyOption::onFreeFromMyShipMode() {
    MyShip* pMyShip = P_MYSHIP;
    _X_on_free = _X - pMyShip->_X;
    _Y_on_free = _Y - pMyShip->_Y;
    _Z_on_free = _Z - pMyShip->_Z;
}

void MyOption::onHit(GgafActor* prm_pOtherActor) {
    sayonara();
}

MyOption::~MyOption() {
}

