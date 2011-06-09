#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) ((a) > (MAX2(b, c)) ? (a) : (MAX2(b, c)))

MyOptionCurveLaserChip001::MyOptionCurveLaserChip001(const char* prm_name) :
        CurveLaserChip(prm_name, "MyOptionCurveLaserChip001") {
    _class_name = "MyOptionCurveLaserChip001";
    MyStgUtil::resetMyOptionCurveLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    _pOrg = NULL;
    _lockon = 0;
    _isLockon = false;
}

void MyOptionCurveLaserChip001::initialize() {
    _pMvNavigator->relateFaceAngWithMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    _SX = _SY = _SZ = 6 * 1000;
    _fAlpha = 0.99f;
    _radius_bounding_sphere = 60.0f;

}

void MyOptionCurveLaserChip001::onActive() {
    MyStgUtil::resetMyOptionCurveLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    CurveLaserChip::onActive();
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
        if (_pChip_front == NULL) {
            //先端チップ
            _lockon = 1;
        } else {
            //先端以外
            _lockon = ((MyOptionCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (_pChip_front == NULL) {
            //先端チップ
            _lockon = 0;
        } else {
            //先端以外
            _lockon = ((MyOptionCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
        }
    }
    _jerkVx = _jerkVy = _jerkVz = 0;      //躍度リセット
    _pMvTransporter->setZeroVxyzMvAcce(); //加速度リセット
    //Vxyzの速度はオプション側で設定される

    _renge = 150000;
    _pMvTransporter->forceVxyzMvVeloRange(-_renge, _renge);
    _maxAcceRange= _renge/20;
    _pMvTransporter->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);

//    MyStgUtil::resetMyOptionCurveLaserChip001Status(_pStatus);
//    _default_stamina = _pStatus->get(STAT_Stamina);
//    CurveLaserChip::onActive();
//    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
//    _pMvNavigator->setMvVelo(0);
//    _pMvTransporter->setVxMvAcce(0);
//    _pMvTransporter->setVyMvAcce(0);
//    _pMvTransporter->setVzMvAcce(0);
//    _isLockon = false;
//    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
//        if (_pChip_front == NULL) {
//            //先端チップ
//            _lockon = 1;
//            _isLockon = true;
//        } else {
//            //先端以外
//            _lockon = ((MyOptionCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
//            _isLockon = ((MyOptionCurveLaserChip001*) _pChip_front)->_isLockon;//一つ前のロックオン情報を引き継ぐ
//        }
//    } else {
//        if (_pChip_front == NULL) {
//            //先端チップ
//            _lockon = 0;
//        } else {
//            //先端以外
//            _lockon = ((MyOptionCurveLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
//            _isLockon = ((MyOptionCurveLaserChip001*) _pChip_front)->_isLockon;//一つ前のロックオン情報を引き継ぐ
//        }
//    }
//    _renge = 150000;
//    _pMvTransporter->forceVxyzMvVeloRange(-_renge, _renge);
//    _maxAcceRange= _renge / 30;
//    _pMvTransporter->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);


}

void MyOptionCurveLaserChip001::processBehavior() {
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();

    if (_lockon == 1) {
        if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
            //    |             vVT 仮的
            //    |     ─→        ^                           |      仮的
            //    |    |仮的| = 6v /                            |       ｜
            //    |               /           仮自              |       ｜
            //    |              /         ┐                   |      仮自
            //    |             /        ／vVM                  |       ｜
            //    |            /       ／                       |       ｜
            //    |           /      ／                         |       ｜
            //    |          /     ／                           |       ｜
            //    |         /    ／   ─→                      |       ｜
            //    |    vT 的   ／    |仮自| = 5v                |       的
            //    |       /  ／                                 |       ｜
            //    |      / ┐                                   |       ↑
            //    |     /／vM                                   |       ｜
            //    |    自                                       |       自
            // ---+---------------------------               ---+---------------------------
            //    |                                             |
            //
            //自→的
            int vTx = pMainLockOnTarget->_X - _X;
            int vTy = pMainLockOnTarget->_Y - _Y;
            int vTz = pMainLockOnTarget->_Z - _Z;
            //自→仮自
            int vVMx = _pMvTransporter->_veloVxMv*5;
            int vVMy = _pMvTransporter->_veloVyMv*5;
            int vVMz = _pMvTransporter->_veloVzMv*5;

            //|仮自|
            int lVM = MAX3(abs(vVMx), abs(vVMy), abs(vVMz)); //仮自ベクトル大きさ簡易版
            //|的|
            int lT =  MAX3(abs(vTx),abs(vTy),abs(vTz)); //的ベクトル大きさ簡易版
            //|仮自|/|的|
            double r = 1.3*lVM / lT;
            //自→仮的
            int vVTx = vTx * r;
            int vVTy = vTy * r;
            int vVTz = vTz * r;
            //仮自→仮的
            int vVMVTx = vVTx - vVMx;
            int vVMVTy = vVTy - vVMy;
            int vVMVTz = vVTz - vVMz;

            _pMvTransporter->setVxMvAcce(vVMVTx/5/20);
            _pMvTransporter->setVyMvAcce(vVMVTy/5/20);
            _pMvTransporter->setVzMvAcce(vVMVTz/5/20);
        } else {
            //_pMvTransporter->setZeroVxyzMvAcce();
            _lockon = 2;
        }
    }

    if (_lockon == 2) {
        //先端ならば特別に、オプションの反対の座標をターゲットする
        if (_pChip_front == NULL) {
            _new_target_X = _X + (_X - _pOrg->_X);
            _new_target_Y = _Y + (_Y - _pOrg->_Y);
            _new_target_Z = _Z + (_Z - _pOrg->_Z);
            int dx = _new_target_X - _X;
            int dy = _new_target_Y - _Y;
            int dz = _new_target_Z - _Z;
            _pMvTransporter->setVxMvAcce(dx);
            _pMvTransporter->setVyMvAcce(dy);
            _pMvTransporter->setVzMvAcce(dz);
        } else {
            //新たなターゲットを作成
            int dx = _pChip_front->_X - (_X + _pMvTransporter->_veloVxMv);
            int dy = _pChip_front->_Y - (_Y + _pMvTransporter->_veloVyMv);
            int dz = _pChip_front->_Z - (_Z + _pMvTransporter->_veloVzMv);
            _pMvTransporter->setVxMvAcce(dx/20);
            _pMvTransporter->setVyMvAcce(dy/20);
            _pMvTransporter->setVzMvAcce(dz/20);
        }

    }
//なす角を小さくなるように頑張れば良い
//    →                       →
//    Ａ = (ａｘ, ａｙ, ａｚ)  Ｂ ＝ (ｂｘ, ｂｙ, ｂｚ)
//
//    Ａ×Ｂ ＝ (ａｙ･ｂｚ - ａｚ･ｂｙ,  ａｚ･ｂｘ - ａｘ･ｂｚ,  ａｘ･ｂｙ － ａｙ･ｂｘ)
//
//    |Ａ×Ｂ| = |Ａ||Ｂ|sin(θ)

    CurveLaserChip::processBehavior();//座標を移動させてから呼び出すこと




//    int TX = pMainLockOnTarget->_X - _X;
//    int TY = pMainLockOnTarget->_Y - _Y;
//    int TZ = pMainLockOnTarget->_Z - _Z;
//    int dot = _pMvTransporter->dot(TX,TY,TZ);
//    if (dot < _pMvTransporter->dot(TX+1000,TY,TZ)) {
//        _pMvTransporter->addVxMvAcce(-500);
//    } else {
//        _pMvTransporter->addVxMvAcce(+500);
//    }
//    if (dot < _pMvTransporter->dot(TX,TY+1000,TZ)) {
//        _pMvTransporter->addVyMvAcce(-500);
//    } else {
//        _pMvTransporter->addVyMvAcce(+500);
//    }
//    if (dot < _pMvTransporter->dot(TX,TY,TZ+1000)) {
//        _pMvTransporter->addVzMvAcce(-500);
//    } else {
//        _pMvTransporter->addVzMvAcce(+500);
//    }
//            int fdx = pMainLockOnTarget->_X - (_X + _pMvTransporter->_veloVxMv*5);
//            int fdy = pMainLockOnTarget->_Y - (_Y + _pMvTransporter->_veloVyMv*5);
//            int fdz = pMainLockOnTarget->_Z - (_Z + _pMvTransporter->_veloVzMv*5);
//            //velo : _renge = x : _maxAcceRange
//            // x = velo  _maxAcceRange / _renge
//            _pMvTransporter->addVxMvAcce(sgn(fdx)*((_pMvTransporter->_veloVxMv*_maxAcceRange) /_renge) );
//            _pMvTransporter->addVyMvAcce(sgn(fdy)*((_pMvTransporter->_veloVyMv*_maxAcceRange) /_renge) );
//            _pMvTransporter->addVzMvAcce(sgn(fdz)*((_pMvTransporter->_veloVzMv*_maxAcceRange) /_renge) );



//    int fdx = pMainLockOnTarget->_X - (_X + _pMvTransporter->_veloVxMv*5);
//    int fdy = pMainLockOnTarget->_Y - (_Y + _pMvTransporter->_veloVyMv*5);
//    int fdz = pMainLockOnTarget->_Z - (_Z + _pMvTransporter->_veloVzMv*5);
//    //velo : _renge = x : _maxAcceRange
//    // x = velo  _maxAcceRange / _renge
//    _pMvTransporter->addVxMvAcce(sgn(fdx)*((_pMvTransporter->_veloVxMv*_maxAcceRange) /_renge) );
//    _pMvTransporter->addVyMvAcce(sgn(fdy)*((_pMvTransporter->_veloVyMv*_maxAcceRange) /_renge) );
//    _pMvTransporter->addVzMvAcce(sgn(fdz)*((_pMvTransporter->_veloVzMv*_maxAcceRange) /_renge) );


//    int fdx = pMainLockOnTarget->_X - _X;
//    int fdy = pMainLockOnTarget->_Y - _Y;
//    int fdz = pMainLockOnTarget->_Z - _Z;
//    _jerkVx = sgn(fdx) * 100;
//    _jerkVy = sgn(fdy) * 100;
//    _jerkVz = sgn(fdz) * 100;
//    _pMvTransporter->_acceVxMv += _jerkVx;
//    _pMvTransporter->_acceVyMv += _jerkVy;
//    _pMvTransporter->_acceVzMv += _jerkVz;






















//    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
//
//    if (_lockon == 1) {
//        if (getActivePartFrame() < 120) {
//            _maxAcceRange+=100;
//            _pMvTransporter->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
////            if (_pOrg->_pLockonTarget && _pOrg->_pLockonTarget->isActiveActor() && _pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) > 0) {
//                                                                                 //体力の判定はオプション側で行うことにした
//            if (pMainLockOnTarget) {
//                if (pMainLockOnTarget->isActiveActor()) {
//                    float rate = 8.0 - 0.06*getActivePartFrame(); //0.06 * 120 = 8.0
//                    rate = rate > 0 ? rate : 0;
//                    int fdx = pMainLockOnTarget->_X - (_X + _pMvTransporter->_veloVxMv*rate);
//                    int fdy = pMainLockOnTarget->_Y - (_Y + _pMvTransporter->_veloVyMv*rate);
//                    int fdz = pMainLockOnTarget->_Z - (_Z + _pMvTransporter->_veloVzMv*rate);
//                    _pMvTransporter->setVxMvAcce(fdx);
//                    _pMvTransporter->setVyMvAcce(fdy);
//                    _pMvTransporter->setVzMvAcce(fdz);
//                } else {
//
//
//                }
//            } else {
//                _lockon = 2;
//            }
//        } else {
//            _lockon = 2;
//        }
//    }
//
//
//
//    int dx, dy, dz;
//    if (_lockon == 2) {
//        if (_isLockon) {
//            _isLockon = false;
//            //先端ならば特別に、オプションの反対の座標をターゲットする
//            if (_pChip_front == NULL) {
//                _new_target_X = _X + (_X - _pOrg->_X);
//                _new_target_Y = _Y + (_Y - _pOrg->_Y);
//                _new_target_Z = _Z + (_Z - _pOrg->_Z);
//                dx = _new_target_X - (_X );
//                dy = _new_target_Y - (_Y );
//                dz = _new_target_Z - (_Z );
//                _pMvTransporter->setVxMvAcce(dx);
//                _pMvTransporter->setVyMvAcce(dy);
//                _pMvTransporter->setVzMvAcce(dz);
//            }
//        }
//
//
//
//        _maxAcceRange+=100;
//        _pMvTransporter->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
//        if (_pChip_front == NULL) {
//            _maxAcceRange+=100;
//            //上の処理１回と、毎回 _maxAcceRange+=100;
//        } else if (_pChip_front->_pChip_front == NULL) {
//            //新たなターゲットを作成
//            dx = _pChip_front->_X - (_X + _pMvTransporter->_veloVxMv);
//            dy = _pChip_front->_Y - (_Y + _pMvTransporter->_veloVyMv);
//            dz = _pChip_front->_Z - (_Z + _pMvTransporter->_veloVzMv);
//            _pMvTransporter->setVxMvAcce(dx);
//            _pMvTransporter->setVyMvAcce(dy);
//            _pMvTransporter->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
//            dx = _pChip_front->_pChip_front->_X - (_X + _pMvTransporter->_veloVxMv*2);
//            dy = _pChip_front->_pChip_front->_Y - (_Y + _pMvTransporter->_veloVyMv*2);
//            dz = _pChip_front->_pChip_front->_Z - (_Z + _pMvTransporter->_veloVzMv*2);
//            _pMvTransporter->setVxMvAcce(dx);
//            _pMvTransporter->setVyMvAcce(dy);
//            _pMvTransporter->setVzMvAcce(dz);
//        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == NULL) {
//            dx = _pChip_front->_pChip_front->_pChip_front->_X - (_X + _pMvTransporter->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pMvTransporter->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pMvTransporter->_veloVzMv*3);
//            _pMvTransporter->setVxMvAcce(dx);
//            _pMvTransporter->setVyMvAcce(dy);
//            _pMvTransporter->setVzMvAcce(dz);
//        } else {
//            dx = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_X - (_X + _pMvTransporter->_veloVxMv*3);
//            dy = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Y - (_Y + _pMvTransporter->_veloVyMv*3);
//            dz = _pChip_front->_pChip_front->_pChip_front->_pChip_front->_Z - (_Z + _pMvTransporter->_veloVzMv*3);
//            _pMvTransporter->setVxMvAcce(dx);
//            _pMvTransporter->setVyMvAcce(dy);
//            _pMvTransporter->setVzMvAcce(dz);
//        }
//    }
//    if (_pChip_front == NULL) {
//        _pSeTransmitter->behave();
//    }
//
////    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
////        _lockon = 1;
////        _isLockon = true;
////    }
//
////    _pMvNavigator->_angFace[AXIS_X] =  _pOrg->_pMvNavigator->_angFace[AXIS_Y];
//    CurveLaserChip::processBehavior();//座標を移動させてから呼び出すこと
//
//    //根元からレーザー表示のため強制的に座標補正
//    if (onChangeToActive()) {
//        locateAs(_pOrg);
//        _tmpX = _X;
//        _tmpY = _Y;
//        _tmpZ = _Z;
//    }

}

void MyOptionCurveLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDx9DrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void MyOptionCurveLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*) prm_pOtherActor;
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    //ヒットエフェクト
    //無し

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //既にオプションはロックオン中
            if (pOther == pMainLockOnTarget) {
                //オプションのロックオンに見事命中した場合

                _lockon = 2; //ロックオンをやめる。非ロックオン（ロックオン→非ロックオン）
                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
                    //中間先頭チップがヒットした場合、先端にも伝える
                    ((MyOptionCurveLaserChip001*)_pChip_front)->_lockon = 2;
                }
            } else {
                //オプションのロックオン以外のアクターに命中した場合
            }
        } else {
            //オプション非ロックオン中に命中した場合
        }

        int stamina = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力

            //破壊されたエフェクト
            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
            if (pExplo001) {
                pExplo001->locateAs(this);
                pExplo001->activate();
            }
            //ロックオン可能アクターならロックオン
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                _pOrg->_pLockonController->lockon(pOther);
            }
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            _pStatus->set(STAT_Stamina, _default_stamina);
            //ロックオン可能アクターならロックオン
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                _pOrg->_pLockonController->lockon(pOther);
            }
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら

        //破壊されたエフェクト
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->activate();
        }
        sayonara();
    }
}
//void MyOptionCurveLaserChip001::processFinal() {
//    CurveLaserChip::processFinal();
//    //ロックオンが消滅ならば、切る
//    if (_pOrg->_pLockonTarget) {
//        if (_pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) <= 0) {
//            _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
//        }
//    }
//}

void MyOptionCurveLaserChip001::onInactive() {
    CurveLaserChip::onInactive();
    _lockon = 0;
}

MyOptionCurveLaserChip001::~MyOptionCurveLaserChip001() {
}

