#include "TestGuShot.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

TestGuShot::TestGuShot(const char* prm_name) :
        SingleLaser(prm_name, "TestGuShot", STATUS(TestGuShot)) {
    _class_name = "TestGuShot";
}

void TestGuShot::initialize() {
    setHitAble(false);
    setCullingDraw(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));

}

void TestGuShot::onActive() {
    getStatus()->reset();
    setHitAble(true);
    getKuroko()->setMvVelo(PX_C(30));
}

void TestGuShot::processBehavior() {
    getKuroko()->behave();
}

void TestGuShot::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void TestGuShot::onHit(const GgafCore::Actor* prm_pOtherActor) {
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara();
}

TestGuShot::~TestGuShot() {
}
