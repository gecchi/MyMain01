#include "stdafx.h"
#include "MyOptionWateringLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



GgafDxCore::GgafDxModel* MyOptionWateringLaserChip001::pModel_  = nullptr;
char MyOptionWateringLaserChip001::aaTextureName[3][51];
int MyOptionWateringLaserChip001::tex_no_ = 0;


MyOptionWateringLaserChip001::MyOptionWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyOptionWateringLaserChip001", STATUS(MyOptionWateringLaserChip001)) {
    _class_name = "MyOptionWateringLaserChip001";
    default_stamina_ = _pStatus->get(STAT_Stamina);
    pOrg_ = nullptr;
    lockon_st_ = 0;
    is_lockon_ = false;
    max_acce_renge_ = 0;
    max_velo_renge_ = 160000; //���̒l��傫������ƁA�ō����x�������Ȃ�B
    r_max_acce_ = 20; //���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�
    rr_max_acce_ = 1.0 / r_max_acce_; //�v�Z�ȑf���p
    if (!MyOptionWateringLaserChip001::pModel_) {
        if (_pModel->_num_materials != 3) {
            throwGgafCriticalException("MyOptionWateringLaserChip001::onCreateModel() MyOptionWateringLaserChip001���f���́A�}�e���A���R�K�v�ł��B");
        }
        for (DWORD i = 0; i < _pModel->_num_materials; i ++) {
            strcpy(MyOptionWateringLaserChip001::aaTextureName[i], _pModel->_papTextureConnection[i]->peek()->getName());
        }
        MyOptionWateringLaserChip001::pModel_ = _pModel;
    }
}

void MyOptionWateringLaserChip001::initialize() {
    _pKurokoA->relateFaceWithMvAng(true);
    registerHitAreaCube_AutoGenMidColli(80000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
}

void MyOptionWateringLaserChip001::onCreateModel() {

}

void MyOptionWateringLaserChip001::onActive() {
    _pStatus->reset();
    default_stamina_ = _pStatus->get(STAT_Stamina);
    WateringLaserChip::onActive();
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (_pChip_front == nullptr) {
            //��[�`�b�v
            lockon_st_ = 1;
        } else {
            //��[�ȊO
            MyOptionWateringLaserChip001* pF = (MyOptionWateringLaserChip001*) _pChip_front;
            lockon_st_ = pF->lockon_st_;//��O�̃��b�N�I�����������p��
        }
    } else {
        if (_pChip_front == nullptr) {
            //��[�`�b�v
            lockon_st_ = 0;
        } else {
            //��[�ȊO
            MyOptionWateringLaserChip001* pF = (MyOptionWateringLaserChip001*) _pChip_front;
            lockon_st_ = pF->lockon_st_;//��O�̃��b�N�I�����������p��
        }
    }
    _pKurokoB->setZeroVxyzMvAcce(); //�����x���Z�b�g
    //Vxyz�̑��x�̓I�v�V�������Őݒ肳���


    _pKurokoB->forceVxyzMvVeloRange(-max_velo_renge_, max_velo_renge_);
    max_acce_renge_ = max_velo_renge_/r_max_acce_;
    _pKurokoB->forceVxyzMvAcceRange(-max_acce_renge_, max_acce_renge_);
}

void MyOptionWateringLaserChip001::processBehavior() {
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    if (getActiveFrame() > 6) {
        if (lockon_st_ == 1) {
            if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
                moveChip(pMainLockOnTarget->_x,
                         pMainLockOnTarget->_y,
                         pMainLockOnTarget->_z );
            } else {
                //_pKurokoB->setZeroVxyzMvAcce();
                lockon_st_ = 2;
            }
        }

        if (lockon_st_ == 2) {
            if (_pLeader) {
                if (_pLeader == this) {
                    moveChip(_x + _pKurokoB->_veloVxMv*4+1,
                             _y + _pKurokoB->_veloVyMv*2+1,
                             _z + _pKurokoB->_veloVzMv*2+1 );
                } else {
                    moveChip(_pLeader->_x, _pLeader->_y, _pLeader->_z);
                }
            }
        }
    }

    WateringLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
    //�������烌�[�U�[�\���̂��ߋ����I�ɍ��W�␳
    if (onChangeToActive()) {
        positionAs(pOrg_);
        _tmpX = _x;
        _tmpY = _y;
        _tmpZ = _z;
    }

}

void MyOptionWateringLaserChip001::moveChip(int tX, int tY, int tZ) {
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
    int vTx = tX - _x;
    int vTy = tY - _y;
    int vTz = tZ - _z;

    //���������B��}�� |����| = 5*vM
    int vVMx = _pKurokoB->_veloVxMv*5;
    int vVMy = _pKurokoB->_veloVyMv*5;
    int vVMz = _pKurokoB->_veloVzMv*5;

    //|����|
    int lVM = MAX3(ABS(vVMx), ABS(vVMy), ABS(vVMz)); //�����x�N�g���傫���ȈՔ�
    //|�I|
    int lT =  MAX3(ABS(vTx), ABS(vTy), ABS(vTz)); //�I�x�N�g���傫���ȈՔ�
    //|����|/|�I|      vT �̉��{�� vVT ���I �ɂȂ�̂������߂�B
    double r = (lVM*1.5) / lT;
    //* 2�� �E��}�̂悤�Ɉ꒼���ɕ��񂾍ۂ��A�i�s�������ێ����邽�߂ɁA
    //|���I| > |����| �Ƃ����֌W���ێ����邽�߂ɂ������K���Ȋ���

    //vVP ���������I �̉����x�ݒ�
    double accX = ((vTx * r) - vVMx) * rr_max_acce_;
    double accY = ((vTy * r) - vVMy) * rr_max_acce_;
    double accZ = ((vTz * r) - vVMz) * rr_max_acce_;

    if (_pChip_front == nullptr) {
        //�擪�͂�⑬�߂ɁBSGN(accX)*5 �����Z����̂́A�����x��0�ɂ��Ȃ�����
        _pKurokoB->setVxyzMvAcce(accX + SGN(accX)*5.0,
                                 accY + SGN(accY)*5.0,
                                 accZ + SGN(accZ)*5.0);
    } else {
        _pKurokoB->setVxyzMvAcce(accX + SGN(accX)*3.0,
                                 accY + SGN(accY)*3.0,
                                 accZ + SGN(accZ)*3.0);
    }
    //�l�W���`�悪�����Ȃ�Ȃ��悤�ɉ�]�𐧌�
    if (lVM > max_velo_renge_/2) {
        angle rz_temp, ry_temp;
        UTIL::convVectorToRzRy(vVMx, vVMy, vVMz, rz_temp, ry_temp);
        angle angDRZ = UTIL::getAngDiff(rz_temp, _rz);
        angle angDRY = UTIL::getAngDiff(ry_temp, _ry);
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

void MyOptionWateringLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void MyOptionWateringLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    //�q�b�g�G�t�F�N�g
    UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g�o��

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //���ɃI�v�V�����̓��b�N�I����
            if (pOther == pMainLockOnTarget) {
                //�I�v�V�����̃��b�N�I���Ɍ������������ꍇ

                lockon_st_ = 2; //���b�N�I������߂�B�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
                if (_pChip_front && _pChip_front->_pChip_front == nullptr) {
                    //���Ԑ擪�`�b�v���q�b�g�����ꍇ�A��[�ɂ��`����(��[�͓����蔻��Ȃ����ߒ��Ԑ擪�Ɠ��l�ɂ���)
                    ((MyOptionWateringLaserChip001*)_pChip_front)->lockon_st_ = 2;
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
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }
            sayonara();
        } else {
            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
            _pStatus->set(STAT_Stamina, default_stamina_);
            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I��
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�
        sayonara();
    }
}

void MyOptionWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
    lockon_st_ = 0;
}

void MyOptionWateringLaserChip001::chengeTex(int prm_tex_no) {
    if (MyOptionWateringLaserChip001::pModel_) {
        MyOptionWateringLaserChip001::tex_no_ = prm_tex_no;
        MyOptionWateringLaserChip001::pModel_->swapTopTextureOrder(aaTextureName[prm_tex_no]);
    }
}

MyOptionWateringLaserChip001::~MyOptionWateringLaserChip001() {
    MyOptionWateringLaserChip001::pModel_ = nullptr;
}

