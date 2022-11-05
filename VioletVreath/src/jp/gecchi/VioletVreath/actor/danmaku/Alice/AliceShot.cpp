#include "AliceShot.h"

#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;
using namespace VioletVreath;

AliceShot::AliceShot(const char* prm_name, const char* prm_model) :
        VvEnemyActor<SingleLaser>(prm_name, prm_model, StatusReset(AliceShot)) { //SingleLaser�͍ő�27�Z�b�g�ł���
        //SingleLaser(prm_name, "27,laser_single") { //SingleLaser�͍ő�27�Z�b�g�ł���
    _class_name = "AliceShot";
}

void AliceShot::initialize() {
    setHitAble(false);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}
void AliceShot::onReset() {
    setCullingDraw(false);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setRollFaceAngVelo(D_ANG(3));
    pVecVehicle->linkFaceAngByMvAng(true);
}

void AliceShot::onActive() {
    setHitAble(true, false);
    getStatus()->reset();
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setRyMvAng(D90ANG);
    pVecVehicle->setRzMvAngVelo(D_ANG(1));
}

void AliceShot::processBehavior() {
    //���W�ɔ��f
    getVecVehicle()->behave();
}

void AliceShot::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void AliceShot::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        sayonara();
    } else {
    }
}

AliceShot::~AliceShot() {
}
