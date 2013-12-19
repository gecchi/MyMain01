#include "stdafx.h"
#include "Camera.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "ViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverHelperA.h"
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

    pUp_ = NEW DefaultGeometricActor("CAM_UP", nullptr, nullptr);
    pAxsMver_Up_ = NEW GgafDxAxesMover(pUp_);
    pUp_->position(DX_C(_pVecCamUp->x), DX_C(_pVecCamUp->y), DX_C(_pVecCamUp->z));
    addSubLast(pUp_);
    up_face_ = Camera::cnvVec2FaceNo(_pVecCamUp->x, _pVecCamUp->y, _pVecCamUp->z);
}

GgafDxCameraViewPoint* Camera::createViewPoint() {
    ViewPoint* pVP = NEW ViewPoint("ViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}

void Camera::initialize() {
    DefaultCamera::initialize();
}

void Camera::processBehavior() {

    ViewPoint* pVP = (ViewPoint*)getViewPoint();

    vcv_face_prev_ = vcv_face_;

    pAxsMver_Up_->behave();
    setVecCamUp(C_DX(pUp_->_x), C_DX(pUp_->_y), C_DX(pUp_->_z));

    pAxsMver_->behave();
    _pKuroko->behave();

    int bk_up_face_ = up_face_;

    if (isMoving() || pVP->isMoving()) {
        vcv_face_ = getCamToVpFaceNo();
//        _TRACE_("CAM or VP move  vcv_face_ = "<<vcv_face_);
        if (vcv_face_ != vcv_face_prev_) {
            if (vcv_face_ == up_face_) {
                //ç°ÇÃUP(up_face_)ÇÃñ Ç…ÉJÉÅÉâÅ®éãì_ÉxÉNÉgÉã(vcv_face_)Ç™ìÀÇ´éhÇ≥ÇÈèÍçá
                //à»ëOÇÃÉJÉÅÉâÅ®éãì_(vcv_face_prev_) ÇÃê^ó†ÇÃñ Ç…UPÇ™à⁄ìÆ
                setCamUpFace(7 - vcv_face_prev_);
            } else if (vcv_face_ == 7 - up_face_) {  //up_face_ÇÃó†ñ 
                 //ç°ÇÃUP(up_face_)ÇÃñ ÇÃê^ó†Ç…ÉJÉÅÉâÅ®éãì_ÉxÉNÉgÉã(vcv_face_)Ç™ìÀÇ´éhÇ≥ÇÈèÍçá
                 //à»ëOÇÃÉJÉÅÉâÅ®éãì_(vcv_face_prev_) ÇÃñ Ç™UPÇ…ïœçX
                setCamUpFace(vcv_face_prev_);
            } else {
                //ïœâªÇµÇ»Ç¢
                setCamUpFace(up_face_);
            }
        }
    }

//    _TRACE_("cam=("<<_x<<","<<_y<<","<<_z<<") vp=("<< pVP->_x <<","<< pVP->_y <<","<< pVP->_z <<")  UP=("<< pUp_->_x <<","<< pUp_->_y <<","<< pUp_->_z <<")");
//    _TRACE_("vcv="<<vcv_face_prev_<<"Å®"<<vcv_face_<<" up_face_="<<bk_up_face_<<"Å®"<<up_face_<<"");
    DefaultCamera::processBehavior();

}

void Camera::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    pAxsMver_->hlprA()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.4, 0, true);
}
void Camera::slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
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
        throwGgafCriticalException("CameraWorker::setCamUpFace() face_no="<<face_no);
    }
}
void Camera::setCamUpFace(int prm_cam_up_face) {
    up_face_ = prm_cam_up_face;
    dxcoord up_x, up_y, up_z;
    Camera::cnvFaceNo2Vec(prm_cam_up_face, up_x, up_y, up_z);
    pAxsMver_Up_->hlprA()->
             slideVxyzMvByDtTo(DX_C(up_x), DX_C(up_y), DX_C(up_z), 120, 0.3, 0.4, 0, true);
}
Camera::~Camera() {
    GGAF_DELETE(pAxsMver_Up_);
    GGAF_DELETE(pAxsMver_);
}
