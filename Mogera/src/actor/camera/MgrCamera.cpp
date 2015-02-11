#include "MgrCamera.h"

#include "MgrCameraUpVector.h"
#include "MgrCameraViewPoint.h"
#include "jp/ggaf/core/util/GgafUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/dxcore/util/GgafDxDirectionUtil.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

MgrCamera::MgrCamera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "MgrCamera";
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
    pAxsMver_ = NEW GgafDxAxesMover(this);
}

GgafDxCameraViewPoint* MgrCamera::createCameraViewPoint() {
    MgrCameraViewPoint* pVP = NEW MgrCameraViewPoint("MgrCameraViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}
GgafDxCameraUpVector* MgrCamera::createCameraUpVector() {
    MgrCameraUpVector* pUp = NEW MgrCameraUpVector("MgrCameraUpVector");
    return (GgafDxCameraUpVector*)pUp;
}

void MgrCamera::initialize() {
    DefaultCamera::initialize();
}

void MgrCamera::processBehavior() {
    //_TRACE_("CAMERA("<<_x<<","<<_y<<","<<_z<<")");
    pAxsMver_->behave();
    getKuroko()->behave();
    DefaultCamera::processBehavior();
}

void MgrCamera::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.7, 0, true);
}
void MgrCamera::slideMvTo(GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}

void MgrCamera::slideMvTo(coord tx, coord ty, coord tz, frame t,
                       float prm_x_p1, float prm_y_p1, float prm_z_p1) {
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              prm_x_p1, prm_x_p1, 0,
                              prm_y_p1, prm_y_p1, 0,
                              prm_z_p1, prm_z_p1, 0,
                              true);
}
void MgrCamera::slideMvTo(GgafDxGeometricActor* pTarget, frame t,
                       float prm_x_p1, float prm_y_p1, float prm_z_p1) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t,
              prm_x_p1, prm_y_p1, prm_z_p1);
}

face26 MgrCamera::getVpFaceNo() {
    float vcv_x, vcv_y, vcv_z;
    MgrCameraViewPoint* pVp = (MgrCameraViewPoint*)getCameraViewPoint();
    UTIL::getNormalizeVector (
            pVp->_x - _x,
            pVp->_y - _y,
            pVp->_z - _z,
            vcv_x, vcv_y, vcv_z  );
    return GgafDxDirectionUtil::cnvVec2FaceNo(vcv_x, vcv_y, vcv_z);
}

MgrCamera::~MgrCamera() {
    GGAF_DELETE(pAxsMver_);
}
