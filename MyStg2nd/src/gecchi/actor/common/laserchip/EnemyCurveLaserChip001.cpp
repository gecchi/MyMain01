#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace EnemyStg2nd;

EnemyCurveLaserChip001::EnemyCurveLaserChip001(const char* prm_name) :
        CurveLaserChip(prm_name, "EnemyCurveLaserChip001") {
    _class_name = "EnemyCurveLaserChip001";
    EnemyStgUtil::resetEnemyCurveLaserChip001Status(_pStatus);
    _pOrg = NULL;
    _lockon = 0;

}

void EnemyCurveLaserChip001::initialize() {
    _pMover->relateRzRyFaceAngToMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    _SX = _SY = _SZ = 6 * 1000;
    _fAlpha = 0.99f;
    _fBoundingSphereRadius = 60.0f;

}

void EnemyCurveLaserChip001::onActive() {
    EnemyStgUtil::resetEnemyCurveLaserChip001Status(_pStatus);
    CurveLaserChip::onActive();
    _pMover->setMvVelo(0);
    _pMover->setVxMvAcce(0);
    _pMover->setVyMvAcce(0);
    _pMover->setVzMvAcce(0);
    if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
        if (_pChip_front == NULL) {
            //先端チップ
            _lockon = 1;
        } else {
            //先端以外
            _lockon = ((EnemyCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (_pChip_front == NULL) {
            //先端チップ
            _lockon = 0;
        } else {
            //先端以外
            _lockon = ((EnemyCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
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

void EnemyCurveLaserChip001::processBehavior() {
    if (_lockon == 1) {
        if (getPartFrame() < 100) {
            _maxAcceRange+=100;
            _pMover->forceVxMvAcceRange(-_maxAcceRange, _maxAcceRange);
            _pMover->forceVyMvAcceRange(-_maxAcceRange, _maxAcceRange);
            _pMover->forceVzMvAcceRange(-_maxAcceRange, _maxAcceRange);
            if (_pOrg->_pLockOnTarget && _pOrg->_pLockOnTarget->isActive()) {
                float rate = 8.0 - 0.06*getPartFrame(); //0.06 * 120 = 8.0
                rate = rate > 0 ? rate : 0;
                int fdx = _pOrg->_pLockOnTarget->_X - (_X + _pMover->_veloVxMv*rate);
                int fdy = _pOrg->_pLockOnTarget->_Y - (_Y + _pMover->_veloVyMv*rate);
                int fdz = _pOrg->_pLockOnTarget->_Z - (_Z + _pMover->_veloVzMv*rate);
                _pMover->setVxMvAcce(fdx);
                _pMover->setVyMvAcce(fdy);
                _pMover->setVzMvAcce(fdz);
//                //上記のホーミングは優秀だが、距離に応じて減速していくため移動する敵には永遠に当たらない。
//                //ある程度近づいたら見切りで直進させる
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
                _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
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
            //新たなターゲットを作成
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
    CurveLaserChip::processBehavior();//座標を移動させてから呼び出すこと
}

void EnemyCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*) prm_pOtherActor;

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (_pOrg->_pLockOnTarget) { //既にオプションはロックオン中
            if (pOther == _pOrg->_pLockOnTarget) {
                //オプションのロックオンに見事命中した場合

                _lockon = 2; //ロックオンをやめる。非ロックオン（ロックオン→非ロックオン）
                //もうホーミングする必要はない。今後の方針を決定

                //中間先頭チップがヒットした場合の処理。(_chip_kind=3の場合)
                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
                    //先端チップへ今後の方針を伝える。（先端チップは当たり判定がないため）
                    EnemyCurveLaserChip001* pTip = (EnemyCurveLaserChip001*)_pChip_front; //先端チップ
                    pTip->_lockon = 2; //先端に伝える
                    //今後の移動方角(加速度)を伝えるのだが、先端チップや自身や移動方向は、急激な角度に曲がっている可能性が極めて高く
                    //不自然な角度のカーブを描きかねないので、やや後方のチップが存在するならば、そちらの移動方向をコピーする。
                    LaserChip* pChipPrev = this;
                    for (int i = 0; i < 4; i++) { //最高3つ後方まで在れば採用
                        if (pChipPrev->_pChip_behind) {
                            pChipPrev = pChipPrev->_pChip_behind;
                        } else {
                            break;
                        }
                    }
                    pTip->_pMover->setVxMvVelo(pChipPrev->_pMover->_veloVxMv*2);
                    pTip->_pMover->setVyMvVelo(pChipPrev->_pMover->_veloVyMv*2);
                    pTip->_pMover->setVzMvVelo(pChipPrev->_pMover->_veloVzMv*2);
                    //ターゲットがなくなり、レーザーの「ハジけた感（解放感）」を演出するため
                    //加速度の正負逆を設定する。
                    pTip->_pMover->setVxMvAcce(-(pChipPrev->_pMover->_acceVxMv));
                    pTip->_pMover->setVyMvAcce(-(pChipPrev->_pMover->_acceVyMv));
                    pTip->_pMover->setVzMvAcce(-(pChipPrev->_pMover->_acceVzMv));
                }
            } else {
                //オプションのロックオン以外のアクターに命中した場合

            }
        } else {
            //オプション非ロックオン中に命中した場合

        }
        int default_stamina = _pStatus->get(STAT_Stamina);
        int stamina = EnemyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力
            sayonara();
            //ロックオン可能アクターならロックオン更新
            if (pOther->_pStatus->get(STAT_LockOnAble) == 1) {
                _pOrg->_pLockOnTarget = pOther;
            }
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            _pStatus->set(STAT_Stamina, default_stamina);
            //ロックオン可能アクターならロックオン更新
            if (pOther->_pStatus->get(STAT_LockOnAble) == 1) {
                _pOrg->_pLockOnTarget = pOther;
            }
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        sayonara();
    }
//        if (_pOrg->_pLockOnTarget) {
//            _pMover->setVxMvVelo(-(_pMover->_veloVxMv));
//            _pMover->setVyMvVelo(-(_pMover->_veloVyMv));
//            _pMover->setVzMvVelo(-(_pMover->_veloVzMv));
//        }

////        if (_pOrg->_pLockOnTarget) {
//            _pMover->setVxMvVelo(-(_pMover->_veloVxMv));
//            //_pMover->setVxMvAcce(-(_pMover->_acceVxMv));
//            _pMover->setVyMvVelo(-(_pMover->_veloVyMv));
//            //_pMover->setVyMvAcce(-(_pMover->_acceVyMv));
//            _pMover->setVzMvVelo(-(_pMover->_veloVzMv));
//            //_pMover->setVzMvAcce(-(_pMover->_acceVzMv));
//            _pMover->behave();
////        }

//        if (abs(_pMover->_veloVxMv) >= abs(_pMover->_veloVyMv) && abs(_pMover->_veloVxMv) >= abs(_pMover->_veloVzMv)) {
//            _pMover->setVxMvVelo(-(_pMover->_veloVxMv));
//            _pMover->setVxMvAcce(-(_pMover->_acceVxMv));
//        } else if (abs(_pMover->_veloVyMv) >= abs(_pMover->_veloVxMv) && abs(_pMover->_veloVyMv) >= abs(_pMover->_veloVzMv)) {
//            _pMover->setVyMvVelo(-(_pMover->_veloVyMv));
//            _pMover->setVyMvAcce(-(_pMover->_acceVyMv));
//        } else if (abs(_pMover->_veloVzMv) >= abs(_pMover->_veloVxMv) && abs(_pMover->_veloVzMv) >= abs(_pMover->_veloVyMv)) {
//            _pMover->setVzMvVelo(-(_pMover->_veloVzMv));
//            _pMover->setVzMvAcce(-(_pMover->_acceVzMv));
//        }


}
void EnemyCurveLaserChip001::processFinal() {
    CurveLaserChip::processFinal();
    //ロックオンが消滅ならば、切る
    if (_pOrg->_pLockOnTarget) {
        if (_pOrg->_pLockOnTarget->_pStatus->get(STAT_Stamina) <= 0) {
            _pOrg->_pLockOnTarget = NULL;
            _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
        }
    }
}

void EnemyCurveLaserChip001::onInactive() {
    CurveLaserChip::onInactive();
    _lockon = 0;
}

EnemyCurveLaserChip001::~EnemyCurveLaserChip001() {
}

