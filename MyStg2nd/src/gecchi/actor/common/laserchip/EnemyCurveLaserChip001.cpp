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
//            //先端チップ
//            _lockon = 1;
//        } else {
//            //先端以外
//            _lockon = ((EnemyCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
//        }
//    } else {
//        if (_pChip_front == NULL) {
//            //先端チップ
//            _lockon = 0;
//        } else {
//            //先端以外
//            _lockon = ((EnemyCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
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
////                //上記のホーミングは優秀だが、距離に応じて減速していくため移動する敵には永遠に当たらない。
////                //ある程度近づいたら見切りで直進させる
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
//                _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
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
//            //新たなターゲットを作成
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
//    CurveLaserChip::processBehavior();//座標を移動させてから呼び出すこと
//}
//
//void EnemyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
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
//                    EnemyCurveLaserChip001* pTip = (EnemyCurveLaserChip001*)_pChip_front; //先端チップ
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
//                    pTip->_pKuroko->setVxMvVelo(pChipPrev->_pKuroko->_veloVxMv*2);
//                    pTip->_pKuroko->setVyMvVelo(pChipPrev->_pKuroko->_veloVyMv*2);
//                    pTip->_pKuroko->setVzMvVelo(pChipPrev->_pKuroko->_veloVzMv*2);
//                    //ターゲットがなくなり、レーザーの「ハジけた感（解放感）」を演出するため
//                    //加速度の正負逆を設定する。
//                    pTip->_pKuroko->setVxMvAcce(-(pChipPrev->_pKuroko->_acceVxMv));
//                    pTip->_pKuroko->setVyMvAcce(-(pChipPrev->_pKuroko->_acceVyMv));
//                    pTip->_pKuroko->setVzMvAcce(-(pChipPrev->_pKuroko->_acceVzMv));
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
//    //ロックオンが消滅ならば、切る
//    if (_pOrg->_pLockonTarget) {
//        if (_pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) <= 0) {
//            _pOrg->_pLockonTarget = NULL;
//            _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
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

