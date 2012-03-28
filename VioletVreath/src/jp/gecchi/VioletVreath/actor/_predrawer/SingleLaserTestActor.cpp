#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

SingleLaserTestActor::SingleLaserTestActor(const char* prm_name) :
        SingleLaser(prm_name, "_chk_SingleLaserTestModel", NULL) { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaserは最大27セットである
    _class_name = "SingleLaserTestActor";
}

void SingleLaserTestActor::initialize() {
    setHitAble(false);
//    _pColliChecker->makeCollision(1);
//    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);

}
void SingleLaserTestActor::onReset() {
//    setScaleR(100.0);
    setAlpha(0.99); //半透明にすることで両面レンダリング
//    _pKurokoA->setMvVelo(40000);             //移動速度
//    _pKurokoA->setMvAcce(1000);             //移動速度
//    _pKurokoA->relateFaceAngWithMvAng(true);
}

void SingleLaserTestActor::onActive() {
    setHitAble(true, false);
}

void SingleLaserTestActor::processBehavior() {
    //加算ランクポイントを減少
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //弾なので不要

    //座標に反映
//    _pKurokoA->behave();
}

void SingleLaserTestActor::processJudgement() {
//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void SingleLaserTestActor::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
////    //・・・ココにヒットされたエフェクト
//    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //破壊された場合
//        //・・・ココに破壊されたエフェクト
//        EffectExplosion001* pExplo001 = getFromCommon(EffectExplosion001);
//        if (pExplo001) {
//            pExplo001->locatedBy(this);
//        }
//        sayonara();
//    }
}


SingleLaserTestActor::~SingleLaserTestActor() {
}
