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

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

const int MyBunshinWateringLaserChip001::max_velo_renge_ = 160000; //���̒l��傫������ƁA�ō����x�������Ȃ�B
const int MyBunshinWateringLaserChip001::r_max_acce_ = 20; //���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�
const double MyBunshinWateringLaserChip001::rr_max_acce_ = 1.0 / r_max_acce_; //�v�Z�ȑf���p
const float MyBunshinWateringLaserChip001::max_acce_renge_ = max_velo_renge_/r_max_acce_;

GgafDxCore::GgafDxModel* MyBunshinWateringLaserChip001::pModel_  = nullptr;
char MyBunshinWateringLaserChip001::aaTextureName[3][51];
int MyBunshinWateringLaserChip001::tex_no_ = 0;

MyBunshinWateringLaserChip001::MyBunshinWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyBunshinWateringLaserChip001", STATUS(MyBunshinWateringLaserChip001)) {
    _class_name = "MyBunshinWateringLaserChip001";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    default_stamina_ = getStatus()->get(STAT_Stamina);
    pOrg_ = nullptr;
    pOrg_pLockonCtrler_pRingTarget_ = nullptr;
    lockon_st_ = 0;
    is_lockon_ = false;
    GgafDxModel* pModel = getModel();
    if (!MyBunshinWateringLaserChip001::pModel_) {
        if (pModel->_num_materials != 3) {
            throwGgafCriticalException("MyBunshinWateringLaserChip001::onCreateModel() MyBunshinWateringLaserChip001���f���́A�}�e���A���R�K�v�ł��B");
        }
        for (DWORD i = 0; i < pModel->_num_materials; i ++) {
            strcpy(MyBunshinWateringLaserChip001::aaTextureName[i], pModel->_papTextureConnection[i]->peek()->getName());
        }
        MyBunshinWateringLaserChip001::pModel_ = pModel;
    }
}

void MyBunshinWateringLaserChip001::initialize() {
    getKuroko()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(80000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
    pAxsMver_->forceVxyzMvVeloRange(-max_velo_renge_, max_velo_renge_);
    pAxsMver_->forceVxyzMvAcceRange(-max_acce_renge_, max_acce_renge_);
}

void MyBunshinWateringLaserChip001::onCreateModel() {

}

void MyBunshinWateringLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);

    WateringLaserChip::onActive();

    //���b�N�I�����̈����p��
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_pLockonCtrler_pRingTarget_->getCurrent();
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (getFrontChip() == nullptr) {
            //��[�`�b�v
            lockon_st_ = 1;
        } else {
            //��[�ȊO
            MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getFrontChip();
            lockon_st_ = pF->lockon_st_;//��O�̃��b�N�I�����������p��
        }
    } else {
        if (getFrontChip() == nullptr) {
            //��[�`�b�v
            lockon_st_ = 0;
        } else {
            //��[�ȊO
            MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getFrontChip();
            lockon_st_ = pF->lockon_st_;//��O�̃��b�N�I�����������p��
        }
    }
}

void MyBunshinWateringLaserChip001::processBehavior() {
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_pLockonCtrler_pRingTarget_->getCurrent();
    if (getActiveFrame() > 7) {
        if (lockon_st_ == 1) {
            if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
                aimChip(pMainLockOnTarget->_x,
                        pMainLockOnTarget->_y,
                        pMainLockOnTarget->_z );
            } else {
                lockon_st_ = 2;
            }
        }
        if (lockon_st_ == 2) {
            if (_pLeader == this) {
                aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                        _y + pAxsMver_->_velo_vy_mv*2+1,
                        _z + pAxsMver_->_velo_vz_mv*2+1 );
            } else {
                aimChip(_pLeader->_x, _pLeader->_y, _pLeader->_z);
            }
        }
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
        pAxsMver_->setVxyzMvVeloTwd(_rz, _ry, PX_C(100));
        pAxsMver_->setZeroVxyzMvAcce();
    }
    WateringLaserChip::processSettlementBehavior();
}

void MyBunshinWateringLaserChip001::setOrg(MyBunshin* prm_pOrg) {
    pOrg_ = prm_pOrg;
    pOrg_pLockonCtrler_pRingTarget_ = pOrg_->pLockonCtrler_->pRingTarget_;
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
    //    |                        /    �^ |����| = 5*vM = lVM         |       �b
    //    |                   vT �I   �^                               |       �I
    //    |             ��       ^  �^                                 |       ��
    //    |               �_    / ��vM ���݂̈ړ������x�N�g��          |       �b
    //    | vVP ���������I  �_ /�^ (veloVxMv_,veloVyMv_,veloVzMv_)     |       �b
    //    |                   ��                                       |       ��
    // ---+------------------------------------------               ---+---------------------------
    //    |                                                            |
    //
    // vVP ���������������BvVP�����߂�I

    //�����I
    const int vTx = tX - _x;
    const int vTy = tY - _y;
    const int vTz = tZ - _z;

    //���������B��}�� |����| = 5*vM
    const int vVMx = pAxsMver_->_velo_vx_mv*5;
    const int vVMy = pAxsMver_->_velo_vy_mv*5;
    const int vVMz = pAxsMver_->_velo_vz_mv*5;

    //|����|
    const int lVM = MAX3(ABS(vVMx), ABS(vVMy), ABS(vVMz)); //�����x�N�g���傫���ȈՔ�
    //|�I|
    const int lT =  MAX3(ABS(vTx), ABS(vTy), ABS(vTz)); //�I�x�N�g���傫���ȈՔ�
    //|����|/|�I|      vT �̉��{�� vVT ���I �ɂȂ�̂������߂�B
    const double r = (lVM*1.5) / lT;
    //* 1.5�� �E��}�̂悤�Ɉ꒼���ɕ��񂾍ۂ��A�i�s�������ێ����邽�߂ɁA
    //|���I| > |����| �Ƃ����֌W���ێ����邽�߂ɂ������K���Ȋ���

    //vVP ���������I �̉����x�ݒ�
    const double accX = ((vTx * r) - vVMx) * rr_max_acce_;
    const double accY = ((vTy * r) - vVMy) * rr_max_acce_;
    const double accZ = ((vTz * r) - vVMz) * rr_max_acce_;

    if (_pLeader == this) {
        //�擪�͂�⑬�߂ɁBSGN(accX)*5 �����Z����̂́A�����x��0�ɂ��Ȃ�����
        pAxsMver_->setVxyzMvAcce(accX + SGN(accX)*5.0,
                                 accY + SGN(accY)*5.0,
                                 accZ + SGN(accZ)*5.0);
    } else {
        pAxsMver_->setVxyzMvAcce(accX + SGN(accX)*3.0,
                                 accY + SGN(accY)*3.0,
                                 accZ + SGN(accZ)*3.0);
    }
    //�l�W���`�悪�����Ȃ�Ȃ��悤�ɉ�]�𐧌�
    if (lVM > max_velo_renge_/2) {
        angle rz_temp, ry_temp;
        UTIL::convVectorToRzRy(vVMx, vVMy, vVMz, rz_temp, ry_temp);
        const angle angDRZ = UTIL::getAngDiff(rz_temp, _rz);
        const angle angDRY = UTIL::getAngDiff(ry_temp, _ry);
        if (-4000 <= angDRZ) {
            _rz -= 4000;
        } else if (angDRZ <= 4000) {
            _rz += 4000;
        } else {
            _rz += angDRZ;
        }
        if (-4000 <= angDRY) {
            _ry -= 4000;
        } else if (angDRY <= 4000) {
            _ry += 4000;
        } else {
            _ry += angDRY;
        }
        if (_rz >= D360ANG) {
            _rz -= D360ANG;
        }
        if (_rz < 0) {
            _rz += D360ANG;
        }
        if (_ry >= D360ANG) {
            _ry -= D360ANG;
        }
        if (_ry < 0) {
            _ry += D360ANG;
        }
    }
}

void MyBunshinWateringLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_pLockonCtrler_pRingTarget_->getCurrent();
    //�q�b�g�G�t�F�N�g
    UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g�o��

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //���ɃI�v�V�����̓��b�N�I����
            if (pOther == pMainLockOnTarget) {
                //�I�v�V�����̃��b�N�I���Ɍ������������ꍇ

                lockon_st_ = 2; //���b�N�I������߂�B�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
                if (getFrontChip() && getFrontChip()->getFrontChip() == nullptr) {
                    //���Ԑ擪�`�b�v���q�b�g�����ꍇ�A��[�ɂ��`����(��[�͓����蔻��Ȃ����ߒ��Ԑ擪�Ɠ��l�ɂ���)
                    ((MyBunshinWateringLaserChip001*)getFrontChip())->lockon_st_ = 2;
                }
            } else {
                //�I�v�V�����̃��b�N�I���ȊO�̃A�N�^�[�ɖ��������ꍇ
            }
        } else {
            //�I�v�V�����񃍃b�N�I�����ɖ��������ꍇ
        }

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //�ꌂ�Ń`�b�v���ł̍U����
            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I��
            if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }
            sayonara();
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
    WateringLaserChip::onInactive();
    lockon_st_ = 0;
    pOrg_ = nullptr;
    pOrg_pLockonCtrler_pRingTarget_ = nullptr;
}

void MyBunshinWateringLaserChip001::chengeTex(int prm_tex_no) {
    if (MyBunshinWateringLaserChip001::pModel_) {
        MyBunshinWateringLaserChip001::tex_no_ = prm_tex_no;
        MyBunshinWateringLaserChip001::pModel_->swapTopTextureOrder(aaTextureName[prm_tex_no]);
    }
}

MyBunshinWateringLaserChip001::~MyBunshinWateringLaserChip001() {
    GGAF_DELETE(pAxsMver_);
    MyBunshinWateringLaserChip001::pModel_ = nullptr;
}

