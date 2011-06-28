#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


MyOptionStraightLaserChip001::MyOptionStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "MyOptionStraightLaserChip001") {
    _class_name = "MyOptionStraightLaserChip001";
    MyStgUtil::resetMyOptionStraightLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    _veloMv = 100000;


    _pOrg = NULL;
    _lockon = 0;
    _isLockon = false;
}

void MyOptionStraightLaserChip001::initialize() {
    _pKurokoA->setRzRyMvAng(0,0);
    registHitAreaCube(60000);
    setHitAble(true);
    _SX = _SY = _SZ = 5 * 1000;
    _fAlpha = 0.99;
    _radius_bounding_sphere = 20.0;


}
void MyOptionStraightLaserChip001::onActive() {


    MyStgUtil::resetMyOptionStraightLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    StraightLaserChip::onActive();

    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    _pKurokoA->setMvVelo(80000);
    _pKurokoA->setMvAcce(300);
    _isLockon = false;
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            _lockon = 1;
            _isLockon = true;
        } else {
            //��[�ȊO
            _lockon = ((MyOptionStraightLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
            _isLockon = ((MyOptionStraightLaserChip001*) _pChip_front)->_isLockon;//��O�̃��b�N�I�����������p��
        }
    } else {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            _lockon = 0;
        } else {
            //��[�ȊO
            _lockon = ((MyOptionStraightLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
            _isLockon = ((MyOptionStraightLaserChip001*) _pChip_front)->_isLockon;//��O�̃��b�N�I�����������p��
        }
    }

}



void MyOptionStraightLaserChip001::processBehavior() {
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();


    if (_lockon == 1) {
        if (getActivePartFrame() < 120) {
            if (pMainLockOnTarget) {
            } else {
                _lockon = 2;
            }
        } else {
            _lockon = 2;
        }
    }
    if (_lockon == 2) {
        if (_isLockon) {
            _isLockon = false;
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
        _pSeTransmitter->behave();
    }
    StraightLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
    //�������烌�[�U�[�\���̂��ߋ��G�ɍ��W�␳
    //�������烌�[�U�[�\���̂��ߋ����I�ɍ��W�␳
    if (onChangeToActive()) {
        locateAs(_pOrg);
//        _tmpX = _X;
//        _tmpY = _Y;
//        _tmpZ = _Z;
    }
}



void MyOptionStraightLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}




void MyOptionStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*) prm_pOtherActor;
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    //�q�b�g�G�t�F�N�g
    //����

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //���ɃI�v�V�����̓��b�N�I����
            if (pOther == pMainLockOnTarget) {
                //�I�v�V�����̃��b�N�I���Ɍ������������ꍇ

                _lockon = 2; //���b�N�I������߂�B�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
                    //���Ԑ擪�`�b�v���q�b�g�����ꍇ�A��[�ɂ��`����
                    ((MyOptionStraightLaserChip001*)_pChip_front)->_lockon = 2;
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
            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
            if (pExplo001) {
                pExplo001->locateAs(this);
            }
            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I��
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                _pOrg->_pLockonController->lockon(pOther);
            }
            sayonara();
        } else {
            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
            _pStatus->set(STAT_Stamina, _default_stamina);
            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I��
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                _pOrg->_pLockonController->lockon(pOther);
            }
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�

        //�j�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        sayonara();
    }
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//
//
//    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
//        int stamina = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
//        if (stamina <= 0) {
//            //�ꌂ�Ń`�b�v���ł̍U����
//
//            //�j�󂳂ꂽ�G�t�F�N�g
//            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
//            if (pExplo001) {
//                pExplo001->locateAs(this);
//                pExplo001->activate();
//            }
//            sayonara();
//        } else {
//            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
//            _pStatus->set(STAT_Stamina, _default_stamina);
//        }
//    } else if (pOther->getKind() & KIND_CHIKEI) {
//        //�n�`����͖��������悤�Ȃ�
//        //�j�󂳂ꂽ�G�t�F�N�g
//        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
//        if (pExplo001) {
//            pExplo001->locateAs(this);
//        }
//        sayonara();
//    }

}
void MyOptionStraightLaserChip001::onInactive() {
    StraightLaserChip::onInactive();
    _lockon = 0;
}

MyOptionStraightLaserChip001::~MyOptionStraightLaserChip001() {
}

