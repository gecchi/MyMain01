#include "AniTest.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/util/Input.h"

using namespace GgafLib;
using namespace Mogera;

AniTest::AniTest(const char* prm_name) :
        DefaultSkinAniMeshActor(prm_name, "tiny_4anim") {  //"tiny"
//AniTest::AniTest(const char* prm_name) :
//        DefaultBoneAniMeshActor(prm_name, "AnimatedSkelton2") {
    _class_name = "AniTest";
    setScaleR(0.4);
}

void AniTest::onCreateModel() {
}

void AniTest::initialize() {
}

void AniTest::onActive() {
}

void AniTest::processBehavior() {
    getLocoVehicle()->behave();
    _pPuppeteer->behave();
}

void AniTest::processJudgement() {
}

void AniTest::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

void AniTest::onInactive() {
}

AniTest::~AniTest() {
}


