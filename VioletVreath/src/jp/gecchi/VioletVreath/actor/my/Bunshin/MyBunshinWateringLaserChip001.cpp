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

const int MyBunshinWateringLaserChip001::MAX_VELO_RENGE = PX_C(180); //���̒l��傫������ƁA�ō����x�������Ȃ�B
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 16; //���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�
const double MyBunshinWateringLaserChip001::RR_MAX_ACCE = 1.0 / R_MAX_ACCE; //�v�Z�ȑf���p
const float MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO_RENGE/R_MAX_ACCE;

GgafDxCore::GgafDxModel* MyBunshinWateringLaserChip001::pModel_  = nullptr;
int MyBunshinWateringLaserChip001::tex_no_ = 0;


#define AIM_TIME_OUT (900)

MyBunshinWateringLaserChip001::MyBunshinWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyBunshinWateringLaserChip001", STATUS(MyBunshinWateringLaserChip001)) {
    _class_name = "MyBunshinWateringLaserChip001";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    default_stamina_ = getStatus()->get(STAT_Stamina);
    pOrg_ = nullptr;
    pLockon_ = nullptr;
    is_lockon_ = false;
    GgafDxModel* pModel = getModel();
    if (!MyBunshinWateringLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwGgafCriticalException("MyBunshinWateringLaserChip001::onCreateModel() MyBunshinWateringLaserChip001���f���́A�e�N�X�`���i�}�e���A���j��"<<MAX_LASER_LEVEL<<"�K�v�ł��B");
        }
        MyBunshinWateringLaserChip001::pModel_ = pModel;
    }
    _tmp_x = _x;
    _tmp_y = _y;
    _tmp_z = _z;
    _tmp_acc_vx = _tmp_acc_vy = _tmp_acc_vz = 0;
    pAimInfo_ = nullptr;
}

void MyBunshinWateringLaserChip001::initialize() {
    getKuroko()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(40000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
    pAxsMver_->forceVxyzMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
    pAxsMver_->forceVxyzMvAcceRange(-MAX_ACCE_RENGE, MAX_ACCE_RENGE);
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
    frame active_frame = getActiveFrame();
    MyBunshin::AimInfo* pAimInfo = pAimInfo_;
    if (active_frame >= AIM_TIME_OUT*2) {
        sayonara(); //�ی��̃^�C���A�E�g
    } else if (active_frame < 6 || pAimInfo->pTarget == nullptr) {
        //�Ȃɂ����Ȃ�
    } else {
        GgafDxGeometricActor* pAimTarget = pAimInfo->pTarget;
        if (pAimTarget) {

            //��[�`�b�v���i������\���̂���LeaderChip�ɂ��炸�I�j�AT1�����ς�炸���b�N�I���^�[�Q�b�g�Ȃ�΍X�V
            if (getInfrontChip() == nullptr && pAimTarget == pLockon_->pTarget_ && pAimInfo_->_spent_frames_to_t1 < AIM_TIME_OUT) {
                pAimInfo->t1_x = pAimTarget->_x; //t1�X�V
                pAimInfo->t1_y = pAimTarget->_y;
                pAimInfo->t1_z = pAimTarget->_z;
            }

            MyBunshinWateringLaserChip001* pAimLeaderChip = pAimInfo->pLeaderChip_;
            if (this == pAimLeaderChip) {

                if (pAimInfo->_spent_frames_to_t1 == 0) {
                    //��Leader �� t1 �� Aim
                    if (pAimTarget->isActiveInTheTree() && getActiveFrame() < AIM_TIME_OUT)  {
                        //pAimTarget ������
                        aimChip(pAimInfo->t1_x,
                                pAimInfo->t1_y,
                                pAimInfo->t1_z );
                        static const coord renge = MyBunshinWateringLaserChip001::MAX_VELO_RENGE;
                        if (_x >= pAimInfo->t1_x - renge) {
                            if (_x <= pAimInfo->t1_x + renge) {
                                if (_y >= pAimInfo->t1_y - renge) {
                                    if (_y <= pAimInfo->t1_y + renge) {
                                        if (_z >= pAimInfo->t1_z - renge) {
                                            if (_z <= pAimInfo->t1_z + renge) {
                                                 pAimInfo_->_spent_frames_to_t1 = getActiveFrame(); //Aim t1 �I��
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        //���߂� pAimTarget ���������̂ɁA�r���ŏ������B
                        pAimInfo_->_spent_frames_to_t1 = getActiveFrame(); //Aim t1 �I��
                    }


                } else if (pAimInfo->_spent_frames_to_t2 == 0) {
                    //��Leader �� t1 �� Aim ���I���������
                    //t2�����߂闷�AonInactive���ł��A�����́A�^�C���A�E�g�҂�
                    if (getActiveFrame() < AIM_TIME_OUT)  {
                        MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
                        if (pB) {
                            coord dx = _x - pB->_x;
                            coord dy = _y - pB->_y;
                            coord dz = _z - pB->_z;
                            aimChip(_x + dx*4+1,
                                    _y + dy*4+1,
                                    _z + dz*4+1 );
                        } else {
                            aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                                    _y + pAxsMver_->_velo_vy_mv*4+1,
                                    _z + pAxsMver_->_velo_vz_mv*4+1 );
                        }
                    } else {
                        pAimInfo_->_spent_frames_to_t2 = getActiveFrame(); //Aim t2 �I��
                    }
                    pAimInfo->t2_x = pAimLeaderChip->_x;
                    pAimInfo->t2_y = pAimLeaderChip->_y;
                    pAimInfo->t2_z = pAimLeaderChip->_z;
                } else {
                    //��Leader �� t2 ��ݒ肵�����ƁB

                    if (getActiveFrame() < AIM_TIME_OUT)  {
                        MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
                        if (pB) {
                            coord dx = _x - pB->_x;
                            coord dy = _y - pB->_y;
                            coord dz = _z - pB->_z;
                            aimChip(_x + dx*4+1,
                                    _y + dy*4+1,
                                    _z + dz*4+1 );
                        } else {
                            aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                                    _y + pAxsMver_->_velo_vy_mv*4+1,
                                    _z + pAxsMver_->_velo_vz_mv*4+1 );
                        }
                    } else {
                        aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                                _y + pAxsMver_->_velo_vy_mv*4+1,
                                _z + pAxsMver_->_velo_vz_mv*4+1 );
                    }
                }

            } else {

                if (pAimInfo->_spent_frames_to_t1 == 0) {
                    //��Leader�ȊO�� t1 ����܂�܂ł̓���
                    aimChip(pAimInfo->t1_x,
                            pAimInfo->t1_y,
                            pAimInfo->t1_z );
                } else if (active_frame < pAimInfo->_spent_frames_to_t1) {
                    //��Leader�ȊO�� t1 ����܂��Ă��� t1 ���B�܂ł̓���
                    aimChip(pAimInfo->t1_x,
                            pAimInfo->t1_y,
                            pAimInfo->t1_z );
                } else if (active_frame >= pAimInfo->_spent_frames_to_t1) {
                    //��Leader�ȊO�� t1 ��ʉ�
                    if (pAimInfo->_spent_frames_to_t2 == 0) {
                        //�����̌� Leader�ȊO�� t2 ����܂�܂ł̓���
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                                    _y + pAxsMver_->_velo_vy_mv*4+1,
                                    _z + pAxsMver_->_velo_vz_mv*4+1 );
                        }
                    } else if (active_frame < pAimInfo->_spent_frames_to_t2) {
                        //�����̌� Leader�ȊO�� t2 ����܂��āAt2�Ɍ������܂ł̓���
                        aimChip(pAimInfo->t2_x,
                                pAimInfo->t2_y,
                                pAimInfo->t2_z );
                    } else if (active_frame >= pAimInfo->_spent_frames_to_t2) {
                        //�����̌� Leader�ȊO�� t2 ��ʉ߂�����̓���
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                                    _y + pAxsMver_->_velo_vy_mv*4+1,
                                    _z + pAxsMver_->_velo_vz_mv*4+1 );
                        }
                    }
                }
            }

        }

    }

    pAxsMver_->behave();
    WateringLaserChip::processBehavior();
    _tmp_x = _x;
    _tmp_y = _y;
    _tmp_z = _z;
    _tmp_acc_vx =  pAxsMver_->_acce_vx_mv;
    _tmp_acc_vy =  pAxsMver_->_acce_vy_mv;
    _tmp_acc_vz =  pAxsMver_->_acce_vz_mv;

}

void MyBunshinWateringLaserChip001::processSettlementBehavior() {
    //���g��FK�Ȃ̂ŁA��΍��W�̊m�肪 processSettlementBehavior() �ȍ~�ƂȂ邽�߁A�����ŏ����ݒ肪�K�v
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
                pAimInfo_->pLeaderChip_ = this;
                pAimInfo_->pTarget = pLockonTarget;
                pAimInfo_->t1_x = pAimInfo_->pTarget->_x;
                pAimInfo_->t1_y = pAimInfo_->pTarget->_y;
                pAimInfo_->t1_z = pAimInfo_->pTarget->_z;
                pAxsMver_->forceVxyzMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
            } else {
                //��[�Ń��b�N�I�����Ă��Ȃ�
                pAimInfo_ = pOrg_->getAimInfo();
                pAimInfo_->pLeaderChip_ = this;
                pAimInfo_->pTarget = nullptr;
                pAxsMver_->forceVxyzMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
            }
        } else {
            //��[�ȊO�͑O�̂��󂯌p��
            pAimInfo_ = pF->pAimInfo_; //�󂯌p��
            coord velo = pF->pAxsMver_->_top_velo_vx_mv - PX_C(0.5);
            pAxsMver_->forceVxyzMvVeloRange(-velo, velo);
        }

        //�����J�n����t���[���A�`�b�v�̑��x�ƌ����̏����ݒ�
        setFaceAngAs(pOrg_);
        positionAs(pOrg_);
        pAxsMver_->setVxyzMvVeloTwd(_rz, _ry, PX_C(100)); //�����͂�����
        pAxsMver_->setZeroVxyzMvAcce();
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
            _x = ((pF->_tmp_x + pB->_tmp_x)/2 + _tmp_x)/2;
            _y = ((pF->_tmp_y + pB->_tmp_y)/2 + _tmp_y)/2;
            _z = ((pF->_tmp_z + pB->_tmp_z)/2 + _tmp_z)/2;
            pAxsMver_->setVxyzMvAcce( ( ((pF->_tmp_acc_vx + pB->_tmp_acc_vx)/2) + _tmp_acc_vx)/2,
                                      ( ((pF->_tmp_acc_vy + pB->_tmp_acc_vy)/2) + _tmp_acc_vy)/2,
                                      ( ((pF->_tmp_acc_vz + pB->_tmp_acc_vz)/2) + _tmp_acc_vz)/2 );
        }
    }
    WateringLaserChip::processSettlementBehavior();
}

void MyBunshinWateringLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        if (pAimInfo_->pLeaderChip_ == this) {
            pAimInfo_->t2_x = _x;
            pAimInfo_->t2_y = _y;
            pAimInfo_->t2_z = _z;
            pAimInfo_->_spent_frames_to_t2 = getActiveFrame();

            if (pAimInfo_->_spent_frames_to_t1 == 0) {
                pAimInfo_->t1_x = pAimInfo_->t2_x;
                pAimInfo_->t1_y = pAimInfo_->t2_y;
                pAimInfo_->t1_z = pAimInfo_->t2_z;
                pAimInfo_->_spent_frames_to_t1 = getActiveFrame();
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
    GgafDxAxesMover* pAxsMver = pAxsMver_;

    //�����I
    const int vTx = tX - _x;
    const int vTy = tY - _y;
    const int vTz = tZ - _z;

    //���������B
    const int vVMx = pAxsMver->_velo_vx_mv;
    const int vVMy = pAxsMver->_velo_vy_mv;
    const int vVMz = pAxsMver->_velo_vz_mv;
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

    pAxsMver->setVxyzMvAcce(accX + SGN(accX)*3.0,
                            accY + SGN(accY)*3.0,
                            accZ + SGN(accZ)*3.0);
}

void MyBunshinWateringLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    //�q�b�g�G�t�F�N�g
    UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g�o��

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //�ꌂ�Ń`�b�v���ł̍U����
            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I��
            if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }

getStatus()->set(STAT_Stamina, default_stamina_);
//sayonara();
        } else {
            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
            getStatus()->set(STAT_Stamina, default_stamina_);
            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I��
            if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }
        }

        if (this == pAimInfo_->pLeaderChip_ && pAimInfo_->pTarget == prm_pOtherActor) {
            //��[���ڕW�Ɍ������������ꍇ��T1�I��
            pAimInfo_->t1_x = _x;
            pAimInfo_->t1_y = _y;
            pAimInfo_->t1_z = _z;
            pAimInfo_->_spent_frames_to_t1 = getActiveFrame();
        }


    } else if (pOther->getKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::onInactive() {
    MyBunshin::AimInfo* pAimInfo = pAimInfo_;

    if (pAimInfo->pLeaderChip_ == this) {
        if (pAimInfo->_spent_frames_to_t2 == 0) {
            static const Spacetime* pSpaceTime =  P_GOD->getSpacetime();
            static const double zf_r = UTIL::getDistance(
                                              0.0, 0.0, 0.0,
                                              (double)(pSpaceTime->_x_bound_right),
                                              (double)(pSpaceTime->_y_bound_top),
                                              (double)(pSpaceTime->_z_bound_far)
                                             ) * 1.2;

            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB) {
                pAimInfo->setT2(zf_r, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                pAimInfo->_spent_frames_to_t2 = getActiveFrame()+AIM_TIME_OUT;
            } else {
                pAimInfo->setT2(zf_r, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                pAimInfo->_spent_frames_to_t2 = getActiveFrame()+AIM_TIME_OUT;
            }

            if (pAimInfo->_spent_frames_to_t1 == 0) {
                pAimInfo->t1_x = pAimInfo->t2_x;
                pAimInfo->t1_y = pAimInfo->t2_y;
                pAimInfo->t1_z = pAimInfo->t2_z;
                pAimInfo->_spent_frames_to_t1 = getActiveFrame()+AIM_TIME_OUT;
            }

        }
        pAimInfo->pLeaderChip_ = nullptr;
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
    GGAF_DELETE(pAxsMver_);
    MyBunshinWateringLaserChip001::pModel_ = nullptr;
}

