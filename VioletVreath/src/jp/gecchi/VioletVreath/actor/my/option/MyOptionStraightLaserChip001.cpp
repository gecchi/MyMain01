#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MyOptionStraightLaserChip001::MyOptionStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "MyOptionStraightLaserChip001", STATUS(MyOptionStraightLaserChip001)) {
    _class_name = "MyOptionStraightLaserChip001";
    default_stamina_ = _pStatus->get(STAT_Stamina);
    _veloMv = 100000;
    
    pOrg_ = NULL;
    lockon_st_ = 0;
    is_lockon_ = false;
}

void MyOptionStraightLaserChip001::initialize() {
    _pKurokoA->setRzRyMvAng(0,0);
    registHitAreaCube(60000);
    setHitAble(true);
    _SX = _SY = _SZ = R_SC(5);
    _alpha = 0.99;
    _bounding_sphere_radius = 20.0;


}
void MyOptionStraightLaserChip001::onActive() {
    _pStatus->reset();
    default_stamina_ = _pStatus->get(STAT_Stamina);
    StraightLaserChip::onActive();

    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();
    _pKurokoA->setMvVelo(80000);
    _pKurokoA->setMvAcce(300);
    is_lockon_ = false;
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            lockon_st_ = 1;
            is_lockon_ = true;
        } else {
            //��[�ȊO
            lockon_st_ = ((MyOptionStraightLaserChip001*) _pChip_front)->lockon_st_;//��O�̃��b�N�I�����������p��
            is_lockon_ = ((MyOptionStraightLaserChip001*) _pChip_front)->is_lockon_;//��O�̃��b�N�I�����������p��
        }
    } else {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            lockon_st_ = 0;
        } else {
            //��[�ȊO
            lockon_st_ = ((MyOptionStraightLaserChip001*) _pChip_front)->lockon_st_;//��O�̃��b�N�I�����������p��
            is_lockon_ = ((MyOptionStraightLaserChip001*) _pChip_front)->is_lockon_;//��O�̃��b�N�I�����������p��
        }
    }

}



void MyOptionStraightLaserChip001::processBehavior() {
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();


    if (lockon_st_ == 1) {
        if (getActivePartFrame() < 120) {
            if (pMainLockOnTarget) {
            } else {
                lockon_st_ = 2;
            }
        } else {
            lockon_st_ = 2;
        }
    }
    if (lockon_st_ == 2) {
        if (is_lockon_) {
            is_lockon_ = false;
//            if (_pChip_front == NULL) {
//            }
        }
//        if (_pChip_front == NULL) {
//        } else if (_pChip_front->_pChip_front == NULL) {
//        } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
//        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == NULL) {
//        } else {
//        }
    }
    if (_pChip_front == NULL) {
        _pSeTx->behave();
    }
    StraightLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
    //�������烌�[�U�[�\���̂��ߋ��G�ɍ��W�␳
    //�������烌�[�U�[�\���̂��ߋ����I�ɍ��W�␳
    if (onChangeToActive()) {
        locatedBy(pOrg_);
//        _tmpX = _X;
//        _tmpY = _Y;
//        _tmpZ = _Z;
    }
}



void MyOptionStraightLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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




void MyOptionStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();
    //�q�b�g�G�t�F�N�g
    //����

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //���ɃI�v�V�����̓��b�N�I����
            if (pOther == pMainLockOnTarget) {
                //�I�v�V�����̃��b�N�I���Ɍ������������ꍇ

                lockon_st_ = 2; //���b�N�I������߂�B�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
                    //���Ԑ擪�`�b�v���q�b�g�����ꍇ�A��[�ɂ��`����
                    ((MyOptionStraightLaserChip001*)_pChip_front)->lockon_st_ = 2;
                }
            } else {
                //�I�v�V�����̃��b�N�I���ȊO�̃A�N�^�[�ɖ��������ꍇ
            }
        } else {
            //�I�v�V�����񃍃b�N�I�����ɖ��������ꍇ
        }

        int stamina = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
        if (stamina <= 0) {
            //�ꌂ�Ń`�b�v���ł̍U����

            //�j�󂳂ꂽ�G�t�F�N�g
            EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
            if (pExplo001) {
                pExplo001->locatedBy(this);
            }
            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I��
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrlr_->lockon(pOther);
            }
            sayonara();
        } else {
            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
            _pStatus->set(STAT_Stamina, default_stamina_);
            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I��
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrlr_->lockon(pOther);
            }
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�

        //�j�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locatedBy(this);
        }
        sayonara();
    }
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//
//
//    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
//        int stamina = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
//        if (stamina <= 0) {
//            //�ꌂ�Ń`�b�v���ł̍U����
//
//            //�j�󂳂ꂽ�G�t�F�N�g
//            EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
//            if (pExplo001) {
//                pExplo001->locatedBy(this);
//                pExplo001->activate();
//            }
//            sayonara();
//        } else {
//            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
//            _pStatus->set(STAT_Stamina, default_stamina_);
//        }
//    } else if (pOther->getKind() & KIND_CHIKEI) {
//        //�n�`����͖��������悤�Ȃ�
//        //�j�󂳂ꂽ�G�t�F�N�g
//        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
//        if (pExplo001) {
//            pExplo001->locatedBy(this);
//        }
//        sayonara();
//    }

}
void MyOptionStraightLaserChip001::onInactive() {
    StraightLaserChip::onInactive();
    lockon_st_ = 0;
}

MyOptionStraightLaserChip001::~MyOptionStraightLaserChip001() {
}

