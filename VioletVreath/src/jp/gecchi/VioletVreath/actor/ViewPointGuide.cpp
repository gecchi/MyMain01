#include "ViewPointGuide.h"

#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraViewPoint.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

ViewPointGuide::ViewPointGuide(const char* prm_name)
               : DefaultD3DXMeshActor(prm_name, "Gizmo", nullptr) {
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
    Camera* pCam = P_GOD->getSpacetime()->getCamera();
    locateAs(pCam->getCameraViewPoint());
}

void ViewPointGuide::processJudgement() {
}

void ViewPointGuide::onInactive() {
}

void ViewPointGuide::onHit(const GgafActor* prm_pOtherActor) {
}

ViewPointGuide::~ViewPointGuide() {
}
