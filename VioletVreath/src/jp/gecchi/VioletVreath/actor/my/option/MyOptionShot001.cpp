#include "MyOptionShot001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyOptionShot001::MyOptionShot001(const char* prm_name) :
        SingleLaser(prm_name, "MyOptionShot001", STATUS(MyOptionShot001)) { //SingleLaser‚ÍÅ‘å27ƒZƒbƒg‚Å‚ ‚é
    _class_name = "MyOptionShot001";
}

void MyOptionShot001::initialize() {
    setHitAble(false);
    _sx = R_SC(45);
    _sy = _sz = R_SC(35);
    setBoundingSphereRadiusRate(45.0f);
    setAlpha(0.99);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB(0, -PX_C(50), -PX_C(50), -PX_C(50),
                              PX_C(50),  PX_C(50),  PX_C(50));
    getKuroko()->setRollFaceAngVelo(D_ANG(-12));
    getKuroko()->linkFaceAngByMvAng(true);
}

void MyOptionShot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
}

void MyOptionShot001::processBehavior() {
    getKuroko()->behave();
}

void MyOptionShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MyOptionShot001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}


//void MyOptionShot001::drawHitArea() {
//    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
//}
MyOptionShot001::~MyOptionShot001() {
}
