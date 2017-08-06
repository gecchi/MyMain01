#include "EnemyAlisana.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyAlisana::EnemyAlisana(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Alisana", STATUS(EnemyAlisana)) {
    _class_name = "EnemyAlisana";
    pAFader_ = NEW GgafDxAlphaFader(this);
    frame_of_morph_interval_ = 120;

    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
    pSe->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSe->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyAlisana::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyAlisana::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, 200000);

    setHitAble(true);
    setScaleR(1.0);
}

void EnemyAlisana::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyAlisana::processBehavior() {
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
                pAFader_->transitionLinearUntil(0.999, frame_of_entering);
            }
            if (pProg->hasArrivedAt(frame_of_entering)) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (pProg->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MPH_HATCH_OPEN,
                                           1.0, frame_of_morph_interval_);
            }
            if (!getMorpher()->isTransitioning()) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_HATCH_OPEN_DONE: {
            if (pProg->hasJustChanged()) {
            }
            //おしまい。
            break;
        }

        //-----------------------------------------------------------------------
        case PROG_HATCH_CLOSE: {
            if (pProg->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MPH_HATCH_OPEN,
                                           0.0, frame_of_morph_interval_);
            }
            if (!getMorpher()->isTransitioning()) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_LEAVE: {
            if (pProg->hasJustChanged()) {
                setHitAble(false);
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinearUntil(0.0, 30);
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
    pAFader_->behave();
    getMorpher()->behave();
    getKuroko()->behave();
}

void EnemyAlisana::processJudgement() {
}

void EnemyAlisana::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyAlisana::onInactive() {
    sayonara();
}

void EnemyAlisana::acitve_open(frame prm_delay) {
    activateDelay(prm_delay);
}

bool EnemyAlisana::isOpenDone() {
    if (getProgress()->get() == PROG_HATCH_OPEN_DONE) {
        return true;
    } else {
        return false;
    }
}

void EnemyAlisana::close_sayonara() {
    getMorpher()->stop();
    getProgress()->change(PROG_HATCH_CLOSE);
}

EnemyAlisana::~EnemyAlisana() {
    GGAF_DELETE(pAFader_);
}

