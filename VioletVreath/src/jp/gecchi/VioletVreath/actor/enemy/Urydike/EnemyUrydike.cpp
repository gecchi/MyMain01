#include "EnemyUrydike.h"

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
#include "jp/gecchi/VioletVreath/actor/enemy/Urydike/FormationUrydike.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION ,
};
enum {
    PROG_INIT   ,
    PROG_ENTRY  ,
    PROG_MOVE_BEGIN ,
    PROG_CURVE ,
    PROG_SCATTER ,
    PROG_LEAVE ,
    PROG_BANPEI,
};

EnemyUrydike::EnemyUrydike(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Urydike", StatusReset(EnemyUrydike)) {
    _class_name = "EnemyUrydike";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    pVehicleLeader_ = nullptr; //フォーメーションオブジェクトが設定する
    scatter_flg_ = false;
    delay_ = 0;
}

void EnemyUrydike::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyUrydike::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    pVecVehicle->linkFaceAngByMvAng(true);
}

void EnemyUrydike::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyUrydike::processBehavior() {
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pProg->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
                pVecVehicle->setRollFaceAngVelo(D_ANG(3));
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                pAlphaFader->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pProg->hasArrivedAt(frame_of_entering)) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }
        case PROG_MOVE_BEGIN: {
            if (pProg->hasJustChanged()) {

            }
            if (pProg->hasArrivedAt(120)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_CURVE: {
            if (pProg->hasJustChanged()) {
                getVecVehicle()->setMvAcce(0); //加速度がある場合は切っておく
                pVehicleLeader_->start(RELATIVE_COORD_DIRECTION, 1);
            }
            pVehicleLeader_->behave(); //カーブ移動するようにDriverを操作

            if (scatter_flg_) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_SCATTER: {
            if (pProg->hasJustChanged()) {
                delay_ = RND(0, 120);
            }
            if (pProg->hasArrivedAt(delay_)) {
                //散り散りになる
                pVehicleLeader_->stop();
                pVecVehicle->turnRzRyMvAngTo(RND_ABOUT(pVecVehicle->_rz_mv, D_ANG(90)), RND_ABOUT(pVecVehicle->_ry_mv, D_ANG(90)),
                                         D_ANG(2), 0, TURN_CLOSE_TO,false);
                pVecVehicle->setMvAcce(100);
            }

            if (pProg->hasArrivedAt(delay_ + 200)) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_LEAVE: {
            if (pProg->hasJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAlphaFader->transitionLinearUntil(0.0, 30);
            }
            if (pProg->hasArrivedAt(60)) {
                sayonara();
                pProg->changeNothing(); //おしまい！
            }
            break;
        }
        default :
            break;
    }

    pAlphaFader->behave();
    pVecVehicle->behave();
}

void EnemyUrydike::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyUrydike::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
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
