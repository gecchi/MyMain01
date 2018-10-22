#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxTrucker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxTruckerAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "jp/ggaf/lib/util/Direction26Util.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

CameraWorker::CameraWorker(const char* prm_name, DefaultCamera* prm_pCamera) : GgafMainActor(prm_name, nullptr) {
    _class_name = "CameraWorker";
    t_x_VP_ =  0;
    t_y_VP_ =  0;
    t_z_VP_ =  0;
    t_x_CAM_ =  0;
    t_y_CAM_ =  0;
    t_z_CAM_ =  0;
    t_x_UP_ =  0;
    t_y_UP_ =  0;
    t_z_UP_ =  0;
    frame_of_behaving_since_onSwitch_ = 0;
    pCam_ = prm_pCamera;
    pVp_ = (DefaultCameraViewPoint*)(pCam_->getCameraViewPoint());
    pUp_ = (DefaultCameraUpVector*)(pCam_->getCameraUpVector());

    static volatile bool is_init = CameraWorker::initStatic(); //静的メンバ初期化
    //注意：Cameraはまだ生成されていないためここでP_CAMは使用不可
}

bool CameraWorker::initStatic() {
    return true;
}

void CameraWorker::initialize() {
    t_x_VP_ = pVp_->_x;
    t_y_VP_ = pVp_->_y;
    t_z_VP_ = pVp_->_z;
    t_x_CAM_ = pCam_->_x;
    t_y_CAM_ = pCam_->_y;
    t_z_CAM_ = pCam_->_z;
    t_x_UP_ =  pUp_->_x;
    t_y_UP_ =  pUp_->_y;
    t_z_UP_ =  pUp_->_z;
}
void CameraWorker::onActive() {
    //現在のターゲットを再ターゲット
    slideMvCamTo(t_x_CAM_, t_y_CAM_, t_z_CAM_, DEFAULT_CAMERA_SLIDE_FRAMES);
    slideMvVpTo(t_x_VP_, t_y_VP_, t_z_VP_, DEFAULT_CAMERA_SLIDE_FRAMES);
    slideMvUpVecTo(t_x_UP_, t_y_UP_, t_z_UP_, DEFAULT_CAMERA_SLIDE_FRAMES);
}

void CameraWorker::onSwitchCameraWork() {
    //現在のターゲットを再ターゲット
    slideMvCamTo(t_x_CAM_, t_y_CAM_, t_z_CAM_, DEFAULT_CAMERA_SLIDE_FRAMES);
    slideMvVpTo(t_x_VP_, t_y_VP_, t_z_VP_, DEFAULT_CAMERA_SLIDE_FRAMES);
    slideMvUpVecTo(t_x_UP_, t_y_UP_, t_z_UP_, DEFAULT_CAMERA_SLIDE_FRAMES);
}

void CameraWorker::onChangedToOtherCameraWork() {
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

void CameraWorker::slideMvCamTo(coord tx, coord ty, coord tz, frame t,
                                float prm_p1, float prm_p2) {
    t_x_CAM_ = tx;
    t_y_CAM_ = ty;
    t_z_CAM_ = tz;
    pCam_->slideMvTo(tx, ty, tz, t, prm_p1, prm_p2);
}

void CameraWorker::slideMvCamTo(coord tx, coord ty, coord tz, frame t,
                                float prm_x_p1, float prm_y_p1, float prm_z_p1) {
    t_x_CAM_ = tx;
    t_y_CAM_ = ty;
    t_z_CAM_ = tz;
    pCam_->slideMvTo(tx, ty, tz, t, prm_x_p1, prm_y_p1, prm_z_p1);
}

void CameraWorker::mvCamTo(coord tx, coord ty, coord tz) {
    t_x_CAM_ = tx;
    t_y_CAM_ = ty;
    t_z_CAM_ = tz;
    pCam_->setPosition(tx, ty, tz);
}

bool CameraWorker::isCamSliding() {
    return pCam_->isSliding();
}
void CameraWorker::slideMvVpTo(coord tx, coord ty, coord tz, frame t, float prm_p1, float prm_p2)  {
    t_x_VP_ = tx;
    t_y_VP_ = ty;
    t_z_VP_ = tz;
    pVp_->slideMvTo(tx, ty, tz, t, prm_p1, prm_p2);
}
void CameraWorker::slideMvUpVecTo(coord tx, coord ty, coord tz, frame t, float prm_p1, float prm_p2)  {
    t_x_UP_ = tx;
    t_y_UP_ = ty;
    t_z_UP_ = tz;
    pUp_->slideMvTo(tx, ty, tz, t, prm_p1, prm_p2);
}

void CameraWorker::setUpVec(coord tx, coord ty, coord tz) {
    pUp_->setPosition(tx,ty,tz);
}
void CameraWorker::stopMvCam() {
    pCam_->getTrucker()->stopMv();
}

void CameraWorker::stopMvVp() {
    pVp_->getTrucker()->stopMv();
}

CameraWorker::~CameraWorker() {

}
