#include "MgrCameraWorker.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "jp/ggaf/dxcore/util/GgafDxDirectionUtil.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "MgrGod.h"
#include "scene/MgrSpacetime.h"
#include "actor/camera/MgrCameraUpVector.h"
#include "actor/camera/MgrCameraViewPoint.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

MgrCameraWorker::MgrCameraWorker(const char* prm_name) : GgafMainActor(prm_name, nullptr) {
    _class_name = "MgrCameraWorker";
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

    static volatile bool is_init = MgrCameraWorker::initStatic(); //�ÓI�����o������
    //���ӁFMgrCamera�͂܂���������Ă��Ȃ����߂�����P_CAM�͎g�p�s��
}

int MgrCameraWorker::relation_up_vec_[3*3*3][3*3*3];
int (*MgrCameraWorker::relation_up_by_vec_)[3*3*3];
bool MgrCameraWorker::initStatic() {
    for (int i = 0; i < 3*3*3; i++) {
        for (int j = 0; j < 3*3*3; j++) {
            MgrCameraWorker::relation_up_vec_[i][j] = GgafDxDirectionUtil::FACE_XXX;
        }
    }
    MgrCameraWorker::relation_up_by_vec_ =  (int (*)[3*3*3])(&(MgrCameraWorker::relation_up_vec_[13][13])); //13 �� 3*3*3=27 �̐^�񒆂̗v�f�A_relation_up_vec[-13�`13][-13�`13]�ŃA�N�Z�X�����
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1,-1,-1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1,-1, 0)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1,-1, 1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 0,-1)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 0, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 0, 1)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 1,-1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 1, 0)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN( 1, 1, 1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1,-1,-1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1,-1, 0)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1,-1, 1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 0,-1)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 0, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 0, 1)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 1,-1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 1, 0)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 0)][TN(-1, 1, 1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1,-1,-1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1,-1, 0)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1,-1, 1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 0,-1)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 0, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 0, 1)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 1,-1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 1, 0)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN(-1, 1, 1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1,-1,-1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1,-1, 0)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1,-1, 1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 0,-1)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 0, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 0, 1)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 1,-1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 1, 0)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 0)][TN( 1, 1, 1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1, 1,-1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1, 1, 0)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1, 1, 1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0, 1,-1)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0, 1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0, 1, 1)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1, 1,-1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1, 1, 0)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1, 1, 1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1,-1,-1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1,-1, 0)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN(-1,-1, 1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0,-1,-1)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0,-1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 0,-1, 1)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1,-1,-1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1,-1, 0)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 0)][TN( 1,-1, 1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1,-1,-1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1,-1, 0)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1,-1, 1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0,-1,-1)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0,-1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0,-1, 1)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1,-1,-1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1,-1, 0)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1,-1, 1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1, 1,-1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1, 1, 0)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN(-1, 1, 1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0, 1,-1)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0, 1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 0, 1, 1)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1, 1,-1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1, 1, 0)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 0)][TN( 1, 1, 1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1,-1, 1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 0, 1)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 1, 1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0,-1, 1)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 0, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 1, 1)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1,-1, 1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 0, 1)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 1, 1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1,-1,-1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 0,-1)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN(-1, 1,-1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0,-1,-1)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 0,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 0, 1,-1)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1,-1,-1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 0,-1)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0, 1)][TN( 1, 1,-1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1,-1,-1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 0,-1)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 1,-1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0,-1,-1)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 0,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 1,-1)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1,-1,-1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 0,-1)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 1,-1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1,-1, 1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 0, 1)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN(-1, 1, 1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0,-1, 1)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 0, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 0, 1, 1)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1,-1, 1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 0, 1)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 0,-1)][TN( 1, 1, 1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0, 1,-1)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0, 1, 0)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0, 1, 1)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 0,-1)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 0, 0)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 0, 1)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 1,-1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 1, 1, 1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1,-1,-1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1,-1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1,-1, 1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1, 0,-1)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1, 0, 0)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN(-1, 0, 1)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0,-1,-1)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0,-1, 0)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 0)][TN( 0,-1, 1)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1,-1,-1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1,-1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1,-1, 1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1, 0,-1)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1, 0, 0)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN(-1, 0, 1)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0,-1,-1)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0,-1, 0)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0,-1, 1)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0, 1,-1)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0, 1, 0)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 0, 1, 1)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 0,-1)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 0, 0)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 0, 1)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 1,-1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 0)][TN( 1, 1, 1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0,-1, 1)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 0, 1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 1, 1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1,-1, 0)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 0, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 1, 0)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1,-1, 1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 0, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 1, 1, 1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1,-1,-1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 0,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 1,-1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1,-1, 0)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 0, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN(-1, 1, 0)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0,-1,-1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 0,-1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0, 1)][TN( 0, 1,-1)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1,-1,-1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 0,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 1,-1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1,-1, 0)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 0, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN(-1, 1, 0)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0,-1,-1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 0,-1)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 1,-1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0,-1, 1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 0, 1)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 0, 1, 1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1,-1, 0)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 0, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 1, 0)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1,-1, 1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 0, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0,-1)][TN( 1, 1, 1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 0, 1)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 0, 1)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 0, 1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 1, 0)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 1, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 1, 0)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 1, 1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 1, 1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1,-1,-1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0,-1,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1,-1,-1)] = TN( 1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1,-1, 0)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0,-1, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1,-1, 0)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN(-1, 0,-1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 0, 0,-1)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1, 1)][TN( 1, 0,-1)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1,-1,-1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0,-1,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1,-1,-1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1,-1, 0)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0,-1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1,-1, 0)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 0,-1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 0,-1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 0,-1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 0, 1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 0, 1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 0, 1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 1, 0)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 1, 0)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN(-1, 1, 1)] = TN(-1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 0, 1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1,-1)][TN( 1, 1, 1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0, 1,-1)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0, 1, 0)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0, 1, 1)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 0,-1)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 0, 0)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 0, 1)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 1,-1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN(-1, 1, 1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1,-1,-1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1,-1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1,-1, 1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1, 0,-1)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1, 0, 0)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 1, 0, 1)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0,-1,-1)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0,-1, 0)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 0)][TN( 0,-1, 1)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1, 0,-1)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1, 0, 0)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1, 0, 1)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0,-1,-1)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0,-1, 0)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0,-1, 1)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1,-1,-1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1,-1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 1,-1, 1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 1,-1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 1, 0)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 1, 1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0, 1,-1)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0, 1, 0)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN( 0, 1, 1)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 0,-1)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 0, 0)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 0)][TN(-1, 0, 1)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0,-1, 1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 0, 1)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 1, 1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1,-1, 0)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 0, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 1, 0)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1,-1, 1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 0, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN(-1, 1, 1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1,-1,-1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 0,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 1,-1)] = TN(-1, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1,-1, 0)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 0, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 1, 1, 0)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0,-1,-1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 0,-1)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 0, 1)][TN( 0, 1,-1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1,-1, 0)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 0, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 1, 0)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0,-1,-1)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 0,-1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 1,-1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1,-1,-1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 0,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 1, 1,-1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1,-1, 1)] = TN( 1,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 0, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 1, 1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0,-1, 1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 0, 1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN( 0, 1, 1)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1,-1, 0)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 0, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 0,-1)][TN(-1, 1, 0)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 0, 1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 0, 1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 0, 1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1,-1, 0)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0,-1, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1,-1, 0)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1,-1, 1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0,-1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1,-1, 1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 1,-1)] = TN(-1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 1,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 1,-1)] = TN( 1,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 1, 0)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 1, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 1, 0)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN(-1, 0,-1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 0, 0,-1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0,-1, 1)][TN( 1, 0,-1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 1, 0)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 1, 0)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 0,-1)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 0,-1)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 0,-1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 1,-1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 1,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 1,-1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1,-1, 1)] = TN(-1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0,-1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1,-1, 1)] = TN( 1, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1, 0, 1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0, 0, 1)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1, 0, 1)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN(-1,-1, 0)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 0,-1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 0, 1,-1)][TN( 1,-1, 0)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 0, 0, 1)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 0, 1, 0)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 0, 1, 1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 0, 0)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 0, 1)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 1, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 1, 1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 0,-1, 0)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN( 0,-1,-1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN(-1, 0, 0)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN(-1, 0,-1)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN(-1,-1, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1, 1)][TN(-1,-1,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 0, 0,-1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 0,-1,-1)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN(-1, 0, 0)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN(-1, 0,-1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN(-1,-1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN(-1,-1,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 0, 0, 1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 0, 1, 0)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 0, 0)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 0, 1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1,-1)][TN( 1, 1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 0,-1)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 1, 0)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 1,-1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 1, 0,-1)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 1, 1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 1, 1,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0, 0, 1)] = TN( 1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0,-1, 0)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN( 0,-1, 1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN(-1, 0, 0)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN(-1,-1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1, 1,-1)][TN(-1,-1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 0, 1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0,-1, 0)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0,-1, 1)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN(-1, 0, 0)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN(-1, 0, 1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN(-1,-1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 0,-1)] = TN(-1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 1, 0)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 0, 1,-1)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 0, 0)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 0,-1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 1, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1,-1, 1)][TN( 1, 1,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 0, 1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0,-1, 0)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0,-1, 1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 1, 0, 0)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 1, 0, 1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 1,-1, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 1,-1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 0,-1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 1, 0)] = TN( 1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN( 0, 1,-1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 0, 0)] = TN( 0,-1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 0,-1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 1, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1, 1)][TN(-1, 1,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 0,-1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 1, 0)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 1,-1)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 0, 0)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 0,-1)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN(-1, 1,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0, 0, 1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0,-1, 0)] = TN(-1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 0,-1, 1)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 1, 0, 0)] = TN( 0, 1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 1, 0, 1)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 1,-1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1,-1)][TN( 1,-1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 0,-1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0,-1, 0)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0,-1,-1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 1, 0, 0)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 1, 0,-1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 1,-1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 1,-1,-1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 0, 1)] = TN( 1,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 1, 0)] = TN( 1, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN( 0, 1, 1)] = TN( 1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 0, 0)] = TN( 0,-1,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 0, 1)] = TN( 0,-1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 1, 0)] = TN( 0, 0,-1);
    MgrCameraWorker::relation_up_by_vec_[TN( 1,-1,-1)][TN(-1, 1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 0, 1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 1, 0)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 1, 1)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 0, 0)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 0, 1)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 1, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN(-1, 1, 1)] = TN( 0, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0, 0,-1)] = TN(-1, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0,-1, 0)] = TN(-1, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 0,-1,-1)] = TN(-1, 0, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 1, 0, 0)] = TN( 0, 1, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 1, 0,-1)] = TN( 0, 1, 0);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 1,-1, 0)] = TN( 0, 0, 1);
    MgrCameraWorker::relation_up_by_vec_[TN(-1, 1, 1)][TN( 1,-1,-1)] = TN( 0, 0, 0);
    return true;
}

void MgrCameraWorker::initialize() {
    pCam_ = P_GOD->getSpacetime()->getCamera();
    pVp_ = (MgrCameraViewPoint*)(pCam_->getCameraViewPoint());
    pUp_ = (MgrCameraUpVector*)(pCam_->getCameraUpVector());
    t_x_VP_ = pVp_->_x;
    t_y_VP_ = pVp_->_y;
    t_z_VP_ = pVp_->_z;
    t_x_CAM_ = pCam_->_x;
    t_y_CAM_ = pCam_->_y;
    t_z_CAM_ = pCam_->_z;
    t_cam_up_face_ = pUp_->up_face_;
}
void MgrCameraWorker::onActive() {
    //���݂̃^�[�Q�b�g���ă^�[�Q�b�g
    slideMvCamTo(t_x_CAM_, t_y_CAM_, t_z_CAM_, 60);
    slideMvVpTo(t_x_VP_, t_y_VP_, t_z_VP_, 60);
    slideMvUpTo(t_cam_up_face_, 30);
}


void MgrCameraWorker::processBehavior() {
    //UP�x�N�g�����J���������_�x�N�g���ɂ���Ď����ݒ�
    vcv_face_ = pCam_->getVpFaceNo();
    if (vcv_face_ != vcv_face_prev_) { //�J���������_�x�N�g���̖ʔԍ����ω�������UP���P��l��
        frame up_frames = 30;
        int up_hx1, up_hy1, up_hz1;
        GgafDxDirectionUtil::cnvFaceNo2Sgn(pUp_->up_face_, up_hx1, up_hy1, up_hz1);
        int up_face_next = MgrCameraWorker::relation_up_by_vec_[pUp_->up_face_][vcv_face_];
        if (up_face_next == GgafDxDirectionUtil::FACE_XXX) {
            //FACE_XXX�́AUP�͓����K�v�Ȃ�
        } else {
            if (up_face_next == GgafDxDirectionUtil::FACE_ZZZ) {
                //�J���������_�x�N�g���̖ʔԍ����AUP�̖ʔԍ��Ɠ������^���ɂȂ����B
                //���̏ꍇ�́A�J���������_�x�N�g���̈�O�̖ʔԍ����̗p����UP�̏ꏊ�����߂�B
                int up_face_next_other = MgrCameraWorker::relation_up_by_vec_[pUp_->up_face_][vcv_face_prev_];
                if (up_face_next_other == GgafDxDirectionUtil::FACE_XXX) {
                    //FACE_XXX�́AUP�͓����K�v�Ȃ�
                } else {
                    if (up_face_next_other == GgafDxDirectionUtil::FACE_ZZZ) {
                        //�J���������_�x�N�g���̖ʔԍ����^���ֈ�C�ɓ��������ƂɂȂ�B
                        //����グ�BUP�͂ǂ��ɍs���΂悢���s��B����������UP�͂��̂܂܁B
                    } else {
                        slideMvUpTo(up_face_next_other, up_frames);
                    }
                }
            } else {
                //�J���������_�x�N�g���ʔԍ����AUP�x�N�g���ʔԍ��ɗאڂ����̂ŁA
                //���̗אږʂ̔��Α��̗אږʂ̕��p��UP�x�N�g���𓦂��B
                //�����́A�J���������_�x�N�g���ʔԍ����AUP�x�N�g���ʔԍ����璼�p�ȏ�̊p�x�ŉ�������̂ŁA
                //UP�x�N�g�����ߊ�点��B
                slideMvUpTo(up_face_next, up_frames);
            }
        }

    }
    vcv_face_prev_ = vcv_face_;
}

void MgrCameraWorker::slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvCamTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}


void MgrCameraWorker::slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t,
                                float prm_x_p1, float prm_y_p1, float prm_z_p1) {
     slideMvCamTo(pTarget->_x, pTarget->_y, pTarget->_z, t, prm_x_p1, prm_y_p1, prm_z_p1);

}
void MgrCameraWorker::slideMvVpTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvVpTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}
void MgrCameraWorker::slideMvCamTo(coord tx, coord ty, coord tz, frame t) {
    t_x_CAM_ = tx;
    t_y_CAM_ = ty;
    t_z_CAM_ = tz;
    pCam_->slideMvTo(tx, ty, tz, t);
}
void MgrCameraWorker::slideMvCamTo(coord tx, coord ty, coord tz, frame t,
            float prm_x_p1, float prm_y_p1, float prm_z_p1) {
    t_x_CAM_ = tx;
    t_y_CAM_ = ty;
    t_z_CAM_ = tz;
    pCam_->slideMvTo(tx, ty, tz, t, prm_x_p1, prm_y_p1, prm_z_p1);
}


void MgrCameraWorker::slideMvVpTo(coord tx, coord ty, coord tz, frame t) {
    t_x_VP_ = tx;
    t_y_VP_ = ty;
    t_z_VP_ = tz;
    pVp_->slideMvTo(tx, ty, tz, t);
}

void MgrCameraWorker::slideMvUpTo(face26 prm_up_face_no, frame t) {
    t_cam_up_face_ = prm_up_face_no;
    pUp_->moveTo(prm_up_face_no, t);
}

void MgrCameraWorker::stopMvCam() {
    pCam_->pAxsMver_->stopMv();
}
void MgrCameraWorker::stopMvVp() {
    pVp_->pAxsMver_->stopMv();
}
MgrCameraWorker::~MgrCameraWorker() {

}
