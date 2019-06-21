#include "Shot004.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

Shot004::Shot004(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Shot004", StatusReset(Shot004)) { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27,laser_single") { //SingleLaserは最大27セットである
    _class_name = "Shot004";
    view_in_ = false;
}

void Shot004::initialize() {
    setHitAble(false);
    setZEnableDraw(true);   //描画時、Zバッファ値は考慮される
    setZWriteEnable(false); //自身のZバッファを書き込みしない
    effectBlendOne();       //加算合成
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}
void Shot004::onReset() {
    setScaleR(3.0);
    setCullingDraw(false);
    GgafDx::Rikisha* const pRikisha = callRikisha();
    pRikisha->setRollFaceAngVelo(D_ANG(3));
    pRikisha->setMvVelo(30000);
    pRikisha->setMvAcce(1000);
    pRikisha->linkFaceAngByMvAng(true);
}

void Shot004::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004::processBehavior() {
    //弾なので不要

    //座標に反映
    callRikisha()->behave();
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

void Shot004::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

Shot004::~Shot004() {
}
