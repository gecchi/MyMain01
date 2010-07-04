#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyShot001::MyShot001(const char* prm_name) :
        SingleLaser(prm_name, "27/MyShot001") { //SingleLaserは最大27セットである
    _class_name = "MyShot001";
    MyStgUtil::resetMyShot001Status(_pStatus);
}

void MyShot001::initialize() {
    setHitAble(false);
    _SX = _SY = _SZ = 50 * 1000;
    setAlpha(0.99); //半透明にすることで両面レンダリング
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void MyShot001::onActive() {
    setHitAble(true);
    _pMover->setMvVelo(50000);             //移動速度
}

void MyShot001::processBehavior() {
    //加算ランクポイントを減少
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //弾なので不要

    //座標に反映
    _pMover->behave();
}

void MyShot001::processJudgement() {
    if (isOutOfGameSpace()) {
        sayonara();
    }
}

void MyShot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
//    //・・・ココにヒットされたエフェクト
    if (MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
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


void MyShot001::drawHitArea() {
    CubeEx::get()->drawHitarea(_pCollisionChecker); SphereEx::get()->drawHitarea(_pCollisionChecker);
}
MyShot001::~MyShot001() {
}
