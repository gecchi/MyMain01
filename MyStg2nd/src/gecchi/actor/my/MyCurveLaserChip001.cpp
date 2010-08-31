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
    CurveLaserChip::onActive();
    _pMover->setMvVelo(0);
    _pMover->setVxMvAcce(0);
    _pMover->setVyMvAcce(0);
    _pMover->setVzMvAcce(0);
    if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            _lockon = 1;
        } else {
            //��[�ȊO
            _lockon = ((MyCurveLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
        }
    } else {
        if (_pChip_front == NULL) {
            //��[�`�b�v
            _lockon = 0;
        } else {
            //��[�ȊO
            _lockon = ((MyCurveLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
        }
        _pOrg->_pLockOnTarget = NULL;
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
    if (_lockon == 1) {
        if (getActivePartFrame() < 100) {
            _maxAcceRange+=100;
            _pMover->forceVxMvAcceRange(-_maxAcceRange, _maxAcceRange);
            _pMover->forceVyMvAcceRange(-_maxAcceRange, _maxAcceRange);
            _pMover->forceVzMvAcceRange(-_maxAcceRange, _maxAcceRange);
            if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
                float rate = 6.0 - 0.06*getActivePartFrame(); //0.06 * 100 = 6.0
                rate = rate > 0 ? rate : 0;
                int fdx = _pOrg->_pLockOnTarget->_X - (_X + _pMover->_veloVxMv*rate);
                int fdy = _pOrg->_pLockOnTarget->_Y - (_Y + _pMover->_veloVyMv*rate);
                int fdz = _pOrg->_pLockOnTarget->_Z - (_Z + _pMover->_veloVzMv*rate);
                _pMover->setVxMvAcce(fdx);
                _pMover->setVyMvAcce(fdy);
                _pMover->setVzMvAcce(fdz);
//                //��L�̃z�[�~���O�͗D�G�����A�����ɉ����Č������Ă������߈ړ�����G�ɂ͉i���ɓ�����Ȃ��B
//                //������x�߂Â����猩�؂�Œ��i������
//                int dx = _pOrg->_pLockOnTarget->_X - _X;
//                int dy = _pOrg->_pLockOnTarget->_Y - _Y;
//                int dz = _pOrg->_pLockOnTarget->_Z - _Z;
//                if (abs(dx)+abs(dy)+abs(dz) < 150*1000) {
//                    _pMover->setVxMvVelo(dx);
//                    _pMover->setVyMvVelo(dy);
//                    _pMover->setVzMvVelo(dz);
//                    _pMover->setVxMvAcce(dx/10);
//                    _pMover->setVyMvAcce(dy/10);
//                    _pMover->setVzMvAcce(dz/10);
//                    _lockon = 2;
//                }

            } else {
                _lockon = 2; //�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
            }
        } else {
            _lockon = 2;
        }
    }

    if (_lockon == 2) {
        int dx, dy, dz;
        if (_pChip_front == NULL) {
//            _pMover->addVxMvAcce(_pMover->_acceVxMv);
//            _pMover->addVyMvAcce(_pMover->_acceVyMv);
//            _pMover->addVzMvAcce(_pMover->_acceVzMv);
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
        } else {
            dx = _pChip_front->_pChip_front->_pChip_front->_X - (_X + _pMover->_veloVxMv*3);
            dy = _pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pMover->_veloVyMv*3);
            dz = _pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pMover->_veloVzMv*3);
            _pMover->setVxMvAcce(dx);
            _pMover->setVyMvAcce(dy);
            _pMover->setVzMvAcce(dz);
        }
    }
    if (_pChip_front == NULL) {
        _pSeTransmitter->behave();
    }
    CurveLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
}

void MyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*) prm_pOtherActor;

    //�q�b�g�G�t�F�N�g
    //����

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (_pOrg->_pLockOnTarget) { //���ɃI�v�V�����̓��b�N�I����
            if (pOther == _pOrg->_pLockOnTarget) {
                //�I�v�V�����̃��b�N�I���Ɍ������������ꍇ

                _lockon = 2; //���b�N�I������߂�B�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
                //�����z�[�~���O����K�v�͂Ȃ��B����̕��j������

                //���Ԑ擪�`�b�v���q�b�g�����ꍇ�̏����B(_chip_kind=3�̏ꍇ)
                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
                    //��[�`�b�v�֍���̕��j��`����B�i��[�`�b�v�͓����蔻�肪�Ȃ����߁j
                    MyCurveLaserChip001* pTip = (MyCurveLaserChip001*)_pChip_front; //��[�`�b�v
                    pTip->_lockon = 2; //��[�ɓ`����
                    //����̈ړ����p(�����x)��`����̂����A��[�`�b�v�⎩�g��ړ������́A�}���Ȋp�x�ɋȂ����Ă���\�����ɂ߂č���
                    //�s���R�Ȋp�x�̃J�[�u��`�����˂Ȃ��̂ŁA������̃`�b�v�����݂���Ȃ�΁A������̈ړ��������R�s�[����B
                    LaserChip* pChipPrev = this;
                    for (int i = 0; i < 2; i++) { //�ō�2����܂ō݂�΍̗p
                        if (pChipPrev->_pChip_behind) {
                            pChipPrev = pChipPrev->_pChip_behind;
                        } else {
                            break;
                        }
                    }
                    pTip->_pMover->setVxMvVelo(pChipPrev->_pMover->_veloVxMv);
                    pTip->_pMover->setVyMvVelo(pChipPrev->_pMover->_veloVyMv);
                    pTip->_pMover->setVzMvVelo(pChipPrev->_pMover->_veloVzMv);
                    pTip->_pMover->setVxMvAcce(pChipPrev->_pMover->_acceVxMv);
                    pTip->_pMover->setVyMvAcce(pChipPrev->_pMover->_acceVyMv);
                    pTip->_pMover->setVzMvAcce(pChipPrev->_pMover->_acceVzMv);
                }
            } else {
                //�I�v�V�����̃��b�N�I���ȊO�̃A�N�^�[�ɖ��������ꍇ

            }
        } else {
            //�I�v�V�����񃍃b�N�I�����ɖ��������ꍇ

        }


        int default_stamina = _pStatus->get(STAT_Stamina);
        int stamina = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
        if (stamina <= 0) {
            //�ꌂ�Ń`�b�v���ł̍U����

            //�j�󂳂ꂽ�G�t�F�N�g
            EffectExplosion001* pExplo001 = (EffectExplosion001*)pCOMMONSCENE->_pDispatcher_EffectExplosion001->employ();
            if (pExplo001 != NULL) {
                pExplo001->setGeometry(this);
                pExplo001->activate();
            }
            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I���X�V
            if (pOther->_pStatus->get(STAT_LockOnAble) == 1) {
                _pOrg->_pLockOnTarget = pOther;
            }
//
//            //����̃`�b�v�ɍ���̕��j��`����
//            if (_pChip_behind && _pChip_behind->isActive()) {
//                _pChip_behind->_pMover->setVxMvVelo(_pMover->_veloVxMv);
//                _pChip_behind->_pMover->setVyMvVelo(_pMover->_veloVyMv);
//                _pChip_behind->_pMover->setVzMvVelo(_pMover->_veloVzMv);
//                _pChip_behind->_pMover->setVxMvAcce(_pMover->_acceVxMv);
//                _pChip_behind->_pMover->setVyMvAcce(_pMover->_acceVyMv);
//                _pChip_behind->_pMover->setVzMvAcce(_pMover->_acceVzMv);
//            }
            sayonara();

        } else {
            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
            _pStatus->set(STAT_Stamina, default_stamina);
            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I���X�V
            if (pOther->_pStatus->get(STAT_LockOnAble) == 1) {
                _pOrg->_pLockOnTarget = pOther;
            }
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //�n�`����͖��������悤�Ȃ�

        //�j�󂳂ꂽ�G�t�F�N�g
        EffectExplosion001* pExplo001 = (EffectExplosion001*)pCOMMONSCENE->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->setGeometry(this);
            pExplo001->activate();
        }
        sayonara();
    }
}
void MyCurveLaserChip001::processFinal() {
    CurveLaserChip::processFinal();
    //���b�N�I�������łȂ�΁A�؂�
    if (_pOrg->_pLockOnTarget) {
        if (_pOrg->_pLockOnTarget->_pStatus->get(STAT_Stamina) <= 0) {
            _pOrg->_pLockOnTarget = NULL;
            _lockon = 2; //�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
        }
    }
}

void MyCurveLaserChip001::onInactive() {
    CurveLaserChip::onInactive();
    _lockon = 0;
}

MyCurveLaserChip001::~MyCurveLaserChip001() {
}

