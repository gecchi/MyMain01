#include "VamSysCamWorker.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/AxisVehicle.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/camera/Camera.h"
#include "jp/gecchi/VioletVreath/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/dx/actor/supporter/AxisVehicleAssistantA.h"
#include "jp/ggaf/lib/util/Direction26Util.h"
#include "jp/ggaf/lib/util/Direction8Util.h"
#include "jp/ggaf/lib/util/Quaternion.hpp"
#include "jp/ggaf/dx/actor/GeometricActor.h"

#include "jp/gecchi/VioletVreath/actor/camera/CameraUpVector.h"
#include "jp/ggaf/dx/sound/SeTransmitter.h"
#include <math.h>



using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_RETURNNING_CAM_POS     ,
};

dir26 VamSysCamWorker::nbhd_dir_entity_[3*3*3][6];
dir26 (*VamSysCamWorker::nbhd_dir_)[6];
dir26 VamSysCamWorker::cam_to_8dir_entity_[3*3*3][8];
dir26 (*VamSysCamWorker::cam_to_8dir_)[8];


VamSysCamWorker::FovInfo VamSysCamWorker::cam_hosei_fov_entity_[3*3*3][3*3*3];
VamSysCamWorker::FovInfo (*VamSysCamWorker::cam_hosei_fov_)[3*3*3];
VamSysCamWorker::FovInfo VamSysCamWorker::vp_hosei_fov_entity_[3*3*3][3*3*3];
VamSysCamWorker::FovInfo (*VamSysCamWorker::vp_hosei_fov_)[3*3*3];
coord VamSysCamWorker::cam_radius_;

double VamSysCamWorker::mv_ang_;
double VamSysCamWorker::mv_ang_sinHalf_;
double VamSysCamWorker::mv_ang_cosHalf_;

bool VamSysCamWorker::initStatic(Camera* prm_pCamera) {
    for (int i = 0; i < 3*3*3; i++) {
        for (int j = 0; j < 6; j++) {
            VamSysCamWorker::nbhd_dir_entity_[i][j] = DIR26_NULL;
        }
    }
    //第１要素を -13 ～ 0 ～ 13 （ DIR26(-1,-1,-1) ～ DIR26(0,0,0) ～ DIR26(1,1,1) ）でアクセスす為に
    //真ん中要素のポインタを nbhd_dir_[0] に登録
    VamSysCamWorker::nbhd_dir_ = (int (*)[6])(&(VamSysCamWorker::nbhd_dir_entity_[13][0])); //13 は DIR26 の真ん中の要素

    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1, 1)][0] = DIR26( 1, 1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1, 1)][1] = DIR26( 1, 0, 1);
    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1, 1)][2] = DIR26( 1, 0, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1, 1)][3] = DIR26( 0, 1, 1);
    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1, 1)][4] = DIR26( 0, 1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1, 1)][5] = DIR26( 0, 0, 1);

    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1,-1)][0] = DIR26( 1, 1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1,-1)][1] = DIR26( 1, 0,-1);
    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1,-1)][2] = DIR26( 1, 0, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1,-1)][3] = DIR26( 0, 1,-1);
    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1,-1)][4] = DIR26( 0, 1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1, 1,-1)][5] = DIR26( 0, 0,-1);

    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1, 1)][0] = DIR26( 1,-1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1, 1)][1] = DIR26( 1, 0, 1);
    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1, 1)][2] = DIR26( 1, 0, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1, 1)][3] = DIR26( 0,-1, 1);
    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1, 1)][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1, 1)][5] = DIR26( 0, 0, 1);

    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1,-1)][0] = DIR26( 1,-1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1,-1)][1] = DIR26( 1, 0,-1);
    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1,-1)][2] = DIR26( 1, 0, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1,-1)][3] = DIR26( 0,-1,-1);
    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1,-1)][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26( 1,-1,-1)][5] = DIR26( 0, 0,-1);

    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1, 1)][0] = DIR26(-1, 1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1, 1)][1] = DIR26(-1, 0, 1);
    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1, 1)][2] = DIR26(-1, 0, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1, 1)][3] = DIR26( 0, 1, 1);
    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1, 1)][4] = DIR26( 0, 1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1, 1)][5] = DIR26( 0, 0, 1);

    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1,-1)][0] = DIR26(-1, 1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1,-1)][1] = DIR26(-1, 0,-1);
    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1,-1)][2] = DIR26(-1, 0, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1,-1)][3] = DIR26( 0, 1,-1);
    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1,-1)][4] = DIR26( 0, 1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1, 1,-1)][5] = DIR26( 0, 0,-1);

    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1, 1)][0] = DIR26(-1,-1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1, 1)][1] = DIR26(-1, 0, 1);
    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1, 1)][2] = DIR26(-1, 0, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1, 1)][3] = DIR26( 0,-1, 1);
    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1, 1)][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1, 1)][5] = DIR26( 0, 0, 1);

    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1,-1)][0] = DIR26(-1,-1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1,-1)][1] = DIR26(-1, 0,-1);
    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1,-1)][2] = DIR26(-1, 0, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1,-1)][3] = DIR26( 0,-1,-1);
    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1,-1)][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::nbhd_dir_[DIR26(-1,-1,-1)][5] = DIR26( 0, 0,-1);

//////////////////////
    for (int i = 0; i < 3*3*3; i++) {
        for (int j = 0; j < 8; j++) {
            VamSysCamWorker::cam_to_8dir_entity_[i][j] = DIR26_NULL;
        }
    }
    //第１要素を -13 ～ 0 ～ 13 （ DIR26(-1,-1,-1) ～ DIR26(0,0,0) ～ DIR26(1,1,1) ）でアクセスす為に
    //真ん中要素のポインタを cam_to_8dir_[0] に登録
    VamSysCamWorker::cam_to_8dir_ = (int (*)[8])(&(VamSysCamWorker::cam_to_8dir_entity_[13][0])); //13 は DIR26 の真ん中の要素

    //全て右回りに順に設定すること
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT][1] = DIR26(+1,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT][2] = DIR26(+1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT][3] = DIR26(+1,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT][5] = DIR26(-1,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT][6] = DIR26(-1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT][7] = DIR26(-1,+1, 0);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT][1] = DIR26(-1,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT][2] = DIR26(-1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT][3] = DIR26(-1,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT][5] = DIR26(+1,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT][6] = DIR26(+1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT][7] = DIR26(+1,+1, 0);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT][1] = DIR26( 0,+1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT][2] = DIR26( 0, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT][3] = DIR26( 0,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT][5] = DIR26( 0,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT][6] = DIR26( 0, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT][7] = DIR26( 0,+1,-1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND][0] = DIR26( 0,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND][1] = DIR26( 0,+1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND][2] = DIR26( 0, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND][3] = DIR26( 0,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND][5] = DIR26( 0,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND][6] = DIR26( 0, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND][7] = DIR26( 0,+1,+1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_UP][0] = DIR26( 0, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_UP][1] = DIR26(+1, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_UP][2] = DIR26(+1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_UP][3] = DIR26(+1, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_UP][4] = DIR26( 0, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_UP][5] = DIR26(-1, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_UP][6] = DIR26(-1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_UP][7] = DIR26(-1, 0,+1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_DOWN][0] = DIR26( 0, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_DOWN][1] = DIR26(-1, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_DOWN][2] = DIR26(-1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_DOWN][3] = DIR26(-1, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_DOWN][4] = DIR26( 0, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_DOWN][5] = DIR26(+1, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_DOWN][6] = DIR26(+1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_DOWN][7] = DIR26(+1, 0,+1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_UP][0] = DIR26( 0,+1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_UP][1] = DIR26(+1,+1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_UP][2] = DIR26(+1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_UP][3] = DIR26(+1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_UP][4] = DIR26( 0,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_UP][5] = DIR26(-1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_UP][6] = DIR26(-1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_UP][7] = DIR26(-1,+1,+1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][0] = DIR26( 0,+1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][1] = DIR26(-1,+1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][2] = DIR26(-1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][3] = DIR26(-1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][4] = DIR26( 0,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][5] = DIR26(+1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][6] = DIR26(+1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][7] = DIR26(+1,+1,+1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][0] = DIR26( 0,+1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][1] = DIR26(+1,+1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][2] = DIR26(+1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][3] = DIR26(+1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][4] = DIR26( 0,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][5] = DIR26(-1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][6] = DIR26(-1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][7] = DIR26(-1,+1,-1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_UP][0] = DIR26( 0,+1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_UP][1] = DIR26(-1,+1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_UP][2] = DIR26(-1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_UP][3] = DIR26(-1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_UP][4] = DIR26( 0,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_UP][5] = DIR26(+1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_UP][6] = DIR26(+1, 0, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_ZLEFT_UP][7] = DIR26(+1,+1,-1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][1] = DIR26(+1,+1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][2] = DIR26(+1, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][3] = DIR26(+1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][5] = DIR26(-1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][6] = DIR26(-1, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][7] = DIR26(-1,+1,-1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][1] = DIR26(-1,+1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][2] = DIR26(-1, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][3] = DIR26(-1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][5] = DIR26(+1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][6] = DIR26(+1, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][7] = DIR26(+1,+1,+1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][1] = DIR26(+1,+1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][2] = DIR26(+1, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][3] = DIR26(+1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][5] = DIR26(-1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][6] = DIR26(-1, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][7] = DIR26(-1,+1,+1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][1] = DIR26(-1,+1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][2] = DIR26(-1, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][3] = DIR26(-1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][5] = DIR26(+1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][6] = DIR26(+1, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][7] = DIR26(+1,+1,-1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_UP][0] = DIR26(-1,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_UP][1] = DIR26(-1,+1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_UP][2] = DIR26( 0, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_UP][3] = DIR26(+1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_UP][4] = DIR26(+1,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_UP][5] = DIR26(+1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_UP][6] = DIR26( 0, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_UP][7] = DIR26(-1,+1,-1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_DOWN][0] = DIR26(-1,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_DOWN][1] = DIR26(-1,+1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_DOWN][2] = DIR26( 0, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_DOWN][3] = DIR26(+1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_DOWN][4] = DIR26(+1,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_DOWN][5] = DIR26(+1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_DOWN][6] = DIR26( 0, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_DOWN][7] = DIR26(-1,+1,+1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_DOWN][0] = DIR26(+1,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_DOWN][1] = DIR26(+1,+1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_DOWN][2] = DIR26( 0, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_DOWN][3] = DIR26(-1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_DOWN][4] = DIR26(-1,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_DOWN][5] = DIR26(-1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_DOWN][6] = DIR26( 0, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_FRONT_DOWN][7] = DIR26(+1,+1,-1);

    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_UP][0] = DIR26(+1,+1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_UP][1] = DIR26(+1,+1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_UP][2] = DIR26( 0, 0,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_UP][3] = DIR26(-1,-1,-1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_UP][4] = DIR26(-1,-1, 0);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_UP][5] = DIR26(-1,-1,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_UP][6] = DIR26( 0, 0,+1);
    VamSysCamWorker::cam_to_8dir_[VAM_POS_BEHIND_UP][7] = DIR26(+1,+1,+1);

    dxcoord cam_dz_org = ABS(prm_pCamera->_cameraZ_org); //DZ
    VamSysCamWorker::cam_radius_ = DX_C(cam_dz_org);
    //     z+
    //    ^
    //    |
    //    |                      /        ┐ 視線ベクトル
    //    |                     /       ／
    //    |                    /      ／               →
    //    |          cam_x    /     ／          ＿─   Ａ = カメラの表示の右の境界線ベクトル
    // ---+-------------+----/----／------自＿─---------
    //    |         ^   :   /   ／ vp   ＿─    ↑
    //    |         |   :  /  ／    ＿─   :     a  画面の端っことX軸の交点
    //    |      DZ |   : / ／  ＿─       :
    //    |         v   :/／＿─  b        :
    //    |            ∀------------------:
    //    |           cam
    //    |                        <-------->
    //    |                          vp_DX
    //    |
    //    |            <-------------------->
    //    |                   cam_DX
    //    |
    //    |<-------------------------------->
    //               MyShip::lim_x_infront_ = l
    //
    //∠vp(大きいほう)  = θ とすると
    //∠a = 2π - H_FOVX - θ
    //        coord DZ  = cam_radius_;
    //        double vp_th = (PI/2); //ここを調整する！
    //        double H_FOVX = prm_pCamera->_rad_half_fovX;
    //        double a = PI - H_FOVX - vp_th;
    //        //camからX軸に平行線と→Ａ(カメラの表示の右の境界線ベクトル)のなす角(b)は、錯角で角 aと等しい
    //        //∠b = a = PI - H_FOVX - vp_th;
    //        double b = PI - H_FOVX - vp_th;;
    //        //cam_x ～ a の長さをDX
    //        //tan(b) = DZ/cam_DX より、cam_DX = DZ / tan(b)
    //        double cam_DX = DZ / tan(b);
    //        CAM_HOSEI_FOV_X_DX_ = DX_C(cam_DX);
    //        //直角三角形 cam, vp, cam_x を考える
    //        //∠vp(小さいほう)  = π-θ
    //        double vp_th2 = 2*PI - vp_th;
    //        //tan(∠vp(小さいほう)) =  DZ / (cam_x ～ vp_xの長さ)
    //        //cam_x ～ vp_xの長さ = DZ / tan(∠vp(小さいほう))
    //        // vp_DX = cam_DX - (cam_x ～ vp_xの長さ)
    //        double vp_DX = cam_DX - (DZ / tan(vp_th2));
    //        VP_HOSEI_FOV_X_DX_ = DX_C(vp_DX);

    double rad_half_fovX = prm_pCamera->_rad_half_fovX * 0.8; //0.8は調整、1.0で左右端まで行く
    double vpx_th = 2*PI * 120.0 / 360.0; //ここを調整する！
    double cam_DX = cam_dz_org / tan(PI-vpx_th-rad_half_fovX);
    coord CAM_HOSEI_FOV_X = DX_C(cam_DX);
    double vp_DX = cam_DX - (cam_dz_org / tan(PI - vpx_th));
    coord VP_HOSEI_FOV_X = DX_C(vp_DX);

    double rad_half_fovY = prm_pCamera->_rad_half_fovY * 0.9; //0.9は調整、1.0で上下端まで行く
    double vpy_th = 2*PI * 100.0 / 360.0; //ここを調整する！
    double cam_DY = cam_dz_org / tan(PI-vpy_th-rad_half_fovY);
    coord CAM_HOSEI_FOV_Y = DX_C(cam_DY);
    double vp_DY = cam_DY - (cam_dz_org / tan(PI - vpy_th));
    coord VP_HOSEI_FOV_Y = DX_C(vp_DY);
    //奥行き補正は適当
    coord CAM_HOSEI_FOV_Z = CAM_HOSEI_FOV_Y/4;
    coord VP_HOSEI_FOV_Z = VP_HOSEI_FOV_Y/4;

    //斜めったときの補正
//    int CAM_HOSEI_FOV_XY = CAM_HOSEI_FOV_Y * 0.7071067811865475; //1/√2
//    int VP_HOSEI_FOV_XY = VP_HOSEI_FOV_Y * 0.7071067811865475;  //1/√2
//    int CAM_HOSEI_FOV_YZ = CAM_HOSEI_FOV_Z * 0.7071067811865475; //1/√2
//    int VP_HOSEI_FOV_YZ = VP_HOSEI_FOV_Z * 0.7071067811865475;  //1/√2
//    int CAM_HOSEI_FOV_ZX = CAM_HOSEI_FOV_X * 0.7071067811865475; //1/√2
//    int VP_HOSEI_FOV_ZX = VP_HOSEI_FOV_X * 0.7071067811865475;  //1/√2

//    int CAM_HOSEI_FOV_XYZ = CAM_HOSEI_FOV_Z * 0.5773502691896258; //1/√3
//    int VP_HOSEI_FOV_XYZ = VP_HOSEI_FOV_Z * 0.5773502691896258;   //1/√3

    int CAM_HOSEI_FOV_XY = CAM_HOSEI_FOV_Y / 2;
    int VP_HOSEI_FOV_XY = VP_HOSEI_FOV_Y / 2;
    int CAM_HOSEI_FOV_YZ = CAM_HOSEI_FOV_Z;
    int VP_HOSEI_FOV_YZ = VP_HOSEI_FOV_Z;
    int CAM_HOSEI_FOV_ZX = CAM_HOSEI_FOV_X / 2;
    int VP_HOSEI_FOV_ZX = VP_HOSEI_FOV_X / 2;

    int CAM_HOSEI_FOV_XYZ = CAM_HOSEI_FOV_Z;
    int VP_HOSEI_FOV_XYZ = CAM_HOSEI_FOV_Z;


    VamSysCamWorker::cam_hosei_fov_ =  (FovInfo (*)[3*3*3])(&(VamSysCamWorker::cam_hosei_fov_entity_[13][13])); //13 は 3*3*3=27 の真ん中の要素、_relation_up_vec[-13～13][-13～13]でアクセスする為
    //                                 CAM             UP                   x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26( 0,+1, 0)].set(CAM_HOSEI_FOV_X , CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1,+1, 0)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1, 0, 0)].set(CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_X , CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1,-1, 0)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26( 0,-1, 0)].set(CAM_HOSEI_FOV_X , CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1,-1, 0)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1, 0, 0)].set(CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_X , CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1,+1, 0)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z);
    // 真裏は同じなので、VAM_POS_ZRIGHT の定義を VAM_POS_ZLEFT にコピー
    memcpy(&VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZLEFT][DIR26(-1,-1,-1)],
           &VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM             UP                   x_axis_fov       y_axis_fov      z_axis_fov
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT][DIR26( 0,+1, 0)].set(CAM_HOSEI_FOV_Z, CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_X );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT][DIR26( 0,+1,+1)].set(CAM_HOSEI_FOV_Z, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT][DIR26( 0, 0,+1)].set(CAM_HOSEI_FOV_Z, CAM_HOSEI_FOV_X , CAM_HOSEI_FOV_Y );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT][DIR26( 0,-1,+1)].set(CAM_HOSEI_FOV_Z, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT][DIR26( 0,-1, 0)].set(CAM_HOSEI_FOV_Z, CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_X );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT][DIR26( 0,-1,-1)].set(CAM_HOSEI_FOV_Z, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT][DIR26( 0, 0,-1)].set(CAM_HOSEI_FOV_Z, CAM_HOSEI_FOV_X , CAM_HOSEI_FOV_Y );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT][DIR26( 0,+1,-1)].set(CAM_HOSEI_FOV_Z, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY);
    // 真裏は同じなので、VAM_POS_FRONT の定義を VAM_POS_BEHIND にコピー
    memcpy(&VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND][DIR26(-1,-1,-1)],
           &VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM             UP               x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_UP][DIR26( 0, 0,+1)].set(CAM_HOSEI_FOV_X,  CAM_HOSEI_FOV_Z , CAM_HOSEI_FOV_Y );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_UP][DIR26(+1, 0,+1)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z , CAM_HOSEI_FOV_XY);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_UP][DIR26(+1, 0, 0)].set(CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_Z , CAM_HOSEI_FOV_X );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_UP][DIR26(+1, 0,-1)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z , CAM_HOSEI_FOV_XY);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_UP][DIR26( 0, 0,-1)].set(CAM_HOSEI_FOV_X,  CAM_HOSEI_FOV_Z , CAM_HOSEI_FOV_Y );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_UP][DIR26(-1, 0,-1)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z , CAM_HOSEI_FOV_XY);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_UP][DIR26(-1, 0, 0)].set(CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_Z , CAM_HOSEI_FOV_X );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_UP][DIR26(-1, 0,+1)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z , CAM_HOSEI_FOV_XY);
    // 真裏は同じなので、VAM_POS_UP の定義を VAM_POS_DOWN にコピー
    memcpy(&VamSysCamWorker::cam_hosei_fov_[VAM_POS_DOWN][DIR26(-1,-1,-1)],
           &VamSysCamWorker::cam_hosei_fov_[VAM_POS_UP][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                UP                   x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26( 0,+1,+1)].set(CAM_HOSEI_FOV_X  , CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_YZ );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(+1,+1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(+1, 0, 0)].set(CAM_HOSEI_FOV_Y  , CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_ZX );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(+1,-1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26( 0,-1,-1)].set(CAM_HOSEI_FOV_X  , CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_YZ );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(-1,-1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(-1, 0, 0)].set(CAM_HOSEI_FOV_Y  , CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_ZX );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(-1,+1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_ZRIGHT_UP の定義を VAM_POS_ZLEFT_DOWN にコピー
    memcpy(&VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZLEFT_DOWN][DIR26(-1,-1,-1)],
           &VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                  UP                   x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26( 0,+1,-1)].set(CAM_HOSEI_FOV_X  , CAM_HOSEI_FOV_YZ,  CAM_HOSEI_FOV_YZ );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(+1,+1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(+1, 0, 0)].set(CAM_HOSEI_FOV_Y  , CAM_HOSEI_FOV_ZX,  CAM_HOSEI_FOV_ZX );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(+1,-1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26( 0,-1,+1)].set(CAM_HOSEI_FOV_X  , CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_YZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(-1,-1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(-1, 0, 0)].set(CAM_HOSEI_FOV_Y  , CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_ZX );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(-1,+1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_ZRIGHT_DOWN の定義を VAM_POS_ZLEFT_UP にコピー
    memcpy(&VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZLEFT_UP][DIR26(-1,-1,-1)],
           &VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                  UP                    x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26( 0,+1, 0)].set(CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_Y  , CAM_HOSEI_FOV_ZX );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(+1,+1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(+1, 0,+1)].set(CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_X  , CAM_HOSEI_FOV_YZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(+1,-1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26( 0,-1, 0)].set(CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_Y  , CAM_HOSEI_FOV_ZX );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(-1,-1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(-1, 0,-1)].set(CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_X  , CAM_HOSEI_FOV_YZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(-1,+1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_FRONT_ZRIGHT の定義を VAM_POS_BEHIND_ZLEFT にコピー
    memcpy(&VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_ZLEFT][DIR26(-1,-1,-1)],
           &VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                  UP                    x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26( 0,+1, 0)].set(CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_Y  , CAM_HOSEI_FOV_ZX );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(+1,+1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(+1, 0,-1)].set(CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_X  , CAM_HOSEI_FOV_YZ );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(+1,-1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26( 0,-1, 0)].set(CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_Y  , CAM_HOSEI_FOV_ZX );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(-1,-1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(-1, 0,+1)].set(CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_X  , CAM_HOSEI_FOV_YZ );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(-1,+1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_BEHIND_ZRIGHT の定義を VAM_POS_FRONT_ZLEFT にコピー
    memcpy(&VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_ZLEFT][DIR26(-1,-1,-1)],
           &VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                  UP                x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_UP][DIR26(-1,+1, 0)].set(CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_X  );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_UP][DIR26(-1,+1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_UP][DIR26( 0, 0,+1)].set(CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_Y  );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_UP][DIR26(+1,-1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_UP][DIR26(+1,-1, 0)].set(CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_X  );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_UP][DIR26(+1,-1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_UP][DIR26( 0, 0,-1)].set(CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_Y  );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_UP][DIR26(-1,+1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_FRONT_UP の定義を VAM_POS_BEHIND_DOWN にコピー
    memcpy(&VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_DOWN][DIR26(-1,-1,-1)],
           &VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_UP][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                  UP                 x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(+1,+1, 0)].set(CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_X  );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(+1,+1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26( 0, 0,+1)].set(CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_Y  );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(-1,-1,+1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(-1,-1, 0)].set(CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_YZ , CAM_HOSEI_FOV_X  );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(-1,-1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26( 0, 0,-1)].set(CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_ZX , CAM_HOSEI_FOV_Y  );
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(+1,+1,-1)].set(CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ, CAM_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_FRONT_DOWN の定義を VAM_POS_BEHIND_UP にコピー
    memcpy(&VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_UP][DIR26(-1,-1,-1)],
           &VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);


    //VPも同様に
    VamSysCamWorker::vp_hosei_fov_ =  (FovInfo (*)[3*3*3])(&(VamSysCamWorker::vp_hosei_fov_entity_[13][13])); //13 は 3*3*3=27 の真ん中の要素、_relation_up_vec[-13～13][-13～13]でアクセスする為
    //                                 CAM             UP                   x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26( 0,+1, 0)].set(VP_HOSEI_FOV_X , VP_HOSEI_FOV_Y , VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1,+1, 0)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1, 0, 0)].set(VP_HOSEI_FOV_Y , VP_HOSEI_FOV_X , VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1,-1, 0)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26( 0,-1, 0)].set(VP_HOSEI_FOV_X , VP_HOSEI_FOV_Y , VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1,-1, 0)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1, 0, 0)].set(VP_HOSEI_FOV_Y , VP_HOSEI_FOV_X , VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1,+1, 0)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z);
    // 真裏は同じなので、VAM_POS_ZRIGHT の定義を VAM_POS_ZLEFT にコピー
    memcpy(&VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZLEFT][DIR26(-1,-1,-1)],
           &VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM             UP                   x_axis_fov       y_axis_fov      z_axis_fov
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT][DIR26( 0,+1, 0)].set(VP_HOSEI_FOV_Z, VP_HOSEI_FOV_Y , VP_HOSEI_FOV_X );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT][DIR26( 0,+1,+1)].set(VP_HOSEI_FOV_Z, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT][DIR26( 0, 0,+1)].set(VP_HOSEI_FOV_Z, VP_HOSEI_FOV_X , VP_HOSEI_FOV_Y );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT][DIR26( 0,-1,+1)].set(VP_HOSEI_FOV_Z, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT][DIR26( 0,-1, 0)].set(VP_HOSEI_FOV_Z, VP_HOSEI_FOV_Y , VP_HOSEI_FOV_X );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT][DIR26( 0,-1,-1)].set(VP_HOSEI_FOV_Z, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT][DIR26( 0, 0,-1)].set(VP_HOSEI_FOV_Z, VP_HOSEI_FOV_X , VP_HOSEI_FOV_Y );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT][DIR26( 0,+1,-1)].set(VP_HOSEI_FOV_Z, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY);
    // 真裏は同じなので、VAM_POS_FRONT の定義を VAM_POS_BEHIND にコピー
    memcpy(&VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND][DIR26(-1,-1,-1)],
           &VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM             UP               x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_UP][DIR26( 0, 0,+1)].set(VP_HOSEI_FOV_X,  VP_HOSEI_FOV_Z , VP_HOSEI_FOV_Y );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_UP][DIR26(+1, 0,+1)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z , VP_HOSEI_FOV_XY);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_UP][DIR26(+1, 0, 0)].set(VP_HOSEI_FOV_Y , VP_HOSEI_FOV_Z , VP_HOSEI_FOV_X );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_UP][DIR26(+1, 0,-1)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z , VP_HOSEI_FOV_XY);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_UP][DIR26( 0, 0,-1)].set(VP_HOSEI_FOV_X,  VP_HOSEI_FOV_Z , VP_HOSEI_FOV_Y );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_UP][DIR26(-1, 0,-1)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z , VP_HOSEI_FOV_XY);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_UP][DIR26(-1, 0, 0)].set(VP_HOSEI_FOV_Y , VP_HOSEI_FOV_Z , VP_HOSEI_FOV_X );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_UP][DIR26(-1, 0,+1)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z , VP_HOSEI_FOV_XY);
    // 真裏は同じなので、VAM_POS_UP の定義を VAM_POS_DOWN にコピー
    memcpy(&VamSysCamWorker::vp_hosei_fov_[VAM_POS_DOWN][DIR26(-1,-1,-1)],
           &VamSysCamWorker::vp_hosei_fov_[VAM_POS_UP][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                UP                   x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26( 0,+1,+1)].set(VP_HOSEI_FOV_X  , VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_YZ );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(+1,+1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(+1, 0, 0)].set(VP_HOSEI_FOV_Y  , VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_ZX );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(+1,-1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26( 0,-1,-1)].set(VP_HOSEI_FOV_X  , VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_YZ );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(-1,-1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(-1, 0, 0)].set(VP_HOSEI_FOV_Y  , VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_ZX );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(-1,+1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_ZRIGHT_UP の定義を VAM_POS_ZLEFT_DOWN にコピー
    memcpy(&VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZLEFT_DOWN][DIR26(-1,-1,-1)],
           &VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_UP][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                  UP                   x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26( 0,+1,-1)].set(VP_HOSEI_FOV_X  , VP_HOSEI_FOV_YZ,  VP_HOSEI_FOV_YZ );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(+1,+1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(+1, 0, 0)].set(VP_HOSEI_FOV_Y  , VP_HOSEI_FOV_ZX,  VP_HOSEI_FOV_ZX );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(+1,-1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26( 0,-1,+1)].set(VP_HOSEI_FOV_X  , VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_YZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(-1,-1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(-1, 0, 0)].set(VP_HOSEI_FOV_Y  , VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_ZX );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(-1,+1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_ZRIGHT_DOWN の定義を VAM_POS_ZLEFT_UP にコピー
    memcpy(&VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZLEFT_UP][DIR26(-1,-1,-1)],
           &VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT_DOWN][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                  UP                    x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26( 0,+1, 0)].set(VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_Y  , VP_HOSEI_FOV_ZX );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(+1,+1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(+1, 0,+1)].set(VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_X  , VP_HOSEI_FOV_YZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(+1,-1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26( 0,-1, 0)].set(VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_Y  , VP_HOSEI_FOV_ZX );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(-1,-1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(-1, 0,-1)].set(VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_X  , VP_HOSEI_FOV_YZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(-1,+1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_FRONT_ZRIGHT の定義を VAM_POS_BEHIND_ZLEFT にコピー
    memcpy(&VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_ZLEFT][DIR26(-1,-1,-1)],
           &VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_ZRIGHT][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                  UP                    x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26( 0,+1, 0)].set(VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_Y  , VP_HOSEI_FOV_ZX );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(+1,+1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(+1, 0,-1)].set(VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_X  , VP_HOSEI_FOV_YZ );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(+1,-1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26( 0,-1, 0)].set(VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_Y  , VP_HOSEI_FOV_ZX );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(-1,-1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(-1, 0,+1)].set(VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_X  , VP_HOSEI_FOV_YZ );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(-1,+1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_BEHIND_ZRIGHT の定義を VAM_POS_FRONT_ZLEFT にコピー
    memcpy(&VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_ZLEFT][DIR26(-1,-1,-1)],
           &VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_ZRIGHT][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                  UP                x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_UP][DIR26(-1,+1, 0)].set(VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_X  );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_UP][DIR26(-1,+1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_UP][DIR26( 0, 0,+1)].set(VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_Y  );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_UP][DIR26(+1,-1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_UP][DIR26(+1,-1, 0)].set(VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_X  );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_UP][DIR26(+1,-1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_UP][DIR26( 0, 0,-1)].set(VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_Y  );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_UP][DIR26(-1,+1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_FRONT_UP の定義を VAM_POS_BEHIND_DOWN にコピー
    memcpy(&VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_DOWN][DIR26(-1,-1,-1)],
           &VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_UP][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);
    //                                 CAM                  UP                 x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(+1,+1, 0)].set(VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_X  );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(+1,+1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26( 0, 0,+1)].set(VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_Y  );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(-1,-1,+1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(-1,-1, 0)].set(VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_YZ , VP_HOSEI_FOV_X  );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(-1,-1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26( 0, 0,-1)].set(VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_ZX , VP_HOSEI_FOV_Y  );
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(+1,+1,-1)].set(VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ, VP_HOSEI_FOV_XYZ);
    //真裏は同じなので、 VAM_POS_FRONT_DOWN の定義を VAM_POS_BEHIND_UP にコピー
    memcpy(&VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_UP][DIR26(-1,-1,-1)],
           &VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);


    VamSysCamWorker::mv_ang_ = (2*PI) * (2.0/360.0); //2度
    VamSysCamWorker::mv_ang_sinHalf_ = sin(VamSysCamWorker::mv_ang_/2);
    VamSysCamWorker::mv_ang_cosHalf_ = cos(VamSysCamWorker::mv_ang_/2);

    _TRACE_("VamSysCamWorker::initStatic() 初期化OK");
    return true;
}

VamSysCamWorker::VamSysCamWorker(const char* prm_name, Camera* prm_pCamera) : CameraWorker(prm_name, (DefaultCamera*)prm_pCamera) {
    _class_name = "VamSysCamWorker";

    static volatile bool is_init = VamSysCamWorker::initStatic(prm_pCamera); //静的メンバ初期化

    pMyShip_ = nullptr; //MyShipSceneに設定してもらう

    pos_vam_camera_ = VAM_POS_ZRIGHT;
    pos_vam_camera_prev_ = VAM_POS_NON;
    is_just_changed_pos_vam_cam_ = false;

    returning_cam_pos_ = false;
    returning_cam_pos_frames_ = 0;

    pos_vam_up_ = VAM_POS_UP;
    pos_vam_up_prev_ = VAM_POS_NON;
    pSe_ = NEW GgafDx::SeTransmitter();
    pSe_->set(SE_RETURNNING_CAM_POS, "SE_MY_RETURNNING_CAM_POS" ,0);

    mv_t_x_vUP_  = 0;
    mv_t_y_vUP_  = DX_C(1);
    mv_t_z_vUP_  = 0;

    mv_t_x_vCAM_ = 0;
    mv_t_y_vCAM_ = 0;
    mv_t_z_vCAM_ = -cam_radius_;

    cam_sgn_x_ = 0;
    cam_sgn_y_ = 0;
    cam_sgn_z_ = -1;

    cam_sgn_x_ = 0;
    cam_sgn_y_ = 1;
    cam_sgn_z_ = 0;
}


void VamSysCamWorker::initialize() {
    CameraWorker::initialize();
    _TRACE_(FUNC_NAME<<" this="<<NODE_INFO);
}
void VamSysCamWorker::onActive() {
    CameraWorker::onActive();
}

void VamSysCamWorker::processBehavior() {
    if (pMyShip_ == nullptr) {
        return; //MyShipSceneシーンが未だならカメラワーク禁止
    }
    VirtualButton* pVbPlay = VB_PLAY;
    coord pMyShip_x = pMyShip_->_x;
    coord pMyShip_y = pMyShip_->_y;
    coord pMyShip_z = pMyShip_->_z;

    const bool isPressed_VB_UP    = pVbPlay->isPressed(0, VB_UP);
    const bool isPressed_VB_DOWN  = pVbPlay->isPressed(0, VB_DOWN);
    const bool isPressed_VB_LEFT  = pVbPlay->isPressed(0, VB_LEFT);
    const bool isPressed_VB_RIGHT = pVbPlay->isPressed(0, VB_RIGHT);

    const bool isPressed_VB_VIEW = pVbPlay->isPressed(0, VB_VIEW);
    const bool isDoublePushedDown_VB_VIEW = pVbPlay->isDoublePushedDown(0, VB_VIEW);
    const bool isPressed_VB_VIEW_UP    = pVbPlay->isPressed(0, VB_VIEW_UP)    ||  (isPressed_VB_VIEW && isPressed_VB_UP   );
    const bool isPressed_VB_VIEW_DOWN  = pVbPlay->isPressed(0, VB_VIEW_DOWN)  ||  (isPressed_VB_VIEW && isPressed_VB_DOWN );
    const bool isPressed_VB_VIEW_LEFT  = pVbPlay->isPressed(0, VB_VIEW_LEFT)  ||  (isPressed_VB_VIEW && isPressed_VB_LEFT );
    const bool isPressed_VB_VIEW_RIGHT = pVbPlay->isPressed(0, VB_VIEW_RIGHT) ||  (isPressed_VB_VIEW && isPressed_VB_RIGHT);

    if (returning_cam_pos_) {
        if (returning_cam_pos_frames_ == 0) {
            returning_cam_pos_ = false;
        } else {
            returning_cam_pos_frames_--;
        }
    }

    if (isDoublePushedDown_VB_VIEW) {
        //プリセット位置に移動
        pSe_->play(SE_RETURNNING_CAM_POS);
        mv_t_x_vUP_  = 0;
        mv_t_y_vUP_  = DX_C(1);
        mv_t_z_vUP_  = 0;
        coord mv_t_x_vCAM_from = mv_t_x_vCAM_;
        coord mv_t_y_vCAM_from = mv_t_y_vCAM_;
        coord mv_t_z_vCAM_from = mv_t_z_vCAM_;
        if (isPressed_VB_DOWN) {
            mv_t_x_vCAM_ = -VamSysCamWorker::cam_radius_;
            mv_t_y_vCAM_ = 0;
            mv_t_z_vCAM_ = 0;
        } else if (isPressed_VB_RIGHT) {
            mv_t_x_vCAM_ = 0;
            mv_t_y_vCAM_ = 0;
            mv_t_z_vCAM_ = -VamSysCamWorker::cam_radius_;
        } else if (isPressed_VB_LEFT) {
            mv_t_x_vCAM_ = 0;
            mv_t_y_vCAM_ = 0;
            mv_t_z_vCAM_ = VamSysCamWorker::cam_radius_;
        } else if (isPressed_VB_UP) {
            mv_t_x_vCAM_ = VamSysCamWorker::cam_radius_;
            mv_t_y_vCAM_ = 0;
            mv_t_z_vCAM_ = 0;
        } else {
            //デフォルトはRIGHT
            mv_t_x_vCAM_ = 0;
            mv_t_y_vCAM_ = 0;
            mv_t_z_vCAM_ = -VamSysCamWorker::cam_radius_;
        }

        coord dcam = UTIL::getDistance(mv_t_x_vCAM_from, mv_t_y_vCAM_from, mv_t_z_vCAM_from,
                                       mv_t_x_vCAM_, mv_t_y_vCAM_, mv_t_z_vCAM_);
        returning_cam_pos_frames_ = (1.0 * dcam /VamSysCamWorker:: cam_radius_) * 40; //真反対にいたら2倍フレーム
        if (returning_cam_pos_frames_ < 20) {
            returning_cam_pos_frames_ = 20;
        }
        returning_cam_pos_ = true;
    }

    //注視点→カメラ の方向ベクトル(vx, vy, vz)
    const dxcoord f_mv_t_x_vCAM = C_DX(mv_t_x_vCAM_);
    const dxcoord f_mv_t_y_vCAM = C_DX(mv_t_y_vCAM_);
    const dxcoord f_mv_t_z_vCAM = C_DX(mv_t_z_vCAM_);
    const dxcoord f_mv_t_x_vUP = C_DX(mv_t_x_vUP_);
    const dxcoord f_mv_t_y_vUP = C_DX(mv_t_y_vUP_);
    const dxcoord f_mv_t_z_vUP = C_DX(mv_t_z_vUP_);
    //視点を中心にカメラが回転移動
    //カメラを中心に視点が回転移動
    //カメラをと視点が平行移動
    //共通の計算

    //ワールド回転軸方向ベクトル、(vX_axis, vY_axis, vZ_axis) を計算 begin =======>
    if (!returning_cam_pos_ &&
        (isPressed_VB_VIEW_UP || isPressed_VB_VIEW_DOWN || isPressed_VB_VIEW_LEFT || isPressed_VB_VIEW_RIGHT)
    ) {
        double vx = 0;
        double vy = 0;
        if (isPressed_VB_VIEW_UP) {
            if (isPressed_VB_VIEW_LEFT) {
                vx = 0.7071067811865475;
                vy = -0.7071067811865475;
            } else if (isPressed_VB_VIEW_RIGHT) {
                vx = 0.7071067811865475;
                vy = 0.7071067811865475;
            } else {
                vx = 1;
                vy = 0;
            }
        } else if (isPressed_VB_VIEW_DOWN) {
            if (isPressed_VB_VIEW_LEFT) {
                vx = -0.7071067811865475;
                vy = -0.7071067811865475;
            } else if (isPressed_VB_VIEW_RIGHT) {
                vx = -0.7071067811865475;
                vy = 0.7071067811865475;
            } else {
                vx = -1;
                vy = 0;
            }
        } else if (isPressed_VB_VIEW_LEFT) {
            vx = 0;
            vy = -1;
        } else if (isPressed_VB_VIEW_RIGHT) {
            vx = 0;
            vy = 1;
        }
        const D3DXVECTOR3 vecCamFromPoint(f_mv_t_x_vCAM, f_mv_t_y_vCAM, f_mv_t_z_vCAM ); //位置
        const D3DXVECTOR3 vecCamLookatPoint( 0.0f, 0.0f, 0.0f ); //注視する方向
        const D3DXVECTOR3 vecCamUp(f_mv_t_x_vUP, f_mv_t_y_vUP, f_mv_t_z_vUP); //上方向
        D3DXMATRIX matView;
        // VIEW変換行列作成
        D3DXMatrixLookAtLH(
           &matView,             // pOut [in, out] 演算結果である D3DXMATRIX 構造体へのポインタ。
           &vecCamFromPoint,     // pEye [in] 視点を定義する D3DXVECTOR3 構造体へのポインタ。この値は、平行移動に使用される。
           &vecCamLookatPoint,   // pAt  [in] カメラの注視対象を定義する D3DXVECTOR3 構造体へのポインタ。
           &vecCamUp             // pUp  [in] カレント ワールドの上方、一般には [0, 1, 0] を定義する D3DXVECTOR3 構造体へのポインタ。
        );

        //平面回転軸(vx,vy)をVPのワールド空間軸に変換
        //VP→CAMのワールド空間方向ベクトルを法線とする平面上に回転軸ベクトルは存在する
        D3DXMATRIX InvView;
        D3DXMatrixInverse(&InvView, nullptr, &matView);
        //(vx,vy,vz) * InvView
        // 11_, 12_, 13_, 14_
        // 21_, 22_, 23_, 24_
        // 31_, 32_, 33_, 34_
        // vx*11_ + vy*21_ + vz*31_ + 41_, vx*12_ + vy*22_ + vz*32_ + 42_, vx*13_ + vy*23_ + vz*33_ + 43_, vx*14_ + vy*24_ + vz*34_ + 44_
        //方向ベクトル(0,0,0)->(vx,vy,vz) を逆ビュー変換
        //変換後方向ベクトル = (vx,vy,vz)変換後座標 - (0,0,0)変換後座標
        double vX_axis = vx*InvView._11 + vy*InvView._21;
        double vY_axis = vx*InvView._12 + vy*InvView._22;
        double vZ_axis = vx*InvView._13 + vy*InvView._23;
        //正規化
        const double t = 1.0 / sqrt(vX_axis*vX_axis + vY_axis*vY_axis + vZ_axis*vZ_axis);
        vX_axis *= t;
        vY_axis *= t;
        vZ_axis *= t;

        //<==========  ワールド回転軸方向ベクトル、(vX_axis, vY_axis, vZ_axis) を計算 end

        //ある座標(x, y, z)において、回転の軸が(α, β, γ)で、θ回す回転
        //P = (0; x, y, z)
        //Q = (cos(θ/2); α sin(θ/2), β sin(θ/2), γ sin(θ/2))
        //R = (cos(θ/2); -α sin(θ/2), -β sin(θ/2), -γ sin(θ/2))
        //R P Q = (0; 答え)
        //(α, β, γ) = (vX_axis,vY_axis,vY_axis);
        //(x, y, z) は CAM か VP か UP

        //回転させたい角度
        const double sinHalf = VamSysCamWorker::mv_ang_sinHalf_;
        const double cosHalf = VamSysCamWorker::mv_ang_cosHalf_;
        Quaternion qu(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
        Quaternion qu2 = qu;
        Quaternion Q(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf);
        qu.mul(0, f_mv_t_x_vCAM, f_mv_t_y_vCAM, f_mv_t_z_vCAM); //R*P
        qu.mul(Q); //R*P*Q
        mv_t_x_vCAM_ = DX_C(qu.i);
        mv_t_y_vCAM_ = DX_C(qu.j);
        mv_t_z_vCAM_ = DX_C(qu.k);
        //UPもまわす
        {
            qu2.mul(0, f_mv_t_x_vUP, f_mv_t_y_vUP, f_mv_t_z_vUP);//R*P
            qu2.mul(Q); //R*P*Q
            mv_t_x_vUP_ = DX_C(qu2.i);
            mv_t_y_vUP_ = DX_C(qu2.j);
            mv_t_z_vUP_ = DX_C(qu2.k);
        }
    }
    const FovInfo* pFovInfo_cam = (&VamSysCamWorker::cam_hosei_fov_[pos_vam_camera_][pos_vam_up_]);
    const coord cam_x_hosei_fov = pFovInfo_cam->x_fov;
    const coord cam_y_hosei_fov = pFovInfo_cam->y_fov;
    const coord cam_z_hosei_fov = pFovInfo_cam->z_fov;
    const FovInfo* pFovInfo_vp = (&VamSysCamWorker::vp_hosei_fov_[pos_vam_camera_][pos_vam_up_]);
    const coord vp_x_hosei_fov = pFovInfo_vp->x_fov;
    const coord vp_y_hosei_fov = pFovInfo_vp->y_fov;
    const coord vp_z_hosei_fov = pFovInfo_vp->z_fov;
#ifdef MY_DEBUG
    if (cam_x_hosei_fov == 0 || cam_y_hosei_fov == 0 || cam_z_hosei_fov == 0 ||
        vp_x_hosei_fov == 0 || vp_y_hosei_fov == 0 || vp_z_hosei_fov == 0)
    {
        throwCriticalException("VamSysCamWorker::processBehavior() 想定外のCamとUp方向の組み合わせに遭遇。要調査。\n"<<
                "pos_vam_camera_="<<pos_vam_camera_<<", pos_vam_up_="<<pos_vam_up_);
    }
#endif
    const coord cam_x_hosei = RCNV(MyShip::lim_x_behaind_, MyShip::lim_x_infront_, pMyShip_x, -cam_x_hosei_fov, cam_x_hosei_fov);
    const coord vp_x_hosei  = RCNV(MyShip::lim_x_behaind_, MyShip::lim_x_infront_, pMyShip_x, -vp_x_hosei_fov , vp_x_hosei_fov );
    const coord cam_y_hosei = RCNV(MyShip::lim_y_bottom_ , MyShip::lim_y_top_    , pMyShip_y, -cam_y_hosei_fov, cam_y_hosei_fov);
    const coord vp_y_hosei  = RCNV(MyShip::lim_y_bottom_ , MyShip::lim_y_top_    , pMyShip_y, -vp_y_hosei_fov , vp_y_hosei_fov );
    const coord cam_z_hosei = RCNV(MyShip::lim_z_right_  , MyShip::lim_z_left_   , pMyShip_z, -cam_z_hosei_fov, cam_z_hosei_fov);
    const coord vp_z_hosei  = RCNV(MyShip::lim_z_right_  , MyShip::lim_z_left_   , pMyShip_z, -vp_z_hosei_fov , vp_z_hosei_fov );

    const coord mv_t_x_CAM = pMyShip_x + mv_t_x_vCAM_ - cam_x_hosei;
    const coord mv_t_y_CAM = pMyShip_y + mv_t_y_vCAM_ - cam_y_hosei;
    const coord mv_t_z_CAM = pMyShip_z + mv_t_z_vCAM_ - cam_z_hosei;
    const coord mv_t_x_VP = pMyShip_x - vp_x_hosei;
    const coord mv_t_y_VP = pMyShip_y - vp_y_hosei;
    const coord mv_t_z_VP = pMyShip_z - vp_z_hosei;

    if (_t_x_CAM != mv_t_x_CAM  || _t_y_CAM != mv_t_y_CAM || _t_z_CAM != mv_t_z_CAM ||
        _t_x_VP  != mv_t_x_VP   || _t_y_VP  != mv_t_y_VP  || _t_z_VP  != mv_t_z_VP
    ) {
        if (returning_cam_pos_) {
            slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                         returning_cam_pos_frames_, 0.3, 0.8);
            slideMvVpTo(mv_t_x_VP, mv_t_y_VP, mv_t_z_VP,
                        returning_cam_pos_frames_*0.8, 0.3, 0.8);
            slideMvUpVecTo(mv_t_x_vUP_, mv_t_y_vUP_, mv_t_z_vUP_,
                           returning_cam_pos_frames_, 0.3, 0.8);
        } else {
            slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                         60, 0.2, 0.5);
            slideMvVpTo(mv_t_x_VP, mv_t_y_VP, mv_t_z_VP,
                        60*0.8, 0.2, 0.5);
            slideMvUpVecTo(mv_t_x_vUP_, mv_t_y_vUP_, mv_t_z_vUP_,
                           60, 0.2, 0.5);
        }
    }

    //18方向へ
    if (mv_t_x_vCAM_ == 0 && mv_t_y_vCAM_ == 0 && mv_t_z_vCAM_ == 0) {
        mv_t_z_vCAM_ = -C_PX(1); //0除算防止
    }
    VamSysCamWorker::cnvVec2VamSgn(mv_t_x_vCAM_, mv_t_y_vCAM_, mv_t_z_vCAM_,
                                   cam_sgn_x_, cam_sgn_y_, cam_sgn_z_);
    pos_vam_camera_ = DIR26(cam_sgn_x_, cam_sgn_y_, cam_sgn_z_); //18方向へ
    if ((pos_vam_camera_prev_ != pos_vam_camera_) || isDoublePushedDown_VB_VIEW) {
        is_just_changed_pos_vam_cam_ = true;
        //UPも更新する
        if (mv_t_x_vUP_ == 0 && mv_t_y_vUP_ == 0 && mv_t_z_vUP_ == 0) {
            mv_t_y_vUP_ = C_PX(1); //0除算防止
        }
        VamSysCamWorker::cnvVec2VamUpSgn(pos_vam_camera_,
                                         mv_t_x_vUP_, mv_t_y_vUP_, mv_t_z_vUP_,
                                         up_sgn_x_, up_sgn_y_, up_sgn_z_);
        pos_vam_up_ = DIR26(up_sgn_x_, up_sgn_y_, up_sgn_z_);
    } else {
        is_just_changed_pos_vam_cam_ = false;
    }
    pos_vam_camera_prev_ = pos_vam_camera_;
}

void VamSysCamWorker::onSwitchCameraWork() {
    CameraWorker::onSwitchCameraWork();
}

VamSysCamWorker::~VamSysCamWorker() {
    GGAF_DELETE(pSe_);
}


void VamSysCamWorker::cnvVec2VamUpSgn(const dir26 prm_vam_cam_pos,
                                      const coord prm_vx, const coord prm_vy, const coord prm_vz,
                                      int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {
    if (prm_vam_cam_pos == VAM_POS_ZRIGHT || prm_vam_cam_pos == VAM_POS_ZLEFT) {
        //Z要素を0にしてのXY平面上の8方向の直近
        Direction8Util::cnvVec2Sgn(prm_vx, prm_vy,
                                   out_sgn_x, out_sgn_y);
        out_sgn_z = 0;
    } else if (prm_vam_cam_pos == VAM_POS_BEHIND || prm_vam_cam_pos == VAM_POS_FRONT) {
        //X要素を0にしてのYZ平面上の8方向の直近 (y→x, z→y)
        Direction8Util::cnvVec2Sgn(prm_vy, prm_vz,
                                   out_sgn_y, out_sgn_z);
        out_sgn_x = 0;
    } else if (prm_vam_cam_pos == VAM_POS_BEHIND || prm_vam_cam_pos == VAM_POS_FRONT) {
        //Y要素を0にしてのZX平面上の8方向の直近 (z→x, x→y)
        Direction8Util::cnvVec2Sgn(prm_vz, prm_vx,
                                   out_sgn_z, out_sgn_x);
        out_sgn_y = 0;
    } else {
        //カメラの位置が
        //VAM_POS_ZRIGHT_UP, VAM_POS_ZLEFT_DOWN, VAM_POS_ZRIGHT_DOWN, VAM_POS_ZLEFT_UP
        //VAM_POS_FRONT_ZRIGHT, VAM_POS_BEHIND_ZLEFT, VAM_POS_BEHIND_ZRIGHT, VAM_POS_FRONT_ZLEFT
        //VAM_POS_FRONT_UP, VAM_POS_BEHIND_DOWN, VAM_POS_FRONT_DOWN, VAM_POS_BEHIND_UP
        //の何れか
        double t_nvx, t_nvy, t_nvz; //正規化された方向ベクトル
        Direction26Util::cnvVec2Sgn(prm_vx, prm_vy, prm_vz,
                                    t_nvx, t_nvy, t_nvz,
                                    out_sgn_x, out_sgn_y, out_sgn_z);
        dir26 t_dir = DIR26(out_sgn_x, out_sgn_y, out_sgn_z);
        dir26* pa_dir8 = VamSysCamWorker::cam_to_8dir_[prm_vam_cam_pos];
        bool is_match = false;
        for (int i = 0; i < 8; i++) {
            is_match = (t_dir == pa_dir8[i]);
            if (is_match) {
                //めでたく一致したら
                //out_sgn_x, out_sgn_y, out_sgn_z をそれを採用しておしまい
                break;
            }
        }
        if (!is_match) {
            //８方向のどれにもマッチしない場合、直近の方向に収める。
            double max_dot = 0;
            dir26 nearest_dir = pa_dir8[0];
            for (int i = 0; i < 8; i++) {
                double d_vx,d_vy,d_vz;
                Direction26Util::cnvDirNo2Vec(pa_dir8[i], d_vx, d_vy, d_vz);
                double dot = t_nvx*d_vx + t_nvy*d_vy + t_nvz*d_vz;
                if (max_dot < dot) { //内積が大きいものに寄せる
                    max_dot = dot;
                    nearest_dir = pa_dir8[i];
                }
            }
            Direction26Util::cnvDirNo2Sgn(nearest_dir, out_sgn_x, out_sgn_y, out_sgn_z);
        }

    }
}

void VamSysCamWorker::cnvVec2VamSgn(const coord prm_vx, const coord prm_vy, const coord prm_vz,
                                     int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {
    //半径１に内接する正八角形の１辺は 2√2 - 2
    //                  y
    //                  ^
    //                  |
    //              ____|____
    //            ／   ^|   /＼
    //          ／   v || 1/:  ＼
    //        ／       || / :    ＼
    //       |         v|/  :      | θ=3/8π
    //      -+----------+---+------+---------> x
    //       |         0|<->       |
    //        ＼        | u      ／
    //          ＼      |      ／
    //            ＼＿＿|＿＿／
    //                  |
    // u = cos(3/8π)  = 0.38268343236509
    // v = sin(3/8π)  = 0.92387953251129

    static const double u = 0.38268343236509f;
//    static const double v = 0.92387953251129f;
    double nvx, nvy, nvz;
    UTIL::getNormalizedVector(prm_vx, prm_vy, prm_vz,
                              nvx, nvy, nvz);
    if (nvx < -u) {
        out_sgn_x = -1;
    } else if (u < nvx) {
        out_sgn_x = +1;
    } else {
        out_sgn_x = 0;
    }

    if (nvy < -u) {
        out_sgn_y = -1;
    } else if (u < nvy) {
        out_sgn_y = +1;
    } else {
        out_sgn_y = 0;
    }

    if (nvz < -u) {
        out_sgn_z = -1;
    } else if (u < nvz) {
        out_sgn_z = +1;
    } else {
        out_sgn_z = 0;
    }
    //VAM用
    if ((out_sgn_x != 0 && out_sgn_y != 0 && out_sgn_z != 0) || (out_sgn_x == 0 && out_sgn_y == 0 && out_sgn_z == 0)) {
        //斜め方向又は0,0,0の場合、VAM方向に無理やり吸収
        //どこに近いか内積で比較して計算
        dir26 td = DIR26(out_sgn_x, out_sgn_y, out_sgn_z);
        // nvx, nvy, nvz;
        double max_dot = 0;
        dir26 nearest_dir = 0;
        dir26* pa_dir6 = VamSysCamWorker::nbhd_dir_[td];
        for (int i = 0; i < 6; i++) {
            double d_vx,d_vy,d_vz;
            Direction26Util::cnvDirNo2Vec(pa_dir6[i], d_vx, d_vy, d_vz);
            double dot = nvx*d_vx + nvy*d_vy + nvz*d_vz;
            if (max_dot < dot) { //内積が大きいものに寄せる
                max_dot = dot;
                nearest_dir = pa_dir6[i];
            }
        }
        Direction26Util::cnvDirNo2Sgn(nearest_dir, out_sgn_x, out_sgn_y, out_sgn_z);
    }
}
