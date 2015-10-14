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

    static volatile bool is_init = CameraWorker::initStatic(); //静的メンバ初期化
    //注意：Cameraはまだ生成されていないためここでP_CAMは使用不可
}

int CameraWorker::relation_up_vec_[3*3*3][3*3*3];
int (*CameraWorker::relation_up_by_vec_)[3*3*3];
bool CameraWorker::initStatic() {
    for (int i = 0; i < 3*3*3; i++) {
        for (int j = 0; j < 3*3*3; j++) {
            CameraWorker::relation_up_vec_[i][j] = DIR26_NULL;
        }
    }
    CameraWorker::relation_up_by_vec_ =  (int (*)[3*3*3])(&(CameraWorker::relation_up_vec_[13][13])); //13 は 3*3*3=27 の真ん中の要素、_relation_up_vec[-13～13][-13～13]でアクセスする為
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
    //現在のターゲットを再ターゲット
    slideMvCamTo(t_x_CAM_, t_y_CAM_, t_z_CAM_, 60);
    slideMvVpTo(t_x_VP_, t_y_VP_, t_z_VP_, 60);
    slideMvUpVecTo(t_cam_up_dir_, 30);
}

void CameraWorker::onSwitchCameraWork() {
    //現在のターゲットを再ターゲット
    slideMvCamTo(t_x_CAM_, t_y_CAM_, t_z_CAM_, 60);
    slideMvVpTo(t_x_VP_, t_y_VP_, t_z_VP_, 60);
    slideMvUpVecTo(t_cam_up_dir_, 30);
}

void CameraWorker::onChangedToOtherCameraWork() {
}

void CameraWorker::targetAutoCamup() {
    //UPベクトルをカメラ→視点ベクトルによって自動設定
    vcv_dir_ = pCam_->getVpDirNo();
    if (vcv_dir_ != vcv_dir_prev_) { //カメラ→視点ベクトルの面番号が変化したらUPを１回考慮
        frame up_frames = 30;
        int up_hx1, up_hy1, up_hz1;
        GgafDx26DirectionUtil::cnvDirNo2Sgn(pUp_->up_dir_, up_hx1, up_hy1, up_hz1);
        int up_dir_next = CameraWorker::relation_up_by_vec_[pUp_->up_dir_][vcv_dir_];
        if (up_dir_next == DIR26_NULL) {
            //FACE_XXXは、UPは動く必要なし
        } else {
            if (up_dir_next == DIR26( 0, 0, 0)) {
                //カメラ→視点ベクトルの面番号が、UPの面番号と同じか真裏になった。
                //その場合は、カメラ→視点ベクトルの一つ前の面番号を採用してUPの場所を求める。
                int up_dir_next_other = CameraWorker::relation_up_by_vec_[pUp_->up_dir_][vcv_dir_prev_];
                if (up_dir_next_other == DIR26_NULL) {
                    //FACE_XXXは、UPは動く必要なし
                } else {
                    if (up_dir_next_other == DIR26( 0, 0, 0)) {
                        //カメラ→視点ベクトルの面番号が真裏へ一気に動いたことになる。
                        //お手上げ。UPはどこに行けばよいか不定。したがってUPはそのまま。
                    } else {
                        slideMvUpVecTo(up_dir_next_other, up_frames);
                    }
                }
            } else {
                //カメラ→視点ベクトル面番号が、UPベクトル面番号に隣接したので、
                //その隣接面の反対側の隣接面の方角へUPベクトルを逃す。
                //或いは、カメラ→視点ベクトル面番号が、UPベクトル面番号から直角以上の角度で遠ざかるので、
                //UPベクトルを近寄らせる。
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
