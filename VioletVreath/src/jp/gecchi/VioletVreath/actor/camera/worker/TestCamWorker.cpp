#include "TestCamWorker.h"

#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraViewPoint.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
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
    Camera* pCam = P_GOD->getUniverse()->getCamera();
    pCam->positionAs(P_MYSHIP);
    GgafDxGeometricActor* pVP = pCam->getCameraViewPoint();
    pVP->positionAs(P_MYSHIP);
}

void TestCamWorker::processBehavior() {
    Camera* pCam = P_GOD->getUniverse()->getCamera();
    GgafDxGeometricActor* pVP = pCam->getCameraViewPoint();
    pVP->positionAs(P_MYSHIP);
    pCam->_x += 2000;
    pCam->_y += 2000;
    pCam->_z += 2000;
}

void TestCamWorker::processJudgement() {
}

void TestCamWorker::onInactive() {
}

TestCamWorker::~TestCamWorker() {
}
