#include "EnemyOzartiaShot01.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyOzartiaShot01::EnemyOzartiaShot01(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "myvic", STATUS(EnemyOzartiaShot01)) {
    _class_name = "EnemyOzartiaShot01";
    pAFader_ = NEW GgafDxAlphaFader(this);
}

void EnemyOzartiaShot01::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
    getProgress()->reset(PROG_INIT);
}

void EnemyOzartiaShot01::onActive() {
    getStatus()->reset();
}

void EnemyOzartiaShot01::processBehavior() {
    UTIL::updateEnemyRankPoint(this);
    //本体移動系の処理 ここから --->
    GgafDxKuroko* const pKuroko = getKuroko();
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
            static const frame frame_of_summons = pEffectEntry->getFrameOfSummonsBegin();
            static const frame summoning_frames = pEffectEntry->getSummoningFrames();
            if (_pProg->hasArrivedAt(frame_of_summons)) {
                pAFader_->transitionLinerUntil(1.0, summoning_frames);
            }
            if (_pProg->hasArrivedAt(frame_of_summons+summoning_frames)) {
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
                 pAFader_->transitionLinerUntil(0.0, 15);
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
    pKuroko->behave();
}

void EnemyOzartiaShot01::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyOzartiaShot01::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
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
    GGAF_DELETE(pAFader_);
}
