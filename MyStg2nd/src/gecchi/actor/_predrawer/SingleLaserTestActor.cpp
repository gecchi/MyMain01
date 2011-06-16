#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

SingleLaserTestActor::SingleLaserTestActor(const char* prm_name) :
        SingleLaser(prm_name, "_chk_SingleLaserEffectTest") { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaserは最大27セットである
    _class_name = "SingleLaserTestActor";
}

void SingleLaserTestActor::initialize() {
    setHitAble(false);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);

}
void SingleLaserTestActor::onReset() {
    setScaleRate(100.0);
    setAlpha(0.99); //半透明にすることで両面レンダリング
    _pMvNavigator->setMvVelo(40000);             //移動速度
    _pMvNavigator->setMvAcce(1000);             //移動速度
    _pMvNavigator->relateFaceAngWithMvAng(true);
}

void SingleLaserTestActor::onActive() {
    setHitAble(true, false);
}

void SingleLaserTestActor::processBehavior() {
    //加算ランクポイントを減少
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //弾なので不要

    //座標に反映
    _pMvNavigator->behave();
}

void SingleLaserTestActor::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void SingleLaserTestActor::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        sayonara();
    }
}


void SingleLaserTestActor::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}
SingleLaserTestActor::~SingleLaserTestActor() {
}
