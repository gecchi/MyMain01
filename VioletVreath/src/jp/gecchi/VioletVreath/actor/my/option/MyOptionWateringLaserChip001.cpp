#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



MyOptionWateringLaserChip001::MyOptionWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyOptionWateringLaserChip001", STATUS(MyOptionWateringLaserChip001)) {
    _class_name = "MyOptionWateringLaserChip001";
    default_stamina_ = _pStatus->get(STAT_Stamina);
    pOrg_ = NULL;
    lockon_st_ = 0;
    is_lockon_ = false;
    max_acce_renge_ = 0;
    max_velo_renge_ = 160000; //この値を大きくすると、最高速度が早くなる。
    r_max_acce_ = 18; //この値を大きくすると、カーブが緩くなる
}

void MyOptionWateringLaserChip001::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    registHitAreaCube(80000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
}

void MyOptionWateringLaserChip001::onActive() {
    _pStatus->reset();
    default_stamina_ = _pStatus->get(STAT_Stamina);
    WateringLaserChip::onActive();
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (_pChip_front == NULL) {
            //先端チップ
            lockon_st_ = 1;
        } else {
            //先端以外
            MyOptionWateringLaserChip001* pF = (MyOptionWateringLaserChip001*) _pChip_front;
            lockon_st_ = pF->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (_pChip_front == NULL) {
            //先端チップ
            lockon_st_ = 0;
        } else {
            //先端以外
            MyOptionWateringLaserChip001* pF = (MyOptionWateringLaserChip001*) _pChip_front;
            lockon_st_ = pF->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    }
    _pKurokoB->setZeroVxyzMvAcce(); //加速度リセット
    //Vxyzの速度はオプション側で設定される


    _pKurokoB->forceVxyzMvVeloRange(-max_velo_renge_, max_velo_renge_);
    max_acce_renge_ = max_velo_renge_/r_max_acce_;
    _pKurokoB->forceVxyzMvAcceRange(-max_acce_renge_, max_acce_renge_);
}

void MyOptionWateringLaserChip001::processBehavior() {
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();
    if (getActivePartFrame() > 6) {
        if (lockon_st_ == 1) {
            if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
                moveChip(pMainLockOnTarget->_X,
                         pMainLockOnTarget->_Y,
                         pMainLockOnTarget->_Z );
            } else {
                //_pKurokoB->setZeroVxyzMvAcce();
                lockon_st_ = 2;
            }
        }

        if (lockon_st_ == 2) {
            if (_pLeader) {
                if (_pLeader == this) {
                    moveChip(_X + _pKurokoB->_veloVxMv*4+1,
                             _Y + _pKurokoB->_veloVyMv*2+1,
                             _Z + _pKurokoB->_veloVzMv*2+1 );
                } else {
                    moveChip(_pLeader->_X, _pLeader->_Y, _pLeader->_Z);
                }
            }
        }
    }

    WateringLaserChip::processBehavior();//座標を移動させてから呼び出すこと
    //根元からレーザー表示のため強制的に座標補正
    if (onChangeToActive()) {
        locateWith(pOrg_);
        _tmpX = _X;
        _tmpY = _Y;
        _tmpZ = _Z;
    }

}

void MyOptionWateringLaserChip001::moveChip(int tX,int tY, int tZ) {
    //    |                            vVT 仮的                        |
    //    |                                ^ ┌                        |
    //    |                 |仮的| > 5*vM /    ＼  vVP 仮自→仮的      |      仮的
    //    |                 となるような /       ＼                    |       ↑
    //    |                 vVTを設定   /         ┐                   |      仮自
    //    |                            /        ／vVM  仮自            |       ↑
    //    |                           /       ／  (vVMx,vVMy,vVMz)     |       ｜
    //    |                          /      ／                         |       ｜
    //    |                         /     ／                           |       ｜
    //    |                        /    ／ |仮自| = 5*vM = lVM         |       ｜
    //    |                   vT 的   ／                               |       的
    //    |             ┌       ^  ／                                 |       ↑
    //    |               ＼    / ┐vM 現在の移動方向ベクトル          |       ｜
    //    | vVP 仮自→仮的  ＼ /／ (veloVxMv_,veloVyMv_,veloVzMv_)     |       ｜
    //    |                   自                                       |       自
    // ---+------------------------------------------               ---+---------------------------
    //    |                                                            |
    //
    // vVP が動きたい方向。vVPを求める！


    //自→的
    int vTx = tX - _X;
    int vTy = tY - _Y;
    int vTz = tZ - _Z;

    //自→仮自。上図の |仮自| = 5*vM
    int vVMx = _pKurokoB->_veloVxMv*5;
    int vVMy = _pKurokoB->_veloVyMv*5;
    int vVMz = _pKurokoB->_veloVzMv*5;

    //|仮自|
    int lVM = MAX3(ABS(vVMx), ABS(vVMy), ABS(vVMz)); //仮自ベクトル大きさ簡易版
    //|的|
    int lT =  MAX3(ABS(vTx), ABS(vTy), ABS(vTz)); //的ベクトル大きさ簡易版
    //|仮自|/|的|      vT の何倍が vVT 仮的 になるのかを求める。
    double r = (lVM*1.5) / lT;
    //* 2は 右上図のように一直線に並んだ際も、進行方向を維持するために、
    //|仮的| > |仮自| という関係を維持するためにかけた適当な割合

    //vVP 仮自→仮的 の加速度設定
    double accX = ((vTx * r) - vVMx) / r_max_acce_;
    double accY = ((vTy * r) - vVMy) / r_max_acce_;
    double accZ = ((vTz * r) - vVMz) / r_max_acce_;

    if (_pChip_front == NULL) {
        //先頭はやや速めに
        _pKurokoB->setVxMvAcce(accX+SGN(accX)*5); //SGN(accX)*5 を加算するのは、加速度を0にしないため
        _pKurokoB->setVyMvAcce(accY+SGN(accY)*5);
        _pKurokoB->setVzMvAcce(accZ+SGN(accZ)*5);
    } else {
        _pKurokoB->setVxMvAcce(accX+SGN(accX)*3); //SGN(accX)*3 を加算するのは、加速度を0にしないため
        _pKurokoB->setVyMvAcce(accY+SGN(accY)*3);
        _pKurokoB->setVzMvAcce(accZ+SGN(accZ)*3);
    }
    //ネジレ描画が汚くならないように回転を制限
    if (lVM > max_velo_renge_/2) {
        angle RZ_temp = _RZ;
        angle RY_temp = _RY;
        UTIL::getRzRyAng(vVMx, vVMy, vVMz,
                                RZ_temp, RY_temp);
        angle angDRZ = UTIL::getAngDiff(RZ_temp, _RZ);
        angle angDRY = UTIL::getAngDiff(RY_temp, _RY);
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
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();
    //ヒットエフェクト
    //無し

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //既にオプションはロックオン中
            if (pOther == pMainLockOnTarget) {
                //オプションのロックオンに見事命中した場合

                lockon_st_ = 2; //ロックオンをやめる。非ロックオン（ロックオン→非ロックオン）
                if (_pChip_front && _pChip_front->_pChip_front == NULL) {
                    //中間先頭チップがヒットした場合、先端にも伝える(先端は当たり判定ないため中間先頭と同値にする)
                    ((MyOptionWateringLaserChip001*)_pChip_front)->lockon_st_ = 2;
                }
            } else {
                //オプションのロックオン以外のアクターに命中した場合
            }
        } else {
            //オプション非ロックオン中に命中した場合
        }

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力

            //破壊されたエフェクト
            EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
            if (pExplo001) {
                pExplo001->locateWith(this);
            }
            //ロックオン可能アクターならロックオン
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrlr_->lockon(pOther);
            }
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            _pStatus->set(STAT_Stamina, default_stamina_);
            //ロックオン可能アクターならロックオン
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrlr_->lockon(pOther);
            }
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら

        //破壊されたエフェクト
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locateWith(this);
        }
        sayonara();
    }
}

void MyOptionWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
    lockon_st_ = 0;
}

MyOptionWateringLaserChip001::~MyOptionWateringLaserChip001() {
}

