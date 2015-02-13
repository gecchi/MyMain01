#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultCameraUpVector::DefaultCameraUpVector(const char* prm_name) : GgafDxCameraUpVector(prm_name) {
    _class_name = "DefaultCameraUpVector";
}

DefaultCameraUpVector::~DefaultCameraUpVector() {
}
