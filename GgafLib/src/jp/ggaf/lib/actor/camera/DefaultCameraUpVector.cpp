#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"

#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicleAssistantA.h"
#include "jp/ggaf/lib/util/Direction26Util.h"



using namespace GgafLib;

DefaultCameraUpVector::DefaultCameraUpVector(const char* prm_name) : GgafDx::CameraUpVector(prm_name) {
    _class_name = "DefaultCameraUpVector";
    up_dir_ = DIR26(0,1,0);
}

void DefaultCameraUpVector::processBehavior() {
    getCoordVehicle()->behave();
    getLocoVehicle()->behave();
}

//void DefaultCameraUpVector::moveTo(dir26 prm_dir_no, frame prm_spent) {
//    _TRACE_("moveTo dir26 ("<<prm_dir_no<<") prm_spent="<<prm_spent);
//    dxcoord up_x, up_y, up_z;
//    Direction26Util::cnvDirNo2Vec(prm_dir_no, up_x, up_y, up_z);
//    getCoordVehicle()->asst()->slideVxyzMvByDtTo(DX_C(up_x), DX_C(up_y), DX_C(up_z), prm_spent, 0.3, 0.4, 0, true);
//    up_dir_ = prm_dir_no;
//}

void DefaultCameraUpVector::slideMvTo(coord tx, coord ty, coord tz, frame prm_spent, float prm_p1, float prm_p2) {
    getCoordVehicle()->asst()->slideVxyzMvByDtTo(tx, ty, tz, prm_spent, prm_p1, prm_p2, 0, true);
    up_dir_ = Direction26Util::cnvVec2DirNo(C_DX(tx), C_DX(ty), C_DX(tz));
}

DefaultCameraUpVector::~DefaultCameraUpVector() {
}
