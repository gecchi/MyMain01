#include "Camera.h"

#include "CameraUpVector.h"
#include "CameraViewPoint.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/VamSysCamWorker.h"



using namespace GgafLib;
using namespace VioletVreath;

Camera::Camera(const char* prm_name) :
        DefaultCamera(prm_name, 2*PI * 90.0 / 360.0) { //���Ȃ艡����ʂȂ̂Ŏ���p90�`100�x���炢
    _class_name = "Camera";
    // VamSysCamWorker::initStatic() �����s���Ă��������E�E�E
    VamSysCamWorker* wk = NEW VamSysCamWorker("WK",this);
    GGAF_DELETE(wk);
}

GgafDx::CameraViewPoint* Camera::createCameraViewPoint() {
    CameraViewPoint* pVP = NEW CameraViewPoint("CameraViewPoint");
    return (GgafDx::CameraViewPoint*)pVP;
}

void Camera::processBehavior() {
    DefaultCamera::processBehavior();
}

GgafDx::CameraUpVector* Camera::createCameraUpVector() {
    CameraUpVector* pUp = NEW CameraUpVector("CameraUpVector");
    return (GgafDx::CameraUpVector*)pUp;
}

Camera::~Camera() {
}
