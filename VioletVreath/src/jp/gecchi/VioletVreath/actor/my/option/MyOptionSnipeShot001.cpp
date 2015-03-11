#include "MyOptionSnipeShot001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyOptionSnipeShot001::MyOptionSnipeShot001(const char* prm_name) :
        SingleLaser(prm_name, "MyOptionSnipeShot001", STATUS(MyOptionSnipeShot001)) { //SingleLaser‚ÍÅ‘å27ƒZƒbƒg‚Å‚ ‚é
    _class_name = "MyOptionSnipeShot001";
}

void MyOptionSnipeShot001::initialize() {
    setHitAble(false);
    setScaleR(4.0);
    setAlpha(0.99);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB(0, -PX_C(50), -PX_C(50), -PX_C(50),
                              PX_C(50),  PX_C(50),  PX_C(50));
    getKuroko()->setFaceAngVelo(AXIS_X, D_ANG(12));
    getKuroko()->relateFaceByMvAng(true);
}

void MyOptionSnipeShot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
}

void MyOptionSnipeShot001::processBehavior() {
    getKuroko()->behave();
}

void MyOptionSnipeShot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void MyOptionSnipeShot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}


//void MyOptionSnipeShot001::drawHitArea() {
//    ColliAABActor::get()->drawHitarea(_pColliChecker); ColliAAPrismActor::get()->drawHitarea(_pColliChecker); ColliSphereActor::get()->drawHitarea(_pColliChecker);
//}
MyOptionSnipeShot001::~MyOptionSnipeShot001() {
}
