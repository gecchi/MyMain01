#include "stdafx.h"
#include "MyStraightLaserChip001.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


GgafDxCore::GgafDxModel* MyStraightLaserChip001::pModel_  = nullptr;
char MyStraightLaserChip001::aaTextureName[3][51];
int MyStraightLaserChip001::tex_no_ = 0;


MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "MyStraightLaserChip001", STATUS(MyStraightLaserChip001)) {
    _class_name = "MyStraightLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    _veloMv = 100000;
    pOrg_ = nullptr;
    lockon_st_ = 0;
    GgafDxModel* pModel = getModel();
    if (!MyStraightLaserChip001::pModel_) {
        if (pModel->_num_materials != 3) {
            throwGgafCriticalException("MyStraightLaserChip001::onCreateModel() MyStraightLaserChip001���f���́A�}�e���A���R�K�v�ł��B");
        }
        for (DWORD i = 0; i < pModel->_num_materials; i ++) {
            strcpy(MyStraightLaserChip001::aaTextureName[i], pModel->_papTextureConnection[i]->peek()->getName());
        }
        MyStraightLaserChip001::pModel_ = pModel;
    }
}

void MyStraightLaserChip001::initialize() {
    pOrg_ = P_MYSHIP;
    getKuroko()->setRzRyMvAng(0,0);
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB_WHD(0,120000,60000,60000);

    setHitAble(true);
    _sx = _sy = _sz = R_SC(5);
    _alpha = 0.99;
    _bounding_sphere_radius = 20.0;
}

void MyStraightLaserChip001::onCreateModel() {
}


void MyStraightLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    StraightLaserChip::onActive();

    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    getKuroko()->setMvVelo(80000);
    getKuroko()->setMvAcce(1000);
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (_pChip_front == nullptr) {
            //��[�`�b�v
            lockon_st_ = 1;
        } else {
            //��[�ȊO
            lockon_st_ = ((MyStraightLaserChip001*)_pChip_front)->lockon_st_;//��O�̃��b�N�I�����������p��
        }
    } else {
        if (_pChip_front == nullptr) {
            //��[�`�b�v
            lockon_st_ = 0;
        } else {
            //��[�ȊO
            lockon_st_ = ((MyStraightLaserChip001*)_pChip_front)->lockon_st_;//��O�̃��b�N�I�����������p��
        }
    }
}

void MyStraightLaserChip001::processBehavior() {
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();

    if (lockon_st_ == 1) {
        if (getActiveFrame() < 120) {
            if (pMainLockOnTarget) {
            } else {
                lockon_st_ = 2;
            }
        } else {
            lockon_st_ = 2;
        }
    }
    if (_pChip_front == nullptr) {
        getSeTx()->behave();
    }
    StraightLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
    //�������烌�[�U�[�\���̂��ߋ����I�ɍ��W�␳
    if (onChangeToActive()) {
        positionAs(pOrg_);
    }
}

void MyStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    //�q�b�g�G�t�F�N�g
    //����
    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //���ɃI�v�V�����̓��b�N�I����
            if (pOther == pMainLockOnTarget) {
                //�I�v�V�����̃��b�N�I���Ɍ������������ꍇ
                lockon_st_ = 2; //���b�N�I������߂�B�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
                if (_pChip_front && _pChip_front->_pChip_front == nullptr) {
                    //���Ԑ擪�`�b�v���q�b�g�����ꍇ�A��[�ɂ��`����
                    ((MyStraightLaserChip001*)_pChip_front)->lockon_st_ = 2;
                }
            } else {
                //�I�v�V�����̃��b�N�I���ȊO�̃A�N�^�[�ɖ��������ꍇ
            }
        } else {
            //�I�v�V�����񃍃b�N�I�����ɖ��������ꍇ
        }
        //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I�������݂�
        if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
            pOrg_->pLockonCtrler_->lockon(pOther);
        }

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //�ꌂ�Ń`�b�v���ł̍U����
            setHitAble(false);
            UTIL::activateExplosionEffectOf(this); //�j�󂳂ꂽ�G�t�F�N�g
            sayonara();
        } else {
            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
            getStatus()->set(STAT_Stamina, default_stamina_);
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this); //�j�󂳂ꂽ�G�t�F�N�g
        sayonara();
    }

}

void MyStraightLaserChip001::onInactive() {
    StraightLaserChip::onInactive();
    lockon_st_ = 0;
}

void MyStraightLaserChip001::chengeTex(int prm_tex_no) {
    if (MyStraightLaserChip001::pModel_) {
        MyStraightLaserChip001::tex_no_ = prm_tex_no;
        MyStraightLaserChip001::pModel_->swapTopTextureOrder(aaTextureName[prm_tex_no]);
    }
}

MyStraightLaserChip001::~MyStraightLaserChip001() {
    MyStraightLaserChip001::pModel_ = nullptr;
}


