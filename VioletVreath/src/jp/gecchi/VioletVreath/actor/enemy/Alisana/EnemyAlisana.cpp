#include "stdafx.h"
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
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyAlisana::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAlisana::initialize() {

    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 200000);

    setHitAble(true);
    setScaleR(1.0);
}

void EnemyAlisana::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
    _pKuroko->setFaceAngVelo(AXIS_X, 200);
}

void EnemyAlisana::processBehavior() {

    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (_pProg->isJustChanged()) {
                pAFader_->transitionLinerUntil(0.7, 30);
            }
            if (_pProg->getFrameInProgress() == 20) {
                setHitAble(true);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->transitionLinerUntil(MPH_HATCH_OPEN,
                                           1.0, frame_of_morph_interval_);
            }
            if (!_pMorpher->isTransitioning()) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_HATCH_OPEN_DONE: {
            if (_pProg->isJustChanged()) {
            }
            //‚¨‚µ‚Ü‚¢B
            break;
        }

        //-----------------------------------------------------------------------
        case PROG_HATCH_CLOSE: {
            if (_pProg->isJustChanged()) {
                _pMorpher->transitionLinerUntil(MPH_HATCH_OPEN,
                                           0.0, frame_of_morph_interval_);
            }
            if (!_pMorpher->isTransitioning()) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_LEAVE: {
            if (_pProg->isJustChanged()) {
                setHitAble(false);
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinerUntil(0.0, 30);
            }
            if (_pProg->getFrameInProgress() == 60) {
                sayonara();
                _pProg->changeNothing(); //‚¨‚µ‚Ü‚¢I
            }
            break;
        }
        default :
            break;
    }
    //‰ÁŽZƒ‰ƒ“ƒNƒ|ƒCƒ“ƒg‚ðŒ¸­
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    pAFader_->behave();
    _pMorpher->behave();
    _pKuroko->behave();
}

void EnemyAlisana::processJudgement() {
}

void EnemyAlisana::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //”j‰óŽž
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //”ñ”j‰óŽž
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyAlisana::onInactive() {
    sayonara();
}

void EnemyAlisana::acitve_open(frame prm_delay) {
    activateDelay(prm_delay);
}
bool EnemyAlisana::isOpenDone() {
    if (_pProg->get() == PROG_HATCH_OPEN_DONE) {
        return true;
    } else {
        return false;
    }
}
void EnemyAlisana::close_sayonara() {
    _pMorpher->stop();
    _pProg->change(PROG_HATCH_CLOSE);
}


EnemyAlisana::~EnemyAlisana() {
    GGAF_DELETE(pAFader_);
}
