#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

CameraWorker::CameraWorker(const char* prm_name) : GgafMainActor(prm_name, NULL) {
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
    //���ӁFCamera�͂܂���������Ă��Ȃ����߂�����P_CAM�͎g�p�s��
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

void CameraWorker::setMoveTargetCam(coord X, coord Y, coord Z) {
    _move_target_X_CAM = X;
    _move_target_Y_CAM = Y;
    _move_target_Z_CAM = Z;
}
void CameraWorker::setMoveTargetCamVp(coord X, coord Y, coord Z) {
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

    //�����J�����ړ��͈͐���
//    float revise = 0.7; //�΂߂��猩��̂ŕ␳�l���|����B1.0�̏ꍇ�͌��_����Ńh���s�V���B����͔��������J��Ԃ���
    GgafDx9Camera* pCam = P_CAM;
    GgafDx9GeometricActor* pVP = pCam->_pViewPoint;

    int cam_velo_renge = _cam_velo_renge;  //�J�����̈ړ����x�̍ő�A�ŏ��~���l
    //�J�����̈ړ����x�̍ő�A�ŏ�������ݒ�
    pCam->_pKurokoB->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pKurokoB->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pKurokoB->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKurokoB->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKurokoB->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKurokoB->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);

    //�J�����A�y�уr���[�|�C���g�̈ړ����x�����߂�B

    //�J�����̖ڕW���W�܂ł̊e���̋����i���W�����j
    int dX_CAM = _move_target_X_CAM - pCam->_X;
    int dY_CAM = _move_target_Y_CAM - pCam->_Y;
    int dZ_CAM = _move_target_Z_CAM - pCam->_Z;
    if ( _pLockOnTarget) {
        _move_target_X_VP = _pLockOnTarget->_X;
        _move_target_Y_VP = _pLockOnTarget->_Y;
        _move_target_Z_VP = _pLockOnTarget->_Z;
    }
    //�r���[�|�C���g�̖ڕW���W�܂ł̊e���̋����i���W�����j
    int dX_VP = _move_target_X_VP - pVP->_X;
    int dY_VP = _move_target_Y_VP - pVP->_Y;
    int dZ_VP = _move_target_Z_VP - pVP->_Z;
    velo veloVxRenge = 4000;
    velo veloVyRenge = 4000;
    velo veloVzRenge = 4000;

    velo last_CAM_veloVxMv = pCam->_pKurokoB->_veloVxMv;
    velo  new_CAM_veloVxMv = _burenai_speed*(dX_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVxMv-veloVxRenge <= new_CAM_veloVxMv && new_CAM_veloVxMv <= last_CAM_veloVxMv+veloVxRenge) {
        pCam->_pKurokoB->setVxMvVelo(new_CAM_veloVxMv);
    } else {
        if (last_CAM_veloVxMv-veloVxRenge > new_CAM_veloVxMv) {
            pCam->_pKurokoB->setVxMvVelo(last_CAM_veloVxMv-veloVxRenge);
        } else if (new_CAM_veloVxMv > last_CAM_veloVxMv+veloVxRenge) {
            pCam->_pKurokoB->setVxMvVelo(last_CAM_veloVxMv+veloVxRenge);
        }
    }
    velo last_VP_veloVxMv = pVP->_pKurokoB->_veloVxMv;
    velo  new_VP_veloVxMv = _burenai_speed*(dX_VP*1.0 / _stop_renge);
    if (last_VP_veloVxMv-veloVxRenge <= new_VP_veloVxMv && new_VP_veloVxMv <= last_VP_veloVxMv+veloVxRenge) {
        pVP->_pKurokoB->setVxMvVelo(new_VP_veloVxMv);
    } else {
        if (last_VP_veloVxMv-veloVxRenge > new_VP_veloVxMv) {
            pVP->_pKurokoB->setVxMvVelo(last_VP_veloVxMv-veloVxRenge);
        } else if (new_VP_veloVxMv > last_VP_veloVxMv+veloVxRenge) {
            pVP->_pKurokoB->setVxMvVelo(last_VP_veloVxMv+veloVxRenge);
        }
    }

    velo last_CAM_veloVyMv = pCam->_pKurokoB->_veloVyMv;
    velo  new_CAM_veloVyMv = _burenai_speed*(dY_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVyMv-veloVyRenge <= new_CAM_veloVyMv && new_CAM_veloVyMv <= last_CAM_veloVyMv+veloVyRenge) {
        pCam->_pKurokoB->setVyMvVelo(new_CAM_veloVyMv);
    } else {
        if (last_CAM_veloVyMv-veloVyRenge > new_CAM_veloVyMv) {
            pCam->_pKurokoB->setVyMvVelo(last_CAM_veloVyMv-veloVyRenge);
        } else if (new_CAM_veloVyMv > last_CAM_veloVyMv+veloVyRenge) {
            pCam->_pKurokoB->setVyMvVelo(last_CAM_veloVyMv+veloVyRenge);
        }
    }
    velo last_VP_veloVyMv = pVP->_pKurokoB->_veloVyMv;
    velo  new_VP_veloVyMv = _burenai_speed*(dY_VP*1.0 / _stop_renge);
    if (last_VP_veloVyMv-veloVyRenge <= new_VP_veloVyMv && new_VP_veloVyMv <= last_VP_veloVyMv+veloVyRenge) {
        pVP->_pKurokoB->setVyMvVelo(new_VP_veloVyMv);
    } else {
        if (last_VP_veloVyMv-veloVyRenge > new_VP_veloVyMv) {
            pVP->_pKurokoB->setVyMvVelo(last_VP_veloVyMv-veloVyRenge);
        } else if (new_VP_veloVyMv > last_VP_veloVyMv+veloVyRenge) {
            pVP->_pKurokoB->setVyMvVelo(last_VP_veloVyMv+veloVyRenge);
        }
    }

    velo last_CAM_veloVzMv = pCam->_pKurokoB->_veloVzMv;
    velo  new_CAM_veloVzMv = _burenai_speed*(dZ_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVzMv-veloVzRenge <= new_CAM_veloVzMv && new_CAM_veloVzMv <= last_CAM_veloVzMv+veloVzRenge) {
        pCam->_pKurokoB->setVzMvVelo(new_CAM_veloVzMv);
    } else {
        if (last_CAM_veloVzMv-veloVzRenge > new_CAM_veloVzMv) {
            pCam->_pKurokoB->setVzMvVelo(last_CAM_veloVzMv-veloVzRenge);
        } else if (new_CAM_veloVzMv > last_CAM_veloVzMv+veloVzRenge) {
            pCam->_pKurokoB->setVzMvVelo(last_CAM_veloVzMv+veloVzRenge);
        }
    }
    velo last_VP_veloVzMv = pVP->_pKurokoB->_veloVzMv;
    velo  new_VP_veloVzMv = _burenai_speed*(dZ_VP*1.0 / _stop_renge);
    if (last_VP_veloVzMv-veloVzRenge <= new_VP_veloVzMv && new_VP_veloVzMv <= last_VP_veloVzMv+veloVzRenge) {
        pVP->_pKurokoB->setVzMvVelo(new_VP_veloVzMv);
    } else {
        if (last_VP_veloVzMv-veloVzRenge > new_VP_veloVzMv) {
            pVP->_pKurokoB->setVzMvVelo(last_VP_veloVzMv-veloVzRenge);
        } else if (new_VP_veloVzMv > last_VP_veloVzMv+veloVzRenge) {
            pVP->_pKurokoB->setVzMvVelo(last_VP_veloVzMv+veloVzRenge);
        }
    }

    //�J������UP���v�Z
    ang_velo ang_velo_cam_up = cam_velo_renge/20;

    if (_angXY_nowCamUp != _move_target_XY_CAM_UP) {
        angle da = GgafDx9Util::getAngDiff(_angXY_nowCamUp, _move_target_XY_CAM_UP);
        if (-ang_velo_cam_up < da && da < ang_velo_cam_up) {
            _angXY_nowCamUp = _move_target_XY_CAM_UP;
        } else {
            _angXY_nowCamUp += (ang_velo_cam_up * sgn(da));
        }
        _angXY_nowCamUp = GgafDx9Util::simplifyAng(_angXY_nowCamUp);
        pCam->_pVecCamUp->x = GgafDx9Util::COS[_angXY_nowCamUp/ANGLE_RATE];
        pCam->_pVecCamUp->y = GgafDx9Util::SIN[_angXY_nowCamUp/ANGLE_RATE];
        pCam->_pVecCamUp->z = 0.0f;
    }

    pCam->_pKurokoB->behave();
    pVP->_pKurokoB->behave();

}
CameraWorker::~CameraWorker() {
}
