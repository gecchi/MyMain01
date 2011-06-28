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
    _pKurokoA->relateFaceAngWithMvAng(true);
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
    _pKurokoB->setZeroVxyzMvAcce(); //�����x���Z�b�g
    //Vxyz�̑��x�̓I�v�V�������Őݒ肳���


    _pKurokoB->forceVxyzMvVeloRange(-_renge, _renge);
    _maxAcceRange= _renge/_r_maxacce;
    _pKurokoB->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
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
                //���������B��}�� |����| = 5*vM
                int vVMx = _pKurokoB->_veloVxMv*5;
                int vVMy = _pKurokoB->_veloVyMv*5;
                int vVMz = _pKurokoB->_veloVzMv*5;

                //|����|
                int lVM = MAX3(abs(vVMx), abs(vVMy), abs(vVMz)); //�����x�N�g���傫���ȈՔ�
                //|�I|
                int lT =  MAX3(abs(vTx), abs(vTy), abs(vTz)); //�I�x�N�g���傫���ȈՔ�
                //|����|/|�I|
                double r = 1.5*lVM / lT;
                //1.5�� �E��}�̂悤�Ɉ꒼���ɕ��񂾍ۂ��A�i�s�������ێ����邽�߂ɁA
                //|���I| > |����| �Ƃ����֌W���ێ����邽�߂ɂ������K���Ȋ���

                //���������I �̉����x�ݒ�
                _pKurokoB->setVxMvAcce(((vTx * r) - vVMx)/_r_maxacce);
                _pKurokoB->setVyMvAcce(((vTy * r) - vVMy)/_r_maxacce);
                _pKurokoB->setVzMvAcce(((vTz * r) - vVMz)/_r_maxacce);
                if (lVM > _renge/2) {
                    appangle RZ_temp = _RZ;
                    appangle RY_temp = _RY;
                    GgafDx9Util::getRzRyAng(vVMx, vVMy, vVMz,
                                            RZ_temp, RY_temp);
                    appangle angDRZ = GgafDx9Util::getAngDiff(RZ_temp, _RZ);
                    appangle angDRY = GgafDx9Util::getAngDiff(RY_temp, _RY);
                    if (-5000 <= angDRZ) {
                        _RZ -= 5000;
                    } else if (angDRZ <= 5000) {
                        _RZ += 5000;
                    } else {
                        _RZ += angDRZ;
                    }
                    if (-5000 <= angDRY) {
                        _RY -= 5000;
                    } else if (angDRY <= 5000) {
                        _RY += 5000;
                    } else {
                        _RY += angDRY;
                    }
                    if (_RZ >= ANGLE360) {
                        _RZ -= ANGLE360;
                    }
                    if (_RZ < 0) {
                        _RZ += ANGLE360;
                    }
                    if (_RY >= ANGLE360) {
                        _RY -= ANGLE360;
                    }
                    if (_RY < 0) {
                        _RY += ANGLE360;
                    }
                }

//                appangle RZ2 = _RZ;
//                appangle RY2 = _RY;
//                GgafDx9Util::getRzRyAng(vVMx,vVMy,vVMz,RZ2,RY2);
//                appangle RZ1 = RZ2;
//                appangle RY1 = RY2;
//                GgafDx9Util::anotherRzRy(RZ2, RY2);
//                appangle d1_angRz = GgafDx9Util::getAngDiff(_RZ, RZ1);
//                appangle d1_angRy = GgafDx9Util::getAngDiff(_RY, RY1);
//                appangle d1 = abs(d1_angRz) > abs(d1_angRy) ? abs(d1_angRz) : abs(d1_angRy);
//                appangle d2_angRz = GgafDx9Util::getAngDiff(_RZ, RZ2);
//                appangle d2_angRy = GgafDx9Util::getAngDiff(_RY, RY2);
//                appangle d2 = abs(d2_angRz) > abs(d2_angRy) ? abs(d2_angRz) : abs(d2_angRy);
//                if (d1 <= d2) {
//                    _RZ = RZ1;
//                    _RY = RY1;
//                } else {
//                    _RZ = RZ2;
//                    _RY = RY2;
//                }
            } else {
                //_pKurokoB->setZeroVxyzMvAcce();
                _lockon = 2;
            }
        }

        if (_lockon == 2) {

            //��[�Ȃ�Γ��ʂɁA�I�v�V�����̔��΂̍��W���^�[�Q�b�g����
            if (_pChip_front == NULL) {
//                int dx = (_X - _pOrg->_X);
//                int dy = (_Y - _pOrg->_Y);
//                int dz = (_Z - _pOrg->_Z);
//                _pKurokoB->setVxMvAcce(dx/_r_maxacce);
//                _pKurokoB->setVyMvAcce(dy/_r_maxacce);
//                _pKurokoB->setVzMvAcce(dy/_r_maxacce);
            } else {
                //�V���ȃ^�[�Q�b�g���쐬
                _pKurokoB->setVxMvAcce((_pChip_front->_X - _X)/_r_maxacce);
                _pKurokoB->setVyMvAcce((_pChip_front->_Y - _Y)/_r_maxacce);
                _pKurokoB->setVzMvAcce((_pChip_front->_Z - _Z)/_r_maxacce);
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

