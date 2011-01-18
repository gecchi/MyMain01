#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyCurveLaserChip001::MyCurveLaserChip001(const char* prm_name) :
        CurveLaserChip(prm_name, "MyCurveLaserChip001") {
    _class_name = "MyCurveLaserChip001";
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    _pOrg = NULL;
    _lockon = 0;

}

void MyCurveLaserChip001::initialize() {
    _pMover->relateRzRyFaceAngToMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    _SX = _SY = _SZ = 6 * 1000;
    _fAlpha = 0.99f;
    _fBoundingSphereRadius = 60.0f;

}

void MyCurveLaserChip001::onActive() {
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    CurveLaserChip::onActive();
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    _pMover->setMvVelo(0);
    _pMover->setVxMvAcce(0);
    _pMover->setVyMvAcce(0);
    _pMover->setVzMvAcce(0);
    _isLockon = false;
    if (pMainLockOnTarget && pMainLockOnTarget->isActive()) {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            _lockon = 1;
            _isLockon = true;
        } else {
            //��[�ȊO
            _lockon = ((MyCurveLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
            _isLockon = ((MyCurveLaserChip001*) _pChip_front)->_isLockon;//��O�̃��b�N�I�����������p��
        }
    } else {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            _lockon = 0;
        } else {
            //��[�ȊO
            _lockon = ((MyCurveLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
            _isLockon = ((MyCurveLaserChip001*) _pChip_front)->_isLockon;//��O�̃��b�N�I�����������p��
        }
    }
    _renge = 150000;
    _pMover->forceVxMvVeloRange(-_renge, _renge);
    _pMover->forceVyMvVeloRange(-_renge, _renge);
    _pMover->forceVzMvVeloRange(-_renge, _renge);
    _maxAcceRange= _renge / 30;
    _pMover->forceVxMvAcceRange(-_maxAcceRange, _maxAcceRange);
    _pMover->forceVyMvAcceRange(-_maxAcceRange, _maxAcceRange);
    _pMover->forceVzMvAcceRange(-_maxAcceRange, _maxAcceRange);


}

void MyCurveLaserChip001::processBehavior() {
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();

    if (_lockon == 1) {
        if (getActivePartFrame() < 120) {
            _maxAcceRange+=100;
            _pMover->forceVxMvAcceRange(-_maxAcceRange, _maxAcceRange);
            _pMover->forceVyMvAcceRange(-_maxAcceRange, _maxAcceRange);
            _pMover->forceVzMvAcceRange(-_maxAcceRange, _maxAcceRange);
//            if (_pOrg->_pLockonTarget && _pOrg->_pLockonTarget->isActive() && _pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) > 0) {
                                                                                 //�̗͂̔���̓I�v�V�������ōs�����Ƃɂ���
            if (pMainLockOnTarget) {
                if (pMainLockOnTarget->isActive()) {
                    float rate = 8.0 - 0.06*getActivePartFrame(); //0.06 * 120 = 8.0
                    rate = rate > 0 ? rate : 0;
                    int fdx = pMainLockOnTarget->_X - (_X + _pMover->_veloVxMv*rate);
                    int fdy = pMainLockOnTarget->_Y - (_Y + _pMover->_veloVyMv*rate);
                    int fdz = pMainLockOnTarget->_Z - (_Z + _pMover->_veloVzMv*rate);
                    _pMover->setVxMvAcce(fdx);
                    _pMover->setVyMvAcce(fdy);
                    _pMover->setVzMvAcce(fdz);
                } else {


                }
            } else {
                _lockon = 2;
            }
        } else {
            _lockon = 2;
        }
    }



    int dx, dy, dz;
    if (_lockon == 2) {
        if (_isLockon) {
            _isLockon = false;
            //��[�Ȃ�Γ��ʂɁA�I�v�V�����̔��΂̍��W���^�[�Q�b�g����
            if (_pChip_front == NULL) {
                _new_target_X = _X + (_X - _pOrg->_X);
                _new_target_Y = _Y + (_Y - _pOrg->_Y);
                _new_target_Z = _Z + (_Z - _pOrg->_Z);
                dx = _new_target_X - (_X );
                dy = _new_target_Y - (_Y );
                dz = _new_target_Z - (_Z );
                _pMover->setVxMvAcce(dx);
                _pMover->setVyMvAcce(dy);
                _pMover->setVzMvAcce(dz);
            }
        }



        _maxAcceRange+=100;
        _pMover->forceVxMvAcceRange(-_maxAcceRange, _maxAcceRange);
        _pMover->forceVyMvAcceRange(-_maxAcceRange, _maxAcceRange);
        _pMover->forceVzMvAcceRange(-_maxAcceRange, _maxAcceRange);

        if (_pChip_front == NULL) {
            _maxAcceRange+=100;
            //��̏����P��ƁA���� _maxAcceRange+=100;
        } else if (_pChip_front->_pChip_front == NULL) {
            //�V���ȃ^�[�Q�b�g���쐬
            dx = _pChip_front->_X - (_X + _pMover->_veloVxMv);
            dy = _pChip_front->_Y - (_Y + _pMover->_veloVyMv);
            dz = _pChip_front->_Z - (_Z + _pMover->_veloVzMv);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
        } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
            dx = _pChip_front->_pChip_front->_X - (_X + _pMover->_veloVxMv*2);
            dy = _pChip_front->_pChip_front->_Y - (_Y + _pMover->_veloVyMv*2);
            dz = _pChip_front->_pChip_front->_Z - (_Z + _pMover->_veloVzMv*2);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == NULL) {
            dx = _pChip_front->_pChip_front->_pChip_front->_X - (_X + _pMover->_veloVxMv*3);
            dy = _pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pMover->_veloVyMv*3);
            dz = _pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pMover->_veloVzMv*3);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
        } else {
            dx = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_X - (_X + _pMover->_veloVxMv*3);
            dy = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pMover->_veloVyMv*3);
            dz = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pMover->_veloVzMv*3);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
        }
    }
    if (_pChip_front == NULL) {
        _pSeTransmitter->behave();
    }

//    if (pMainLockOnTarget && pMainLockOnTarget->isActive()) {
//        _lockon = 1;
//        _isLockon = true;
//    }


    CurveLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������

    //�������烌�[�U�[�\���̂��ߋ����I�ɍ��W�␳
    if (onChangeToActive()) {
        setCoordinateBy(_pOrg);
        _tmpX = _X;
        _tmpY = _Y;
        _tmpZ = _Z;
    }

}

void MyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
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
                    ((MyCurveLaserChip001*)_pChip_front)->_lockon = 2;
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
            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDispatcher_EffectExplosion001->employ();
            if (pExplo001) {
                pExplo001->setCoordinateBy(this);
                pExplo001->activate();
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
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001) {
            pExplo001->setCoordinateBy(this);
            pExplo001->activate();
        }
        sayonara();
    }
}
//void MyCurveLaserChip001::processFinal() {
//    CurveLaserChip::processFinal();
//    //���b�N�I�������łȂ�΁A�؂�
//    if (_pOrg->_pLockonTarget) {
//        if (_pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) <= 0) {
//            _lockon = 2; //�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
//        }
//    }
//}

void MyCurveLaserChip001::onInactive() {
    CurveLaserChip::onInactive();
    _lockon = 0;
}

MyCurveLaserChip001::~MyCurveLaserChip001() {
}

