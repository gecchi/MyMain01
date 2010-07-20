#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Shot004::Shot004(const char* prm_name) :
        SingleLaser(prm_name, "27/MyShot001") { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaserは最大27セットである
    _class_name = "Shot004";
    MyStgUtil::resetShot004Status(_pStatus);
}

void Shot004::initialize() {
    setHitAble(false);
    _SX = _SY = _SZ = 50 * 1000;
    setAlpha(0.99); //半透明にすることで両面レンダリング
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void Shot004::onActive() {
    setHitAble(true);
    _pMover->setMvVelo(10000);             //移動速度
}

void Shot004::processBehavior() {
    //加算ランクポイントを減少
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //弾なので不要

    //座標に反映
    _pMover->behave();
}

void Shot004::processJudgement() {
    if (isOutOfGameSpace()) {
        sayonara();
    }
}

void Shot004::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setGeometry(this);
        }
        sayonara();
    }
}


void Shot004::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}
Shot004::~Shot004() {
}
