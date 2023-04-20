#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"

#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleMvAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicleAssistantA.h"



using namespace GgafLib;

DefaultCameraViewPoint::DefaultCameraViewPoint(const char* prm_name) : GgafDx::CameraViewPoint(prm_name) {
    _class_name = "DefaultCameraViewPoint";
}

void DefaultCameraViewPoint::initialize() {
}

void DefaultCameraViewPoint::processBehavior() {
    getCoordVehicle()->behave();
    getLocoVehicle()->behave();
}

void DefaultCameraViewPoint::slideMvTo(coord tx, coord ty, coord tz, frame t, double prm_p1, double prm_p2) {
    //ƒJƒƒ‰‚Ê‚é‚Á‚ÆˆÚ“®
    getCoordVehicle()->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              prm_p1, prm_p2, 0, true);
}

void DefaultCameraViewPoint::slideMvTo(GgafDx::GeometricActor* pTarget, frame t, double prm_p1, double prm_p2) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t, prm_p1, prm_p2);
}

DefaultCameraViewPoint::~DefaultCameraViewPoint() {
}
