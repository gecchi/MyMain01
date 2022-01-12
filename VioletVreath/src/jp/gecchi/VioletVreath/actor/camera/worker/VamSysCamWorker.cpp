#include "VamSysCamWorker.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/GeoDriver.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/camera/Camera.h"
#include "jp/gecchi/VioletVreath/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/dx/actor/supporter/GeoDriverAssistantA.h"
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
    //��P�v�f�� -13 �` 0 �` 13 �i DIR26(-1,-1,-1) �` DIR26(0,0,0) �` DIR26(1,1,1) �j�ŃA�N�Z�X���ׂ�
    //�^�񒆗v�f�̃|�C���^�� nbhd_dir_[0] �ɓo�^
    VamSysCamWorker::nbhd_dir_ = (int (*)[6])(&(VamSysCamWorker::nbhd_dir_entity_[13][0])); //13 �� DIR26 �̐^�񒆂̗v�f

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
    //��P�v�f�� -13 �` 0 �` 13 �i DIR26(-1,-1,-1) �` DIR26(0,0,0) �` DIR26(1,1,1) �j�ŃA�N�Z�X���ׂ�
    //�^�񒆗v�f�̃|�C���^�� cam_to_8dir_[0] �ɓo�^
    VamSysCamWorker::cam_to_8dir_ = (int (*)[8])(&(VamSysCamWorker::cam_to_8dir_entity_[13][0])); //13 �� DIR26 �̐^�񒆂̗v�f

    //�S�ĉE���ɏ��ɐݒ肷�邱��
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
    //    |                      /        �� �����x�N�g��
    //    |                     /       �^
    //    |                    /      �^               ��
    //    |          cam_x    /     �^          �Q��   �` = �J�����̕\���̉E�̋��E���x�N�g��
    // ---+-------------+----/----�^------���Q��---------
    //    |         ^   :   /   �^ vp   �Q��    ��
    //    |         |   :  /  �^    �Q��   :     a  ��ʂ̒[������X���̌�_
    //    |      DZ |   : / �^  �Q��       :
    //    |         v   :/�^�Q��  b        :
    //    |            ��------------------:
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
    //��vp(�傫���ق�)  = �� �Ƃ����
    //��a = 2�� - H_FOVX - ��
    //        coord DZ  = cam_radius_;
    //        double vp_th = (PI/2); //�����𒲐�����I
    //        double H_FOVX = prm_pCamera->_rad_half_fovX;
    //        double a = PI - H_FOVX - vp_th;
    //        //cam����X���ɕ��s���Ɓ��`(�J�����̕\���̉E�̋��E���x�N�g��)�̂Ȃ��p(b)�́A���p�Ŋp a�Ɠ�����
    //        //��b = a = PI - H_FOVX - vp_th;
    //        double b = PI - H_FOVX - vp_th;;
    //        //cam_x �` a �̒�����DX
    //        //tan(b) = DZ/cam_DX ���Acam_DX = DZ / tan(b)
    //        double cam_DX = DZ / tan(b);
    //        CAM_HOSEI_FOV_X_DX_ = DX_C(cam_DX);
    //        //���p�O�p�` cam, vp, cam_x ���l����
    //        //��vp(�������ق�)  = ��-��
    //        double vp_th2 = 2*PI - vp_th;
    //        //tan(��vp(�������ق�)) =  DZ / (cam_x �` vp_x�̒���)
    //        //cam_x �` vp_x�̒��� = DZ / tan(��vp(�������ق�))
    //        // vp_DX = cam_DX - (cam_x �` vp_x�̒���)
    //        double vp_DX = cam_DX - (DZ / tan(vp_th2));
    //        VP_HOSEI_FOV_X_DX_ = DX_C(vp_DX);

    double rad_half_fovX = prm_pCamera->_rad_half_fovX * 0.8; //0.8�͒����A1.0�ō��E�[�܂ōs��
    double vpx_th = 2*PI * 120.0 / 360.0; //�����𒲐�����I
    double cam_DX = cam_dz_org / tan(PI-vpx_th-rad_half_fovX);
    coord CAM_HOSEI_FOV_X = DX_C(cam_DX);
    double vp_DX = cam_DX - (cam_dz_org / tan(PI - vpx_th));
    coord VP_HOSEI_FOV_X = DX_C(vp_DX);

    double rad_half_fovY = prm_pCamera->_rad_half_fovY * 0.9; //0.9�͒����A1.0�ŏ㉺�[�܂ōs��
    double vpy_th = 2*PI * 100.0 / 360.0; //�����𒲐�����I
    double cam_DY = cam_dz_org / tan(PI-vpy_th-rad_half_fovY);
    coord CAM_HOSEI_FOV_Y = DX_C(cam_DY);
    double vp_DY = cam_DY - (cam_dz_org / tan(PI - vpy_th));
    coord VP_HOSEI_FOV_Y = DX_C(vp_DY);
    //���s���␳�͓K��
    coord CAM_HOSEI_FOV_Z = CAM_HOSEI_FOV_Y/4;
    coord VP_HOSEI_FOV_Z = VP_HOSEI_FOV_Y/4;

    //�΂߂����Ƃ��̕␳
//    int CAM_HOSEI_FOV_XY = CAM_HOSEI_FOV_Y * 0.7071067811865475; //1/��2
//    int VP_HOSEI_FOV_XY = VP_HOSEI_FOV_Y * 0.7071067811865475;  //1/��2
//    int CAM_HOSEI_FOV_YZ = CAM_HOSEI_FOV_Z * 0.7071067811865475; //1/��2
//    int VP_HOSEI_FOV_YZ = VP_HOSEI_FOV_Z * 0.7071067811865475;  //1/��2
//    int CAM_HOSEI_FOV_ZX = CAM_HOSEI_FOV_X * 0.7071067811865475; //1/��2
//    int VP_HOSEI_FOV_ZX = VP_HOSEI_FOV_X * 0.7071067811865475;  //1/��2

//    int CAM_HOSEI_FOV_XYZ = CAM_HOSEI_FOV_Z * 0.5773502691896258; //1/��3
//    int VP_HOSEI_FOV_XYZ = VP_HOSEI_FOV_Z * 0.5773502691896258;   //1/��3

    int CAM_HOSEI_FOV_XY = CAM_HOSEI_FOV_Y / 2;
    int VP_HOSEI_FOV_XY = VP_HOSEI_FOV_Y / 2;
    int CAM_HOSEI_FOV_YZ = CAM_HOSEI_FOV_Z;
    int VP_HOSEI_FOV_YZ = VP_HOSEI_FOV_Z;
    int CAM_HOSEI_FOV_ZX = CAM_HOSEI_FOV_X / 2;
    int VP_HOSEI_FOV_ZX = VP_HOSEI_FOV_X / 2;

    int CAM_HOSEI_FOV_XYZ = CAM_HOSEI_FOV_Z;
    int VP_HOSEI_FOV_XYZ = CAM_HOSEI_FOV_Z;


    VamSysCamWorker::cam_hosei_fov_ =  (FovInfo (*)[3*3*3])(&(VamSysCamWorker::cam_hosei_fov_entity_[13][13])); //13 �� 3*3*3=27 �̐^�񒆂̗v�f�A_relation_up_vec[-13�`13][-13�`13]�ŃA�N�Z�X�����
    //                                 CAM             UP                   x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26( 0,+1, 0)].set(CAM_HOSEI_FOV_X , CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1,+1, 0)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1, 0, 0)].set(CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_X , CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1,-1, 0)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26( 0,-1, 0)].set(CAM_HOSEI_FOV_X , CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1,-1, 0)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1, 0, 0)].set(CAM_HOSEI_FOV_Y , CAM_HOSEI_FOV_X , CAM_HOSEI_FOV_Z);
    VamSysCamWorker::cam_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1,+1, 0)].set(CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_XY, CAM_HOSEI_FOV_Z);
    // �^���͓����Ȃ̂ŁAVAM_POS_ZRIGHT �̒�`�� VAM_POS_ZLEFT �ɃR�s�[
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
    // �^���͓����Ȃ̂ŁAVAM_POS_FRONT �̒�`�� VAM_POS_BEHIND �ɃR�s�[
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
    // �^���͓����Ȃ̂ŁAVAM_POS_UP �̒�`�� VAM_POS_DOWN �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_ZRIGHT_UP �̒�`�� VAM_POS_ZLEFT_DOWN �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_ZRIGHT_DOWN �̒�`�� VAM_POS_ZLEFT_UP �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_FRONT_ZRIGHT �̒�`�� VAM_POS_BEHIND_ZLEFT �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_BEHIND_ZRIGHT �̒�`�� VAM_POS_FRONT_ZLEFT �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_FRONT_UP �̒�`�� VAM_POS_BEHIND_DOWN �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_FRONT_DOWN �̒�`�� VAM_POS_BEHIND_UP �ɃR�s�[
    memcpy(&VamSysCamWorker::cam_hosei_fov_[VAM_POS_BEHIND_UP][DIR26(-1,-1,-1)],
           &VamSysCamWorker::cam_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);


    //VP�����l��
    VamSysCamWorker::vp_hosei_fov_ =  (FovInfo (*)[3*3*3])(&(VamSysCamWorker::vp_hosei_fov_entity_[13][13])); //13 �� 3*3*3=27 �̐^�񒆂̗v�f�A_relation_up_vec[-13�`13][-13�`13]�ŃA�N�Z�X�����
    //                                 CAM             UP                   x_axis_fov       y_axis_fov       z_axis_fov
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26( 0,+1, 0)].set(VP_HOSEI_FOV_X , VP_HOSEI_FOV_Y , VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1,+1, 0)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1, 0, 0)].set(VP_HOSEI_FOV_Y , VP_HOSEI_FOV_X , VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(+1,-1, 0)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26( 0,-1, 0)].set(VP_HOSEI_FOV_X , VP_HOSEI_FOV_Y , VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1,-1, 0)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1, 0, 0)].set(VP_HOSEI_FOV_Y , VP_HOSEI_FOV_X , VP_HOSEI_FOV_Z);
    VamSysCamWorker::vp_hosei_fov_[VAM_POS_ZRIGHT][DIR26(-1,+1, 0)].set(VP_HOSEI_FOV_XY, VP_HOSEI_FOV_XY, VP_HOSEI_FOV_Z);
    // �^���͓����Ȃ̂ŁAVAM_POS_ZRIGHT �̒�`�� VAM_POS_ZLEFT �ɃR�s�[
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
    // �^���͓����Ȃ̂ŁAVAM_POS_FRONT �̒�`�� VAM_POS_BEHIND �ɃR�s�[
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
    // �^���͓����Ȃ̂ŁAVAM_POS_UP �̒�`�� VAM_POS_DOWN �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_ZRIGHT_UP �̒�`�� VAM_POS_ZLEFT_DOWN �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_ZRIGHT_DOWN �̒�`�� VAM_POS_ZLEFT_UP �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_FRONT_ZRIGHT �̒�`�� VAM_POS_BEHIND_ZLEFT �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_BEHIND_ZRIGHT �̒�`�� VAM_POS_FRONT_ZLEFT �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_FRONT_UP �̒�`�� VAM_POS_BEHIND_DOWN �ɃR�s�[
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
    //�^���͓����Ȃ̂ŁA VAM_POS_FRONT_DOWN �̒�`�� VAM_POS_BEHIND_UP �ɃR�s�[
    memcpy(&VamSysCamWorker::vp_hosei_fov_[VAM_POS_BEHIND_UP][DIR26(-1,-1,-1)],
           &VamSysCamWorker::vp_hosei_fov_[VAM_POS_FRONT_DOWN][DIR26(-1,-1,-1)],
           sizeof(FovInfo)*3*3*3);


    VamSysCamWorker::mv_ang_ = (2*PI) * (2.0/360.0); //2�x
    VamSysCamWorker::mv_ang_sinHalf_ = sin(VamSysCamWorker::mv_ang_/2);
    VamSysCamWorker::mv_ang_cosHalf_ = cos(VamSysCamWorker::mv_ang_/2);

    _TRACE_("VamSysCamWorker::initStatic() ������OK");
    return true;
}

VamSysCamWorker::VamSysCamWorker(const char* prm_name, Camera* prm_pCamera) : CameraWorker(prm_name, (DefaultCamera*)prm_pCamera) {
    _class_name = "VamSysCamWorker";

    static volatile bool is_init = VamSysCamWorker::initStatic(prm_pCamera); //�ÓI�����o������

    pMyShip_ = nullptr; //MyShipScene�ɐݒ肵�Ă��炤

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
        return; //MyShipScene�V�[���������Ȃ�J�������[�N�֎~
    }
    VirtualButton* pVbPlay = VB_PLAY;
    coord pMyShip_x = pMyShip_->_x;
    coord pMyShip_y = pMyShip_->_y;
    coord pMyShip_z = pMyShip_->_z;

    const bool isPressed_VB_UP    = pVbPlay->isPressed(VB_UP);
    const bool isPressed_VB_DOWN  = pVbPlay->isPressed(VB_DOWN);
    const bool isPressed_VB_LEFT  = pVbPlay->isPressed(VB_LEFT);
    const bool isPressed_VB_RIGHT = pVbPlay->isPressed(VB_RIGHT);

    const bool isPressed_VB_VIEW = pVbPlay->isPressed(VB_VIEW);
    const bool isDoublePushedDown_VB_VIEW = pVbPlay->isDoublePushedDown(VB_VIEW);
    const bool isPressed_VB_VIEW_UP    = pVbPlay->isPressed(VB_VIEW_UP)    ||  (isPressed_VB_VIEW && isPressed_VB_UP   );
    const bool isPressed_VB_VIEW_DOWN  = pVbPlay->isPressed(VB_VIEW_DOWN)  ||  (isPressed_VB_VIEW && isPressed_VB_DOWN );
    const bool isPressed_VB_VIEW_LEFT  = pVbPlay->isPressed(VB_VIEW_LEFT)  ||  (isPressed_VB_VIEW && isPressed_VB_LEFT );
    const bool isPressed_VB_VIEW_RIGHT = pVbPlay->isPressed(VB_VIEW_RIGHT) ||  (isPressed_VB_VIEW && isPressed_VB_RIGHT);

    if (returning_cam_pos_) {
        if (returning_cam_pos_frames_ == 0) {
            returning_cam_pos_ = false;
        } else {
            returning_cam_pos_frames_--;
        }
    }

    if (isDoublePushedDown_VB_VIEW) {
        //�v���Z�b�g�ʒu�Ɉړ�
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
            //�f�t�H���g��RIGHT
            mv_t_x_vCAM_ = 0;
            mv_t_y_vCAM_ = 0;
            mv_t_z_vCAM_ = -VamSysCamWorker::cam_radius_;
        }

        coord dcam = UTIL::getDistance(mv_t_x_vCAM_from, mv_t_y_vCAM_from, mv_t_z_vCAM_from,
                                       mv_t_x_vCAM_, mv_t_y_vCAM_, mv_t_z_vCAM_);
        returning_cam_pos_frames_ = (1.0 * dcam /VamSysCamWorker:: cam_radius_) * 40; //�^���΂ɂ�����2�{�t���[��
        if (returning_cam_pos_frames_ < 20) {
            returning_cam_pos_frames_ = 20;
        }
        returning_cam_pos_ = true;
    }

    //�����_���J���� �̕����x�N�g��(vx, vy, vz)
    const dxcoord f_mv_t_x_vCAM = C_DX(mv_t_x_vCAM_);
    const dxcoord f_mv_t_y_vCAM = C_DX(mv_t_y_vCAM_);
    const dxcoord f_mv_t_z_vCAM = C_DX(mv_t_z_vCAM_);
    const dxcoord f_mv_t_x_vUP = C_DX(mv_t_x_vUP_);
    const dxcoord f_mv_t_y_vUP = C_DX(mv_t_y_vUP_);
    const dxcoord f_mv_t_z_vUP = C_DX(mv_t_z_vUP_);
    //���_�𒆐S�ɃJ��������]�ړ�
    //�J�����𒆐S�Ɏ��_����]�ړ�
    //�J�������Ǝ��_�����s�ړ�
    //���ʂ̌v�Z

    //���[���h��]�������x�N�g���A(vX_axis, vY_axis, vZ_axis) ���v�Z begin =======>
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
        const D3DXVECTOR3 vecCamFromPoint(f_mv_t_x_vCAM, f_mv_t_y_vCAM, f_mv_t_z_vCAM ); //�ʒu
        const D3DXVECTOR3 vecCamLookatPoint( 0.0f, 0.0f, 0.0f ); //�����������
        const D3DXVECTOR3 vecCamUp(f_mv_t_x_vUP, f_mv_t_y_vUP, f_mv_t_z_vUP); //�����
        D3DXMATRIX matView;
        // VIEW�ϊ��s��쐬
        D3DXMatrixLookAtLH(
           &matView,             // pOut [in, out] ���Z���ʂł��� D3DXMATRIX �\���̂ւ̃|�C���^�B
           &vecCamFromPoint,     // pEye [in] ���_���`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B���̒l�́A���s�ړ��Ɏg�p�����B
           &vecCamLookatPoint,   // pAt  [in] �J�����̒����Ώۂ��`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
           &vecCamUp             // pUp  [in] �J�����g ���[���h�̏���A��ʂɂ� [0, 1, 0] ���`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
        );

        //���ʉ�]��(vx,vy)��VP�̃��[���h��Ԏ��ɕϊ�
        //VP��CAM�̃��[���h��ԕ����x�N�g����@���Ƃ��镽�ʏ�ɉ�]���x�N�g���͑��݂���
        D3DXMATRIX InvView;
        D3DXMatrixInverse(&InvView, nullptr, &matView);
        //(vx,vy,vz) * InvView
        // 11_, 12_, 13_, 14_
        // 21_, 22_, 23_, 24_
        // 31_, 32_, 33_, 34_
        // vx*11_ + vy*21_ + vz*31_ + 41_, vx*12_ + vy*22_ + vz*32_ + 42_, vx*13_ + vy*23_ + vz*33_ + 43_, vx*14_ + vy*24_ + vz*34_ + 44_
        //�����x�N�g��(0,0,0)->(vx,vy,vz) ���t�r���[�ϊ�
        //�ϊ�������x�N�g�� = (vx,vy,vz)�ϊ�����W - (0,0,0)�ϊ�����W
        double vX_axis = vx*InvView._11 + vy*InvView._21;
        double vY_axis = vx*InvView._12 + vy*InvView._22;
        double vZ_axis = vx*InvView._13 + vy*InvView._23;
        //���K��
        const double t = 1.0 / sqrt(vX_axis*vX_axis + vY_axis*vY_axis + vZ_axis*vZ_axis);
        vX_axis *= t;
        vY_axis *= t;
        vZ_axis *= t;

        //<==========  ���[���h��]�������x�N�g���A(vX_axis, vY_axis, vZ_axis) ���v�Z end

        //������W(x, y, z)�ɂ����āA��]�̎���(��, ��, ��)�ŁA�Ɖ񂷉�]
        //P = (0; x, y, z)
        //Q = (cos(��/2); �� sin(��/2), �� sin(��/2), �� sin(��/2))
        //R = (cos(��/2); -�� sin(��/2), -�� sin(��/2), -�� sin(��/2))
        //R P Q = (0; ����)
        //(��, ��, ��) = (vX_axis,vY_axis,vY_axis);
        //(x, y, z) �� CAM �� VP �� UP

        //��]���������p�x
        const double sinHalf = VamSysCamWorker::mv_ang_sinHalf_;
        const double cosHalf = VamSysCamWorker::mv_ang_cosHalf_;
        Quaternion<double> qu(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
        Quaternion<double> qu2 = qu;
        Quaternion<double> Q(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf);
        qu.mul(0, f_mv_t_x_vCAM, f_mv_t_y_vCAM, f_mv_t_z_vCAM); //R*P
        qu.mul(Q); //R*P*Q
        mv_t_x_vCAM_ = DX_C(qu.i);
        mv_t_y_vCAM_ = DX_C(qu.j);
        mv_t_z_vCAM_ = DX_C(qu.k);
        //UP���܂킷
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
        throwCriticalException("VamSysCamWorker::processBehavior() �z��O��Cam��Up�����̑g�ݍ��킹�ɑ����B�v�����B\n"<<
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

    //18������
    if (mv_t_x_vCAM_ == 0 && mv_t_y_vCAM_ == 0 && mv_t_z_vCAM_ == 0) {
        mv_t_z_vCAM_ = -C_PX(1); //0���Z�h�~
    }
    VamSysCamWorker::cnvVec2VamSgn(mv_t_x_vCAM_, mv_t_y_vCAM_, mv_t_z_vCAM_,
                                   cam_sgn_x_, cam_sgn_y_, cam_sgn_z_);
    pos_vam_camera_ = DIR26(cam_sgn_x_, cam_sgn_y_, cam_sgn_z_); //18������
    if ((pos_vam_camera_prev_ != pos_vam_camera_) || isDoublePushedDown_VB_VIEW) {
        is_just_changed_pos_vam_cam_ = true;
        //UP���X�V����
        if (mv_t_x_vUP_ == 0 && mv_t_y_vUP_ == 0 && mv_t_z_vUP_ == 0) {
            mv_t_y_vUP_ = C_PX(1); //0���Z�h�~
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
        //Z�v�f��0�ɂ��Ă�XY���ʏ��8�����̒���
        Direction8Util::cnvVec2Sgn(prm_vx, prm_vy,
                                   out_sgn_x, out_sgn_y);
        out_sgn_z = 0;
    } else if (prm_vam_cam_pos == VAM_POS_BEHIND || prm_vam_cam_pos == VAM_POS_FRONT) {
        //X�v�f��0�ɂ��Ă�YZ���ʏ��8�����̒��� (y��x, z��y)
        Direction8Util::cnvVec2Sgn(prm_vy, prm_vz,
                                   out_sgn_y, out_sgn_z);
        out_sgn_x = 0;
    } else if (prm_vam_cam_pos == VAM_POS_BEHIND || prm_vam_cam_pos == VAM_POS_FRONT) {
        //Y�v�f��0�ɂ��Ă�ZX���ʏ��8�����̒��� (z��x, x��y)
        Direction8Util::cnvVec2Sgn(prm_vz, prm_vx,
                                   out_sgn_z, out_sgn_x);
        out_sgn_y = 0;
    } else {
        //�J�����̈ʒu��
        //VAM_POS_ZRIGHT_UP, VAM_POS_ZLEFT_DOWN, VAM_POS_ZRIGHT_DOWN, VAM_POS_ZLEFT_UP
        //VAM_POS_FRONT_ZRIGHT, VAM_POS_BEHIND_ZLEFT, VAM_POS_BEHIND_ZRIGHT, VAM_POS_FRONT_ZLEFT
        //VAM_POS_FRONT_UP, VAM_POS_BEHIND_DOWN, VAM_POS_FRONT_DOWN, VAM_POS_BEHIND_UP
        //�̉��ꂩ
        float t_nvx, t_nvy, t_nvz; //���K�����ꂽ�����x�N�g��
        Direction26Util::cnvVec2Sgn(prm_vx, prm_vy, prm_vz,
                                    t_nvx, t_nvy, t_nvz,
                                    out_sgn_x, out_sgn_y, out_sgn_z);
        dir26 t_dir = DIR26(out_sgn_x, out_sgn_y, out_sgn_z);
        dir26* pa_dir8 = VamSysCamWorker::cam_to_8dir_[prm_vam_cam_pos];
        bool is_match = false;
        for (int i = 0; i < 8; i++) {
            is_match = (t_dir == pa_dir8[i]);
            if (is_match) {
                //�߂ł�����v������
                //out_sgn_x, out_sgn_y, out_sgn_z ��������̗p���Ă����܂�
                break;
            }
        }
        if (!is_match) {
            //�W�����̂ǂ�ɂ��}�b�`���Ȃ��ꍇ�A���߂̕����Ɏ��߂�B
            float max_dot = 0;
            dir26 nearest_dir = pa_dir8[0];
            for (int i = 0; i < 8; i++) {
                float d_vx,d_vy,d_vz;
                Direction26Util::cnvDirNo2Vec(pa_dir8[i], d_vx, d_vy, d_vz);
                float dot = t_nvx*d_vx + t_nvy*d_vy + t_nvz*d_vz;
                if (max_dot < dot) { //���ς��傫�����̂Ɋ񂹂�
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
    //���a�P�ɓ��ڂ��鐳���p�`�̂P�ӂ� 2��2 - 2
    //                  y
    //                  ^
    //                  |
    //              ____|____
    //            �^   ^|   /�_
    //          �^   v || 1/:  �_
    //        �^       || / :    �_
    //       |         v|/  :      | ��=3/8��
    //      -+----------+---+------+---------> x
    //       |         0|<->       |
    //        �_        | u      �^
    //          �_      |      �^
    //            �_�Q�Q|�Q�Q�^
    //                  |
    // u = cos(3/8��)  = 0.38268343236509
    // v = sin(3/8��)  = 0.92387953251129

    static const float u = 0.38268343236509f;
//    static const float v = 0.92387953251129f;
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
    //VAM�p
    if ((out_sgn_x != 0 && out_sgn_y != 0 && out_sgn_z != 0) || (out_sgn_x == 0 && out_sgn_y == 0 && out_sgn_z == 0)) {
        //�΂ߕ�������0,0,0�̏ꍇ�AVAM�����ɖ������z��
        //�ǂ��ɋ߂������ςŔ�r���Čv�Z
        dir26 td = DIR26(out_sgn_x, out_sgn_y, out_sgn_z);
        // nvx, nvy, nvz;
        float max_dot = 0;
        dir26 nearest_dir = 0;
        dir26* pa_dir6 = VamSysCamWorker::nbhd_dir_[td];
        for (int i = 0; i < 6; i++) {
            float d_vx,d_vy,d_vz;
            Direction26Util::cnvDirNo2Vec(pa_dir6[i], d_vx, d_vy, d_vz);
            float dot = nvx*d_vx + nvy*d_vy + nvz*d_vz;
            if (max_dot < dot) { //���ς��傫�����̂Ɋ񂹂�
                max_dot = dot;
                nearest_dir = pa_dir6[i];
            }
        }
        Direction26Util::cnvDirNo2Sgn(nearest_dir, out_sgn_x, out_sgn_y, out_sgn_z);
    }
}
