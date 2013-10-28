#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCameraViewPoint::GgafDxCameraViewPoint() :
        GgafDxGeometricActor("ViewPoint", nullptr, nullptr) {
    _class_name = "GgafDxCameraViewPoint";
    _x_prev = 0;
    _y_prev = 0;
    _z_prev = 0;
    _offset_frames = 0;
}

void GgafDxCameraViewPoint::initialize() {
    _pKurokoA->setMvVelo(0);
}

void GgafDxCameraViewPoint::processBehavior() {
    _x_prev = _x;
    _y_prev = _y;
    _z_prev = _z;
}

bool GgafDxCameraViewPoint::isMoving() {
    if (_x_prev == _x && _y_prev == _y && _z_prev == _z) {
        return false;
    } else {
        return true;
    }
}

GgafDxCameraViewPoint::~GgafDxCameraViewPoint() {
}
