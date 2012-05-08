#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


/** �P�I�v�V����������̍ő�\���b�N�I���� */
int MyOption::max_lockon_num_ = 9;
int MyOption::lockon_num_ = 8;
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pOptCtrlr) : DefaultMorphMeshActor(prm_name, "4/Ceres") {
//MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pOptCtrlr) : CubeMapMeshSetActor(prm_name, "4/Core4cm_") {
MyOption::MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pOptCtrlr) :
        DefaultMeshSetActor(prm_name, "8/CORE4", STATUS(MyOption)) {

    _TRACE_("MyOption::MyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyOption";
    pOptionCtrlr_ = prm_pOptCtrlr;
    no_ = prm_no;
    angveloMove_ = 0;//����ړ��p���x�i�ǂݏo����p�j

    angPosition_ = 0;     //�~���㏉���ʒu�p�x�i���͊p�j�i�㏑�������ݒ�j
    radiusPosition_ = 150000;     //�������a�����i�㏑�������ݒ�j
    veloMv_ = 5000;     //����ړ����x�i�㏑�������ݒ�j
    angExpanse_ = 0;      //�I�v�V�����̍L����p�̉�]�p�i�㏑�������ݒ�j

    angPosition_base_ = angPosition_;
    radiusPosition_base_ = radiusPosition_;
    radiusPosition_stopping_ = radiusPosition_;

    angExpanse_default_ = angExpanse_;
    veloMv_base_ = veloMv_;

    return_to_base_radiusPosition_seq_ = false;
    return_to_base_angExpanse_seq_ = false;

    angveloExpanseNomal_ = 3000;
    angveloExpanseSlow_ = 1000;

    pEffect_ = NEW EffectMyOption("EffectMyOption", this);
    addSubGroup(pEffect_);

    //���[�U�[���˃G�t�F�N�g
//    pEffect_LaserIrradiate_ = NEW EffectLockon001_Main("OP_Eff_Ref");
//    pEffect_LaserIrradiate_->inactivateImmed();
//    addSubGroup(pEffect_LaserIrradiate_);
    pEffect_LaserIrradiate_ = NULL;
    pLaserChipDepo_ = NEW LaserChipDepository("ROTLaser");
    MyOptionWateringLaserChip001* pChip;
//    MyOptionStraightLaserChip001* pChip;
    for (int i = 0; i < 80; i++) { //���[�U�[�X�g�b�N
        std::stringstream name;
        name <<  getName() << "'s MYS_LaserChip" << i;
        std::string name2 = name.str();
        pChip = NEW MyOptionWateringLaserChip001(name2.c_str());
        //pChip = NEW MyOptionStraightLaserChip001(name2.c_str());
        //MyOptionStraightLaserChip001�̏ꍇ�ȉ����K�v
        //�X�g���[�g�p
//        pChip->setSource(this);
//        pChip->pSource_vX_ = &Q._x;
//        pChip->pSource_vY_ = &Q._y;
//        pChip->pSource_vZ_ = &Q._z;

        pLaserChipDepo_->addSubLast(pChip);
    }
    pLaserChipDepo_->config(80, 25, pEffect_LaserIrradiate_);
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
    pLockonCtrlr_ = NEW MyOptionLockonController("LockonController");
    addSubGroup(pLockonCtrlr_);

    //�t�H�g���R���g���[���[
    pTorpedoCtrlr_ = NEW MyOptionTorpedoController("TorpedoController", this);
    addSubGroup(pTorpedoCtrlr_);

    _pSeTx->useSe(3);
    _pSeTx->set(0, "laser001", GgafRepeatSeq::nextVal("CH_laser001"));
    _pSeTx->set(1, "fire01", GgafRepeatSeq::nextVal("CH_fire01"));
    _pSeTx->set(2, "bse5", GgafRepeatSeq::nextVal("CH_torpedo"));
    //prepareSe(0,"bse5", GgafRepeatSeq::nextVal("CH_bse5"));
    need_adjust_pos_flg_ = false;
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
    angveloMove_ = ((1.0f*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
    _pKurokoA->setMvVelo(veloMv_);
    _pKurokoA->setRzMvAng(angPosition_+D90ANG);
    _pKurokoA->setRyMvAng(-D90ANG);
    _pKurokoA->setRzMvAngVelo(angveloMove_);//�攼�a�q�����x�u�^�p���x��
    _pKurokoA->setRyMvAngVelo(0);//�攼�a�q�����x�u�^�p���x��
    _Z = GgafDxUtil::COS[angPosition_/SANG_RATE]*radiusPosition_; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
    _Y = GgafDxUtil::SIN[angPosition_/SANG_RATE]*radiusPosition_; //X���̐��̕����������Ď��v���ɔz�u
                                                                    //���[���h�ϊ��́i����@�j��X����]�Ƃ͂Ƌt�̉�]�Ȃ̂Œ���
    _X = 0;
    _pKurokoA->setFaceAngVelo(AXIS_X, 4000);
    Xorg_ = _X;
    Yorg_ = _Y;
    Zorg_ = _Z;
    angPosition_ = _pKurokoA->_angRzMv;

    adjust_angPos_seq_progress_ = 0;
    adjust_angPos_seq_new_angPosition_base_ = angPosition_;
    adjust_angPos_seq_spent_frame_ = 0;

    radiusPosition_stopping_ = radiusPosition_;
}

void MyOption::onActive() {
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����T�u�ɂ��邽��
    //�ʂɌĂяo��
    pLockonCtrlr_->onActive();
    pTorpedoCtrlr_->onActive();
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
    if (radius < prm_min_radius) {
        radius = prm_min_radius; //�I�v�V�����Œᔼ�a����
    } else if (radius > prm_max_radius) {
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
        angveloMove_ = 0;
        _pKurokoA->setRzMvAngVelo(angveloMove_);
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
    angveloMove_ = ((1.0*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
    _pKurokoA->setRzMvAngVelo(angveloMove_);
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
        if (radiusPosition_ == radiusPosition_base_) {
            //kk
            return_to_base_radiusPosition_seq_ = false;
        } else if (radiusPosition_ > radiusPosition_base_) {
            addRadiusPosition(-10000, radiusPosition_base_);
        } else if (radiusPosition_ < radiusPosition_base_) {
            addRadiusPosition(10000, 1, radiusPosition_base_);
        }

        radiusPosition_stopping_ = radiusPosition_base_;
    } else {

        //�I�v�V�����Ɨ��ړ����䎞
        if (VB_PLAY->isBeingPressed(VB_OPTION) && pOptionCtrlr_->is_handle_move_mode_) {
            //�I�v�V�����̍L����p���A�I�v�V�����ړ����x�ƁA���񔼌a�������x�Ƀx�N�g�������B
            //���̂����̐��񔼌a�������x�݂̂�ݒ�B
            addRadiusPosition(GgafDxUtil::SIN[angExpanse_/ SANG_RATE] * pOptionCtrlr_->veloOptionsMv_);
            //�I�v�V�����ړ����x�̏�����MyOption�N���X�ōs���B
        }
    }

    if (return_to_base_angExpanse_seq_) {

        //�����߂�
        if (angExpanse_ > angExpanse_default_) {
            angExpanse_ -= 2000;
        }
        if (angExpanse_ < angExpanse_default_) {
            angExpanse_ += 2000;
        }
        if (-2000 <= angExpanse_default_-angExpanse_ && angExpanse_default_-angExpanse_ <= 2000) {
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
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(3000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(-3000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            } else if (pos_camera == VAM_POS_LEFT) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(+3000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(-3000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            } else if (pos_camera == VAM_POS_TOP) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(3000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(-3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(-3000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
            } else if (pos_camera == VAM_POS_BOTTOM) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(-3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(-3000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(3000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
            } else if (pos_camera > VAM_POS_TO_BEHIND) {
                if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (VB_PLAY->isBeingPressed(VB_UP)) {
                    addRadiusPosition(3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(3000 * (radiusPosition_base_/60000));
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-3000 * (radiusPosition_base_/60000));
                    radiusPosition_stopping_+=(-3000 * (radiusPosition_base_/60000));
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            }
            angExpanse_ = GgafDxUtil::simplifyAng(angExpanse_);
        } else {
            if (pOptionCtrlr_->is_free_from_myship_mode_) {
                //
            } else {
                    GgafDxGeoElem* pGeoOpCon = pOptionCtrlr_->pRing_OptCtrlGeoHistory_->getPrev();
                    if (VB_PLAY->isBeingPressed(VB_OPTION)) {
                        //�I�v�V�����{�^����������
                        //radiusPosition��������Ȃ�
                    } else if (pGeoOpCon->_X == pOptionCtrlr_->_X &&
                               pGeoOpCon->_Y == pOptionCtrlr_->_Y &&
                               pGeoOpCon->_Z == pOptionCtrlr_->_Z )
                    {
                        //��ړ���
                        if (radiusPosition_stopping_ == radiusPosition_) {
                            //kk
                        } else if (radiusPosition_stopping_ > radiusPosition_) {
                            addRadiusPosition(+2000, 1, radiusPosition_stopping_);
                        } else if (radiusPosition_stopping_ < radiusPosition_) {
                            addRadiusPosition(-2000, radiusPosition_);
                        }
                        if (veloMv_ == veloMv_base_) {

                        } else {
                            veloMv_ += 100;
                            if (veloMv_ >= veloMv_base_) {
                                if (need_adjust_pos_flg_) {
                                    MyOptionController::adjustDefaltAngPosition(radiusPosition_stopping_ / 1000);
                                    need_adjust_pos_flg_ = false;
                                }
                                veloMv_ = veloMv_base_;
                            }
                        }
                    } else {
                        //�ړ���
                        if (1 < radiusPosition_) {
                            addRadiusPosition(-3000, 1);
                        }
                        if (radiusPosition_ < 10000) {
                            need_adjust_pos_flg_ = true;
                        }

                        veloMv_ -= 200;
                        if (veloMv_ < 0) {
                            veloMv_ = 0;
                        }
                    }
//                }

            }
        }
    }

    if (adjust_angPos_seq_progress_ > 0) {
        if (adjust_angPos_seq_progress_ == 1) {
            //��������
            adjust_angPos_seq_progress_ = 2;
        }


        if (adjust_angPos_seq_progress_ == 2) {
            angle angPosition_now;
            //�����̊p�x�ʒu�擾
            if (radiusPosition_ > 0) {
                angPosition_now = MyStgUtil::getAngle2D(_Z, _Y);
            } else {
                angPosition_now = MyStgUtil::getAngle2D(-_Z, -_Y);
            }
            //���݂̊p����
            angle ang_diff = MyStgUtil::getAngDiff(angPosition_now, adjust_angPos_seq_new_angPosition_base_, sgn(veloMv_));
            if (GgafUtil::abs(ang_diff) > D_ANG(350)) {
                ang_diff = MyStgUtil::getAngDiff(angPosition_now, adjust_angPos_seq_new_angPosition_base_, TURN_CLOSE_TO);
            }
            //�c�t���[���Ǝc�ړ��p���K�v�Ȋp���x
            angvelo angvelo_need = ang_diff / (angvelo)adjust_angPos_seq_spent_frame_;
            //�K�v�Ȋp���x����
            angvelo angvelo_offset = angvelo_need - angveloMove_;
            //�K�v�Ȋp���x�����ɑΉ�����ړ����x�����߂�
            velo veloMv_offset =  (2.0*PI*radiusPosition_ * angvelo_offset) / D360ANG;
            //���x�ݒ�
            _pKurokoA->setRzMvAngVelo(angveloMove_ + angvelo_offset);
            _pKurokoA->setMvVelo(veloMv_ + veloMv_offset);
            adjust_angPos_seq_spent_frame_ --;

            if (adjust_angPos_seq_spent_frame_ == 0) {
                angPosition_base_ = adjust_angPos_seq_new_angPosition_base_;
                //�덷�C���̂��ߗ��z�ʒu�ɍĐݒ�
                angveloMove_ = ((1.0*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
                _pKurokoA->setMvVelo(veloMv_);
                _pKurokoA->setRzMvAng(GgafDxUtil::simplifyAng(angPosition_base_ + D90ANG));
                _pKurokoA->setRzMvAngVelo(angveloMove_);//�攼�a�q�����x�u�^�p���x��
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
    angPosition_ = GgafDxUtil::simplifyAng(angPosition_+angveloMove_);

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

    float sinRZ = GgafDxUtil::SIN[pOptionCtrlr_->_pKurokoA->_angFace[AXIS_Z] / SANG_RATE];
    float cosRZ = GgafDxUtil::COS[pOptionCtrlr_->_pKurokoA->_angFace[AXIS_Z] / SANG_RATE];
    float sinRY = GgafDxUtil::SIN[pOptionCtrlr_->_pKurokoA->_angFace[AXIS_Y] / SANG_RATE];
    float cosRY = GgafDxUtil::COS[pOptionCtrlr_->_pKurokoA->_angFace[AXIS_Y] / SANG_RATE];
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
    GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf); //R
//    Q.set(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
    Q.mul(0, pOptionCtrlr_->_pKurokoA->_vX,
             pOptionCtrlr_->_pKurokoA->_vY,
             pOptionCtrlr_->_pKurokoA->_vZ); //R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
    Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //Q._x, Q._y, Q._z ����]��̍��W�ƂȂ�
    //Z����]�AY����]�p�x���v�Z
    GgafDxUtil::getRzRyAng(Q._x, Q._y, Q._z,
                           _RZ, _RY);


    _X += pOptionCtrlr_->_X;
    _Y += pOptionCtrlr_->_Y;
    _Z += pOptionCtrlr_->_Z;


    //TODO
    //�œK��
    if (pMyShip->is_shooting_laser_ && VB_PLAY->isBeingPressed(VB_SHOT1)) {
        MyOptionWateringLaserChip001* pLaserChip = (MyOptionWateringLaserChip001*)pLaserChipDepo_->dispatch();
//        MyOptionStraightLaserChip001* pLaserChip = (MyOptionStraightLaserChip001*)pLaserChipDepo_->dispatch();

        if (pLaserChip) {
            if (pLaserChipDepo_->_pEffectActor_Irradiate) {
                pLaserChipDepo_->_pEffectActor_Irradiate->locatedBy(this);
            }
            //�X�g���[�g�p
//            pLaserChip->_pKurokoA->behave();
//            pLaserChip->_pKurokoB->behave();
//            pLaserChip->pOrg_ = this;
//            pLaserChip->activate();

              //�J�[�u�p
//            pLaserChip->_pKurokoA->_vX = Q._x;
//            pLaserChip->_pKurokoA->_vY = Q._y;
//            pLaserChip->_pKurokoA->_vZ = Q._z;
//            pLaserChip->_pKurokoA->_angRzMv = _RZ;
//            pLaserChip->_pKurokoA->_angRyMv = _RY;
////            pLaserChip->_pKurokoA->_angFace[AXIS_X] = _pKurokoA->_angFace[AXIS_X];
//            pLaserChip->_pKurokoA->_angFace[AXIS_Z] = _RZ;
//            pLaserChip->_pKurokoA->_angFace[AXIS_Y] = _RY;

            pLaserChip->_pKurokoB->setVxMvVelo(Q._x*pLaserChip->max_velo_renge_);
            pLaserChip->_pKurokoB->setVyMvVelo(Q._y*pLaserChip->max_velo_renge_);
            pLaserChip->_pKurokoB->setVzMvVelo(Q._z*pLaserChip->max_velo_renge_);
            pLaserChip->_pKurokoB->setVxMvAcce(Q._x*pLaserChip->max_velo_renge_/pLaserChip->r_max_acce_);
            pLaserChip->_pKurokoB->setVyMvAcce(Q._y*pLaserChip->max_velo_renge_/pLaserChip->r_max_acce_);
            pLaserChip->_pKurokoB->setVzMvAcce(Q._z*pLaserChip->max_velo_renge_/pLaserChip->r_max_acce_);
//            pLaserChip->_pKurokoA->behave();
            pLaserChip->_pKurokoB->behave();
            pLaserChip->_X = _X;
            pLaserChip->_Y = _Y;
            pLaserChip->_Z = _Z;
            pLaserChip->_RZ = _RZ;
            pLaserChip->_RY = _RY;
            pLaserChip->pOrg_ = this;

            if (pLaserChip->_pChip_front == NULL) {
                _pSeTx->play3D(0);
            }
        }
    } else {
        pLockonCtrlr_->releaseAllLockon();
    }
    if (pMyShip->just_shot_) {
        MyShot001* pShot = (MyShot001*)pDepo_MyShots001_->dispatch();
        if (pShot) {
            _pSeTx->play3D(1);
            pShot->locatedBy(this);
            pShot->_pKurokoA->_angFace[AXIS_X] = _RX;
            pShot->_pKurokoA->_angFace[AXIS_Z] = _RZ;
            pShot->_pKurokoA->_angFace[AXIS_Y] = _RY;
            pShot->_pKurokoA->setRzRyMvAng(_RZ, _RY);
        }
    }

    _pSeTx->behave();

}

void MyOption::processJudgement() {
}

void MyOption::onInactive() {
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����T�u�ɂ��邽��
    //�ʂɌĂяo��
    pLockonCtrlr_->onInactive();
    pTorpedoCtrlr_->onInactive();
    pLaserChipDepo_->reset();

}

void MyOption::onHit(GgafActor* prm_pOtherActor) {
    sayonara();
}

MyOption::~MyOption() {
}

