#include "stdafx.h"
#include "TestNomalShot.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TestNomalShot::TestNomalShot(const char* prm_name) :
        SingleLaser(prm_name, "TestNomalShot", STATUS(TestNomalShot)) {
    _class_name = "TestNomalShot";
}

void TestNomalShot::initialize() {
    setHitAble(false);
    setAlpha(0.99);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -PX_C(30), -PX_C(30), -PX_C(30),
                                    PX_C(30),  PX_C(30),  PX_C(30));
}

void TestNomalShot::onActive() {
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setMvVelo(PX_C(30));
}

void TestNomalShot::processBehavior() {
    _pKurokoA->behave();
}

void TestNomalShot::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void TestNomalShot::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}

TestNomalShot::~TestNomalShot() {
}
