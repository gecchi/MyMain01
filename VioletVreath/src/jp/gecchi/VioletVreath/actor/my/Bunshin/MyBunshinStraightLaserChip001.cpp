#include "MyBunshinStraightLaserChip001.h"

#include "MyBunshin.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
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
const velo MyBunshinStraightLaserChip001::MAX_VELO = PX_C(1024);

MyBunshinStraightLaserChip001::MyBunshinStraightLaserChip001(const char* prm_name) :
        VvMyActor<StraightLaserChip>(prm_name, "MyLaserChip001", StatusReset(MyBunshinStraightLaserChip001)) {
    _class_name = "MyBunshinStraightLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    setMvVelo(MAX_VELO*N_DISPATCH_AT_ONCE);
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
    registerHitAreaCube_AutoGenMidColli(MAX_VELO/4, PX_C(40)); //PX_C(40) は自機と同じ大きさ

    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    WorldCollisionChecker* pExChecker = (WorldCollisionChecker*)pChecker->_pNextExChecker;
    pExChecker->_kind = KIND_CHECK_CHIKEI_HIT;

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
}

void MyBunshinStraightLaserChip001::processBehavior() {
    frame active_frames = getActiveFrame();
    double power = active_frames <= 300 ? UTIL::SHOT_POWER[active_frames] : UTIL::SHOT_POWER[300];
    getStatus()->set(STAT_AttackPowerRate, power);
    _power = power;

    if (getInfrontChip() == nullptr) {
        getSeXmtr()->behave();
    }
    StraightLaserChip::processBehavior();//座標を移動させてから呼び出すこと
}
void MyBunshinStraightLaserChip001::processSettlementBehavior() {
    if (hasJustChangedToActive()) {
        setMvVelo(MAX_VELO*_n_dispatch_at_once); //初速はここで
        //根元からレーザー表示のため強制的に座標補正
        int n = _n_dispatch_at_once-1 - _dispatch_index;
        if (n == 0) {
            setPositionAt(pOrg_);
        } else {
            double vx, vy, vz;
            UTIL::convRzRyToVector(pOrg_->_rz, pOrg_->_ry,
                                    vx, vy, vz);
//            coord velo_mv = getMvVelo();
//            setPosition(pOrg_->_x + (vx*(velo_mv/_n_dispatch_at_once)*n) ,
//                        pOrg_->_y + (vy*(velo_mv/_n_dispatch_at_once)*n) ,
//                        pOrg_->_z + (vz*(velo_mv/_n_dispatch_at_once)*n) );
            velo v = (getMvVelo()*n) /_n_dispatch_at_once;
            setPosition(pOrg_->_x + (vx*v) ,
                        pOrg_->_y + (vy*v) ,
                        pOrg_->_z + (vz*v) );
        }
        MyBunshinStraightLaserChip001* pF = (MyBunshinStraightLaserChip001*)getInfrontChip();
        MyBunshinStraightLaserChip001* pB = (MyBunshinStraightLaserChip001*)getBehindChip();
        if (pF == nullptr) {
            //先端チップ
        } else {
            //ひねってみよう
            //setRxFaceAng(pF->_rx + D_ANG(45));
        }
    }
    VvMyActor<StraightLaserChip>::processSettlementBehavior();
}
void MyBunshinStraightLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MyBunshinStraightLaserChip001::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)(prm_pOppHitChecker->_pActor);
    //ヒットエフェクト
    GgafDx::FigureActor* pE = UTIL::activateCommonEffectOf(this, STAT_ExplosionEffectKind); //爆発エフェクト出現

    if ((prm_pOppHitChecker->_kind & KIND_ENEMY_BODY) ) {
        //ロックオン可能アクターならロックオン
        if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
            pOrg_->pLockonCtrler_->lockon(pOther);
        }

        int stamina = calcStamina(pOther);
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力
            getStatus()->set(STAT_Stamina, default_stamina_);
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            getStatus()->set(STAT_Stamina, default_stamina_);
        }

    } else if ((prm_pThisHitChecker->_kind & KIND_CHECK_CHIKEI_HIT) && (prm_pOppHitChecker->_kind & KIND_CHIKEI)) {
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


