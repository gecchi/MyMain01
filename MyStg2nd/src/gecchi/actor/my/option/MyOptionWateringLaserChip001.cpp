#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;



MyOptionWateringLaserChip001::MyOptionWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyOptionWateringLaserChip001", STATUS(MyOptionWateringLaserChip001)) {
    _class_name = "MyOptionWateringLaserChip001";
    _default_stamina = _pStatus->get(STAT_Stamina);
    _pOrg = NULL;
    _lockon = 0;
    _isLockon = false;
    _renge = 160000; //���̒l��傫������ƁA�ō����x�������Ȃ�B
    _r_maxacce = 18; //���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�
}

void MyOptionWateringLaserChip001::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    setScaleRate(6.0);
    setAlpha(0.99);
}

void MyOptionWateringLaserChip001::onActive() {
    _pStatus->reset();
    _default_stamina = _pStatus->get(STAT_Stamina);
    WateringLaserChip::onActive();
    GgafDxGeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
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
    _KTRACE_("this="<<this<<" "<<getName()<<"  "<<_pChip_front <<"<--["<<this<<"]<--"<<_pChip_behind);

    GgafDxGeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    if (getActivePartFrame() > 8) {
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
                double accX = ((vTx * r) - vVMx)/_r_maxacce;
                double accY = ((vTy * r) - vVMy)/_r_maxacce;
                double accZ = ((vTz * r) - vVMz)/_r_maxacce;
                _pKurokoB->setVxMvAcce(accX+sgn(accX)*2); //sgn(accX)*2 �����Z����̂́A�����x��0�ɂ��Ȃ�����
                _pKurokoB->setVyMvAcce(accY+sgn(accY)*2);
                _pKurokoB->setVzMvAcce(accZ+sgn(accZ)*2);

                //�l�W���`�悪�����Ȃ�Ȃ��悤�ɉ�]�𐧌�
                if (lVM > _renge/2) {
                    angle RZ_temp = _RZ;
                    angle RY_temp = _RY;
                    GgafDxUtil::getRzRyAng(vVMx, vVMy, vVMz,
                                            RZ_temp, RY_temp);
                    angle angDRZ = GgafDxUtil::getAngDiff(RZ_temp, _RZ);
                    angle angDRY = GgafDxUtil::getAngDiff(RY_temp, _RY);
                    if (-4000 <= angDRZ) {
                        _RZ -= 4000;
                    } else if (angDRZ <= 4000) {
                        _RZ += 4000;
                    } else {
                        _RZ += angDRZ;
                    }
                    if (-4000 <= angDRY) {
                        _RY -= 4000;
                    } else if (angDRY <= 4000) {
                        _RY += 4000;
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
            } else {
                //_pKurokoB->setZeroVxyzMvAcce();
                _lockon = 2;
            }
        }

        if (_lockon == 2) {

//
            int vTx,vTy,vTz;
//            _KTRACE_("XYZ="<<_X<<","<<_Y<<","<<_Z<<" Org="<<_pOrg->_X<<","<<_pOrg->_Y<<","<<_pOrg->_Z);
            if (_pChip_front == NULL) {
                //��[�Ȃ�Γ��ʂɁA�I�v�V�����̔��΂̍��W���^�[�Q�b�g����
                int dx = (_X - _pOrg->_X);
                int dy = (_Y - _pOrg->_Y);
                int dz = (_Z - _pOrg->_Z);
//                _KTRACE_("_pChip_front == NULL");
//                _KTRACE_("dx,dy,dz="<<dx<<","<<dy<<","<<dz);
                coord zf = Dx2App(P_CAM->_zf);
                vTx = _X+dx*(dx == 0 ? zf : zf/dx);
                vTy = _Y+dy*(dy == 0 ? zf : zf/dy);
                vTz = _Z+dz*(dz == 0 ? zf : zf/dz);
//                _KTRACE_("vTx,vTy,vTz="<<vTx<<","<<vTy<<","<<vTz);
            } else {
                LaserChip* p = _pChip_front;
                for (int i = 0; i < 5; i++) {
                    if (p->_pChip_front == NULL) {
                        vTx = p->_X - _X;
                        vTy = p->_Y - _Y;
                        vTz = p->_Z - _Z;
                    } else {
                        p = p->_pChip_front;
                    }
                }
            }

//
//
//                if (_pChip_front->_pChip_front == NULL) {
////                _KTRACE_("_pChip_front->_pChip_front == NULL");
//                //��[�ȊO�͑O���̃`�b�v��V���ȃ^�[�Q�b�g�ɂ���
//                vTx = _pChip_front->_X - _X;
//                vTy = _pChip_front->_Y - _Y;
//                vTz = _pChip_front->_Z - _Z;
////                _KTRACE_("vTx,vTy,vTz="<<vTx<<","<<vTy<<","<<vTz);
//            } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
////                _KTRACE_("} else {");
//                vTx = _pChip_front->_pChip_front->_X - _X;
//                vTy = _pChip_front->_pChip_front->_Y - _Y;
//                vTz = _pChip_front->_pChip_front->_Z - _Z;
////                _KTRACE_("vTx,vTy,vTz="<<vTx<<","<<vTy<<","<<vTz);
//            } else {
//
//            }
            //���������B��}�� |����| = 5*vM
//            _KTRACE_("_pKurokoB->_veloVxyzMv="<<_pKurokoB->_veloVxMv<<","<<_pKurokoB->_veloVyMv<<","<<_pKurokoB->_veloVzMv);
            int vVMx = _pKurokoB->_veloVxMv*5;
            int vVMy = _pKurokoB->_veloVyMv*5;
            int vVMz = _pKurokoB->_veloVzMv*5;
//            _KTRACE_("vVMx,vVMy,vVMz="<<vVMx<<","<<vVMy<<","<<vVMz);
            //|����|
            int lVM = MAX3(abs(vVMx), abs(vVMy), abs(vVMz)); //�����x�N�g���傫���ȈՔ�
            //|�I|
            int lT =  MAX3(abs(vTx), abs(vTy), abs(vTz)); //�I�x�N�g���傫���ȈՔ�
//            _KTRACE_("lVM="<<lVM<<"/lT="<<lT);
            //|����|/|�I|
            double r = 1.5*lVM / lT;
//            _KTRACE_("r="<<r<<" 1.5*lVM / lT="<<(1.5*lVM / lT));
            //1.5�� �E��}�̂悤�Ɉ꒼���ɕ��񂾍ۂ��A�i�s�������ێ����邽�߂ɁA
            //|���I| > |����| �Ƃ����֌W���ێ����邽�߂ɂ������K���Ȋ���

            //���������I �̉����x�ݒ�
//            _KTRACE_("_r_maxacce="<<_r_maxacce);
//            _KTRACE_("befor _pKurokoB->_acceVxyzMv="<<_pKurokoB->_acceVxMv<<","<<_pKurokoB->_acceVyMv<<","<<_pKurokoB->_acceVzMv);
//            _KTRACE_("((vTx * r) - vVMx)/_r_maxacce="<<(((vTx * r) - vVMx)/_r_maxacce));
//            _KTRACE_("((vTy * r) - vVMy)/_r_maxacce="<<(((vTy * r) - vVMy)/_r_maxacce));
//            _KTRACE_("((vTz * r) - vVMz)/_r_maxacce="<<(((vTz * r) - vVMz)/_r_maxacce));
            double accX = ((vTx * r) - vVMx)/_r_maxacce;
            double accY = ((vTy * r) - vVMy)/_r_maxacce;
            double accZ = ((vTz * r) - vVMz)/_r_maxacce;
            _pKurokoB->setVxMvAcce(accX+sgn(accX)*2);
            _pKurokoB->setVyMvAcce(accY+sgn(accY)*2);
            _pKurokoB->setVzMvAcce(accZ+sgn(accZ)*2);
//            _KTRACE_("after _pKurokoB->_acceVxyzMv="<<_pKurokoB->_acceVxMv<<","<<_pKurokoB->_acceVyMv<<","<<_pKurokoB->_acceVzMv);

            if (lVM > _renge/2) {
                angle RZ_temp = _RZ;
                angle RY_temp = _RY;
                GgafDxUtil::getRzRyAng(vVMx, vVMy, vVMz,
                                        RZ_temp, RY_temp);
                angle angDRZ = GgafDxUtil::getAngDiff(RZ_temp, _RZ);
                angle angDRY = GgafDxUtil::getAngDiff(RY_temp, _RY);
                if (-4000 <= angDRZ) {
                    _RZ -= 4000;
                } else if (angDRZ <= 4000) {
                    _RZ += 4000;
                } else {
                    _RZ += angDRZ;
                }
                if (-4000 <= angDRY) {
                    _RY -= 4000;
                } else if (angDRY <= 4000) {
                    _RY += 4000;
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
        }
    }

//                _pKurokoB->setVxMvAcce(dx/_r_maxacce);
//                _pKurokoB->setVyMvAcce(dy/_r_maxacce);
////                _pKurokoB->setVzMvAcce(dy/_r_maxacce);
//           } else {
////                //�V���ȃ^�[�Q�b�g���쐬
//
//                if (_pChip_front->_pChip_front == NULL) {
//                    //�V���ȃ^�[�Q�b�g���쐬
//                    int dx = _pChip_front->_X - (_X + _pKurokoB->_veloVxMv);
//                    int dy = _pChip_front->_Y - (_Y + _pKurokoB->_veloVyMv);
//                    int dz = _pChip_front->_Z - (_Z + _pKurokoB->_veloVzMv);
//                    _pKurokoB->setVxMvAcce(dx);
//                    _pKurokoB->setVyMvAcce(dy);
//                    _pKurokoB->setVzMvAcce(dz);
//                } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
//                    int dx = _pChip_front->_pChip_front->_X - (_X + _pKurokoB->_veloVxMv*5);
//                    int dy = _pChip_front->_pChip_front->_Y - (_Y + _pKurokoB->_veloVyMv*5);
//                    int dz = _pChip_front->_pChip_front->_Z - (_Z + _pKurokoB->_veloVzMv*5);
//                    _pKurokoB->setVxMvAcce(dx);
//                    _pKurokoB->setVyMvAcce(dy);
//                    _pKurokoB->setVzMvAcce(dz);
//                } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == NULL) {
//                    int dx = _pChip_front->_pChip_front->_pChip_front->_X - (_X + _pKurokoB->_veloVxMv*5);
//                    int dy = _pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pKurokoB->_veloVyMv*5);
//                    int dz = _pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pKurokoB->_veloVzMv*5);
//                    _pKurokoB->setVxMvAcce(dx);
//                    _pKurokoB->setVyMvAcce(dy);
//                    _pKurokoB->setVzMvAcce(dz);
//                } else {
//                    int dx = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_X - (_X + _pKurokoB->_veloVxMv*5);
//                    int dy = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pKurokoB->_veloVyMv*5);
//                    int dz = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pKurokoB->_veloVzMv*5);
//                    _pKurokoB->setVxMvAcce(dx);
//                    _pKurokoB->setVyMvAcce(dy);
//                    _pKurokoB->setVzMvAcce(dz);
//                }
//
//
////                _pKurokoB->setVxMvAcce((_pChip_front->_X - _X)/_r_maxacce);
////                _pKurokoB->setVyMvAcce((_pChip_front->_Y - _Y)/_r_maxacce);
////                _pKurokoB->setVzMvAcce((_pChip_front->_Z - _Z)/_r_maxacce);
//                _pKurokoB->setVxMvAcce(0);
//                _pKurokoB->setVyMvAcce(0);
//                _pKurokoB->setVzMvAcce(0);
//                MyOptionWateringLaserChip001* p = (MyOptionWateringLaserChip001*)_pChip_front;
//                _pKurokoB->setVxMvVelo(p->_tmpX - _X);
//                _pKurokoB->setVyMvVelo(p->_tmpY - _Y);
//                _pKurokoB->setVzMvVelo(p->_tmpZ - _Z);
//            }



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
    GgafDxGeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
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

