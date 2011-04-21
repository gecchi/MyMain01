#include "stdafx.h"
//using namespace std;
//using namespace GgafCore;
//using namespace GgafDx9Core;
//using namespace GgafDx9LibStg;
//using namespace MyStg2nd;
//
//EnemyCurveLaserChip001::EnemyCurveLaserChip001(const char* prm_name) :
//        CurveLaserChip(prm_name, "EnemyCurveLaserChip001") {
//    _class_name = "EnemyCurveLaserChip001";
//    MyStgUtil::resetEnemyCurveLaserChip001Status(_pStatus);
//    _pOrg = NULL;
//    _lockon = 0;
//
//}
//
//void EnemyCurveLaserChip001::initialize() {
//    _pKuroko->relateRzRyFaceAngToMvAng(true);
//    registHitAreaCube(80000);
//    setHitAble(true);
//    _SX = _SY = _SZ = 6 * 1000;
//    _fAlpha = 0.99f;
//    _radius_bounding_sphere = 60.0f;
//
//}
//
//void EnemyCurveLaserChip001::onActive() {
//    MyStgUtil::resetEnemyCurveLaserChip001Status(_pStatus);
//    CurveLaserChip::onActive();
//    _pKuroko->setMvVelo(0);
//    _pKuroko->setVxMvAcce(0);
//    _pKuroko->setVyMvAcce(0);
//    _pKuroko->setVzMvAcce(0);
//    if (_pOrg->_pLockonTarget && _pOrg->_pLockonTarget->isActiveActor()) {
//        if (_pChip_front == NULL) {
//            //��[�`�b�v
//            _lockon = 1;
//        } else {
//            //��[�ȊO
//            _lockon = ((EnemyCurveLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
//        }
//    } else {
//        if (_pChip_front == NULL) {
//            //��[�`�b�v
//            _lockon = 0;
//        } else {
//            //��[�ȊO
//            _lockon = ((EnemyCurveLaserChip001*) _pChip_front)->_lockon;//��O�̃��b�N�I�����������p��
//        }
//        _pOrg->_pLockonTarget = NULL;
//    }
//    _renge = 150000;
//    _pKuroko->forceVxMvVeloRange(-_renge, _renge);
//    _pKuroko->forceVyMvVeloRange(-_renge, _renge);
//    _pKuroko->forceVzMvVeloRange(-_renge, _renge);
//    _maxAcceRange= _renge / 30;
//    _pKuroko->forceVxMvAcceRange(-_maxAcceRange, _maxAcceRange);
//    _pKuroko->forceVyMvAcceRange(-_maxAcceRange, _maxAcceRange);
//    _pKuroko->forceVzMvAcceRange(-_maxAcceRange, _maxAcceRange);
//}
//
//void EnemyCurveLaserChip001::processBehavior() {
//    if (_lockon == 1) {
//        if (getActivePartFrame() < 100) {
//            _maxAcceRange+=100;
//            _pKuroko->forceVxMvAcceRange(-_maxAcceRange, _maxAcceRange);
//            _pKuroko->forceVyMvAcceRange(-_maxAcceRange, _maxAcceRange);
//            _pKuroko->forceVzMvAcceRange(-_maxAcceRange, _maxAcceRange);
//            if (_pOrg->_pLockonTarget && _pOrg->_pLockonTarget->isActiveActor()) {
//                float rate = 8.0 - 0.06*getActivePartFrame(); //0.06 * 120 = 8.0
//                rate = rate > 0 ? rate : 0;
//                int fdx = _pOrg->_pLockonTarget->_X - (_X + _pKuroko->_veloVxMv*rate);
//                int fdy = _pOrg->_pLockonTarget->_Y - (_Y + _pKuroko->_veloVyMv*rate);
//                int fdz = _pOrg->_pLockonTarget->_Z - (_Z + _pKuroko->_veloVzMv*rate);
//                _pKuroko->setVxMvAcce(fdx);
//                _pKuroko->setVyMvAcce(fdy);
//                _pKuroko->setVzMvAcce(fdz);
////                //��L�̃z�[�~���O�͗D�G�����A�����ɉ����Č������Ă������߈ړ�����G�ɂ͉i���ɓ�����Ȃ��B
////                //������x�߂Â����猩�؂�Œ��i������
////                int dx = _pOrg->_pLockonTarget->_X - _X;
////                int dy = _pOrg->_pLockonTarget->_Y - _Y;
////                int dz = _pOrg->_pLockonTarget->_Z - _Z;
////                if (abs(dx)+abs(dy)+abs(dz) < 150*1000) {
////                    _pKuroko->setVxMvVelo(dx);
////                    _pKuroko->setVyMvVelo(dy);
////                    _pKuroko->setVzMvVelo(dz);
////                    _pKuroko->setVxMvAcce(dx/10);
////                    _pKuroko->setVyMvAcce(dy/10);
////                    _pKuroko->setVzMvAcce(dz/10);
////                    _lockon = 2;
////                }
//
//            } else {
//                _lockon = 2; //�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
//            }
//        } else {
//            _lockon = 2;
//        }
//    } else if (_lockon == 2) {
//        int dx, dy, dz;
//        if (_pChip_front == NULL) {
////            _pKuroko->addVxMvAcce(_pKuroko->_acceVxMv);
////            _pKuroko->addVyMvAcce(_pKuroko->_acceVyMv);
////            _pKuroko->addVzMvAcce(_pKuroko->_acceVzMv);
//        } else if (_pChip_front->_pChip_front == NULL) {
//            //�V���ȃ^�[�Q�b�g���쐬
//            dx = _pChip_front->_X - (_X + _pKuroko->_veloVxMv);
//            dy = _pChip_front->_Y - (_Y + _pKuroko->_veloVyMv);
//            dz = _pChip_front->_Z - (_Z + _pKuroko->_veloVzMv);
//            _pKuroko->setVxMvAcce(dx);
//            _pKuroko->setVyMvAcce(dy);
//            _pKuroko->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
//            dx = _pChip_front->_pChip_front->_X - (_X + _pKuroko->_veloVxMv*2);
//            dy = _pChip_front->_pChip_front->_Y - (_Y + _pKuroko->_veloVyMv*2);
//            dz = _pChip_front->_pChip_front->_Z - (_Z + _pKuroko->_veloVzMv*2);
//            _pKuroko->setVxMvAcce(dx);
//            _pKuroko->setVyMvAcce(dy);
//            _pKuroko->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == NULL) {
//            dx = _pChip_front->_pChip_front->_pChip_front->_X - (_X + _pKuroko->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pKuroko->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pKuroko->_veloVzMv*3);
//            _pKuroko->setVxMvAcce(dx);
//            _pKuroko->setVyMvAcce(dy);
//            _pKuroko->setVzMvAcce(dz);
//        } else {
//            dx = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_X - (_X + _pKuroko->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pKuroko->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pKuroko->_veloVzMv*3);
//            _pKuroko->setVxMvAcce(dx);
//            _pKuroko->setVyMvAcce(dy);
//            _pKuroko->setVzMvAcce(dz);
//        }
//    }
//    if (_pChip_front == NULL) {
//        _pSeTransmitter->behave();
//    }
//    CurveLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
//}
//
//void EnemyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*) prm_pOtherActor;
//
//    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
//        if (_pOrg->_pLockonTarget) { //���ɃI�v�V�����̓��b�N�I����
//            if (pOther == _pOrg->_pLockonTarget) {
//                //�I�v�V�����̃��b�N�I���Ɍ������������ꍇ
//
//                _lockon = 2; //���b�N�I������߂�B�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
//                //�����z�[�~���O����K�v�͂Ȃ��B����̕��j������
//
//                //���Ԑ擪�`�b�v���q�b�g�����ꍇ�̏����B(_chip_kind=3�̏ꍇ)
//                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
//                    //��[�`�b�v�֍���̕��j��`����B�i��[�`�b�v�͓����蔻�肪�Ȃ����߁j
//                    EnemyCurveLaserChip001* pTip = (EnemyCurveLaserChip001*)_pChip_front; //��[�`�b�v
//                    pTip->_lockon = 2; //��[�ɓ`����
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
//                    pTip->_pKuroko->setVxMvVelo(pChipPrev->_pKuroko->_veloVxMv*2);
//                    pTip->_pKuroko->setVyMvVelo(pChipPrev->_pKuroko->_veloVyMv*2);
//                    pTip->_pKuroko->setVzMvVelo(pChipPrev->_pKuroko->_veloVzMv*2);
//                    //�^�[�Q�b�g���Ȃ��Ȃ�A���[�U�[�́u�n�W�������i������j�v�����o���邽��
//                    //�����x�̐����t��ݒ肷��B
//                    pTip->_pKuroko->setVxMvAcce(-(pChipPrev->_pKuroko->_acceVxMv));
//                    pTip->_pKuroko->setVyMvAcce(-(pChipPrev->_pKuroko->_acceVyMv));
//                    pTip->_pKuroko->setVzMvAcce(-(pChipPrev->_pKuroko->_acceVzMv));
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
//        int stamina = MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
//        if (stamina <= 0) {
//            //�ꌂ�Ń`�b�v���ł̍U����
//            sayonara();
//            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I���X�V
//            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
//                _pOrg->_pLockonTarget = pOther;
//            }
//        } else {
//            //�ς����Ȃ�΁A�ʊт��A�X�^�~�i�񕜁i�U����100�̎G���Ȃ�Βʊсj
//            _pStatus->set(STAT_Stamina, default_stamina);
//            //���b�N�I���\�A�N�^�[�Ȃ烍�b�N�I���X�V
//            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
//                _pOrg->_pLockonTarget = pOther;
//            }
//        }
//    } else if (pOther->getKind() & KIND_CHIKEI) {
//        sayonara();
//    }
////        if (_pOrg->_pLockonTarget) {
////            _pKuroko->setVxMvVelo(-(_pKuroko->_veloVxMv));
////            _pKuroko->setVyMvVelo(-(_pKuroko->_veloVyMv));
////            _pKuroko->setVzMvVelo(-(_pKuroko->_veloVzMv));
////        }
//
//////        if (_pOrg->_pLockonTarget) {
////            _pKuroko->setVxMvVelo(-(_pKuroko->_veloVxMv));
////            //_pKuroko->setVxMvAcce(-(_pKuroko->_acceVxMv));
////            _pKuroko->setVyMvVelo(-(_pKuroko->_veloVyMv));
////            //_pKuroko->setVyMvAcce(-(_pKuroko->_acceVyMv));
////            _pKuroko->setVzMvVelo(-(_pKuroko->_veloVzMv));
////            //_pKuroko->setVzMvAcce(-(_pKuroko->_acceVzMv));
////            _pKuroko->behave();
//////        }
//
////        if (abs(_pKuroko->_veloVxMv) >= abs(_pKuroko->_veloVyMv) && abs(_pKuroko->_veloVxMv) >= abs(_pKuroko->_veloVzMv)) {
////            _pKuroko->setVxMvVelo(-(_pKuroko->_veloVxMv));
////            _pKuroko->setVxMvAcce(-(_pKuroko->_acceVxMv));
////        } else if (abs(_pKuroko->_veloVyMv) >= abs(_pKuroko->_veloVxMv) && abs(_pKuroko->_veloVyMv) >= abs(_pKuroko->_veloVzMv)) {
////            _pKuroko->setVyMvVelo(-(_pKuroko->_veloVyMv));
////            _pKuroko->setVyMvAcce(-(_pKuroko->_acceVyMv));
////        } else if (abs(_pKuroko->_veloVzMv) >= abs(_pKuroko->_veloVxMv) && abs(_pKuroko->_veloVzMv) >= abs(_pKuroko->_veloVyMv)) {
////            _pKuroko->setVzMvVelo(-(_pKuroko->_veloVzMv));
////            _pKuroko->setVzMvAcce(-(_pKuroko->_acceVzMv));
////        }
//
//
//}
//void EnemyCurveLaserChip001::processFinal() {
//    CurveLaserChip::processFinal();
//    //���b�N�I�������łȂ�΁A�؂�
//    if (_pOrg->_pLockonTarget) {
//        if (_pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) <= 0) {
//            _pOrg->_pLockonTarget = NULL;
//            _lockon = 2; //�񃍃b�N�I���i���b�N�I�����񃍃b�N�I���j
//        }
//    }
//}
//
//void EnemyCurveLaserChip001::onInactive() {
//    CurveLaserChip::onInactive();
//    _lockon = 0;
//}
//
//EnemyCurveLaserChip001::~EnemyCurveLaserChip001() {
//}

