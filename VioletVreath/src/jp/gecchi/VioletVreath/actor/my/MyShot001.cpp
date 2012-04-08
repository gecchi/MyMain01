#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyShot001::MyShot001(const char* prm_name) :
        SingleLaser(prm_name, "MyShot001", STATUS(MyShot001)) { //SingleLaserは最大27セットである
    _class_name = "MyShot001";
}

void MyShot001::initialize() {
    setHitAble(false);
    _SX = R_SC(45);
    _SY = _SZ = R_SC(35);
    setBoundingSphereRadiusRate(45.0f);
    setAlpha(0.99); //半透明にすることで両面レンダリング
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -PX_C(50), -PX_C(50), -PX_C(50),
                                    PX_C(50),  PX_C(50),  PX_C(50));
    _pKurokoA->setFaceAngVelo(AXIS_X, D_ANG(12));
}

void MyShot001::onActive() {
    setHitAble(true);
    _pKurokoA->setMvVelo(PX_C(70));             //移動速度
    _pKurokoA->setMvAcce(100);
}

void MyShot001::processBehavior() {
    //加算ランクポイントを減少
    //_pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //弾なので不要

    //座標に反映
    //if (onChangeToActive()) {

    //} else {
        _pKurokoA->behave();
    //}
}

void MyShot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void MyShot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //if (MyStgUtil::calcMyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
        if (pExplo001) {
            pExplo001->locatedBy(this);
        }
        sayonara();
    //}
}


void MyShot001::drawHitArea() {
    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
}
MyShot001::~MyShot001() {
}
