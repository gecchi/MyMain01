#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "MyStraightLaserChip001", STATUS(MyStraightLaserChip001)) {
    _class_name = "MyStraightLaserChip001";
    default_stamina_ = _pStatus->get(STAT_Stamina);
    _veloMv = 100000;
    pOrg_ = NULL;
    lockon_st_ = 0;
}

void MyStraightLaserChip001::initialize() {
    pOrg_ = P_MYSHIP;
    _pKurokoA->setRzRyMvAng(0,0);
    registHitAreaCube(60000);
    setHitAble(true);
    _SX = _SY = _SZ = R_SC(5);
    _alpha = 0.99;
    _bounding_sphere_radius = 20.0;
}

void MyStraightLaserChip001::onActive() {
    _pStatus->reset();
    default_stamina_ = _pStatus->get(STAT_Stamina);
    StraightLaserChip::onActive();

    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrlr_->pRingTarget_->getCurrent();
    _pKurokoA->setMvVelo(80000);
    _pKurokoA->setMvAcce(1000);
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (_pChip_front == NULL) {
            //先端チップ
            lockon_st_ = 1;
        } else {
            //先端以外
            lockon_st_ = ((MyStraightLaserChip001*) _pChip_front)->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (_pChip_front == NULL) {
            //先端チップ
            lockon_st_ = 0;
        } else {
            //先端以外
            lockon_st_ = ((MyStraightLaserChip001*) _pChip_front)->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    }
}

void MyStraightLaserChip001::processBehavior() {
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
    if (_pChip_front == NULL) {
        _pSeTx->behave();
    }
    StraightLaserChip::processBehavior();//座標を移動させてから呼び出すこと
    //根元からレーザー表示のため強制的に座標補正
    if (onChangeToActive()) {
        locateWith(pOrg_);
    }
}

void MyStraightLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void MyStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
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
                    ((MyStraightLaserChip001*)_pChip_front)->lockon_st_ = 2;
                }
            } else {
                //オプションのロックオン以外のアクターに命中した場合
            }
        } else {
            //オプション非ロックオン中に命中した場合
        }
        //ロックオン可能アクターならロックオンを試みる
        if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
            pOrg_->pLockonCtrlr_->lockon(pOther);
        }

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力
            setHitAble(false);
            UTIL::activateExplosionEffectOf(this); //破壊されたエフェクト
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            _pStatus->set(STAT_Stamina, default_stamina_);
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this); //破壊されたエフェクト
        sayonara();
    }

}

void MyStraightLaserChip001::onInactive() {
    StraightLaserChip::onInactive();
    lockon_st_ = 0;
}

MyStraightLaserChip001::~MyStraightLaserChip001() {
}

