#include "AniTest2.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/Puppeteer.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/dx/model/Model.h"

using namespace GgafLib;
using namespace Mogera;

AniTest2::AniTest2(const char* prm_name) :
        DefaultBoneAniMeshActor(prm_name, "AnimatedSkelton2") {
    _class_name = "AniTest2";
    setScaleR(0.2);
    setMaterialColor(0.4, 1.0, 0.6);
}

void AniTest2::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 2.0);
}

void AniTest2::initialize() {
}

void AniTest2::onActive() {
}

void AniTest2::processBehavior() {
    getLocusVehicle()->behave();
    _pPuppeteer->behave();
}

void AniTest2::processJudgement() {
}

void AniTest2::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

void AniTest2::onInactive() {
}

AniTest2::~AniTest2() {
}



