#include "EnemyIrce.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION,
};

EnemyIrce::EnemyIrce(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Eres", StatusReset(EnemyErmione)) {
    _class_name = "EnemyIrce";
    iMovePatternNo_ = 0;
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_EXPLOSION, "SE_EXPLOSION_001");
}

void EnemyIrce::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyIrce::initialize() {
    setHitAble(true);
    setScale(1000);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
    pLocusVehicle->setMvVelo(3000);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAABox(0, -10000, -10000, -10000, 10000, 10000, 10000);
    _x = PX_C(200);
}

void EnemyIrce::onActive() {
    getStatus()->reset();
    iMovePatternNo_ = 0;
}

void EnemyIrce::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->turnMvAngTwd(pMYSHIP,
                          50, 0, TURN_CLOSE_TO, true);
    pLocusVehicle->behave();
    getScaler()->behave();
    //getSeXmtr()->behave();
}


void EnemyIrce::processJudgement() {
//    if (isOutOfSpacetime()) {
//        sayonara();
//    }
}

void EnemyIrce::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        getSeXmtr()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyIrce::onInactive() {
    sayonara();
}

EnemyIrce::~EnemyIrce() {
}
