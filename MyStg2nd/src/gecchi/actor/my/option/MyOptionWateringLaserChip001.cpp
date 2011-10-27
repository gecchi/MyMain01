#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;



MyOptionWateringLaserChip001::MyOptionWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyOptionWateringLaserChip001", STATUS(MyOptionWateringLaserChip001)) {
    _class_name = "MyOptionWateringLaserChip001";
    _default_stamina = _pStatus->get(STAT_Stamina);
    _pOrg = NULL;
    _lockon = 0;
    _isLockon = false;
    _renge = 160000; //この値を大きくすると、最高速度が早くなる。
    _r_maxacce = 18; //この値を大きくすると、カーブが緩くなる
}

void MyOptionWateringLaserChip001::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    setScaleRate(6.0);
    setAlpha(0.99);
}

void MyOptionWateringLaserChip001::onActive() {
    _pStatus->reset();
    _default_stamina = _pStatus->get(STAT_Stamina);
    WateringLaserChip::onActive();
    GgafDxGeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
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
    _pKurokoB->setZeroVxyzMvAcce(); //加速度リセット
    //Vxyzの速度はオプション側で設定される


    _pKurokoB->forceVxyzMvVeloRange(-_renge, _renge);
    _maxAcceRange= _renge/_r_maxacce;
    _pKurokoB->forceVxyzMvAcceRange(-_maxAcceRange, _maxAcceRange);
}

void MyOptionWateringLaserChip001::processBehavior() {
    _KTRACE_("this="<<this<<" "<<getName()<<"  "<<_pChip_front <<"<--["<<this<<"]<--"<<_pChip_behind);

    GgafDxGeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
    if (getActivePartFrame() > 6) {
        if (_lockon == 1) {
            if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
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
                //自→仮自。上図の |仮自| = 5*vM
                int vVMx = _pKurokoB->_veloVxMv*5;
                int vVMy = _pKurokoB->_veloVyMv*5;
                int vVMz = _pKurokoB->_veloVzMv*5;

                //|仮自|
                int lVM = MAX3(abs(vVMx), abs(vVMy), abs(vVMz)); //仮自ベクトル大きさ簡易版
                //|的|
                int lT =  MAX3(abs(vTx), abs(vTy), abs(vTz)); //的ベクトル大きさ簡易版
                //|仮自|/|的|
                double r = 1.5*lVM / lT;
                //1.5は 右上図のように一直線に並んだ際も、進行方向を維持するために、
                //|仮的| > |仮自| という関係を維持するためにかけた適当な割合

                //仮自→仮的 の加速度設定
                double accX = ((vTx * r) - vVMx)/_r_maxacce;
                double accY = ((vTy * r) - vVMy)/_r_maxacce;
                double accZ = ((vTz * r) - vVMz)/_r_maxacce;

                if (_pChip_front == NULL) {
                    //先頭はやや速めに
                    _pKurokoB->setVxMvAcce(accX+sgn(accX)*5); //sgn(accX)*5 を加算するのは、加速度を0にしないため
                    _pKurokoB->setVyMvAcce(accY+sgn(accY)*5);
                    _pKurokoB->setVzMvAcce(accZ+sgn(accZ)*5);
                } else {
                    _pKurokoB->setVxMvAcce(accX+sgn(accX)*3); //sgn(accX)*3 を加算するのは、加速度を0にしないため
                    _pKurokoB->setVyMvAcce(accY+sgn(accY)*3);
                    _pKurokoB->setVzMvAcce(accZ+sgn(accZ)*3);
                }
                //ネジレ描画が汚くならないように回転を制限
                if (lVM > _renge/2) {
                    angle RZ_temp = _RZ;
                    angle RY_temp = _RY;
                    GgafDxUtil::getRzRyAng(vVMx, vVMy, vVMz,
                                            RZ_temp, RY_temp);
                    angle angDRZ = GgafDxUtil::getAngDiff(RZ_temp, _RZ);
                    angle angDRY = GgafDxUtil::getAngDiff(RY_temp, _RY);
                    if (-4000 <= angDRZ) {
                        _RZ -= 4000;
                    } else if (angDRZ <= 4000) {
                        _RZ += 4000;
                    } else {
                        _RZ += angDRZ;
                    }
                    if (-4000 <= angDRY) {
                        _RY -= 4000;
                    } else if (angDRY <= 4000) {
                        _RY += 4000;
                    } else {
                        _RY += angDRY;
                    }
                    if (_RZ >= D360ANG) {
                        _RZ -= D360ANG;
                    }
                    if (_RZ < 0) {
                        _RZ += D360ANG;
                    }
                    if (_RY >= D360ANG) {
                        _RY -= D360ANG;
                    }
                    if (_RY < 0) {
                        _RY += D360ANG;
                    }
                }
            } else {
                //_pKurokoB->setZeroVxyzMvAcce();
                _lockon = 2;
            }
        }

        if (_lockon == 2) {
//
            int vTx,vTy,vTz;
            if (_pChip_front == NULL) {
                //先端ならば特別に、オプションの反対の座標をターゲットする
                int dx = (_X - _pOrg->_X);
                int dy = (_Y - _pOrg->_Y);
                int dz = (_Z - _pOrg->_Z);
                static coord zf = DX2CO(P_CAM->_zf)*2;
                vTx = _X+dx*(dx == 0 ? zf : abs(zf/dx));
                vTy = _Y+dy*(dy == 0 ? zf : abs(zf/dy));
                vTz = _Z+dz*(dz == 0 ? zf : abs(zf/dz));
            } else {
                LaserChip* p = _pChip_front;
                for (int i = 0; i < 4; i++) {
                    if (p->_pChip_front == NULL) {
                        vTx = p->_X - _X;
                        vTy = p->_Y - _Y;
                        vTz = p->_Z - _Z;
                    } else {
                        p = p->_pChip_front;
                    }
                }
            }

            //自→仮自。上図の |仮自| = 5*vM
            int vVMx = _pKurokoB->_veloVxMv*5;
            int vVMy = _pKurokoB->_veloVyMv*5;
            int vVMz = _pKurokoB->_veloVzMv*5;
            //|仮自|
            int lVM = MAX3(abs(vVMx), abs(vVMy), abs(vVMz)); //仮自ベクトル大きさ簡易版
            //|的|
            int lT =  MAX3(abs(vTx), abs(vTy), abs(vTz)); //的ベクトル大きさ簡易版
            //|仮自|/|的|
            double r = 1.5*lVM / lT;
            //1.5は 右上図のように一直線に並んだ際も、進行方向を維持するために、
            //|仮的| > |仮自| という関係を維持するためにかけた適当な割合

            //仮自→仮的 の加速度設定
            double accX = ((vTx * r) - vVMx)/_r_maxacce;
            double accY = ((vTy * r) - vVMy)/_r_maxacce;
            double accZ = ((vTz * r) - vVMz)/_r_maxacce;
            if (_pChip_front == NULL) {
                //先頭はやや速めに
                _pKurokoB->setVxMvAcce(accX+sgn(accX)*5); //sgn(accX)*5 を加算するのは、加速度を0にしないため
                _pKurokoB->setVyMvAcce(accY+sgn(accY)*5);
                _pKurokoB->setVzMvAcce(accZ+sgn(accZ)*5);
            } else {
                _pKurokoB->setVxMvAcce(accX+sgn(accX)*3); //sgn(accX)*3 を加算するのは、加速度を0にしないため
                _pKurokoB->setVyMvAcce(accY+sgn(accY)*3);
                _pKurokoB->setVzMvAcce(accZ+sgn(accZ)*3);
            }


            if (lVM > _renge/2) {
                angle RZ_temp = _RZ;
                angle RY_temp = _RY;
                GgafDxUtil::getRzRyAng(vVMx, vVMy, vVMz,
                                        RZ_temp, RY_temp);
                angle angDRZ = GgafDxUtil::getAngDiff(RZ_temp, _RZ);
                angle angDRY = GgafDxUtil::getAngDiff(RY_temp, _RY);
                if (-4000 <= angDRZ) {
                    _RZ -= 4000;
                } else if (angDRZ <= 4000) {
                    _RZ += 4000;
                } else {
                    _RZ += angDRZ;
                }
                if (-4000 <= angDRY) {
                    _RY -= 4000;
                } else if (angDRY <= 4000) {
                    _RY += 4000;
                } else {
                    _RY += angDRY;
                }
                if (_RZ >= D360ANG) {
                    _RZ -= D360ANG;
                }
                if (_RZ < 0) {
                    _RZ += D360ANG;
                }
                if (_RY >= D360ANG) {
                    _RY -= D360ANG;
                }
                if (_RY < 0) {
                    _RY += D360ANG;
                }
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
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void MyOptionWateringLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    GgafDxGeometricActor* pMainLockOnTarget = _pOrg->_pLockonController->_pRingTarget->getCurrent();
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
            EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
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
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
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

