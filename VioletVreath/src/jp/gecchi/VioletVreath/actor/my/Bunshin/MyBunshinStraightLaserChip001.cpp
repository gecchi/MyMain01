#include "MyBunshinStraightLaserChip001.h"

#include "MyBunshin.h"

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


GgafDx::Model* MyBunshinStraightLaserChip001::pModel_  = nullptr;
int MyBunshinStraightLaserChip001::tex_no_ = 0;

MyBunshinStraightLaserChip001::MyBunshinStraightLaserChip001(const char* prm_name) :
        VvMyActor<StraightLaserChip>(prm_name, "MyLaserChip001", StatusReset(MyBunshinStraightLaserChip001)) {
    _class_name = "MyBunshinStraightLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    setMvVelo(PX_C(300));
    pOrg_ = nullptr;
    pLockonCursor_ = nullptr;
    GgafDx::Model* pModel = getModel();
    if (!MyBunshinStraightLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwCriticalException("MyBunshinStraightLaserChip001モデルは、テクスチャ（マテリアル）が"<<MAX_LASER_LEVEL<<"つ必要です。");
        }
        MyBunshinStraightLaserChip001::pModel_ = pModel;
    }
}

void MyBunshinStraightLaserChip001::initialize() {
    registerHitAreaCube_AutoGenMidColli(getMvVelo()/4);
    setHitAble(true);
    setScaleR(6.0);
    setCullingDraw(false);
}

void MyBunshinStraightLaserChip001::setOrg(MyBunshin* prm_pOrg) {
    pOrg_ = prm_pOrg;
    pLockonCursor_ = pOrg_->pLockonCtrler_->pMainLockonCursor_;
}

void MyBunshinStraightLaserChip001::onCreateModel() {
}


void MyBunshinStraightLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    StraightLaserChip::onActive();
    setMvVelo(PX_C(300));
}

void MyBunshinStraightLaserChip001::processBehavior() {
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
void MyBunshinStraightLaserChip001::processSettlementBehavior() {
    MyBunshinStraightLaserChip001* pF = (MyBunshinStraightLaserChip001*) getInfrontChip();
    if (pF == nullptr) {
        //先端チップ
    } else {
        //ひねってみよう
        setRxFaceAng(pF->_rx + D_ANG(45));
    }
    VvMyActor<StraightLaserChip>::processSettlementBehavior();
}
void MyBunshinStraightLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MyBunshinStraightLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*) prm_pOtherActor;
    //ヒットエフェクト
    GgafDx::FigureActor* pE = UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現
    GgafDx::CollisionPart* pColliPart = getWorldCollisionChecker()->getLastHitCollisionPart();
    pE->setPosition(pE->_x + pColliPart->_cx, pE->_y + pColliPart->_cy, pE->_z + pColliPart->_cz); //爆発エフェクト位置を補正

    if ((pOther->lookUpKind() & KIND_ENEMY_BODY) ) {
        //ロックオン可能アクターならロックオン
        if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
            pOrg_->pLockonCtrler_->lockon(pOther);
        }

        int stamina = UTIL::calcMyStamina(this, pOther);
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

void MyBunshinStraightLaserChip001::onInactive() {
    StraightLaserChip::onInactive();
}

void MyBunshinStraightLaserChip001::chengeTex(int prm_tex_no) {
    if (MyBunshinStraightLaserChip001::pModel_) {
        MyBunshinStraightLaserChip001::tex_no_ = prm_tex_no;
        MyBunshinStraightLaserChip001::pModel_->setDefaultTextureMaterialNo(prm_tex_no);
    }
}

MyBunshinStraightLaserChip001::~MyBunshinStraightLaserChip001() {
    MyBunshinStraightLaserChip001::pModel_ = nullptr;
}


