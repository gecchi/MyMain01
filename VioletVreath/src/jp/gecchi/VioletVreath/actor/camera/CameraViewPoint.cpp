#include "CameraViewPoint.h"

using namespace GgafLib;
using namespace VioletVreath;

CameraViewPoint::CameraViewPoint(const char* prm_name) :
        DefaultCameraViewPoint(prm_name) {
    _class_name = "CameraViewPoint";
}

CameraViewPoint::~CameraViewPoint() {
}
