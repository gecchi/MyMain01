#include "EnemyStraeaLaserChip001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafLib;
using namespace VioletVreath;

EnemyStraeaLaserChip001::EnemyStraeaLaserChip001(const char* prm_name) :
        VvEnemyActor<HomingLaserChip>(prm_name, "StraeaLaserChip001", StatusReset(EnemyStraeaLaserChip001)) {
    _class_name = "EnemyStraeaLaserChip001";
}

void EnemyStraeaLaserChip001::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
}

void EnemyStraeaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setMvVelo(10000);
    pLocusVehicle->setMvAcce(400);
    pLocusVehicle->linkFaceAngByMvAng(true);
}

void EnemyStraeaLaserChip001::processBehaviorHeadChip() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    if (getActiveFrame() == 40) {
        pLocusVehicle->turnMvAngTwd(pMYSHIP,
                              7000, 0,
                              TURN_ANTICLOSE_TO, false);
    }
    if (!pLocusVehicle->isTurningMvAng()) {
        pLocusVehicle->turnMvAngTwd(pMYSHIP,
                              100, 0,
                              TURN_CLOSE_TO, false);
    }
//
//    if (frame_of_behaving_from_onActive_ == 35) {
//        pLocusVehicle->turnMvAngTwd(
//                    pMYSHIP,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    pLocusVehicle->behave();
}

void EnemyStraeaLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

EnemyStraeaLaserChip001::~EnemyStraeaLaserChip001() {

}

