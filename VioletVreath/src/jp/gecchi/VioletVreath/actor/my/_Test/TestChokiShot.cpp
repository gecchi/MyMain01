#include "TestChokiShot.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TestChokiShot::TestChokiShot(const char* prm_name) :
        SingleLaser(prm_name, "TestChokiShot", STATUS(TestChokiShot)) {
    _class_name = "TestChokiShot";
}

void TestChokiShot::initialize() {
    setHitAble(false);
    setCullingDraw(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -PX_C(30), -PX_C(30), -PX_C(30),
                                   PX_C(30),  PX_C(30),  PX_C(30));
}

void TestChokiShot::onActive() {
    getStatus()->reset();
    setHitAble(true);
    getKuroko()->setMvVelo(PX_C(30));
}

void TestChokiShot::processBehavior() {
    getKuroko()->behave();
}

void TestChokiShot::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestChokiShot::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}

TestChokiShot::~TestChokiShot() {
}
