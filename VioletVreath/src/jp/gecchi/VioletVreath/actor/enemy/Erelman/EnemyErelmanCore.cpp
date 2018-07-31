#include "EnemyErelmanCore.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/FormationErelman001.h"
#include "EnemyErelmanController.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT  ,
    PROG_ENTRY ,
    PROG_WAIT01 ,
    PROG_LEAVE ,
    PROG_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_UNDAMAGED  ,
    SE_EXPLOSION,
    SE_FIRE,
};

EnemyErelmanCore::EnemyErelmanCore(const char* prm_name, EnemyErelmanController* prm_pController) :
        DefaultMorphMeshActor(prm_name, "1/ErelmanCore", STATUS(EnemyErelmanCore)) {
    _class_name = "EnemyErelmanCore";
    pController_ = prm_pController;

    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_UNDAMAGED, "WAVE_ENEMY_UNDAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_002");
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_BANPEI);

}

void EnemyErelmanCore::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyErelmanCore::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->forceMvVeloRange(PX_C(15));
}

void EnemyErelmanCore::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyErelmanCore::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafDxAlphaFader* pAlphaFader = getAlphaFader();

    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
//            pKuroko->setRollFaceAngVelo(D_ANG(3));
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

        case PROG_WAIT01: {
            if (pProg->hasJustChanged()) {
//                pKuroko->setRollPitchYawFaceAngVelo(D_ANG(0.027), D_ANG(0.0031), D_ANG(0.0071));
            }
            if (pProg->hasArrivedAt(10*60*60)) {
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

void EnemyErelmanCore::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyErelmanCore::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    pController_->onCoreHit();
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyErelmanCore::onInactive() {
    sayonara();
//    pController_->pErelmanCore_ = nullptr;
}

EnemyErelmanCore::~EnemyErelmanCore() {
}
