#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicleAssistant.h"
#include "jp/ggaf/lib/util/Direction26Util.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"



using namespace GgafLib;

DefaultCamera::DefaultCamera(const char* prm_name, double prm_rad_fovX, double prm_dep) : GgafDx::Camera(prm_name, prm_rad_fovX, prm_dep) {
    _class_name = "DefaultCamera";
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
}

DefaultCamera::DefaultCamera(const char* prm_name, double prm_rad_fovX) :
        GgafDx::Camera(prm_name, prm_rad_fovX, CONFIG::GAME_SPACE_DEPTH) {
    _class_name = "DefaultCamera";
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
}

DefaultCamera::DefaultCamera(const char* prm_name) :
        GgafDx::Camera(prm_name, PI * 90.0f / 180.0f, CONFIG::GAME_SPACE_DEPTH) {
    _class_name = "DefaultCamera";
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
}

GgafDx::CameraViewPoint* DefaultCamera::createCameraViewPoint() {
    DefaultCameraViewPoint* p = NEW DefaultCameraViewPoint("DefaultCameraViewPoint");
    return (GgafDx::CameraViewPoint*)p;
}

GgafDx::CameraUpVector* DefaultCamera::createCameraUpVector() {
    DefaultCameraUpVector* p = NEW DefaultCameraUpVector("DefaultCameraUpVector");
    return (GgafDx::CameraUpVector*)p;
}

void DefaultCamera::initialize() {
    GgafDx::Camera::initialize();
}

void DefaultCamera::processBehavior() {
    getCoordVehicle()->behave();
    getLocusVehicle()->behave();
    GgafDx::Camera::processBehavior();
}

void DefaultCamera::slideMvTo(coord tx, coord ty, coord tz, frame t, double prm_p1, double prm_p2) {
    getCoordVehicle()->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              prm_p1, prm_p2, 0, true);
}

void DefaultCamera::slideMvTo(GgafDx::GeometricActor* pTarget, frame t, double prm_p1, double prm_p2) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t, prm_p1, prm_p2);
}

void DefaultCamera::slideMvTo(coord tx, coord ty, coord tz, frame t,
                       double prm_x_p1, double prm_y_p1, double prm_z_p1) {
    getCoordVehicle()->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              prm_x_p1, prm_x_p1, 0,
                              prm_y_p1, prm_y_p1, 0,
                              prm_z_p1, prm_z_p1, 0,
                              true);
}
void DefaultCamera::slideMvTo(GgafDx::GeometricActor* pTarget, frame t,
                       double prm_x_p1, double prm_y_p1, double prm_z_p1) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t,
              prm_x_p1, prm_y_p1, prm_z_p1);
}

dir26 DefaultCamera::getVpDirNo() {
    double vcv_x, vcv_y, vcv_z;
    DefaultCameraViewPoint* pVp = (DefaultCameraViewPoint*)getCameraViewPoint();
    UTIL::getNormalizedVector (
            pVp->_x - _x,
            pVp->_y - _y,
            pVp->_z - _z,
            vcv_x, vcv_y, vcv_z  );
    return Direction26Util::cnvVec2DirNo(vcv_x, vcv_y, vcv_z);
}

bool DefaultCamera::isSliding() {
    return getCoordVehicle()->asst()->isSliding();
}

DefaultCamera::~DefaultCamera() {
}
