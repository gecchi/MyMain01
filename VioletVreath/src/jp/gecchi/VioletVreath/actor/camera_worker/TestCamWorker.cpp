#include "stdafx.h"
#include "TestCamWorker.h"

#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TestCamWorker::TestCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "TestCamWorker";
}

void TestCamWorker::onActive() {

}

void TestCamWorker::onSwitchCameraWork() {
    P_CAM->locateAs(P_MYSHIP);
    GgafDxGeometricActor* pVP = P_CAM->_pViewPoint;
    pVP->locateAs(P_MYSHIP);
}

void TestCamWorker::processBehavior() {
    GgafDxGeometricActor* pVP = P_CAM->_pViewPoint;
    pVP->locateAs(P_MYSHIP);
    P_CAM->_X += 2000;
    P_CAM->_Y += 2000;
    P_CAM->_Z += 2000;
}

void TestCamWorker::processJudgement() {
}

void TestCamWorker::onInactive() {
}

TestCamWorker::~TestCamWorker() {
}
