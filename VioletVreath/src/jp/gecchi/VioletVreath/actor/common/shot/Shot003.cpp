#include "Shot003.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
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
    useZBufferDrawing(true);   //描画時、Zバッファ値は考慮される
    setZBufferWriteEnable(false); //自身のZバッファを書き込みしない
    effectBlendOne();       //加算合成
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
}

void Shot003::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    getLocusVehicle()->setMvVelo(20000);

}

void Shot003::processBehavior() {
    //加算ランクポイントを減少
    //座標に反映
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->behave();
}

void Shot003::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot003::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
//    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)(prm_pOppHitChecker->_pActor);
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
