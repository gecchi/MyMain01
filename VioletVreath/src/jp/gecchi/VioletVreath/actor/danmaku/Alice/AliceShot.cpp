#include "AliceShot.h"

#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;
using namespace VioletVreath;

AliceShot::AliceShot(const char* prm_name, const char* prm_model) :
        VvEnemyActor<SingleLaser>(prm_name, prm_model, StatusReset(AliceShot)) { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27,laser_single") { //SingleLaserは最大27セットである
    _class_name = "AliceShot";
}

void AliceShot::initialize() {
    setHitAble(false);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}

void AliceShot::onReset() {
    setCullingDraw(false);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRollFaceAngVelo(D_ANG(3));
    pLocusVehicle->linkFaceAngByMvAng(true);
}

void AliceShot::onActive() {
    setHitAble(true, false);
    getStatus()->reset();
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRyMvAng(D90ANG);
    pLocusVehicle->setRzMvAngVelo(D_ANG(1));
}

void AliceShot::processBehavior() {
    //座標に反映
    getLocusVehicle()->behave();
}

void AliceShot::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void AliceShot::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        sayonara();
    } else {
    }
}

AliceShot::~AliceShot() {
}
