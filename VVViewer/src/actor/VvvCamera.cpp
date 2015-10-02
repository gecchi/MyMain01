#include "VvvCamera.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraViewPoint.h"
#include "actor/VvvCameraViewPoint.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"

#include "VvvCameraUpVector.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvCamera::VvvCamera(const char* prm_name) :
        DefaultCamera(prm_name, PI * 90.0 / 180.0) {
    _class_name = "VvvCamera";
    pAxsMver_ = NEW GgafDxAxesMover(this);

    vcv_dir_ = 0;
    vcv_dir_prev_ = vcv_dir_;


    for (int i = 0; i < 3*3*3; i++) {
        for (int j = 0; j < 3*3*3; j++) {
            relation_up_vec_[i][j] = DIR26_NULL;
        }
    }
    relation_up_by_vec_ =  (int (*)[3*3*3])(&(relation_up_vec_[13][13])); //13 �� 3*3*3=27 �̐^�񒆂̗v�f�A_relation_up_vec[-13�`13][-13�`13]�ŃA�N�Z�X�����

    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1,-1,-1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1,-1, 0)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1,-1, 1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 0,-1)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 0, 1)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 1,-1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 1, 0)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 1, 1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1,-1,-1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1,-1, 0)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1,-1, 1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 0,-1)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 0, 1)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 1,-1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 1, 0)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 1, 1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1,-1,-1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1,-1, 0)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1,-1, 1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 0,-1)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 0, 1)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 1,-1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 1, 0)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 1, 1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1,-1,-1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1,-1, 0)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1,-1, 1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 0,-1)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 0, 1)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 1,-1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 1, 0)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 1, 1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1, 1,-1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1, 1, 0)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1, 1, 1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0, 1,-1)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0, 1, 1)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1, 1,-1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1, 1, 0)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1, 1, 1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1,-1,-1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1,-1, 0)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1,-1, 1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0,-1,-1)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0,-1, 1)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1,-1,-1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1,-1, 0)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1,-1, 1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1,-1,-1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1,-1, 0)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1,-1, 1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0,-1,-1)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0,-1, 1)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1,-1,-1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1,-1, 0)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1,-1, 1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1, 1,-1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1, 1, 0)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1, 1, 1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0, 1,-1)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0, 1, 1)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1, 1,-1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1, 1, 0)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1, 1, 1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1,-1, 1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 0, 1)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 1, 1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0,-1, 1)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 0, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 1, 1)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1,-1, 1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 0, 1)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 1, 1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1,-1,-1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 0,-1)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 1,-1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0,-1,-1)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 0,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 1,-1)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1,-1,-1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 0,-1)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 1,-1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1,-1,-1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 0,-1)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 1,-1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0,-1,-1)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 0,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 1,-1)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1,-1,-1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 0,-1)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 1,-1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1,-1, 1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 0, 1)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 1, 1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0,-1, 1)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 0, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 1, 1)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1,-1, 1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 0, 1)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 1, 1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0, 1,-1)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0, 1, 1)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 0,-1)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 0, 1)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 1,-1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 1, 1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1,-1,-1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1,-1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1,-1, 1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1, 0,-1)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1, 0, 1)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0,-1,-1)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0,-1, 1)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1,-1,-1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1,-1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1,-1, 1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1, 0,-1)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1, 0, 1)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0,-1,-1)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0,-1, 1)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0, 1,-1)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0, 1, 1)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 0,-1)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 0, 1)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 1,-1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 1, 1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0,-1, 1)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 0, 1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 1, 1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1,-1, 0)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 1, 0)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1,-1, 1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 0, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 1, 1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1,-1,-1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 0,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 1,-1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1,-1, 0)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 1, 0)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0,-1,-1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 0,-1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 1,-1)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1,-1,-1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 0,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 1,-1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1,-1, 0)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 1, 0)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0,-1,-1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 0,-1)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 1,-1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0,-1, 1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 0, 1)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 1, 1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1,-1, 0)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 0, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 1, 0)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1,-1, 1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 0, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 1, 1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 0, 1)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 0, 1)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 0, 1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 1, 0)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 1, 0)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 1, 1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 1, 1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1,-1,-1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0,-1,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1,-1,-1)] = DIR26( 1, 1, 1);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1,-1, 0)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1,-1, 0)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 0,-1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 0,-1)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 0,-1)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1,-1,-1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0,-1,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1,-1,-1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1,-1, 0)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0,-1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1,-1, 0)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 0,-1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 0,-1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 0,-1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 0, 1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 0, 1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 0, 1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 1, 0)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 1, 0)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 1, 1)] = DIR26(-1,-1,-1);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 1, 1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0, 1,-1)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0, 1, 1)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 0,-1)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 0, 1)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 1,-1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 1, 1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1,-1,-1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1,-1, 1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1, 0,-1)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1, 0, 1)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0,-1,-1)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0,-1, 1)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1, 0,-1)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1, 0, 1)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0,-1,-1)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0,-1, 1)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1,-1,-1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1,-1, 1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 1,-1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 1, 1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0, 1,-1)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0, 1, 1)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 0,-1)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 0, 1)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0,-1, 1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 0, 1)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 1, 1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1,-1, 0)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 1, 0)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1,-1, 1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 0, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 1, 1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1,-1,-1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 0,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 1,-1)] = DIR26(-1, 1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1,-1, 0)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 1, 0)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0,-1,-1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 0,-1)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 1,-1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1,-1, 0)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 0, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 1, 0)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0,-1,-1)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 0,-1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 1,-1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1,-1,-1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 0,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 1,-1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1,-1, 1)] = DIR26( 1,-1,-1);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 0, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 1, 1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0,-1, 1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 0, 1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 1, 1)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1,-1, 0)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 1, 0)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 0, 1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 0, 1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 0, 1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1,-1, 0)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1,-1, 0)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1,-1, 1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0,-1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1,-1, 1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 1,-1)] = DIR26(-1,-1, 1);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 1,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 1,-1)] = DIR26( 1,-1, 1);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 1, 0)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 1, 0)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 0,-1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 0,-1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 0,-1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 1, 0)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 1, 0)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 0,-1)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 0,-1)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 0,-1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 1,-1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 1,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 1,-1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1,-1, 1)] = DIR26(-1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0,-1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1,-1, 1)] = DIR26( 1, 1,-1);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 0, 1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 0, 1)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 0, 1)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1,-1, 0)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0,-1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1,-1, 0)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0, 0, 1)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0, 1, 1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 0, 1)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0,-1,-1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1, 0,-1)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1,-1, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1,-1,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0, 0,-1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0,-1,-1)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1, 0, 0)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1, 0,-1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1,-1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1,-1,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0, 0, 1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0, 1, 0)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 0, 0)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 0, 1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 0,-1)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 1, 0)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 1,-1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 1, 0,-1)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 1, 1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 1, 1,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 0, 1)] = DIR26( 1, 1, 0);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0,-1, 0)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0,-1, 1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26(-1,-1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26(-1,-1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 0, 1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0,-1, 1)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26(-1, 0, 1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26(-1,-1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 0,-1)] = DIR26(-1,-1, 0);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 1,-1)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 0,-1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 1,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 0, 1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0,-1, 1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1, 0, 1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1,-1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 0,-1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 1);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 1,-1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 1);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 0,-1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 1,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 0,-1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 1, 0)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 1,-1)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 0,-1)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 1,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 0, 1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0,-1, 0)] = DIR26(-1, 0,-1);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0,-1, 1)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1, 0, 0)] = DIR26( 0, 1,-1);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1, 0, 1)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1,-1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1,-1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 0,-1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0,-1, 0)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0,-1,-1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1, 0, 0)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1, 0,-1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1,-1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1,-1,-1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 0, 1)] = DIR26( 1,-1, 0);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 1, 0)] = DIR26( 1, 0,-1);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 1, 1)] = DIR26( 1, 0, 0);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 0, 0)] = DIR26( 0,-1,-1);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 0, 1)] = DIR26( 0,-1, 0);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 1, 0)] = DIR26( 0, 0,-1);
    relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 0, 1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 1, 1)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 0, 1)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 1, 1)] = DIR26( 0, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 0,-1)] = DIR26(-1, 1, 0);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 1);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0,-1,-1)] = DIR26(-1, 0, 0);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 1);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1, 0,-1)] = DIR26( 0, 1, 0);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 1);
    relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1,-1,-1)] = DIR26( 0, 0, 0);

    auto_up_wait_frames = 0;
}

GgafDxCameraViewPoint* VvvCamera::createCameraViewPoint() {
    VvvCameraViewPoint* pVP = NEW VvvCameraViewPoint("VvvCameraViewPoint");
    return (GgafDxCameraViewPoint*)pVP;
}

GgafDxCameraUpVector* VvvCamera::createCameraUpVector() {
    VvvCameraUpVector* pUp = NEW VvvCameraUpVector("VvvCameraUpVector");
    return (GgafDxCameraUpVector*)pUp;
}

void VvvCamera::initialize() {
    DefaultCamera::initialize();
}

void VvvCamera::processBehavior() {
    VvvCameraViewPoint* pVP = (VvvCameraViewPoint*)getCameraViewPoint();
    VvvCameraUpVector* pUpV = (VvvCameraUpVector*)getCameraUpVector();

    pAxsMver_->behave();
    getKuroko()->behave();

    vcv_dir_ = getCamToVpFaceNo();

    if (auto_up_wait_frames == 0) {
        if (vcv_dir_ != vcv_dir_prev_) { //�J���������_�x�N�g���̖ʔԍ����ω�������UP���P��l��

            int up_dir_wk = pUpV->up_dir_; //�f�o�b�O�p

            int up_hx1, up_hy1, up_hz1;
            GgafDx26DirectionUtil::cnvDirNo2Sgn(pUpV->up_dir_, up_hx1, up_hy1, up_hz1);

            int up_dir_next = relation_up_by_vec_[pUpV->up_dir_][vcv_dir_];
            if (up_dir_next == DIR26_NULL) {
                //FACE_XXX�́AUP�͓����K�v�Ȃ�
            } else {
                if (up_dir_next == DIR26( 0, 0, 0)) {
                    //�J���������_�x�N�g���̖ʔԍ����AUP�̖ʔԍ��Ɠ������^���ɂȂ����B
                    //���̏ꍇ�́A�J���������_�x�N�g���̈�O�̖ʔԍ����̗p����UP�̏ꏊ�����߂�B
                    int up_dir_next_other = relation_up_by_vec_[pUpV->up_dir_][vcv_dir_prev_];
                    if (up_dir_next_other == DIR26_NULL) {
                        //FACE_XXX�́AUP�͓����K�v�Ȃ�
                    } else {
                        if (up_dir_next_other == DIR26( 0, 0, 0)) {
                            //�J���������_�x�N�g���̖ʔԍ����^���ֈ�C�ɓ��������ƂɂȂ�B
                            //����グ�BUP�͂ǂ��ɍs���΂悢���s��B����������UP�͂��̂܂܁B
                        } else {
                            pUpV->setFaceNo(up_dir_next_other);
                        }
                    }
                } else {
                    //�J���������_�x�N�g���ʔԍ����AUP�x�N�g���ʔԍ��ɗאڂ����̂ŁA
                    //���̗אږʂ̔��Α��̗אږʂ̕��p��UP�x�N�g���𓦂��B
                    //�����́A�J���������_�x�N�g���ʔԍ����AUP�x�N�g���ʔԍ����璼�p�ȏ�̊p�x�ŉ�������̂ŁA
                    //UP�x�N�g�����ߊ�点��B
                    pUpV->setFaceNo(up_dir_next);
                }
            }


            int eye_hx1, eye_hy1, eye_hz1;
            GgafDx26DirectionUtil::cnvDirNo2Sgn(vcv_dir_prev_, eye_hx1, eye_hy1, eye_hz1);
            int eye_hx2, eye_hy2, eye_hz2;
            GgafDx26DirectionUtil::cnvDirNo2Sgn(vcv_dir_, eye_hx2, eye_hy2, eye_hz2);
            int up_hx_1, up_hy_1, up_hz_1;
            GgafDx26DirectionUtil::cnvDirNo2Sgn(up_dir_wk, up_hx_1, up_hy_1, up_hz_1);
            int up_hx2, up_hy2, up_hz2;
            GgafDx26DirectionUtil::cnvDirNo2Sgn(pUpV->up_dir_, up_hx2, up_hy2, up_hz2);
            _TRACE_("EYE["<<vcv_dir_prev_<<"]("<<eye_hx1<<","<< eye_hy1<<","<<eye_hz1<<") �� ["<<vcv_dir_<<"]("<<eye_hx2<<","<< eye_hy2<<","<<eye_hz2<<")");
            _TRACE_(" �� UP["<<up_dir_wk<<"]("<<up_hx_1<<","<< up_hy_1<<","<<up_hz_1<<") �� ["<<pUpV->up_dir_<<"]("<<up_hx2<<","<< up_hy2<<","<<up_hz2<<")");
        }
    } else {
        auto_up_wait_frames--;
    }

    DefaultCamera::processBehavior();

    vcv_dir_prev_ = vcv_dir_;
}

void VvvCamera::slideMvTo(coord tx, coord ty, coord tz, frame t) {
    //_TRACE_(" VvvCamera::slideMvTo("<<tx<<","<<ty<<","<<tz<<",t="<<t<<")");
    pAxsMver_->asst()->slideVxyzMvByDtTo(
                              tx, ty, tz, t,
                              0.3, 0.4, 0, true);
}
void VvvCamera::slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}
int VvvCamera::getCamToVpFaceNo() {
    float vcv_x, vcv_y, vcv_z;
    VvvCameraViewPoint* pVP = (VvvCameraViewPoint*)getCameraViewPoint();
    UTIL::getNormalizedVector (
            pVP->_x - _x,
            pVP->_y - _y,
            pVP->_z - _z,
            vcv_x, vcv_y, vcv_z  );
    return GgafDx26DirectionUtil::cnvVec2DirNo(vcv_x, vcv_y, vcv_z);
}

VvvCamera::~VvvCamera() {
    GGAF_DELETE(pAxsMver_);
}
