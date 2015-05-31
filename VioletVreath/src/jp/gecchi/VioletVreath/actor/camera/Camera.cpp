#include "Camera.h"

#include "CameraUpVector.h"
#include "CameraViewPoint.h"
#include "jp/ggaf/core/util/GgafUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/dxcore/util/GgafDxDirectionUtil.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Camera::Camera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 100.0 / 180.0) { //‚©‚È‚è‰¡’·‰æ–Ê‚È‚Ì‚ÅŽ‹–ìŠp‚P‚O‚O“x‚®‚ç‚¢
    _class_name = "Camera";
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
    pAxsMver_ = NEW GgafDxAxesMover(this);
}

GgafDxCameraViewPoint* Camera::createCameraViewPoint() {
    CameraViewPoint* pVP = NEW CameraViewPoint("CameraViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}
GgafDxCameraUpVector* Camera::createCameraUpVector() {
    CameraUpVector* pUp = NEW CameraUpVector("CameraUpVector");
    return (GgafDxCameraUpVector*)pUp;
}

void Camera::initialize() {
    DefaultCamera::initialize();
}

void Camera::processBehavior() {
    pAxsMver_->behave();
    getKuroko()->behave();
    DefaultCamera::processBehavior();
}

void Camera::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.7, 0, true);
}

void Camera::slideMvTo(GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}

void Camera::slideMvTo(coord tx, coord ty, coord tz, frame t,
                       float prm_x_p1, float prm_y_p1, float prm_z_p1) {
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              prm_x_p1, prm_x_p1, 0,
                              prm_y_p1, prm_y_p1, 0,
                              prm_z_p1, prm_z_p1, 0,
                              true);
}
void Camera::slideMvTo(GgafDxGeometricActor* pTarget, frame t,
                       float prm_x_p1, float prm_y_p1, float prm_z_p1) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t,
              prm_x_p1, prm_y_p1, prm_z_p1);
}

face26 Camera::getVpFaceNo() {
    float vcv_x, vcv_y, vcv_z;
    CameraViewPoint* pVp = (CameraViewPoint*)getCameraViewPoint();
    UTIL::getNormalizeVector (
            pVp->_x - _x,
            pVp->_y - _y,
            pVp->_z - _z,
            vcv_x, vcv_y, vcv_z  );
    return GgafDxDirectionUtil::cnvVec2FaceNo(vcv_x, vcv_y, vcv_z);
}

Camera::~Camera() {
    GGAF_DELETE(pAxsMver_);
}
