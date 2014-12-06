#include "VVCamera.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "ViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/core/util/GgafUtil.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



//Ternary numeral -1,0,1 ÇÃ3êîÇÃ3êiñ@ Ç îzóÒóvëfÇÃÇΩÇﬂê≥ÇÃ10êiêîÇ…ïœä∑Ç∑ÇÈÉ}ÉNÉç
#define TN(X,Y,Z) (((3*3)*((X)+1)) + (3*((Y)+1)) + ((Z)+1))

VVCamera::VVCamera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "VVCamera";
    tx_ = _x;
    ty_ = _y;
    tz_ = _z;
    pAxsMver_ = NEW GgafDxAxesMover(this);

    pUp_ = NEW DefaultGeometricActor("CAM_UP", nullptr, nullptr);
    pAxsMver_Up_ = NEW GgafDxAxesMover(pUp_);
    pUp_->position(DX_C(_pVecCamUp->x), DX_C(_pVecCamUp->y), DX_C(_pVecCamUp->z));
    addSubLast(pUp_);
    up_face_ = VVCamera::cnvVec2FaceNo(_pVecCamUp->x, _pVecCamUp->y, _pVecCamUp->z);
}

GgafDxCameraViewPoint* VVCamera::createViewPoint() {
    ViewPoint* pVP = NEW ViewPoint("ViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}

void VVCamera::initialize() {
    DefaultCamera::initialize();
}

void VVCamera::processBehavior() {
    ViewPoint* pVp = (ViewPoint*)getViewPoint();
    pAxsMver_Up_->behave();
    //ÉJÉÅÉâÇÃUPÇîΩâf
    float v_up_x, v_up_y, v_up_z;
    UTIL::getNormalizeVector (
            pUp_->_x,
            pUp_->_y,
            pUp_->_z,
            v_up_x, v_up_y, v_up_z );
    setVecCamUp(v_up_x, v_up_y, v_up_z );
    pAxsMver_->behave();
    getKuroko()->behave();

    DefaultCamera::processBehavior();

    vcv_face_prev_ = vcv_face_;
    if (isMoving() || pVp->isMoving()) {  //isMoving()ÇÕç¿ïWà⁄ìÆå„Ç≈Ç»Ç¢Ç∆à”ñ°Ç™ñ≥Ç¢
         vcv_face_ = getCamToVpFaceNo();
    }
#ifdef MY_DEBUG
    if (vcv_face_prev_!=vcv_face_) {
        _TRACE_("VVCamera::processBehavior()  vcv="<<vcv_face_prev_<<"Å®"<<vcv_face_<<"");
    }
#endif
}

void VVCamera::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.7, 0, true);
}
void VVCamera::slideMvTo(GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}

void VVCamera::slideMvTo(coord tx, coord ty, coord tz, frame t,
                       float prm_x_p1, float prm_y_p1, float prm_z_p1) {
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              prm_x_p1, prm_x_p1, 0,
                              prm_y_p1, prm_y_p1, 0,
                              prm_z_p1, prm_z_p1, 0,
                              true);
}
void VVCamera::slideMvTo(GgafDxGeometricActor* pTarget, frame t,
                       float prm_x_p1, float prm_y_p1, float prm_z_p1) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t,
              prm_x_p1, prm_y_p1, prm_z_p1);
}
int VVCamera::getCamToVpFaceNo() {
    float vcv_x, vcv_y, vcv_z;
    ViewPoint* pVP = (ViewPoint*)getViewPoint();
    UTIL::getNormalizeVector (
            pVP->_x - _x,
            pVP->_y - _y,
            pVP->_z - _z,
            vcv_x, vcv_y, vcv_z  );
    return VVCamera::cnvVec2FaceNo(vcv_x, vcv_y, vcv_z);
}

int VVCamera::cnvVec2FaceNo(float vx, float vy, float vz) {

//              ________
//            Å^        Å_
//          Å^            Å_
//        Å^                Å_
//       |                    |
//       |                    |
//       |                    |
//        Å_                Å^
//          Å_            Å^
//            Å_ÅQÅQÅQÅQÅ^
//
//               2-Å„2

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

void VVCamera::cnvFaceNo2Vec(int face_no, float& out_vx, float& out_vy, float& out_vz) {
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
        throwGgafCriticalException("VVCameraWorker::cnvFaceNo2Vec() face_no="<<face_no);
    }
}

void VVCamera::slideUpCamTo(int prm_face_no, frame prm_t) {
    dxcoord up_x, up_y, up_z;
    VVCamera::cnvFaceNo2Vec(prm_face_no, up_x, up_y, up_z);
    slideUpCamTo(DX_C(up_x), DX_C(up_y), DX_C(up_z), prm_t);
}

void VVCamera::slideUpCamTo(coord tx, coord ty, coord tz, frame t) {
    pAxsMver_Up_->asst()->
             slideVxyzMvByDtTo(tx, ty, tz, t, 0.3, 0.4, 0, true);
    int up_face_wk = up_face_;
    up_face_ = VVCamera::cnvVec2FaceNo(C_DX(tx), C_DX(ty), C_DX(tz));

#ifdef MY_DEBUG
    if (up_face_wk != up_face_) {
        _TRACE_("VVCamera::slideUpCamTo  up_face_="<<up_face_wk<<"Å®"<<up_face_<<"");
    }
#endif
}

VVCamera::~VVCamera() {
    GGAF_DELETE(pAxsMver_Up_);
    GGAF_DELETE(pAxsMver_);
}
