#include "Camera.h"

#include "CameraUpVector.h"
#include "CameraViewPoint.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Camera::Camera(const char* prm_name) :
        DefaultCamera(prm_name, 2*PI * 90.0 / 360.0) { //かなり横長画面なので視野角90〜100度ぐらい
    _class_name = "Camera";
}

GgafDxCameraViewPoint* Camera::createCameraViewPoint() {
    CameraViewPoint* pVP = NEW CameraViewPoint("CameraViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}

void Camera::processBehavior() {
    DefaultCamera::processBehavior();
}

GgafDxCameraUpVector* Camera::createCameraUpVector() {
    CameraUpVector* pUp = NEW CameraUpVector("CameraUpVector");
    return (GgafDxCameraUpVector*)pUp;
}

Camera::~Camera() {
}
