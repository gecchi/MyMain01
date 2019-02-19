#include "AliceShot.h"

#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"

using namespace GgafLib;
using namespace VioletVreath;

AliceShot::AliceShot(const char* prm_name, const char* prm_model_id) :
        VvEnemyActor<SingleLaser>(prm_name, prm_model_id, StatusReset(AliceShot)) { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27,laser_single") { //SingleLaserは最大27セットである
    _class_name = "AliceShot";
}

void AliceShot::initialize() {
    setHitAble(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}
void AliceShot::onReset() {
    setCullingDraw(false);
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->setRollFaceAngVelo(D_ANG(3));
    pKuroko->linkFaceAngByMvAng(true);
}

void AliceShot::onActive() {
    setHitAble(true, false);
    getStatus()->reset();
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->setRyMvAng(D90ANG);
    pKuroko->setRzMvAngVelo(D_ANG(1));
}

void AliceShot::processBehavior() {
    //座標に反映
    getKuroko()->behave();
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
