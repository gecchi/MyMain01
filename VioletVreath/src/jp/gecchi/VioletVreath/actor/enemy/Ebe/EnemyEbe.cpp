#include "EnemyEbe.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_MOVE01_1   ,
    PHASE_CURVE_MOVE,
    PHASE_MOVE02_1   ,
    PHASE_MOVE02_2   ,
    PHASE_BANPEI,
};

EnemyEbe::EnemyEbe(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Ebe", StatusReset(EnemyEbe)) {
    _class_name = "EnemyEbe";
    pVehicleLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    getLocusVehicle()->linkFaceAngByMvAng(true);
}

void EnemyEbe::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyEbe::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyEbe::config(
        GgafDx::CurveManufacture*  prm_pCurveManufacture,
        GgafCore::ActorDepository* prm_pDepo_shot,
        GgafCore::ActorDepository* prm_pDepo_shotEffect
        ) {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
    pVehicleLeader_ = createCurveVehicleLeader(prm_pCurveManufacture);
    pDepo_shot_ = prm_pDepo_shot;
    pDepo_effect_ = prm_pDepo_shotEffect;
}

void EnemyEbe::onActive() {
    if (pVehicleLeader_ == nullptr) {
        throwCriticalException("EnemyEbeはスプライン必須ですconfigして下さい");
    }
    getStatus()->reset();
    setHitAble(true);
    getLocusVehicle()->setMvAcce(0);
    getPhase()->reset(PHASE_MOVE01_1);
}

void EnemyEbe::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_MOVE01_1: {
            if ((int)(pPhase->getFrame()) > (int)(PX_C(300) / ABS(pLocusVehicle->_velo_mv))) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_CURVE_MOVE: {
            if (pPhase->hasJustChanged()) {
                pVehicleLeader_->start(RELATIVE_COORD);
            }
            pVehicleLeader_->behave();

            if (pVehicleLeader_->isFinished()) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_MOVE02_1: {
            if (pPhase->hasJustChanged()) {
                pLocusVehicle->turnMvAngTwd(_x - PX_C(300), _y, _z,
                                      D_ANG(1), 0, TURN_CLOSE_TO, false);
            }

            break;
        }
    }

    pLocusVehicle->behave();
}

void EnemyEbe::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEbe::onInactive() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}

EnemyEbe::~EnemyEbe() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}


