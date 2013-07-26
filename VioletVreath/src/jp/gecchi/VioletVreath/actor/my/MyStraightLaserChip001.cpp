#include "stdafx.h"
#include "MyStraightLaserChip001.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


GgafDxCore::GgafDxModel* MyStraightLaserChip001::pModel_  = nullptr;
char MyStraightLaserChip001::aaTextureName[3][51];
int MyStraightLaserChip001::tex_no_ = 0;


MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "MyStraightLaserChip001", STATUS(MyStraightLaserChip001)) {
    _class_name = "MyStraightLaserChip001";
    default_stamina_ = _pStatus->get(STAT_Stamina);
    _veloMv = 100000;
    pOrg_ = nullptr;
    lockon_st_ = 0;
}

void MyStraightLaserChip001::initialize() {
    pOrg_ = P_MYSHIP;
    _pKurokoA->setRzRyMvAng(0,0);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_WHD(0,120000,60000,60000);

    setHitAble(true);
    _SX = _SY = _SZ = R_SC(5);
    _alpha = 0.99;
    _bounding_sphere_radius = 20.0;
}

void MyStraightLaserChip001::onCreateModel() {
    if (_pModel->_num_materials != 3) {
        throwGgafCriticalException("MyStraightLaserChip001::onCreateModel() MyStraightLaserChip001モデルは、マテリアが３つ必要です。");
    }
    pModel_ = _pModel;
    for (DWORD i = 0; i < _pModel->_num_materials; i ++) {
        strcpy(aaTextureName[i], _pModel->_papTextureConnection[i]->peek()->getName());
    }
}


void MyStraightLaserChip001::onActive() {
    _pStatus->reset();
    default_stamina_ = _pStatus->get(STAT_Stamina);
    StraightLaserChip::onActive();

    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    _pKurokoA->setMvVelo(80000);
    _pKurokoA->setMvAcce(1000);
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (_pChip_front == nullptr) {
            //先端チップ
            lockon_st_ = 1;
        } else {
            //先端以外
            lockon_st_ = ((MyStraightLaserChip001*) _pChip_front)->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (_pChip_front == nullptr) {
            //先端チップ
            lockon_st_ = 0;
        } else {
            //先端以外
            lockon_st_ = ((MyStraightLaserChip001*) _pChip_front)->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    }
}

void MyStraightLaserChip001::processBehavior() {
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
    if (_pChip_front == nullptr) {
        _pSeTx->behave();
    }
    StraightLaserChip::processBehavior();//座標を移動させてから呼び出すこと
    //根元からレーザー表示のため強制的に座標補正
    if (onChangeToActive()) {
        positionAs(pOrg_);
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
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    //ヒットエフェクト
    //無し
    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //既にオプションはロックオン中
            if (pOther == pMainLockOnTarget) {
                //オプションのロックオンに見事命中した場合
                lockon_st_ = 2; //ロックオンをやめる。非ロックオン（ロックオン→非ロックオン）
                if (_pChip_front && _pChip_front->_pChip_front == nullptr) {
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
            pOrg_->pLockonCtrler_->lockon(pOther);
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

void MyStraightLaserChip001::chengeTex(int prm_tex_no) {
    if (pModel_) {
        MyStraightLaserChip001::tex_no_ = prm_tex_no;
        pModel_->swapTopTextureOrder(aaTextureName[prm_tex_no]);
    }
}

MyStraightLaserChip001::~MyStraightLaserChip001() {
}


