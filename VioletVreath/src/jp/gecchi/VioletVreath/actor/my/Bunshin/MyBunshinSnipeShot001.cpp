#include "MyBunshinSnipeShot001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyBunshinSnipeShot001::MyBunshinSnipeShot001(const char* prm_name) :
        SingleLaser(prm_name, "MyBunshinSnipeShot001", STATUS(MyBunshinSnipeShot001)) { //SingleLaser‚ÍÅ‘å27ƒZƒbƒg‚Å‚ ‚é
    _class_name = "MyBunshinSnipeShot001";
}

void MyBunshinSnipeShot001::initialize() {
    setHitAble(false);
    setScaleR(4.0);
    setAlpha(0.99);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -PX_C(50), -PX_C(50), -PX_C(50),
                              PX_C(50),  PX_C(50),  PX_C(50));
    getKuroko()->setRollFaceAngVelo(D_ANG(12));
    getKuroko()->linkFaceAngByMvAng(true);
}

void MyBunshinSnipeShot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
}

void MyBunshinSnipeShot001::processBehavior() {
    getKuroko()->behave();
}

void MyBunshinSnipeShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MyBunshinSnipeShot001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}


//void MyBunshinSnipeShot001::drawHitArea() {
//    CollisionChecker::drawHitArea(_pColliChecker);
//}
MyBunshinSnipeShot001::~MyBunshinSnipeShot001() {
}
