#include "EnemyUnomia.h"

#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_ENTRY      ,
    PHASE_CURVE_MOVE,
    PHASE_MOVE01_1   ,
    PHASE_MOVE01_2   ,
    PHASE_LEAVE      ,
    PHASE_BANPEI,
};
enum {
    SE_EXPLOSION ,
};

EnemyUnomia::EnemyUnomia(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Unomia", StatusReset(EnemyUnomia)) {
    _class_name = "EnemyUnomia";
    pVehicleLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_EXPLOSION, "SE_EXPLOSION_001");     //爆発
}

void EnemyUnomia::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyUnomia::initialize() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->linkFaceAngByMvAng(true);
    pLocoVehicle->setRollFaceAngVelo(-4000);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyUnomia::onReset() {
}

void EnemyUnomia::config(
        GgafDx::CurveManufacture* prm_pCurveManufacture,
        GgafCore::ActorDepository* prm_pDepo_shot,
        GgafCore::ActorDepository* prm_pDepo_shotEffect
        ) {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
    pVehicleLeader_ = createCurveVehicleLeader(prm_pCurveManufacture);
    pDepo_shot_ = prm_pDepo_shot;
    pDepo_effect_ = prm_pDepo_shotEffect;
}


void EnemyUnomia::onActive() {
    if (pVehicleLeader_ == nullptr) {
        throwCriticalException("EnemyUnomiaはスプライン必須ですconfigして下さい");
    }
    getStatus()->reset();
    setHitAble(true);
    setRzFaceAng(0);
    getPhase()->reset(PHASE_ENTRY);
}

void EnemyUnomia::processBehavior() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_ENTRY: {
            pVehicleLeader_->start(ABSOLUTE_COORD);
            pPhase->changeNext();
            break;
        }
        case PHASE_CURVE_MOVE: {
            pVehicleLeader_->behave(); //カーブ移動するようにDriverを操作
            if (pVehicleLeader_->isFinished()) {
                pPhase->changeNext(); //次へ
            }
            break;
        }
        case PHASE_MOVE01_1: {
            if (pPhase->hasJustChanged()) {
                //自機へ方向転換
                pLocoVehicle->turnMvAngTwd(
                               pMYSHIP->_x, _y, pMYSHIP->_z,
                               2000, 0,
                               TURN_CLOSE_TO, true
                           );
            }

//            if (pDepo_shot_) {
//                //放射状ショット
//                int way = RF_EnemyUnomia_ShotWay(G_RANK); //ショットWAY数
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDx::FigureActor* pActor_shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_shot = (GgafDx::FigureActor*)pDepo_shot_->dispatch();
//                    if (pActor_shot) {
//                        pActor_shot->setPositionAt(this);
//                        pActor_shot->getLocoVehicle()->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                GGAF_DELETEARR(paAng_way);
//                //ショット発射エフェクト
//                if (pDepo_effect_) {
//                    GgafDx::FigureActor* pTestActor_Shot = (GgafDx::FigureActor*)pDepo_effect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->setPositionAt(this);
//                    }
//                }
//            }
            break;
        }
        default: {
            break;
        }
    }

    pLocoVehicle->behave();
}

void EnemyUnomia::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyUnomia::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeXmtr()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyUnomia::onInactive() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}

EnemyUnomia::~EnemyUnomia() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}


