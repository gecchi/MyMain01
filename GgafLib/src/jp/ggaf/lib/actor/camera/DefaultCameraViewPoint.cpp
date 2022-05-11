#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"

#include "jp/ggaf/dx/actor/supporter/AxisVehicle.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/AxisVehicleAssistantA.h"



using namespace GgafLib;

DefaultCameraViewPoint::DefaultCameraViewPoint(const char* prm_name) : GgafDx::CameraViewPoint(prm_name) {
    _class_name = "DefaultCameraViewPoint";
}

void DefaultCameraViewPoint::initialize() {
}

void DefaultCameraViewPoint::processBehavior() {
    getAxisVehicle()->behave();
    getVecVehicle()->behave();
}

void DefaultCameraViewPoint::slideMvTo(coord tx, coord ty, coord tz, frame t, float prm_p1, float prm_p2) {
    //ƒJƒƒ‰‚Ê‚é‚Á‚ÆˆÚ“®
    getAxisVehicle()->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              prm_p1, prm_p2, 0, true);
}

void DefaultCameraViewPoint::slideMvTo(GgafDx::GeometricActor* pTarget, frame t, float prm_p1, float prm_p2) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t, prm_p1, prm_p2);
}

DefaultCameraViewPoint::~DefaultCameraViewPoint() {
}
