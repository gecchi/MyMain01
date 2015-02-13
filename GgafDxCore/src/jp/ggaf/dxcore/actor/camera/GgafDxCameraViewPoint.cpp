#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraViewPoint.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCameraViewPoint::GgafDxCameraViewPoint(const char* prm_name) :
        GgafDxGeometricActor(prm_name, nullptr, nullptr) {
    _class_name = "GgafDxCameraViewPoint";
}


GgafDxCameraViewPoint::~GgafDxCameraViewPoint() {
}
