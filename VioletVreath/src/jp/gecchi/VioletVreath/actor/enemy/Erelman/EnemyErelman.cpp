#include "EnemyErelman.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/FormationErelman.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
#include "FormationErelman.h"


using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION ,
};
enum {
    PROG_INIT   ,
    PROG_ENTRY  ,
    PROG_MOVE_BEGIN ,
    PROG_SPLINE ,
    PROG_SCATTER ,
    PROG_LEAVE ,
    PROG_BANPEI,
};

EnemyErelman::EnemyErelman(const char* prm_name) :
        DefaultMassMeshActor(prm_name, "Erelman", STATUS(EnemyErelman)) {
    _class_name = "EnemyErelman";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
    pKurokoLeader_ = nullptr; //フォーメーションオブジェクトが設定する
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
    GgafDx::Kuroko* const pKuroko = getKuroko();
//    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->forceMvVeloRange(PX_C(15));
}

void EnemyErelman::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyErelman::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
//            pKuroko->setRollFaceAngVelo(D_ANG(3));
            setRyFaceAng(D_ANG(90));
            pKuroko->setRzFaceAngVelo(D_ANG(3));
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

        case PROG_SPLINE: {
            if (pProg->hasJustChanged()) {
                getKuroko()->setMvAcce(0); //加速度がある場合は切っておく
                pKurokoLeader_->start(RELATIVE_COORD_DIRECTION, -1); //-1は無限ループ
            }
            if (free_interval_ == 0) {
                FormationErelman* pFormation = (FormationErelman*)getFormation();
                pKurokoLeader_->setStartPosition(pFormation->geo_.x, pFormation->geo_.y, pFormation->geo_.z);
                pKurokoLeader_->setStartAngle(pFormation->geo_.rx, pFormation->geo_.ry, pFormation->geo_.rz);
                pKurokoLeader_->behave(); //スプライン移動を振る舞い
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
                pKurokoLeader_->stop();
                pKuroko->turnRzRyMvAngTo(RND_ABOUT(pKuroko->_rz_mv, D_ANG(90)), RND_ABOUT(pKuroko->_ry_mv, D_ANG(90)),
                                         D_ANG(2), 0, TURN_CLOSE_TO,false);
                pKuroko->setMvAcce(100);
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
    pKuroko->behave();
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
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
