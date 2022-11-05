#include "Shot003.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"

using namespace GgafLib;
using namespace VioletVreath;

Shot003::Shot003(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "laser_single", StatusReset(Shot003)) {
    _class_name = "Shot003";
}

void Shot003::initialize() {
    setHitAble(false);
    _sx = _sy = _sz = R_SC(50);
    setCullingDraw(false);
    setZEnableDraw(true);   //描画時、Zバッファ値は考慮される
    setZWriteEnable(false); //自身のZバッファを書き込みしない
    effectBlendOne();       //加算合成
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}

void Shot003::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    getVecVehicle()->setMvVelo(20000);

}

void Shot003::processBehavior() {
    //加算ランクポイントを減少
    //座標に反映
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->behave();
}

void Shot003::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot003::onHit(const GgafCore::Actor* prm_pOtherActor) {
//    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
//    //・・・ココにヒットされたエフェクト
//    if (MyStgUtil::calcEnemyStamina(this, pOther) <= 0) {
//        //破壊された場合
//        //・・・ココに破壊されたエフェクト
//        EffectExplosion003* pExplo003 = (EffectExplosion003*)pCOMMON_SCENE->pDepo_EffectExplosion003_->dispatch();
//        playSe3D1();
//        if (pExplo003) {
//            pExplo003->setPositionAt(this);
//        }
//        sayonara();
//    }
}

Shot003::~Shot003() {
}
