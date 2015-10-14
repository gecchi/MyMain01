#include "CameraWorker.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/camera/CameraUpVector.h"
#include "jp/gecchi/VioletVreath/actor/camera/CameraViewPoint.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CameraWorker::CameraWorker(const char* prm_name, Camera* prm_pCamera) : GgafMainActor(prm_name, nullptr) {
    _class_name = "CameraWorker";
    t_x_VP_ =  0;
    t_y_VP_ =  0;
    t_z_VP_ =  0;
    t_x_CAM_ =  0;
    t_y_CAM_ =  0;
    t_z_CAM_ =  0;
    frame_of_behaving_since_onSwitch_ = 0;
    pCam_ = prm_pCamera;
    pVp_ = (CameraViewPoint*)(pCam_->getCameraViewPoint());
    pUp_ = (CameraUpVector*)(pCam_->getCameraUpVector());
    t_cam_up_dir_ = DIR26( 0, 1, 0);
    vcv_dir_ = 0;
    vcv_dir_prev_ = vcv_dir_;

    static volatile bool is_init = CameraWorker::initStatic(); //�ÓI�����o������
    //���ӁFCamera�͂܂���������Ă��Ȃ����߂�����P_CAM�͎g�p�s��
}

int CameraWorker::relation_up_vec_[3*3*3][3*3*3];
int (*CameraWorker::relation_up_by_vec_)[3*3*3];
bool CameraWorker::initStatic() {
    for (int i = 0; i < 3*3*3; i++) {
        for (int j = 0; j < 3*3*3; j++) {
            CameraWorker::relation_up_vec_[i][j] = DIR26_NULL;
        }
    }
    CameraWorker::relation_up_by_vec_ =  (int (*)[3*3*3])(&(CameraWorker::relation_up_vec_[13][13])); //13 �� 3*3*3=27 �̐^�񒆂̗v�f�A_relation_up_vec[-13�`13][-13�`13]�ŃA�N�Z�X�����
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1,-1,-1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1,-1, 0)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1,-1, 1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 0,-1)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 0, 1)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 1,-1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 1, 0)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 1, 1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1,-1,-1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1,-1, 0)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1,-1, 1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 0,-1)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 0, 1)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 1,-1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 1, 0)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 1, 1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1,-1,-1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1,-1, 0)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1,-1, 1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 0,-1)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 0, 1)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 1,-1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 1, 0)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 1, 1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1,-1,-1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1,-1, 0)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1,-1, 1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 0,-1)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 0, 1)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 1,-1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 1, 0)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 1, 1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1, 1,-1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1, 1, 0)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1, 1, 1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0, 1,-1)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0, 1, 1)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1, 1,-1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1, 1, 0)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1, 1, 1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1,-1,-1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1,-1, 0)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1,-1, 1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0,-1,-1)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0,-1, 1)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1,-1,-1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1,-1, 0)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1,-1, 1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1,-1,-1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1,-1, 0)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1,-1, 1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0,-1,-1)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0,-1, 1)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1,-1,-1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1,-1, 0)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1,-1, 1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1, 1,-1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1, 1, 0)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1, 1, 1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0, 1,-1)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0, 1, 1)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1, 1,-1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1, 1, 0)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1, 1, 1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1,-1, 1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 0, 1)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 1, 1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0,-1, 1)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 0, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 1, 1)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1,-1, 1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 0, 1)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 1, 1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1,-1,-1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 0,-1)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 1,-1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0,-1,-1)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 0,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 1,-1)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1,-1,-1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 0,-1)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 1,-1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1,-1,-1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 0,-1)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 1,-1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0,-1,-1)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 0,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 1,-1)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1,-1,-1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 0,-1)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 1,-1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1,-1, 1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 0, 1)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 1, 1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0,-1, 1)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 0, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 1, 1)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1,-1, 1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 0, 1)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 1, 1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0, 1,-1)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0, 1, 1)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 0,-1)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 0, 1)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 1,-1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 1, 1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1,-1,-1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1,-1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1,-1, 1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1, 0,-1)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1, 0, 1)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0,-1,-1)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0,-1, 1)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1,-1,-1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1,-1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1,-1, 1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1, 0,-1)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1, 0, 1)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0,-1,-1)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0,-1, 1)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0, 1,-1)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0, 1, 1)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 0,-1)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 0, 1)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 1,-1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 1, 1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0,-1, 1)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 0, 1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 1, 1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1,-1, 0)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 1, 0)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1,-1, 1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 0, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 1, 1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1,-1,-1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 0,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 1,-1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1,-1, 0)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 1, 0)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0,-1,-1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 0,-1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 1,-1)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1,-1,-1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 0,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 1,-1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1,-1, 0)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 1, 0)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0,-1,-1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 0,-1)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 1,-1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0,-1, 1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 0, 1)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 1, 1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1,-1, 0)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 0, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 1, 0)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1,-1, 1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 0, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 1, 1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 0, 1)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 0, 1)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 0, 1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 1, 0)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 1, 0)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 1, 1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 1, 1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1,-1,-1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0,-1,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1,-1,-1)] = DIR26( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1,-1, 0)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1,-1, 0)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 0,-1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 0,-1)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 0,-1)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1,-1,-1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0,-1,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1,-1,-1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1,-1, 0)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0,-1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1,-1, 0)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 0,-1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 0,-1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 0,-1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 0, 1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 0, 1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 0, 1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 1, 0)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 1, 0)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 1, 1)] = DIR26(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 1, 1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0, 1,-1)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0, 1, 1)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 0,-1)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 0, 1)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 1,-1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 1, 1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1,-1,-1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1,-1, 1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1, 0,-1)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1, 0, 1)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0,-1,-1)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0,-1, 1)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1, 0,-1)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1, 0, 1)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0,-1,-1)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0,-1, 1)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1,-1,-1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1,-1, 1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 1,-1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 1, 1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0, 1,-1)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0, 1, 1)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 0,-1)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 0, 1)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0,-1, 1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 0, 1)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 1, 1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1,-1, 0)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 1, 0)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1,-1, 1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 0, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 1, 1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1,-1,-1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 0,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 1,-1)] = DIR26(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1,-1, 0)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 1, 0)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0,-1,-1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 0,-1)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 1,-1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1,-1, 0)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 0, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 1, 0)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0,-1,-1)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 0,-1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 1,-1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1,-1,-1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 0,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 1,-1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1,-1, 1)] = DIR26( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 0, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 1, 1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0,-1, 1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 0, 1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 1, 1)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1,-1, 0)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 1, 0)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 0, 1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 0, 1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 0, 1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1,-1, 0)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1,-1, 0)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1,-1, 1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0,-1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1,-1, 1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 1,-1)] = DIR26(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 1,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 1,-1)] = DIR26( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 1, 0)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 1, 0)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 0,-1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 0,-1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 0,-1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 1, 0)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 1, 0)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 0,-1)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 0,-1)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 0,-1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 1,-1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 1,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 1,-1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1,-1, 1)] = DIR26(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0,-1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1,-1, 1)] = DIR26( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 0, 1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 0, 1)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 0, 1)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1,-1, 0)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0,-1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1,-1, 0)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0, 0, 1)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0, 1, 1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 0, 1)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0,-1,-1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1, 0,-1)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1,-1, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1,-1,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0, 0,-1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0,-1,-1)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1, 0, 0)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1, 0,-1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1,-1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1,-1,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0, 0, 1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0, 1, 0)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 0, 0)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 0, 1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 0,-1)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 1, 0)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 1,-1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 1, 0,-1)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 1, 1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 1, 1,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 0, 1)] = DIR26( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0,-1, 0)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0,-1, 1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26(-1,-1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26(-1,-1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 0, 1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0,-1, 1)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26(-1, 0, 1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26(-1,-1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 0,-1)] = DIR26(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 1,-1)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 0,-1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 1,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 0, 1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0,-1, 1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1, 0, 1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1,-1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 0,-1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 1,-1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 0,-1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 1,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 0,-1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 1, 0)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 1,-1)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 0,-1)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 1,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 0, 1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0,-1, 0)] = DIR26(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0,-1, 1)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1, 0, 0)] = DIR26( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1, 0, 1)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1,-1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1,-1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 0,-1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0,-1, 0)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0,-1,-1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1, 0, 0)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1, 0,-1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1,-1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1,-1,-1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 0, 1)] = DIR26( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 1, 0)] = DIR26( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 1, 1)] = DIR26( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 0, 0)] = DIR26( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 0, 1)] = DIR26( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 1, 0)] = DIR26( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 0, 1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 1, 1)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 0, 1)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 1, 1)] = DIR26( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 0,-1)] = DIR26(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0,-1,-1)] = DIR26(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1, 0,-1)] = DIR26( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1,-1,-1)] = DIR26( 0, 0, 0);
    return true;
}

void CameraWorker::initialize() {
    t_x_VP_ = pVp_->_x;
    t_y_VP_ = pVp_->_y;
    t_z_VP_ = pVp_->_z;
    t_x_CAM_ = pCam_->_x;
    t_y_CAM_ = pCam_->_y;
    t_z_CAM_ = pCam_->_z;
    t_cam_up_dir_ = pUp_->up_dir_;
}
void CameraWorker::onActive() {
    //���݂̃^�[�Q�b�g���ă^�[�Q�b�g
    slideMvCamTo(t_x_CAM_, t_y_CAM_, t_z_CAM_, 60);
    slideMvVpTo(t_x_VP_, t_y_VP_, t_z_VP_, 60);
    slideMvUpVecTo(t_cam_up_dir_, 30);
}

void CameraWorker::onSwitchCameraWork() {
    //���݂̃^�[�Q�b�g���ă^�[�Q�b�g
    slideMvCamTo(t_x_CAM_, t_y_CAM_, t_z_CAM_, 60);
    slideMvVpTo(t_x_VP_, t_y_VP_, t_z_VP_, 60);
    slideMvUpVecTo(t_cam_up_dir_, 30);
}

void CameraWorker::onChangedToOtherCameraWork() {
}

void CameraWorker::targetAutoCamup() {
    //UP�x�N�g�����J���������_�x�N�g���ɂ���Ď����ݒ�
    vcv_dir_ = pCam_->getVpDirNo();
    if (vcv_dir_ != vcv_dir_prev_) { //�J���������_�x�N�g���̖ʔԍ����ω�������UP���P��l��
        frame up_frames = 30;
        int up_hx1, up_hy1, up_hz1;
        GgafDx26DirectionUtil::cnvDirNo2Sgn(pUp_->up_dir_, up_hx1, up_hy1, up_hz1);
        int up_dir_next = CameraWorker::relation_up_by_vec_[pUp_->up_dir_][vcv_dir_];
        if (up_dir_next == DIR26_NULL) {
            //FACE_XXX�́AUP�͓����K�v�Ȃ�
        } else {
            if (up_dir_next == DIR26( 0, 0, 0)) {
                //�J���������_�x�N�g���̖ʔԍ����AUP�̖ʔԍ��Ɠ������^���ɂȂ����B
                //���̏ꍇ�́A�J���������_�x�N�g���̈�O�̖ʔԍ����̗p����UP�̏ꏊ�����߂�B
                int up_dir_next_other = CameraWorker::relation_up_by_vec_[pUp_->up_dir_][vcv_dir_prev_];
                if (up_dir_next_other == DIR26_NULL) {
                    //FACE_XXX�́AUP�͓����K�v�Ȃ�
                } else {
                    if (up_dir_next_other == DIR26( 0, 0, 0)) {
                        //�J���������_�x�N�g���̖ʔԍ����^���ֈ�C�ɓ��������ƂɂȂ�B
                        //����グ�BUP�͂ǂ��ɍs���΂悢���s��B����������UP�͂��̂܂܁B
                    } else {
                        slideMvUpVecTo(up_dir_next_other, up_frames);
                    }
                }
            } else {
                //�J���������_�x�N�g���ʔԍ����AUP�x�N�g���ʔԍ��ɗאڂ����̂ŁA
                //���̗אږʂ̔��Α��̗אږʂ̕��p��UP�x�N�g���𓦂��B
                //�����́A�J���������_�x�N�g���ʔԍ����AUP�x�N�g���ʔԍ����璼�p�ȏ�̊p�x�ŉ�������̂ŁA
                //UP�x�N�g�����ߊ�点��B
                slideMvUpVecTo(up_dir_next, up_frames);
            }
        }

    }
    vcv_dir_prev_ = vcv_dir_;
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
void CameraWorker::mvCamTo(coord tx, coord ty, coord tz) {
    t_x_CAM_ = tx;
    t_y_CAM_ = ty;
    t_z_CAM_ = tz;
    pCam_->position(tx, ty, tz);
}

bool CameraWorker::isCamSliding() {
    return pCam_->isSliding();
}


void CameraWorker::slideMvVpTo(coord tx, coord ty, coord tz, frame t) {
    t_x_VP_ = tx;
    t_y_VP_ = ty;
    t_z_VP_ = tz;
    pVp_->slideMvTo(tx, ty, tz, t);
}
void CameraWorker::slideMvUpVecTo(coord tx, coord ty, coord tz, frame t) {
    pUp_->moveTo(tx, ty, tz, t);
    t_cam_up_dir_ = pUp_->up_dir_;
}
void CameraWorker::slideMvUpVecTo(dir26 prm_up_dir_no, frame t) {
    t_cam_up_dir_ = prm_up_dir_no;
    pUp_->moveTo(prm_up_dir_no, t);
}
void CameraWorker::setUpVec(coord tx, coord ty, coord tz) {
    pUp_->position(tx,ty,tz);
}
void CameraWorker::stopMvCam() {
    pCam_->pAxsMver_->stopMv();
}

void CameraWorker::stopMvVp() {
    pVp_->pAxsMver_->stopMv();
}

CameraWorker::~CameraWorker() {

}
