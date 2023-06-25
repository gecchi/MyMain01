#include "VvvCameraUpVector.h"

using namespace GgafLib;
using namespace VVViewer;

VvvCameraUpVector::VvvCameraUpVector(const char* prm_name) :
        DefaultCameraUpVector(prm_name) {
    _class_name = "VvvCameraUpVector";
}

VvvCameraUpVector::~VvvCameraUpVector() {
}
