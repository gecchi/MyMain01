#include "CameraUpVector.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CameraUpVector::CameraUpVector(const char* prm_name) :
        DefaultCameraUpVector(prm_name) {
    _class_name = "CameraUpVector";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    up_dir_ = DIR26(0,1,0);
    _x = 0;
    _y = PX_C(1);
    _z = 0;
}

void CameraUpVector::processBehavior() {
    DefaultCameraUpVector::processBehavior();
    pAxsMver_->behave();
    getKuroko()->behave();
}

void CameraUpVector::moveTo(dir26 prm_dir_no, frame prm_spent) {
    dxcoord up_x, up_y, up_z;
    GgafDx26DirectionUtil::cnvDirNo2Vec(prm_dir_no, up_x, up_y, up_z);
    pAxsMver_->asst()->slideVxyzMvByDtTo(DX_C(up_x), DX_C(up_y), DX_C(up_z), prm_spent, 0.3, 0.4, 0, true);
    up_dir_ = prm_dir_no;
}
void CameraUpVector::moveTo(coord tx, coord ty, coord tz, frame prm_spent) {
    pAxsMver_->asst()->slideVxyzMvByDtTo(tx, ty, tz, prm_spent, 0.3, 0.4, 0, true);
    up_dir_ = GgafDx26DirectionUtil::cnvVec2DirNo(C_DX(tx), C_DX(ty), C_DX(tz));
}
CameraUpVector::~CameraUpVector() {
    GGAF_DELETE(pAxsMver_);
}
