#include "VvvCamera.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "actor/VvvViewPoint.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvCamera::VvvCamera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "VvvCamera";
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
    pAxsMver_ = NEW GgafDxAxesMover(this);

    pUp_ = NEW DefaultGeometricActor("CAM_UP", nullptr, nullptr);
    pAxsMver_Up_ = NEW GgafDxAxesMover(pUp_);
    pUp_->position(DX_C(_pVecCamUp->x), DX_C(_pVecCamUp->y), DX_C(_pVecCamUp->z));
    addSubLast(pUp_);
    up_face_ = VvvCamera::cnvVec2FaceNo(_pVecCamUp->x, _pVecCamUp->y, _pVecCamUp->z);
}

GgafDxCameraViewPoint* VvvCamera::createViewPoint() {
    VvvViewPoint* pVP = NEW VvvViewPoint("VvvViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}

void VvvCamera::initialize() {
    DefaultCamera::initialize();
}

void VvvCamera::processBehavior() {

    VvvViewPoint* pVP = (VvvViewPoint*)getViewPoint();

    vcv_face_prev_ = vcv_face_;

    pAxsMver_Up_->behave();

    float v_up_x, v_up_y, v_up_z;
    UTIL::getNormalizeVector (
            pUp_->_x,
            pUp_->_y,
            pUp_->_z,
            v_up_x, v_up_y, v_up_z );
    setVecCamUp(v_up_x, v_up_y, v_up_z );

    pAxsMver_->behave();
    getKuroko()->behave();

    int bk_up_face_ = up_face_;

    if (isMoving() || pVP->isMoving()) {
        vcv_face_ = getCamToVpFaceNo();
//        _DTRACE_("CAM or VP move  vcv_face_ = "<<vcv_face_);
        if (vcv_face_ != vcv_face_prev_) {
            if (vcv_face_ == up_face_) {
                //ç°ÇÃUP(up_face_)ÇÃñ Ç…ÉJÉÅÉâÅ®éãì_ÉxÉNÉgÉã(vcv_face_)Ç™ìÀÇ´éhÇ≥ÇÈèÍçá
                //à»ëOÇÃÉJÉÅÉâÅ®éãì_(vcv_face_prev_) ÇÃê^ó†ÇÃñ Ç…UPÇ™à⁄ìÆ
                slideUpCamTo(7 - vcv_face_prev_);
            } else if (vcv_face_ == 7 - up_face_) {  //up_face_ÇÃó†ñ 
                 //ç°ÇÃUP(up_face_)ÇÃñ ÇÃê^ó†Ç…ÉJÉÅÉâÅ®éãì_ÉxÉNÉgÉã(vcv_face_)Ç™ìÀÇ´éhÇ≥ÇÈèÍçá
                 //à»ëOÇÃÉJÉÅÉâÅ®éãì_(vcv_face_prev_) ÇÃñ Ç™UPÇ…ïœçX
                slideUpCamTo(vcv_face_prev_);
            } else {
                //ïœâªÇµÇ»Ç¢
                slideUpCamTo(up_face_);
            }
        }
    }
    //_DTRACE_("cam=("<<_x<<","<<_y<<","<<_z<<")");
//    _DTRACE_("cam=("<<_x<<","<<_y<<","<<_z<<") vp=("<< pVP->_x <<","<< pVP->_y <<","<< pVP->_z <<")  UP=("<< pUp_->_x <<","<< pUp_->_y <<","<< pUp_->_z <<") CAM_UP=("<< _pVecCamUp->x <<","<< _pVecCamUp->y <<","<< _pVecCamUp->z <<")");
//    _DTRACE_("vcv="<<vcv_face_prev_<<"Å®"<<vcv_face_<<" up_face_="<<bk_up_face_<<"Å®"<<up_face_<<"");
    DefaultCamera::processBehavior();

}

void VvvCamera::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    _DTRACE_(" VvvCamera::slideMvTo("<<tx<<","<<ty<<","<<tz<<",t="<<t<<")");
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.4, 0, true);
}
void VvvCamera::slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}
int VvvCamera::getCamToVpFaceNo() {
    float vcv_x, vcv_y, vcv_z;
    VvvViewPoint* pVP = (VvvViewPoint*)getViewPoint();
    UTIL::getNormalizeVector (
            pVP->_x - _x,
            pVP->_y - _y,
            pVP->_z - _z,
            vcv_x, vcv_y, vcv_z  );
    return VvvCamera::cnvVec2FaceNo(vcv_x, vcv_y, vcv_z);
}

int VvvCamera::cnvVec2FaceNo(float vx, float vy, float vz) {
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

void VvvCamera::cnvFaceNo2Vec(int face_no, float& out_vx, float& out_vy, float& out_vz) {
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
        throwGgafCriticalException("VvvCameraWorker::slideUpCamTo() face_no="<<face_no);
    }
}
void VvvCamera::slideUpCamTo(int prm_face_no) {
    up_face_ = prm_face_no;
    dxcoord up_x, up_y, up_z;
    VvvCamera::cnvFaceNo2Vec(prm_face_no, up_x, up_y, up_z);
    pAxsMver_Up_->asst()->
             slideVxyzMvByDtTo(DX_C(up_x), DX_C(up_y), DX_C(up_z), 60, 0.3, 0.4, 0, true);
}
VvvCamera::~VvvCamera() {
    GGAF_DELETE(pAxsMver_Up_);
    GGAF_DELETE(pAxsMver_);
}
