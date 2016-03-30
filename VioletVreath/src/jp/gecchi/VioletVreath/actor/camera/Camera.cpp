#include "Camera.h"

#include "CameraUpVector.h"
#include "CameraViewPoint.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Camera::Camera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 100.0 / 180.0) { //���Ȃ艡����ʂȂ̂Ŏ���p�P�O�O�x���炢
    _class_name = "Camera";
}

GgafDxCameraViewPoint* Camera::createCameraViewPoint() {
    CameraViewPoint* pVP = NEW CameraViewPoint("CameraViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}
GgafDxCameraUpVector* Camera::createCameraUpVector() {
    CameraUpVector* pUp = NEW CameraUpVector("CameraUpVector");
    return (GgafDxCameraUpVector*)pUp;
}

Camera::~Camera() {
}
