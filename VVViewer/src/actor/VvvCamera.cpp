#include "VvvCamera.h"

#include "VvvCameraViewPoint.h"
#include "VvvCameraUpVector.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvCamera::VvvCamera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "VvvCamera";
}

GgafDxCameraViewPoint* VvvCamera::createCameraViewPoint() {
    VvvCameraViewPoint* pVP = NEW VvvCameraViewPoint("VvvCameraViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}

GgafDxCameraUpVector* VvvCamera::createCameraUpVector() {
    VvvCameraUpVector* pUp = NEW VvvCameraUpVector("VvvCameraUpVector");
    return (GgafDxCameraUpVector*)pUp;
}

VvvCamera::~VvvCamera() {
}
