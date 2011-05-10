#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyOptionCurveLaserChip001::MyOptionCurveLaserChip001(const char* prm_name) :
        CurveLaserChip(prm_name, "MyOptionCurveLaserChip001") {
    _class_name = "MyOptionCurveLaserChip001";
    MyStgUtil::resetMyOptionCurveLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    _pOrg = NULL;
    _lockon = 0;
    _isLockon = false;
}

void MyOptionCurveLaserChip001::initialize() {
    _pKuroko->relateRzRyFaceAngToMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    _SX = _SY = _SZ = 6 * 1000;
    _fAlpha = 0.99f;
    _radius_bounding_sphere = 60.0f;

}

void MyOptionCurveLaserChip001::onActive() {
    MyStgUtil::resetMyOptionCurveLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    CurveLaserChip::onActive();
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    _pKuroko->setMvVelo(0);
    _pKuroko->setVxMvAcce(0);
    _pKuroko->setVyMvAcce(0);
    _pKuroko->setVzMvAcce(0);
    _isLockon = false;
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            _lockon = 1;
            _isLockon = true;
        } else {
            //��[�ȊO
            _lockon = ((MyOptionCurveLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
            _isLockon = ((MyOptionCurveLaserChip001*) _pChip_front)->_isLockon;//��O�̃��b�N�I�����������p��
        }
    } else {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            _lockon = 0;
        } else {
            //��[�ȊO
            _lockon = ((MyOptionCurveLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
            _isLockon = ((MyOptionCurveLaserChip001*) _pChip_front)->_isLockon;//��O�̃��b�N�I�����������p��
        }
    }
    _renge = 150000;
    _pKuroko->forceVxyzMvVeloRange(-_renge, _renge);
    _maxAcceRange= _renge / 30;
    _pKuroko->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);


}

void MyOptionCurveLaserChip001::processBehavior() {
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();

    if (_lockon == 1) {
        if (getActivePartFrame() < 120) {
            _maxAcceRange+=100;
            _pKuroko->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
//            if (_pOrg->_pLockonTarget && _pOrg->_pLockonTarget->isActiveActor() && _pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) > 0) {
                                                                                 //�̗͂̔���̓I�v�V�������ōs�����Ƃɂ���
            if (pMainLockOnTarget) {
                if (pMainLockOnTarget->isActiveActor()) {
                    float rate = 8.0 - 0.06*getActivePartFrame(); //0.06 * 120 = 8.0
                    rate = rate > 0 ? rate : 0;
                    int fdx = pMainLockOnTarget->_X - (_X + _pKuroko->_veloVxMv*rate);
                    int fdy = pMainLockOnTarget->_Y - (_Y + _pKuroko->_veloVyMv*rate);
                    int fdz = pMainLockOnTarget->_Z - (_Z + _pKuroko->_veloVzMv*rate);
                    _pKuroko->setVxMvAcce(fdx);
                    _pKuroko->setVyMvAcce(fdy);
                    _pKuroko->setVzMvAcce(fdz);
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
                _pKuroko->setVxMvAcce(dx);
                _pKuroko->setVyMvAcce(dy);
                _pKuroko->setVzMvAcce(dz);
            }
        }



        _maxAcceRange+=100;
        _pKuroko->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
        if (_pChip_front == NULL) {
            _maxAcceRange+=100;
            //��̏����P��ƁA���� _maxAcceRange+=100;
        } else if (_pChip_front->_pChip_front == NULL) {
            //�V���ȃ^�[�Q�b�g���쐬
            dx = _pChip_front->_X - (_X + _pKuroko->_veloVxMv);
            dy = _pChip_front->_Y - (_Y + _pKuroko->_veloVyMv);
            dz = _pChip_front->_Z - (_Z + _pKuroko->_veloVzMv);
            _pKuroko->setVxMvAcce(dx);
            _pKuroko->setVyMvAcce(dy);
            _pKuroko->setVzMvAcce(dz);
        } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
            dx = _pChip_front->_pChip_front->_X - (_X + _pKuroko->_veloVxMv*2);
            dy = _pChip_front->_pChip_front->_Y - (_Y + _pKuroko->_veloVyMv*2);
            dz = _pChip_front->_pChip_front->_Z - (_Z + _pKuroko->_veloVzMv*2);
            _pKuroko->setVxMvAcce(dx);
            _pKuroko->setVyMvAcce(dy);
            _pKuroko->setVzMvAcce(dz);
        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == NULL) {
            dx = _pChip_front->_pChip_front->_pChip_front->_X - (_X + _pKuroko->_veloVxMv*3);
            dy = _pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pKuroko->_veloVyMv*3);
            dz = _pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pKuroko->_veloVzMv*3);
            _pKuroko->setVxMvAcce(dx);
            _pKuroko->setVyMvAcce(dy);
            _pKuroko->setVzMvAcce(dz);
        } else {
            dx = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_X - (_X + _pKuroko->_veloVxMv*3);
            dy = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pKuroko->_veloVyMv*3);
            dz = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pKuroko->_veloVzMv*3);
            _pKuroko->setVxMvAcce(dx);
            _pKuroko->setVyMvAcce(dy);
            _pKuroko->setVzMvAcce(dz);
        }
    }
    if (_pChip_front == NULL) {
        _pSeTransmitter->behave();
    }

//    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
//        _lockon = 1;
//        _isLockon = true;
//    }

//    _pKuroko->_angFace[AXIS_X] =  _pOrg->_pKuroko->_angFace[AXIS_Y];
    CurveLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������

    //�������烌�[�U�[�\���̂��ߋ����I�ɍ��W�␳
    if (onChangeToActive()) {
        locateAs(_pOrg);
        _tmpX = _X;
        _tmpY = _Y;
        _tmpZ = _Z;
    }

}

void MyOptionCurveLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void MyOptionCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
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
                    ((MyOptionCurveLaserChip001*)_pChip_front)->_lockon = 2;
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
            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
            if (pExplo001) {
                pExplo001->locateAs(this);
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
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->activate();
        }
        sayonara();
    }
}
//void MyOptionCurveLaserChip001::processFinal() {
//    CurveLaserChip::processFinal();
//    //���b�N�I�������łȂ�΁A�؂�
//    if (_pOrg->_pLockonTarget) {
//        if (_pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) <= 0) {
//            _lockon = 2; //�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
//        }
//    }
//}

void MyOptionCurveLaserChip001::onInactive() {
    CurveLaserChip::onInactive();
    _lockon = 0;
}

MyOptionCurveLaserChip001::~MyOptionCurveLaserChip001() {
}
