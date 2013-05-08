#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyPalisana::EnemyPalisana(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Palisana", STATUS(EnemyPalisana)) {
    _class_name = "EnemyPalisana";
    _pActor_Base = nullptr;
    frame_of_morph_interval_   = 120;

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_LEAVE);
}

void EnemyPalisana::onCreateModel() {
//    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.1, 1.0);
//    _pModel->_pTexBlinker->setPower(0.1);
//    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyPalisana::initialize() {

    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 200000);

    setHitAble(true);
    setScaleR(1.0);
}

void EnemyPalisana::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
    _pKurokoA->setFaceAngVelo(AXIS_X, 200);
}

void EnemyPalisana::processBehavior() {

    switch (_pProg->get()) {
        case PROG_INIT: {
            _TRACE_("EnemyPalisana::processBehavior() ["<<getName()<<"] PROG_INIT きた");
            setHitAble(false);
            _pAFader->setAlpha(0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            _TRACE_("EnemyPalisana::processBehavior() "<<getName()<<" _X,_Y,_Z="<<_X<<","<<_Y<<","<<_Z<<"");
            break;
        }
        case PROG_ENTRY: {
            if (_pProg->isJustChanged()) {
                _TRACE_("EnemyPalisana::processBehavior() ["<<getName()<<"] PROG_ENTRY きた");
                _pAFader->fadeLinerUntil(0.7, 30);
            }
            if (_pProg->getFrameInProgress() == 20) {
                setHitAble(true);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("EnemyPalisana::processBehavior() ["<<getName()<<"] PROG_HATCH_OPEN きた");
                _pMorpher->morphLinerUntil(MPH_HATCH_OPEN,
                                           1.0, frame_of_morph_interval_);
            }
            if (!_pMorpher->isMorphing()) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_HATCH_OPEN_DONE: {
            if (_pProg->isJustChanged()) {
                _TRACE_("EnemyPalisana::processBehavior() ["<<getName()<<"] PROG_HATCH_OPEN_DONE きた");
            }
            //おしまい。
            break;
        }

        //-----------------------------------------------------------------------
        case PROG_HATCH_CLOSE: {
            if (_pProg->isJustChanged()) {
                _TRACE_("EnemyPalisana::processBehavior() ["<<getName()<<"] PROG_HATCH_CLOSE きた");
                _pMorpher->morphLinerUntil(MPH_HATCH_OPEN,
                                           0.0, frame_of_morph_interval_);
            }
            if (!_pMorpher->isMorphing()) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_LEAVE: {
            if (_pProg->isJustChanged()) {
                _TRACE_("EnemyPalisana::processBehavior() ["<<getName()<<"] PROG_LEAVE きた");
                setHitAble(false);
                UTIL::activateLeaveEffectOf(this);
                _pAFader->fadeLinerUntil(0.0, 30);
            }
            if (_pProg->getFrameInProgress() == 60) {
                sayonara();
                _pProg->changeNothing(); //おしまい！
            }
            break;
        }
        default :
            break;
    }
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    _pAFader->behave();
    _pMorpher->behave();
    _pKurokoA->behave();
}

void EnemyPalisana::processJudgement() {
}

void EnemyPalisana::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    //effectFlush(2); //フラッシュ
    _pSeTx->play3D(SE_DAMAGED);
}

void EnemyPalisana::onInactive() {
    sayonara();
}

void EnemyPalisana::acitve_open(frame prm_delay) {
    activateDelay(prm_delay);
}
bool EnemyPalisana::isOpenDone() {
    if (_pProg->get() == PROG_HATCH_OPEN_DONE) {
        return true;
    } else {
        return false;
    }
}
void EnemyPalisana::close_sayonara() {
    _pMorpher->stopImmed();
    _pProg->change(PROG_HATCH_CLOSE);
}


EnemyPalisana::~EnemyPalisana() {
}
