#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;



MyOptionWateringLaserChip001::MyOptionWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyOptionWateringLaserChip001") { //"MyOptionWateringLaserChip001") {
    _class_name = "MyOptionWateringLaserChip001";
    MyStgUtil::resetMyOptionWateringLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    _pOrg = NULL;
    _lockon = 0;
    _isLockon = false;
	_renge = 150000;
    _r_maxacce = 15;
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
    _pMvTransporter->setZeroVxyzMvAcce(); //�����x���Z�b�g
    //Vxyz�̑��x�̓I�v�V�������Őݒ肳���


    _pMvTransporter->forceVxyzMvVeloRange(-_renge, _renge);
    _maxAcceRange= _renge/_r_maxacce;
    _pMvTransporter->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
}

void MyOptionWateringLaserChip001::processBehavior() {
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    if (getActivePartFrame() > 5) {
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
                int vVMx = _pMvTransporter->_veloVxMv*4;
                int vVMy = _pMvTransporter->_veloVyMv*4;
                int vVMz = _pMvTransporter->_veloVzMv*4;

                //|����|
                int lVM = MAX3(abs(vVMx), abs(vVMy), abs(vVMz)); //�����x�N�g���傫���ȈՔ�
                //|�I|
                int lT =  MAX3(abs(vTx), abs(vTy), abs(vTz)); //�I�x�N�g���傫���ȈՔ�
                //|����|/|�I|
                double r = 1.5*lVM / lT;
                //���������I �̉����x�ݒ�
                _pMvTransporter->setVxMvAcce(((vTx * r) - vVMx)/_r_maxacce);
                _pMvTransporter->setVyMvAcce(((vTy * r) - vVMy)/_r_maxacce);
                _pMvTransporter->setVzMvAcce(((vTz * r) - vVMz)/_r_maxacce);

                if (lVM > _renge/2) {
                    GgafDx9Util::getRzRyAng(vVMx,vVMy,vVMz,_RZ,_RY);
                }
            } else {
                //_pMvTransporter->setZeroVxyzMvAcce();
                _lockon = 2;
            }
        }

        if (_lockon == 2) {

            //��[�Ȃ�Γ��ʂɁA�I�v�V�����̔��΂̍��W���^�[�Q�b�g����
            if (_pChip_front == NULL) {
//                int dx = (_X - _pOrg->_X);
//                int dy = (_Y - _pOrg->_Y);
//                int dz = (_Z - _pOrg->_Z);
//                _pMvTransporter->setVxMvAcce(dx/_r_maxacce);
//                _pMvTransporter->setVyMvAcce(dy/_r_maxacce);
//                _pMvTransporter->setVzMvAcce(dy/_r_maxacce);
            } else {
                //�V���ȃ^�[�Q�b�g���쐬
                _pMvTransporter->setVxMvAcce((_pChip_front->_X - _X)/_r_maxacce);
                _pMvTransporter->setVyMvAcce((_pChip_front->_Y - _Y)/_r_maxacce);
                _pMvTransporter->setVzMvAcce((_pChip_front->_Z - _Z)/_r_maxacce);
            }

        }
    }


    WateringLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
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
            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
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
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
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

