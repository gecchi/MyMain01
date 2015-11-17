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

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

const int MyBunshinWateringLaserChip001::MAX_VELO_RENGE = PX_C(160); //���̒l��傫������ƁA�ō����x�������Ȃ�B
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 20; //���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�
const double MyBunshinWateringLaserChip001::RR_MAX_ACCE = 1.0 / R_MAX_ACCE; //�v�Z�ȑf���p
const float MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO_RENGE/R_MAX_ACCE;

GgafDxCore::GgafDxModel* MyBunshinWateringLaserChip001::pModel_  = nullptr;
int MyBunshinWateringLaserChip001::tex_no_ = 0;

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
    aim_status_ = PROG_BANPEI;
    pAimPoint_ = nullptr;
}

void MyBunshinWateringLaserChip001::initialize() {
    getKuroko()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(80000);
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
    aim_status_ = PROG_AIM_AT_NOTHING;

    WateringLaserChip::onActive();

    //���b�N�I�����̈����p��
//    GgafDxGeometricActor* pLockonTarget = pOrg_pLockonCtrler_pRingTarget_->getCurrent();
    MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getInfrontChip();
    if (pF == nullptr) {
        //��[�`�b�v
        GgafDxGeometricActor* pLockonTarget = pLockon_->pTarget_;
        if (pLockonTarget && pLockonTarget->isActiveInTheTree()) {
            //���b�N�I����
            pAimPoint_ = pOrg_->getAimPoint();
            pAimPoint_->pTarget = pLockonTarget;
            pAimPoint_->target01_x = pLockonTarget->_x;
            pAimPoint_->target01_y = pLockonTarget->_y;
            pAimPoint_->target01_z = pLockonTarget->_z;
            aim_status_ = PROG_AIM_AT_LOCK_ON_TARGET01;
        } else {
            //���b�N�I�����Ă��Ȃ�
            pAimPoint_ = pOrg_->getAimPoint();
            pAimPoint_->pTarget = nullptr;
            pAimPoint_->target01_x = pOrg_->_x;
            pAimPoint_->target01_y = pOrg_->_y;
            pAimPoint_->target01_z = pOrg_->_z;
            aim_status_ = PROG_AIM_AT_NOTHING;
        }
    } else {
        //��[�ȊO

        pAimPoint_ = pF->pAimPoint_; //�󂯌p��
        aim_status_ = pF->aim_status_;
    }

}

void MyBunshinWateringLaserChip001::processBehavior() {
    GgafProgress* pProg = getProgress();
    frame active_frame = getActiveFrame();
    MyBunshin::AimPoint* pAimPoint = pAimPoint_;
    if (aim_status_ == PROG_AIM_AT_LOCK_ON_TARGET01) {
        if (pAimPoint->is_enable_target01) { //���b�N�I���ɖ��������ꍇ�B
            if (_pLeader == this) {
                aim_status_ = PROG_AIM_AT_NOTHING_TARGET01_AFTER;
                goto AIM_AT_NOTHING_TARGET01_AFTER;
            } else {
                aim_status_ = PROG_AIM_AT_TARGET01;
                goto AIM_AT_TARGET01;
            }
        } else {
            GgafDxGeometricActor* pAimTarget = pAimPoint->pTarget;
            if (pAimTarget && pAimTarget->isActiveInTheTree() && getActiveFrame() < 120)  {
                if (active_frame > 7 ) {
                    aimChip(pAimTarget->_x,
                            pAimTarget->_y,
                            pAimTarget->_z );
                }
                if (_pLeader == this) {
                    pAimPoint->target01_x = pAimTarget->_x;
                    pAimPoint->target01_y = pAimTarget->_y;
                    pAimPoint->target01_z = pAimTarget->_z;
                      //�����L���ɂ͂��ĂȂ��B���W�X�V�̂�
                }
            } else {
                aim_status_ = PROG_AIM_AT_TARGET01;
                goto AIM_AT_TARGET01;
            }
        }
    }

    AIM_AT_TARGET01:

    if (aim_status_ == PROG_AIM_AT_TARGET01) {
        static const coord renge = MyBunshinWateringLaserChip001::MAX_VELO_RENGE;
        if (_x >= pAimPoint->target01_x - renge) {
            if (_x <= pAimPoint->target01_x + renge) {
                if (_y >= pAimPoint->target01_y - renge) {
                    if (_y <= pAimPoint->target01_y + renge) {
                        if (_z >= pAimPoint->target01_z - renge) {
                            if (_z <= pAimPoint->target01_z + renge) {
                                aim_status_ = PROG_AIM_AT_NOTHING_TARGET01_AFTER;
                                goto AIM_AT_NOTHING_TARGET01_AFTER;
                            }
                        }
                    }
                }
            }
        }
        if (active_frame < 120) {
            if (active_frame > 7 ) {
                aimChip(pAimPoint->target01_x,
                        pAimPoint->target01_y,
                        pAimPoint->target01_z );
            }
        } else {
            aim_status_ = PROG_AIM_AT_NOTHING_TARGET01_AFTER;
            goto AIM_AT_NOTHING_TARGET01_AFTER;
        }
    }

    AIM_AT_NOTHING_TARGET01_AFTER:

    if (aim_status_ == PROG_AIM_AT_NOTHING_TARGET01_AFTER) {
        if (pAimPoint->is_enable_target02) {
            aim_status_ = PROG_AIM_AT_TARGET02;
            goto AIM_AT_TARGET02;
        } else {
            if (_pLeader == this) {
                MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
                if (pB) {
                    coord dx = _x - pB->_x;
                    coord dy = _y - pB->_y;
                    coord dz = _z - pB->_z;
                    aimChip(_x + dx*2+1,
                            _y + dy*2+1,
                            _z + dz*2+1 );
                } else {
                    aimChip(_x + pAxsMver_->_velo_vx_mv*2+1,
                            _y + pAxsMver_->_velo_vy_mv*2+1,
                            _z + pAxsMver_->_velo_vz_mv*2+1 );
                }
            } else {
                if (_pLeader) {
                    aimChip(_pLeader->_x,
                            _pLeader->_y,
                            _pLeader->_z);
                }
                MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
                if (pF) {
                    if (pF != _pLeader && pF->aim_status_ == PROG_AIM_AT_TARGET01 ) {
                        pF->aim_status_ = PROG_AIM_AT_NOTHING_TARGET01_AFTER;
                    }
                }
            }
        }
    }

    AIM_AT_TARGET02:

    if (aim_status_ == PROG_AIM_AT_TARGET02) {
        if (pAimPoint->is_enable_target02) {
            static const coord renge = MyBunshinWateringLaserChip001::MAX_VELO_RENGE;
            if (_x >= pAimPoint->target02_x - renge) {
                if (_x <= pAimPoint->target02_x + renge) {
                    if (_y >= pAimPoint->target02_y - renge) {
                        if (_y <= pAimPoint->target02_y + renge) {
                            if (_z >= pAimPoint->target02_z - renge) {
                                if (_z <= pAimPoint->target02_z + renge) {
                                    aim_status_ = PROG_AIM_AT_NOTHING_TARGET02_AFTER;
                                    goto AIM_AT_NOTHING_TARGET02_AFTER;
                                }
                            }
                        }
                    }
                }
            }
            aimChip(pAimPoint->target02_x,
                    pAimPoint->target02_y,
                    pAimPoint->target02_z );
        }
    }

    AIM_AT_NOTHING_TARGET02_AFTER:

    if (aim_status_ == PROG_AIM_AT_NOTHING_TARGET02_AFTER) {
        aimChip(_x + pAxsMver_->_velo_vx_mv*20+1,
                _y + pAxsMver_->_velo_vy_mv*20+1,
                _z + pAxsMver_->_velo_vz_mv*20+1 );
    }

    pAxsMver_->behave();
    WateringLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
}

void MyBunshinWateringLaserChip001::processSettlementBehavior() {
    //���g��FK�Ȃ̂ŁA��΍��W�̊m�肪 processSettlementBehavior() �ȍ~�ƂȂ邽�߁A�����ŏ����ݒ肪�K�v
    if (hasJustChangedToActive()) {
        //�����J�n����t���[���A�`�b�v�̑��x�ƌ����̏����ݒ�
        setFaceAngAs(pOrg_);
        positionAs(pOrg_);
        pAxsMver_->setVxyzMvVeloTwd(_rz, _ry, PX_C(100)); //�����͂�����
        pAxsMver_->setZeroVxyzMvAcce();
    }
    WateringLaserChip::processSettlementBehavior();
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

    if (_pLeader == this) {
        //�擪�͂�⑬�߂ɁBSGN(accX)*5 �����Z����̂́A�����x��0�ɂ��Ȃ�����
        pAxsMver->setVxyzMvAcce(accX*1.5 + SGN(accX)*5.0,
                                accY*1.5 + SGN(accY)*5.0,
                                accZ*1.5 + SGN(accZ)*5.0);
    } else {
        pAxsMver->setVxyzMvAcce(accX + SGN(accX)*3.0,
                                accY + SGN(accY)*3.0,
                                accZ + SGN(accZ)*3.0);
    }
    static const coord min_velo = MyBunshinWateringLaserChip001::MAX_VELO_RENGE/3;
    if (lVM < min_velo) {
        if (vVMx == 0 && vVMy == 0 && vVMz == 0) {
            GgafDxKuroko* pOrg_Kuroko = pOrg_->getKuroko();
            pAxsMver->setVxyzMvVelo(pOrg_Kuroko->_vX*min_velo,
                                    pOrg_Kuroko->_vY*min_velo,
                                    pOrg_Kuroko->_vZ*min_velo );
        } else {
            double t = (1.0 / sqrt(1.0*vVMx*vVMx + 1.0*vVMy*vVMy + 1.0*vVMz*vVMz)) * min_velo;
            pAxsMver->setVxyzMvVelo(vVMx*t, vVMy*t, vVMz*t);
        }
    }
}

void MyBunshinWateringLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    //�q�b�g�G�t�F�N�g
    UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g�o��

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
        if (pF) {
            MyBunshinWateringLaserChip001* pFF = (MyBunshinWateringLaserChip001*)(pF->getInfrontChip());
            if (pFF == nullptr) {
                //��[�`�b�v�i��[�̎��`�b�v�������j�Ȃ�΁A��[�ɏ��R�s�[�i��[�͓����蔻��Ȃ��̂�)
                if (pF == _pLeader) {
                    MyBunshin::AimPoint* pF_pAimPoint = pF->pAimPoint_;
                    if (pF_pAimPoint->pTarget == prm_pOtherActor && pF->aim_status_ == PROG_AIM_AT_LOCK_ON_TARGET01) {
                        //�ڕW�Ɍ������������ꍇ
                        pF_pAimPoint->target01_x = pF_pAimPoint->pTarget->_x;
                        pF_pAimPoint->target01_y = pF_pAimPoint->pTarget->_y;
                        pF_pAimPoint->target01_z = pF_pAimPoint->pTarget->_z;
                        pF_pAimPoint->is_enable_target01 = true;
                        pF->aim_status_ = PROG_AIM_AT_NOTHING_TARGET01_AFTER;
                    }
                }
            }
        }

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
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::onInactive() {

    if (_pLeader == this) {
        pAimPoint_->target02_x = _x;
        pAimPoint_->target02_y = _y;
        pAimPoint_->target02_z = _z;
        pAimPoint_->is_enable_target02 = true;
    }
    pOrg_ = nullptr;
    pLockon_ = nullptr;
    WateringLaserChip::onInactive();

//    pOrg_pLockonCtrler_pRingTarget_ = nullptr;
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

