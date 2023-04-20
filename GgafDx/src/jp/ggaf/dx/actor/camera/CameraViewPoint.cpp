#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"


using namespace GgafDx;

CameraViewPoint::CameraViewPoint(const char* prm_name) :
        GeometricActor(prm_name, nullptr) {
    _class_name = "CameraViewPoint";
}


CameraViewPoint::~CameraViewPoint() {
}
