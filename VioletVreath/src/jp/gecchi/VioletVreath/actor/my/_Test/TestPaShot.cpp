#include "TestPaShot.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TestPaShot::TestPaShot(const char* prm_name) :
        SingleLaser(prm_name, "TestPaShot", STATUS(TestPaShot)) {
    _class_name = "TestPaShot";
}

void TestPaShot::initialize() {
    setHitAble(false);
    setAlpha(0.99);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -PX_C(30), -PX_C(30), -PX_C(30),
                                    PX_C(30),  PX_C(30),  PX_C(30));
}

void TestPaShot::onActive() {
    getStatus()->reset();
    setHitAble(true);
    getKuroko()->setMvVelo(PX_C(30));
}

void TestPaShot::processBehavior() {
    getKuroko()->behave();
}

void TestPaShot::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestPaShot::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}

TestPaShot::~TestPaShot() {
}
