#include "ViewPointGuide.h"

#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"
#include "jp/gecchi/VioletVreath/God.h"



using namespace GgafLib;
using namespace VioletVreath;

ViewPointGuide::ViewPointGuide(const char* prm_name)
               : DefaultD3DXMeshActor(prm_name, "Gizmo") {
    _class_name = "ViewPointGuide";
    setHitAble(false);
}

void ViewPointGuide::initialize() {
}

void ViewPointGuide::onReset() {
}

void ViewPointGuide::onActive() {
}

void ViewPointGuide::processBehavior() {
    Camera* pCam = pGOD->getSpacetime()->getCamera();
    setPositionAt(pCam->getCameraViewPoint());
}

void ViewPointGuide::processJudgement() {
}

void ViewPointGuide::onInactive() {
}

void ViewPointGuide::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

ViewPointGuide::~ViewPointGuide() {
}
