#include "AniTest3.h"

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

AniTest3::AniTest3(const char* prm_name) :
        DefaultSkinAniMeshActor(prm_name, "tiny_4anim") { //"tiny" "Captain" "tiny_4anim"
    _class_name = "AniTest3";
    setScaleR(0.1);
    //setMaterialColor(0.4, 1.0, 0.6);
}

void AniTest3::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 2.0);
}

void AniTest3::initialize() {
}

void AniTest3::onActive() {
}

void AniTest3::processBehavior() {
    getLocusVehicle()->behave();
    _pPuppeteer->behave();
}

void AniTest3::processJudgement() {
}

void AniTest3::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
}

void AniTest3::onInactive() {
}

AniTest3::~AniTest3() {
}



