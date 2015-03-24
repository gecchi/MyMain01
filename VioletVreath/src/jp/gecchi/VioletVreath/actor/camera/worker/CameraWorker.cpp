#include "CameraWorker.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"
#include "jp/ggaf/dxcore/util/GgafDxDirectionUtil.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/camera/CameraUpVector.h"
#include "jp/gecchi/VioletVreath/actor/camera/CameraViewPoint.h"

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
    pUp_ = nullptr;
    t_cam_up_face_ = GgafDxDirectionUtil::FACE_ZPZ; //TN(0,1,0)
    vcv_face_ = 0;
    vcv_face_prev_ = vcv_face_;

    static volatile bool is_init = CameraWorker::initStatic(); //静的メンバ初期化
    //注意：Cameraはまだ生成されていないためここでP_CAMは使用不可
}

int CameraWorker::relation_up_vec_[3*3*3][3*3*3];
int (*CameraWorker::relation_up_by_vec_)[3*3*3];
bool CameraWorker::initStatic() {
    for (int i = 0; i < 3*3*3; i++) {
        for (int j = 0; j < 3*3*3; j++) {
            CameraWorker::relation_up_vec_[i][j] = GgafDxDirectionUtil::FACE_XXX;
        }
    }
    CameraWorker::relation_up_by_vec_ =  (int (*)[3*3*3])(&(CameraWorker::relation_up_vec_[13][13])); //13 は 3*3*3=27 の真ん中の要素、_relation_up_vec[-13～13][-13～13]でアクセスする為
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1,-1,-1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1,-1, 0)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1,-1, 1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 0,-1)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 0, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 0, 1)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 1,-1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 1, 0)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 1, 1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1,-1,-1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1,-1, 0)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1,-1, 1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 0,-1)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 0, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 0, 1)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 1,-1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 1, 0)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 1, 1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1,-1,-1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1,-1, 0)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1,-1, 1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 0,-1)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 0, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 0, 1)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 1,-1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 1, 0)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 1, 1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1,-1,-1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1,-1, 0)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1,-1, 1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 0,-1)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 0, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 0, 1)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 1,-1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 1, 0)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 1, 1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1, 1,-1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1, 1, 0)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1, 1, 1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0, 1,-1)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0, 1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0, 1, 1)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1, 1,-1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1, 1, 0)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1, 1, 1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1,-1,-1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1,-1, 0)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1,-1, 1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0,-1,-1)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0,-1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0,-1, 1)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1,-1,-1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1,-1, 0)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1,-1, 1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1,-1,-1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1,-1, 0)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1,-1, 1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0,-1,-1)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0,-1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0,-1, 1)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1,-1,-1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1,-1, 0)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1,-1, 1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1, 1,-1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1, 1, 0)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1, 1, 1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0, 1,-1)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0, 1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0, 1, 1)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1, 1,-1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1, 1, 0)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1, 1, 1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1,-1, 1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 0, 1)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 1, 1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0,-1, 1)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 0, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 1, 1)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1,-1, 1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 0, 1)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 1, 1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1,-1,-1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 0,-1)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 1,-1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0,-1,-1)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 0,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 1,-1)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1,-1,-1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 0,-1)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 1,-1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1,-1,-1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 0,-1)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 1,-1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0,-1,-1)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 0,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 1,-1)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1,-1,-1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 0,-1)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 1,-1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1,-1, 1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 0, 1)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 1, 1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0,-1, 1)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 0, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 1, 1)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1,-1, 1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 0, 1)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 1, 1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0, 1,-1)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0, 1, 0)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0, 1, 1)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 0,-1)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 0, 0)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 0, 1)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 1,-1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 1, 1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1,-1,-1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1,-1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1,-1, 1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1, 0,-1)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1, 0, 0)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1, 0, 1)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0,-1,-1)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0,-1, 0)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0,-1, 1)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1,-1,-1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1,-1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1,-1, 1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1, 0,-1)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1, 0, 0)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1, 0, 1)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0,-1,-1)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0,-1, 0)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0,-1, 1)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0, 1,-1)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0, 1, 0)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0, 1, 1)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 0,-1)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 0, 0)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 0, 1)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 1,-1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 1, 1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0,-1, 1)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 0, 1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 1, 1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1,-1, 0)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 0, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 1, 0)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1,-1, 1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 0, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 1, 1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1,-1,-1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 0,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 1,-1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1,-1, 0)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 0, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 1, 0)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0,-1,-1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 0,-1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 1,-1)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1,-1,-1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 0,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 1,-1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1,-1, 0)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 0, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 1, 0)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0,-1,-1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 0,-1)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 1,-1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0,-1, 1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 0, 1)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 1, 1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1,-1, 0)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 0, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 1, 0)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1,-1, 1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 0, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 1, 1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 0, 1)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 0, 1)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 0, 1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 1, 0)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 1, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 1, 0)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 1, 1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 1, 1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1,-1,-1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0,-1,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1,-1,-1)] = TN( 1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1,-1, 0)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0,-1, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1,-1, 0)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 0,-1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 0,-1)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 0,-1)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1,-1,-1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0,-1,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1,-1,-1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1,-1, 0)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0,-1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1,-1, 0)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 0,-1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 0,-1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 0,-1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 0, 1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 0, 1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 0, 1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 1, 0)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 1, 0)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 1, 1)] = TN(-1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 1, 1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0, 1,-1)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0, 1, 0)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0, 1, 1)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 0,-1)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 0, 0)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 0, 1)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 1,-1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 1, 1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1,-1,-1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1,-1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1,-1, 1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1, 0,-1)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1, 0, 0)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1, 0, 1)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0,-1,-1)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0,-1, 0)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0,-1, 1)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1, 0,-1)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1, 0, 0)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1, 0, 1)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0,-1,-1)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0,-1, 0)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0,-1, 1)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1,-1,-1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1,-1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1,-1, 1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 1,-1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 1, 0)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 1, 1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0, 1,-1)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0, 1, 0)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0, 1, 1)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 0,-1)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 0, 0)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 0, 1)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0,-1, 1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 0, 1)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 1, 1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1,-1, 0)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 0, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 1, 0)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1,-1, 1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 0, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 1, 1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1,-1,-1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 0,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 1,-1)] = TN(-1, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1,-1, 0)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 0, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 1, 0)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0,-1,-1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 0,-1)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 1,-1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1,-1, 0)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 0, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 1, 0)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0,-1,-1)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 0,-1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 1,-1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1,-1,-1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 0,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 1,-1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1,-1, 1)] = TN( 1,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 0, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 1, 1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0,-1, 1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 0, 1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 1, 1)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1,-1, 0)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 0, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 1, 0)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 0, 1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 0, 1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 0, 1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1,-1, 0)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0,-1, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1,-1, 0)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1,-1, 1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0,-1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1,-1, 1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 1,-1)] = TN(-1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 1,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 1,-1)] = TN( 1,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 1, 0)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 1, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 1, 0)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 0,-1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 0,-1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 0,-1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 1, 0)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 1, 0)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 0,-1)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 0,-1)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 0,-1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 1,-1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 1,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 1,-1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1,-1, 1)] = TN(-1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0,-1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1,-1, 1)] = TN( 1, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 0, 1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 0, 1)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 0, 1)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1,-1, 0)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0,-1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1,-1, 0)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 0, 0, 1)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 0, 1, 0)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 0, 1, 1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 0, 0)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 0, 1)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 1, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 0,-1, 0)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 0,-1,-1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN(-1, 0, 0)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN(-1, 0,-1)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN(-1,-1, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN(-1,-1,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 0, 0,-1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 0,-1,-1)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN(-1, 0, 0)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN(-1, 0,-1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN(-1,-1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN(-1,-1,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 0, 0, 1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 0, 1, 0)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 0, 0)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 0, 1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 0,-1)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 1, 0)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 1,-1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 1, 0,-1)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 1, 1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 1, 1,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 0, 1)] = TN( 1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0,-1, 0)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0,-1, 1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN(-1, 0, 0)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN(-1,-1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN(-1,-1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 0, 1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0,-1, 0)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0,-1, 1)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN(-1, 0, 0)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN(-1, 0, 1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN(-1,-1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 0,-1)] = TN(-1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 1, 0)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 1,-1)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 0, 0)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 0,-1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 1, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 1,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 0, 1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0,-1, 0)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0,-1, 1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 1, 0, 0)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 1, 0, 1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 1,-1, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 1,-1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 0,-1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 1, 0)] = TN( 1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 1,-1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 0, 0)] = TN( 0,-1, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 0,-1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 1, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 1,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 0,-1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 1, 0)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 1,-1)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 0, 0)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 0,-1)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 1,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 0, 1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0,-1, 0)] = TN(-1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0,-1, 1)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 1, 0, 0)] = TN( 0, 1,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 1, 0, 1)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 1,-1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 1,-1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 0,-1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0,-1, 0)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0,-1,-1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 1, 0, 0)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 1, 0,-1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 1,-1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 1,-1,-1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 0, 1)] = TN( 1,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 1, 0)] = TN( 1, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 1, 1)] = TN( 1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 0, 0)] = TN( 0,-1,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 0, 1)] = TN( 0,-1, 0);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 1, 0)] = TN( 0, 0,-1);
    CameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 0, 1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 1, 0)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 1, 1)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 0, 0)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 0, 1)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 1, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 1, 1)] = TN( 0, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 0,-1)] = TN(-1, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0,-1, 0)] = TN(-1, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0,-1,-1)] = TN(-1, 0, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 1, 0, 0)] = TN( 0, 1, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 1, 0,-1)] = TN( 0, 1, 0);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 1,-1, 0)] = TN( 0, 0, 1);
    CameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 1,-1,-1)] = TN( 0, 0, 0);
    return true;
}

void CameraWorker::initialize() {
    pCam_ = P_GOD->getSpacetime()->getCamera();
    pVp_ = (CameraViewPoint*)(pCam_->getCameraViewPoint());
    pUp_ = (CameraUpVector*)(pCam_->getCameraUpVector());
    t_x_VP_ = pVp_->_x;
    t_y_VP_ = pVp_->_y;
    t_z_VP_ = pVp_->_z;
    t_x_CAM_ = pCam_->_x;
    t_y_CAM_ = pCam_->_y;
    t_z_CAM_ = pCam_->_z;
    t_cam_up_face_ = pUp_->up_face_;
}
void CameraWorker::onActive() {
    //現在のターゲットを再ターゲット
    slideMvCamTo(t_x_CAM_, t_y_CAM_, t_z_CAM_, 60);
    slideMvVpTo(t_x_VP_, t_y_VP_, t_z_VP_, 60);
    slideMvUpTo(t_cam_up_face_, 30);
}

void CameraWorker::onSwitchCameraWork() {
    //frame_of_behaving_since_onSwitch_ = 0; は Spacetime::switchCameraWork() が行う。
}

void CameraWorker::onUndoCameraWork() {
}

void CameraWorker::onSwitchToOtherCameraWork() {
}

void CameraWorker::onCameBackFromOtherCameraWork() {
}

void CameraWorker::processBehavior() {
    //UPベクトルをカメラ→視点ベクトルによって自動設定
    vcv_face_ = pCam_->getVpFaceNo();
    if (vcv_face_ != vcv_face_prev_) { //カメラ→視点ベクトルの面番号が変化したらUPを１回考慮
        frame up_frames = 30;
        int up_hx1, up_hy1, up_hz1;
        GgafDxDirectionUtil::cnvFaceNo2Sgn(pUp_->up_face_, up_hx1, up_hy1, up_hz1);
        int up_face_next = CameraWorker::relation_up_by_vec_[pUp_->up_face_][vcv_face_];
        if (up_face_next == GgafDxDirectionUtil::FACE_XXX) {
            //FACE_XXXは、UPは動く必要なし
        } else {
            if (up_face_next == GgafDxDirectionUtil::FACE_ZZZ) {
                //カメラ→視点ベクトルの面番号が、UPの面番号と同じか真裏になった。
                //その場合は、カメラ→視点ベクトルの一つ前の面番号を採用してUPの場所を求める。
                int up_face_next_other = CameraWorker::relation_up_by_vec_[pUp_->up_face_][vcv_face_prev_];
                if (up_face_next_other == GgafDxDirectionUtil::FACE_XXX) {
                    //FACE_XXXは、UPは動く必要なし
                } else {
                    if (up_face_next_other == GgafDxDirectionUtil::FACE_ZZZ) {
                        //カメラ→視点ベクトルの面番号が真裏へ一気に動いたことになる。
                        //お手上げ。UPはどこに行けばよいか不定。したがってUPはそのまま。
                    } else {
                        slideMvUpTo(up_face_next_other, up_frames);
                    }
                }
            } else {
                //カメラ→視点ベクトル面番号が、UPベクトル面番号に隣接したので、
                //その隣接面の反対側の隣接面の方角へUPベクトルを逃す。
                //或いは、カメラ→視点ベクトル面番号が、UPベクトル面番号から直角以上の角度で遠ざかるので、
                //UPベクトルを近寄らせる。
                slideMvUpTo(up_face_next, up_frames);
            }
        }

    }
    vcv_face_prev_ = vcv_face_;
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

void CameraWorker::slideMvUpTo(face26 prm_up_face_no, frame t) {
    t_cam_up_face_ = prm_up_face_no;
    pUp_->moveTo(prm_up_face_no, t);
}

//void CameraWorker::behaveAutoCamUp() {
//#ifdef MY_DEBUG
//    int bk_up_face_ = pCam_->up_face_;
//#endif
//    if (pCam_->vcv_face_ != pCam_->vcv_face_prev_) {
//        GgafDxAxesMoverAssistantA* asstA = pCam_->pAxsMver_->asst();
//        int fx = asstA->_smthVxMv._prm._flg ? asstA->_smthVxMv._prm._target_frames : 10;
//        int fy = asstA->_smthVyMv._prm._flg ? asstA->_smthVyMv._prm._target_frames : 10;
//        int fz = asstA->_smthVzMv._prm._flg ? asstA->_smthVzMv._prm._target_frames : 10;
//        frame up_frames = (frame)(MAX3(fx,fy,fz) / 2) ; //半分のフレーム時間でUP変更を完了させる
//        if (pCam_->vcv_face_ == pCam_->up_face_) {
//            //今のUP(up_face_)の面にカメラ→視点ベクトル(vcv_face_)が突き刺さる場合
//            //以前のカメラ→視点(vcv_face_prev_) の真裏の面にUPが移動
//            pCam_->slideUpCamTo(7 - pCam_->vcv_face_prev_, up_frames);
//        } else if (pCam_->vcv_face_ == 7 - pCam_->up_face_) {  //up_face_の裏面
//             //今のUP(up_face_)の面の真裏にカメラ→視点ベクトル(vcv_face_)が突き刺さる場合
//             //以前のカメラ→視点(vcv_face_prev_) の面がUPに変更
//            pCam_->slideUpCamTo(pCam_->vcv_face_prev_, up_frames);
//        } else {
//            //変化しない
//            pCam_->slideUpCamTo(pCam_->up_face_, up_frames);
//        }
//        _TRACE_("CameraWorker::behaveAutoCamUp() up_frames="<<up_frames<<" vcv="<<pCam_->vcv_face_prev_<<"→"<<pCam_->vcv_face_<<" up_face_="<<bk_up_face_<<"→"<<pCam_->up_face_<<"");
//    }
////    _TRACE_("cam=("<<_x<<","<<_y<<","<<_z<<") vp=("<< pVP->_x <<","<< pVP->_y <<","<< pVP->_z <<")  UP=("<< pUp_->_x <<","<< pUp_->_y <<","<< pUp_->_z <<") CAM_UP=("<< _pVecCamUp->x <<","<< _pVecCamUp->y <<","<< _pVecCamUp->z <<")");
////    _TRACE_("vcv="<<vcv_face_prev_<<"→"<<vcv_face_<<" up_face_="<<bk_up_face_<<"→"<<up_face_<<"");
//}
////void CameraWorker::stopNaturallyCam(coord distance, frame t) {
////    float vx,vy,vz;
////    GgafDxAxesMover* pAxMvr = pCam_->pAxsMver_;
////    UTIL::getNormalizeVector(
////            pAxMvr->_velo_vx_mv,
////            pAxMvr->_velo_vy_mv,
////            pAxMvr->_velo_vz_mv,
////            vx,vy,vz);
////    pAxMvr->asstA()->slideVxyzMvByDt(distance*vx, distance*vy, distance*vz,
////                                     t,
////                                     0.0, 0.0, 0, true);
////}
////void CameraWorker::stopNaturallyVp(coord distance, frame t) {
////    float vx,vy,vz;
////    GgafDxAxesMover* pAxMvr = pVp_->pAxsMver_;
////    UTIL::getNormalizeVector(
////            pAxMvr->_velo_vx_mv,
////            pAxMvr->_velo_vy_mv,
////            pAxMvr->_velo_vz_mv,
////            vx,vy,vz);
////    pAxMvr->asstA()->slideVxyzMvByDt(distance*vx, distance*vy, distance*vz,
////                                     t,
////                                     0.0, 0.0, 0, true);
////}
void CameraWorker::stopMvCam() {
    pCam_->pAxsMver_->stopMv();
}
void CameraWorker::stopMvVp() {
    pVp_->pAxsMver_->stopMv();
}
CameraWorker::~CameraWorker() {

}
