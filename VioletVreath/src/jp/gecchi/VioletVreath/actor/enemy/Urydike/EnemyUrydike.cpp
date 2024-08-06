#include "EnemyUrydike.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/FormationUrydike.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION ,
};
enum {
    PHASE_INIT   ,
    PHASE_ENTRY  ,
    PHASE_MOVE_BEGIN ,
    PHASE_CURVE ,
    PHASE_SCATTER ,
    PHASE_LEAVE ,
    PHASE_BANPEI,
};

EnemyUrydike::EnemyUrydike(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Urydike", StatusReset(EnemyUrydike)) {
    _class_name = "EnemyUrydike";
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    pVehicleLeader_ = nullptr; //フォーメーションオブジェクトが設定する
    scatter_flg_ = false;
    delay_ = 0;
}

void EnemyUrydike::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyUrydike::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
}

void EnemyUrydike::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyUrydike::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
            pPhase->changeNext();
            break;
        }
        case PHASE_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pPhase->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
                pLocusVehicle->setRollFaceAngVelo(D_ANG(3));
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pPhase->hasArrivedFrameAt(frame_of_summons_begin)) {
                pAlphaFader->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                setHitAble(true);
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_MOVE_BEGIN: {
            if (pPhase->hasJustChanged()) {

            }
            if (pPhase->hasArrivedFrameAt(120)) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_CURVE: {
            if (pPhase->hasJustChanged()) {
                getLocusVehicle()->setMvAcce(0); //加速度がある場合は切っておく
                pVehicleLeader_->start(RELATIVE_COORD_DIRECTION, 1);
            }
            pVehicleLeader_->behave(); //カーブ移動するようにDriverを操作

            if (scatter_flg_) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_SCATTER: {
            if (pPhase->hasJustChanged()) {
                delay_ = RND(0, 120);
            }
            if (pPhase->hasArrivedFrameAt(delay_)) {
                //散り散りになる
                pVehicleLeader_->stop();
                pLocusVehicle->turnRzRyMvAngTo(RND_ABOUT(pLocusVehicle->_rz_mv, D_ANG(90)), RND_ABOUT(pLocusVehicle->_ry_mv, D_ANG(90)),
                                         D_ANG(2), 0, TURN_CLOSE_TO,false);
                pLocusVehicle->setMvAcce(100);
            }

            if (pPhase->hasArrivedFrameAt(delay_ + 200)) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_LEAVE: {
            if (pPhase->hasJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAlphaFader->transitionLinearUntil(0.0, 30);
            }
            if (pPhase->hasArrivedFrameAt(60)) {
                sayonara();
                pPhase->changeNothing(); //おしまい！
            }
            break;
        }
        default :
            break;
    }

    pAlphaFader->behave();
    pLocusVehicle->behave();
}

void EnemyUrydike::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyUrydike::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        getSeXmtr()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyUrydike::onInactive() {
    if (getBehaveingFrame() > 10) {
        //EnemyUrydikeCoreに管理されている。初めはInactive()であるため。
        sayonara();
    }
}

void EnemyUrydike::scatter() {
    //Formationから指示がある。
    scatter_flg_ = true;
}

EnemyUrydike::~EnemyUrydike() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
