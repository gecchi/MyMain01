#include "stdafx.h"
#include "ViewPointGuide.h"

#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/actor/Camera.h"

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
    locateAs(P_CAM->_pViewPoint);
}

void ViewPointGuide::processJudgement() {
}

void ViewPointGuide::onInactive() {
}

void ViewPointGuide::onHit(GgafActor* prm_pOtherActor) {
}

ViewPointGuide::~ViewPointGuide() {
}
