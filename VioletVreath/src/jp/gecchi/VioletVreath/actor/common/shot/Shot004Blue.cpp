#include "Shot004Blue.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot004Blue::Shot004Blue(const char* prm_name) :
        SingleLaser(prm_name, "Shot004Blue", STATUS(Shot004)) { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaserは最大27セットである
    _class_name = "Shot004Blue";
    view_in_ = false;
}

void Shot004Blue::initialize() {
    setHitAble(false);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, PX_C(16));
}
void Shot004Blue::onReset() {
    setScaleR(3.0);
    setAlpha(0.99); //半透明にすることで両面レンダリング
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setFaceAngVelo(AXIS_X, D_ANG(3));
    pKuroko->setMvVelo(40000);             //移動速度
    pKuroko->setMvAcce(1000);             //移動速度
    pKuroko->relateFaceByMvAng(true);
}

void Shot004Blue::onActive() {
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004Blue::processBehavior() {
    //加算ランクポイントを減少
    //UTIL::updateEnemyRankPoint(this);
    //弾なので不要

    //座標に反映
    getKuroko()->behave();
}

void Shot004Blue::processJudgement() {
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
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot004Blue::onHit(GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

Shot004Blue::~Shot004Blue() {
}
