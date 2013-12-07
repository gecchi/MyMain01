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
//    _pKuroko->relateFaceWithMvAng(true);
//    registerHitAreaCube_AutoGenMidColli(80000);
//    setHitAble(true);
//    _sx = _sy = _sz = R_SC(6);
//    _alpha = 0.99f;
//    _bounding_sphere_radius = 60.0f;
//
//}
//
//void EnemyWateringLaserChip001::onActive() {
//    UTIL::resetEnemyWateringLaserChip001Status(_pStatus);
//    WateringLaserChip::onActive();
//    _pKuroko->setMvVelo(0);
//    _pKuroko->setVxMvAcce(0);
//    _pKuroko->setVyMvAcce(0);
//    _pKuroko->setVzMvAcce(0);
//    if (pOrg_->pLockonTarget_ && pOrg_->pLockonTarget_->isActiveInTheTree()) {
//        if (_pChip_front == nullptr) {
//            //先端チップ
//            lockon_st_ = 1;
//        } else {
//            //先端以外
//            lockon_st_ = ((EnemyWateringLaserChip001*) _pChip_front)->lockon_st_;//一つ前のロックオン情報を引き継ぐ
//        }
//    } else {
//        if (_pChip_front == nullptr) {
//            //先端チップ
//            lockon_st_ = 0;
//        } else {
//            //先端以外
//            lockon_st_ = ((EnemyWateringLaserChip001*) _pChip_front)->lockon_st_;//一つ前のロックオン情報を引き継ぐ
//        }
//        pOrg_->pLockonTarget_ = nullptr;
//    }
//    renge_ = 150000;
//    _pKuroko->forceVxMvVeloRange(-renge_, renge_);
//    _pKuroko->forceVyMvVeloRange(-renge_, renge_);
//    _pKuroko->forceVzMvVeloRange(-renge_, renge_);
//    maxAcceRange_= renge_ / 30;
//    _pKuroko->forceVxMvAcceRange(-maxAcceRange_, maxAcceRange_);
//    _pKuroko->forceVyMvAcceRange(-maxAcceRange_, maxAcceRange_);
//    _pKuroko->forceVzMvAcceRange(-maxAcceRange_, maxAcceRange_);
//}
//
//void EnemyWateringLaserChip001::processBehavior() {
//    if (lockon_st_ == 1) {
//        if (getActiveFrame() < 100) {
//            maxAcceRange_+=100;
//            _pKuroko->forceVxMvAcceRange(-maxAcceRange_, maxAcceRange_);
//            _pKuroko->forceVyMvAcceRange(-maxAcceRange_, maxAcceRange_);
//            _pKuroko->forceVzMvAcceRange(-maxAcceRange_, maxAcceRange_);
//            if (pOrg_->pLockonTarget_ && pOrg_->pLockonTarget_->isActiveInTheTree()) {
//                float rate = 8.0 - 0.06*getActiveFrame(); //0.06 * 120 = 8.0
//                rate = rate > 0 ? rate : 0;
//                int fdx = pOrg_->pLockonTarget_->_x - (_x + _pKuroko->_veloVxMv*rate);
//                int fdy = pOrg_->pLockonTarget_->_y - (_y + _pKuroko->_veloVyMv*rate);
//                int fdz = pOrg_->pLockonTarget_->_z - (_z + _pKuroko->_veloVzMv*rate);
//                _pKuroko->setVxMvAcce(fdx);
//                _pKuroko->setVyMvAcce(fdy);
//                _pKuroko->setVzMvAcce(fdz);
////                //上記のホーミングは優秀だが、距離に応じて減速していくため移動する敵には永遠に当たらない。
////                //ある程度近づいたら見切りで直進させる
////                int dx = pOrg_->pLockonTarget_->_x - _x;
////                int dy = pOrg_->pLockonTarget_->_y - _y;
////                int dz = pOrg_->pLockonTarget_->_z - _z;
////                if (ABS(dx)+ABS(dy)+ABS(dz) < 150*1000) {
////                    _pKuroko->setVxMvVelo(dx);
////                    _pKuroko->setVyMvVelo(dy);
////                    _pKuroko->setVzMvVelo(dz);
////                    _pKuroko->setVxMvAcce(dx/10);
////                    _pKuroko->setVyMvAcce(dy/10);
////                    _pKuroko->setVzMvAcce(dz/10);
////                    lockon_st_ = 2;
////                }
//
//            } else {
//                lockon_st_ = 2; //非ロックオン（ロックオン→非ロックオン）
//            }
//        } else {
//            lockon_st_ = 2;
//        }
//    } else if (lockon_st_ == 2) {
//        int dx, dy, dz;
//        if (_pChip_front == nullptr) {
////            _pKuroko->addVxMvAcce(_pKuroko->acceVxMv_);
////            _pKuroko->addVyMvAcce(_pKuroko->acceVyMv_);
////            _pKuroko->addVzMvAcce(_pKuroko->acceVzMv_);
//        } else if (_pChip_front->_pChip_front == nullptr) {
//            //新たなターゲットを作成
//            dx = _pChip_front->_x - (_x + _pKuroko->_veloVxMv);
//            dy = _pChip_front->_y - (_y + _pKuroko->_veloVyMv);
//            dz = _pChip_front->_z - (_z + _pKuroko->_veloVzMv);
//            _pKuroko->setVxMvAcce(dx);
//            _pKuroko->setVyMvAcce(dy);
//            _pKuroko->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front == nullptr) {
//            dx = _pChip_front->_pChip_front->_x - (_x + _pKuroko->_veloVxMv*2);
//            dy = _pChip_front->_pChip_front->_y - (_y + _pKuroko->_veloVyMv*2);
//            dz = _pChip_front->_pChip_front->_z - (_z + _pKuroko->_veloVzMv*2);
//            _pKuroko->setVxMvAcce(dx);
//            _pKuroko->setVyMvAcce(dy);
//            _pKuroko->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == nullptr) {
//            dx = _pChip_front->_pChip_front->_pChip_front->_x - (_x + _pKuroko->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_y - (_y + _pKuroko->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_z - (_z + _pKuroko->_veloVzMv*3);
//            _pKuroko->setVxMvAcce(dx);
//            _pKuroko->setVyMvAcce(dy);
//            _pKuroko->setVzMvAcce(dz);
//        } else {
//            dx = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_x - (_x + _pKuroko->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_y - (_y + _pKuroko->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_z - (_z + _pKuroko->_veloVzMv*3);
//            _pKuroko->setVxMvAcce(dx);
//            _pKuroko->setVyMvAcce(dy);
//            _pKuroko->setVzMvAcce(dz);
//        }
//    }
//    if (_pChip_front == nullptr) {
//        _pSeTx->behave();
//    }
//    WateringLaserChip::processBehavior();//座標を移動させてから呼び出すこと
//}
//
//void EnemyWateringLaserChip001::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
//
//    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
//        if (pOrg_->pLockonTarget_) { //既にオプションはロックオン中
//            if (pOther == pOrg_->pLockonTarget_) {
//                //オプションのロックオンに見事命中した場合
//
//                lockon_st_ = 2; //ロックオンをやめる。非ロックオン（ロックオン→非ロックオン）
//                //もうホーミングする必要はない。今後の方針を決定
//
//                //中間先頭チップがヒットした場合の処理。(_chip_kind=3の場合)
//                if (_pChip_front && _pChip_front->_pChip_front == nullptr) {
//                    //先端チップへ今後の方針を伝える。（先端チップは当たり判定がないため）
//                    EnemyWateringLaserChip001* pTip = (EnemyWateringLaserChip001*)_pChip_front; //先端チップ
//                    pTip->lockon_st_ = 2; //先端に伝える
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
//                    pTip->_pKuroko->setVxMvAcce(-(pChipPrev->_pKuroko->acceVxMv_));
//                    pTip->_pKuroko->setVyMvAcce(-(pChipPrev->_pKuroko->acceVyMv_));
//                    pTip->_pKuroko->setVzMvAcce(-(pChipPrev->_pKuroko->acceVzMv_));
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
//        int stamina = UTIL::calcEnemyStamina(this, pOther);
//        if (stamina <= 0) {
//            //一撃でチップ消滅の攻撃力
//            sayonara();
//            //ロックオン可能アクターならロックオン更新
//            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
//                pOrg_->pLockonTarget_ = pOther;
//            }
//        } else {
//            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
//            _pStatus->set(STAT_Stamina, default_stamina);
//            //ロックオン可能アクターならロックオン更新
//            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
//                pOrg_->pLockonTarget_ = pOther;
//            }
//        }
//    } else if (pOther->getKind() & KIND_CHIKEI) {
//        sayonara();
//    }
////        if (pOrg_->pLockonTarget_) {
////            _pKuroko->setVxMvVelo(-(_pKuroko->_veloVxMv));
////            _pKuroko->setVyMvVelo(-(_pKuroko->_veloVyMv));
////            _pKuroko->setVzMvVelo(-(_pKuroko->_veloVzMv));
////        }
//
//////        if (pOrg_->pLockonTarget_) {
////            _pKuroko->setVxMvVelo(-(_pKuroko->_veloVxMv));
////            //_pKuroko->setVxMvAcce(-(_pKuroko->acceVxMv_));
////            _pKuroko->setVyMvVelo(-(_pKuroko->_veloVyMv));
////            //_pKuroko->setVyMvAcce(-(_pKuroko->acceVyMv_));
////            _pKuroko->setVzMvVelo(-(_pKuroko->_veloVzMv));
////            //_pKuroko->setVzMvAcce(-(_pKuroko->acceVzMv_));
////            _pKuroko->behave();
//////        }
//
////        if (ABS(_pKuroko->_veloVxMv) >= ABS(_pKuroko->_veloVyMv) && ABS(_pKuroko->_veloVxMv) >= ABS(_pKuroko->_veloVzMv)) {
////            _pKuroko->setVxMvVelo(-(_pKuroko->_veloVxMv));
////            _pKuroko->setVxMvAcce(-(_pKuroko->acceVxMv_));
////        } else if (ABS(_pKuroko->_veloVyMv) >= ABS(_pKuroko->_veloVxMv) && ABS(_pKuroko->_veloVyMv) >= ABS(_pKuroko->_veloVzMv)) {
////            _pKuroko->setVyMvVelo(-(_pKuroko->_veloVyMv));
////            _pKuroko->setVyMvAcce(-(_pKuroko->acceVyMv_));
////        } else if (ABS(_pKuroko->_veloVzMv) >= ABS(_pKuroko->_veloVxMv) && ABS(_pKuroko->_veloVzMv) >= ABS(_pKuroko->_veloVyMv)) {
////            _pKuroko->setVzMvVelo(-(_pKuroko->_veloVzMv));
////            _pKuroko->setVzMvAcce(-(_pKuroko->acceVzMv_));
////        }
//
//
//}
//void EnemyWateringLaserChip001::processFinal() {
//    WateringLaserChip::processFinal();
//    //ロックオンが消滅ならば、切る
//    if (pOrg_->pLockonTarget_) {
//        if (pOrg_->pLockonTarget_->_pStatus->get(STAT_Stamina) <= 0) {
//            pOrg_->pLockonTarget_ = nullptr;
//            lockon_st_ = 2; //非ロックオン（ロックオン→非ロックオン）
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

