#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot004::Shot004(const char* prm_name) :
        SingleLaser(prm_name, "Shot004") { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaserは最大27セットである
    _class_name = "Shot004";
    _view_in = false;
    MyStgUtil::resetShot004Status(_pStatus);
}

void Shot004::initialize() {
    setHitAble(false);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);

}
void Shot004::onReset() {
    setScaleRate(100.0);
    setAlpha(0.99); //半透明にすることで両面レンダリング
    _pKurokoA->setMvVelo(40000);             //移動速度
    _pKurokoA->setMvAcce(1000);             //移動速度
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void Shot004::onActive() {
    setHitAble(true, false);
    _view_in = false;
}

void Shot004::processBehavior() {
    //加算ランクポイントを減少
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //弾なので不要

    //座標に反映
    _pKurokoA->behave();
}

void Shot004::processJudgement() {
    if (isOutOfView()) {
        if (_view_in) {
            sayonara();
        }
        if (getActivePartFrame() > 60) {
            sayonara();
        }
    } else {
        _view_in = true;
    }
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot004::onHit(GgafActor* prm_pOtherActor) {
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


void Shot004::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pCollisionChecker); ColliAAPrismActor::get()->drawHitarea(_pCollisionChecker); ColliSphereActor::get()->drawHitarea(_pCollisionChecker);
}
Shot004::~Shot004() {
}
