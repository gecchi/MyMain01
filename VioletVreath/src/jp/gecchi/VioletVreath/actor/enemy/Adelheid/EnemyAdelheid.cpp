#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAdelheid::EnemyAdelheid(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Adelheid", STATUS(EnemyAdelheid)) {
    _class_name = "EnemyAdelheid";
    pKurokoLeader_ = nullptr;
    pDepo_Shot_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    useProgress(PROG_FINISH);
}

void EnemyAdelheid::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAdelheid::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAdelheid::config(
        GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
        GgafCore::GgafActorDepository* prm_pDepo_Shot
        ) {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    pKurokoLeader_ = prm_pKurokoLeader;
    pDepo_Shot_ = prm_pDepo_Shot;
}

void EnemyAdelheid::onActive() {
//_TRACE_("EnemyAdelheid::onActive() ["<<getName()<<"] "<<_frame_of_life<<" onActive()来ましたはbrfor pKurokoLeader_="<<pKurokoLeader_);
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyAdelheidはスプライン必須ですconfigして下さい。 this="<<this<<" name="<<getName());
    }
//	_TRACE_("EnemyAdelheid::onActive() ["<<getName()<<"] "<<_frame_of_life<<"  onActive()来ましたはafter pKurokoLeader_="<<pKurokoLeader_);
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setFaceAng(AXIS_X, 0);
    _pKurokoA->setMvAcce(0);
    _pKurokoA->keepOnTurningFaceAngTwd(P_MYSHIP,
                                       D_ANG(2), 0, TURN_CLOSE_TO, false);
    _pProg->reset(PROG_INIT);

//    _TRACE_("onActive X,Y,Z="<<_X<<","<<_Y<<","<<_Z);
}

void EnemyAdelheid::processBehavior() {
//    _TRACE_("befor X,Y,Z="<<_X<<","<<_Y<<","<<_Z);


    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    switch (_pProg->get()) {
        case PROG_INIT: {
            _TRACE_("EnemyAdelheid::processBehavior() ["<<getName()<<"] PROG_INIT よー");
            _pProg->changeNext();
            break;
        }

        case PROG_SPLINE_MOVE: {
            if (_pProg->isJustChanged()) {
                _TRACE_("EnemyAdelheid::processBehavior() ["<<getName()<<"] PROG_SPLINE_MOVE よー");
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION);
            }
            break;
        }

        case PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _TRACE_("EnemyAdelheid::processBehavior() ["<<getName()<<"] PROG_FINISH ");
            }
            break;
        }
    }

    pKurokoLeader_->behave(); //スプライン移動を振る舞い
    _pKurokoA->behave();

//    _TRACE_("after X,Y,Z="<<_X<<","<<_Y<<","<<_Z);
}

void EnemyAdelheid::processJudgement() {
    if (pKurokoLeader_->isFinished()) {
        _TRACE_("EnemyAdelheid::processJudgement() ["<<getName()<<"] isFinished  sayonara();");
        sayonara();
    }

    if (isOutOfUniverse()) {
        _TRACE_("EnemyAdelheid::processJudgement() ["<<getName()<<"] isOutOfUniverse  sayonara();");
        sayonara();
    }
}

void EnemyAdelheid::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //破壊時
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_EXPLOSION);

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
            UTIL::activateItemOf(this);
        }
        //sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
    }
}

void EnemyAdelheid::onInactive() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

EnemyAdelheid::~EnemyAdelheid() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}


