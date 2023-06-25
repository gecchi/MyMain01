#include "VvvCamera.h"

#include "VvvCameraViewPoint.h"
#include "VvvCameraUpVector.h"

using namespace GgafLib;
using namespace VVViewer;

VvvCamera::VvvCamera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "VvvCamera";
}

GgafDx::CameraViewPoint* VvvCamera::createCameraViewPoint() {
    VvvCameraViewPoint* pVP = NEW VvvCameraViewPoint("VvvCameraViewPoint");
    return (GgafDx::CameraViewPoint*)pVP;
}

GgafDx::CameraUpVector* VvvCamera::createCameraUpVector() {
    VvvCameraUpVector* pUp = NEW VvvCameraUpVector("VvvCameraUpVector");
    return (GgafDx::CameraUpVector*)pUp;
}

VvvCamera::~VvvCamera() {
}
