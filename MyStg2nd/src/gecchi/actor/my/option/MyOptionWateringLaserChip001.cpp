#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;



MyOptionWateringLaserChip001::MyOptionWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyOptionWateringLaserChip001") {
    _class_name = "MyOptionWateringLaserChip001";
    MyStgUtil::resetMyOptionWateringLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    _pOrg = NULL;
    _lockon = 0;
    _isLockon = false;
}

void MyOptionWateringLaserChip001::initialize() {
    _pMvNavigator->relateFaceAngWithMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    setScaleRate(6.0);
    setAlpha(0.99);
}

void MyOptionWateringLaserChip001::onActive() {
    MyStgUtil::resetMyOptionWateringLaserChip001Status(_pStatus);
    _default_stamina = _pStatus->get(STAT_Stamina);
    WateringLaserChip::onActive();
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
        if (_pChip_front == NULL) {
            //先端チップ
            _lockon = 1;
        } else {
            //先端以外
            _lockon = ((MyOptionWateringLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (_pChip_front == NULL) {
            //先端チップ
            _lockon = 0;
        } else {
            //先端以外
            _lockon = ((MyOptionWateringLaserChip001*) _pChip_front)->_lockon;//一つ前のロックオン情報を引き継ぐ
        }
    }
    _jerkVx = _jerkVy = _jerkVz = 0;      //躍度リセット
    _pMvTransporter->setZeroVxyzMvAcce(); //加速度リセット
    //Vxyzの速度はオプション側で設定される

    _renge = 180000;
    _pMvTransporter->forceVxyzMvVeloRange(-_renge, _renge);
    _maxAcceRange= _renge/R_MAXACCE;
    _pMvTransporter->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
}

void MyOptionWateringLaserChip001::processBehavior() {
    GgafDx9GeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    if (getActivePartFrame() > 3) {
        if (_lockon == 1) {
            if (pMainLockOnTarget && pMainLockOnTarget->isActiveActor()) {
                //    |             vVT 仮的                        |
                //    |                 ^                           |      仮的
                //    |  |仮的| > 5*vM /                            |       ｜
                //    |               /           仮自              |       ｜
                //    |              /         ┐                   |      仮自
                //    |             /        ／vVM                  |       ｜
                //    |            /       ／                       |       ｜
                //    |           /      ／                         |       ｜
                //    |          /     ／                           |       ｜
                //    |         /    ／                             |       ｜
                //    |    vT 的   ／    |仮自| = 5*vM              |       的
                //    |       /  ／                                 |       ｜
                //    |      / ┐vM                                 |       ↑
                //    |     /／ (_veloVxMv,_veloVyMv,_veloVzMv)     |       ｜
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
                int lT =  MAX3(abs(vTx), abs(vTy), abs(vTz)); //的ベクトル大きさ簡易版
                //|仮自|/|的|
                double r = 1.5*lVM / lT;
                //仮自→仮的 の加速度設定
                _pMvTransporter->setVxMvAcce(((vTx * r) - vVMx)/R_MAXACCE);
                _pMvTransporter->setVyMvAcce(((vTy * r) - vVMy)/R_MAXACCE);
                _pMvTransporter->setVzMvAcce(((vTz * r) - vVMz)/R_MAXACCE);
            } else {
                //_pMvTransporter->setZeroVxyzMvAcce();
                _lockon = 2;
            }
        }

        if (_lockon == 2) {

            //先端ならば特別に、オプションの反対の座標をターゲットする
            if (_pChip_front == NULL) {
                int dx = (_X - _pOrg->_X);
                int dy = (_Y - _pOrg->_Y);
                int dz = (_Z - _pOrg->_Z);
                int dmax = MAX3(abs(dx), abs(dx), abs(dz));
                _pMvTransporter->setVxMvAcce((1.0*dx/dmax)*_maxAcceRange);
                _pMvTransporter->setVyMvAcce((1.0*dy/dmax)*_maxAcceRange);
                _pMvTransporter->setVzMvAcce((1.0*dz/dmax)*_maxAcceRange);
            } else {
                //新たなターゲットを作成
                _pMvTransporter->setVxMvAcce((_pChip_front->_X - _X)/R_MAXACCE);
                _pMvTransporter->setVyMvAcce((_pChip_front->_Y - _Y)/R_MAXACCE);
                _pMvTransporter->setVzMvAcce((_pChip_front->_Z - _Z)/R_MAXACCE);
            }

        }
    }
    WateringLaserChip::processBehavior();//座標を移動させてから呼び出すこと
    //根元からレーザー表示のため強制的に座標補正
    if (onChangeToActive()) {
        locateAs(_pOrg);
        _tmpX = _X;
        _tmpY = _Y;
        _tmpZ = _Z;
    }

}

void MyOptionWateringLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void MyOptionWateringLaserChip001::onHit(GgafActor* prm_pOtherActor) {
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
                    ((MyOptionWateringLaserChip001*)_pChip_front)->_lockon = 2;
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
//void MyOptionWateringLaserChip001::processFinal() {
//    WateringLaserChip::processFinal();
//    //ロックオンが消滅ならば、切る
//    if (_pOrg->_pLockonTarget) {
//        if (_pOrg->_pLockonTarget->_pStatus->get(STAT_Stamina) <= 0) {
//            _lockon = 2; //非ロックオン（ロックオン→非ロックオン）
//        }
//    }
//}

void MyOptionWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
    _lockon = 0;
}

MyOptionWateringLaserChip001::~MyOptionWateringLaserChip001() {
}

