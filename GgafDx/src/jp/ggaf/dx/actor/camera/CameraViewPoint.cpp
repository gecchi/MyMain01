#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"


using namespace GgafDx;

CameraViewPoint::CameraViewPoint(const char* prm_name) :
        GeometricActor(prm_name, nullptr, nullptr) {
    _class_name = "CameraViewPoint";
}


CameraViewPoint::~CameraViewPoint() {
}
