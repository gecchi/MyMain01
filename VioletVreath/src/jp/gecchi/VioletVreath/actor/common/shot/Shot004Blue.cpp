#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot004Blue::Shot004Blue(const char* prm_name) :
        SingleLaser(prm_name, "Shot004Blue", STATUS(Shot004)) { //SingleLaserは最大27セットである
        //SingleLaser(prm_name, "27/laser_single") { //SingleLaserは最大27セットである
    _class_name = "Shot004Blue";
    view_in_ = false;
}

void Shot004Blue::initialize() {

    setHitAble(false);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}
void Shot004Blue::onReset() {
    setScaleR(3.0);
    setAlpha(0.99); //半透明にすることで両面レンダリング
    _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(3));
    _pKurokoA->setMvVelo(40000);             //移動速度
    _pKurokoA->setMvAcce(1000);             //移動速度
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void Shot004Blue::onActive() {
    setHitAble(true, false);
    view_in_ = false;
}

void Shot004Blue::processBehavior() {
    //加算ランクポイントを減少
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //弾なので不要

    //座標に反映
    _pKurokoA->behave();
}

void Shot004Blue::processJudgement() {
    if (isOutOfView()) {
        if (view_in_) {
            sayonara();
        }
        if (getActivePartFrame() > 60) {
            sayonara();
        }
    } else {
        view_in_ = true;
    }
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot004Blue::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //・・・ココにヒットされたエフェクト
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //破壊された場合
        //・・・ココに破壊されたエフェクト
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locateWith(this);
        }
        sayonara();
    }
}


void Shot004Blue::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}
Shot004Blue::~Shot004Blue() {
}
