#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHebe::EnemyHebe(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Hebe", STATUS(EnemyHebe)) {
    _class_name = "EnemyHebe";
    pSplSeq_ = NULL;
    pDepo_Shot_ = NULL;
    pDepo_ShotEffect_ = NULL;
    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"        , GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
    useProgress(10);
}

void EnemyHebe::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyHebe::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyHebe::config(
        GgafLib::SplineSequence* prm_pSplSeq,
        GgafCore::GgafActorDepository* prm_pDepo_Shot,
        GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
        ) {
    DELETE_POSSIBLE_NULL(pSplSeq_);
    pSplSeq_ = prm_pSplSeq;
    pDepo_Shot_ = prm_pDepo_Shot;
    pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
}


void EnemyHebe::onActive() {
    if (pSplSeq_ == NULL) {
        throwGgafCriticalException("EnemyHebeはスプライン必須ですconfigして下さい");
    }
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setFaceAng(AXIS_X, 0);
    _pKurokoA->setMvAcce(0);
    _pProg->set(PROG_MOVE01_1);
}

void EnemyHebe::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    switch (_pProg->get()) {
        case PROG_MOVE01_1: {
            if (_pProg->getFrameInProgress() > (PX_C(300) / ABS(_pKurokoA->_veloMv))) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_SPLINE_MOVE: {
            if (_pProg->isJustChanged()) {
                pSplSeq_->exec(SplineSequence::RELATIVE_COORD);
            }
            if (!pSplSeq_->isExecuting()) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE02_1: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->execTurnMvAngSequence(_X - PX_C(300), _Y, _Z,
                                                 D_ANG(1), 0, TURN_CLOSE_TO, false);
            }

            break;
        }
    }

    pSplSeq_->behave(); //スプライン移動を振る舞い
    _pKurokoA->behave();
    //_pSeTxer->behave();
}

void EnemyHebe::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyHebe::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //破壊時
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
            UTIL::activateItemOf(this);
        }
        sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
    }
}

void EnemyHebe::onInactive() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}

EnemyHebe::~EnemyHebe() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}


