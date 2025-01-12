#include "EnemyRatislaviaEye.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EffectRatislaviaEye001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislavia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEyeStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_MOVE ,
    PHASE_OPEN ,
    PHASE_TURN ,
    PHASE_FIRE_BEGIN,
    PHASE_IN_FIRE   ,
    PHASE_FIRE_END  ,
    PHASE_CLOSE     ,
    PHASE_BANPEI,
};
enum {
    SE_FIRE,
};

EnemyRatislaviaEye::EnemyRatislaviaEye(const char* prm_name, EnemyRatislavia* prm_pRatislavia) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "RatislaviaEye", StatusReset(EnemyRatislaviaEye)) {
        //CubeMapMorphMeshActor(prm_name, "HaliaCM") {
    _class_name = "EnemyRatislaviaEye";
    setScaleR(0.3*10);
    pRatislavia_ = prm_pRatislavia;
    setPositionAt(pRatislavia_);

    pLaserChipDepo_ = NEW LaserChipDepository("DepoLaserChip");
    pLaserChipDepo_->config(60, 1); //Haliaは弾切れフレームを1にしないとパクパクしちゃいます。
    EnemyRatislaviaEyeStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //レーザーストック
        std::string name = "LaserChip("+ XTOS(i) + ")";
        pChip = NEW EnemyRatislaviaEyeStraightLaserChip001(name.c_str());
        pChip->setSource(this); //位置向き同期
        pLaserChipDepo_->put(pChip);
    }
    appendChild(pLaserChipDepo_);

    pEffect_ = NEW EffectRatislaviaEye001("EffectRatislaviaEye001");
    pEffect_->inactivate();
    appendChild(pEffect_);
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_FIRE     , "SE_ENEMY_FIRE_LASER_001");

    is_wake_ = false;
}

void EnemyRatislaviaEye::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyRatislaviaEye::initialize() {
    setHitAble(true);
    getLocusVehicle()->linkFaceAngByMvAng(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSphere(0, 200000);
}

void EnemyRatislaviaEye::onActive() {
    getStatus()->reset();
    setMorphWeight(1, 0.0);
    getPhase()->reset(PHASE_MOVE);
    setPositionAt(pRatislavia_);
    setFaceAngAs(pRatislavia_);
    getLocusVehicle()->setRzRyMvAngVelo(pRatislavia_->getLocusVehicle()->_angvelo_face[AXIS_Z],
                                  pRatislavia_->getLocusVehicle()->_angvelo_face[AXIS_Y]);
}

void EnemyRatislaviaEye::processBehavior() {
    setPositionAt(pRatislavia_);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_MOVE: {
            break;
        }
        case PHASE_OPEN: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(1, 1.0, 180); //開く
            }
            if (pPhase->getFrame() > 240) {
                pPhase->changeNext();
            }
            pLocusVehicle->takeoverFrom(pRatislavia_->getLocusVehicle());
            pLocusVehicle->setRzRyMvAngVelo(pRatislavia_->getLocusVehicle()->_angvelo_face[AXIS_Z],
                                      pRatislavia_->getLocusVehicle()->_angvelo_face[AXIS_Y]);
            break;
        }

        case PHASE_TURN: {
            if (pPhase->hasJustChanged()) {
                pLocusVehicle->turnMvAngTwd(pMYSHIP,
                                        D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            if (pPhase->getFrame() > 240) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_FIRE_BEGIN: {
            if (pPhase->hasJustChanged()) {
                //_pLocusVehicle->turnMvAngTwd(pMYSHIP, D_ANG(1), 0, TURN_ANTICLOSE_TO, false);
                pEffect_->activate();
            }
            pEffect_->setPositionAt(this);
            if (pEffect_->hasJustChangedToInactive()) {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_IN_FIRE: {
            if (pPhase->hasJustChanged()) {
                pLocusVehicle->turnMvAngTwd(pMYSHIP,
                                        10, 0, TURN_CLOSE_TO, false);
            }
            LaserChip* pChip = pLaserChipDepo_->dispatch();
            if (pChip) {
                if (pChip->getInfrontChip() == nullptr) {
                    getSeXmtr()->play3D(SE_FIRE);
                }
            } else {
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_FIRE_END: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(1, 0.0, 180); //閉じる
                pLocusVehicle->setRzRyMvAngVelo(pRatislavia_->getLocusVehicle()->_angvelo_face[AXIS_Z],
                                          pRatislavia_->getLocusVehicle()->_angvelo_face[AXIS_Y]);
            }
            //硬直
            if (pPhase->getFrame() >= 300) {
                pPhase->change(PHASE_OPEN);
            }
            break;
        }

        default: {
            break;
        }
    }

    pLocusVehicle->behave();
    getMorpher()->behave();
    getSeXmtr()->behave();
}

void EnemyRatislaviaEye::processJudgement() {
//    if (isOutOfSpacetime()) {
//        sayonara();
//    }
}

void EnemyRatislaviaEye::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    bool is_stamina_zero = performEnemyHit(prm_pOppHitChecker);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        sayonara();
        _TRACE_(FUNC_NAME<<" 上位になげるthrowEventUpperTree(RATISLAVIA_EXPLOSION)");
        throwEventUpperTree(RATISLAVIA_EXPLOSION); //親のEnemyRatislaviaを破壊するイベントを投げる
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyRatislaviaEye::onInactive() {
    //sayonara();
}

void EnemyRatislaviaEye::wake() {
    is_wake_ = true;
    getPhase()->change(PHASE_OPEN);
}

EnemyRatislaviaEye::~EnemyRatislaviaEye() {
}
