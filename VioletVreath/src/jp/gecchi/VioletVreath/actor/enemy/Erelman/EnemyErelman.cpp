#include "EnemyErelman.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
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
    PROG_INIT   ,
    PROG_ENTRY  ,
    PROG_MOVE_BEGIN ,
    PROG_CURVE ,
    PROG_SCATTER ,
    PROG_LEAVE ,
    PROG_BANPEI,
};

EnemyErelman::EnemyErelman(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Erelman", StatusReset(EnemyErelman)) {
    _class_name = "EnemyErelman";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    pDriverLeader_ = nullptr; //フォーメーションオブジェクトが設定する
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
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
//    pVecDriver->linkFaceAngByMvAng(true);
    pVecDriver->forceMvVeloRange(PX_C(15));
}

void EnemyErelman::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyErelman::processBehavior() {
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
//            pVecDriver->setRollFaceAngVelo(D_ANG(3));
            setRyFaceAng(D_ANG(90));
            pVecDriver->setRzFaceAngVelo(D_ANG(3));
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pProg->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
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
                getVecDriver()->setMvAcce(0); //加速度がある場合は切っておく
                pDriverLeader_->start(RELATIVE_COORD_DIRECTION, -1); //-1は無限ループ
            }
            if (free_interval_ == 0) {
                FormationErelman* pFormation = (FormationErelman*)getFormation();
                pDriverLeader_->setStartPosition(pFormation->geo_.x, pFormation->geo_.y, pFormation->geo_.z);
                pDriverLeader_->setStartAngle(pFormation->geo_.rx, pFormation->geo_.ry, pFormation->geo_.rz);
                pDriverLeader_->behave(); //スプライン移動を振る舞い
            } else {
                free_interval_--;
            }
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
                pDriverLeader_->stop();
                pVecDriver->turnRzRyMvAngTo(RND_ABOUT(pVecDriver->_rz_mv, D_ANG(90)), RND_ABOUT(pVecDriver->_ry_mv, D_ANG(90)),
                                         D_ANG(2), 0, TURN_CLOSE_TO,false);
                pVecDriver->setMvAcce(100);
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
    pVecDriver->behave();
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
    GGAF_DELETE_NULLABLE(pDriverLeader_);
}
