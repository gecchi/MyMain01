#include "Shot004.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

Shot004::Shot004(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Shot004", StatusReset(Shot004)) {
        //SingleLaser(prm_name, "laser_single") { //SingleLaserは最大26セットである
    _class_name = "Shot004";
    view_in_ = false;
}

void Shot004::initialize() {
    setHitAble(false);
    useZBufferDrawing(true);   //描画時、Zバッファ値は考慮される
    setZBufferWriteEnable(false); //自身のZバッファを書き込みしない
    effectBlendOne();       //加算合成
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}
void Shot004::onReset() {
    setScaleR(3.0);
    setCullingDraw(false);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRollFaceAngVelo(D_ANG(3));
    pLocusVehicle->setMvVelo(30000);
    pLocusVehicle->setMvAcce(1000);
    pLocusVehicle->linkFaceAngByMvAng(true);
}

void Shot004::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004::processBehavior() {
    //弾なので不要

    //座標に反映
    getLocusVehicle()->behave();
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

Shot004::~Shot004() {
}
