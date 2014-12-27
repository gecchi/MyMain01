#include "jp/ggaf/dxcore/actor/GgafDxCameraUpVector.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxDirectionUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCameraUpVector::GgafDxCameraUpVector(const char* prm_name) :
        GgafDxGeometricActor(prm_name, nullptr, nullptr) {
    _class_name = "GgafDxCameraUpVector";
}

void GgafDxCameraUpVector::positionByFaceNo(face26 prm_face_no) {
    float out_vx, out_vy, out_vz;
    GgafDxDirectionUtil::cnvFaceNo2Vec(prm_face_no, out_vx, out_vy, out_vz);
    position(DX_C(out_vx), DX_C(out_vy), DX_C(out_vz));
}

GgafDxCameraUpVector::~GgafDxCameraUpVector() {
}
