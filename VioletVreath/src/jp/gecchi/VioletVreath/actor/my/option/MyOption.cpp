#include "stdafx.h"
#include "MyOption.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/util/GgafDxQuaternion.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "MyOptionWateringLaserChip001.h"
#include "EffectMyOption.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShot001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

//MyOption::MyOption(const char* prm_name, uint32_t prm_no, MyOptionController* prm_pOptCtrler) : DefaultMorphMeshActor(prm_name, "4/Eres") {
//MyOption::MyOption(const char* prm_name, uint32_t prm_no, MyOptionController* prm_pOptCtrler) : CubeMapMeshSetActor(prm_name, "4/Core4cm_") {
MyOption::MyOption(const char* prm_name, uint32_t prm_no, MyOptionController* prm_pOptCtrler) :
        DefaultMeshSetActor(prm_name, "8/CORE4", STATUS(MyOption)) {

    _TRACE_("MyOption::MyOption("<<prm_name<<","<<prm_no<<")");
    _class_name = "MyOption";
    pOptionCtrler_ = prm_pOptCtrler;
    no_ = prm_no;
    angveloMove_ = 0;//����ړ��p���x�i�ǂݏo����p�j

    angPosition_ = 0;     //�~���㏉���ʒu�p�x�i���͊p�j�i�㏑�������ݒ�j
    veloMv_ = 5000;     //����ړ����x�i�㏑�������ݒ�j
    angExpanse_ = 0;      //�I�v�V�����̍L����p�̉�]�p�i�㏑�������ݒ�j

    adjust_angPos_seq_progress_ = 0;
    adjust_angPos_seq_new_angPosition_base_ = angPosition_;
    adjust_angPos_seq_spent_frame_ = 0;

    angPosition_base_ = angPosition_;
    radiusPosition_base_ = 150000; //�������a�����i�㏑�������ݒ�j
    radiusPosition_= radiusPosition_base_;
    radiusPosition_stopping_ = radiusPosition_base_;
    radiusPosition_velo_ = 3000 * (radiusPosition_base_/60000);

    angExpanse_default_ = angExpanse_;
    veloMv_base_ = veloMv_;

    return_to_base_radiusPosition_seq_ = false;
    return_to_base_angExpanse_seq_ = false;

    angveloExpanseNomal_ = 3000;
    angveloExpanseSlow_ = 1000;

    x_org_ = _x;
    y_org_ = _y;
    z_org_ = _z;

    //TODO::EffectMyOption
    pEffect_ = NEW EffectMyOption("EffectMyOption", this);
    addSubGroup(pEffect_);

    //���[�U�[���˃G�t�F�N�g
//    pEffect_LaserIrradiate_ = NEW EffectLockon001_Main("OP_Eff_Ref");
//    pEffect_LaserIrradiate_->inactivate();
//    addSubGroup(pEffect_LaserIrradiate_);
    pEffect_LaserIrradiate_ = nullptr;
    pLaserChipDepo_ = NEW LaserChipDepository("ROTLaser");
    MyOptionWateringLaserChip001* pChip;
//    MyOptionStraightLaserChip001* pChip;
    for (int i = 0; i < 80; i++) { //���[�U�[�X�g�b�N
        std::string name = std::string(getName()) + "'s LaserChip(" + XTOS(i) + ")";
        pChip = NEW MyOptionWateringLaserChip001(name.c_str());
        //pChip = NEW MyOptionStraightLaserChip001(name2.c_str());
        //MyOptionStraightLaserChip001�̏ꍇ�ȉ����K�v
        //�X�g���[�g�p
//        pChip->setSource(this);
//        pChip->pSource_vX_ = &Q._x;
//        pChip->pSource_vY_ = &Q._y;
//        pChip->pSource_vZ_ = &Q._z;

        pLaserChipDepo_->put(pChip);
    }
    pLaserChipDepo_->config(80, 25, pEffect_LaserIrradiate_);
    addSubGroup(pLaserChipDepo_);

    pDepo_MyShots001_ = NEW GgafActorDepository("RotShot001");
    for (int i = 0; i < 25; i++) { //���e�X�g�b�N
        std::string name = std::string(getName()) + "'s Shot001(" + XTOS(i) + ")";
        pDepo_MyShots001_->put(NEW MyShot001(name.c_str()));
    }
    addSubGroup(pDepo_MyShots001_);

    //���b�N�I���R���g���[���[
    pLockonCtrler_ = NEW MyLockonController("LockonController");
    addSubGroup(pLockonCtrler_);

    //�t�H�g���R���g���[���[
    pTorpedoCtrler_ = NEW MyTorpedoController("TorpedoController", this, pLockonCtrler_);
    addSubGroup(pTorpedoCtrler_);
    _pSeTx->set(SE_FIRE_LASER,   "WAVE_MY_FIRE_LASER_002");
    _pSeTx->set(SE_FIRE_SHOT,    "WAVE_MY_FIRE_SHOT_002");
    _pSeTx->set(SE_FIRE_TORPEDO, "WAVE_MY_FIRE_TORPEDO_002");
    //prepareSe(0,"bse5", GgafRepeatSeq::nextVal("CH_bse5"));
    need_adjust_pos_flg_ = false;
}

void MyOption::onCreateModel() {
//    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.3, 2.0);
//    _pModel->_pTexBlinker->setPower(1.0);
//    _pModel->_pTexBlinker->beat(120, 10, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void MyOption::initialize() {
    _sx=_sy=_sz=100;
}

void MyOption::onReset() {
    angveloMove_ = ((1.0f*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
    _pKurokoA->setMvVelo(veloMv_);
    _pKurokoA->setRzMvAng(angPosition_+D90ANG);
    _pKurokoA->setRyMvAng(-D90ANG);
    _pKurokoA->setRzMvAngVelo(angveloMove_);//�攼�a�q�����x�u�^�p���x��
    _pKurokoA->setRyMvAngVelo(0);//�攼�a�q�����x�u�^�p���x��
    _z = ANG_COS(angPosition_)*radiusPosition_; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
    _y = ANG_SIN(angPosition_)*radiusPosition_; //X���̐��̕����������Ď��v���ɔz�u
                                                //���[���h�ϊ��́i����@�j��X����]�Ƃ͂Ƌt�̉�]�Ȃ̂Œ���
    _x = 0;
    _pKurokoA->setFaceAngVelo(AXIS_X, 4000);
    //���[�J�����W�n���A(x_org_,y_org_,z_org_) �֑ޔ�
    x_org_ = _x;
    y_org_ = _y;
    z_org_ = _z;
    angPosition_ = _pKurokoA->_angRzMv;

    adjust_angPos_seq_progress_ = 0;
    adjust_angPos_seq_new_angPosition_base_ = angPosition_;
    adjust_angPos_seq_spent_frame_ = 0;

    radiusPosition_stopping_ = radiusPosition_base_;
}

void MyOption::onActive() {
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����T�u�ɂ��邽��
    //�ʂɌĂяo��
    pLockonCtrler_->onActive();
    pTorpedoCtrler_->onActive();
}

void MyOption::addRadiusPosition(int prm_radius_offset, int prm_min_radius, int prm_max_radius) {
    //    _x = x_org_;
    //    _y = y_org_;
    //    _z = z_org_;
    //����
    //    x_org_ = _x;
    //    y_org_ = _y;
    //    z_org_ = _z;
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
//    _x = x_org_;
//    _y = y_org_;
//    _z = z_org_;
//����
//    x_org_ = _x;
//    y_org_ = _y;
//    z_org_ = _z;
//���O
//�ł����Ăяo���Ă͂����܂���B
    radiusPosition_ = prm_radius;
    if (radiusPosition_ == -1  || radiusPosition_ == 0 || radiusPosition_ == 1) {
        _z = _y = 0;
        _pKurokoA->setRzMvAng(D90ANG);
        angveloMove_ = 0;
        _pKurokoA->setRzMvAngVelo(angveloMove_);
        return;

    }

    angle angZY_ROTANG_x;
    if (radiusPosition_ > 0) {
        angZY_ROTANG_x = UTIL::getAngle2D(_z, _y); //�����̈ʒu
        _z = radiusPosition_ * ANG_COS(angZY_ROTANG_x);
        _y = radiusPosition_ * ANG_SIN(angZY_ROTANG_x);
    } else {
        angZY_ROTANG_x = UTIL::getAngle2D(-_z, -_y); //�����̈ʒu
        _z = radiusPosition_ * ANG_COS(angZY_ROTANG_x);
        _y = radiusPosition_ * ANG_SIN(angZY_ROTANG_x);
    }
    //����prm_len��0�̏ꍇ�A���_�I�ɂ͌��̈ʒu�ɖ߂�͂��Ȃ̂����A
    //�덷�ۂߍ��݂̂��߁A�����Ɉʒu���ς��B
    //����āA�ړ����p�A�ړ��p���x�����݂̈ʒu(_z,_y)�ōĐݒ肵�Ȃ���΃Y����B
    _pKurokoA->setRzMvAng(angZY_ROTANG_x + D90ANG);
    angveloMove_ = ((1.0*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
    _pKurokoA->setRzMvAngVelo(angveloMove_);
}


void MyOption::adjustAngPosition(angle prm_new_angPosition_base, frame prm_spent_frame) {
    adjust_angPos_seq_progress_ = 1;
    adjust_angPos_seq_new_angPosition_base_ = UTIL::simplifyAng(prm_new_angPosition_base);
    adjust_angPos_seq_spent_frame_ = prm_spent_frame + 1;
}



void MyOption::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    VirtualButton* pVbPlay = VB_PLAY;
    GgafDxKurokoA* const pKurokoA = _pKurokoA;
    //�������C��

    //�ޔ����Ă������[�J�����W�n���A(x_org_,y_org_,z_org_) ��
    //_pKurokoA�̃��\�b�h�𗘗p���邽�߁A(_x,_y,_z)�փR�s�[
    //����ȍ~processBehavior()����(_x,_y,_z)�̓��[�J�����W�n
    _x = x_org_;
    _y = y_org_;
    _z = z_org_;

    if (return_to_base_radiusPosition_seq_) {
        //���a�|�W�V���������߂蒆
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
        if (pVbPlay->isBeingPressed(VB_OPTION) && pOptionCtrler_->is_handle_move_mode_) {
            //�I�v�V�����̍L����p���A�I�v�V�����ړ����x�ƁA���񔼌a�������x�Ƀx�N�g�������B
            //���̂����̐��񔼌a�������x�݂̂�ݒ�B
            addRadiusPosition(ANG_SIN(angExpanse_) * pOptionCtrler_->veloOptionsMv_);
            //�I�v�V�����ړ����x�̏�����MyOption�N���X�ōs���B
        }
    }

    if (return_to_base_angExpanse_seq_) {
        //�I�v�V�����L���莩���߂蒆
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
        angExpanse_ = UTIL::simplifyAng(angExpanse_);
    } else {
        //�I�v�V�����L����ƌ�������
        if (pVbPlay->isBeingPressed(VB_OPTION) && pVbPlay->isBeingPressed(VB_TURBO)) {
            int pos_camera = P_VAM->pos_camera_;
            if (pos_camera == VAM_POS_RIGHT) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    addRadiusPosition(radiusPosition_velo_);
                    radiusPosition_stopping_ += radiusPosition_velo_;
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-radiusPosition_velo_);
                    radiusPosition_stopping_ -= radiusPosition_velo_;
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            } else if (pos_camera == VAM_POS_LEFT) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    addRadiusPosition(radiusPosition_velo_);
                    radiusPosition_stopping_ += radiusPosition_velo_;
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-radiusPosition_velo_);
                    radiusPosition_stopping_ -= radiusPosition_velo_;
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            } else if (pos_camera == VAM_POS_TOP) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(radiusPosition_velo_);
                    radiusPosition_stopping_ += radiusPosition_velo_;
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(-radiusPosition_velo_);
                    radiusPosition_stopping_ -= radiusPosition_velo_;
                    //angExpanse_ -= angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
            } else if (pos_camera == VAM_POS_BOTTOM) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    addRadiusPosition(-radiusPosition_velo_);
                    radiusPosition_stopping_ -= radiusPosition_velo_;
                    //angExpanse_ -= angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    addRadiusPosition(radiusPosition_velo_);
                    radiusPosition_stopping_ += radiusPosition_velo_;
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
            } else if (pos_camera > VAM_POS_TO_BEHIND) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    angExpanse_ += angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    angExpanse_ -= angveloExpanseNomal_;
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    addRadiusPosition(radiusPosition_velo_);
                    radiusPosition_stopping_ += radiusPosition_velo_;
                    //angExpanse_ += angveloExpanseSlow_;
                }
                if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    addRadiusPosition(-radiusPosition_velo_);
                    radiusPosition_stopping_ -= radiusPosition_velo_;
                    //angExpanse_ -= angveloExpanseSlow_;
                }
            }

            if (radiusPosition_stopping_ < OPT_RADIUS_POS_MIN) {
                radiusPosition_stopping_ = OPT_RADIUS_POS_MIN;
            }
            if (radiusPosition_stopping_ > OPT_RADIUS_POS_MAX) {
                radiusPosition_stopping_ = OPT_RADIUS_POS_MAX;
            }
            angExpanse_ = UTIL::simplifyAng(angExpanse_);
        } else {
            if (pOptionCtrler_->is_free_from_myship_mode_) {
                //
            } else {
                GgafDxGeoElem* pGeoOpCtrl = pOptionCtrler_->pRing_OptCtrlGeoHistory_->getPrev();
                if (pVbPlay->isBeingPressed(VB_OPTION)) {
                    //�I�v�V�����{�^����������
                    //radiusPosition��������Ȃ�
                } else if (pGeoOpCtrl->x == pOptionCtrler_->_x &&
                           pGeoOpCtrl->y == pOptionCtrler_->_y &&
                           pGeoOpCtrl->z == pOptionCtrler_->_z )
                {
                    //�I�v�V�����R���g���[���[��ړ����A
                    //���̋O���ɖ߂邽�߂ɔ��a���W�𑝂₷�B
                    if (!pMyShip->is_trace_waiting_) {
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
                                if (need_adjust_pos_flg_) { //�ʒu�̍Đݒ�v������
                                    MyOptionController::adjustDefaltAngPosition(radiusPosition_stopping_ / 1000);
                                    need_adjust_pos_flg_ = false;
                                }
                                veloMv_ = veloMv_base_;
                            }
                        }
                    } else {
                        //�g���[�X������Ƒ҂�
                    }
                } else {
                    //�I�v�V�����R���g���[���[���ړ����A
                    //�I�v�V�����R���g���[���[�Ɍ������Ă����悤�ɁA���a���W�����炷�B
                    if (1 < radiusPosition_) {
                        addRadiusPosition(-3000, 1);
                    }
                    if (radiusPosition_ < 10000) { //���Ȃ蔼�a���������Ȃ��Ă��܂����ꍇ
                        need_adjust_pos_flg_ = true; //��ړ����Ɉʒu�̍Đݒ�v���i��������j
                    }

                    veloMv_ -= 200;
                    if (veloMv_ < 0) {
                        veloMv_ = 0;
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
            angle angPosition_now;
            //�����̊p�x�ʒu�擾
            if (radiusPosition_ > 0) {
                angPosition_now = UTIL::getAngle2D(_z, _y);
            } else {
                angPosition_now = UTIL::getAngle2D(-_z, -_y);
            }
            //���݂̊p����
            angle ang_diff = UTIL::getAngDiff(angPosition_now, adjust_angPos_seq_new_angPosition_base_, SGN(veloMv_));
            if (ABS(ang_diff) > D_ANG(350)) {
                ang_diff = UTIL::getAngDiff(angPosition_now, adjust_angPos_seq_new_angPosition_base_, TURN_CLOSE_TO);
            }
            //�c�t���[���Ǝc�ړ��p���K�v�Ȋp���x
            angvelo angvelo_need = ang_diff / (angvelo)adjust_angPos_seq_spent_frame_;
            //�K�v�Ȋp���x����
            angvelo angvelo_offset = angvelo_need - angveloMove_;
            //�K�v�Ȋp���x�����ɑΉ�����ړ����x�����߂�
            velo veloMv_offset =  (2.0*PI*radiusPosition_ * angvelo_offset) / D360ANG;
            //���x�ݒ�
            pKurokoA->setRzMvAngVelo(angveloMove_ + angvelo_offset);
            pKurokoA->setMvVelo(veloMv_ + veloMv_offset);
            adjust_angPos_seq_spent_frame_--;

            if (adjust_angPos_seq_spent_frame_ == 0) {
                angPosition_base_ = adjust_angPos_seq_new_angPosition_base_;
                //�덷�C���̂��ߗ��z�ʒu�ɍĐݒ�
                angveloMove_ = ((1.0*veloMv_ / radiusPosition_)*(double)D180ANG)/PI;
                pKurokoA->setMvVelo(veloMv_);
                pKurokoA->setRzMvAng(UTIL::simplifyAng(angPosition_base_ + D90ANG));
                pKurokoA->setRzMvAngVelo(angveloMove_);//�攼�a�q�����x�u�^�p���x��
                _z = ANG_COS(angPosition_base_)*radiusPosition_; //X�����S��]�Ȃ̂�XY�ł͂Ȃ���ZY
                _y = ANG_SIN(angPosition_base_)*radiusPosition_; //X���̐��̕����������Ď��v���ɔz�u
                _x = 0;
                adjust_angPos_seq_progress_ = 0;
            }
        }
    } else {
         //�ʏ펞
        pKurokoA->setMvVelo(veloMv_);
    }
    angPosition_ = UTIL::simplifyAng(angPosition_+angveloMove_);

    pKurokoA->behave();
    //pKurokoA���g���āA(_x,_y,_z)���[�J�����W�n�̌v�Z���ł����̂ŁA
    //(_x,_y,_z)�̃��[�J�����W�n���ʂ��A(x_org_,y_org_,z_org_) �ɏ㏑���R�s�[�ōX�V����B
    x_org_ = _x;
    y_org_ = _y;
    z_org_ = _z;

    //��������
    //�����܂łŁAGgafDxKurokoA�̋@�\�݂̂ŁA
    //�ȉ��̂悤�ȏ�Ԃ܂ł����Ă����B
    //(100,0,0) �ӂ肩�猴�_�������C���[�W�A���iMyOptionController�j�͌��_
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
    GgafDxKurokoA* const pOptionCtrler_pKurokoA = pOptionCtrler_->_pKurokoA;
    float sin_rz = ANG_SIN(pOptionCtrler_pKurokoA->_angFace[AXIS_Z]);
    float cos_rz = ANG_COS(pOptionCtrler_pKurokoA->_angFace[AXIS_Z]);
    float sin_ry = ANG_SIN(pOptionCtrler_pKurokoA->_angFace[AXIS_Y]);
    float cos_ry = ANG_COS(pOptionCtrler_pKurokoA->_angFace[AXIS_Y]);
    //�S�I�v�V��������̉�Ƃ���OptionController�𒆐S��WORLD�ϊ��̂悤�Ȑ���
    coord X = cos_ry*cos_rz*x_org_ + cos_ry*-sin_rz*y_org_ + sin_ry*z_org_;
    coord Y = sin_rz*x_org_ + cos_rz*y_org_;
    coord Z = -sin_ry*cos_rz*x_org_ + -sin_ry*-sin_rz*y_org_ + cos_ry*z_org_;


    //�����d���̏Ǝˊp���L����悤�ȉ�]�iQuaternion�Ŏ����j
    //��������
    //������W(x, y, z)�ɂ����āA��]�̎���(��, ��, ��)�ŁA�Ɖ񂷉�]�������Ƃ̍��W�����߂�B
    //P,Q,R ���l�����i�x�N�g���\���j�Ƃ����A
    //P = (0; x, y, z)
    //Q = (cos(��/2);  �� sin(��/2),  �� sin(��/2),  �� sin(��/2))
    //R = (cos(��/2); -�� sin(��/2), -�� sin(��/2), -�� sin(��/2))
    //�Ƃ������A�n�~���g����
    //R P Q = (0; ����)
    //�������ƂȂ�

    //������W(x, y, z)�������x�N�g��(pOptionCtrler_pKurokoA->_vX,pOptionCtrler_pKurokoA->_vY,pOptionCtrler_pKurokoA->_vZ)
    //��]��  (��, ��, ��)=(vX_axis, vY_axis, vZ_axis) �A
    //��]�p��= angExpanse_
    float vX_axis = cos_ry*cos_rz*pKurokoA->_vX + cos_ry*-sin_rz*pKurokoA->_vY + sin_ry*pKurokoA->_vZ;
    float vY_axis = sin_rz*pKurokoA->_vX + cos_rz*pKurokoA->_vY;
    float vZ_axis = -sin_ry*cos_rz*pKurokoA->_vX + -sin_ry*-sin_rz*pKurokoA->_vY + cos_ry*pKurokoA->_vZ;
    float sinHalf = ANG_SIN(angExpanse_/2); //angExpanse_=��]���������p�x
    float cosHalf = ANG_COS(angExpanse_/2);

    GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf); //R
    Q.mul(0,
          pOptionCtrler_pKurokoA->_vX,
          pOptionCtrler_pKurokoA->_vY,
          pOptionCtrler_pKurokoA->_vZ); //R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
    Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
    //Q._x, Q._y, Q._z ����]��̍��W�ƂȂ�
    //Z����]�AY����]�p�x���v�Z
    UTIL::convVectorToRzRy(Q._x, Q._y, Q._z, _rz, _ry);

    //�ŏI�I�ɂ�(_x,_y,_z)�ɐ�΍��W�n�̍��W�l�ɍX�V�B
    _x = X + pOptionCtrler_->_x;
    _y = Y + pOptionCtrler_->_y;
    _z = Z + pOptionCtrler_->_z;
    //���Ȃ݂Ƀ��[�J�����W�n���ʂ́A(x_org_,y_org_,z_org_)


    //���[�U�[���ˁBTODO:�œK��
    if (pMyShip->is_shooting_laser_ && pVbPlay->isBeingPressed(VB_SHOT1)) {
        MyOptionWateringLaserChip001* pLaserChip = (MyOptionWateringLaserChip001*)pLaserChipDepo_->dispatch();
        if (pLaserChip) {
//            if (pLaserChipDepo_->_pEffectActor_Irradiate) {
//                pLaserChipDepo_->_pEffectActor_Irradiate->positionAs(this);
//            }
            //�J�[�u�p
            int max_velo_renge = pLaserChip->max_velo_renge_;
            int r_max_acce = pLaserChip->r_max_acce_;
            velo veloVx = Q._x*max_velo_renge;
            velo veloVy = Q._y*max_velo_renge;
            velo veloVz = Q._z*max_velo_renge;
            pLaserChip->_pKurokoB->setVxyzMvVelo(veloVx, veloVy, veloVz);
            pLaserChip->_pKurokoB->setVxyzMvAcce(veloVx / r_max_acce,
                                                 veloVy / r_max_acce,
                                                 veloVz / r_max_acce );
            pLaserChip->_pKurokoB->behave();

            pLaserChip->positionAs(this);
            pLaserChip->_rz = _rz;
            pLaserChip->_ry = _ry;
            pLaserChip->pOrg_ = this;

            if (pLaserChip->_pChip_front == nullptr) {
                _pSeTx->play3D(SE_FIRE_LASER);
            }
        }
    } else {
        pLockonCtrler_->releaseAllLockon(); //���b�N�I������
    }

    //�V���b�g����
    if (pMyShip->just_shot_) {
        MyShot001* pShot = (MyShot001*)pDepo_MyShots001_->dispatch();
        if (pShot) {
            GgafDxKurokoA* const pShot_pKurokoA = pShot->_pKurokoA;
            _pSeTx->play3D(SE_FIRE_SHOT);
            pShot->positionAs(this);
            pShot_pKurokoA->setFaceAng(_rx, _ry, _rz);
            pShot_pKurokoA->setRzRyMvAng(_rz, _ry);
        }
    }
    //���q��������
    if (pVbPlay->isPushedDown(VB_SHOT2)) {
        if (pTorpedoCtrler_->fire()) {
            _pSeTx->play3D(SE_FIRE_TORPEDO);
        }
    }
//    _pSeTx->behave();

//    if (no_ == 3 ) {
//        if (_pKurokoA->_angveloRzMv == 0 || _pKurokoA->_angveloRzMv == 360000) {
//            if (veloMv_ == 1000) {
//                if (radiusPosition_ == 1) {
//                    _TRACE_(getBehaveingFrame()<<":before �������鐬���I�I�I");
//                }
//            }
//
//        }
//        _TRACE_(getBehaveingFrame()<<":after  radiusPosition_="<<radiusPosition_<<" radiusPosition_stopping_="<<radiusPosition_stopping_<<" _angveloRzMv="<<(_pKurokoA->_angveloRzMv)<<" veloMv_="<<veloMv_);
//    }

}

void MyOption::processJudgement() {
}

void MyOption::onInactive() {
    //���[�U�[�⃍�b�N���^�[�Q�b�g�⋛�����T�u�ɂ��邽��
    //�ʂɌĂяo��
    pLockonCtrler_->onInactive();
    pTorpedoCtrler_->onInactive();
    //pLaserChipDepo_->reset();
}

void MyOption::onHit(GgafActor* prm_pOtherActor) {
    sayonara();
}

MyOption::~MyOption() {
}



//�I�u�V�����ɂ��Ĕ��Y�^2013/10/21
//���@(MyShip) -> �I�v�V�����R���g���[���[(MyOptionController) x 9
//                       ���ꂼ��̃R���g���[���[�� �I�v�V����(MyOption)
//����{���쁄
//���@�̓O���f�B�E�X�I�v�V�����g���[�X�̓������I�v�V�����R���g���[���[�ɂ��čs���Ă���B
//�I�v�V�����́A�I�v�V�����R���g���[���[��(0,0,0)�̎��������O���ŉ���Ă���B
//�I�v�V��������O���̔��a�̋����́A�I�v�V�����R���g���[���[���ړ�����ƒZ���Ȃ�B
//�I�v�V�����R���g���[���[���ړ���������ƁA�I�v�V�����R���g���[���[��(0,0,0)
//�t�߂Œ�~���Ă���悤�Ɍ�����قǔ��a���������Ȃ�B
//�I�v�V�����R���g���[���[��~����ƁA�I�v�V�����͌��̔��a�̋����ɖ߂낤�Ƃ���B




