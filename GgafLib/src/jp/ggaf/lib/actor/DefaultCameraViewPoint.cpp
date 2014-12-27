#include "jp/ggaf/lib/actor/DefaultCameraViewPoint.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultCameraViewPoint::DefaultCameraViewPoint(const char* prm_name) : GgafDxCameraViewPoint(prm_name) {
    _class_name = "DefaultCameraViewPoint";
}

DefaultCameraViewPoint::~DefaultCameraViewPoint() {
}
