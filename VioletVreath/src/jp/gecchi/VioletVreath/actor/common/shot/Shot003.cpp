#include "stdafx.h"
using namespace std;
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
    _SX = _SY = _SZ = R_SC(50);
    setAlpha(0.99); //半透明にすることで両面レンダリング
    changeEffectTechnique("DestBlendOne"); //加算合成
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void Shot003::onActive() {
    setHitAble(true);
    _pKurokoA->setMvVelo(20000);             //移動速度

}

void Shot003::processBehavior() {
    //加算ランクポイントを減少
    //座標に反映
    _pKurokoA->behave();
}

void Shot003::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot003::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //・・・ココにヒットされたエフェクト
//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //破壊された場合
//        //・・・ココに破壊されたエフェクト
//        EffectExplosion003* pExplo003 = (EffectExplosion003*)P_COMMON_SCENE->pDepo_EffectExplosion003_->dispatch();
//        playSe3D1();
//        if (pExplo003) {
//            pExplo003->locatedBy(this);
//        }
//        sayonara();
//    }
}

Shot003::~Shot003() {
}
