#include "MyStraightLaserChip001.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"


using namespace GgafLib;
using namespace VioletVreath;


GgafDx::Model* MyStraightLaserChip001::pModel_  = nullptr;
int MyStraightLaserChip001::tex_no_ = 0;

MyStraightLaserChip001::MyStraightLaserChip001(const char* prm_name) :
        VvMyActor<StraightLaserChip>(prm_name, "MyLaserChip001", StatusReset(MyStraightLaserChip001)) {
    _class_name = "MyStraightLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    setMvVelo(PX_C(300));
    pOrg_ = nullptr;
    GgafDx::Model* pModel = getModel();
    if (!MyStraightLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwCriticalException("MyStraightLaserChip001モデルは、テクスチャ（マテリアル）が"<<MAX_LASER_LEVEL<<"つ必要です。");
        }
        MyStraightLaserChip001::pModel_ = pModel;
    }
}

void MyStraightLaserChip001::initialize() {
    pOrg_ = pMYSHIP;
    getLocoVehicle()->setRzRyMvAng(0,0);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAABox_WHD(0,PX_C(300),PX_C(80),PX_C(80));

    setHitAble(true);
    setScaleR(5.0);
    setCullingDraw(false);
}

void MyStraightLaserChip001::onCreateModel() {
}


void MyStraightLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    StraightLaserChip::onActive();

    getLocoVehicle()->setMvVelo(100000);
    getLocoVehicle()->setMvAcce(1000);
}

void MyStraightLaserChip001::processBehavior() {
    frame active_frames = getActiveFrame();
    double power = active_frames <= 300 ? UTIL::SHOT_POWER[active_frames] : UTIL::SHOT_POWER[300];
    getStatus()->set(STAT_AttackPowerRate, power);
    _power = power;

    if (getInfrontChip() == nullptr) {
        getSeTransmitter()->behave();
    }
    StraightLaserChip::processBehavior();//座標を移動させてから呼び出すこと
    //根元からレーザー表示のため強制的に座標補正
    if (hasJustChangedToActive()) {
        setPositionAt(pOrg_);
    }
}

void MyStraightLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MyStraightLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*) prm_pOtherActor;
    //ヒットエフェクト
    UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現

    if ((pOther->lookUpKind() & KIND_ENEMY_BODY) ) {
        //ロックオン可能アクターならロックオンを試みる
        if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
            pOrg_->pLockonCtrler_->lockon(pOther);
        }
        const int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力
            getStatus()->set(STAT_Stamina, default_stamina_);
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            getStatus()->set(STAT_Stamina, default_stamina_);
        }
    } else if (pOther->lookUpKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら
        sayonara();
    }
}

void MyStraightLaserChip001::onInactive() {
    StraightLaserChip::onInactive();
}

void MyStraightLaserChip001::chengeTex(int prm_tex_no) {
    if (MyStraightLaserChip001::pModel_) {
        MyStraightLaserChip001::tex_no_ = prm_tex_no;
        MyStraightLaserChip001::pModel_->setDefaultTextureMaterialNo(prm_tex_no);
    }
}

MyStraightLaserChip001::~MyStraightLaserChip001() {
    MyStraightLaserChip001::pModel_ = nullptr;
}


