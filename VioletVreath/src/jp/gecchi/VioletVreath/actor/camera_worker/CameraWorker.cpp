#include "stdafx.h"
#include "CameraWorker.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/actor/ViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CameraWorker::CameraWorker(const char* prm_name) : GgafMainActor(prm_name, nullptr) {
    _class_name = "CameraWorker";
    pos_camera_ = 0;
    dZ_camera_init_ = 0;
    pLockOnTarget_ = nullptr;
    move_target_XY_CAM_UP_ = D90ANG;
    angXY_nowCamUp_ = D90ANG;
    burenai_speed_ = 10000;
    cam_velo_renge_ = 30000;
    stop_renge_ = 60000;
    move_target_x_CAM_ = 0;
    move_target_y_CAM_ = 0;
    move_target_z_CAM_ = 0;
    move_target_x_VP_ =  0;
    move_target_y_VP_ =  0;
    move_target_z_VP_ =  0;
    frame_of_behaving_since_onSwitch_ = 0;
    //注意：Cameraはまだ生成されていないためここでP_CAMは使用不可
}

void CameraWorker::setMoveTargetCamBy(GgafDxCore::GgafDxGeometricActor* pTarget) {
    move_target_x_CAM_ = pTarget->_x;
    move_target_y_CAM_ = pTarget->_y;
    move_target_z_CAM_ = pTarget->_z;
}
void CameraWorker::setMoveTargetCamVpBy(GgafDxCore::GgafDxGeometricActor* pTarget) {
    move_target_x_VP_ = pTarget->_x;
    move_target_y_VP_ = pTarget->_y;
    move_target_z_VP_ = pTarget->_z;
}

void CameraWorker::setMoveTargetCam(coord X, coord Y, coord Z) {
    move_target_x_CAM_ = X;
    move_target_y_CAM_ = Y;
    move_target_z_CAM_ = Z;
}
void CameraWorker::setMoveTargetCamVp(coord X, coord Y, coord Z) {
    move_target_x_VP_ = X;
    move_target_y_VP_ = Y;
    move_target_z_VP_ = Z;
}
void CameraWorker::lockCamVp(GgafDxCore::GgafDxGeometricActor* pTarget) {
    pLockOnTarget_ = pTarget;
}
void CameraWorker::unlockCamVp() {
    pLockOnTarget_ = nullptr;
}


void CameraWorker::onSwitchCameraWork() {
    Camera* pCam = P_CAM;
    ViewPoint* pVP = (ViewPoint*)(pCam->getViewPoint());
    setMoveTargetCamBy(pCam);
    setMoveTargetCamVpBy(pVP);
    pCam->_pKuroko->stopMv();
    pCam->_pKuroko->stopTurnMvAng();
    pCam->_pKuroko->stopTurnFaceAng();
    pCam->_pKuroko->hlprA()->stopSlidingMv();
    pCam->pAxsMver_->stopGravitationMvSequence();
    pCam->pAxsMver_->setZeroVxyzMvVelo();
    pCam->pAxsMver_->setZeroVxyzMvAcce();

    pVP->_pKuroko->stopMv();
    pVP->_pKuroko->stopTurnMvAng();
    pVP->_pKuroko->stopTurnFaceAng();
    pVP->_pKuroko->hlprA()->stopSlidingMv();
    pVP->pAxsMver_->stopGravitationMvSequence();
    pVP->pAxsMver_->setZeroVxyzMvVelo();
    pVP->pAxsMver_->setZeroVxyzMvAcce();

    angXY_nowCamUp_ = UTIL::getAngle2D(pCam->_pVecCamUp->x, pCam->_pVecCamUp->y);
    move_target_XY_CAM_UP_ = angXY_nowCamUp_;
    //frame_of_behaving_since_onSwitch_ = 0; は Universe::switchCameraWork() が行う。
}

void CameraWorker::onUndoCameraWork() {
}

void CameraWorker::onSwitchToOtherCameraWork() {
}

void CameraWorker::onCameBackFromOtherCameraWork() {
    angXY_nowCamUp_ = UTIL::getAngle2D(P_CAM->_pVecCamUp->x, P_CAM->_pVecCamUp->y);
}

void CameraWorker::processBehavior() {

    //DefaultCameraWorker::processBehavior();
    //初期カメラ移動範囲制限
//    float revise = 0.7; //斜めから見るので補正値を掛ける。1.0の場合は原点からでドンピシャ。これは微調整を繰り返した
    Camera* pCam = P_CAM;
    ViewPoint* pVP = (ViewPoint*)(pCam->getViewPoint());

    int cam_velo_renge = cam_velo_renge_;  //カメラの移動速度の最大、最小敷居値
    //カメラの移動速度の最大、最小制限を設定
    pCam->pAxsMver_->forceVxyzMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->pAxsMver_->forceVxyzMvVeloRange(-cam_velo_renge, cam_velo_renge);

    //カメラ、及びビューポイントの移動速度を求める。

    //カメラの目標座標までの各軸の距離（座標差分）
    int dX_CAM = move_target_x_CAM_ - pCam->_x;
    int dY_CAM = move_target_y_CAM_ - pCam->_y;
    int dZ_CAM = move_target_z_CAM_ - pCam->_z;
    if ( pLockOnTarget_) {
        move_target_x_VP_ = pLockOnTarget_->_x;
        move_target_y_VP_ = pLockOnTarget_->_y;
        move_target_z_VP_ = pLockOnTarget_->_z;
    }
    //ビューポイントの目標座標までの各軸の距離（座標差分）
    int dX_VP = move_target_x_VP_ - pVP->_x;
    int dY_VP = move_target_y_VP_ - pVP->_y;
    int dZ_VP = move_target_z_VP_ - pVP->_z;
    static const velo veloVxRenge = 4000;
    static const velo veloVyRenge = 4000;
    static const velo veloVzRenge = 4000;

    velo last_CAM_veloVxMv = pCam->pAxsMver_->_veloVxMv;
    velo  new_CAM_veloVxMv = burenai_speed_*(dX_CAM*1.0 / stop_renge_);
    if (last_CAM_veloVxMv-veloVxRenge <= new_CAM_veloVxMv && new_CAM_veloVxMv <= last_CAM_veloVxMv+veloVxRenge) {
        pCam->pAxsMver_->setVxMvVelo(new_CAM_veloVxMv);
    } else {
        if (last_CAM_veloVxMv-veloVxRenge > new_CAM_veloVxMv) {
            pCam->pAxsMver_->setVxMvVelo(last_CAM_veloVxMv-veloVxRenge);
        } else if (new_CAM_veloVxMv > last_CAM_veloVxMv+veloVxRenge) {
            pCam->pAxsMver_->setVxMvVelo(last_CAM_veloVxMv+veloVxRenge);
        }
    }
    velo last_VP_veloVxMv = pVP->pAxsMver_->_veloVxMv;
    velo  new_VP_veloVxMv = burenai_speed_*(dX_VP*1.0 / stop_renge_);
    if (last_VP_veloVxMv-veloVxRenge <= new_VP_veloVxMv && new_VP_veloVxMv <= last_VP_veloVxMv+veloVxRenge) {
        pVP->pAxsMver_->setVxMvVelo(new_VP_veloVxMv);
    } else {
        if (last_VP_veloVxMv-veloVxRenge > new_VP_veloVxMv) {
            pVP->pAxsMver_->setVxMvVelo(last_VP_veloVxMv-veloVxRenge);
        } else if (new_VP_veloVxMv > last_VP_veloVxMv+veloVxRenge) {
            pVP->pAxsMver_->setVxMvVelo(last_VP_veloVxMv+veloVxRenge);
        }
    }

    velo last_CAM_veloVyMv = pCam->pAxsMver_->_veloVyMv;
    velo  new_CAM_veloVyMv = burenai_speed_*(dY_CAM*1.0 / stop_renge_);
    if (last_CAM_veloVyMv-veloVyRenge <= new_CAM_veloVyMv && new_CAM_veloVyMv <= last_CAM_veloVyMv+veloVyRenge) {
        pCam->pAxsMver_->setVyMvVelo(new_CAM_veloVyMv);
    } else {
        if (last_CAM_veloVyMv-veloVyRenge > new_CAM_veloVyMv) {
            pCam->pAxsMver_->setVyMvVelo(last_CAM_veloVyMv-veloVyRenge);
        } else if (new_CAM_veloVyMv > last_CAM_veloVyMv+veloVyRenge) {
            pCam->pAxsMver_->setVyMvVelo(last_CAM_veloVyMv+veloVyRenge);
        }
    }
    velo last_VP_veloVyMv = pVP->pAxsMver_->_veloVyMv;
    velo  new_VP_veloVyMv = burenai_speed_*(dY_VP*1.0 / stop_renge_);
    if (last_VP_veloVyMv-veloVyRenge <= new_VP_veloVyMv && new_VP_veloVyMv <= last_VP_veloVyMv+veloVyRenge) {
        pVP->pAxsMver_->setVyMvVelo(new_VP_veloVyMv);
    } else {
        if (last_VP_veloVyMv-veloVyRenge > new_VP_veloVyMv) {
            pVP->pAxsMver_->setVyMvVelo(last_VP_veloVyMv-veloVyRenge);
        } else if (new_VP_veloVyMv > last_VP_veloVyMv+veloVyRenge) {
            pVP->pAxsMver_->setVyMvVelo(last_VP_veloVyMv+veloVyRenge);
        }
    }

    velo last_CAM_veloVzMv = pCam->pAxsMver_->_veloVzMv;
    velo  new_CAM_veloVzMv = burenai_speed_*(dZ_CAM*1.0 / stop_renge_);
    if (last_CAM_veloVzMv-veloVzRenge <= new_CAM_veloVzMv && new_CAM_veloVzMv <= last_CAM_veloVzMv+veloVzRenge) {
        pCam->pAxsMver_->setVzMvVelo(new_CAM_veloVzMv);
    } else {
        if (last_CAM_veloVzMv-veloVzRenge > new_CAM_veloVzMv) {
            pCam->pAxsMver_->setVzMvVelo(last_CAM_veloVzMv-veloVzRenge);
        } else if (new_CAM_veloVzMv > last_CAM_veloVzMv+veloVzRenge) {
            pCam->pAxsMver_->setVzMvVelo(last_CAM_veloVzMv+veloVzRenge);
        }
    }
    velo last_VP_veloVzMv = pVP->pAxsMver_->_veloVzMv;
    velo  new_VP_veloVzMv = burenai_speed_*(dZ_VP*1.0 / stop_renge_);
    if (last_VP_veloVzMv-veloVzRenge <= new_VP_veloVzMv && new_VP_veloVzMv <= last_VP_veloVzMv+veloVzRenge) {
        pVP->pAxsMver_->setVzMvVelo(new_VP_veloVzMv);
    } else {
        if (last_VP_veloVzMv-veloVzRenge > new_VP_veloVzMv) {
            pVP->pAxsMver_->setVzMvVelo(last_VP_veloVzMv-veloVzRenge);
        } else if (new_VP_veloVzMv > last_VP_veloVzMv+veloVzRenge) {
            pVP->pAxsMver_->setVzMvVelo(last_VP_veloVzMv+veloVzRenge);
        }
    }

    //カメラのUPを計算
    angvelo angvelo_cam_up = cam_velo_renge/20;

    if (angXY_nowCamUp_ != move_target_XY_CAM_UP_) {
        angle da = UTIL::getAngDiff(angXY_nowCamUp_, move_target_XY_CAM_UP_);
        if (-angvelo_cam_up < da && da < angvelo_cam_up) {
            angXY_nowCamUp_ = move_target_XY_CAM_UP_;
        } else {
            angXY_nowCamUp_ += (angvelo_cam_up * SGN(da));
        }
        angXY_nowCamUp_ = UTIL::simplifyAng(angXY_nowCamUp_);
        pCam->_pVecCamUp->x = ANG_COS(angXY_nowCamUp_);
        pCam->_pVecCamUp->y = ANG_SIN(angXY_nowCamUp_);
        pCam->_pVecCamUp->z = 0.0f;
    }

}
CameraWorker::~CameraWorker() {
}
