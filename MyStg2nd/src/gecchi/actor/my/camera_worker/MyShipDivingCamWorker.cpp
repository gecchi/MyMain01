#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyShipDivingCamWorker::MyShipDivingCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "MyShipDivingCamWorker";
//    _pMyShip = NULL; //MyShipScene‚ÉÝ’è‚µ‚Ä‚à‚ç‚¤
}
void MyShipDivingCamWorker::initialize() {
}

void MyShipDivingCamWorker::onSwitchedCameraWork() {
    GgafDx9Camera* pCam = P_CAM;
    GgafDx9CameraViewPoint* pVP = pCam->_pViewPoint;
    pCam->_pKuroko->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pCam->_pKuroko->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pCam->_pKuroko->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pKuroko->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pKuroko->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pKuroko->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    _move_target_X_CAM = P_CAM->_X;
    _move_target_Y_CAM = P_CAM->_Y;
    _move_target_Z_CAM = P_CAM->_Z;
    _move_target_X_VP = pVP->_X;
    _move_target_Y_VP = pVP->_Y;
    _move_target_Z_VP = pVP->_Z;
}
void MyShipDivingCamWorker::onUndoneCameraWork() {
}


MyShipDivingCamWorker::~MyShipDivingCamWorker() {
}
