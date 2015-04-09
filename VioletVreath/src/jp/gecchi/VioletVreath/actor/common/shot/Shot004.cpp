#include "Shot004.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot004::Shot004(const char* prm_name) :
        SingleLaser(prm_name, "Shot004", STATUS(Shot004)) { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaserは最大27セットである
    _class_name = "Shot004";
    view_in_ = false;
}

void Shot004::initialize() {
    setHitAble(false);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, PX_C(16));
}
void Shot004::onReset() {
    setScaleR(3.0);
    setAlpha(0.99); //半透明にすることで両面レンダリング
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setRollFaceAngVelo(D_ANG(3));
    pKuroko->setMvVelo(30000);
    pKuroko->setMvAcce(1000);
    pKuroko->linkFaceAngByMvAng(true);
}

void Shot004::onActive() {
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004::processBehavior() {
    //加算ランクポイントを減少
    //UTIL::updateEnemyRankPoint(this);
    //弾なので不要

    //座標に反映
    getKuroko()->behave();
}

void Shot004::processJudgement() {
    if (isOutOfView()) {
        if (view_in_) {
            sayonara();
        }
        if (getActiveFrame() > 60) {
            sayonara();
        }
    } else {
        view_in_ = true;
    }
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot004::onHit(const GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

Shot004::~Shot004() {
}
