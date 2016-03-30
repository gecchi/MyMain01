#include "MgrCameraViewPoint.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

MgrCameraViewPoint::MgrCameraViewPoint(const char* prm_name) :
        DefaultCameraViewPoint(prm_name) {
    _class_name = "MgrCameraViewPoint";
}

MgrCameraViewPoint::~MgrCameraViewPoint() {
}
