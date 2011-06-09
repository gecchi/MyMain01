#include "stdafx.h"
//using namespace std;
//using namespace GgafCore;
//using namespace GgafDx9Core;
//using namespace GgafDx9LibStg;
//using namespace MyStg2nd;
//
//EnemyWateringLaserChip001::EnemyWateringLaserChip001(const char* prm_name) :
//        WateringLaserChip(prm_name, "EnemyWateringLaserChip001") {
//    _class_name = "EnemyWateringLaserChip001";
//    MyStgUtil::resetEnemyWateringLaserChip001Status(_pStatus);
//    _pOrg = NULL;
//    _lockon = 0;
//
//}
//
//void EnemyWateringLaserChip001::initialize() {
//    _pMvNavigator->relateFaceAngWithMvAng(true);
//    registHitAreaCube(80000);
//    setHitAble(true);
//    _SX = _SY = _SZ = 6 * 1000;
//    _fAlpha = 0.99f;
//    _radius_bounding_sphere = 60.0f;
//
//}
//
//void EnemyWateringLaserChip001::onActive() {
//    MyStgUtil::resetEnemyWateringLaserChip001Status(_pStatus);
//    WateringLaserChip::onActive();
//    _pMvNavigator->setMvVelo(0);
//    _pMvNavigator->setVxMvAcce(0);
//    _pMvNavigator->setVyMvAcce(0);
//    _pMvNavigator->setVzMvAcce(0);
//    if (_pOrg->_pLockonTarget && _pOrg->_pLockonTarget->isActiveActor()) {
//        if (_pChip_front == NULL) {
//            //先端チップ
//            _lockon = 1;
//        } else {
//            //先端以外
//            _lockon = ((EnemyWateringLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
//        }
//    } else {
//        if (_pChip_front == NULL) {
//            //先端チップ
//            _lockon = 0;
//        } else {
//            //先端以外
//            _lockon = ((EnemyWateringLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
//        }
//        _pOrg->_pLockonTarget = NULL;
//    }
//    _renge = 150000;
//    _pMvNavigator->forceVxMvVeloRange(-_renge, _renge);
//    _pMvNavigator->forceVyMvVeloRange(-_renge, _renge);
//    _pMvNavigator->forceVzMvVeloRange(-_renge, _renge);
//    _maxAcceRange= _renge / 30;
//    _pMvNavigator->forceVxMvAcceRange(-_maxAcceRange, _maxAcceRange);
//    _pMvNavigator->forceVyMvAcceRange(-_maxAcceRange, _maxAcceRange);
//    _pMvNavigator->forceVzMvAcceRange(-_maxAcceRange, _maxAcceRange);
//}
//
//void EnemyWateringLaserChip001::processBehavior() {
//    if (_lockon == 1) {
//        if (getActivePartFrame() < 100) {
//            _maxAcceRange+=100;
//            _pMvNavigator->forceVxMvAcceRange(-_maxAcceRange, _maxAcceRange);
//            _pMvNavigator->forceVyMvAcceRange(-_maxAcceRange, _maxAcceRange);
//            _pMvNavigator->forceVzMvAcceRange(-_maxAcceRange, _maxAcceRange);
//            if (_pOrg->_pLockonTarget && _pOrg->_pLockonTarget->isActiveActor()) {
//                float rate = 8.0 - 0.06*getActivePartFrame(); //0.06 * 120 = 8.0
//                rate = rate > 0 ? rate : 0;
//                int fdx = _pOrg->_pLockonTarget->_X - (_X + _pMvNavigator->_veloVxMv*rate);
//                int fdy = _pOrg->_pLockonTarget->_Y - (_Y + _pMvNavigator->_veloVyMv*rate);
//                int fdz = _pOrg->_pLockonTarget->_Z - (_Z + _pMvNavigator->_veloVzMv*rate);
//                _pMvNavigator->setVxMvAcce(fdx);
//                _pMvNavigator->setVyMvAcce(fdy);
//                _pMvNavigator->setVzMvAcce(fdz);
////                //上記のホーミングは優秀だが、距離に応じて減速していくため移動する敵には永遠に当たらない。
////                //ある程度近づいたら見切りで直進させる
////                int dx = _pOrg->_pLockonTarget->_X - _X;
////                int dy = _pOrg->_pLockonTarget->_Y - _Y;
////                int dz = _pOrg->_pLockonTarget->_Z - _Z;
////                if (abs(dx)+abs(dy)+abs(dz) < 150*1000) {
////                    _pMvNavigator->setVxMvVelo(dx);
////                    _pMvNavigator->setVyMvVelo(dy);
////                    _pMvNavigator->setVzMvVelo(dz);
////                    _pMvNavigator->setVxMvAcce(dx/10);
////                    _pMvNavigator->setVyMvAcce(dy/10);
////                    _pMvNavigator->setVzMvAcce(dz/10);
////                    _lockon = 2;
////                }
//
//            } else {
//                _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
//            }
//        } else {
//            _lockon = 2;
//        }
//    } else if (_lockon == 2) {
//        int dx, dy, dz;
//        if (_pChip_front == NULL) {
////            _pMvNavigator->addVxMvAcce(_pMvNavigator->_acceVxMv);
////            _pMvNavigator->addVyMvAcce(_pMvNavigator->_acceVyMv);
////            _pMvNavigator->addVzMvAcce(_pMvNavigator->_acceVzMv);
//        } else if (_pChip_front->_pChip_front == NULL) {
//            //新たなターゲットを作成
//            dx = _pChip_front->_X - (_X + _pMvNavigator->_veloVxMv);
//            dy = _pChip_front->_Y - (_Y + _pMvNavigator->_veloVyMv);
//            dz = _pChip_front->_Z - (_Z + _pMvNavigator->_veloVzMv);
//            _pMvNavigator->setVxMvAcce(dx);
//            _pMvNavigator->setVyMvAcce(dy);
//            _pMvNavigator->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
//            dx = _pChip_front->_pChip_front->_X - (_X + _pMvNavigator->_veloVxMv*2);
//            dy = _pChip_front->_pChip_front->_Y - (_Y + _pMvNavigator->_veloVyMv*2);
//            dz = _pChip_front->_pChip_front->_Z - (_Z + _pMvNavigator->_veloVzMv*2);
//            _pMvNavigator->setVxMvAcce(dx);
//            _pMvNavigator->setVyMvAcce(dy);
//            _pMvNavigator->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == NULL) {
//            dx = _pChip_front->_pChip_front->_pChip_front->_X - (_X + _pMvNavigator->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pMvNavigator->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pMvNavigator->_veloVzMv*3);
//            _pMvNavigator->setVxMvAcce(dx);
//            _pMvNavigator->setVyMvAcce(dy);
//            _pMvNavigator->setVzMvAcce(dz);
//        } else {
//            dx = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_X - (_X + _pMvNavigator->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pMvNavigator->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pMvNavigator->_veloVzMv*3);
//            _pMvNavigator->setVxMvAcce(dx);
//            _pMvNavigator->setVyMvAcce(dy);
//            _pMvNavigator->setVzMvAcce(dz);
//        }
//    }
//    if (_pChip_front == NULL) {
//        _pSeTransmitter->behave();
//    }
//    WateringLaserChip::processBehavior();//座標を移動させてから呼び出すこと
//}
//
//void EnemyWateringLaserChip001::onHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*) prm_pOtherActor;
//
//    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
//        if (_pOrg->_pLockonTarget) { //既にオプションはロックオン中
//            if (pOther == _pOrg->_pLockonTarget) {
//                //オプションのロックオンに見事命中した場合
//
//                _lockon = 2; //ロックオンをやめる。非ロックオン（ロックオン→非ロックオン）
//                //もうホーミングする必要はない。今後の方針を決定
//
//                //中間先頭チップがヒットした場合の処理。(_chip_kind=3の場合)
//                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
//                    //先端チップへ今後の方針を伝える。（先端チップは当たり判定がないため）
//                    EnemyWateringLaserChip001* pTip = (EnemyWateringLaserChip001*)_pChip_front; //先端チップ
//                    pTip->_lockon = 2; //先端に伝える
//                    //今後の移動方角(加速度)を伝えるのだが、先端チップや自身や移動方向は、急激な角度に曲がっている可能性が極めて高く
//                    //不自然な角度のカーブを描きかねないので、やや後方のチップが存在するならば、そちらの移動方向をコピーする。
//                    LaserChip* pChipPrev = this;
//                    for (int i = 0; i < 4; i++) { //最高3つ後方まで在れば採用
//                        if (pChipPrev->_pChip_behind) {
//                            pChipPrev = pChipPrev->_pChip_behind;
//                        } else {
//                            break;
//                        }
//                    }
//                    pTip->_pMvNavigator->setVxMvVelo(pChipPrev->_pMvNavigator->_veloVxMv*2);
//                    pTip->_pMvNavigator->setVyMvVelo(pChipPrev->_pMvNavigator->_veloVyMv*2);
//                    pTip->_pMvNavigator->setVzMvVelo(pChipPrev->_pMvNavigator->_veloVzMv*2);
//                    //ターゲットがなくなり、レーザーの「ハジけた感（解放感）」を演出するため
//                    //加速度の正負逆を設定する。
//                    pTip->_pMvNavigator->setVxMvAcce(-(pChipPrev->_pMvNavigator->_acceVxMv));
//                    pTip->_pMvNavigator->setVyMvAcce(-(pChipPrev->_pMvNavigator->_acceVyMv));
//                    pTip->_pMvNavigator->setVzMvAcce(-(pChipPrev->_pMvNavigator->_acceVzMv));
//                }
//            } else {
//                //オプションのロックオン以外のアクターに命中した場合
//
//            }
//        } else {
//            //オプション非ロックオン中に命中した場合
//
//        }
//        int default_stamina = _pStatus->get(STAT_Stamina);
//        int stamina = MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
//        if (stamina <= 0) {
//            //一撃でチップ消滅の攻撃力
//            sayonara();
//            //ロックオン可能アクターならロックオン更新
//            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
//                _pOrg->_pLockonTarget = pOther;
//            }
//        } else {
//            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
//            _pStatus->set(STAT_Stamina, default_stamina);
//            //ロックオン可能アクターならロックオン更新
//            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
//                _pOrg->_pLockonTarget = pOther;
//            }
//        }
//    } else if (pOther->getKind() & KIND_CHIKEI) {
//        sayonara();
//    }
////        if (_pOrg->_pLockonTarget) {
////            _pMvNavigator->setVxMvVelo(-(_pMvNavigator->_veloVxMv));
////            _pMvNavigator->setVyMvVelo(-(_pMvNavigator->_veloVyMv));
////            _pMvNavigator->setVzMvVelo(-(_pMvNavigator->_veloVzMv));
////        }
//
//////        if (_pOrg->_pLockonTarget) {
////            _pMvNavigator->setVxMvVelo(-(_pMvNavigator->_veloVxMv));
////            //_pMvNavigator->setVxMvAcce(-(_pMvNavigator->_acceVxMv));
////            _pMvNavigator->setVyMvVelo(-(_pMvNavigator->_veloVyMv));
////            //_pMvNavigator->setVyMvAcce(-(_pMvNavigator->_acceVyMv));
////            _pMvNavigator->setVzMvVelo(-(_pMvNavigator->_veloVzMv));
////            //_pMvNavigator->setVzMvAcce(-(_pMvNavigator->_acceVzMv));
////            _pMvNavigator->behave();
//////        }
//
////        if (abs(_pMvNavigator->_veloVxMv) >= abs(_pMvNavigator->_veloVyMv) && abs(_pMvNavigator->_veloVxMv) >= abs(_pMvNavigator->_veloVzMv)) {
////            _pMvNavigator->setVxMvVelo(-(_pMvNavigator->_veloVxMv));
////            _pMvNavigator->setVxMvAcce(-(_pMvNavigator->_acceVxMv));
////        } else if (abs(_pMvNavigator->_veloVyMv) >= abs(_pMvNavigator->_veloVxMv) && abs(_pMvNavigator->_veloVyMv) >= abs(_pMvNavigator->_veloVzMv)) {
////            _pMvNavigator->setVyMvVelo(-(_pMvNavigator->_veloVyMv));
////            _pMvNavigator->setVyMvAcce(-(_pMvNavigator->_acceVyMv));
////        } else if (abs(_pMvNavigator->_veloVzMv) >= abs(_pMvNavigator->_veloVxMv) && abs(_pMvNavigator->_veloVzMv) >= abs(_pMvNavigator->_veloVyMv)) {
////            _pMvNavigator->setVzMvVelo(-(_pMvNavigator->_veloVzMv));
////            _pMvNavigator->setVzMvAcce(-(_pMvNavigator->_acceVzMv));
////        }
//
//
//}
//void EnemyWateringLaserChip001::processFinal() {
//    WateringLaserChip::processFinal();
//    //ロックオンが消滅ならば、切る
//    if (_pOrg->_pLockonTarget) {
//        if (_pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) <= 0) {
//            _pOrg->_pLockonTarget = NULL;
//            _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
//        }
//    }
//}
//
//void EnemyWateringLaserChip001::onInactive() {
//    WateringLaserChip::onInactive();
//    _lockon = 0;
//}
//
//EnemyWateringLaserChip001::~EnemyWateringLaserChip001() {
//}

