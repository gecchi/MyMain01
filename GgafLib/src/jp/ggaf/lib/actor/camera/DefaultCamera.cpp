#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"
#include "jp/ggaf/lib/GgafLibConfig.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

DefaultCamera::DefaultCamera(const char* prm_name, double prm_rad_fovX, double prm_dep) : GgafDxCamera(prm_name, prm_rad_fovX, prm_dep) {
    _class_name = "DefaultCamera";
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
}

DefaultCamera::DefaultCamera(const char* prm_name, double prm_rad_fovX) :
        GgafDxCamera(prm_name, prm_rad_fovX, CONFIG::GAME_SPACE_DEPTH) {
    _class_name = "DefaultCamera";
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
}

DefaultCamera::DefaultCamera(const char* prm_name) :
        GgafDxCamera(prm_name, PI * 90.0f / 180.0f, CONFIG::GAME_SPACE_DEPTH) {
    _class_name = "DefaultCamera";
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
}

GgafDxCameraViewPoint* DefaultCamera::createCameraViewPoint() {
    DefaultCameraViewPoint* p = NEW DefaultCameraViewPoint("DefaultCameraViewPoint");
    return (GgafDxCameraViewPoint*)p;
}

GgafDxCameraUpVector* DefaultCamera::createCameraUpVector() {
    DefaultCameraUpVector* p = NEW DefaultCameraUpVector("DefaultCameraUpVector");
    return (GgafDxCameraUpVector*)p;
}

void DefaultCamera::initialize() {
    GgafDxCamera::initialize();
}

void DefaultCamera::processBehavior() {
    getAxesMover()->behave();
    getKuroko()->behave();
    GgafDxCamera::processBehavior();
}

void DefaultCamera::slideMvTo(coord tx, coord ty, coord tz, frame t, float prm_p1, float prm_p2) {
    getAxesMover()->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              prm_p1, prm_p2, 0, true);
}

void DefaultCamera::slideMvTo(GgafDxGeometricActor* pTarget, frame t, float prm_p1, float prm_p2) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t, prm_p1, prm_p2);
}

void DefaultCamera::slideMvTo(coord tx, coord ty, coord tz, frame t,
                       float prm_x_p1, float prm_y_p1, float prm_z_p1) {
    getAxesMover()->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              prm_x_p1, prm_x_p1, 0,
                              prm_y_p1, prm_y_p1, 0,
                              prm_z_p1, prm_z_p1, 0,
                              true);
}
void DefaultCamera::slideMvTo(GgafDxGeometricActor* pTarget, frame t,
                       float prm_x_p1, float prm_y_p1, float prm_z_p1) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t,
              prm_x_p1, prm_y_p1, prm_z_p1);
}

dir26 DefaultCamera::getVpDirNo() {
    float vcv_x, vcv_y, vcv_z;
    DefaultCameraViewPoint* pVp = (DefaultCameraViewPoint*)getCameraViewPoint();
    UTIL::getNormalizedVector (
            pVp->_x - _x,
            pVp->_y - _y,
            pVp->_z - _z,
            vcv_x, vcv_y, vcv_z  );
    return GgafDx26DirectionUtil::cnvVec2DirNo(vcv_x, vcv_y, vcv_z);
}

bool DefaultCamera::isSliding() {
    return getAxesMover()->asst()->isSliding();
}

DefaultCamera::~DefaultCamera() {
}
