#include "MgrCamera.h"

#include "MgrCameraUpVector.h"
#include "MgrCameraViewPoint.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

MgrCamera::MgrCamera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "MgrCamera";
}

GgafDxCameraViewPoint* MgrCamera::createCameraViewPoint() {
    MgrCameraViewPoint* pVP = NEW MgrCameraViewPoint("MgrCameraViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}
GgafDxCameraUpVector* MgrCamera::createCameraUpVector() {
    MgrCameraUpVector* pUp = NEW MgrCameraUpVector("MgrCameraUpVector");
    return (GgafDxCameraUpVector*)pUp;
}

MgrCamera::~MgrCamera() {
}
