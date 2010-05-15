#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyCurveLaserChip001::MyCurveLaserChip001(const char* prm_name) :
        CurveLaserChip(prm_name, "12/laser_chip") { //LaserChip�n�͍ő�12�Z�b�g
    _class_name = "MyCurveLaserChip001";
    MyStgUtil::resetMyCurveLaserChip001Status(_pStatus);
    _pOrg = NULL;
    _lockon = 0;

}

void MyCurveLaserChip001::initialize() {
    _pMover->relateRzRyFaceAngToMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    _SX = _SY = _SZ = 100 * 1000;
    _fAlpha = 0.99f;
    _fBoundingSphereRadius = 50.0f;

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

    _pMover->forceVxMvAcceRange(-_renge / 20, _renge / 20);
    _pMover->forceVyMvAcceRange(-_renge / 20, _renge / 20);
    _pMover->forceVzMvAcceRange(-_renge / 20, _renge / 20);
}

void MyCurveLaserChip001::processBehavior() {
    if (_lockon == 1) {
        if (getPartFrame() < 180) {
            if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
                int dx = _pOrg->_pLockOnTarget->_X - (_X + _pMover->_veloVxMv*10);
                int dy = _pOrg->_pLockOnTarget->_Y - (_Y + _pMover->_veloVyMv*7);
                int dz = _pOrg->_pLockOnTarget->_Z - (_Z + _pMover->_veloVzMv*10);
                _pMover->setVxMvAcce(dx);
                _pMover->setVyMvAcce(dy);
                _pMover->setVzMvAcce(dz);
            } else {
                _lockon = 2; //�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
            }
        } else {
            _lockon = 2;
        }
    } else if (_lockon == 2) {
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
        _pSeReflector->behave();
    }
    CurveLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
}

void MyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*) prm_pOtherActor;
    if (pOther->getKind() & KIND_ENEMY) {
        //�G�̏ꍇ
        if (_pOrg->_pLockOnTarget) {
            if (pOther == _pOrg->_pLockOnTarget) {
                _lockon = 2; //�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j

                //���Ԑ擪�`�b�v���q�b�g�����ꍇ�̏����B(_chip_kind=3�̏ꍇ)
                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
                    //��[�`�b�v�֍���̕��j��`����B�i��[�`�b�v�͓����蔻�肪�Ȃ����߁j
                    MyCurveLaserChip001* pTip = (MyCurveLaserChip001*)_pChip_front; //��[�`�b�v
                    pTip->_lockon = 2; //��[�ɓ`����
                    //����̈ړ����p(�����x)��`����̂����A��[�`�b�v�⎩�g��ړ������́A�}���Ȋp�x�ɋȂ����Ă���\�����ɂ߂č���
                    //�s���R�Ȋp�x�̃J�[�u��`�����˂Ȃ��̂ŁA������̃`�b�v�����݂���Ȃ�΁A������̈ړ��������R�s�[����B
                    LaserChip* pChipPrev = this;
                    for (int i = 0; i < 3; i++) { //�ō�3����܂ō݂�΍̗p
                        if (pChipPrev->_pChip_behind) {
                            pChipPrev = pChipPrev->_pChip_behind;
                        } else {
                            break;
                        }
                    }
                    pTip->_pMover->setVxMvVelo(pChipPrev->_pMover->_veloVxMv*2);
                    pTip->_pMover->setVyMvVelo(pChipPrev->_pMover->_veloVyMv*2);
                    pTip->_pMover->setVzMvVelo(pChipPrev->_pMover->_veloVzMv*2);
                    //�^�[�Q�b�g�Ɍ������Ă���Œ��ł��邽�߁A�w�ǂ̏ꍇ�������ł���B
                    //���̂܉����x��ݒ肷��ƁA������t�����Ɍ��������ƂɂȂ��Ă��܂��B�B
                    //�{���������ׂ������ɋߎ����邽�߁A�����t��ݒ肷��B
                    pTip->_pMover->setVxMvAcce(-(pChipPrev->_pMover->_acceVxMv));
                    pTip->_pMover->setVyMvAcce(-(pChipPrev->_pMover->_acceVyMv));
                    pTip->_pMover->setVzMvAcce(-(pChipPrev->_pMover->_acceVzMv));
                }
            }
        } else {
            _pOrg->_pLockOnTarget = pOther;
        }
        //������My�̃q�b�g�G�t�F�N�g
        if (MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
            //������My�̏��ŃG�t�F�N�g
            inactivate();
        } else {

        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        inactivate();
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

