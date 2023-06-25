#include "TestCamWorker.h"

#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"



using namespace GgafLib;
using namespace VioletVreath;

TestCamWorker::TestCamWorker(const char* prm_name, Camera* prm_pCamera) : DefaultCamWorker(prm_name, (DefaultCamera*)prm_pCamera) {
    _class_name = "TestCamWorker";
}

void TestCamWorker::onActive() {

}

void TestCamWorker::onSwitchCameraWork() {
    Camera* pCam = pCARETAKER->getSpacetime()->getCamera();
    pCam->setPositionAt(pMYSHIP);
    GgafDx::GeometricActor* pVP = pCam->getCameraViewPoint();
    pVP->setPositionAt(pMYSHIP);
}

void TestCamWorker::processBehavior() {
    Camera* pCam = pCARETAKER->getSpacetime()->getCamera();
    GgafDx::GeometricActor* pVP = pCam->getCameraViewPoint();
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
