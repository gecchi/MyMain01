#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MyOptionStraightLaserChip001::MyOptionStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "MyOptionStraightLaserChip001", STATUS(MyOptionStraightLaserChip001)) {
    _class_name = "MyOptionStraightLaserChip001";
    default_stamina_ = _pStatus->get(STAT_Stamina);
    _veloMv = 100000;
    
    pOrg_ = NULL;
    lockon_st_ = 0;
    is_lockon_ = false;
}

void MyOptionStraightLaserChip001::initialize() {
    _pKurokoA->setRzRyMvAng(0,0);
    registHitAreaCube(60000);
    setHitAble(true);
    _SX = _SY = _SZ = R_SC(5);
    _alpha = 0.99;
    _bounding_sphere_radius = 20.0;


}
void MyOptionStraightLaserChip001::onActive() {
    _pStatus->reset();
    default_stamina_ = _pStatus->get(STAT_Stamina);
    StraightLaserChip::onActive();

    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();
    _pKurokoA->setMvVelo(80000);
    _pKurokoA->setMvAcce(300);
    is_lockon_ = false;
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (_pChip_front == NULL) {
            //先端チップ
            lockon_st_ = 1;
            is_lockon_ = true;
        } else {
            //先端以外
            lockon_st_ = ((MyOptionStraightLaserChip001*) _pChip_front)->lockon_st_;//一つ前のロックオン情報を引き継ぐ
            is_lockon_ = ((MyOptionStraightLaserChip001*) _pChip_front)->is_lockon_;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (_pChip_front == NULL) {
            //先端チップ
            lockon_st_ = 0;
        } else {
            //先端以外
            lockon_st_ = ((MyOptionStraightLaserChip001*) _pChip_front)->lockon_st_;//一つ前のロックオン情報を引き継ぐ
            is_lockon_ = ((MyOptionStraightLaserChip001*) _pChip_front)->is_lockon_;//一つ前のロックオン情報を引き継ぐ
        }
    }

}



void MyOptionStraightLaserChip001::processBehavior() {
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();


    if (lockon_st_ == 1) {
        if (getActivePartFrame() < 120) {
            if (pMainLockOnTarget) {
            } else {
                lockon_st_ = 2;
            }
        } else {
            lockon_st_ = 2;
        }
    }
    if (lockon_st_ == 2) {
        if (is_lockon_) {
            is_lockon_ = false;
//            if (_pChip_front == NULL) {
//            }
        }
//        if (_pChip_front == NULL) {
//        } else if (_pChip_front->_pChip_front == NULL) {
//        } else if (_pChip_front->_pChip_front->_pChip_front == NULL) {
//        } else if (_pChip_front->_pChip_front->_pChip_front->_pChip_front == NULL) {
//        } else {
//        }
    }
    if (_pChip_front == NULL) {
        _pSeTx->behave();
    }
    StraightLaserChip::processBehavior();//座標を移動させてから呼び出すこと
    //根元からレーザー表示のため強敵に座標補正
    //根元からレーザー表示のため強制的に座標補正
    if (onChangeToActive()) {
        locatedBy(pOrg_);
//        _tmpX = _X;
//        _tmpY = _Y;
//        _tmpZ = _Z;
    }
}



void MyOptionStraightLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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




void MyOptionStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
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
                    //中間先頭チップがヒットした場合、先端にも伝える
                    ((MyOptionStraightLaserChip001*)_pChip_front)->lockon_st_ = 2;
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
            EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
            if (pExplo001) {
                pExplo001->locatedBy(this);
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
            pExplo001->locatedBy(this);
        }
        sayonara();
    }
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//
//
//    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
//        int stamina = MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind());
//        if (stamina <= 0) {
//            //一撃でチップ消滅の攻撃力
//
//            //破壊されたエフェクト
//            EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
//            if (pExplo001) {
//                pExplo001->locatedBy(this);
//                pExplo001->activate();
//            }
//            sayonara();
//        } else {
//            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
//            _pStatus->set(STAT_Stamina, default_stamina_);
//        }
//    } else if (pOther->getKind() & KIND_CHIKEI) {
//        //地形相手は無条件さようなら
//        //破壊されたエフェクト
//        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
//        if (pExplo001) {
//            pExplo001->locatedBy(this);
//        }
//        sayonara();
//    }

}
void MyOptionStraightLaserChip001::onInactive() {
    StraightLaserChip::onInactive();
    lockon_st_ = 0;
}

MyOptionStraightLaserChip001::~MyOptionStraightLaserChip001() {
}

