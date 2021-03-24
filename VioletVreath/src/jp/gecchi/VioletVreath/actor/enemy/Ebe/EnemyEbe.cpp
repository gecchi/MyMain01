#include "EnemyEbe.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_MOVE01_1   ,
    PROG_SPLINE_MOVE,
    PROG_MOVE02_1   ,
    PROG_MOVE02_2   ,
    PROG_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_EXPLOSION,
};

EnemyEbe::EnemyEbe(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Ebe", StatusReset(EnemyEbe)) {
    _class_name = "EnemyEbe";
    pVecDriverLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    callVecDriver()->linkFaceAngByMvAng(true);
}

void EnemyEbe::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyEbe::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyEbe::config(
        SplineLeader* prm_pVecDriverLeader,
        GgafCore::ActorDepository* prm_pDepo_shot,
        GgafCore::ActorDepository* prm_pDepo_shotEffect
        ) {
    GGAF_DELETE_NULLABLE(pVecDriverLeader_);
    pVecDriverLeader_ = prm_pVecDriverLeader;
    pDepo_shot_ = prm_pDepo_shot;
    pDepo_effect_ = prm_pDepo_shotEffect;
}

void EnemyEbe::onActive() {
    if (pVecDriverLeader_ == nullptr) {
        throwCriticalException("EnemyEbeはスプライン必須ですconfigして下さい");
    }
    getStatus()->reset();
    setHitAble(true);
    callVecDriver()->setMvAcce(0);
    getProgress()->reset(PROG_MOVE01_1);
}

void EnemyEbe::processBehavior() {
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_MOVE01_1: {
            if ((int)(pProg->getFrame()) > (int)(PX_C(300) / ABS(pVecDriver->_velo_mv))) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_SPLINE_MOVE: {
            if (pProg->hasJustChanged()) {
                pVecDriverLeader_->start(RELATIVE_COORD);
            }
            pVecDriverLeader_->behave();

            if (pVecDriverLeader_->isFinished()) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE02_1: {
            if (pProg->hasJustChanged()) {
                pVecDriver->turnMvAngTwd(_x - PX_C(300), _y, _z,
                                      D_ANG(1), 0, TURN_CLOSE_TO, false);
            }

            break;
        }
    }

    pVecDriver->behave();
}

void EnemyEbe::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEbe::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyEbe::onInactive() {
    GGAF_DELETE_NULLABLE(pVecDriverLeader_);
}

EnemyEbe::~EnemyEbe() {
    GGAF_DELETE_NULLABLE(pVecDriverLeader_);
}


