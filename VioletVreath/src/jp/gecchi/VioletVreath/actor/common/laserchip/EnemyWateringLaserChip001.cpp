#include "stdafx.h"
#include "EnemyWateringLaserChip001.h"

////using namespace GgafCore;
//using namespace GgafDxCore;
//using namespace GgafLib;
//using namespace VioletVreath;
//
//EnemyWateringLaserChip001::EnemyWateringLaserChip001(const char* prm_name) :
//        WateringLaserChip(prm_name, "EnemyWateringLaserChip001") {
//    _class_name = "EnemyWateringLaserChip001";
//    UTIL::resetEnemyWateringLaserChip001Status(_pStatus);
//    pOrg_ = nullptr;
//    lockon_st_ = 0;
//
//}
//
//void EnemyWateringLaserChip001::initialize() {
//    _pKurokoA->relateMvFaceAng(true);
//    registerHitAreaCube_AutoGenMidColli(80000);
//    setHitAble(true);
//    _SX = _SY = _SZ = R_SC(6);
//    _alpha = 0.99f;
//    _bounding_sphere_radius = 60.0f;
//
//}
//
//void EnemyWateringLaserChip001::onActive() {
//    UTIL::resetEnemyWateringLaserChip001Status(_pStatus);
//    WateringLaserChip::onActive();
//    _pKurokoA->setMvVelo(0);
//    _pKurokoA->setVxMvAcce(0);
//    _pKurokoA->setVyMvAcce(0);
//    _pKurokoA->setVzMvAcce(0);
//    if (pOrg_->pLockonTarget_ && pOrg_->pLockonTarget_->isActiveInTheTree()) {
//        if (_pChip_front == nullptr) {
//            //��[�`�b�v
//            lockon_st_ = 1;
//        } else {
//            //��[�ȊO
//            lockon_st_ = ((EnemyWateringLaserChip001*) _pChip_front)->lockon_st_;//��O�̃��b�N�I�����������p��
//        }
//    } else {
//        if (_pChip_front == nullptr) {
//            //��[�`�b�v
//            lockon_st_ = 0;
//        } else {
//            //��[�ȊO
//            lockon_st_ = ((EnemyWateringLaserChip001*) _pChip_front)->lockon_st_;//��O�̃��b�N�I�����������p��
//        }
//        pOrg_->pLockonTarget_ = nullptr;
//    }
//    renge_ = 150000;
//    _pKurokoA->forceVxMvVeloRange(-renge_, renge_);
//    _pKurokoA->forceVyMvVeloRange(-renge_, renge_);
//    _pKurokoA->forceVzMvVeloRange(-renge_, renge_);
//    maxAcceRange_= renge_ / 30;
//    _pKurokoA->forceVxMvAcceRange(-maxAcceRange_, maxAcceRange_);
//    _pKurokoA->forceVyMvAcceRange(-maxAcceRange_, maxAcceRange_);
//    _pKurokoA->forceVzMvAcceRange(-maxAcceRange_, maxAcceRange_);
//}
//
//void EnemyWateringLaserChip001::processBehavior() {
//    if (lockon_st_ == 1) {
//        if (getActiveFrame() < 100) {
//            maxAcceRange_+=100;
//            _pKurokoA->forceVxMvAcceRange(-maxAcceRange_, maxAcceRange_);
//            _pKurokoA->forceVyMvAcceRange(-maxAcceRange_, maxAcceRange_);
//            _pKurokoA->forceVzMvAcceRange(-maxAcceRange_, maxAcceRange_);
//            if (pOrg_->pLockonTarget_ && pOrg_->pLockonTarget_->isActiveInTheTree()) {
//                float rate = 8.0 - 0.06*getActiveFrame(); //0.06 * 120 = 8.0
//                rate = rate > 0 ? rate : 0;
//                int fdx = pOrg_->pLockonTarget_->_X - (_X + _pKurokoA->_veloVxMv*rate);
//                int fdy = pOrg_->pLockonTarget_->_Y - (_Y + _pKurokoA->_veloVyMv*rate);
//                int fdz = pOrg_->pLockonTarget_->_Z - (_Z + _pKurokoA->_veloVzMv*rate);
//                _pKurokoA->setVxMvAcce(fdx);
//                _pKurokoA->setVyMvAcce(fdy);
//                _pKurokoA->setVzMvAcce(fdz);
////                //��L�̃z�[�~���O�͗D�G�����A�����ɉ����Č������Ă������߈ړ�����G�ɂ͉i���ɓ�����Ȃ��B
////                //������x�߂Â����猩�؂�Œ��i������
////                int dx = pOrg_->pLockonTarget_->_X - _X;
////                int dy = pOrg_->pLockonTarget_->_Y - _Y;
////                int dz = pOrg_->pLockonTarget_->_Z - _Z;
////                if (ABS(dx)+ABS(dy)+ABS(dz) < 150*1000) {
////                    _pKurokoA->setVxMvVelo(dx);
////                    _pKurokoA->setVyMvVelo(dy);
////                    _pKurokoA->setVzMvVelo(dz);
////                    _pKurokoA->setVxMvAcce(dx/10);
////                    _pKurokoA->setVyMvAcce(dy/10);
////                    _pKurokoA->setVzMvAcce(dz/10);
////                    lockon_st_ = 2;
////                }
//
//            } else {
//                lockon_st_ = 2; //�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
//            }
//        } else {
//            lockon_st_ = 2;
//        }
//    } else if (lockon_st_ == 2) {
//        int dx, dy, dz;
//        if (_pChip_front == nullptr) {
////            _pKurokoA->addVxMvAcce(_pKurokoA->acceVxMv_);
////            _pKurokoA->addVyMvAcce(_pKurokoA->acceVyMv_);
////            _pKurokoA->addVzMvAcce(_pKurokoA->acceVzMv_);
//        } else if (_pChip_front->_pChip_front == nullptr) {
//            //�V���ȃ^�[�Q�b�g���쐬
//            dx = _pChip_front->_X - (_X + _pKurokoA->_veloVxMv);
//            dy = _pChip_front->_Y - (_Y + _pKurokoA->_veloVyMv);
//            dz = _pChip_front->_Z - (_Z + _pKurokoA->_veloVzMv);
//            _pKurokoA->setVxMvAcce(dx);
//            _pKurokoA->setVyMvAcce(dy);
//            _pKurokoA->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front == nullptr) {
//            dx = _pChip_front->_pChip_front->_X - (_X + _pKurokoA->_veloVxMv*2);
//            dy = _pChip_front->_pChip_front->_Y - (_Y + _pKurokoA->_veloVyMv*2);
//            dz = _pChip_front->_pChip_front->_Z - (_Z + _pKurokoA->_veloVzMv*2);
//            _pKurokoA->setVxMvAcce(dx);
//            _pKurokoA->setVyMvAcce(dy);
//            _pKurokoA->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == nullptr) {
//            dx = _pChip_front->_pChip_front->_pChip_front->_X - (_X + _pKurokoA->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pKurokoA->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pKurokoA->_veloVzMv*3);
//            _pKurokoA->setVxMvAcce(dx);
//            _pKurokoA->setVyMvAcce(dy);
//            _pKurokoA->setVzMvAcce(dz);
//        } else {
//            dx = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_X - (_X + _pKurokoA->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pKurokoA->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pKurokoA->_veloVzMv*3);
//            _pKurokoA->setVxMvAcce(dx);
//            _pKurokoA->setVyMvAcce(dy);
//            _pKurokoA->setVzMvAcce(dz);
//        }
//    }
//    if (_pChip_front == nullptr) {
//        _pSeTx->behave();
//    }
//    WateringLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
//}
//
//void EnemyWateringLaserChip001::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
//
//    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
//        if (pOrg_->pLockonTarget_) { //���ɃI�v�V�����̓��b�N�I����
//            if (pOther == pOrg_->pLockonTarget_) {
//                //�I�v�V�����̃��b�N�I���Ɍ������������ꍇ
//
//                lockon_st_ = 2; //���b�N�I������߂�B�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
//                //�����z�[�~���O����K�v�͂Ȃ��B����̕��j������
//
//                //���Ԑ擪�`�b�v���q�b�g�����ꍇ�̏����B(_chip_kind=3�̏ꍇ)
//                if (_pChip_front && _pChip_front->_pChip_front == nullptr) {
//                    //��[�`�b�v�֍���̕��j��`����B�i��[�`�b�v�͓����蔻�肪�Ȃ����߁j
//                    EnemyWateringLaserChip001* pTip = (EnemyWateringLaserChip001*)_pChip_front; //��[�`�b�v
//                    pTip->lockon_st_ = 2; //��[�ɓ`����
//                    //����̈ړ����p(�����x)��`����̂����A��[�`�b�v�⎩�g��ړ������́A�}���Ȋp�x�ɋȂ����Ă���\�����ɂ߂č���
//                    //�s���R�Ȋp�x�̃J�[�u��`�����˂Ȃ��̂ŁA������̃`�b�v�����݂���Ȃ�΁A������̈ړ��������R�s�[����B
//                    LaserChip* pChipPrev = this;
//                    for (int i = 0; i < 4; i++) { //�ō�3����܂ō݂�΍̗p
//                        if (pChipPrev->_pChip_behind) {
//                            pChipPrev = pChipPrev->_pChip_behind;
//                        } else {
//                            break;
//                        }
//                    }
//                    pTip->_pKurokoA->setVxMvVelo(pChipPrev->_pKurokoA->_veloVxMv*2);
//                    pTip->_pKurokoA->setVyMvVelo(pChipPrev->_pKurokoA->_veloVyMv*2);
//                    pTip->_pKurokoA->setVzMvVelo(pChipPrev->_pKurokoA->_veloVzMv*2);
//                    //�^�[�Q�b�g���Ȃ��Ȃ�A���[�U�[�́u�n�W�������i������j�v�����o���邽��
//                    //�����x�̐����t��ݒ肷��B
//                    pTip->_pKurokoA->setVxMvAcce(-(pChipPrev->_pKurokoA->acceVxMv_));
//                    pTip->_pKurokoA->setVyMvAcce(-(pChipPrev->_pKurokoA->acceVyMv_));
//                    pTip->_pKurokoA->setVzMvAcce(-(pChipPrev->_pKurokoA->acceVzMv_));
//                }
//            } else {
//                //�I�v�V�����̃��b�N�I���ȊO�̃A�N�^�[�ɖ��������ꍇ
//
//            }
//        } else {
//            //�I�v�V�����񃍃b�N�I�����ɖ��������ꍇ
//
//        }
//        int default_stamina = _pStatus->get(STAT_Stamina);
//        int stamina = UTIL::calcEnemyStamina(this, pOther);
//        if (stamina <= 0) {
//            //�ꌂ�Ń`�b�v���ł̍U����
//            sayonara();
//            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I���X�V
//            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
//                pOrg_->pLockonTarget_ = pOther;
//            }
//        } else {
//            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
//            _pStatus->set(STAT_Stamina, default_stamina);
//            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I���X�V
//            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
//                pOrg_->pLockonTarget_ = pOther;
//            }
//        }
//    } else if (pOther->getKind() & KIND_CHIKEI) {
//        sayonara();
//    }
////        if (pOrg_->pLockonTarget_) {
////            _pKurokoA->setVxMvVelo(-(_pKurokoA->_veloVxMv));
////            _pKurokoA->setVyMvVelo(-(_pKurokoA->_veloVyMv));
////            _pKurokoA->setVzMvVelo(-(_pKurokoA->_veloVzMv));
////        }
//
//////        if (pOrg_->pLockonTarget_) {
////            _pKurokoA->setVxMvVelo(-(_pKurokoA->_veloVxMv));
////            //_pKurokoA->setVxMvAcce(-(_pKurokoA->acceVxMv_));
////            _pKurokoA->setVyMvVelo(-(_pKurokoA->_veloVyMv));
////            //_pKurokoA->setVyMvAcce(-(_pKurokoA->acceVyMv_));
////            _pKurokoA->setVzMvVelo(-(_pKurokoA->_veloVzMv));
////            //_pKurokoA->setVzMvAcce(-(_pKurokoA->acceVzMv_));
////            _pKurokoA->behave();
//////        }
//
////        if (ABS(_pKurokoA->_veloVxMv) >= ABS(_pKurokoA->_veloVyMv) && ABS(_pKurokoA->_veloVxMv) >= ABS(_pKurokoA->_veloVzMv)) {
////            _pKurokoA->setVxMvVelo(-(_pKurokoA->_veloVxMv));
////            _pKurokoA->setVxMvAcce(-(_pKurokoA->acceVxMv_));
////        } else if (ABS(_pKurokoA->_veloVyMv) >= ABS(_pKurokoA->_veloVxMv) && ABS(_pKurokoA->_veloVyMv) >= ABS(_pKurokoA->_veloVzMv)) {
////            _pKurokoA->setVyMvVelo(-(_pKurokoA->_veloVyMv));
////            _pKurokoA->setVyMvAcce(-(_pKurokoA->acceVyMv_));
////        } else if (ABS(_pKurokoA->_veloVzMv) >= ABS(_pKurokoA->_veloVxMv) && ABS(_pKurokoA->_veloVzMv) >= ABS(_pKurokoA->_veloVyMv)) {
////            _pKurokoA->setVzMvVelo(-(_pKurokoA->_veloVzMv));
////            _pKurokoA->setVzMvAcce(-(_pKurokoA->acceVzMv_));
////        }
//
//
//}
//void EnemyWateringLaserChip001::processFinal() {
//    WateringLaserChip::processFinal();
//    //���b�N�I�������łȂ�΁A�؂�
//    if (pOrg_->pLockonTarget_) {
//        if (pOrg_->pLockonTarget_->_pStatus->get(STAT_Stamina) <= 0) {
//            pOrg_->pLockonTarget_ = nullptr;
//            lockon_st_ = 2; //�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
//        }
//    }
//}
//
//void EnemyWateringLaserChip001::onInactive() {
//    WateringLaserChip::onInactive();
//    lockon_st_ = 0;
//}
//
//EnemyWateringLaserChip001::~EnemyWateringLaserChip001() {
//}

