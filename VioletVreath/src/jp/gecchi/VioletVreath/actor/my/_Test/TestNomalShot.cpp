#include "TestNomalShot.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

TestNomalShot::TestNomalShot(const char* prm_name) :
        SingleLaser(prm_name, "TestNomalShot") {
    _class_name = "TestNomalShot";
    getStatus()->reset(statusResetFunction(TestNomalShot));
}

void TestNomalShot::initialize() {
    setHitAble(false);
    setCullingDraw(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
}

void TestNomalShot::onActive() {
    getStatus()->reset();
    setHitAble(true);
    getKuroko()->setMvVelo(PX_C(30));
}

void TestNomalShot::processBehavior() {
    getKuroko()->behave();
}

void TestNomalShot::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestNomalShot::onHit(const GgafCore::Actor* prm_pOtherActor) {
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}

TestNomalShot::~TestNomalShot() {
}
