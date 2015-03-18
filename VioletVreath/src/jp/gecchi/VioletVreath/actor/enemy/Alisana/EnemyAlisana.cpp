#include "EnemyAlisana.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyAlisana::EnemyAlisana(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Alisana", STATUS(EnemyAlisana)) {
    _class_name = "EnemyAlisana";
    pAFader_ = NEW GgafDxAlphaFader(this);
    frame_of_morph_interval_ = 120;

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyAlisana::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyAlisana::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 200000);

    setHitAble(true);
    setScaleR(1.0);
}

void EnemyAlisana::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
    getKuroko()->setFaceAngVelo(AXIS_X, 200);
}

void EnemyAlisana::processBehavior() {
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (pProg->isJustChanged()) {
                pAFader_->transitionLinerUntil(0.7, 30);
            }
            if (pProg->hasArrivedAt(20)) {
                setHitAble(true);
                pProg->changeNext();
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (pProg->isJustChanged()) {
                getMorpher()->transitionLinerUntil(MPH_HATCH_OPEN,
                                           1.0, frame_of_morph_interval_);
            }
            if (!getMorpher()->isTransitioning()) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_HATCH_OPEN_DONE: {
            if (pProg->isJustChanged()) {
            }
            //おしまい。
            break;
        }

        //-----------------------------------------------------------------------
        case PROG_HATCH_CLOSE: {
            if (pProg->isJustChanged()) {
                getMorpher()->transitionLinerUntil(MPH_HATCH_OPEN,
                                           0.0, frame_of_morph_interval_);
            }
            if (!getMorpher()->isTransitioning()) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_LEAVE: {
            if (pProg->isJustChanged()) {
                setHitAble(false);
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinerUntil(0.0, 30);
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
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    pAFader_->behave();
    getMorpher()->behave();
    getKuroko()->behave();
}

void EnemyAlisana::processJudgement() {
}

void EnemyAlisana::onHit(const GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTx()->play3D(SE_DAMAGED);
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
