#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

CameraWorker::CameraWorker(const char* prm_name) : GgafMainActor(prm_name) {
    _class_name = "CameraWorker";
    _pos_camera = 0;
    _pLockOnTarget = NULL;
    _move_target_XY_CAM_UP = ANGLE90;
    _angXY_nowCamUp = ANGLE90;
    _burenai_speed = 10000;
    _cam_velo_renge = 30000;
    _stop_renge = 60000;
    _move_target_X_CAM = 0;
    _move_target_Y_CAM = 0;
    _move_target_Z_CAM = 0;
    _move_target_X_VP =  0;
    _move_target_Y_VP =  0;
    _move_target_Z_VP =  0;
    //注意：Cameraはまだ生成されていないためここでP_CAMは使用不可
}

void CameraWorker::setMoveTargetCamBy(GgafDx9Core::GgafDx9GeometricActor* pTarget) {
    _move_target_X_CAM = pTarget->_X;
    _move_target_Y_CAM = pTarget->_Y;
    _move_target_Z_CAM = pTarget->_Z;
}
void CameraWorker::setMoveTargetCamVpBy(GgafDx9Core::GgafDx9GeometricActor* pTarget) {
    _move_target_X_VP = pTarget->_X;
    _move_target_Y_VP = pTarget->_Y;
    _move_target_Z_VP = pTarget->_Z;
}

void CameraWorker::setMoveTargetCam(int X, int Y, int Z) {
    _move_target_X_CAM = X;
    _move_target_Y_CAM = Y;
    _move_target_Z_CAM = Z;
}
void CameraWorker::setMoveTargetCamVp(int X, int Y, int Z) {
    _move_target_X_VP = X;
    _move_target_Y_VP = Y;
    _move_target_Z_VP = Z;
}
void CameraWorker::lockCamVp(GgafDx9Core::GgafDx9GeometricActor* pTarget) {
    _pLockOnTarget = pTarget;
}
void CameraWorker::unlockCamVp() {
    _pLockOnTarget = NULL;
}


void CameraWorker::onSwitchCameraWork() {
    setMoveTargetCamBy(P_CAM);
    setMoveTargetCamVpBy(P_CAM->_pViewPoint);
    _angXY_nowCamUp = GgafDx9Util::getAngle2D(P_CAM->_pVecCamUp->x, P_CAM->_pVecCamUp->y);
    _move_target_XY_CAM_UP = _angXY_nowCamUp;
}

void CameraWorker::onUndoCameraWork() {
}

void CameraWorker::onSwitchToOherCameraWork() {
}

void CameraWorker::onCameBackFromOtherCameraWork() {
    _angXY_nowCamUp = GgafDx9Util::getAngle2D(P_CAM->_pVecCamUp->x, P_CAM->_pVecCamUp->y);
}

void CameraWorker::processBehavior() {

    //DefaultCameraWorker::processBehavior();

    //初期カメラ移動範囲制限
//    float revise = 0.7; //斜めから見るので補正値を掛ける。1.0の場合は原点からでドンピシャ。これは微調整を繰り返した
    GgafDx9Camera* pCam = P_CAM;
    GgafDx9GeometricActor* pVP = pCam->_pViewPoint;

    int cam_velo_renge = _cam_velo_renge;  //カメラの移動速度の最大、最小敷居値
    //カメラの移動速度の最大、最小制限を設定
    pCam->_pMvTransporter->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pMvTransporter->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pMvTransporter->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMvTransporter->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMvTransporter->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMvTransporter->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);

    //カメラ、及びビューポイントの移動速度を求める。

    //カメラの目標座標までの各軸の距離（座標差分）
    int dX_CAM = _move_target_X_CAM - pCam->_X;
    int dY_CAM = _move_target_Y_CAM - pCam->_Y;
    int dZ_CAM = _move_target_Z_CAM - pCam->_Z;
    if ( _pLockOnTarget) {
        _move_target_X_VP = _pLockOnTarget->_X;
        _move_target_Y_VP = _pLockOnTarget->_Y;
        _move_target_Z_VP = _pLockOnTarget->_Z;
    }
    //ビューポイントの目標座標までの各軸の距離（座標差分）
    int dX_VP = _move_target_X_VP - pVP->_X;
    int dY_VP = _move_target_Y_VP - pVP->_Y;
    int dZ_VP = _move_target_Z_VP - pVP->_Z;
    velo veloVxRenge = 4000;
    velo veloVyRenge = 4000;
    velo veloVzRenge = 4000;

    velo last_CAM_veloVxMv = pCam->_pMvTransporter->_veloVxMv;
    velo  new_CAM_veloVxMv = _burenai_speed*(dX_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVxMv-veloVxRenge <= new_CAM_veloVxMv && new_CAM_veloVxMv <= last_CAM_veloVxMv+veloVxRenge) {
        pCam->_pMvTransporter->setVxMvVelo(new_CAM_veloVxMv);
    } else {
        if (last_CAM_veloVxMv-veloVxRenge > new_CAM_veloVxMv) {
            pCam->_pMvTransporter->setVxMvVelo(last_CAM_veloVxMv-veloVxRenge);
        } else if (new_CAM_veloVxMv > last_CAM_veloVxMv+veloVxRenge) {
            pCam->_pMvTransporter->setVxMvVelo(last_CAM_veloVxMv+veloVxRenge);
        }
    }
    velo last_VP_veloVxMv = pVP->_pMvTransporter->_veloVxMv;
    velo  new_VP_veloVxMv = _burenai_speed*(dX_VP*1.0 / _stop_renge);
    if (last_VP_veloVxMv-veloVxRenge <= new_VP_veloVxMv && new_VP_veloVxMv <= last_VP_veloVxMv+veloVxRenge) {
        pVP->_pMvTransporter->setVxMvVelo(new_VP_veloVxMv);
    } else {
        if (last_VP_veloVxMv-veloVxRenge > new_VP_veloVxMv) {
            pVP->_pMvTransporter->setVxMvVelo(last_VP_veloVxMv-veloVxRenge);
        } else if (new_VP_veloVxMv > last_VP_veloVxMv+veloVxRenge) {
            pVP->_pMvTransporter->setVxMvVelo(last_VP_veloVxMv+veloVxRenge);
        }
    }

    velo last_CAM_veloVyMv = pCam->_pMvTransporter->_veloVyMv;
    velo  new_CAM_veloVyMv = _burenai_speed*(dY_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVyMv-veloVyRenge <= new_CAM_veloVyMv && new_CAM_veloVyMv <= last_CAM_veloVyMv+veloVyRenge) {
        pCam->_pMvTransporter->setVyMvVelo(new_CAM_veloVyMv);
    } else {
        if (last_CAM_veloVyMv-veloVyRenge > new_CAM_veloVyMv) {
            pCam->_pMvTransporter->setVyMvVelo(last_CAM_veloVyMv-veloVyRenge);
        } else if (new_CAM_veloVyMv > last_CAM_veloVyMv+veloVyRenge) {
            pCam->_pMvTransporter->setVyMvVelo(last_CAM_veloVyMv+veloVyRenge);
        }
    }
    velo last_VP_veloVyMv = pVP->_pMvTransporter->_veloVyMv;
    velo  new_VP_veloVyMv = _burenai_speed*(dY_VP*1.0 / _stop_renge);
    if (last_VP_veloVyMv-veloVyRenge <= new_VP_veloVyMv && new_VP_veloVyMv <= last_VP_veloVyMv+veloVyRenge) {
        pVP->_pMvTransporter->setVyMvVelo(new_VP_veloVyMv);
    } else {
        if (last_VP_veloVyMv-veloVyRenge > new_VP_veloVyMv) {
            pVP->_pMvTransporter->setVyMvVelo(last_VP_veloVyMv-veloVyRenge);
        } else if (new_VP_veloVyMv > last_VP_veloVyMv+veloVyRenge) {
            pVP->_pMvTransporter->setVyMvVelo(last_VP_veloVyMv+veloVyRenge);
        }
    }

    velo last_CAM_veloVzMv = pCam->_pMvTransporter->_veloVzMv;
    velo  new_CAM_veloVzMv = _burenai_speed*(dZ_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVzMv-veloVzRenge <= new_CAM_veloVzMv && new_CAM_veloVzMv <= last_CAM_veloVzMv+veloVzRenge) {
        pCam->_pMvTransporter->setVzMvVelo(new_CAM_veloVzMv);
    } else {
        if (last_CAM_veloVzMv-veloVzRenge > new_CAM_veloVzMv) {
            pCam->_pMvTransporter->setVzMvVelo(last_CAM_veloVzMv-veloVzRenge);
        } else if (new_CAM_veloVzMv > last_CAM_veloVzMv+veloVzRenge) {
            pCam->_pMvTransporter->setVzMvVelo(last_CAM_veloVzMv+veloVzRenge);
        }
    }
    velo last_VP_veloVzMv = pVP->_pMvTransporter->_veloVzMv;
    velo  new_VP_veloVzMv = _burenai_speed*(dZ_VP*1.0 / _stop_renge);
    if (last_VP_veloVzMv-veloVzRenge <= new_VP_veloVzMv && new_VP_veloVzMv <= last_VP_veloVzMv+veloVzRenge) {
        pVP->_pMvTransporter->setVzMvVelo(new_VP_veloVzMv);
    } else {
        if (last_VP_veloVzMv-veloVzRenge > new_VP_veloVzMv) {
            pVP->_pMvTransporter->setVzMvVelo(last_VP_veloVzMv-veloVzRenge);
        } else if (new_VP_veloVzMv > last_VP_veloVzMv+veloVzRenge) {
            pVP->_pMvTransporter->setVzMvVelo(last_VP_veloVzMv+veloVzRenge);
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

    pCam->_pMvTransporter->behave();
    pVP->_pMvTransporter->behave();

}
CameraWorker::~CameraWorker() {
}
