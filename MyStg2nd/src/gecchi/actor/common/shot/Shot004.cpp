#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot004::Shot004(const char* prm_name) :
        SingleLaser(prm_name, "27/laser_single") { //SingleLaserは最大27セットである
    _class_name = "Shot004";
    MyStgUtil::resetShot004Status(_pStatus);
}

void Shot004::initialize() {
    setHitAble(false);
    _SX = _SY = _SZ = 50 * 1000;
    setAlpha(0.99); //半透明にすることで両面レンダリング
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -30000, -30000, 30000, 30000);
}

void Shot004::onActive() {
    setHitAble(true);
    _pMover->setMvVelo(15000);             //移動速度
}

void Shot004::processBehavior() {
    //加算ランクポイントを減少
    //座標に反映
    _pMover->behave();
}

void Shot004::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void Shot004::onHit(GgafActor* prm_pOtherActor) {
//    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //・・・ココにヒットされたエフェクト
//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //破壊された場合
//        //・・・ココに破壊されたエフェクト
//        EffectExplosion003* pExplo003 = (EffectExplosion003*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion003->employ();
//        playSe3D1();
//        if (pExplo003 != NULL) {
//            pExplo003->activate();
//            pExplo003->setGeometry(this);
//        }
//        inactivate();
//    }
}


void Shot004::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}
Shot004::~Shot004() {
}
