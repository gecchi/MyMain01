#include "EnemyHalia.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAssistant.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_ENTRY  ,
    PHASE_FIRST_MOVE,
    PHASE_MOVE      ,
    PHASE_TURN_OPEN ,
    PHASE_FIRE_BEGIN,
    PHASE_IN_FIRE   ,
    PHASE_CLOSE     ,
    PHASE_BANPEI,
};
enum {
    SE_UNDAMAGED  ,
    SE_FIRE,
};

EnemyHalia::EnemyHalia(const char* prm_name) :
        VvEnemyActor<DefaultMassMorphMeshActor>(prm_name, "Halia", StatusReset(EnemyHalia)) {
        //VvEnemyActor<CubeMapMassMorphMeshActor>(prm_name, "HaliaCM", StatusReset(EnemyHalia)) {
    _class_name = "EnemyHalia";
    veloTopMv_ = 20000;
    pVehicleLeader_ = nullptr;
    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    pLaserChipDepo_->config(60, 1); //Haliaは弾切れフレームを1にしないとパクパクしちゃいます。
    EnemyStraightLaserChip001* pChip;
    for (int i = 0; i < 65; i++) { //レーザーストック
        std::string name = "EnemyStraightLaserChip001["+XTOS(i)+"]";
        pChip = NEW EnemyStraightLaserChip001(name.c_str());
        pChip->setSource(this); //位置向き同期
        pLaserChipDepo_->put(pChip);
    }
    appendChild(pLaserChipDepo_);
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_UNDAMAGED, "SE_ENEMY_UNDAMAGED_001");
    pSeXmtr->set(SE_FIRE     , "SE_ENEMY_FIRE_LASER_001");

    //初期カメラZ位置
    const Camera* const pCam = pCARETAKER->getSpacetime()->getCamera();
    dZ_camera_init_ = -1 * DX_C(pCam->getZOrigin());
}

void EnemyHalia::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
    pModel->setSpecular(5.0, 1.0);
}

void EnemyHalia::initialize() {
    setHitAble(true);
    getLocusVehicle()->linkFaceAngByMvAng(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSphere(0, 90000);
    setScaleR(0.3);
}

void EnemyHalia::onActive() {
    getStatus()->reset();
    setMorphWeight(0.0);
    getPhase()->reset(PHASE_INIT);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRollFaceAngVelo(1000);
    pLocusVehicle->setMvVelo(0);
    pLocusVehicle->setMvAcce(0);
}

void EnemyHalia::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
            pPhase->changeNext();
            break;
        }
        case PHASE_ENTRY: {  //登場
            EffectBlink* pEffectEntry = nullptr;
            if (pPhase->hasJustChanged()) {
                pEffectEntry = (EffectBlink*)UTIL::activateCommonEffectOf(this, STAT_EntryEffectKind);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pPhase->hasArrivedFrameAt(frame_of_summons_begin)) {
                getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                setHitAble(true);
                pPhase->change(PHASE_FIRST_MOVE);
            }
            break;
        }
        case PHASE_FIRST_MOVE: { //初回移動
            if (pPhase->hasJustChanged()) {
                pLocusVehicle->setRzRyMvAng(0, 0);
                pLocusVehicle->asstMv()->slideByVd(veloTopMv_, PX_C(1000),
                                              0.4, 0.6, 0, true);
                pLocusVehicle->setRollFaceAngVelo(D_ANG(1));
            }
            if (!pLocusVehicle->asstMv()->isSliding()) {
                pPhase->change(PHASE_TURN_OPEN);
            }
            break;
        }
        case PHASE_MOVE: {  //２回以降の移動
            if (pPhase->hasJustChanged()) {
                pLocusVehicle->asstMv()->slideByVd(veloTopMv_, PX_C(1000),
                                              0.4, 0.6, 0, true);
                pLocusVehicle->setRollFaceAngVelo(D_ANG(1));
            }
            if (!pLocusVehicle->asstMv()->isSliding()) {
                pPhase->change(PHASE_TURN_OPEN);
            }
            break;
        }
        case PHASE_TURN_OPEN: {
            if (pPhase->hasJustChanged()) {
                pLocusVehicle->turnMvAngTwd(pMYSHIP,
                                      0, 100,
                                      TURN_CLOSE_TO, false);
            }
            if (!pLocusVehicle->isTurningMvAng()) {
                pLocusVehicle->turnMvAngTwd(pMYSHIP,
                                      D_ANG(1), 0,
                                      TURN_CLOSE_TO, false);
                getMorpher()->transitionAcceUntil(1, 1.0, 0.0, 0.0004); //開く 0.0004 開く速さ
                pPhase->changeNext();
            }
            break;
        }
        case PHASE_FIRE_BEGIN: {
            if (!getMorpher()->isTransitioning()) {
                if ( _x - pMYSHIP->_x > -dZ_camera_init_) {
                    pLocusVehicle->setMvVelo(PX_C(1)); //ちょっとバック
                    pLocusVehicle->setRollFaceAngVelo(D_ANG(5));//発射中は速い回転
                    pPhase->change(PHASE_IN_FIRE);
                } else {
                    //背後からは撃たない。
                    pPhase->change(PHASE_CLOSE);
                }
            }
            break;
        }
        case PHASE_IN_FIRE: {
            LaserChip* pLaser = pLaserChipDepo_->dispatch();
            if (pLaser) {
                if (pLaser->getInfrontChip() == nullptr) {
                    getSeXmtr()->play3D(SE_FIRE);
                }
            } else {
                pPhase->change(PHASE_CLOSE);
            }
            break;
        }
        case PHASE_CLOSE: {
            //１サイクルレーザー打ち切った
            getMorpher()->transitionLinearUntil(1, 0.0, 60); //閉じる
            pPhase->change(PHASE_MOVE);
            break;
        }

        default: {
            break;
        }
    }
    pLocusVehicle->behave();
    getMorpher()->behave();
    getSeXmtr()->behave();
    getAlphaFader()->behave();
}

void EnemyHalia::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHalia::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    if (getMorphWeight(1) > 0.3) { //口が空いてたら
        VvEnemyActor<DefaultMassMorphMeshActor>::onHit(prm_pThisHitChecker, prm_pOppHitChecker);
    } else {
        getSeXmtr()->play3D(SE_UNDAMAGED);
    }
}

void EnemyHalia::onInactive() {
    //sayonara();
}

EnemyHalia::~EnemyHalia() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
