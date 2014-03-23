#include "stdafx.h"
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
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -PX_C(30), -PX_C(30), -PX_C(30),
                                    PX_C(30),  PX_C(30),  PX_C(30));
}

void TestPaShot::onActive() {
    _pStatus->reset();
    setHitAble(true);
    getKuroko()->setMvVelo(PX_C(30));
}

void TestPaShot::processBehavior() {
    getKuroko()->behave();
}

void TestPaShot::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void TestPaShot::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}

TestPaShot::~TestPaShot() {
}
