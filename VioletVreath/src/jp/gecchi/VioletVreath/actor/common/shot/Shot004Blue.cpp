#include "Shot004Blue.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

Shot004Blue::Shot004Blue(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Shot004Blue", StatusReset(Shot004)) { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27,laser_single") { //SingleLaserは最大27セットである
    _class_name = "Shot004Blue";
    view_in_ = false;
}

void Shot004Blue::initialize() {
    setHitAble(false);
    setZEnableDraw(true);   //描画時、Zバッファ値は考慮される
    setZWriteEnable(false); //自身のZバッファを書き込みしない
    effectBlendOne();       //加算合成
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}
void Shot004Blue::onReset() {
    setScaleR(3.0);
    setCullingDraw(false);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setRollFaceAngVelo(D_ANG(3));
    pLocusVehicle->setMvVelo(40000);             //移動速度
    pLocusVehicle->setMvAcce(1000);             //移動速度
    pLocusVehicle->linkFaceAngByMvAng(true);
}

void Shot004Blue::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004Blue::processBehavior() {
    //座標に反映
    getLocusVehicle()->behave();
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
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

Shot004Blue::~Shot004Blue() {
}
