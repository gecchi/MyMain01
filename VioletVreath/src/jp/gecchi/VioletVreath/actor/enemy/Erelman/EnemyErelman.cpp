#include "EnemyErelman.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/FormationErelman.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
#include "FormationErelman.h"

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

EnemyErelman::EnemyErelman(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Erelman", StatusReset(EnemyErelman)) {
    _class_name = "EnemyErelman";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    pVehicleLeader_ = nullptr; //フォーメーションオブジェクトが設定する
    scatter_flg_ = false;
    delay_ = 0;
    free_interval_ = 0;
}

void EnemyErelman::onCreateModel() {
    getModel()->setSpecular(5.0, 0.5);
}

void EnemyErelman::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
//    pVecVehicle->linkFaceAngByMvAng(true);
    pVecVehicle->forceMvVeloRange(PX_C(15));
}

void EnemyErelman::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyErelman::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->get()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
//            pVecVehicle->setRollFaceAngVelo(D_ANG(3));
            setRyFaceAng(D_ANG(90));
            pVecVehicle->setRzFaceAngVelo(D_ANG(3));
            pPhase->changeNext();
            break;
        }
        case PHASE_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pPhase->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
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
                getVecVehicle()->setMvAcce(0); //加速度がある場合は切っておく
                pVehicleLeader_->start(RELATIVE_COORD_DIRECTION, -1); //-1は無限ループ
            }
            if (free_interval_ == 0) {
                FormationErelman* pFormation = (FormationErelman*)getFormation();
                pVehicleLeader_->setStartPosition(pFormation->geo_.x, pFormation->geo_.y, pFormation->geo_.z);
                pVehicleLeader_->setStartAngle(pFormation->geo_.rx, pFormation->geo_.ry, pFormation->geo_.rz);
                pVehicleLeader_->behave(); //カーブ移動するようにDriverを操作
            } else {
                free_interval_--;
            }
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
                pVecVehicle->turnRzRyMvAngTo(RND_ABOUT(pVecVehicle->_rz_mv, D_ANG(90)), RND_ABOUT(pVecVehicle->_ry_mv, D_ANG(90)),
                                         D_ANG(2), 0, TURN_CLOSE_TO,false);
                pVecVehicle->setMvAcce(100);
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
    pVecVehicle->behave();
}

void EnemyErelman::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyErelman::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyErelman::onInactive() {
    if (getBehaveingFrame() > 10) {
        //EnemyErelmanCoreに管理されている。初めはInactive()であるため。
        sayonara();
    }
}
void EnemyErelman::scatter() {
    //Formationから指示がある。
    scatter_flg_ = true;
}

EnemyErelman::~EnemyErelman() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
