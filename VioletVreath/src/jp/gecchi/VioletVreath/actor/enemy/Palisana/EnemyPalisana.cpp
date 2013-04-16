#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

EnemyPalisana::EnemyPalisana(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Palisana", STATUS(EnemyPalisana)) {
    _class_name = "EnemyPalisana";
    _pActor_Base = nullptr;
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 20*60;
    frame_of_morph_interval_   = 120;

    pDepo_Fired_ = nullptr;
    pDepoConnection_ = connectToDepositoryManager("Atalante");

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_HATCH_OPEN);
}

void EnemyPalisana::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyPalisana::initialize() {
    setHitAble(true);
    _pKurokoA->relateMvFaceAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 200000);
    _pScaler->setScale(1000);
    _pScaler->forceRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
    pDepo_Fired_ = pDepoConnection_->peek();
}

void EnemyPalisana::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
//    frame_of_moment_nextopen_ = frame_of_close_interval_;
    _pProg->reset(PROG_HATCH_CLOSE);
}

void EnemyPalisana::processBehavior() {

    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            _pAFader->setAlpha(0);
            _pKurokoA->setMvVelo(0);
            _pKurokoA->setMvAcce(0);
            _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(10));
            _pKurokoB->setZeroVxyzMvVelo();
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {
            if (_pProg->isJustChanged()) {
                _pAFader->fadeLinerUntil(1.0, 30);
            }
            if (_pProg->getFrameInProgress() == 30) {
                setHitAble(true);
                _pProg->changeNext();
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->morphLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                1.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, 0);
            }

            break;
        }
        case PROG_HATCH_CLOSE: {
            if (_pProg->isJustChanged()) {
                _pMorpher->morphLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                0.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, -3000);
            }

            //次へ
            if (_pProg->getFrameInProgress() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_LEAVE: {
            if (_pProg->isJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                _pAFader->fadeLinerUntil(0.0, 15);
            }
            if (_pProg->getFrameInProgress() == 15) {
                setHitAble(false);
                sayonara();
            }
            break;
        }
        default :
            break;
    }
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));


    _pScaler->behave();
    _pMorpher->behave();
    _pKurokoA->behave();

}

void EnemyPalisana::processJudgement() {
}

void EnemyPalisana::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_EXPLOSION);

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
            UTIL::activateItemOf(this);
        }
        sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyPalisana::onInactive() {
    sayonara();
}

void EnemyPalisana::acitve_open() {
    _pProg->change(PROG_ENTRY);
}

void EnemyPalisana::close_sayonara() {
    _pProg->change(PROG_HATCH_CLOSE);
}


EnemyPalisana::~EnemyPalisana() {
    pDepoConnection_->close();
}
