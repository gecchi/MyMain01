#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) ( (a)>(b) ? ((a)>(c)?(a):(c)) : ((b)>(c)?(b):(c)) )
//((a) > (MAX2(b, c)) ? (a) : (MAX2(b, c)))

//if (a>b) {
//    if (a>c) {
//        return a;
//    } else { //(a<=c)
//        return c;
//    }
//} else { //(a<=b)
//    if (b>c) {
//        return b;
//    } else { //(b<=c)
//        return c;
//    }
//}
//
//( a>b ? ( a>c ? a : c ) : ( b>c ? b : c ) )


MyOptionWateringLaserChip001::MyOptionWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyOptionWateringLaserChip001") {
    _class_name = "MyOptionWateringLaserChip001";
    MyStgUtil::resetMyOptionWateringLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    _pOrg = NULL;
    _lockon = 0;
    _isLockon = false;
}

void MyOptionWateringLaserChip001::initialize() {
    _pMvNavigator->relateFaceAngWithMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    setScaleRate(6.0);
    setAlpha(0.99);
}

void MyOptionWateringLaserChip001::onActive() {
    MyStgUtil::resetMyOptionWateringLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    WateringLaserChip::onActive();
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            _lockon = 1;
        } else {
            //��[�ȊO
            _lockon = ((MyOptionWateringLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
        }
    } else {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            _lockon = 0;
        } else {
            //��[�ȊO
            _lockon = ((MyOptionWateringLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
        }
    }
    _jerkVx = _jerkVy = _jerkVz = 0;      //���x���Z�b�g
    _pMvTransporter->setZeroVxyzMvAcce(); //�����x���Z�b�g
    //Vxyz�̑��x�̓I�v�V�������Őݒ肳���

    _renge = 150000;
    _pMvTransporter->forceVxyzMvVeloRange(-_renge, _renge);
    _maxAcceRange= _renge/20;
    _pMvTransporter->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);

//    MyStgUtil::resetMyOptionWateringLaserChip001Status(_pStatus);
//    _default_stamina = _pStatus->get(STAT_Stamina);
//    WateringLaserChip::onActive();
//    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
//    _pMvNavigator->setMvVelo(0);
//    _pMvTransporter->setVxMvAcce(0);
//    _pMvTransporter->setVyMvAcce(0);
//    _pMvTransporter->setVzMvAcce(0);
//    _isLockon = false;
//    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
//        if (_pChip_front == NULL) {
//            //��[�`�b�v
//            _lockon = 1;
//            _isLockon = true;
//        } else {
//            //��[�ȊO
//            _lockon = ((MyOptionWateringLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
//            _isLockon = ((MyOptionWateringLaserChip001*) _pChip_front)->_isLockon;//��O�̃��b�N�I�����������p��
//        }
//    } else {
//        if (_pChip_front == NULL) {
//            //��[�`�b�v
//            _lockon = 0;
//        } else {
//            //��[�ȊO
//            _lockon = ((MyOptionWateringLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
//            _isLockon = ((MyOptionWateringLaserChip001*) _pChip_front)->_isLockon;//��O�̃��b�N�I�����������p��
//        }
//    }
//    _renge = 150000;
//    _pMvTransporter->forceVxyzMvVeloRange(-_renge, _renge);
//    _maxAcceRange= _renge / 30;
//    _pMvTransporter->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);


}

void MyOptionWateringLaserChip001::processBehavior() {
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();

    if (_lockon == 1) {
        if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
            //    |             vVT ���I                        |
            //    |                 ^                           |      ���I
            //    |  |���I| > 5*vM /                            |       �b
            //    |               /           ����              |       �b
            //    |              /         ��                   |      ����
            //    |             /        �^vVM                  |       �b
            //    |            /       �^                       |       �b
            //    |           /      �^                         |       �b
            //    |          /     �^                           |       �b
            //    |         /    �^                             |       �b
            //    |    vT �I   �^    |����| = 5*vM              |       �I
            //    |       /  �^                                 |       �b
            //    |      / ��vM                                 |       ��
            //    |     /�^ (_veloVxMv,_veloVyMv,_veloVzMv)     |       �b
            //    |    ��                                       |       ��
            // ---+---------------------------               ---+---------------------------
            //    |                                             |
            //
            //�����I
            int vTx = pMainLockOnTarget->_X - _X;
            int vTy = pMainLockOnTarget->_Y - _Y;
            int vTz = pMainLockOnTarget->_Z - _Z;
            //��������
            int vVMx = _pMvTransporter->_veloVxMv*5;
            int vVMy = _pMvTransporter->_veloVyMv*5;
            int vVMz = _pMvTransporter->_veloVzMv*5;

            //|����|
            int lVM = MAX3(abs(vVMx), abs(vVMy), abs(vVMz)); //�����x�N�g���傫���ȈՔ�
            //|�I|
            int lT =  MAX3(abs(vTx), abs(vTy), abs(vTz)); //�I�x�N�g���傫���ȈՔ�
            //|����|/|�I|
            double r = 1.5*lVM / lT;
            //�������I
//            int vVTx = vTx * r;
//            int vVTy = vTy * r;
//            int vVTz = vTz * r;
            //���������I
//            int vVMVTx = vVTx - vVMx;
//            int vVMVTy = vVTy - vVMy;
//            int vVMVTz = vVTz - vVMz;
//
//            _pMvTransporter->setVxMvAcce(vVMVTx/5/20);
//            _pMvTransporter->setVyMvAcce(vVMVTy/5/20);
//            _pMvTransporter->setVzMvAcce(vVMVTz/5/20);
            _pMvTransporter->setVxMvAcce(((vTx * r) - vVMx)/5/20);
            _pMvTransporter->setVyMvAcce(((vTy * r) - vVMy)/5/20);
            _pMvTransporter->setVzMvAcce(((vTz * r) - vVMz)/5/20);
        } else {
            //_pMvTransporter->setZeroVxyzMvAcce();
            _lockon = 2;
        }
    }

    if (_lockon == 2) {
        _maxAcceRange+=100;
        _pMvTransporter->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
        //��[�Ȃ�Γ��ʂɁA�I�v�V�����̔��΂̍��W���^�[�Q�b�g����
        if (_pChip_front == NULL) {
            _pMvTransporter->setVxMvAcce(_X - _pOrg->_X);
            _pMvTransporter->setVyMvAcce(_X - _pOrg->_X);
            _pMvTransporter->setVzMvAcce(_Z - _pOrg->_Z);
        } else {
            //�V���ȃ^�[�Q�b�g���쐬
            int dx = _pChip_front->_X - (_X + _pMvTransporter->_veloVxMv);
            int dy = _pChip_front->_Y - (_Y + _pMvTransporter->_veloVyMv);
            int dz = _pChip_front->_Z - (_Z + _pMvTransporter->_veloVzMv);
            _pMvTransporter->setVxMvAcce(dx);
            _pMvTransporter->setVyMvAcce(dy);
            _pMvTransporter->setVzMvAcce(dz);
        }

    }
//�Ȃ��p���������Ȃ�悤�Ɋ撣��Ηǂ�
//    ��                       ��
//    �` = (����, ����, ����)  �a �� (����, ����, ����)
//
//    �`�~�a �� (��������� - ���������,  ��������� - ���������,  ��������� �| ���������)
//
//    |�`�~�a| = |�`||�a|sin(��)

    WateringLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������




//    int TX = pMainLockOnTarget->_X - _X;
//    int TY = pMainLockOnTarget->_Y - _Y;
//    int TZ = pMainLockOnTarget->_Z - _Z;
//    int dot = _pMvTransporter->dot(TX,TY,TZ);
//    if (dot < _pMvTransporter->dot(TX+1000,TY,TZ)) {
//        _pMvTransporter->addVxMvAcce(-500);
//    } else {
//        _pMvTransporter->addVxMvAcce(+500);
//    }
//    if (dot < _pMvTransporter->dot(TX,TY+1000,TZ)) {
//        _pMvTransporter->addVyMvAcce(-500);
//    } else {
//        _pMvTransporter->addVyMvAcce(+500);
//    }
//    if (dot < _pMvTransporter->dot(TX,TY,TZ+1000)) {
//        _pMvTransporter->addVzMvAcce(-500);
//    } else {
//        _pMvTransporter->addVzMvAcce(+500);
//    }
//            int fdx = pMainLockOnTarget->_X - (_X + _pMvTransporter->_veloVxMv*5);
//            int fdy = pMainLockOnTarget->_Y - (_Y + _pMvTransporter->_veloVyMv*5);
//            int fdz = pMainLockOnTarget->_Z - (_Z + _pMvTransporter->_veloVzMv*5);
//            //velo : _renge = x : _maxAcceRange
//            // x = velo  _maxAcceRange / _renge
//            _pMvTransporter->addVxMvAcce(sgn(fdx)*((_pMvTransporter->_veloVxMv*_maxAcceRange) /_renge) );
//            _pMvTransporter->addVyMvAcce(sgn(fdy)*((_pMvTransporter->_veloVyMv*_maxAcceRange) /_renge) );
//            _pMvTransporter->addVzMvAcce(sgn(fdz)*((_pMvTransporter->_veloVzMv*_maxAcceRange) /_renge) );



//    int fdx = pMainLockOnTarget->_X - (_X + _pMvTransporter->_veloVxMv*5);
//    int fdy = pMainLockOnTarget->_Y - (_Y + _pMvTransporter->_veloVyMv*5);
//    int fdz = pMainLockOnTarget->_Z - (_Z + _pMvTransporter->_veloVzMv*5);
//    //velo : _renge = x : _maxAcceRange
//    // x = velo  _maxAcceRange / _renge
//    _pMvTransporter->addVxMvAcce(sgn(fdx)*((_pMvTransporter->_veloVxMv*_maxAcceRange) /_renge) );
//    _pMvTransporter->addVyMvAcce(sgn(fdy)*((_pMvTransporter->_veloVyMv*_maxAcceRange) /_renge) );
//    _pMvTransporter->addVzMvAcce(sgn(fdz)*((_pMvTransporter->_veloVzMv*_maxAcceRange) /_renge) );


//    int fdx = pMainLockOnTarget->_X - _X;
//    int fdy = pMainLockOnTarget->_Y - _Y;
//    int fdz = pMainLockOnTarget->_Z - _Z;
//    _jerkVx = sgn(fdx) * 100;
//    _jerkVy = sgn(fdy) * 100;
//    _jerkVz = sgn(fdz) * 100;
//    _pMvTransporter->_acceVxMv += _jerkVx;
//    _pMvTransporter->_acceVyMv += _jerkVy;
//    _pMvTransporter->_acceVzMv += _jerkVz;






















//    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
//
//    if (_lockon == 1) {
//        if (getActivePartFrame() < 120) {
//            _maxAcceRange+=100;
//            _pMvTransporter->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
////            if (_pOrg->_pLockonTarget && _pOrg->_pLockonTarget->isActiveActor() && _pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) > 0) {
//                                                                                 //�̗͂̔���̓I�v�V�������ōs�����Ƃɂ���
//            if (pMainLockOnTarget) {
//                if (pMainLockOnTarget->isActiveActor()) {
//                    float rate = 8.0 - 0.06*getActivePartFrame(); //0.06 * 120 = 8.0
//                    rate = rate > 0 ? rate : 0;
//                    int fdx = pMainLockOnTarget->_X - (_X + _pMvTransporter->_veloVxMv*rate);
//                    int fdy = pMainLockOnTarget->_Y - (_Y + _pMvTransporter->_veloVyMv*rate);
//                    int fdz = pMainLockOnTarget->_Z - (_Z + _pMvTransporter->_veloVzMv*rate);
//                    _pMvTransporter->setVxMvAcce(fdx);
//                    _pMvTransporter->setVyMvAcce(fdy);
//                    _pMvTransporter->setVzMvAcce(fdz);
//                } else {
//
//
//                }
//            } else {
//                _lockon = 2;
//            }
//        } else {
//            _lockon = 2;
//        }
//    }
//
//
//
//    int dx, dy, dz;
//    if (_lockon == 2) {
//        if (_isLockon) {
//            _isLockon = false;
//            //��[�Ȃ�Γ��ʂɁA�I�v�V�����̔��΂̍��W���^�[�Q�b�g����
//            if (_pChip_front == NULL) {
//                _new_target_X = _X + (_X - _pOrg->_X);
//                _new_target_Y = _Y + (_Y - _pOrg->_Y);
//                _new_target_Z = _Z + (_Z - _pOrg->_Z);
//                dx = _new_target_X - (_X );
//                dy = _new_target_Y - (_Y );
//                dz = _new_target_Z - (_Z );
//                _pMvTransporter->setVxMvAcce(dx);
//                _pMvTransporter->setVyMvAcce(dy);
//                _pMvTransporter->setVzMvAcce(dz);
//            }
//        }
//
//
//
//        _maxAcceRange+=100;
//        _pMvTransporter->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
//        if (_pChip_front == NULL) {
//            _maxAcceRange+=100;
//            //��̏����P��ƁA���� _maxAcceRange+=100;
//        } else if (_pChip_front->_pChip_front == NULL) {
//            //�V���ȃ^�[�Q�b�g���쐬
//            dx = _pChip_front->_X - (_X + _pMvTransporter->_veloVxMv);
//            dy = _pChip_front->_Y - (_Y + _pMvTransporter->_veloVyMv);
//            dz = _pChip_front->_Z - (_Z + _pMvTransporter->_veloVzMv);
//            _pMvTransporter->setVxMvAcce(dx);
//            _pMvTransporter->setVyMvAcce(dy);
//            _pMvTransporter->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
//            dx = _pChip_front->_pChip_front->_X - (_X + _pMvTransporter->_veloVxMv*2);
//            dy = _pChip_front->_pChip_front->_Y - (_Y + _pMvTransporter->_veloVyMv*2);
//            dz = _pChip_front->_pChip_front->_Z - (_Z + _pMvTransporter->_veloVzMv*2);
//            _pMvTransporter->setVxMvAcce(dx);
//            _pMvTransporter->setVyMvAcce(dy);
//            _pMvTransporter->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == NULL) {
//            dx = _pChip_front->_pChip_front->_pChip_front->_X - (_X + _pMvTransporter->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pMvTransporter->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pMvTransporter->_veloVzMv*3);
//            _pMvTransporter->setVxMvAcce(dx);
//            _pMvTransporter->setVyMvAcce(dy);
//            _pMvTransporter->setVzMvAcce(dz);
//        } else {
//            dx = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_X - (_X + _pMvTransporter->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pMvTransporter->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pMvTransporter->_veloVzMv*3);
//            _pMvTransporter->setVxMvAcce(dx);
//            _pMvTransporter->setVyMvAcce(dy);
//            _pMvTransporter->setVzMvAcce(dz);
//        }
//    }
//    if (_pChip_front == NULL) {
//        _pSeTransmitter->behave();
//    }
//
////    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
////        _lockon = 1;
////        _isLockon = true;
////    }
//
////    _pMvNavigator->_angFace[AXIS_X] =  _pOrg->_pMvNavigator->_angFace[AXIS_Y];
//    WateringLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
//
    //�������烌�[�U�[�\���̂��ߋ����I�ɍ��W�␳
    if (onChangeToActive()) {
        locateAs(_pOrg);
        _tmpX = _X;
        _tmpY = _Y;
        _tmpZ = _Z;
    }

}

void MyOptionWateringLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void MyOptionWateringLaserChip001::onHit(GgafActor* prm_pOtherActor) {
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
                    ((MyOptionWateringLaserChip001*)_pChip_front)->_lockon = 2;
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
//void MyOptionWateringLaserChip001::processFinal() {
//    WateringLaserChip::processFinal();
//    //���b�N�I�������łȂ�΁A�؂�
//    if (_pOrg->_pLockonTarget) {
//        if (_pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) <= 0) {
//            _lockon = 2; //�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
//        }
//    }
//}

void MyOptionWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
    _lockon = 0;
}

MyOptionWateringLaserChip001::~MyOptionWateringLaserChip001() {
}

