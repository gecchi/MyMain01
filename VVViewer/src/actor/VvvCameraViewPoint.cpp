#include "VvvCameraViewPoint.h"

using namespace GgafLib;
using namespace VVViewer;

VvvCameraViewPoint::VvvCameraViewPoint(const char* prm_name) :
        DefaultCameraViewPoint(prm_name) {
    _class_name = "VvvCameraViewPoint";
}

VvvCameraViewPoint::~VvvCameraViewPoint() {
}
