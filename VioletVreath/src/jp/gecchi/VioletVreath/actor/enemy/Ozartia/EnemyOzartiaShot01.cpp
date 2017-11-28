#include "EnemyOzartiaShot01.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT   ,
    PROG_ENTRY  ,
    PROG_MOVE01 ,
    PROG_LEAVE  ,
    PROG_BANPEI,
};

EnemyOzartiaShot01::EnemyOzartiaShot01(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "myvic", STATUS(EnemyOzartiaShot01)) {
    _class_name = "EnemyOzartiaShot01";
}

void EnemyOzartiaShot01::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
    getProgress()->reset(PROG_INIT);
}

void EnemyOzartiaShot01::onActive() {
    getStatus()->reset();
}

void EnemyOzartiaShot01::processBehavior() {
    //本体移動系の処理 ここから --->
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafDxAlphaFader* pAlphaFader = getAlphaFader();
    GgafProgress* const pProg = getProgress();
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
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                pAlphaFader->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pProg->hasArrivedAt(frame_of_entering)) {
                setHitAble(true);
                pProg->change(PROG_MOVE01);
            }
            break;
        }
        case PROG_MOVE01: {
            if (pProg->hasJustChanged()) {
            }
            if (pProg->hasArrivedAt(60*10)) {
                pProg->change(PROG_LEAVE);
            }
            break;
        }
        case PROG_LEAVE: {
             if (pProg->hasJustChanged()) {
                 UTIL::activateLeaveEffectOf(this);
                 pAlphaFader->transitionLinearUntil(0.0, 15);
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

void EnemyOzartiaShot01::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyOzartiaShot01::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyOzartiaShot01::onInactive() {
    sayonara();
}

EnemyOzartiaShot01::~EnemyOzartiaShot01() {
}
