#include "stdafx.h"
#include "MyShot001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyShot001::MyShot001(const char* prm_name) :
        SingleLaser(prm_name, "MyShot001", STATUS(MyShot001)) { //SingleLaser‚ÍÅ‘å27ƒZƒbƒg‚Å‚ ‚é
    _class_name = "MyShot001";
}

void MyShot001::initialize() {
    setHitAble(false);
    _sx = R_SC(45);
    _sy = _sz = R_SC(35);
    setBoundingSphereRadiusRate(45.0f);
    setAlpha(0.99);
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliAAB(0, -PX_C(50), -PX_C(50), -PX_C(50),
                                   PX_C(50),  PX_C(50),  PX_C(50));
    getKuroko()->setFaceAngVelo(AXIS_X, D_ANG(12));
    getKuroko()->relateFaceByMvAng(true);
}

void MyShot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
}

void MyShot001::processBehavior() {
    getKuroko()->behave();
}

void MyShot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void MyShot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}


//void MyShot001::drawHitArea() {
//    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
//}
MyShot001::~MyShot001() {
}
