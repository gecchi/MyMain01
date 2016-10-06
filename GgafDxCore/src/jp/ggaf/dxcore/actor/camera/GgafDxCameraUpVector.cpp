#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraUpVector.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCameraUpVector::GgafDxCameraUpVector(const char* prm_name) :
        GgafDxGeometricActor(prm_name, nullptr, nullptr) {
    _class_name = "GgafDxCameraUpVector";
}

void GgafDxCameraUpVector::locateByFaceNo(dir26 prm_face_no) {
    float out_vx, out_vy, out_vz;
    GgafDx26DirectionUtil::cnvDirNo2Vec(prm_face_no, out_vx, out_vy, out_vz);
    locate(DX_C(out_vx), DX_C(out_vy), DX_C(out_vz));
}

GgafDxCameraUpVector::~GgafDxCameraUpVector() {
}
