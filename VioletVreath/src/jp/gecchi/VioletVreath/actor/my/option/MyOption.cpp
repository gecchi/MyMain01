#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


/** �P�I�v�V����������̍ő�\���b�N�I���� */
int MyOption::max_lockon_num_ = 9;
int MyOption::lockon_num_ = 8;
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) : DefaultMorphMeshActor(prm_name, "4/Ceres") {
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) : CubeMapMeshSetActor(prm_name, "4/Core4cm_") {
MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController) :
        DefaultMeshSetActor(prm_name, "8/CORE4", STATUS(MyOption)) {

    _TRACE_("MyOption::MyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyOption";
    pMyOptionController_ = prm_pMyOptionController;
    no_ = prm_no;
    ang_veloMove_ = 0;//����ړ��p���x�i�ǂݏo����p�j

    angPosition_ = 0;     //�~���㏉���ʒu�p�x�i���͊p�j�i�㏑�������ݒ�j
    radiusPosition_ = 150000;     //�������a�����i�㏑�������ݒ�j
    veloMv_ = 5000;     //����ړ����x�i�㏑�������ݒ�j
    angExpanse_ = 0;      //�I�v�V�����̍L����p�̉�]�p�i�㏑�������ݒ�j

    angPosition_base_ = angPosition_;
    radiusPosition_base_ = radiusPosition_;
    radiusPosition_stopping_ = radiusPosition_;
    velo_radius_ = 0;

    angExpanse_default_ = angExpanse_;
    veloMv_base_ = veloMv_;

    return_to_base_radiusPosition_seq_ = false;
    return_to_base_angExpanse_seq_ = false;

    ang_veloExpanseNomal_ = 3000;
    ang_veloExpanseSlow_ = 1000;

    pEffect_ = NEW EffectMyOption("EffectMyOption", this);
//    pEffect_->inactivateImmed();
    addSubGroup(pEffect_);

    //���[�U�[���˃G�t�F�N�g
//    pEffect_LaserIrradiate_ = NEW EffectLockon001_Main("OP_Eff_Ref");
//    pEffect_LaserIrradiate_->inactivateImmed();
//    addSubGroup(pEffect_LaserIrradiate_);
    pEffect_LaserIrradiate_ = NULL;
    pLaserChipDepo_ = NEW LaserChipDepository("ROTLaser");
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
//        pChip->pSource_vX_ = &Q_._x;
//        pChip->pSource_vY_ = &Q_._y;
//        pChip->pSource_vZ_ = &Q_._z;

        pLaserChipDepo_->addSubLast(pChip);
    }
    pLaserChipDepo_->config(90, 25, pEffect_LaserIrradiate_);
    addSubGroup(pLaserChipDepo_);

    pDepo_MyShots001_ = NEW GgafActorDepository("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 25; i++) { //���e�X�g�b�N
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmed();
        pDepo_MyShots001_->addSubLast(pShot);
    }
    addSubGroup(pDepo_MyShots001_);

    //���b�N�I���R���g���[���[
    pLockonController_ = NEW MyOptionLockonController("LockonController");
    addSubGroup(pLockonController_);

    //�t�H�g���R���g���[���[
    pTorpedoController_ = NEW MyOptionTorpedoController("TorpedoController", this);
    addSubGroup(pTorpedoController_);

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
    ang_veloMove_ = ((1.0f*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
    _pKurokoA->setMvVelo(veloMv_);
    _pKurokoA->setRzMvAng(angPosition_+D90ANG);
    _pKurokoA->setRyMvAng(-D90ANG);
    _pKurokoA->setRzMvAngVelo(ang_veloMove_);//�攼�a�q�����x�u�^�p���x��
    _pKurokoA->setRyMvAngVelo(0);//�攼�a�q�����x�u�^�p���x��
    _Z = GgafDxUtil::COS[angPosition_/SANG_RATE]*radiusPosition_; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
    _Y = GgafDxUtil::SIN[angPosition_/SANG_RATE]*radiusPosition_; //X���̐��̕����������Ď��v���ɔz�u
                                                                    //���[���h�ϊ��́i����@�j��X����]�Ƃ͂Ƌt�̉�]�Ȃ̂Œ���
    _X = 0;
    _pKurokoA->setFaceAngVelo(AXIS_X, 4000);
    Xorg_ = _X;
    Yorg_ = _Y;
    Zorg_ = _Z;
    //P_COMMON_SCENE->getDirector()->addSubGroup(KIND_MY_SHOT_NOMAL, pLaserChipDepo_->extract());
    angPosition_ = _pKurokoA->_angRzMv;

    adjust_angPos_seq_progress_ = 0;
    adjust_angPos_seq_new_angPosition_base_ = angPosition_;
    adjust_angPos_seq_spent_frame_ = 0;
    adjust_angPos_seq_angPosition_ = 0;

    radiusPosition_stopping_ = radiusPosition_;
}

void MyOption::onActive() {
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����T�u�ɂ��邽��
    //�ʂɌĂяo��
    pLockonController_->onActive();
    pTorpedoController_->onActive();
}

void MyOption::addRadiusPosition(int prm_radius_offset, int prm_min_radius, int prm_max_radius) {
    //    _X = Xorg_;
    //    _Y = Yorg_;
    //    _Z = Zorg_;
    //����
    //    Xorg_ = _X;
    //    Yorg_ = _Y;
    //    Zorg_ = _Z;
    //���O
    //�ł����Ăяo���Ă͂����܂���B


//���̔��a�������ꍇ�͔@���̃��W�b�N�̃R�����g���O��
//    int radius;
//    if (radiusPosition_ == -1 * prm_radius_offset) { //�������������0�ɂȂ�ꍇ
//        //���a��0�ɂ��Ă͂����Ȃ��B0����Z������邽��
//        if (radiusPosition_ > 0) {
//            radius = -100;
//        } else {
//            radius = 100;
//        }
//    } else {
//        radius = radiusPosition_ + prm_radius_offset;
//    }
//    setRadiusPosition(radius);

    int radius;
    radius = radiusPosition_ + prm_radius_offset;
    if (radiusPosition_ < prm_min_radius) {
        radius = prm_min_radius; //�I�v�V�����Œᔼ�a����
    } else if (radiusPosition_ > prm_max_radius) {
        radius = prm_max_radius; //�I�v�V�����Œᔼ�a����
    }

    setRadiusPosition(radius);
}


void MyOption::setRadiusPosition(int prm_radius) {
//    _X = Xorg_;
//    _Y = Yorg_;
//    _Z = Zorg_;
//����
//    Xorg_ = _X;
//    Yorg_ = _Y;
//    Zorg_ = _Z;
//���O
//�ł����Ăяo���Ă͂����܂���B
    radiusPosition_ = prm_radius;
    if (radiusPosition_ == -1  || radiusPosition_ == 0 || radiusPosition_ == 1) {
        _Z = _Y = 0;
        _pKurokoA->setRzMvAng(D90ANG);
        ang_veloMove_ = 0;
        _pKurokoA->setRzMvAngVelo(ang_veloMove_);
        return;

    }

    angle angZY_ROTANG_X;
    if (radiusPosition_ > 0) {
        angZY_ROTANG_X = MyStgUtil::getAngle2D(_Z, _Y); //�����̈ʒu
        _Z = radiusPosition_ * GgafDxUtil::COS[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
        _Y = radiusPosition_ * GgafDxUtil::SIN[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
    } else {
        angZY_ROTANG_X = MyStgUtil::getAngle2D(-_Z, -_Y); //�����̈ʒu
        _Z = radiusPosition_ * GgafDxUtil::COS[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
        _Y = radiusPosition_ * GgafDxUtil::SIN[GgafDxUtil::simplifyAng(angZY_ROTANG_X)/SANG_RATE];
    }
    //����prm_len��0�̏ꍇ�A���_�I�ɂ͌��̈ʒu�ɖ߂�͂��Ȃ̂����A
    //�덷�ۂߍ��݂̂��߁A�����Ɉʒu���ς��B
    //����āA�ړ����p�A�ړ��p���x�����݂̈ʒu(_Z,_Y)�ōĐݒ肵�Ȃ���΃Y����B
    _pKurokoA->setRzMvAng(angZY_ROTANG_X + D90ANG);
    ang_veloMove_ = ((1.0*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
    _pKurokoA->setRzMvAngVelo(ang_veloMove_);
}


void MyOption::adjustAngPosition(angle prm_new_angPosition_base, frame prm_spent_frame) {
    adjust_angPos_seq_progress_ = 1;
    adjust_angPos_seq_new_angPosition_base_ = MyStgUtil::simplifyAng(prm_new_angPosition_base);
    adjust_angPos_seq_spent_frame_ = prm_spent_frame + 1;
}



void MyOption::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    //�������C��
    _X = Xorg_;
    _Y = Yorg_;
    _Z = Zorg_;

    if (return_to_base_radiusPosition_seq_) {
        //�����߂�
        if (radiusPosition_ > radiusPosition_base_) {
            addRadiusPosition(-10000);
        }
        if (radiusPosition_ < radiusPosition_base_) {
            addRadiusPosition(10000);
        }
        if (-10000 < radiusPosition_base_-radiusPosition_ && radiusPosition_base_-radiusPosition_ < 10000) {
            setRadiusPosition(radiusPosition_base_);
            radiusPosition_stopping_ = radiusPosition_;
//            velo_radius_ = 0;
            return_to_base_radiusPosition_seq_ = false;
        }

    } else {

        //�I�v�V�����Ɨ��ړ����䎞
        if (VB_PLAY->isBeingPressed(VB_OPTION) && pMyOptionController_->is_handle_move_mode_) {
            //�I�v�V�����̍L����p���A�I�v�V�����ړ����x�ƁA���񔼌a�������x�Ƀx�N�g�������B
            //���̂����̐��񔼌a�������x�݂̂�ݒ�B
            addRadiusPosition(GgafDxUtil::SIN[angExpanse_/ SANG_RATE] * pMyOptionController_->veloOptionsMv_);
            //�I�v�V�����ړ����x�̏�����MyOption�N���X�ōs���B
        }
    }

    if (return_to_base_angExpanse_seq_) {

        //�����߂�
        if (angExpanse_ > angExpanse_default_) {
            angExpanse_ -= 3000;
        }
        if (angExpanse_ < angExpanse_default_) {
            angExpanse_ += 3000;
        }
        if (-3000 <= angExpanse_default_-angExpanse_ && angExpanse_default_-angExpanse_ <= 3000) {
            angExpanse_ = angExpanse_default_;
            return_to_base_angExpanse_seq_ = false;
        }
        angExpanse_ = GgafDxUtil::simplifyAng(angExpanse_);
    } else {
        //�I�v�V�����L����ƌ�������
        if (VB_PLAY->isBeingPressed(VB_OPTION) && VB_PLAY->isBeingPressed(VB_TURBO)) {
            int pos_camera = P_VAM->pos_camera_;
            if (pos_camera == VAM_POS_RIGHT) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ += ang_veloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    angExpanse_ -= ang_veloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(2000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-2000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            } else if (pos_camera == VAM_POS_LEFT) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ -= ang_veloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    angExpanse_ += ang_veloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(2000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-2000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            } else if (pos_camera == VAM_POS_TOP) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(2000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(-2000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    angExpanse_ += ang_veloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    angExpanse_ -= ang_veloExpanseNomal_;
                }
            } else if (pos_camera == VAM_POS_BOTTOM) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(-2000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(2000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    angExpanse_ -= ang_veloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    angExpanse_ += ang_veloExpanseNomal_;
                }
            } else if (pos_camera > VAM_POS_TO_BEHIND) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ += ang_veloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    angExpanse_ -= ang_veloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(2000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-2000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            }
            radiusPosition_stopping_ = radiusPosition_;
//            velo_radius_ = 0;
            angExpanse_ = GgafDxUtil::simplifyAng(angExpanse_);
        } else {
            if (pMyOptionController_->is_free_from_myship_mode_) {
                //
            } else {
                if (VB_PLAY->isBeingPressed(VB_OPTION) || VB_PLAY->isBeingPressed(VB_POWERUP)) {
                } else {
                    GgafDxGeoElem* pGeoOpCon = pMyOptionController_->pRing_OpConGeoHistory_->getPrev();
                    if (pGeoOpCon->_X == pMyOptionController_->_X &&
                        pGeoOpCon->_Y == pMyOptionController_->_Y &&
                        pGeoOpCon->_Z == pMyOptionController_->_Z) {
                        //��ړ���
                        addRadiusPosition(+2000, 1, radiusPosition_stopping_);
                        if (veloMv_ == veloMv_base_) {

                        } else {
                            veloMv_ += 100;
                            if (veloMv_ >= veloMv_base_) {
                                MyOptionController::adjustDefaltAngPosition(120);
                                veloMv_ = veloMv_base_;
                            }
                        }
                    } else {
                        //�ړ���
                        addRadiusPosition(-2000, 1);
                        veloMv_ -= 100;
                        if (veloMv_ < 0) {
                            veloMv_ = 0;
                        }
                    }
                }

            }
        }
    }

    if (adjust_angPos_seq_progress_ > 0) {
        if (adjust_angPos_seq_progress_ == 1) {
            //��������
            adjust_angPos_seq_progress_ = 2;
        }


        if (adjust_angPos_seq_progress_ == 2) {
            //�����̊p�x�ʒu�擾
            if (radiusPosition_ > 0) {
                adjust_angPos_seq_angPosition_ = MyStgUtil::getAngle2D(_Z, _Y);
            } else {
                adjust_angPos_seq_angPosition_ = MyStgUtil::getAngle2D(-_Z, -_Y);
            }
            //���݂̊p����
            angle ang_diff = MyStgUtil::getAngDiff(adjust_angPos_seq_angPosition_, adjust_angPos_seq_new_angPosition_base_, sgn(veloMv_));
            //�c�t���[���Ǝc�ړ��p���K�v�Ȋp���x
            ang_velo ang_velo_need = ang_diff / (ang_velo)adjust_angPos_seq_spent_frame_;
            //�K�v�Ȋp���x����
            ang_velo ang_velo_offset = ang_velo_need - ang_veloMove_;
            //�K�v�Ȋp���x�����ɑΉ�����ړ����x�����߂�
            velo veloMv_offset =  (2.0*PI*radiusPosition_ * ang_velo_offset) / D360ANG;
            //���x�ݒ�
            _pKurokoA->setRzMvAngVelo(ang_veloMove_ + ang_velo_offset);
            _pKurokoA->setMvVelo(veloMv_ + veloMv_offset);
            adjust_angPos_seq_spent_frame_ --;

            if (adjust_angPos_seq_spent_frame_ == 0) {
                angPosition_base_ = adjust_angPos_seq_new_angPosition_base_;
                //�덷�C���̂��ߗ��z�ʒu�ɍĐݒ�
                ang_veloMove_ = ((1.0*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
                _pKurokoA->setMvVelo(veloMv_);
                _pKurokoA->setRzMvAng(GgafDxUtil::simplifyAng(angPosition_base_ + D90ANG));
                _pKurokoA->setRzMvAngVelo(ang_veloMove_);//�攼�a�q�����x�u�^�p���x��
                _Z = GgafDxUtil::COS[angPosition_base_/SANG_RATE]*radiusPosition_; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
                _Y = GgafDxUtil::SIN[angPosition_base_/SANG_RATE]*radiusPosition_; //X���̐��̕����������Ď��v���ɔz�u
                _X = 0;
                adjust_angPos_seq_progress_ = 0;
            }
        }
    } else {
         //�ʏ펞
        _pKurokoA->setMvVelo(veloMv_);
    }
    angPosition_ = GgafDxUtil::simplifyAng(angPosition_+ang_veloMove_);

    _pKurokoA->behave();
    //_pKurokoB->behave();

    Xorg_ = _X;
    Yorg_ = _Y;
    Zorg_ = _Z;

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
    //��     (0,0,0)      (-50000, 0, radiusPosition_)
    //
    //
    //          ����
    //          (-50000, -1*radiusPosition_, 0)
    //
    //�������܂��F�X�Ɖ�]���������߁B���Ƃ͕��ʂɌv�Z�i�͋Z�j�ŁA���W��]�A������]���s�Ȃ��B
    //�_�~�[�̃A�N�^�[��A�����悤�Ƃ��������낢�����AQuaternion ���g�킴��𓾂Ȃ��i�̂ł͂Ȃ����G�j�B
    //TODO:�œK�����ׂ��AQuaternion�͕֗��������������B�����ėp��

    float sinRZ = GgafDxUtil::SIN[pMyOptionController_->_pKurokoA->_angFace[AXIS_Z] / SANG_RATE];
    float cosRZ = GgafDxUtil::COS[pMyOptionController_->_pKurokoA->_angFace[AXIS_Z] / SANG_RATE];
    float sinRY = GgafDxUtil::SIN[pMyOptionController_->_pKurokoA->_angFace[AXIS_Y] / SANG_RATE];
    float cosRY = GgafDxUtil::COS[pMyOptionController_->_pKurokoA->_angFace[AXIS_Y] / SANG_RATE];
    //�S�I�v�V��������̉�Ƃ���OptionController�𒆐S��WORLD�ϊ��̂悤�Ȑ���
    _X = cosRY*cosRZ*Xorg_ + cosRY*-sinRZ*Yorg_ + sinRY*Zorg_;
    _Y = sinRZ*Xorg_ + cosRZ*Yorg_;
    _Z = -sinRY*cosRZ*Xorg_ + -sinRY*-sinRZ*Yorg_ + cosRY*Zorg_;



    //�����d���̏Ǝˊp���L����悤�ȉ�]�iQuaternion�Ŏ����j
    float vX_axis = cosRY*cosRZ*_pKurokoA->_vX + cosRY*-sinRZ*_pKurokoA->_vY + sinRY*_pKurokoA->_vZ;
    float vY_axis = sinRZ*_pKurokoA->_vX + cosRZ*_pKurokoA->_vY;
    float vZ_axis = -sinRY*cosRZ*_pKurokoA->_vX + -sinRY*-sinRZ*_pKurokoA->_vY + cosRY*_pKurokoA->_vZ;
    float sinHalf = GgafDxUtil::SIN[angExpanse_/SANG_RATE/2]; //angExpanse_=��]���������p�x
    float cosHalf = GgafDxUtil::COS[angExpanse_/SANG_RATE/2];

    //�v�Z
    //������W(x, y, z)�ɂ����āA��]�̎���(��, ��, ��)�ŁA�Ɖ񂷉�]
    //P = (0; x, y, z)
    //Q = (cos(��/2); �� sin(��/2), �� sin(��/2), �� sin(��/2))
    //R = (cos(��/2); -�� sin(��/2), -�� sin(��/2), -�� sin(��/2))
    //
    //R P Q = (0; ����)
    //
    //��]�� ��(vX_axis, vY_axis, vZ_axis) ��]�p�� angExpanse_
    Q_.set(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    Q_.mul(0,
           pMyOptionController_->_pKurokoA->_vX,
           pMyOptionController_->_pKurokoA->_vY,
           pMyOptionController_->_pKurokoA->_vZ); //R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
    Q_.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //Q._x, Q._y, Q._z ����]��̍��W�ƂȂ�
    //Z����]�AY����]�p�x���v�Z
    GgafDxUtil::getRzRyAng(Q_._x, Q_._y, Q_._z,
                           _RZ, _RY);


    _X += pMyOptionController_->_X;
    _Y += pMyOptionController_->_Y;
    _Z += pMyOptionController_->_Z;

//    _RZ = GgafDxUtil::simplifyAng(_RZ);
//    _RY = GgafDxUtil::simplifyAng(_RY);
//    GgafDxGeoElem* pGeoOpCon = pMyOptionController_->pRing_OpConGeoHistory_->getPrev(MyOptionController::o2o_*(no_+2));
//    _X += pGeoOpCon->_X;
//    _Y += pGeoOpCon->_Y;
//    _Z += pGeoOpCon->_Z;
//    if (pMyOptionController_->is_free_from_myship_mode_) {
//        _X += (pMyOptionController_->_X - pMyOptionController_->X_on_free_);
//        _Y += (pMyOptionController_->_Y - pMyOptionController_->Y_on_free_);
//        _Z += (pMyOptionController_->_Z - pMyOptionController_->Z_on_free_);
//    } else {
//
//    }

    //TODO
    //�œK��
    //_pKurokoB->_veloVxMv = 0;
    //_pKurokoB->_veloVyMv = 0;
    //_pKurokoB->_veloVzMv = 0;
    if (pMyShip->is_shooting_laser_ && VB_PLAY->isBeingPressed(VB_SHOT1)) {


        MyOptionWateringLaserChip001* pLaserChip = (MyOptionWateringLaserChip001*)pLaserChipDepo_->dispatch();
//        MyOptionStraightLaserChip001* pLaserChip = (MyOptionStraightLaserChip001*)pLaserChipDepo_->dispatch();

        if (pLaserChip) {


            if (pLaserChipDepo_->_pEffectActor_Irradiate) {
                pLaserChipDepo_->_pEffectActor_Irradiate->locateAs(this);
            }
            //�X�g���[�g�p
//            pLaserChip->_pKurokoA->behave();
//            pLaserChip->_pKurokoB->behave();
//            pLaserChip->pOrg_ = this;
//            pLaserChip->activate();

              //�J�[�u�p
//            pLaserChip->_pKurokoA->_vX = Q_._x;
//            pLaserChip->_pKurokoA->_vY = Q_._y;
//            pLaserChip->_pKurokoA->_vZ = Q_._z;
//            pLaserChip->_pKurokoA->_angRzMv = _RZ;
//            pLaserChip->_pKurokoA->_angRyMv = _RY;
////            pLaserChip->_pKurokoA->_angFace[AXIS_X] = _pKurokoA->_angFace[AXIS_X];
//            pLaserChip->_pKurokoA->_angFace[AXIS_Z] = _RZ;
//            pLaserChip->_pKurokoA->_angFace[AXIS_Y] = _RY;

            pLaserChip->_pKurokoB->setVxMvVelo(Q_._x*pLaserChip->max_velo_renge_);
            pLaserChip->_pKurokoB->setVyMvVelo(Q_._y*pLaserChip->max_velo_renge_);
            pLaserChip->_pKurokoB->setVzMvVelo(Q_._z*pLaserChip->max_velo_renge_);
            pLaserChip->_pKurokoB->setVxMvAcce(Q_._x*pLaserChip->max_velo_renge_/pLaserChip->r_max_acce_);
            pLaserChip->_pKurokoB->setVyMvAcce(Q_._y*pLaserChip->max_velo_renge_/pLaserChip->r_max_acce_);
            pLaserChip->_pKurokoB->setVzMvAcce(Q_._z*pLaserChip->max_velo_renge_/pLaserChip->r_max_acce_);
//            pLaserChip->_pKurokoA->behave();
            pLaserChip->_pKurokoB->behave();
            pLaserChip->_X = _X;
            pLaserChip->_Y = _Y;
            pLaserChip->_Z = _Z;
            pLaserChip->_RZ = _RZ;
            pLaserChip->_RY = _RY;
            pLaserChip->pOrg_ = this;

            if (pLaserChip->_pChip_front == NULL) {
                _pSeTransmitter->play3D(0);
            }
        }
    } else {
        pLockonController_->releaseAllLockon();
    }
    if (pMyShip->just_shot_) {
        MyShot001* pShot = (MyShot001*)pDepo_MyShots001_->dispatch();
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
    pLockonController_->onInactive();
    pTorpedoController_->onInactive();
    pLaserChipDepo_->reset();

}

void MyOption::onHit(GgafActor* prm_pOtherActor) {
    sayonara();
}

MyOption::~MyOption() {
}
