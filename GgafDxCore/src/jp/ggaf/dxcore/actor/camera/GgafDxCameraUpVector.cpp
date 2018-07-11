#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraUpVector.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCameraUpVector::GgafDxCameraUpVector(const char* prm_name) :
        GgafDxGeometricActor(prm_name, nullptr, nullptr) {
    _class_name = "GgafDxCameraUpVector";
}

GgafDxCameraUpVector::~GgafDxCameraUpVector() {
}
