#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyShipDivingCamWorker::MyShipDivingCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "MyShipDivingCamWorker";
    _pMyShip = NULL; //MyShipSceneに設定してもらう
    _move_target_X_CAM = 0;
    _move_target_Y_CAM = 0;
    _move_target_Z_CAM = 0;
    _move_target_X_VP = 0;
    _move_target_Y_VP = 0;
    _move_target_Z_VP = 0;
    _move_target_XY_CAM_UP = ANGLE90;
    _angXY_nowCamUp = ANGLE90;
}
void MyShipDivingCamWorker::initialize() {
    GgafDx9Camera* pCam = P_CAM;
    GgafDx9CameraViewPoint* pVP = pCam->_pViewPoint;
    setMoveTargetCamBy(P_CAM);
    setMoveTargetCamVpBy(pVP);

    _cam_velo_renge = 30000;
    pCam->_pMover->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pCam->_pMover->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pCam->_pMover->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pMover->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pMover->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pMover->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);

    _stop_renge = 60000;
}
void MyShipDivingCamWorker::setMoveTargetCamBy(GgafDx9Core::GgafDx9GeometricActor* pTarget) {
    _move_target_X_CAM = pTarget->_X;
    _move_target_Y_CAM = pTarget->_Y;
    _move_target_Z_CAM = pTarget->_Z;
}
void MyShipDivingCamWorker::setMoveTargetCamVpBy(GgafDx9Core::GgafDx9GeometricActor* pTarget) {
    _move_target_X_VP = pTarget->_X;
    _move_target_Y_VP = pTarget->_Y;
    _move_target_Z_VP = pTarget->_Z;
}

void MyShipDivingCamWorker::setMoveTargetCam(int X, int Y, int Z) {
    _move_target_X_CAM = X;
    _move_target_Y_CAM = Y;
    _move_target_Z_CAM = Z;
}
void MyShipDivingCamWorker::setMoveTargetCamVp(int X, int Y, int Z) {
    _move_target_X_VP = X;
    _move_target_Y_VP = Y;
    _move_target_Z_VP = Z;
}



void MyShipDivingCamWorker::processBehavior() {

    //DefaultMyShipDivingCamWorker::processBehavior();

    //初期カメラ移動範囲制限
    float revise = 0.7; //斜めから見るので補正値を掛ける。1.0の場合は原点からでドンピシャ。これは微調整を繰り返した
    GgafDx9Camera* pCam = P_CAM;
    GgafDx9CameraViewPoint* pVP = pCam->_pViewPoint;

    int cam_velo_renge = _cam_velo_renge;  //カメラの移動速度の最大、最小敷居値
    //カメラの移動速度の最大、最小制限を設定
    pCam->_pMover->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pMover->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pMover->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMover->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMover->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMover->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);

    //カメラ、及びビューポイントの移動速度を求める。

    //カメラの目標座標までの各軸の距離（座標差分）
    int dX_CAM = _move_target_X_CAM - pCam->_X;
    int dY_CAM = _move_target_Y_CAM - pCam->_Y;
    int dZ_CAM = _move_target_Z_CAM - pCam->_Z;
    //ビューポイントの目標座標までの各軸の距離（座標差分）
    int dX_VP = _move_target_X_VP - pVP->_X;
    int dY_VP = _move_target_Y_VP - pVP->_Y;
    int dZ_VP = _move_target_Z_VP - pVP->_Z;
    velo veloVxRenge = 4000;
    velo veloVyRenge = 4000;
    velo veloVzRenge = 4000;

    velo last_CAM_veloVxMv = pCam->_pMover->_veloVxMv;
    velo  new_CAM_veloVxMv = dX_CAM*1.0 / _stop_renge;
    if (last_CAM_veloVxMv-veloVxRenge <= new_CAM_veloVxMv && new_CAM_veloVxMv <= last_CAM_veloVxMv+veloVxRenge) {
        pCam->_pMover->setVxMvVelo(new_CAM_veloVxMv);
    } else {
        if (last_CAM_veloVxMv-veloVxRenge > new_CAM_veloVxMv) {
            pCam->_pMover->setVxMvVelo(last_CAM_veloVxMv-veloVxRenge);
        } else if (new_CAM_veloVxMv > last_CAM_veloVxMv+veloVxRenge) {
            pCam->_pMover->setVxMvVelo(last_CAM_veloVxMv+veloVxRenge);
        }
    }
    velo last_VP_veloVxMv = pVP->_pMover->_veloVxMv;
    velo  new_VP_veloVxMv = dX_VP*1.0 / _stop_renge;
    if (last_VP_veloVxMv-veloVxRenge <= new_VP_veloVxMv && new_VP_veloVxMv <= last_VP_veloVxMv+veloVxRenge) {
        pVP->_pMover->setVxMvVelo(new_VP_veloVxMv);
    } else {
        if (last_VP_veloVxMv-veloVxRenge > new_VP_veloVxMv) {
            pVP->_pMover->setVxMvVelo(last_VP_veloVxMv-veloVxRenge);
        } else if (new_VP_veloVxMv > last_VP_veloVxMv+veloVxRenge) {
            pVP->_pMover->setVxMvVelo(last_VP_veloVxMv+veloVxRenge);
        }
    }

    velo last_CAM_veloVyMv = pCam->_pMover->_veloVyMv;
    velo  new_CAM_veloVyMv = dY_CAM*1.0 / _stop_renge;
    if (last_CAM_veloVyMv-veloVyRenge <= new_CAM_veloVyMv && new_CAM_veloVyMv <= last_CAM_veloVyMv+veloVyRenge) {
        pCam->_pMover->setVyMvVelo(new_CAM_veloVyMv);
    } else {
        if (last_CAM_veloVyMv-veloVyRenge > new_CAM_veloVyMv) {
            pCam->_pMover->setVyMvVelo(last_CAM_veloVyMv-veloVyRenge);
        } else if (new_CAM_veloVyMv > last_CAM_veloVyMv+veloVyRenge) {
            pCam->_pMover->setVyMvVelo(last_CAM_veloVyMv+veloVyRenge);
        }
    }
    velo last_VP_veloVyMv = pVP->_pMover->_veloVyMv;
    velo  new_VP_veloVyMv = dY_VP*1.0 / _stop_renge;
    if (last_VP_veloVyMv-veloVyRenge <= new_VP_veloVyMv && new_VP_veloVyMv <= last_VP_veloVyMv+veloVyRenge) {
        pVP->_pMover->setVyMvVelo(new_VP_veloVyMv);
    } else {
        if (last_VP_veloVyMv-veloVyRenge > new_VP_veloVyMv) {
            pVP->_pMover->setVyMvVelo(last_VP_veloVyMv-veloVyRenge);
        } else if (new_VP_veloVyMv > last_VP_veloVyMv+veloVyRenge) {
            pVP->_pMover->setVyMvVelo(last_VP_veloVyMv+veloVyRenge);
        }
    }

    velo last_CAM_veloVzMv = pCam->_pMover->_veloVzMv;
    velo  new_CAM_veloVzMv = dZ_CAM*1.0 / _stop_renge;
    if (last_CAM_veloVzMv-veloVzRenge <= new_CAM_veloVzMv && new_CAM_veloVzMv <= last_CAM_veloVzMv+veloVzRenge) {
        pCam->_pMover->setVzMvVelo(new_CAM_veloVzMv);
    } else {
        if (last_CAM_veloVzMv-veloVzRenge > new_CAM_veloVzMv) {
            pCam->_pMover->setVzMvVelo(last_CAM_veloVzMv-veloVzRenge);
        } else if (new_CAM_veloVzMv > last_CAM_veloVzMv+veloVzRenge) {
            pCam->_pMover->setVzMvVelo(last_CAM_veloVzMv+veloVzRenge);
        }
    }
    velo last_VP_veloVzMv = pVP->_pMover->_veloVzMv;
    velo  new_VP_veloVzMv = dZ_VP*1.0 / _stop_renge;
    if (last_VP_veloVzMv-veloVzRenge <= new_VP_veloVzMv && new_VP_veloVzMv <= last_VP_veloVzMv+veloVzRenge) {
        pVP->_pMover->setVzMvVelo(new_VP_veloVzMv);
    } else {
        if (last_VP_veloVzMv-veloVzRenge > new_VP_veloVzMv) {
            pVP->_pMover->setVzMvVelo(last_VP_veloVzMv-veloVzRenge);
        } else if (new_VP_veloVzMv > last_VP_veloVzMv+veloVzRenge) {
            pVP->_pMover->setVzMvVelo(last_VP_veloVzMv+veloVzRenge);
        }
    }

    //カメラのUPを計算
    angvelo angvelo_cam_up = cam_velo_renge/20;

    if (_angXY_nowCamUp != _move_target_XY_CAM_UP) {
        angle da = GgafDx9Util::getAngDiff(_angXY_nowCamUp, _move_target_XY_CAM_UP);
        if (-angvelo_cam_up < da && da < angvelo_cam_up) {
            _angXY_nowCamUp = _move_target_XY_CAM_UP;
        } else {
            _angXY_nowCamUp += (angvelo_cam_up * sgn(da));
        }
        _angXY_nowCamUp = GgafDx9Util::simplifyAng(_angXY_nowCamUp);
        pCam->_pVecCamUp->x = GgafDx9Util::COS[_angXY_nowCamUp/ANGLE_RATE];
        pCam->_pVecCamUp->y = GgafDx9Util::SIN[_angXY_nowCamUp/ANGLE_RATE];
        pCam->_pVecCamUp->z = 0.0f;
    }

    pCam->_pMover->behave();
    pVP->_pMover->behave();

}
MyShipDivingCamWorker::~MyShipDivingCamWorker() {
}
