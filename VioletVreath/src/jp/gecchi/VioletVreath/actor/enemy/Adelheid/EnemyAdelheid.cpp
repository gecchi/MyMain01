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
    pFormation_ = nullptr;
    useProgress(PROG_MOVING);
}

void EnemyAdelheid::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAdelheid::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    setScaleR(0.3);

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
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyAdelheidはスプライン必須ですconfigして下さい。 this="<<this<<" name="<<getName());
    }
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setFaceAng(AXIS_X, 0);
    _pKurokoA->setMvAcce(0);
    _pKurokoA->keepOnTurningFaceAngTwd(P_MYSHIP,
                                       D_ANG(2), 0, TURN_CLOSE_TO, false);
    pFormation_ = (FormationAdelheid*)getFormation();
    _pProg->reset(PROG_INIT);
}

void EnemyAdelheid::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    switch (_pProg->get()) {
        case PROG_INIT: {
            pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION);
            _pProg->changeNext();
            break;
        }
        case PROG_MOVING: {
            if (_pProg->isJustChanged()) {
            }
            //pKurokoLeader_->isFinished() 待ち
            break;
        }
    }
    if (pFormation_) {
        _pKurokoA->_veloMv = pFormation_->mv_velo_member_;
    }

    pKurokoLeader_->behave(); //スプライン移動を振る舞い
    _pKurokoA->behave();
}

void EnemyAdelheid::processJudgement() {
    if (pKurokoLeader_->isFinished()) {
        sayonara();
    }

    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAdelheid::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyAdelheid::onInactive() {
    pFormation_ = nullptr;
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

EnemyAdelheid::~EnemyAdelheid() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}


