#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot003::Shot003(const char* prm_name) : DefaultMeshSetActor(prm_name, "laser_single") {
    _class_name = "Shot003";
    MyStgUtil::resetShot003Status(_pStatus);
}

void Shot003::initialize() {
    setHitAble(false);
    _SX = _SY = _SZ = 50 * 1000;
    setAlpha(0.99); //半透明にすることで両面レンダリング
    changeEffectTechnique("DestBlendOne"); //加算合成
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void Shot003::onActive() {
    setHitAble(true);
    _pKuroko->setMvVelo(20000);             //移動速度

}

void Shot003::processBehavior() {
    //加算ランクポイントを減少
    //座標に反映
    _pKuroko->behave();
}

void Shot003::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot003::onHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //・・・ココにヒットされたエフェクト
//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //破壊された場合
//        //・・・ココに破壊されたエフェクト
//        EffectExplosion003* pExplo003 = (EffectExplosion003*)P_COMMON_SCENE->_pDispatcher_EffectExplosion003->employ();
//        playSe3D1();
//        if (pExplo003) {
//            pExplo003->activate();
//            pExplo003->setCoordinateBy(this);
//        }
//        sayonara();
//    }
}

Shot003::~Shot003() {
}
