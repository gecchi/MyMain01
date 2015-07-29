#include "MyStraightLaserChip001.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


GgafDxCore::GgafDxModel* MyStraightLaserChip001::pModel_  = nullptr;
char MyStraightLaserChip001::aaTextureName[MAX_LASER_LEVEL][51];
int MyStraightLaserChip001::tex_no_ = 0;


MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "MyStraightLaserChip001", STATUS(MyStraightLaserChip001)) {
    _class_name = "MyStraightLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    _velo_mv = 100000;
    pOrg_ = nullptr;
    lockon_st_ = 0;
    GgafDxModel* pModel = getModel();
    if (!MyStraightLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwGgafCriticalException("MyStraightLaserChip001::onCreateModel() MyStraightLaserChip001モデルは、テクスチャ（マテリアル）が"<<MAX_LASER_LEVEL<<"つ必要です。");
        }
        for (DWORD i = 0; i < pModel->_num_materials; i ++) {
            strcpy(MyStraightLaserChip001::aaTextureName[i], pModel->_papTextureConnection[i]->peek()->getName());
        }
        MyStraightLaserChip001::pModel_ = pModel;
    }
}

void MyStraightLaserChip001::initialize() {
    pOrg_ = P_MYSHIP;
    getKuroko()->setRzRyMvAng(0,0);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_WHD(0,120000,60000,60000);

    setHitAble(true);
    setScaleR(5.0);
    setAlpha(0.99);
}

void MyStraightLaserChip001::onCreateModel() {
}


void MyStraightLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    StraightLaserChip::onActive();

    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    getKuroko()->setMvVelo(80000);
    getKuroko()->setMvAcce(1000);
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (getInfrontChip() == nullptr) {
            //先端チップ
            lockon_st_ = 1;
        } else {
            //先端以外
            lockon_st_ = ((MyStraightLaserChip001*)getInfrontChip())->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (getInfrontChip() == nullptr) {
            //先端チップ
            lockon_st_ = 0;
        } else {
            //先端以外
            lockon_st_ = ((MyStraightLaserChip001*)getInfrontChip())->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    }
}

void MyStraightLaserChip001::processBehavior() {
    const GgafDxGeometricActor* const pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();

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
    if (getInfrontChip() == nullptr) {
        getSeTx()->behave();
    }
    StraightLaserChip::processBehavior();//座標を移動させてから呼び出すこと
    //根元からレーザー表示のため強制的に座標補正
    if (hasJustChangedToActive()) {
        positionAs(pOrg_);
    }
}

void MyStraightLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    //ヒットエフェクト
    //無し
    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //既にオプションはロックオン中
            if (pOther == pMainLockOnTarget) {
                //オプションのロックオンに見事命中した場合
                lockon_st_ = 2; //ロックオンをやめる。非ロックオン（ロックオン→非ロックオン）
                if (getInfrontChip() && getInfrontChip()->getInfrontChip() == nullptr) {
                    //中間先頭チップがヒットした場合、先端にも伝える
                    ((MyStraightLaserChip001*)getInfrontChip())->lockon_st_ = 2;
                }
            } else {
                //オプションのロックオン以外のアクターに命中した場合
            }
        } else {
            //オプション非ロックオン中に命中した場合
        }
        //ロックオン可能アクターならロックオンを試みる
        if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
            pOrg_->pLockonCtrler_->lockon(pOther);
        }

        const int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力
            setHitAble(false);
            UTIL::activateExplosionEffectOf(this); //破壊されたエフェクト
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            getStatus()->set(STAT_Stamina, default_stamina_);
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
    if (MyStraightLaserChip001::pModel_) {
        MyStraightLaserChip001::tex_no_ = prm_tex_no;
        MyStraightLaserChip001::pModel_->swapTopTextureOrder(aaTextureName[prm_tex_no]);
    }
}

MyStraightLaserChip001::~MyStraightLaserChip001() {
    MyStraightLaserChip001::pModel_ = nullptr;
}


