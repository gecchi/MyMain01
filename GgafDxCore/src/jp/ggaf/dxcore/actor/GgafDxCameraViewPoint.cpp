#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCameraViewPoint::GgafDxCameraViewPoint() :
        GgafDxGeometricActor("ViewPoint", nullptr, nullptr) {
    _class_name = "GgafDxCameraViewPoint";
    _X_prev = 0;
    _Y_prev = 0;
    _Z_prev = 0;
    _offset_frames = 0;
}

void GgafDxCameraViewPoint::initialize() {
    _pKurokoA->setMvVelo(0);
}

void GgafDxCameraViewPoint::processBehavior() {
    _X_prev = _X;
    _Y_prev = _Y;
    _Z_prev = _Z;
}

bool GgafDxCameraViewPoint::isMoving() {
    if (_X_prev == _X && _Y_prev == _Y && _Z_prev == _Z) {
        return false;
    } else {
        return true;
    }
}

GgafDxCameraViewPoint::~GgafDxCameraViewPoint() {
}
