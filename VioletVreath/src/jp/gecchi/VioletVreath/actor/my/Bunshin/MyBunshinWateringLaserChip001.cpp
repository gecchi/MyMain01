#include "MyBunshinWateringLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectLockon001_Main.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

const velo MyBunshinWateringLaserChip001::MAX_VELO_RENGE = PX_C(300); //���̒l��傫������ƁA�ō����x�������Ȃ�B
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 17; //���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�
const velo MyBunshinWateringLaserChip001::INITIAL_VELO = MAX_VELO_RENGE*0.7; //���[�U�[���ˎ��̏������x
const double MyBunshinWateringLaserChip001::RR_MAX_ACCE = 1.0 / R_MAX_ACCE; //�v�Z�ȑf���p
const float MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO_RENGE/R_MAX_ACCE;

GgafDxCore::GgafDxModel* MyBunshinWateringLaserChip001::pModel_  = nullptr;
int MyBunshinWateringLaserChip001::tex_no_ = 0;


MyBunshinWateringLaserChip001::MyBunshinWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyLaserChip001", STATUS(MyBunshinWateringLaserChip001)) {
    _class_name = "MyBunshinWateringLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    pOrg_ = nullptr;
    pLockon_ = nullptr;
    is_lockon_ = false;
    GgafDxModel* pModel = getModel();
    if (!MyBunshinWateringLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwGgafCriticalException("MyBunshinWateringLaserChip001���f���́A�e�N�X�`���i�}�e���A���j��"<<MAX_LASER_LEVEL<<"�K�v�ł��B");
        }
        MyBunshinWateringLaserChip001::pModel_ = pModel;
    }
    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
    tmp_acc_vx_ = tmp_acc_vy_ = tmp_acc_vz_ = 0;
    pAimInfo_ = nullptr;
}

void MyBunshinWateringLaserChip001::initialize() {
    getKuroko()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(PX_C(80));
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
    GgafDxAxesMover* const pAxesMover = getAxesMover();
    pAxesMover->forceVxMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
    pAxesMover->forceVyMvVeloRange(-MAX_VELO_RENGE*1.5, MAX_VELO_RENGE*1.5);
    pAxesMover->forceVzMvVeloRange(-MAX_VELO_RENGE*1.5, MAX_VELO_RENGE*1.5);
    pAxesMover->forceVxMvAcceRange(-MAX_ACCE_RENGE, MAX_ACCE_RENGE);
    pAxesMover->forceVyMvAcceRange(-MAX_ACCE_RENGE*1.5, MAX_ACCE_RENGE*1.5);
    pAxesMover->forceVzMvAcceRange(-MAX_ACCE_RENGE*1.5, MAX_ACCE_RENGE*1.5);
}

void MyBunshinWateringLaserChip001::onCreateModel() {

}

void MyBunshinWateringLaserChip001::setOrg(MyBunshin* prm_pOrg) {
    pOrg_ = prm_pOrg;
    pLockon_ = pOrg_->pLockonCtrler_->pMainLockonEffect_;
}

void MyBunshinWateringLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    WateringLaserChip::onActive();
    pAimInfo_ = nullptr;
}

void MyBunshinWateringLaserChip001::processBehavior() {
    GgafDxAxesMover* const pAxesMover = getAxesMover();
    frame active_frame = getActiveFrame();
    MyBunshin::AimInfo* pAimInfo = pAimInfo_;

    if (active_frame >= 60*20) {
        sayonara(); //�ی��̃^�C���A�E�g20�b
    } else if (active_frame < 7) {
        //�Ȃɂ����Ȃ�
    } else if (pAimInfo && pAimInfo->pTarget == nullptr) {
        //�Ȃɂ����Ȃ�
    } else {
        GgafDxGeometricActor* pAimTarget = pAimInfo->pTarget;
        frame aim_time_out_t1 = pAimInfo->aim_time_out_t1;
        if (pAimTarget) {
            //��[�`�b�v���i������\���̂���LeaderChip�ɂ��炸�I�j�AT1�����ς�炸���b�N�I���^�[�Q�b�g�Ȃ�΍X�V
            if (getInfrontChip() == nullptr && pAimTarget == pLockon_->pTarget_ && pAimInfo_->spent_frames_to_t1 < aim_time_out_t1) {
                pAimInfo->t1_x = pAimTarget->_x; //t1�X�V
                pAimInfo->t1_y = pAimTarget->_y;
                pAimInfo->t1_z = pAimTarget->_z;
            }

            MyBunshinWateringLaserChip001* pAimLeaderChip = pAimInfo->pLeaderChip;
            if (this == pAimLeaderChip) {
                if (pAimInfo->spent_frames_to_t1 == 0) {
                    //��Leader �� t1 �� Aim
                    if (pAimTarget->isActiveInTheTree() && active_frame < aim_time_out_t1)  {
                        //pAimTarget ������
                        aimChip(pAimInfo->t1_x,
                                pAimInfo->t1_y,
                                pAimInfo->t1_z );
                        static const coord renge = MyBunshinWateringLaserChip001::INITIAL_VELO * 0.4;
                        if (_x >= pAimInfo->t1_x - renge) {
                            if (_x <= pAimInfo->t1_x + renge) {
                                if (_y >= pAimInfo->t1_y - renge) {
                                    if (_y <= pAimInfo->t1_y + renge) {
                                        if (_z >= pAimInfo->t1_z - renge) {
                                            if (_z <= pAimInfo->t1_z + renge) {
                                                 pAimInfo_->spent_frames_to_t1 = getActiveFrame(); //Aim t1 �I��
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        //���߂� pAimTarget ���������̂ɁA�r���ŏ������B
                        pAimInfo_->spent_frames_to_t1 = getActiveFrame(); //Aim t1 �I��
                    }


                } else if (pAimInfo->spent_frames_to_t2 == 0) {
                    //��Leader �� t1 �� Aim ���I���������
                    //t2�����߂�
                    static const Spacetime* pSpaceTime =  pGOD->getSpacetime();
                    static const double zf_r = UTIL::getDistance(
                                                      0.0, 0.0, 0.0,
                                                      (double)(pSpaceTime->_x_bound_right),
                                                      (double)(pSpaceTime->_y_bound_top),
                                                      (double)(pSpaceTime->_z_bound_far)
                                                     ) * 1.2;
                    MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
                    if (pB) {
                        pAimInfo->setT2(zf_r, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                    } else {
                        pAimInfo->setT2(zf_r, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                    }
                    coord t2_d = UTIL::getDistance(_x, _y, _z,
                                                   pAimInfo->t2_x,
                                                   pAimInfo->t2_y,
                                                   pAimInfo->t2_z);
                    pAimInfo->spent_frames_to_t2 = active_frame + (t2_d/MyBunshinWateringLaserChip001::MAX_VELO_RENGE);
                    aimChip(pAimInfo->t2_x,
                            pAimInfo->t2_y,
                            pAimInfo->t2_z );
                } else {
                    //��Leader �� t2 ��ݒ肵�����ƁB
                    if (active_frame < pAimInfo->spent_frames_to_t2)  {
                        aimChip(pAimInfo->t2_x,
                                pAimInfo->t2_y,
                                pAimInfo->t2_z );
                    } else {
                        aimChip(_x + pAxesMover->_velo_vx_mv*4+1,
                                _y + pAxesMover->_velo_vy_mv*4+1,
                                _z + pAxesMover->_velo_vz_mv*4+1 );
                    }
                }

            } else {
                //��Leader�ȊO
                if (pAimInfo->spent_frames_to_t1 == 0) {
                    //��Leader�ȊO�� t1 ����܂�܂ł̓���
                    aimChip(pAimInfo->t1_x,
                            pAimInfo->t1_y,
                            pAimInfo->t1_z );
                } else if (active_frame < pAimInfo->spent_frames_to_t1) {
                    //��Leader�ȊO�� t1 ����܂��Ă��� t1 ���B�܂ł̓���
                    aimChip(pAimInfo->t1_x,
                            pAimInfo->t1_y,
                            pAimInfo->t1_z );
                } else if (active_frame >= pAimInfo->spent_frames_to_t1) {
                    //��Leader�ȊO�� t1 ��ʉ�
                    if (pAimInfo->spent_frames_to_t2 == 0) {
                        //�����̌� Leader�ȊO�� t2 ����܂�܂ł̓���
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pAxesMover->_velo_vx_mv*4+1,
                                    _y + pAxesMover->_velo_vy_mv*4+1,
                                    _z + pAxesMover->_velo_vz_mv*4+1 );
                        }
                    } else if (active_frame < pAimInfo->spent_frames_to_t2) {
                        //�����̌� Leader�ȊO�� t2 ����܂��āAt2�Ɍ������܂ł̓���
                        aimChip(pAimInfo->t2_x,
                                pAimInfo->t2_y,
                                pAimInfo->t2_z );
                    } else if (active_frame >= pAimInfo->spent_frames_to_t2) {
                        //�����̌� Leader�ȊO�� t2 ��ʉ߂�����̓���
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pAxesMover->_velo_vx_mv*4+1,
                                    _y + pAxesMover->_velo_vy_mv*4+1,
                                    _z + pAxesMover->_velo_vz_mv*4+1 );
                        }
                    }
                }
            }

        }

    }

    pAxesMover->behave();
    WateringLaserChip::processBehavior();
    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
    tmp_acc_vx_ =  pAxesMover->_acce_vx_mv;
    tmp_acc_vy_ =  pAxesMover->_acce_vy_mv;
    tmp_acc_vz_ =  pAxesMover->_acce_vz_mv;
}

void MyBunshinWateringLaserChip001::processSettlementBehavior() {
    //���g��FK�Ȃ̂ŁA��΍��W�̊m�肪 processSettlementBehavior() �ȍ~�ƂȂ邽�߁A�����ŏ����ݒ肪�K�v
    GgafDxAxesMover* const pAxesMover = getAxesMover();
    if (hasJustChangedToActive()) {
        //�`�b�v�̏����ݒ�
        //���b�N�I�����̈����p��
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getInfrontChip();
        if (pF == nullptr) {
            //��[�`�b�v
            GgafDxGeometricActor* pLockonTarget = pLockon_->pTarget_;
            if (pLockonTarget && pLockonTarget->isActiveInTheTree()) {
                //��[�Ń��b�N�I����
                pAimInfo_ = pOrg_->getAimInfo();
                pAimInfo_->pLeaderChip = this;
                pAimInfo_->pTarget = pLockonTarget;
                pAimInfo_->t1_x = pAimInfo_->pTarget->_x;
                pAimInfo_->t1_y = pAimInfo_->pTarget->_y;
                pAimInfo_->t1_z = pAimInfo_->pTarget->_z;
                // aim_time_out_t1 ���T�Z�ŋ��߂Ă���
                coord t1_d = UTIL::getDistance(this, pLockonTarget);
                pAimInfo_->aim_time_out_t1 = (t1_d / MyBunshinWateringLaserChip001::INITIAL_VELO)*1.2 + 7 + 10;
            } else {
                //��[�Ń��b�N�I�����Ă��Ȃ�
                pAimInfo_ = pOrg_->getAimInfo();
                pAimInfo_->pLeaderChip = this;
                pAimInfo_->pTarget = nullptr;
            }
            pAxesMover->forceVxMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
            pAxesMover->forceVyMvVeloRange(-MAX_VELO_RENGE*1.5, MAX_VELO_RENGE*1.5);
            pAxesMover->forceVzMvVeloRange(-MAX_VELO_RENGE*1.5, MAX_VELO_RENGE*1.5);
        } else {
            //��[�ȊO�͑O�̂��󂯌p��
            pAimInfo_ = pF->pAimInfo_; //�󂯌p��
            velo v = pF->getAxesMover()->_top_velo_vx_mv - PX_C(0.5); //���[�U�[���o�܂Ȃ��悤�� PX_C(0.5) �x������
            pAxesMover->forceVxMvVeloRange(-v, v);
            pAxesMover->forceVyMvVeloRange(-v*1.5, v*1.5);
            pAxesMover->forceVzMvVeloRange(-v*1.5, v*1.5);
#ifdef MY_DEBUG
if (pAimInfo_ == nullptr) {
throwGgafCriticalException("pAimInfo_ �������p����Ă��܂���I"<<this<<
                           " _frame_of_life_when_activation="<<_frame_of_life_when_activation);
}
#endif
        }

        //�����J�n����t���[���A�`�b�v�̑��x�ƌ����̏����ݒ�
        setFaceAngAs(pOrg_);
        setPositionAt(pOrg_);
        pAxesMover->setVxyzMvVeloTwd(_rz, _ry, INITIAL_VELO); //�����͂�����
        pAxesMover->setZeroVxyzMvAcce();
    }

    //���ϋȐ����W�ݒ�B(���[�U�[�����炩�ɂ���m�[�}���C�Y�j
    //processSettlementBehavior() �̃��\�b�h�̈Ӌ`�Ƃ͗���č��W��������ړ����Ă���B
    //�{���� processBehaviorAfter() �I�ȈӖ��̏����ł��邪�A�S���[�U�[�`�b�v���ړ���łȂ��ƈӖ����Ȃ��̂�
    //�d���Ȃ��̂�processSettlementBehavior()�ɐH������ł��܂��B
    //���������Ė{�N���X���p�������ꍇ�A�p���N���X��processSettlementBehavior()�ł́A�擪�ŌĂяo���������ǂ��B
    if (getActiveFrame() > 4) { //FK�I�u�W�F�N�g����̃��[�U�[���˂��l������ƁA_tmpXYZ �����܂�̂�3�t���[���ȍ~�B
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
        MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
        if (pF && pB && pF->isActive() && pB->isActive()) {
            //_pChip_behind == nullptr �̔��肾���ł͂��߁B_pChip_behind->_is_active_flg �Ɣ��肷�邱��
            //�Ȃ��Ȃ� dispatch �̏u�Ԃ�_pChip_behind != nullptr �ƂȂ邪�Aactive()�ɂ��L���ɂȂ�͎̂��t���[��������
            //_x,_y,_z �ɂ͂܂��ςȒl�������Ă���B
            //���ԍ��W�ɍĐݒ�
            _x = ((pF->tmp_x_ + pB->tmp_x_)/2 + tmp_x_)/2;
            _y = ((pF->tmp_y_ + pB->tmp_y_)/2 + tmp_y_)/2;
            _z = ((pF->tmp_z_ + pB->tmp_z_)/2 + tmp_z_)/2;
            pAxesMover->setVxyzMvAcce( ( ((pF->tmp_acc_vx_ + pB->tmp_acc_vx_)/2) + tmp_acc_vx_)/2,
                                       ( ((pF->tmp_acc_vy_ + pB->tmp_acc_vy_)/2) + tmp_acc_vy_)/2,
                                       ( ((pF->tmp_acc_vz_ + pB->tmp_acc_vz_)/2) + tmp_acc_vz_)/2 );
        }
    }
    WateringLaserChip::processSettlementBehavior();
}

void MyBunshinWateringLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        if (pAimInfo_->pLeaderChip == this) {
            pAimInfo_->t2_x = _x;
            pAimInfo_->t2_y = _y;
            pAimInfo_->t2_z = _z;
            pAimInfo_->spent_frames_to_t2 = getActiveFrame();

            if (pAimInfo_->spent_frames_to_t1 == 0) {
                pAimInfo_->t1_x = pAimInfo_->t2_x;
                pAimInfo_->t1_y = pAimInfo_->t2_y;
                pAimInfo_->t1_z = pAimInfo_->t2_z;
                pAimInfo_->spent_frames_to_t1 = getActiveFrame();
            }
        }
        sayonara();
    }
}


void MyBunshinWateringLaserChip001::aimChip(int tX, int tY, int tZ) {
    //    |                            vVT ���I                        |
    //    |                                ^ ��                        |
    //    |                 |���I| > 5*vM /    �_  vVP ���������I      |      ���I
    //    |                 �ƂȂ�悤�� /       �_                    |       ��
    //    |                 vVT��ݒ�   /         ��                   |      ����
    //    |                            /        �^vVM  ����            |       ��
    //    |                           /       �^  (vVMx,vVMy,vVMz)     |       �b
    //    |                          /      �^                         |       �b
    //    |                         /     �^                           |       �b
    //    |                        /    �^ |����| = lVM * 5            |       �b
    //    |                   vT �I   �^                               |       �I
    //    |             ��       ^  �^                                 |       ��
    //    |               �_    / ��vM ���݂̈ړ������x�N�g��          |       �b
    //    | vVP ���������I  �_ /�^ (veloVxMv_,veloVyMv_,veloVzMv_)     |       �b
    //    |                   ��                                       |       ��
    // ---+------------------------------------------               ---+---------------------------
    //    |                                                            |
    //
    // vVP ���������������BvVP�����߂�I
#ifdef MY_DEBUG
    if (tX == INT_MAX) {
        throwGgafCriticalException("��������");
    }
#endif
    GgafDxAxesMover* pAxesMover = getAxesMover();

    //�����I
    const int vTx = tX - _x;
    const int vTy = tY - _y;
    const int vTz = tZ - _z;

    //���������B
    const int vVMx = pAxesMover->_velo_vx_mv;
    const int vVMy = pAxesMover->_velo_vy_mv;
    const int vVMz = pAxesMover->_velo_vz_mv;
    //|����| = lVM * 5
    const int lVM = MAX3(ABS(vVMx), ABS(vVMy), ABS(vVMz)); //�����x�N�g���傫���ȈՔ�
    //|�I|
    const int lT =  MAX3(ABS(vTx), ABS(vTy), ABS(vTz)); //�I�x�N�g���傫���ȈՔ�
    //|����|/|�I|      vT �̉��{�� vVT ���I �ɂȂ�̂������߂�B
    const double r = (lVM*5 * 1.5) / lT;
    //* 1.5�� �E��}�̂悤�Ɉ꒼���ɕ��񂾍ۂ��A�i�s�������ێ����邽�߂ɁA
    //|���I| > |����| �Ƃ����֌W���ێ����邽�߂ɂ������K���Ȋ���

    //vVP ���������I �̉����x�ݒ�
    const double accX = ((vTx * r) - vVMx*5) * RR_MAX_ACCE;
    const double accY = ((vTy * r) - vVMy*5) * RR_MAX_ACCE;
    const double accZ = ((vTz * r) - vVMz*5) * RR_MAX_ACCE;

    pAxesMover->setVxyzMvAcce(accX + SGN(accX)*3.0,
                              accY + SGN(accY)*3.0,
                              accZ + SGN(accZ)*3.0);
}

void MyBunshinWateringLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    //�q�b�g�G�t�F�N�g
    UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g�o��

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
        MyBunshin::AimInfo* pAimInfo = pAimInfo_;
        if (this == pAimInfo->pLeaderChip && pAimInfo->pTarget == prm_pOtherActor) {
            //��[���ڕW�Ɍ������������ꍇ��T1�I��
            pAimInfo->t1_x = _x;
            pAimInfo->t1_y = _y;
            pAimInfo->t1_z = _z;
            pAimInfo->spent_frames_to_t1 = getActiveFrame();
        }

    } else if (pOther->lookUpKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::onInactive() {
    MyBunshin::AimInfo* pAimInfo = pAimInfo_;
    if (pAimInfo && pAimInfo->pLeaderChip == this) {
        if (pAimInfo->spent_frames_to_t2 == 0) {
            frame aim_time_out_t1 = pAimInfo_->aim_time_out_t1;
            static const Spacetime* pSpaceTime =  pGOD->getSpacetime();
            static const double zf_r = UTIL::getDistance(
                                              0.0, 0.0, 0.0,
                                              (double)(pSpaceTime->_x_bound_right),
                                              (double)(pSpaceTime->_y_bound_top),
                                              (double)(pSpaceTime->_z_bound_far)
                                             ) * 1.2;

            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB) {
                pAimInfo->setT2(zf_r, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                pAimInfo->spent_frames_to_t2 = getActiveFrame() + aim_time_out_t1;
            } else {
                pAimInfo->setT2(zf_r, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                pAimInfo->spent_frames_to_t2 = getActiveFrame() + aim_time_out_t1;
            }

            if (pAimInfo->spent_frames_to_t1 == 0) {
                pAimInfo->t1_x = pAimInfo->t2_x;
                pAimInfo->t1_y = pAimInfo->t2_y;
                pAimInfo->t1_z = pAimInfo->t2_z;
                pAimInfo->spent_frames_to_t1 = getActiveFrame() + aim_time_out_t1;
            }

        }
        pAimInfo->pLeaderChip = nullptr;
    }
    pOrg_ = nullptr;
    pLockon_ = nullptr;
    pAimInfo_ = nullptr;

    WateringLaserChip::onInactive();
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

