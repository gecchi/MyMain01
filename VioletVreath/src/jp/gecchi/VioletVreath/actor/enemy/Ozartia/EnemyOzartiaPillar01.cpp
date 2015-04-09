#include "EnemyOzartiaPillar01.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyOzartiaPillar01::EnemyOzartiaPillar01(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "myvic", STATUS(EnemyOzartiaPillar01)) {
    _class_name = "EnemyOzartiaPillar01";
    pAFader_ = NEW GgafDxAlphaFader(this);
}

void EnemyOzartiaPillar01::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
    setHitAble(true);
    getProgress()->reset(PROG_INIT);
}

void EnemyOzartiaPillar01::onActive() {
    getStatus()->reset();
}

void EnemyOzartiaPillar01::processBehavior() {
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
            if (pProg->isJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame scale_in_frames = pEffectEntry->scale_in_frames_;
            static const frame duration_frames = pEffectEntry->duration_frames_;
            if (_pProg->hasArrivedAt(scale_in_frames)) {
                pAFader_->transitionLinerUntil(1.0, duration_frames);
            }
            if (getAlpha() > 0.9) {
                setHitAble(true);
                pProg->change(PROG_MOVE01);
            }
            break;
        }
        case PROG_MOVE01: {
            if (pProg->isJustChanged()) {
            }
            if (pProg->hasArrivedAt(60*10)) {
                pProg->change(PROG_LEAVE);
            }
            break;
        }
        case PROG_LEAVE: {
             if (pProg->isJustChanged()) {
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

void EnemyOzartiaPillar01::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyOzartiaPillar01::onHit(const GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyOzartiaPillar01::onInactive() {
    sayonara();
}

EnemyOzartiaPillar01::~EnemyOzartiaPillar01() {
    GGAF_DELETE(pAFader_);
}
