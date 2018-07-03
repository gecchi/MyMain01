#include "VamSysCamWorker2.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/camera/Camera.h"
#include "jp/gecchi/VioletVreath/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"
#include "jp/ggaf/dxcore/util/GgafDx8DirectionUtil.h"
#include "jp/ggaf/dxcore/util/GgafDxQuaternion.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

#include "jp/gecchi/VioletVreath/actor/camera/CameraUpVector.h"
#include "jp/ggaf/dxcore/sound/GgafDxSeTransmitter.h"
#include <math.h>

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_RETURNNING_CAM_POS     ,
};

dir26 VamSysCamWorker2::nbhd_dir_entity_[3*3*3][6];
dir26 (*VamSysCamWorker2::nbhd_dir_)[6];
dir26 VamSysCamWorker2::cam_to_8dir_entity_[3*3*3][8];
dir26 (*VamSysCamWorker2::cam_to_8dir_)[8];

bool VamSysCamWorker2::initStatic() {
    for (int i = 0; i < 3*3*3; i++) {
        for (int j = 0; j < 6; j++) {
            VamSysCamWorker2::nbhd_dir_entity_[i][j] = DIR26_NULL;
        }
    }
    //第１要素を -13 ～ 0 ～ 13 （ DIR26(-1,-1,-1) ～ DIR26(0,0,0) ～ DIR26(1,1,1) ）でアクセスす為に
    //真ん中要素のポインタを nbhd_dir_[0] に登録
    VamSysCamWorker2::nbhd_dir_ = (int (*)[6])(&(VamSysCamWorker2::nbhd_dir_entity_[13][0])); //13 は DIR26 の真ん中の要素

    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1, 1)][0] = DIR26( 1, 1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1, 1)][1] = DIR26( 1, 0, 1);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1, 1)][2] = DIR26( 1, 0, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1, 1)][3] = DIR26( 0, 1, 1);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1, 1)][4] = DIR26( 0, 1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1, 1)][5] = DIR26( 0, 0, 1);

    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1,-1)][0] = DIR26( 1, 1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1,-1)][1] = DIR26( 1, 0,-1);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1,-1)][2] = DIR26( 1, 0, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1,-1)][3] = DIR26( 0, 1,-1);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1,-1)][4] = DIR26( 0, 1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1, 1,-1)][5] = DIR26( 0, 0,-1);

    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1, 1)][0] = DIR26( 1,-1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1, 1)][1] = DIR26( 1, 0, 1);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1, 1)][2] = DIR26( 1, 0, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1, 1)][3] = DIR26( 0,-1, 1);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1, 1)][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1, 1)][5] = DIR26( 0, 0, 1);

    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1,-1)][0] = DIR26( 1,-1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1,-1)][1] = DIR26( 1, 0,-1);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1,-1)][2] = DIR26( 1, 0, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1,-1)][3] = DIR26( 0,-1,-1);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1,-1)][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26( 1,-1,-1)][5] = DIR26( 0, 0,-1);

    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1, 1)][0] = DIR26(-1, 1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1, 1)][1] = DIR26(-1, 0, 1);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1, 1)][2] = DIR26(-1, 0, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1, 1)][3] = DIR26( 0, 1, 1);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1, 1)][4] = DIR26( 0, 1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1, 1)][5] = DIR26( 0, 0, 1);

    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1,-1)][0] = DIR26(-1, 1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1,-1)][1] = DIR26(-1, 0,-1);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1,-1)][2] = DIR26(-1, 0, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1,-1)][3] = DIR26( 0, 1,-1);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1,-1)][4] = DIR26( 0, 1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1, 1,-1)][5] = DIR26( 0, 0,-1);

    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1, 1)][0] = DIR26(-1,-1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1, 1)][1] = DIR26(-1, 0, 1);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1, 1)][2] = DIR26(-1, 0, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1, 1)][3] = DIR26( 0,-1, 1);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1, 1)][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1, 1)][5] = DIR26( 0, 0, 1);

    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1,-1)][0] = DIR26(-1,-1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1,-1)][1] = DIR26(-1, 0,-1);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1,-1)][2] = DIR26(-1, 0, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1,-1)][3] = DIR26( 0,-1,-1);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1,-1)][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::nbhd_dir_[DIR26(-1,-1,-1)][5] = DIR26( 0, 0,-1);

//////////////////////
    for (int i = 0; i < 3*3*3; i++) {
        for (int j = 0; j < 8; j++) {
            VamSysCamWorker2::cam_to_8dir_entity_[i][j] = DIR26_NULL;
        }
    }
    //第１要素を -13 ～ 0 ～ 13 （ DIR26(-1,-1,-1) ～ DIR26(0,0,0) ～ DIR26(1,1,1) ）でアクセスす為に
    //真ん中要素のポインタを cam_to_8dir_[0] に登録
    VamSysCamWorker2::cam_to_8dir_ = (int (*)[8])(&(VamSysCamWorker2::cam_to_8dir_entity_[13][0])); //13 は DIR26 の真ん中の要素

    //全て右回りに順に設定すること
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT][1] = DIR26(+1,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT][2] = DIR26(+1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT][3] = DIR26(+1,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT][5] = DIR26(-1,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT][6] = DIR26(-1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT][7] = DIR26(-1,+1, 0);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT][1] = DIR26(-1,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT][2] = DIR26(-1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT][3] = DIR26(-1,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT][5] = DIR26(+1,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT][6] = DIR26(+1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT][7] = DIR26(+1,+1, 0);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT][1] = DIR26( 0,+1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT][2] = DIR26( 0, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT][3] = DIR26( 0,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT][5] = DIR26( 0,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT][6] = DIR26( 0, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT][7] = DIR26( 0,+1,-1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND][0] = DIR26( 0,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND][1] = DIR26( 0,+1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND][2] = DIR26( 0, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND][3] = DIR26( 0,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND][5] = DIR26( 0,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND][6] = DIR26( 0, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND][7] = DIR26( 0,+1,+1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_UP][0] = DIR26( 0, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_UP][1] = DIR26(+1, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_UP][2] = DIR26(+1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_UP][3] = DIR26(+1, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_UP][4] = DIR26( 0, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_UP][5] = DIR26(-1, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_UP][6] = DIR26(-1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_UP][7] = DIR26(-1, 0,+1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_DOWN][0] = DIR26( 0, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_DOWN][1] = DIR26(-1, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_DOWN][2] = DIR26(-1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_DOWN][3] = DIR26(-1, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_DOWN][4] = DIR26( 0, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_DOWN][5] = DIR26(+1, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_DOWN][6] = DIR26(+1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_DOWN][7] = DIR26(+1, 0,+1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_UP][0] = DIR26( 0,+1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_UP][1] = DIR26(+1,+1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_UP][2] = DIR26(+1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_UP][3] = DIR26(+1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_UP][4] = DIR26( 0,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_UP][5] = DIR26(-1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_UP][6] = DIR26(-1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_UP][7] = DIR26(-1,+1,+1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][0] = DIR26( 0,+1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][1] = DIR26(-1,+1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][2] = DIR26(-1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][3] = DIR26(-1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][4] = DIR26( 0,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][5] = DIR26(+1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][6] = DIR26(+1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_DOWN][7] = DIR26(+1,+1,+1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][0] = DIR26( 0,+1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][1] = DIR26(+1,+1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][2] = DIR26(+1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][3] = DIR26(+1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][4] = DIR26( 0,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][5] = DIR26(-1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][6] = DIR26(-1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZRIGHT_DOWN][7] = DIR26(-1,+1,-1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_UP][0] = DIR26( 0,+1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_UP][1] = DIR26(-1,+1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_UP][2] = DIR26(-1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_UP][3] = DIR26(-1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_UP][4] = DIR26( 0,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_UP][5] = DIR26(+1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_UP][6] = DIR26(+1, 0, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_ZLEFT_UP][7] = DIR26(+1,+1,-1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][1] = DIR26(+1,+1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][2] = DIR26(+1, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][3] = DIR26(+1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][5] = DIR26(-1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][6] = DIR26(-1, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZRIGHT][7] = DIR26(-1,+1,-1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][1] = DIR26(-1,+1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][2] = DIR26(-1, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][3] = DIR26(-1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][5] = DIR26(+1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][6] = DIR26(+1, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZLEFT][7] = DIR26(+1,+1,+1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][1] = DIR26(+1,+1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][2] = DIR26(+1, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][3] = DIR26(+1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][5] = DIR26(-1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][6] = DIR26(-1, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_ZRIGHT][7] = DIR26(-1,+1,+1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][0] = DIR26( 0,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][1] = DIR26(-1,+1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][2] = DIR26(-1, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][3] = DIR26(-1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][4] = DIR26( 0,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][5] = DIR26(+1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][6] = DIR26(+1, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_ZLEFT][7] = DIR26(+1,+1,-1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_UP][0] = DIR26(-1,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_UP][1] = DIR26(-1,+1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_UP][2] = DIR26( 0, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_UP][3] = DIR26(+1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_UP][4] = DIR26(+1,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_UP][5] = DIR26(+1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_UP][6] = DIR26( 0, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_UP][7] = DIR26(-1,+1,-1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_DOWN][0] = DIR26(-1,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_DOWN][1] = DIR26(-1,+1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_DOWN][2] = DIR26( 0, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_DOWN][3] = DIR26(+1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_DOWN][4] = DIR26(+1,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_DOWN][5] = DIR26(+1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_DOWN][6] = DIR26( 0, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_DOWN][7] = DIR26(-1,+1,+1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_DOWN][0] = DIR26(+1,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_DOWN][1] = DIR26(+1,+1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_DOWN][2] = DIR26( 0, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_DOWN][3] = DIR26(-1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_DOWN][4] = DIR26(-1,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_DOWN][5] = DIR26(-1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_DOWN][6] = DIR26( 0, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_FRONT_DOWN][7] = DIR26(+1,+1,-1);

    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_UP][0] = DIR26(+1,+1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_UP][1] = DIR26(+1,+1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_UP][2] = DIR26( 0, 0,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_UP][3] = DIR26(-1,-1,-1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_UP][4] = DIR26(-1,-1, 0);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_UP][5] = DIR26(-1,-1,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_UP][6] = DIR26( 0, 0,+1);
    VamSysCamWorker2::cam_to_8dir_[VAM_POS_BEHIND_UP][7] = DIR26(+1,+1,+1);

    _TRACE_("VamSysCamWorker2::initStatic() 初期化OK");
    return true;
}

VamSysCamWorker2::VamSysCamWorker2(const char* prm_name, Camera* prm_pCamera) : CameraWorker(prm_name, (DefaultCamera*)prm_pCamera) {
    _class_name = "VamSysCamWorker2";

    pMyShip_ = nullptr; //MyShipSceneに設定してもらう

    pos_vam_camera_ = VAM_POS_ZRIGHT;
    pos_vam_camera_prev_ = VAM_POS_NON;
    is_just_changed_pos_vam_cam_ = false;

    returning_cam_pos_ = false;
    returning_cam_pos_frames_ = 0;

    pos_vam_up_ = DIR26(0,1,0);
    pSe_ = NEW GgafDxSeTransmitter();
    pSe_->set(SE_RETURNNING_CAM_POS, "WAVE_MY_RETURNNING_CAM_POS" ,0);

    dxcoord cam_dz_org = ABS(prm_pCamera->_cameraZ_org); //DZ
    cam_radius_ = DX_C(cam_dz_org);
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
    //        CAM_HOSEI_DX_ = DX_C(cam_DX);
    //        //直角三角形 cam, vp, cam_x を考える
    //        //∠vp(小さいほう)  = π-θ
    //        double vp_th2 = 2*PI - vp_th;
    //        //tan(∠vp(小さいほう)) =  DZ / (cam_x ～ vp_xの長さ)
    //        //cam_x ～ vp_xの長さ = DZ / tan(∠vp(小さいほう))
    //        // vp_DX = cam_DX - (cam_x ～ vp_xの長さ)
    //        double vp_DX = cam_DX - (DZ / tan(vp_th2));
    //        VP_HOSEI_DX_ = DX_C(vp_DX);

    double rad_half_fovX = prm_pCamera->_rad_half_fovX;
    double vpx_th = 2*PI * 100.0 / 360.0; //ここを調整する！
    double cam_DX = cam_dz_org / tan(PI-vpx_th-rad_half_fovX);
    CAM_HOSEI_DX_ = DX_C(cam_DX);
    double vp_DX = cam_DX - (cam_dz_org / tan(PI - vpx_th));
    VP_HOSEI_DX_ = DX_C(vp_DX);

    double rad_half_fovY = prm_pCamera->_rad_half_fovY;
    double vpy_th = (PI/2); //ここを調整する！
    double cam_DY = cam_dz_org / tan(PI-vpy_th-rad_half_fovY);
    CAM_HOSEI_DY_ = DX_C(cam_DY);
    double vp_DY = cam_DY - (cam_dz_org / tan(PI - vpy_th));
    VP_HOSEI_DY_ = DX_C(vp_DY);

    double vpz_th = vpx_th;
    double cam_DZ = cam_dz_org / tan(PI-vpx_th-rad_half_fovX); //そのまま後ろに回ること多いので、rad_half_fovXで
    CAM_HOSEI_DZ_ = DX_C(cam_DZ);
    double vp_DZ = cam_DZ - (cam_dz_org / tan(PI - vpz_th));
    VP_HOSEI_DZ_ = DX_C(vp_DZ);

    mv_t_x_vUP_  = 0;
    mv_t_y_vUP_  = DX_C(1);
    mv_t_z_vUP_  = 0;

    mv_t_x_vCAM_ = 0;
    mv_t_y_vCAM_ = 0;
    mv_t_z_vCAM_ = -cam_radius_;

    static volatile bool is_init = VamSysCamWorker2::initStatic(); //静的メンバ初期化
}


void VamSysCamWorker2::initialize() {
    CameraWorker::initialize();
    _TRACE_(FUNC_NAME<<" this="<<NODE_INFO);
}
void VamSysCamWorker2::onActive() {
    CameraWorker::onActive();
}

void VamSysCamWorker2::processBehavior() {
    if (pMyShip_ == nullptr) {
        return; //MyShipSceneシーンが未だならカメラワーク禁止
    }
    VirtualButton* pVbPlay = VB_PLAY;
    coord pMyShip_x = pMyShip_->_x;
    coord pMyShip_y = pMyShip_->_y;
    coord pMyShip_z = pMyShip_->_z;
    frame cam_mv_frame = 20;

    bool isPressed_VB_VIEW_UP    = pVbPlay->isPressed(VB_VIEW_UP);
    bool isPressed_VB_VIEW_DOWN  = pVbPlay->isPressed(VB_VIEW_DOWN);
    bool isPressed_VB_VIEW_LEFT  = pVbPlay->isPressed(VB_VIEW_LEFT);
    bool isPressed_VB_VIEW_RIGHT = pVbPlay->isPressed(VB_VIEW_RIGHT);

    if (returning_cam_pos_) {
        if (returning_cam_pos_frames_ == 0) {
            returning_cam_pos_ = false;
        } else {
            returning_cam_pos_frames_--;
        }
    }

    if (!returning_cam_pos_) {
        if (pVbPlay->arePushedDownAtOnce(VB_VIEW_UP, VB_VIEW_DOWN) ) {
            pSe_->play(SE_RETURNNING_CAM_POS);
            coord dcam = UTIL::getDistance(mv_t_x_vCAM_, mv_t_y_vCAM_, mv_t_z_vCAM_,
                                           (coord)0, (coord)0,-cam_radius_);
            returning_cam_pos_frames_ = (1.0 * dcam / cam_radius_) * 30; //真反対にいたら30*2=60フレーム
            if (returning_cam_pos_frames_ < 10) {
                returning_cam_pos_frames_ = 10;
            }
            returning_cam_pos_ = true;

            mv_t_x_vUP_  = 0;
            mv_t_y_vUP_  = DX_C(1);
            mv_t_z_vUP_  = 0;

            mv_t_x_vCAM_ = 0;
            mv_t_y_vCAM_ = 0;
            mv_t_z_vCAM_ = -cam_radius_;
            cam_mv_frame = returning_cam_pos_frames_;
        }
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
        double vx, vy, vz;
        vx = vy = vz = 0;
        if (isPressed_VB_VIEW_UP) {
            vx = 1;
        }
        if (isPressed_VB_VIEW_DOWN) {
            vx = -1;
        }
        if (isPressed_VB_VIEW_LEFT) {
            vy = -1;
        }
        if (isPressed_VB_VIEW_RIGHT) {
            vy = 1;
        }
        double d = sqrt(vx * vx + vy * vy);
        double t = 1.0 / d;
        vx = t * vx;
        vy = t * vy;
        vz = 0;

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
        D3DXMatrixInverse( &InvView, nullptr, &matView);
        //(vx,vy,vz) * InvView
        // 11_, 12_, 13_, 14_
        // 21_, 22_, 23_, 24_
        // 31_, 32_, 33_, 34_
        // vx*11_ + vy*21_ + vz*31_ + 41_, vx*12_ + vy*22_ + vz*32_ + 42_, vx*13_ + vy*23_ + vz*33_ + 43_, vx*14_ + vy*24_ + vz*34_ + 44_
        //方向ベクトル(0,0,0)->(vx,vy,vz) を逆ビュー変換
        //変換後方向ベクトル = (vx,vy,vz)変換後座標 - (0,0,0)変換後座標
        //               <------------  (vx,vy,vz)変換後座標-------------------------->    <-- (0,0,0)変換後座標 -->
        double vX_axis = vx*InvView._11 + vy*InvView._21 + vz*InvView._31 + InvView._41  -    InvView._41;
        double vY_axis = vx*InvView._12 + vy*InvView._22 + vz*InvView._32 + InvView._42  -    InvView._42;
        double vZ_axis = vx*InvView._13 + vy*InvView._23 + vz*InvView._33 + InvView._43  -    InvView._43;
        //正規化
        double t2 = 1.0 / sqrt(vX_axis * vX_axis + vY_axis * vY_axis + vZ_axis * vZ_axis);
        vX_axis = t2 * vX_axis;
        vY_axis = t2 * vY_axis;
        vZ_axis = t2 * vZ_axis;

        //<==========  ワールド回転軸方向ベクトル、(vX_axis, vY_axis, vZ_axis) を計算 end

        //ある座標(x, y, z)において、回転の軸が(α, β, γ)で、θ回す回転
        //P = (0; x, y, z)
        //Q = (cos(θ/2); α sin(θ/2), β sin(θ/2), γ sin(θ/2))
        //R = (cos(θ/2); -α sin(θ/2), -β sin(θ/2), -γ sin(θ/2))
        //R P Q = (0; 答え)
        //(α, β, γ) = (vX_axis,vY_axis,vY_axis);
        //(x, y, z) は CAM か VP か UP

        //回転させたい角度
        const double ang = (2*PI) * (2.0/360.0); //2度

        double sinHalf = sin(ang/2);
        double cosHalf = cos(ang/2);
        GgafDxQuaternion qu(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
        GgafDxQuaternion qu2 = qu;
        GgafDxQuaternion Q(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf);
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

    coord cam_x_hosei = RCNV(MyShip::lim_x_behaind_, MyShip::lim_x_infront_, pMyShip_x, -CAM_HOSEI_DX_, CAM_HOSEI_DX_);
    coord vp_x_hosei = RCNV(MyShip::lim_x_behaind_, MyShip::lim_x_infront_, pMyShip_x, -VP_HOSEI_DX_, VP_HOSEI_DX_);
    coord cam_y_hosei = RCNV(MyShip::lim_y_bottom_, MyShip::lim_y_top_, pMyShip_y, -CAM_HOSEI_DY_, CAM_HOSEI_DY_);
    coord vp_y_hosei = RCNV(MyShip::lim_y_bottom_, MyShip::lim_y_top_, pMyShip_y, -VP_HOSEI_DY_, VP_HOSEI_DY_);
    coord cam_z_hosei = RCNV(MyShip::lim_z_right_, MyShip::lim_z_left_, pMyShip_z, -CAM_HOSEI_DZ_, CAM_HOSEI_DZ_);
    coord vp_z_hosei = RCNV(MyShip::lim_z_right_, MyShip::lim_z_left_, pMyShip_z, -VP_HOSEI_DZ_, VP_HOSEI_DZ_);
    //CAM_HOSEI_DY_ VP_HOSEI_DY_ がなんかでかい
    coord mv_t_x_CAM = pMyShip_x + mv_t_x_vCAM_ - cam_x_hosei;
    coord mv_t_y_CAM = pMyShip_y + mv_t_y_vCAM_ - cam_y_hosei;
    coord mv_t_z_CAM = pMyShip_z + mv_t_z_vCAM_ - cam_z_hosei;
    coord mv_t_x_VP = pMyShip_x - vp_x_hosei;
    coord mv_t_y_VP = pMyShip_y - vp_y_hosei;
    coord mv_t_z_VP = pMyShip_z - vp_z_hosei;

    if (t_x_CAM_ != mv_t_x_CAM  || t_y_CAM_ != mv_t_y_CAM || t_z_CAM_ != mv_t_z_CAM ||
        t_x_VP_  != mv_t_x_VP   || t_y_VP_  != mv_t_y_VP  || t_z_VP_  != mv_t_z_VP
    ) {
        slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM, cam_mv_frame);
        slideMvVpTo(mv_t_x_VP, mv_t_y_VP, mv_t_z_VP, cam_mv_frame);
        slideMvUpVecTo(mv_t_x_vUP_, mv_t_y_vUP_, mv_t_z_vUP_, cam_mv_frame);
    }

    int cam_sgn_x, cam_sgn_y, cam_sgn_z;
    if (mv_t_x_vCAM_ == 0 && mv_t_y_vCAM_ == 0 && mv_t_z_vCAM_ == 0) {
        mv_t_z_vCAM_ = -C_PX(1); //0除算防止
    }
    //18方向へ
    VamSysCamWorker2::cnvVec2VamSgn(mv_t_x_vCAM_, mv_t_y_vCAM_, mv_t_z_vCAM_, cam_sgn_x, cam_sgn_y, cam_sgn_z);
    pos_vam_camera_ = DIR26(cam_sgn_x, cam_sgn_y, cam_sgn_z);
    if (pos_vam_camera_prev_ != pos_vam_camera_) {
        is_just_changed_pos_vam_cam_ = true;
        //UPも更新する
        int up_sgn_x, up_sgn_y, up_sgn_z;
        if (mv_t_x_vUP_ == 0 && mv_t_y_vUP_ == 0 && mv_t_z_vUP_ == 0) {
            mv_t_y_vUP_ = C_PX(1); //0除算防止
        }
        VamSysCamWorker2::cnvVec2VamUpSgn(pos_vam_camera_,
                                          mv_t_x_vUP_, mv_t_y_vUP_, mv_t_z_vUP_,
                                          up_sgn_x, up_sgn_y, up_sgn_z);
        pos_vam_up_ = DIR26(up_sgn_x, up_sgn_y, up_sgn_z);
    } else {
        is_just_changed_pos_vam_cam_ = false;
    }

    pos_vam_camera_prev_ = pos_vam_camera_;
}

void VamSysCamWorker2::onSwitchCameraWork() {
    CameraWorker::onSwitchCameraWork();
}

VamSysCamWorker2::~VamSysCamWorker2() {
    GGAF_DELETE(pSe_);
}


void VamSysCamWorker2::cnvVec2VamUpSgn(dir26 prm_vam_cam_pos,
                                       coord prm_vx, coord prm_vy, coord prm_vz,
                                       int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {

    if (prm_vam_cam_pos == VAM_POS_ZRIGHT || prm_vam_cam_pos == VAM_POS_ZLEFT) {
        //Z要素を0にしてのXY平面上の8方向の直近
        GgafDx8DirectionUtil::cnvVec2Sgn(prm_vx, prm_vy,
                                         out_sgn_x, out_sgn_y);
        out_sgn_z = 0;
    } else if (prm_vam_cam_pos == VAM_POS_BEHIND || prm_vam_cam_pos == VAM_POS_FRONT) {
        //X要素を0にしてのYZ平面上の8方向の直近 (y→x, z→y)
        GgafDx8DirectionUtil::cnvVec2Sgn(prm_vy, prm_vz,
                                         out_sgn_y, out_sgn_z);
        out_sgn_x = 0;
    } else if (prm_vam_cam_pos == VAM_POS_BEHIND || prm_vam_cam_pos == VAM_POS_FRONT) {
        //Y要素を0にしてのZX平面上の8方向の直近 (z→x, x→y)
        GgafDx8DirectionUtil::cnvVec2Sgn(prm_vz, prm_vx,
                                         out_sgn_z, out_sgn_x);
        out_sgn_y = 0;
    } else {
        //カメラの位置が
        //VAM_POS_ZRIGHT_UP, VAM_POS_ZLEFT_DOWN, VAM_POS_ZRIGHT_DOWN, VAM_POS_ZLEFT_UP
        //VAM_POS_FRONT_ZRIGHT, VAM_POS_BEHIND_ZLEFT, VAM_POS_BEHIND_ZRIGHT, VAM_POS_FRONT_ZLEFT
        //VAM_POS_FRONT_UP, VAM_POS_BEHIND_DOWN, VAM_POS_FRONT_DOWN, VAM_POS_BEHIND_UP
        //の何れか
        float t_nvx, t_nvy, t_nvz; //正規化された方向ベクトル
        GgafDx26DirectionUtil::cnvVec2Sgn(prm_vx, prm_vy, prm_vz,
                                          t_nvx, t_nvy, t_nvz,
                                          out_sgn_x, out_sgn_y, out_sgn_z);
        dir26 t_dir = DIR26(out_sgn_x, out_sgn_y, out_sgn_z);
        dir26* pa_dir8 = VamSysCamWorker2::cam_to_8dir_[prm_vam_cam_pos];
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
            float max_dot = 0;
            dir26 nearest_dir = pa_dir8[0];
            for (int i = 0; i < 8; i++) {
                float d_vx,d_vy,d_vz;
                GgafDx26DirectionUtil::cnvDirNo2Vec(pa_dir8[i], d_vx, d_vy, d_vz);
                float dot = t_nvx*d_vx + t_nvy*d_vy + t_nvz*d_vz;
                if (max_dot < dot) { //内積が大きいものに寄せる
                    max_dot = dot;
                    nearest_dir = pa_dir8[i];
                }
            }
            GgafDx26DirectionUtil::cnvDirNo2Sgn(nearest_dir, out_sgn_x, out_sgn_y, out_sgn_z);
        }

    }
}

void VamSysCamWorker2::cnvVec2VamSgn(coord prm_vx, coord prm_vy, coord prm_vz,
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

    static const float u = 0.38268343236509f;
    static const float v = 0.92387953251129f;
    float nvx, nvy, nvz;
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
        float max_dot = 0;
        dir26 nearest_dir = 0;
        dir26* pa_dir6 = VamSysCamWorker2::nbhd_dir_[td];
        for (int i = 0; i < 6; i++) {
            float d_vx,d_vy,d_vz;
            GgafDx26DirectionUtil::cnvDirNo2Vec(pa_dir6[i], d_vx, d_vy, d_vz);
            float dot = nvx*d_vx + nvy*d_vy + nvz*d_vz;
            if (max_dot < dot) { //内積が大きいものに寄せる
                max_dot = dot;
                nearest_dir = pa_dir6[i];
            }
        }
        GgafDx26DirectionUtil::cnvDirNo2Sgn(nearest_dir, out_sgn_x, out_sgn_y, out_sgn_z);
    }
}
