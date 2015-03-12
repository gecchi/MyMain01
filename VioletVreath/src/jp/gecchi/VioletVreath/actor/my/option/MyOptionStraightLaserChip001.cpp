#include "MyOptionStraightLaserChip001.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyOptionStraightLaserChip001::MyOptionStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "MyOptionStraightLaserChip001", STATUS(MyOptionStraightLaserChip001)) {
    _class_name = "MyOptionStraightLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    _velo_mv = 100000;

    pOrg_ = nullptr;
    lockon_st_ = 0;
    is_lockon_ = false;
}

void MyOptionStraightLaserChip001::initialize() {
    getKuroko()->setRzRyMvAng(0,0);
    registerHitAreaCube_AutoGenMidColli(60000);
    setHitAble(true);
    setScaleR(5.0);
    setAlpha(0.99);
}

void MyOptionStraightLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    StraightLaserChip::onActive();

    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setMvVelo(80000);
    pKuroko->setMvAcce(300);
    is_lockon_ = false;
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (getFrontChip() == nullptr) {
            //先端チップ
            lockon_st_ = 1;
            is_lockon_ = true;
        } else {
            //先端以外
            lockon_st_ = ((MyOptionStraightLaserChip001*) getFrontChip())->lockon_st_;//一つ前のロックオン情報を引き継ぐ
            is_lockon_ = ((MyOptionStraightLaserChip001*) getFrontChip())->is_lockon_;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (getFrontChip() == nullptr) {
            //先端チップ
            lockon_st_ = 0;
        } else {
            //先端以外
            lockon_st_ = ((MyOptionStraightLaserChip001*) getFrontChip())->lockon_st_;//一つ前のロックオン情報を引き継ぐ
            is_lockon_ = ((MyOptionStraightLaserChip001*) getFrontChip())->is_lockon_;//一つ前のロックオン情報を引き継ぐ
        }
    }
}

void MyOptionStraightLaserChip001::processBehavior() {
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    if (lockon_st_ == 1) {
        if (getActiveFrame() < 120) {
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
//            if (getFrontChip() == nullptr) {
//            }
        }
//        if (getFrontChip() == nullptr) {
//        } else if (getFrontChip()->getFrontChip() == nullptr) {
//        } else if (getFrontChip()->getFrontChip()->getFrontChip() == nullptr) {
//        } else if (getFrontChip()->getFrontChip()->getFrontChip()->getFrontChip() == nullptr) {
//        } else {
//        }
    }
    if (getFrontChip() == nullptr) {
        getSeTx()->behave();
    }
    StraightLaserChip::processBehavior();//座標を移動させてから呼び出すこと
    //根元からレーザー表示のため強敵に座標補正
    //根元からレーザー表示のため強制的に座標補正
    if (onChangeToActive()) {
        positionAs(pOrg_);
//        _tmpX = _x;
//        _tmpY = _y;
//        _tmpZ = _z;
    }
}

void MyOptionStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    //ヒットエフェクト
    //無し

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //既にオプションはロックオン中
            if (pOther == pMainLockOnTarget) {
                //オプションのロックオンに見事命中した場合

                lockon_st_ = 2; //ロックオンをやめる。非ロックオン（ロックオン→非ロックオン）
                if (getFrontChip() && getFrontChip()->getFrontChip() == nullptr) {
                    //中間先頭チップがヒットした場合、先端にも伝える
                    ((MyOptionStraightLaserChip001*)getFrontChip())->lockon_st_ = 2;
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
            EffectExplosion001* pExplo001 = dispatchFromCommon(EffectExplosion001);
            if (pExplo001) {
                pExplo001->positionAs(this);
            }
            //ロックオン可能アクターならロックオン
            if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            getStatus()->set(STAT_Stamina, default_stamina_);
            //ロックオン可能アクターならロックオン
            if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら

        //破壊されたエフェクト
        EffectExplosion001* pExplo001 = dispatchFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->positionAs(this);
        }
        sayonara();
    }
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//
//
//    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
//        int stamina = UTIL::calcMyStamina(this, pOther);
//        if (stamina <= 0) {
//            //一撃でチップ消滅の攻撃力
//
//            //破壊されたエフェクト
//            EffectExplosion001* pExplo001 = dispatchFromCommon(EffectExplosion001);
//            if (pExplo001) {
//                pExplo001->positionAs(this);
//                pExplo001->activate();
//            }
//            sayonara();
//        } else {
//            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
//            getStatus()->set(STAT_Stamina, default_stamina_);
//        }
//    } else if (pOther->getKind() & KIND_CHIKEI) {
//        //地形相手は無条件さようなら
//        //破壊されたエフェクト
//        EffectExplosion001* pExplo001 = dispatchFromCommon(EffectExplosion001);
//        if (pExplo001) {
//            pExplo001->positionAs(this);
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

