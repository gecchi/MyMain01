#include "TestCamWorker.h"

#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraViewPoint.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TestCamWorker::TestCamWorker(const char* prm_name, Camera* prm_pCamera) : CameraWorker(prm_name, (DefaultCamera*)prm_pCamera) {
    _class_name = "TestCamWorker";
}

void TestCamWorker::onActive() {

}

void TestCamWorker::onSwitchCameraWork() {
    Camera* pCam = pGOD->getSpacetime()->getCamera();
    pCam->setPositionAt(pMYSHIP);
    GgafDxGeometricActor* pVP = pCam->getCameraViewPoint();
    pVP->setPositionAt(pMYSHIP);
}

void TestCamWorker::processBehavior() {
    Camera* pCam = pGOD->getSpacetime()->getCamera();
    GgafDxGeometricActor* pVP = pCam->getCameraViewPoint();
    pVP->setPositionAt(pMYSHIP);
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
