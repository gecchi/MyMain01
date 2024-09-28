#include "jp/ggaf/dx/actor/camera/CameraUpVector.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"


using namespace GgafDx;

CameraUpVector::CameraUpVector(const char* prm_name) :
        GeometricActor(prm_name) {
    _class_name = "CameraUpVector";
}

CameraUpVector::~CameraUpVector() {
}
