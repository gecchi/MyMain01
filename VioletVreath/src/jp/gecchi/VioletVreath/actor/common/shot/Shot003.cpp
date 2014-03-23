#include "stdafx.h"
#include "Shot003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot003::Shot003(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "laser_single", STATUS(Shot003)) {
    _class_name = "Shot003";
}

void Shot003::initialize() {
    setHitAble(false);
    _sx = _sy = _sz = R_SC(50);
    setAlpha(0.99); //半透明にすることで両面レンダリング
    effectBlendOne(); //加算合成
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, PX_C(16));
}

void Shot003::onActive() {
    setHitAble(true);
    getKuroko()->setMvVelo(20000);

}

void Shot003::processBehavior() {
    //加算ランクポイントを減少
    //座標に反映
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->behave();
}

void Shot003::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot003::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //・・・ココにヒットされたエフェクト
//    if (MyStgUtil::calcEnemyStamina(this, pOther) <= 0) {
//        //破壊された場合
//        //・・・ココに破壊されたエフェクト
//        EffectExplosion003* pExplo003 = (EffectExplosion003*)P_COMMON_SCENE->pDepo_EffectExplosion003_->dispatch();
//        playSe3D1();
//        if (pExplo003) {
//            pExplo003->positionAs(this);
//        }
//        sayonara();
//    }
}

Shot003::~Shot003() {
}
