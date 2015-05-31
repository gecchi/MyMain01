#include "AliceShot.h"

#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

AliceShot::AliceShot(const char* prm_name, const char* prm_model_id) :
        SingleLaser(prm_name, prm_model_id, STATUS(AliceShot)) { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaserは最大27セットである
    _class_name = "AliceShot";
}

void AliceShot::initialize() {
    setHitAble(false);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, PX_C(16));
}
void AliceShot::onReset() {
    setAlpha(0.99); //半透明にすることで両面レンダリング
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setRollFaceAngVelo(D_ANG(3));
    pKuroko->linkFaceAngByMvAng(true);
}

void AliceShot::onActive() {
    setHitAble(true, false);
    GgafDxKuroko* const pKuroko = getKuroko();
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

void AliceShot::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        sayonara();
    } else {
    }
}

AliceShot::~AliceShot() {
}
