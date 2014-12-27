#include "Camera.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "ViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/core/util/GgafUtil.h"

#include "CameraUpVector.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Camera::Camera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "Camera";
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
    pAxsMver_ = NEW GgafDxAxesMover(this);
    up_face_ = 2;
}

GgafDxCameraViewPoint* Camera::createCameraViewPoint() {
    ViewPoint* pVP = NEW ViewPoint("ViewPoint");
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
    ViewPoint* pVp = (ViewPoint*)getViewPoint();
    pAxsMver_->behave();
    getKuroko()->behave();

    DefaultCamera::processBehavior();

    vcv_face_prev_ = vcv_face_;
//    if (isMoving() || pVp->isMoving()) {  //isMoving()ÇÕç¿ïWà⁄ìÆå„Ç≈Ç»Ç¢Ç∆à”ñ°Ç™ñ≥Ç¢
         vcv_face_ = getCamToVpFaceNo();
//    }
#ifdef MY_DEBUG
    if (vcv_face_prev_!=vcv_face_) {
        _TRACE_("Camera::processBehavior()  vcv="<<vcv_face_prev_<<"Å®"<<vcv_face_<<"");
    }
#endif
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
int Camera::getCamToVpFaceNo() {
    float vcv_x, vcv_y, vcv_z;
    ViewPoint* pVP = (ViewPoint*)getViewPoint();
    UTIL::getNormalizeVector (
            pVP->_x - _x,
            pVP->_y - _y,
            pVP->_z - _z,
            vcv_x, vcv_y, vcv_z  );
    return Camera::cnvVec2FaceNo(vcv_x, vcv_y, vcv_z);
}

int Camera::cnvVec2FaceNo(float vx, float vy, float vz) {
//
//                       (+y)áA      áB(+z)
//                           ^      Å¢
//                           |      /
//                     ______|_________
//                    /|     |    /   /|
//                   / |     |   /   / |
//                  /  |            /  |
//                 /   |           /   |
//                /_______________/    |
//   (-x)áE <-----|--  |__________|____| ------>á@(+x)
//                |    /          |    /
//                |   /           |   /
//                |  /   /   |    |  /
//                | /   /    |    | /
//                |/___/__________|/
//                    /      |
//                   Å§      |
//                  áC(-z)   v
//                           áD(-y)
//
    float abs_vx = ABS(vx);
    float abs_vy = ABS(vy);
    float abs_vz = ABS(vz);
    int r_face_no = -1;
    //íPà óßï˚ëÃÇÃÇ«ÇÃñ Ç…ÉxÉNÉgÉãÇÕéhÇ≥ÇÈÇ©
    if (abs_vx >= abs_vy) {
        if (abs_vx >= abs_vz) {
            if (vx >= 0) {
                //x+ ñ Ç…ìÀÇ´éhÇ≥ÇÈ
                r_face_no = 1;
            } else {
                //x- ñ Ç…ìÀÇ´éhÇ≥ÇÈ
                r_face_no = 6;
            }
        } else {
            if (vz >= 0) {
                //z+ ñ Ç…ìÀÇ´éhÇ≥ÇÈ
                r_face_no = 3;
            } else {
                //z- ñ Ç…ìÀÇ´éhÇ≥ÇÈ
                r_face_no = 4;
            }
        }
    } else {
        if (abs_vy >= abs_vz) {
            if (vy >= 0) {
                //y+ ñ Ç…ìÀÇ´éhÇ≥ÇÈ
                r_face_no = 2;
            } else {
                //y- ñ Ç…ìÀÇ´éhÇ≥ÇÈ
                r_face_no = 5;
            }
        } else {
            if (vz >= 0) {
                //z+ ñ Ç…ìÀÇ´éhÇ≥ÇÈ
                r_face_no = 3;
            } else {
                //z- ñ Ç…ìÀÇ´éhÇ≥ÇÈ
                r_face_no = 4;
            }
        }
    }
    return r_face_no;
}

void Camera::cnvFaceNo2Vec(int face_no, float& out_vx, float& out_vy, float& out_vz) {
    if (face_no == 1) {
        out_vx = 1.0f;   out_vy = 0.0f;  out_vz = 0.0f;
    } else if (face_no == 6) {
        out_vx = -1.0f;  out_vy = 0.0f;  out_vz = 0.0f;
    } else if (face_no == 2) {
        out_vx = 0.0f;   out_vy = 1.0f;   out_vz = 0.0f;
    } else if (face_no == 5) {
        out_vx = 0.0f;   out_vy = -1.0f;  out_vz = 0.0f;
    } else if (face_no == 3) {
        out_vx = 0.0f;   out_vy = 0.0f;   out_vz = 1.0f;
    } else if (face_no == 4) {
        out_vx = 0.0f;   out_vy = 0.0f;   out_vz = -1.0f;
    } else {
        throwGgafCriticalException("CameraWorker::cnvFaceNo2Vec() face_no="<<face_no);
    }
}

void Camera::slideUpCamTo(int prm_face_no, frame prm_t) {
    dxcoord up_x, up_y, up_z;
    Camera::cnvFaceNo2Vec(prm_face_no, up_x, up_y, up_z);
    slideUpCamTo(DX_C(up_x), DX_C(up_y), DX_C(up_z), prm_t);
}

void Camera::slideUpCamTo(coord tx, coord ty, coord tz, frame t) {
    CameraUpVector* pUp = (CameraUpVector*)getCameraUpVector();
    int up_face = Camera::cnvVec2FaceNo(C_DX(tx), C_DX(ty), C_DX(tz));
    pUp->pAxsMver_->asst()->
             slideVxyzMvByDtTo(tx, ty, tz, t, 0.3, 0.4, 0, true);
    int up_face_wk = up_face_;
    up_face_ = Camera::cnvVec2FaceNo(C_DX(tx), C_DX(ty), C_DX(tz));

#ifdef MY_DEBUG
    if (up_face_wk != up_face_) {
        _TRACE_("Camera::slideUpCamTo  up_face_="<<up_face_wk<<"Å®"<<up_face_<<"");
    }
#endif
}

Camera::~Camera() {
    GGAF_DELETE(pAxsMver_);
}
