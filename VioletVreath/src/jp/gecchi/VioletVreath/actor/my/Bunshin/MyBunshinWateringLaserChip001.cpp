#include "MyBunshinWateringLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/NaviVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/LockonCursor001_Main.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"

using namespace GgafLib;
using namespace VioletVreath;

const velo MyBunshinWateringLaserChip001::MAX_VELO = PX_C(512); //���̒l��傫������ƁA�ō����x�������Ȃ�B
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 18; //MAX_VELO �ɑ΂�������x�A���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�
const velo MyBunshinWateringLaserChip001::INITIAL_VELO = MAX_VELO*0.6; //���[�U�[���ˎ��̏������x
const acce MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO/R_MAX_ACCE;
const velo MyBunshinWateringLaserChip001::MIN_VELO_ = MyBunshinWateringLaserChip001::INITIAL_VELO/4; // ��4 �́A�Œ�ړ�����e����INITIAL_VELO�̊���
GgafDx::Model* MyBunshinWateringLaserChip001::pModel_ = nullptr;
int MyBunshinWateringLaserChip001::tex_no_ = 0;

enum {
    PHASE_T1,
    PHASE_T2,
    PHASE_T2_AFTER ,
    PHASE_BANPEI,
};


MyBunshinWateringLaserChip001::MyBunshinWateringLaserChip001(const char* prm_name) :
        VvMyActor<WateringLaserChip>(prm_name, "MyLaserChip001", StatusReset(MyBunshinWateringLaserChip001)) {
    _class_name = "MyBunshinWateringLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    pOrg_ = nullptr;
    pLockonCursor_ = nullptr;
    is_lockon_ = false;
    GgafDx::Model* pModel = getModel();
    if (!MyBunshinWateringLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwCriticalException("MyBunshinWateringLaserChip001���f���́A�e�N�X�`���i�}�e���A���j��"<<MAX_LASER_LEVEL<<"�K�v�ł��B");
        }
        MyBunshinWateringLaserChip001::pModel_ = pModel;
    }
    sgn_vx0_ = 0;
    sgn_vy0_ = 0;
    sgn_vz0_ = 0;
    pLeaderChip_AimInfo_ = nullptr;
    inv_cnt_ = 0;
}

void MyBunshinWateringLaserChip001::initialize() {
    getLocoVehicle()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(MAX_VELO/4); //���x�ɉ����đ傫����ω�
    setHitAble(true);
    setScaleR(6.0);
    setCullingDraw(false);
}

void MyBunshinWateringLaserChip001::onCreateModel() {

}

void MyBunshinWateringLaserChip001::setOrg(MyBunshin* prm_pOrg) {
    pOrg_ = prm_pOrg;
    pLockonCursor_ = pOrg_->pLockonCtrler_->pMainLockonCursor_;
}

void MyBunshinWateringLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    VvMyActor<WateringLaserChip>::onActive();
    pLeaderChip_AimInfo_ = nullptr;
    inv_cnt_ = 0;
    sgn_vx0_ = 0;
    sgn_vy0_ = 0;
    sgn_vz0_ = 0;
    GgafDx::NaviVehicle* pNaviVehicle = getNaviVehicle();
    pNaviVehicle->forceVeloRange(MIN_VELO_*_n_dispatch_at_once, MAX_VELO*_n_dispatch_at_once);
    pNaviVehicle->forceAcceRange(0, MAX_ACCE_RENGE*_n_dispatch_at_once);
    getPhase()->reset(PHASE_T1);
}

void MyBunshinWateringLaserChip001::processBehavior() {
    frame active_frame = getActiveFrame();
    double power = active_frame <= 300 ? UTIL::SHOT_POWER[active_frame] : UTIL::SHOT_POWER[300];
    getStatus()->set(STAT_AttackPowerRate, power);
    _power = power;
    AimInfo* pLeaderChip_AimInfo = pLeaderChip_AimInfo_;

    if (getActiveFrame() >= 60*10) {
        sayonara(); //�ی��̃^�C���A�E�g10�b
    } else if (pLeaderChip_AimInfo == nullptr || active_frame < 4) {
        //�Ȃɂ����Ȃ�
    } else {
        GgafDx::GeometricActor* pAimTarget = pLeaderChip_AimInfo->pTarget;
        if (!(pAimTarget && pAimTarget->isActiveInTheTree()) ) {
            pLeaderChip_AimInfo->pTarget = nullptr;
        }

        if (pLeaderChip_AimInfo->pTarget == nullptr) {
            if (pLeaderChip_AimInfo->aim_time_out_t1 == 0) {
                //�Ȃɂ����Ȃ�
            } else {
                processBehavior_Aiming();
            }
        } else {
            processBehavior_Aiming();
        }
    }

    getNaviVehicle()->behave();
    VvMyActor<WateringLaserChip>::processBehavior();
}

void MyBunshinWateringLaserChip001::processBehavior_Aiming() {
    static const Spacetime* pSpaceTime =  pCARETAKER->getSpacetime();
    static const double ZF_R = pSpaceTime->_x_bound_right - pSpaceTime->_x_bound_left;
    frame active_frame = getActiveFrame();

    GgafDx::NaviVehicle* pNaviVehicle = getNaviVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
         case PHASE_T1: {
            if (getInfrontChip() == nullptr) {
                //��[�`�b�v
                if (this != pLeaderChip_AimInfo_->pLeaderChip) {
                    //��[�`�b�v�Ȃ̂Ƀ��[�_����Ȃ��E�E�E����
                    //pLeaderChip_AimInfo_ �� AimInfo �R�s�[�V�K�ō쐬�BAimInfo�Q�ƃ`�F�[����ؒf
                    pLeaderChip_AimInfo_ = getNewAimInfoCopy(pLeaderChip_AimInfo_);
                    pLeaderChip_AimInfo_->pLeaderChip = this; //���[�_�[��
                }
            }
            AimInfo* pLeaderChip_AimInfo = pLeaderChip_AimInfo_;
            if (this == pLeaderChip_AimInfo->pLeaderChip) {
                //���[�_�[�`�b�v�̏ꍇ
                GgafDx::GeometricActor* pAimTarget = pLeaderChip_AimInfo->pTarget;
                if (pAimTarget) {
                    //�^�[�Q�b�g�����Ȃ��T1���W�X�V
                    pLeaderChip_AimInfo->updateT1(pAimTarget->_x, pAimTarget->_y, pAimTarget->_z);  //t1�X�V
                    //T1���W�̂�����Ɩ����̍��W������ t1_ahead �ɐݒ�
                    coord aim_t1_x = pLeaderChip_AimInfo->t1_x;
                    coord aim_t1_y = pLeaderChip_AimInfo->t1_y;
                    coord aim_t1_z = pLeaderChip_AimInfo->t1_z;
                    coord ahead_vx = aim_t1_x - pLeaderChip_AimInfo->t1_x_prev;
                    coord ahead_vy = aim_t1_y - pLeaderChip_AimInfo->t1_y_prev;
                    coord ahead_vz = aim_t1_z - pLeaderChip_AimInfo->t1_z_prev;
                    if (ahead_vx == 0 &&  ahead_vy == 0 && ahead_vz == 0) {
                        pLeaderChip_AimInfo->setT1Ahead(aim_t1_x, aim_t1_y, aim_t1_z);
                    } else {
                        double out_ahead_nvx, out_ahead_nvy, out_ahead_nvz;
                        UTIL::getNormalizedVector(ahead_vx, ahead_vy, ahead_vz,
                                                  out_ahead_nvx, out_ahead_nvy, out_ahead_nvz);
                        //�q�b�gBOX �����炷
                        static coord d_f = _hitarea_edge_length; //_hitarea_edge_length/2;
                        pLeaderChip_AimInfo->setT1Ahead(aim_t1_x + out_ahead_nvx*d_f,
                                                        aim_t1_y + out_ahead_nvy*d_f,
                                                        aim_t1_z + out_ahead_nvz*d_f);
                    }
                } else {
                    //�^�[�Q�b�g���������ꍇ
                    pLeaderChip_AimInfo->pTarget = nullptr;
                }
            } else {
                //���[�_�[�`�b�v�ȊO�A��[�`�b�v�ȊO
                //T1Ahead ���K������͂�
            }

            if (pLeaderChip_AimInfo->aim_time_out_t1 <= active_frame) {
                //T1 �^�C���A�E�g�ŏI��
                //_TRACE_("aimChip("<<pLeaderChip_AimInfo->t1_ahead_x<<","<<pLeaderChip_AimInfo->t1_ahead_y<<","<<pLeaderChip_AimInfo->t1_ahead_z<<") this=(" << _x << "," << _y << "," << _z << ") name="<<getName()<<"@"<<getActiveFrame()<<" T1 �^�C���A�E�g �� done!!");
                pPhase->changeImmediately(PHASE_T2);
                goto L_PHASE_T2;
            }
            //T1Ahead�iT1������Ɩ����j��Aim
            bool is_done = aimChip(pLeaderChip_AimInfo->t1_ahead_x,
                                   pLeaderChip_AimInfo->t1_ahead_y,
                                   pLeaderChip_AimInfo->t1_ahead_z,
                                   true);
            if (is_done) {
                //T1Ahead �ɏՓˁA���邢�́A�ʂ�߂��ŏI��
                if (pLeaderChip_AimInfo->aim_time_out_t1 > active_frame) {
                    //���߂��Ȃ瑁�߂悤���E�E�E
                    pLeaderChip_AimInfo->aim_time_out_t1 = active_frame;
                }
                pPhase->changeImmediately(PHASE_T2);
                goto L_PHASE_T2;
            }

            break;
         }

L_PHASE_T2:
         case PHASE_T2: {
             AimInfo* pLeaderChip_AimInfo = pLeaderChip_AimInfo_;
             if (pPhase->hasJustChanged() ) {
                 if (pLeaderChip_AimInfo->aim_time_out_t2 == 0) {
                     //T2 ���ݒ肾�����ꍇ�AT2 �̍��W�ݒ�ƊT�Z�����߂�

//                     LaserChip* pB = getBehindChip();
//                     if (pB) { pB = pB->getBehindChip(); if (pB) {  pB = pB->getBehindChip(); }  }
//                     if (pB) {
//                         pLeaderChip_AimInfo->setT2BySphere(ZF_R, pB->_x, pB->_y, pB->_z, _x, _y, _z);
//                     } else {
//                         pLeaderChip_AimInfo->setT2BySphere(ZF_R, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
//                     }

                     LaserChip* pB = getBehindChip();
                     if (pB) { pB = pB->getBehindChip(); if (pB) {  pB = pB->getBehindChip(); }  }
                     if (pB) {
                         GgafDx::NaviVehicle* pB_pNaviVehicle = pB->getNaviVehicle();

//                         velo vx = pNaviVehicle->_velo_vc_x*2 - pB_pNaviVehicle->_velo_vc_x;
//                         velo vy = pNaviVehicle->_velo_vc_y*2 - pB_pNaviVehicle->_velo_vc_y;
//                         velo vz = pNaviVehicle->_velo_vc_z*2 - pB_pNaviVehicle->_velo_vc_z;

//                         pLeaderChip_AimInfo->setT2BySphere(
//                                                ZF_R,
//                                                _x, _y, _z,
//                                                vx, vy, vz
//                                              );


                         pLeaderChip_AimInfo->setT2BySphere(
                                                ZF_R,
                                                _x, _y, _z,
                                                _x + pB_pNaviVehicle->_acce_vc_x,
                                                _y + pB_pNaviVehicle->_acce_vc_y,
                                                _z + pB_pNaviVehicle->_acce_vc_z
                                              );

                     } else {
                         pLeaderChip_AimInfo->setT2BySphere(
                                                ZF_R,
                                                _x, _y, _z,
                                                _x + pNaviVehicle->_velo_vc_x,
                                                _y + pNaviVehicle->_velo_vc_y,
                                                _z + pNaviVehicle->_velo_vc_z
                                              );
                     }
                     coord t2_d = UTIL::getDistance(_x, _y, _z,
                                                    pLeaderChip_AimInfo->t2_x,
                                                    pLeaderChip_AimInfo->t2_y,
                                                    pLeaderChip_AimInfo->t2_z);
                     pLeaderChip_AimInfo->aim_time_out_t2 =
                             active_frame + (frame)(t2_d/(MyBunshinWateringLaserChip001::MAX_VELO*_n_dispatch_at_once)); //T2���B���ԊT�Z
                 }
             }
             if (pLeaderChip_AimInfo->aim_time_out_t2 <= active_frame) {
                 //T2 �I�����̏���
                 pPhase->changeImmediately(PHASE_T2_AFTER);
                 goto L_PHASE_T2_AFTER;
             }
             aimChip(pLeaderChip_AimInfo->t2_x,
                     pLeaderChip_AimInfo->t2_y,
                     pLeaderChip_AimInfo->t2_z );
             break;
         }

L_PHASE_T2_AFTER:
         case PHASE_T2_AFTER: {
             //isOutOfSpacetime() ���������邩�A�ی��̃^�C���A�E�g10�b �܂�
             aimChip(_x + pNaviVehicle->_velo_vc_x*10+1,
                     _y + pNaviVehicle->_velo_vc_y*10+1,
                     _z + pNaviVehicle->_velo_vc_z*10+1 );
             break;
         }
         default: {
             break;
         }
     }
}

void MyBunshinWateringLaserChip001::processSettlementBehavior() {
    //���g��FK�Ȃ̂ŁA��΍��W�̊m�肪 processSettlementBehavior() �ȍ~�ƂȂ邽�߁A�����ŏ����ݒ肪�K�v
    GgafDx::NaviVehicle* const pNaviVehicle = getNaviVehicle();
    if (hasJustChangedToActive()) {
        //�`�b�v�̏����ݒ�
        //�����J�n����t���[���A�`�b�v�̑��x�ƌ����̏����ݒ�
        setFaceAngAs(pOrg_);
        //setPositionAt(pOrg_);
        pNaviVehicle->setVeloTwd(_rz, _ry, INITIAL_VELO*_n_dispatch_at_once); //�����͂�����
        pNaviVehicle->setAcceZero();
        int n = _n_dispatch_at_once-1 - _dispatch_index;
        if (n == 0) {
            setPositionAt(pOrg_);
        } else {
//            setPosition(pOrg_->_x + ((pNaviVehicle->_velo_vc_x/_n_dispatch_at_once) * n) ,
//                        pOrg_->_y + ((pNaviVehicle->_velo_vc_y/_n_dispatch_at_once) * n) ,
//                        pOrg_->_z + ((pNaviVehicle->_velo_vc_z/_n_dispatch_at_once) * n) );
            double v = 1.0*n / _n_dispatch_at_once;
            setPosition(pOrg_->_x + (pNaviVehicle->_velo_vc_x * v) ,
                        pOrg_->_y + (pNaviVehicle->_velo_vc_y * v) ,
                        pOrg_->_z + (pNaviVehicle->_velo_vc_z * v) );
        }

        //���b�N�I�����̈����p��
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getInfrontChip();
        if (pF == nullptr) {
            //��[�`�b�v
            GgafDx::GeometricActor* pLockonTarget = pLockonCursor_->pTarget_;
            if (pLockonTarget && pLockonTarget->isActiveInTheTree()) {
                //��[�Ń��b�N�I����
                pLeaderChip_AimInfo_ = getNewAimInfo();
                pLeaderChip_AimInfo_->pLeaderChip = this;
                pLeaderChip_AimInfo_->pTarget = pLockonTarget;
                pLeaderChip_AimInfo_->setT1_and_T1Ahead(
                        pLeaderChip_AimInfo_->pTarget->_x,
                        pLeaderChip_AimInfo_->pTarget->_y,
                        pLeaderChip_AimInfo_->pTarget->_z);
                // aim_time_out_t1 ���T�Z�ŋ��߂Ă���
                dxcoord x = C_DX(_x);
                dxcoord y = C_DX(_y);
                dxcoord z = C_DX(_z);
                dxcoord tx = C_DX(pLockonTarget->_x);
                dxcoord ty = C_DX(pLockonTarget->_y);
                dxcoord tz = C_DX(pLockonTarget->_z);
                D3DXVECTOR3 V(tx-x, ty-y, tz-z);
                D3DXVECTOR3 W(C_DX(pNaviVehicle->_velo_vc_x), C_DX(pNaviVehicle->_velo_vc_y), C_DX(pNaviVehicle->_velo_vc_z));
                float rad = UTIL::get3DRadAngle(V, W); //�����p
                double rate_estimate = RCNV(0.0, PI, rad, 1.0, 4.0); //�����ɋ߂���� 1.0 �` �^�t 4.0
                coord t1_d = UTIL::getDistance(this, pLockonTarget);
                //�������������x �Ɋ������悶�āA���B���Ԃ��T�Z�Ō��ς���B
                pLeaderChip_AimInfo_->aim_time_out_t1 = getActiveFrame() + ((t1_d / pNaviVehicle->_velo) * rate_estimate);
            } else {
                //��[�Ń��b�N�I�����Ă��Ȃ�
                pLeaderChip_AimInfo_ = getNewAimInfo();
                pLeaderChip_AimInfo_->pLeaderChip = this;
                pLeaderChip_AimInfo_->pTarget = nullptr;
                pLeaderChip_AimInfo_->aim_time_out_t1 = 0;
            }
        } else {
            //��[�ȊO�͑O�̃��[�U�[�`�b�v�̂��󂯌p��
            pLeaderChip_AimInfo_ = pF->pLeaderChip_AimInfo_; //�Q��
#ifdef MY_DEBUG
if (pLeaderChip_AimInfo_ == nullptr) {
throwCriticalException("pLeaderChip_AimInfo_ �������p����Ă��܂���I"<<this<<
                       " _frame_of_life_when_activation="<<_frame_of_life_when_activation);
}
#endif
        }

    }

    //���ϋȐ����W�ݒ�B(���[�U�[�����炩�ɂ���m�[�}���C�Y�j
    //processSettlementBehavior() �̃��\�b�h�̈Ӌ`�Ƃ͗���č��W��������ړ����Ă���B
    //�{���� processBehaviorAfter() �I�ȈӖ��̏����ł��邪�A�S���[�U�[�`�b�v���ړ���łȂ��ƈӖ����Ȃ��̂�
    //�d���Ȃ��̂�processSettlementBehavior()�ɐH������ł��܂��B
    //���������Ė{�N���X���p�������ꍇ�A�p���N���X��processSettlementBehavior()�ł́A�擪�ŌĂяo���������ǂ��B

    MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
    if (getActiveFrame() > 2) {//FK�I�u�W�F�N�g����̃��[�U�[���˂��l������ƁA_tmpXYZ �����܂�̂�3�t���[���ȍ~�B
        if (pF && pF->isActive()) {
            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB && pB->isActive()) {
                //_pChip_behind == nullptr �̔��肾���ł͂��߁B_pChip_behind->_is_active_flg �Ɣ��肷�邱��
                //�Ȃ��Ȃ� dispatch �̏u�Ԃ�_pChip_behind != nullptr �ƂȂ邪�Aactive()�ɂ��L���ɂȂ�͎̂��t���[��������
                //_x,_y,_z �ɂ͂܂��ςȒl�������Ă���B
                //���ԍ��W�ɍĐݒ�
                //���W�̏d�݂́A�i�ЂƂO, ���g, ���j�� (0.2, 0.3, 0.4)
                _x = _x + (coord)((pB->_x-_x)*0.2 + (pF->_x-_x)*0.4);
                _y = _y + (coord)((pB->_y-_y)*0.2 + (pF->_y-_y)*0.4);
                _z = _z + (coord)((pB->_z-_z)*0.2 + (pF->_z-_z)*0.4);
            } else {
                //���[�U�[�������͂˂�i���̖т��͂˂�݂����ɂȂ�j�̂��኱�h��
                //��O�̍��W�ƁA���g�̍��W�𒼐��Ō���ŁA���z�̎����̌��̓_���쐬�B
                //��O�̍��W�A���g�̍��W�A���z�̎����̌��̓_�ŕ��ς����
                //���W�̏d�݂́A�i���z�̂ЂƂO, ���g(����), ���j�� (0.2, 0.3, 0.4)
                coord v_b_x = _x - (pF->_x - _x);
                coord v_b_y = _y - (pF->_y - _y);
                coord v_b_z = _z - (pF->_z - _z);
                _x = _x + (coord)((v_b_x-_x)*0.2 + (pF->_x-_x)*0.4);
                _y = _y + (coord)((v_b_y-_y)*0.2 + (pF->_y-_y)*0.4);
                _z = _z + (coord)((v_b_z-_z)*0.2 + (pF->_z-_z)*0.4);
            }
        }

        if (pF) {
            setFaceAngTwd(pF);
        } else {
            //���[�U�[�`�b�v�̌������ړ������ɐݒ�i��[�`�b�v�j
            UTIL::convVectorToRzRy(pNaviVehicle->_velo_vc_x,
                                   pNaviVehicle->_velo_vc_y,
                                   pNaviVehicle->_velo_vc_z,
                                   _rz, _ry );
        }

    }
    VvMyActor<WateringLaserChip>::processSettlementBehavior();
}

void MyBunshinWateringLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        if (pLeaderChip_AimInfo_->pLeaderChip == this) {
            //T2�����c���Ă���
            pLeaderChip_AimInfo_->setT2(_x, _y, _z);
            pLeaderChip_AimInfo_->aim_time_out_t2 = getActiveFrame();
            if (pLeaderChip_AimInfo_->aim_time_out_t1 == 0) {
                pLeaderChip_AimInfo_->setT1_and_T1Ahead(pLeaderChip_AimInfo_->t2_x, pLeaderChip_AimInfo_->t2_y, pLeaderChip_AimInfo_->t2_z);
                pLeaderChip_AimInfo_->aim_time_out_t1 = getActiveFrame();
            }
        }
        sayonara();
    }
}

bool MyBunshinWateringLaserChip001::aimChip(int tX, int tY, int tZ, bool chk_done) {
    //    |                               ���I    ��
    //    |                                ��    vVT(vVTx,vVTy,vVTz)
    //    |                                ^ �_
    //    |                                |   �_
    //    |                                |     �c                                                 |
    //    |                                |       |d|*7                                            |
    //    |                                |         �c                                             |
    //    |                                |           �_                      ��                   |
    //    |                                |              �I  ���W(tX,tY,tZ)�� vT(vTx,vTy,vTz)      |      ���I
    //    |                                |             ^ ��        ��    ��                       |       ��
    //    |                                |            /    �_ |d|= vT - vVM                       |       �I    ^
    //    |                                |           /       �_       ��                          |       ��    |
    //    |                                |          /         ������ vVM(vVMx,vVMy,vVMz)          |      ����   |      ^
    //    |                                |    |vT| /        �^                                    |       ��    |      |
    //    |                                |        /       �^                                      |       �b    |      |
    //    |                                |       /      �^                                        |       �b    ||vT|  ||vT|*0.9
    //    |                                |      /     �^          *0.9�̈Ӗ��͉E�}�̂悤�ɒ�����  |       �b    |      |
    //    |                                |     /    �^ |vT|*0.9   ���񂾍ۂɉ��� �� �I ��ǂ�     |       �b    |      |
    //    |                                |    /   �^              �z���Ȃ��悤�ɂ��邽��          |       �b    |      |
    //    |        �ݒ肳�������x�̕���  |   /  �^                                                |       �b    |      |
    //    |   setAcceByVc(vVTx,vVTy,vVTz)  ^  / �� ���݂̈ړ������x�N�g��NaviVehicle                |       ��    v      v
    //    |�����\�b�h����MAX_ACCE_RENGE    | /�^ (_velo_vc_x,_velo_vc_x,_velo_vc_z)                 |
    //    |  �͈͂ɒ��������              ��                                                    ---+---------------------------
    //    |                      ���W(_x,_y,_z)=�x�N�g���̊�_(0,0,0)                               |
    // ---+------------------------------------------
    GgafDx::NaviVehicle* pNaviVehicle = getNaviVehicle();
    //�����I�A�����x�N�g�� (��vT)
    coord vTx = tX - _x;
    coord vTy = tY - _y;
    coord vTz = tZ - _z;
    //|vT|
    coord lvT = UTIL::getDistanceFromOrigin(vTx, vTy, vTz);
    double ve = pNaviVehicle->_velo;
    //��������  (��vVM)
    coord vVMx = lvT * (pNaviVehicle->_velo_vc_x / ve)*0.9;
    coord vVMy = lvT * (pNaviVehicle->_velo_vc_y / ve)*0.9;
    coord vVMz = lvT * (pNaviVehicle->_velo_vc_z / ve)*0.9;
    //���������I*10�A((��vT) - (��vVM))*8  ��������I������1�Ƃ��āA�I���狗��7�ꏊ
    coord vVTx = (vTx - vVMx)*8;
    coord vVTy = (vTy - vVMy)*8;
    coord vVTz = (vTz - vVMz)*8;
    //�������I �։����x�ݒ�i�����\�b�h���� MAX_ACCE_RENGE �͈͂ɒ��������j
    pNaviVehicle->setAcceByVc(vVTx, vVTy, vVTz);

    if (chk_done) {
        //�Փ˂�����I��
        if (lvT < _hitarea_edge_length) {
//		if (lvT< MyBunshinWateringLaserChip001::MAX_VELO) {
            //���߂�
            //_TRACE_("aimChip("<<tX<<","<<tY<<","<<tZ<<") this=(" << _x << "," << _y << "," << _z << ") name="<<getName()<<"@"<<getActiveFrame()<<" BOXHIT �� done!!");
            return true;
        }
        //�^�[�Q�b�g�̕t��(pNaviVehicle->_top_velo*2)�ŁA���ς����̏ꍇ�A�^�[�Q�b�g��ɂ������ʂ�z���Ă��܂����ƍl�����Ȃ����낤���B
        //���̏ꍇ�́A���߂Ė߂��Ă��Ăق����Ȃ��B
        if (lvT < _hitarea_edge_length*3)  { //pNaviVehicle->_top_velo*2) {
            //�����̑��x�����x�N�g���ƁA�^�[�Q�b�g�ւ̕����x�N�g���̓��ρi�x�N�g���̈Ⴂ��j���v�Z���A
            //Aim ����߂邩�ǂ����̔��f�Ɏg�p����B
            //�����̑��x�����x�N�g��
            velo velo_vc_x = pNaviVehicle->_velo_vc_x;
            velo velo_vc_y = pNaviVehicle->_velo_vc_y;
            velo velo_vc_z = pNaviVehicle->_velo_vc_z;
            //�^�[�Q�b�g�ւ̕����x�N�g��  vTx, vTy, vTz
            //����
            coord dot = velo_vc_x*vTx + velo_vc_y*vTy + velo_vc_z*vTz;
            if (dot < 0) {
                //���߂�
                //_TRACE_("aimChip("<<tX<<","<<tY<<","<<tZ<<") this=(" << _x << "," << _y << "," << _z << ") name="<<getName()<<"@"<<getActiveFrame()<<" dot �� done!!");
                return true;
            }
        }
    }
    return false;
}

void MyBunshinWateringLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*) prm_pOtherActor;
    //�q�b�g�G�t�F�N�g
    GgafDx::FigureActor* pE = UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g�o��
    GgafDx::CollisionPart* pColliPart = getWorldCollisionChecker()->getLastHitCollisionPart();
    pE->setPosition(pE->_x + pColliPart->_cx, pE->_y + pColliPart->_cy, pE->_z + pColliPart->_cz); //�����G�t�F�N�g�ʒu��␳

    if ((pOther->lookUpKind() & KIND_ENEMY_BODY) ) {
        //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I��
        if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
            pOrg_->pLockonCtrler_->lockon(pOther);
        }

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //�ꌂ�Ń`�b�v���ł̍U����
            getStatus()->set(STAT_Stamina, default_stamina_);
            sayonara();
        } else {
            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
            getStatus()->set(STAT_Stamina, default_stamina_);
        }
        AimInfo* pLeaderChip_AimInfo = pLeaderChip_AimInfo_;
//        if (this == pLeaderChip_AimInfo->pLeaderChip && pLeaderChip_AimInfo->pTarget == prm_pOtherActor) {
        //��[���ڕW�Ɍ������������ꍇ��T1�I��
        if (pLeaderChip_AimInfo->pTarget == prm_pOtherActor) {
             //�ڕW�Ɍ������������ꍇ��T1�I��
            frame active_frame = getActiveFrame();
            if (pLeaderChip_AimInfo->aim_time_out_t1 > active_frame) {
                //_TRACE_("aimChip(" << pLeaderChip_AimInfo->t1_ahead_x << "," << pLeaderChip_AimInfo->t1_ahead_y << "," << pLeaderChip_AimInfo->t1_ahead_z << ") this=(" << _x << "," << _y << "," << _z << ") name=" << getName() << "@" << getActiveFrame() << " onHit �� done!!");
                pLeaderChip_AimInfo->aim_time_out_t1 = active_frame;
            }
            getPhase()->change(PHASE_T2);
        }

    } else if (pOther->lookUpKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::onInactive() {
    static const Spacetime* pSpaceTime =  pCARETAKER->getSpacetime();
    static const double ZF_R = pSpaceTime->_x_bound_right - pSpaceTime->_x_bound_left;

    //�㑱�`�b�v(���[�_�[��pLeaderChip_AimInfo_���Q�Ƃ��Ă���)�̂��߂ɁApLeaderChip_AimInfo_�̏�����n��
    AimInfo* pLeaderChip_AimInfo = pLeaderChip_AimInfo_;
    if (pLeaderChip_AimInfo && pLeaderChip_AimInfo->pLeaderChip == this) {
        if (pLeaderChip_AimInfo->aim_time_out_t2 == 0) {
            frame aim_time_out_t1 = pLeaderChip_AimInfo_->aim_time_out_t1;
            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB) {
                pLeaderChip_AimInfo->setT2BySphere(ZF_R, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                pLeaderChip_AimInfo->aim_time_out_t2 = getActiveFrame() + aim_time_out_t1;
            } else {
                pLeaderChip_AimInfo->setT2BySphere(ZF_R, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                pLeaderChip_AimInfo->aim_time_out_t2 = getActiveFrame() + aim_time_out_t1;
            }

            if (pLeaderChip_AimInfo->aim_time_out_t1 == 0) {
                pLeaderChip_AimInfo->setT1_and_T1Ahead(pLeaderChip_AimInfo->t2_x, pLeaderChip_AimInfo->t2_y, pLeaderChip_AimInfo->t2_z);
                pLeaderChip_AimInfo->aim_time_out_t1 = getActiveFrame() + aim_time_out_t1;
            }

        }
        pLeaderChip_AimInfo->pLeaderChip = nullptr;
    }
    pOrg_ = nullptr;
    pLockonCursor_ = nullptr;
    pLeaderChip_AimInfo_ = nullptr;
    VvMyActor<WateringLaserChip>::onInactive();
}

void MyBunshinWateringLaserChip001::chengeTex(int prm_tex_no) {
    if (MyBunshinWateringLaserChip001::pModel_) {
        MyBunshinWateringLaserChip001::tex_no_ = prm_tex_no;
        MyBunshinWateringLaserChip001::pModel_->setDefaultTextureMaterialNo(prm_tex_no);
    }
}

MyBunshinWateringLaserChip001::~MyBunshinWateringLaserChip001() {
    MyBunshinWateringLaserChip001::pModel_ = nullptr;
}

