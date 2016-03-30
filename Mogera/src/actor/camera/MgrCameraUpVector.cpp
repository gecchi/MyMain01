#include "MgrCameraUpVector.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

MgrCameraUpVector::MgrCameraUpVector(const char* prm_name) :
        DefaultCameraUpVector(prm_name) {
    _class_name = "MgrCameraUpVector";
}

MgrCameraUpVector::~MgrCameraUpVector() {
}
