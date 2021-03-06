#include "MgrCamera.h"

#include "MgrCameraUpVector.h"
#include "MgrCameraViewPoint.h"



using namespace GgafLib;
using namespace Mogera;

MgrCamera::MgrCamera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "MgrCamera";
}

GgafDx::CameraViewPoint* MgrCamera::createCameraViewPoint() {
    MgrCameraViewPoint* pVP = NEW MgrCameraViewPoint("MgrCameraViewPoint");
    return (GgafDx::CameraViewPoint*)pVP;
}
GgafDx::CameraUpVector* MgrCamera::createCameraUpVector() {
    MgrCameraUpVector* pUp = NEW MgrCameraUpVector("MgrCameraUpVector");
    return (GgafDx::CameraUpVector*)pUp;
}

MgrCamera::~MgrCamera() {
}
