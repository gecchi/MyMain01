#include "VamSysCamWorker.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/camera/Camera.h"
#include "jp/gecchi/VioletVreath/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"
#include "jp/ggaf/dxcore/util/GgafDx8DirectionUtil.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

#include "jp/gecchi/VioletVreath/actor/camera/CameraUpVector.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


VamSysCamWorker::VamSysCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "VamSysCamWorker";
    pMyShip_ = nullptr; //MyShipScene�ɐݒ肵�Ă��炤

    //�����J�����ړ��͈͐���
    float revise = 0.7; //�΂߂��猩��̂ŕ␳�l���|����B1.0�̏ꍇ�͌��_����Ńh���s�V���B����͔��������J��Ԃ���
    lim_CAM_top_     = MyShip::lim_y_top_     - (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_CAM_bottom_  = MyShip::lim_y_bottom_  + (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_CAM_infront_ = MyShip::lim_x_infront_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_CAM_behaind_ = MyShip::lim_x_behaind_ + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_CAM_zleft_   = MyShip::lim_z_left_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_CAM_zright_  = MyShip::lim_z_right_  + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;

    lim_VP_top_     = MyShip::lim_y_top_     - (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_VP_bottom_  = MyShip::lim_y_bottom_  + (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_VP_infront_   = MyShip::lim_x_infront_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_VP_behaind_ = MyShip::lim_x_behaind_ + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_VP_zleft_   = MyShip::lim_z_left_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_VP_zright_  = MyShip::lim_z_right_  + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    pos_camera_prev_ = -1;
    pos_camera_ = VAM_POS_ZRIGHT;
    pos_camera_pressed_ = VAM_POS_ZRIGHT;
    cam_mv_frame_base_ = 20;
    cam_mv_frame_ = cam_mv_frame_base_;
    mv_t_x_CAM_prev_ = 0;
    mv_t_y_CAM_prev_ = 0;
    mv_t_z_CAM_prev_ = 0;


    pos_cam_around_ = D180ANG;
    cam_up_regular_ = true;

}
void VamSysCamWorker::initialize() {
    CameraWorker::initialize();

    //�����J����Z�ʒu
    dZ_camera_init_ = -DX_C(pCam_->getZOrigin());
    dZ_camera_init_sqrt2_ = dZ_camera_init_ * sqrt(2.0);

    //��ʔw��p�͈͍���
    //�w���Z���W��dZ_camera_init_/2
    correction_width_ = PX_C(30); //(PROPERTY::GAME_BUFFER_WIDTH*LEN_UNIT/2)/4;
    correction_height_ = PX_C(30); //(PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT/2)/4;
    pos_camera_ = VAM_POS_ZRIGHT;
    pos_camera_prev_ = -100;
    mv_t_x_CAM_prev_ = 0;
    mv_t_y_CAM_prev_ = 0;
    mv_t_z_CAM_prev_ = 0;
    pos_cam_around_ = D180ANG;
    cam_up_regular_ = true;

    _TRACE_("VamSysCamWorker::initialize() this="<<NODE_INFO);
    dump();
}
void VamSysCamWorker::onActive() {
    //CameraWorker::onActive();
    cam_mv_frame_ = cam_mv_frame_base_;
}

void VamSysCamWorker::processBehavior() {
    VirtualButton* pVbPlay = VB_PLAY;
    //�Q�[�����J�������[�N����
    if (pMyShip_ == nullptr) {
        return; //MyShipScene�V�[���������Ȃ�J�������[�N�֎~
    }
    Camera* pCam = pCam_;
    CameraViewPoint* pVP = (CameraViewPoint*)(pCam->getCameraViewPoint());

    //�J�����̈ړ��ڕW���W
    coord mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM;
    //�J�����̃r���[�|�C���g�̈ړ��ڕW���W
    coord mv_t_x_VP, mv_t_y_VP, mv_t_z_VP;

    //�J�����̖ڕW���W�A�r���[�|�C���g�̖ڕW���W��ݒ�
    static const coord Dx = PX_C(PROPERTY::GAME_BUFFER_WIDTH/4);
    //�J�������W
    mv_t_x_CAM = -Dx + (-pMyShip_->_x-200000)*2;
    //�� -200000 �̓J�����ړ��ʒu�A
    //   *2 �͎��@�����ɉ����������̃J�����̃p����B
    //   ���̕ӂ�̐��l�͔[�������܂Œ������J�����B
    //   TODO:�{���̓Q�[���̈�̑傫�����瓮�I�Ɍv�Z�ł���B���������������B
    if (-Dx > mv_t_x_CAM) {
        mv_t_x_CAM = -Dx;
    } else if (mv_t_x_CAM > Dx/2) {
        mv_t_x_CAM = Dx/2;
    }
    if (pVbPlay->isBeingPressed(VB_VIEW_UP)) {
        pos_cam_around_ = UTIL::simplifyAng(pos_cam_around_+D_ANG(2));
        cam_mv_frame_ = 3;
    } else if (pVbPlay->isBeingPressed(VB_VIEW_DOWN)) {
        pos_cam_around_ = UTIL::simplifyAng(pos_cam_around_-D_ANG(2));
        cam_mv_frame_ = 3;
    } else {
        cam_mv_frame_ = cam_mv_frame_base_;
    }
    mv_t_y_CAM = pMyShip_->_y + (ANG_SIN(pos_cam_around_) * dZ_camera_init_);
    mv_t_z_CAM = pMyShip_->_z + (ANG_COS(pos_cam_around_) * dZ_camera_init_);
    slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM, cam_mv_frame_);


    //VP���W
    mv_t_x_VP = Dx - (-pMyShip_->_x-200000)*2;
    if (Dx < mv_t_x_VP) {
        mv_t_x_VP = Dx;
    } else if ( mv_t_x_VP < -Dx/2) {
        mv_t_x_VP = -Dx/2;
    }
    mv_t_y_VP = pMyShip_->_y;
    mv_t_z_VP = pMyShip_->_z;
    slideMvVpTo(mv_t_x_VP, mv_t_y_VP, mv_t_z_VP, cam_mv_frame_);

    //�J������UP��ݒ�
    angle up_ang = UTIL::simplifyAng(pos_cam_around_ - D45ANG);
    coord up_y = pMyShip_->_y  + (ANG_SIN(up_ang) * dZ_camera_init_sqrt2_);
    coord up_z = pMyShip_->_z  + (ANG_COS(up_ang) * dZ_camera_init_sqrt2_);
    slideMvUpVecTo(0, up_y - mv_t_y_CAM, up_z - mv_t_z_CAM, cam_mv_frame_);


    //�J������pos_cam_around_����pos_camera_�֕ϊ�
    int x_cam_sgn, y_cam_sgn;
    GgafDx8DirectionUtil::cnvAng2Sgn(pos_cam_around_, x_cam_sgn, y_cam_sgn);
    pos_camera_ = DIR26(0, y_cam_sgn, x_cam_sgn);


    //�J�����ړ����W�𐧌��B
    if (mv_t_y_CAM > lim_CAM_top_) {
        mv_t_y_CAM = lim_CAM_top_;
    }
    if (mv_t_y_CAM < lim_CAM_bottom_ ) {
        mv_t_y_CAM = lim_CAM_bottom_;
    }
    if (mv_t_z_CAM > lim_CAM_zleft_) {
        mv_t_z_CAM = lim_CAM_zleft_;
    }
    if (mv_t_z_CAM < lim_CAM_zright_) {
        mv_t_z_CAM = lim_CAM_zright_;
    }

    //�r���[�|�C���g�̈ړ����W�𐧌�
    if (mv_t_y_VP > lim_VP_top_) {
        mv_t_y_VP = lim_VP_top_;
    }
    if (mv_t_y_VP < lim_VP_bottom_ ) {
        mv_t_y_VP = lim_VP_bottom_;
    }
    if (mv_t_z_VP > lim_VP_zleft_) {
        mv_t_z_VP = lim_VP_zleft_;
    }
    if (mv_t_z_VP < lim_VP_zright_) {
        mv_t_z_VP = lim_VP_zright_;
    }


    pos_camera_prev_ = pos_camera_;
    mv_t_x_CAM_prev_ = mv_t_x_CAM;
    mv_t_y_CAM_prev_ = mv_t_y_CAM;
    mv_t_z_CAM_prev_ = mv_t_z_CAM;
}
VamSysCamWorker::~VamSysCamWorker() {
}
