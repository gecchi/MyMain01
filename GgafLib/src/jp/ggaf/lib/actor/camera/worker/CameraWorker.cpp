#include "jp/ggaf/lib/actor/camera/worker/CameraWorker.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicleAssistantA.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleFaceAngAssistant.h"
#include "jp/ggaf/lib/util/Direction26Util.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"



using namespace GgafLib;

CameraWorker::CameraWorker(const char* prm_name, DefaultCamera* prm_pCamera,
                          frame prm_slide_frames, double prm_slide_p1, double prm_slide_p2) : GgafCore::MainActor(prm_name) {
    _class_name = "CameraWorker";
    _t_x_VP =  0;
    _t_y_VP =  0;
    _t_z_VP =  0;
    _t_x_CAM =  0;
    _t_y_CAM =  0;
    _t_z_CAM =  0;
    _t_x_UP =  0;
    _t_y_UP =  0;
    _t_z_UP =  0;
    _frame_of_behaving_since_onSwitch = 0;
    _pCam = prm_pCamera;
    _pVp = (DefaultCameraViewPoint*)(_pCam->getCameraViewPoint());
    _pUp = (DefaultCameraUpVector*)(_pCam->getCameraUpVector());
    _slide_frames = prm_slide_frames;
    _slide_p1 = prm_slide_p1;
    _slide_p2 = prm_slide_p2;
    static volatile bool is_init = CameraWorker::initStatic(); //静的メンバ初期化
    (void)is_init;
}

bool CameraWorker::initStatic() {
    return true;
}

void CameraWorker::initialize() {
    _t_x_VP = _pVp->_x;
    _t_y_VP = _pVp->_y;
    _t_z_VP = _pVp->_z;
    _t_x_CAM = _pCam->_x;
    _t_y_CAM = _pCam->_y;
    _t_z_CAM = _pCam->_z;
    _t_x_UP =  _pUp->_x;
    _t_y_UP =  _pUp->_y;
    _t_z_UP =  _pUp->_z;
}
void CameraWorker::onActive() {
    //現在のターゲットを再ターゲット
    slideMvCamTo(_t_x_CAM, _t_y_CAM, _t_z_CAM);
    slideMvVpTo(_t_x_VP, _t_y_VP, _t_z_VP);
    slideMvUpVecTo(_t_x_UP, _t_y_UP, _t_z_UP);
}

void CameraWorker::onSwitchCameraWork() {
    //現在のターゲットを再ターゲット
    slideMvCamTo(_t_x_CAM, _t_y_CAM, _t_z_CAM);
    slideMvVpTo(_t_x_VP, _t_y_VP, _t_z_VP);
    slideMvUpVecTo(_t_x_UP, _t_y_UP, _t_z_UP);
}

void CameraWorker::onChangedToOtherCameraWork() {
}

void CameraWorker::slideMvCamTo(GgafDx::GeometricActor* pTarget, frame t) {
    slideMvCamTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}

void CameraWorker::slideMvCamTo(GgafDx::GeometricActor* pTarget, frame t,
                                double prm_x_p1, double prm_y_p1, double prm_z_p1) {
    slideMvCamTo(pTarget->_x, pTarget->_y, pTarget->_z, t, prm_x_p1, prm_y_p1, prm_z_p1);
}

void CameraWorker::slideMvCamTo(coord tx, coord ty, coord tz, frame t,
                                double prm_p1, double prm_p2) {
    _t_x_CAM = tx;
    _t_y_CAM = ty;
    _t_z_CAM = tz;
    _pCam->slideMvTo(tx, ty, tz, t, prm_p1, prm_p2);
}

void CameraWorker::slideMvCamTo(coord tx, coord ty, coord tz, frame t,
                                double prm_x_p1, double prm_y_p1, double prm_z_p1) {
    _t_x_CAM = tx;
    _t_y_CAM = ty;
    _t_z_CAM = tz;
    _pCam->slideMvTo(tx, ty, tz, t, prm_x_p1, prm_y_p1, prm_z_p1);
}

void CameraWorker::mvCamTo(coord tx, coord ty, coord tz) {
    _t_x_CAM = tx;
    _t_y_CAM = ty;
    _t_z_CAM = tz;
    _pCam->setPosition(tx, ty, tz);
}

bool CameraWorker::isCamSliding() {
    return _pCam->isSliding();
}
void CameraWorker::slideMvVpTo(coord tx, coord ty, coord tz, frame t, double prm_p1, double prm_p2)  {
    _t_x_VP = tx;
    _t_y_VP = ty;
    _t_z_VP = tz;
    _pVp->slideMvTo(tx, ty, tz, t, prm_p1, prm_p2);
}
void CameraWorker::slideMvUpVecTo(coord tx, coord ty, coord tz, frame t, double prm_p1, double prm_p2)  {
    _t_x_UP = tx;
    _t_y_UP = ty;
    _t_z_UP = tz;
    _pUp->slideMvTo(tx, ty, tz, t, prm_p1, prm_p2);
}

void CameraWorker::setUpVec(coord tx, coord ty, coord tz) {
    _pUp->setPosition(tx,ty,tz);
}
void CameraWorker::stopMvCam() {
    _pCam->getCoordVehicle()->stop();
}

void CameraWorker::stopMvVp() {
    _pVp->getCoordVehicle()->stop();
}

CameraWorker::~CameraWorker() {

}
