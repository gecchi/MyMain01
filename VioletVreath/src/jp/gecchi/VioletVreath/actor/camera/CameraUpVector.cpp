#include "CameraUpVector.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CameraUpVector::CameraUpVector(const char* prm_name) :
        DefaultCameraUpVector(prm_name) {
    _class_name = "CameraUpVector";
}

CameraUpVector::~CameraUpVector() {
}
