#include "CameraWorker.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/actor/ViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CameraWorker::CameraWorker(const char* prm_name) : GgafMainActor(prm_name, nullptr) {
    _class_name = "CameraWorker";
    t_x_VP_ =  0;
    t_y_VP_ =  0;
    t_z_VP_ =  0;
    t_x_CAM_ =  0;
    t_y_CAM_ =  0;
    t_z_CAM_ =  0;
    frame_of_behaving_since_onSwitch_ = 0;
    pCam_ = nullptr;
    pVp_ = nullptr;
    t_cam_up_face_ = 2;

    //注意：Cameraはまだ生成されていないためここでP_CAMは使用不可
}

void CameraWorker::initialize() {
    pCam_ = P_CAM;
    pVp_ = (ViewPoint*)(pCam_->getViewPoint());
    t_x_VP_ = pVp_->_x;
    t_y_VP_ = pVp_->_y;
    t_z_VP_ = pVp_->_z;
    t_x_CAM_ = pCam_->_x;
    t_y_CAM_ = pCam_->_y;
    t_z_CAM_ = pCam_->_z;
    t_cam_up_face_ = pCam_->up_face_;
}
void CameraWorker::onActive() {
    //現在のターゲットを再ターゲット
    slideMvCamTo(t_x_CAM_, t_y_CAM_, t_z_CAM_, 60);
    slideMvVpTo(t_x_VP_, t_y_VP_, t_z_VP_, 60);
}

void CameraWorker::onSwitchCameraWork() {
    //frame_of_behaving_since_onSwitch_ = 0; は Universe::switchCameraWork() が行う。
}

void CameraWorker::onUndoCameraWork() {
}

void CameraWorker::onSwitchToOtherCameraWork() {
}

void CameraWorker::onCameBackFromOtherCameraWork() {
}

void CameraWorker::processBehavior() {
    behaveAutoCamUp();
}

void CameraWorker::slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvCamTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}


void CameraWorker::slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t,
                                float prm_x_p1, float prm_y_p1, float prm_z_p1) {
     slideMvCamTo(pTarget->_x, pTarget->_y, pTarget->_z, t, prm_x_p1, prm_y_p1, prm_z_p1);

}
void CameraWorker::slideMvVpTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvVpTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}
void CameraWorker::slideMvCamTo(coord tx, coord ty, coord tz, frame t) {
    t_x_CAM_ = tx;
    t_y_CAM_ = ty;
    t_z_CAM_ = tz;
    pCam_->slideMvTo(tx, ty, tz, t);
}
void CameraWorker::slideMvCamTo(coord tx, coord ty, coord tz, frame t,
            float prm_x_p1, float prm_y_p1, float prm_z_p1) {
    t_x_CAM_ = tx;
    t_y_CAM_ = ty;
    t_z_CAM_ = tz;
    pCam_->slideMvTo(tx, ty, tz, t, prm_x_p1, prm_y_p1, prm_z_p1);
}


void CameraWorker::slideMvVpTo(coord tx, coord ty, coord tz, frame t) {
    t_x_VP_ = tx;
    t_y_VP_ = ty;
    t_z_VP_ = tz;
    pVp_->slideMvTo(tx, ty, tz, t);
}
void CameraWorker::behaveAutoCamUp() {
#ifdef MY_DEBUG
    int bk_up_face_ = pCam_->up_face_;
#endif
    if (pCam_->vcv_face_ != pCam_->vcv_face_prev_) {
        GgafDxAxesMoverAssistantA* asstA = pCam_->pAxsMver_->asst();
        int fx = asstA->_smthVxMv._prm._flg ? asstA->_smthVxMv._prm._target_frames : 10;
        int fy = asstA->_smthVyMv._prm._flg ? asstA->_smthVyMv._prm._target_frames : 10;
        int fz = asstA->_smthVzMv._prm._flg ? asstA->_smthVzMv._prm._target_frames : 10;
        frame up_frames = (frame)(MAX3(fx,fy,fz) / 2) ; //半分のフレーム時間でUP変更を完了させる
        if (pCam_->vcv_face_ == pCam_->up_face_) {
            //今のUP(up_face_)の面にカメラ→視点ベクトル(vcv_face_)が突き刺さる場合
            //以前のカメラ→視点(vcv_face_prev_) の真裏の面にUPが移動
            pCam_->slideUpCamTo(7 - pCam_->vcv_face_prev_, up_frames);
        } else if (pCam_->vcv_face_ == 7 - pCam_->up_face_) {  //up_face_の裏面
             //今のUP(up_face_)の面の真裏にカメラ→視点ベクトル(vcv_face_)が突き刺さる場合
             //以前のカメラ→視点(vcv_face_prev_) の面がUPに変更
            pCam_->slideUpCamTo(pCam_->vcv_face_prev_, up_frames);
        } else {
            //変化しない
            pCam_->slideUpCamTo(pCam_->up_face_, up_frames);
        }
        _TRACE_("CameraWorker::behaveAutoCamUp() up_frames="<<up_frames<<" vcv="<<pCam_->vcv_face_prev_<<"→"<<pCam_->vcv_face_<<" up_face_="<<bk_up_face_<<"→"<<pCam_->up_face_<<"");
    }
//    _TRACE_("cam=("<<_x<<","<<_y<<","<<_z<<") vp=("<< pVP->_x <<","<< pVP->_y <<","<< pVP->_z <<")  UP=("<< pUp_->_x <<","<< pUp_->_y <<","<< pUp_->_z <<") CAM_UP=("<< _pVecCamUp->x <<","<< _pVecCamUp->y <<","<< _pVecCamUp->z <<")");
//    _TRACE_("vcv="<<vcv_face_prev_<<"→"<<vcv_face_<<" up_face_="<<bk_up_face_<<"→"<<up_face_<<"");
}
//void CameraWorker::stopNaturallyCam(coord distance, frame t) {
//    float vx,vy,vz;
//    GgafDxAxesMover* pAxMvr = pCam_->pAxsMver_;
//    UTIL::getNormalizeVector(
//            pAxMvr->_velo_vx_mv,
//            pAxMvr->_velo_vy_mv,
//            pAxMvr->_velo_vz_mv,
//            vx,vy,vz);
//    pAxMvr->asstA()->slideVxyzMvByDt(distance*vx, distance*vy, distance*vz,
//                                     t,
//                                     0.0, 0.0, 0, true);
//}
//void CameraWorker::stopNaturallyVp(coord distance, frame t) {
//    float vx,vy,vz;
//    GgafDxAxesMover* pAxMvr = pVp_->pAxsMver_;
//    UTIL::getNormalizeVector(
//            pAxMvr->_velo_vx_mv,
//            pAxMvr->_velo_vy_mv,
//            pAxMvr->_velo_vz_mv,
//            vx,vy,vz);
//    pAxMvr->asstA()->slideVxyzMvByDt(distance*vx, distance*vy, distance*vz,
//                                     t,
//                                     0.0, 0.0, 0, true);
//}
void CameraWorker::stopMvCam() {
    pCam_->pAxsMver_->stopMv();
}
void CameraWorker::stopMvVp() {
    pVp_->pAxsMver_->stopMv();
}
CameraWorker::~CameraWorker() {

}
