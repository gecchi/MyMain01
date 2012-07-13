#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



MyOptionWateringLaserChip001::MyOptionWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyOptionWateringLaserChip001", STATUS(MyOptionWateringLaserChip001)) {
    _class_name = "MyOptionWateringLaserChip001";
    default_stamina_ = _pStatus->get(STAT_Stamina);
    pOrg_ = NULL;
    lockon_st_ = 0;
    is_lockon_ = false;
    max_acce_renge_ = 0;
    max_velo_renge_ = 160000; //���̒l��傫������ƁA�ō����x�������Ȃ�B
    r_max_acce_ = 18; //���̒l��傫������ƁA�J�[�u���ɂ��Ȃ�
}

void MyOptionWateringLaserChip001::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
}

void MyOptionWateringLaserChip001::onActive() {
    _pStatus->reset();
    default_stamina_ = _pStatus->get(STAT_Stamina);
    WateringLaserChip::onActive();
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            lockon_st_ = 1;
        } else {
            //��[�ȊO
            MyOptionWateringLaserChip001* pF = (MyOptionWateringLaserChip001*) _pChip_front;
            lockon_st_ = pF->lockon_st_;//��O�̃��b�N�I�����������p��
        }
    } else {
        if (_pChip_front == NULL) {
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
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();
    if (getActivePartFrame() > 6) {
        if (lockon_st_ == 1) {
            if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
                moveChip(pMainLockOnTarget->_X,
                         pMainLockOnTarget->_Y,
                         pMainLockOnTarget->_Z );
            } else {
                //_pKurokoB->setZeroVxyzMvAcce();
                lockon_st_ = 2;
            }
        }

        if (lockon_st_ == 2) {
            if (_pLeader) {
                if (_pLeader == this) {
                    moveChip(_X + _pKurokoB->_veloVxMv*4+1,
                             _Y + _pKurokoB->_veloVyMv*2+1,
                             _Z + _pKurokoB->_veloVzMv*2+1 );
                } else {
                    moveChip(_pLeader->_X, _pLeader->_Y, _pLeader->_Z);
                }
            }
        }
    }

    WateringLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
    //�������烌�[�U�[�\���̂��ߋ����I�ɍ��W�␳
    if (onChangeToActive()) {
        locateWith(pOrg_);
        _tmpX = _X;
        _tmpY = _Y;
        _tmpZ = _Z;
    }

}

void MyOptionWateringLaserChip001::moveChip(int tX,int tY, int tZ) {
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
    int vTx = tX - _X;
    int vTy = tY - _Y;
    int vTz = tZ - _Z;

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
    double accX = ((vTx * r) - vVMx) / r_max_acce_;
    double accY = ((vTy * r) - vVMy) / r_max_acce_;
    double accZ = ((vTz * r) - vVMz) / r_max_acce_;

    if (_pChip_front == NULL) {
        //�擪�͂�⑬�߂�
        _pKurokoB->setVxMvAcce(accX+SGN(accX)*5); //SGN(accX)*5 �����Z����̂́A�����x��0�ɂ��Ȃ�����
        _pKurokoB->setVyMvAcce(accY+SGN(accY)*5);
        _pKurokoB->setVzMvAcce(accZ+SGN(accZ)*5);
    } else {
        _pKurokoB->setVxMvAcce(accX+SGN(accX)*3); //SGN(accX)*3 �����Z����̂́A�����x��0�ɂ��Ȃ�����
        _pKurokoB->setVyMvAcce(accY+SGN(accY)*3);
        _pKurokoB->setVzMvAcce(accZ+SGN(accZ)*3);
    }
    //�l�W���`�悪�����Ȃ�Ȃ��悤�ɉ�]�𐧌�
    if (lVM > max_velo_renge_/2) {
        angle RZ_temp = _RZ;
        angle RY_temp = _RY;
        UTIL::getRzRyAng(vVMx, vVMy, vVMz,
                                RZ_temp, RY_temp);
        angle angDRZ = UTIL::getAngDiff(RZ_temp, _RZ);
        angle angDRY = UTIL::getAngDiff(RY_temp, _RY);
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
        if (_RZ >= D360ANG) {
            _RZ -= D360ANG;
        }
        if (_RZ < 0) {
            _RZ += D360ANG;
        }
        if (_RY >= D360ANG) {
            _RY -= D360ANG;
        }
        if (_RY < 0) {
            _RY += D360ANG;
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
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();
    //�q�b�g�G�t�F�N�g
    //����

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //���ɃI�v�V�����̓��b�N�I����
            if (pOther == pMainLockOnTarget) {
                //�I�v�V�����̃��b�N�I���Ɍ������������ꍇ

                lockon_st_ = 2; //���b�N�I������߂�B�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
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

            //�j�󂳂ꂽ�G�t�F�N�g
            EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
            if (pExplo001) {
                pExplo001->locateWith(this);
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
            pExplo001->locateWith(this);
        }
        sayonara();
    }
}

void MyOptionWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
    lockon_st_ = 0;
}

MyOptionWateringLaserChip001::~MyOptionWateringLaserChip001() {
}

