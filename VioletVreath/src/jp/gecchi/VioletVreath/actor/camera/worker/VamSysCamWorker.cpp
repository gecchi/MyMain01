#include "VamSysCamWorker.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/camera/Camera.h"
#include "jp/gecchi/VioletVreath/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"
#include "jp/ggaf/lib/util/Direction26Util.h"
#include "jp/ggaf/lib/util/Direction8Util.h"

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

VamSysCamWorker::VamSysCamWorker(const char* prm_name, Camera* prm_pCamera) : CameraWorker(prm_name, (DefaultCamera*)prm_pCamera) {
    _class_name = "VamSysCamWorker";
    pMyShip_ = nullptr; //MyShipScene�ɐݒ肵�Ă��炤

    pos_camera_ = VAM_POS_ZRIGHT;
    pos_camera_prev_ = VAM_POS_NON;
    cam_mv_frame_base_ = 16;
    cam_mv_frame_ = cam_mv_frame_base_;
    ang_cam_around_base_ = D180ANG;
    ang_cam_around_ = ang_cam_around_base_;
    returning_cam_pos_ = false;
    returning_cam_pos_frames_ = 0;
    is_just_changed_pos_cam_ = false;

    //�J�����̈ړ��͈͋����Z�p
    double H_FOVX = prm_pCamera->_rad_half_fovX;
    double DZ = ABS(prm_pCamera->_cameraZ_org);
    double X_BOUND = prm_pCamera->_zf;
    //����E���E���ƁAX�����A�Q�[���̈�E�[�Ō����ꍇ��CAM��VP�̃X���C�h�Dx�i���ߕ��̓R�[�h�����̃����j
    double DX = (sqrt((cos(H_FOVX)*cos(H_FOVX)-8*sin(H_FOVX)*sin(H_FOVX))*DZ*DZ+12*cos(H_FOVX)*sin(H_FOVX)*X_BOUND*DZ+4*sin(H_FOVX)*sin(H_FOVX)*X_BOUND*X_BOUND)-cos(H_FOVX)*DZ-2*sin(H_FOVX)*X_BOUND)/(4*sin(H_FOVX));
    //���썶���E���ƁAX���̌�_P(X_P, 0, 0) ���ߕ��̓R�[�h�����̃����j
    double X_P = -((DZ*DZ+2*DX*DX)*sin(-H_FOVX)+DX*DZ*cos(-H_FOVX))/(2*DX*sin(-H_FOVX)-DZ*cos(-H_FOVX));
    double X_BEHAIND = C_DX(MyShip::lim_x_behaind_);
    double DX2 = (sqrt((cos(-H_FOVX)*cos(-H_FOVX)-8*sin(-H_FOVX)*sin(-H_FOVX))*DZ*DZ+12*cos(-H_FOVX)*sin(-H_FOVX)*X_BEHAIND*DZ+4*sin(-H_FOVX)*sin(-H_FOVX)*X_BEHAIND*X_BEHAIND)-cos(-H_FOVX)*DZ-2*sin(-H_FOVX)*X_BEHAIND)/(4*sin(-H_FOVX));

    DZC_ = DX_C(DZ);
    DXC_ = DX_C(DX);
    DX2_C_ = DX_C(DX2);
    X_P_C_ = DX_C(X_P);


    pSe_ = NEW GgafDxSeTransmitter();
    pSe_->set(SE_RETURNNING_CAM_POS, "WAVE_MY_RETURNNING_CAM_POS" ,0);
}

void VamSysCamWorker::initialize() {
    CameraWorker::initialize();
    pos_camera_ = VAM_POS_ZRIGHT;
    pos_camera_prev_ = VAM_POS_NON;
    ang_cam_around_ = ang_cam_around_base_;
    returning_cam_pos_frames_ = 0;

    _TRACE_(FUNC_NAME<<" this="<<NODE_INFO);
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
    coord pMyShip_x = pMyShip_->_x;
    coord pMyShip_y = pMyShip_->_y;
    coord pMyShip_z = pMyShip_->_z;

    //�J�����̈ړ��ڕW���W�ݒ�( mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM)
    coord mv_t_x_CAM = -DXC_ + ((X_P_C_*0.85) - pMyShip_x)*2;
                             //�� X_P_C_ �̓J�����ړ��J�n�ʒu�A*0.85 �͎��@�L�����̉������l��
                             //   �Ō�� *2 �͎��@�����ɉ����������̃J�����̃p���̑�����B
    if (-DXC_ > mv_t_x_CAM) {
        mv_t_x_CAM = -DXC_;
    } else if (mv_t_x_CAM > -DX2_C_) {
        mv_t_x_CAM = -DX2_C_;
    }

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
            angle d = UTIL::getAngDiff(ang_cam_around_, ang_cam_around_base_, TURN_CLOSE_TO);
            ang_cam_around_ = ang_cam_around_base_;
            cam_mv_frame_ = (frame)(ANG_D(ABS(d))/3);
            returning_cam_pos_frames_ = cam_mv_frame_;
            returning_cam_pos_ = true;
        }
    }

    if (!returning_cam_pos_) {
        bool isPressed_VB_VIEW_UP   = pVbPlay->isPressed(VB_VIEW_UP);
        bool isPressed_VB_VIEW_DOWN = pVbPlay->isPressed(VB_VIEW_DOWN);
        if (isPressed_VB_VIEW_UP && !isPressed_VB_VIEW_DOWN) {
            ang_cam_around_ = UTIL::simplifyAng(ang_cam_around_-D_ANG(2));
            cam_mv_frame_ = 2;
        } else if (isPressed_VB_VIEW_DOWN && !isPressed_VB_VIEW_UP) {
            ang_cam_around_ = UTIL::simplifyAng(ang_cam_around_+D_ANG(2));
            cam_mv_frame_ = 2;
        } else {
            cam_mv_frame_ = cam_mv_frame_base_;
        }
    }
    coord mv_t_y_CAM = pMyShip_y + (ANG_SIN(ang_cam_around_) * DZC_);
    coord mv_t_z_CAM = pMyShip_z + (ANG_COS(ang_cam_around_) * DZC_);

    //�J�����̃r���[�|�C���g�̈ړ��ڕW���W�ݒ�(mv_t_x_VP, mv_t_y_VP, mv_t_z_VP, cam_mv_frame_)
    coord mv_t_x_VP = DXC_ - ((X_P_C_*0.85) - pMyShip_x)*2;
    if (DXC_ < mv_t_x_VP) {
        mv_t_x_VP = DXC_;
    } else if ( mv_t_x_VP < DX2_C_) {
        mv_t_x_VP = DX2_C_;
    }

    coord mv_t_y_VP = pMyShip_y;
    coord mv_t_z_VP = pMyShip_z;


    //�J�����AVP�̖ڕW���W���ς������X���C�h�ړ��w��
/////////////4TEST
//    if (GgafDxInput::isPressedKey(DIK_H)) {
/////////////////
        if (t_x_CAM_ != mv_t_x_CAM || t_y_CAM_ != mv_t_y_CAM || t_z_CAM_ != mv_t_z_CAM ||
            t_x_VP_  != mv_t_x_VP  || t_y_VP_  != mv_t_y_VP  || t_z_VP_ != mv_t_z_VP
        ) {
            slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM, cam_mv_frame_);
            slideMvVpTo(mv_t_x_VP, mv_t_y_VP, mv_t_z_VP, cam_mv_frame_);
            //�J������UP��ݒ�
            angle up_ang = UTIL::simplifyAng(ang_cam_around_ - D45ANG);
            static const coord cDz_sqrt2 = DZC_ * sqrt(2.0);  //�v�Z�p�萔�A�J������45�x�΂ߏ�̏���Z������
            coord up_y = pMyShip_y  + (ANG_SIN(up_ang) * cDz_sqrt2);
            coord up_z = pMyShip_z  + (ANG_COS(up_ang) * cDz_sqrt2);
            slideMvUpVecTo(0, up_y - mv_t_y_CAM, up_z - mv_t_z_CAM, cam_mv_frame_);
        }
///////////4TEST
//    }
/////////
    //�J������ pos_camera_ �ݒ�
    int x_cam_sgn, y_cam_sgn;
    Direction8Util::cnvAng2Sgn(ang_cam_around_, x_cam_sgn, y_cam_sgn);
    pos_camera_ = DIR26(0, y_cam_sgn, x_cam_sgn); //8������X���W��0�Ƃ���ZX���ʂł�26�����ɕϊ�
    if (pos_camera_prev_ != pos_camera_) {
        is_just_changed_pos_cam_ = true;
    } else {
        is_just_changed_pos_cam_ = false;
    }
    pos_camera_prev_ = pos_camera_;
}

///////////4TEST
void VamSysCamWorker::onSwitchCameraWork() {
    ///////////4TEST
    CameraWorker::onSwitchCameraWork();
    /////////
}
/////////

VamSysCamWorker::~VamSysCamWorker() {
    GGAF_DELETE(pSe_);
}

//2015/10/08 ����
//��Dx�̋��ߕ���
//                         z+
//                        ^
//                        |
//                        |  /        �� �����x�N�g��
//                    DX  | /       �^
//                   <--->|/ DX   �^        ��
//                        /<--->�^          �` = �J�����̕\���̉E�̋��E���x�N�g��
// ----------------------/+---�^--------�Q��
//              ^      P/ | �^ vp   �Q��    ��
//              :      /  �^    �Q��        ��ʂ̒[������X���̌�_
//           DZ :     / �^| �Q��
//              v    /�^�Q��
//                 ��cam  |  X_BOUND
//                        |<-------------->
//                        |
//                        |z-
//
// cam = (-DX, 0, -DZ)
// vp  = (DX, 0, 0)
//                            | DX - (-DX) |   | 2*DX |
// �����x�N�g�� = vp -  cam = | 0  -  0    | = |   0  |
//                            | 0  - (-DZ) |   |  DZ  |
//
//�����ŁAr ��]�ir = ��/2 ��]�i����p�̓Ɓj�j
// ��    | 2*DX*cos(r)  + DZ*sin(r) |
// �` =  | 0                        |    �E�E�E�@
//       | 2*DX*-sin(r) + DZ*cos(r) |
//
//
//  ��                                       | X_BOUND - (-DX) |    | X_BOUND + DX |
//  �` =   ��ʂ̒[������X���̌�_ -  cam  = |  0      -  0    |  = |   0          |
//                                           |  0      - (-DZ) |    |  DZ          |
//
//���ꂪ���s�Ȃ̂�
// (2*DX*cos(r)  + DZ*sin(r)) / (X_BOUND + DX) =  (2*DX*-sin(r) + DZ*cos(r)) / DZ
//or
//  (X_BOUND + DX) / DZ = ( 2*DX*cos(r) + DZ*sin(r)) / (2*DX*-sin(r) + DZ*cos(r))
//�����������
//
//DX=-(sqrt((cos(r)^2-8*sin(r)^2)*DZ^2+12*cos(r)*sin(r)*X_BOUND*DZ+4*sin(r)^2*X_BOUND^2)+cos(r)*DZ+2*sin(r)*X_BOUND)/(4*sin(r))
//DX=(sqrt((cos(r)^2-8*sin(r)^2)*DZ^2+12*cos(r)*sin(r)*X_BOUND*DZ+4*sin(r)^2*X_BOUND^2)-cos(r)*DZ-2*sin(r)*X_BOUND)/(4*sin(r))
//���̂ق�������


//��px�̋��ߕ���
//���썶���E���ƁAX���̌�_P�����߂�
// cam = (-DX, 0, -DZ)
// vp  = (DX, 0, 0)
//                            | DX - (-DX) |   | 2*DX |
// �����x�N�g�� = vp -  cam = | 0  -  0    | = |   0  |
//                            | 0  - (-DZ) |   |  DZ  |
//�����ŁAr = -(��/2) ��]�i����p�̓Ɓj
// ��    | 2*DX*cos(r)  + DZ*sin(r) |
// �` =  | 0                        |    �E�E�E�@
//       | 2*DX*-sin(r) + DZ*cos(r) |
//
//XZ���ʏ�̒����̕����� Z = aX + b �̌X��
// a = (2*DX*-sin(r) + DZ*cos(r)) / (2*DX*cos(r)  + DZ*sin(r))
//�܂��A cam = (-DX, 0, -DZ) ��ʂ�̂ŁB
//
//Z = aX + b
//-DZ = ((2*DX*-sin(r) + DZ*cos(r)) / (2*DX*cos(r)  + DZ*sin(r))) * -DX + b
//b�ɂ��ĉ�����
//b=-((DZ^2+2*DX^2)*sin(r)+DX*DZ*cos(r))/(DZ*sin(r)+2*DX*cos(r))
//
//����Ē����̕�������
//Z = ((2*DX*-sin(r) + DZ*cos(r)) / (2*DX*cos(r)  + DZ*sin(r)))*X + (-((DZ^2+2*DX^2)*sin(r)+DX*DZ*cos(r))/(DZ*sin(r)+2*DX*cos(r)))
//
//���ꂪ�AZ=0�̂Ƃ���X�����߂�
//0 = ((2*DX*-sin(r) + DZ*cos(r)) / (2*DX*cos(r)  + DZ*sin(r)))*X + (-((DZ^2+2*DX^2)*sin(r)+DX*DZ*cos(r))/(DZ*sin(r)+2*DX*cos(r)))
//��X�ɂ��ĉ�����
//X=-((DZ^2+2*DX^2)*sin(r)+DX*DZ*cos(r))/(2*DX*sin(r)-DZ*cos(r))


//�̂̃��� UP�x�N�^����z��
//    for (int i = 0; i < 3*3*3; i++) {
//        for (int j = 0; j < 3*3*3; j++) {
//            VamSysCamWorker2::relation_up_vec_[i][j] = DIR26_NULL;
//        }
//    }
//    VamSysCamWorker2::relation_up_by_vec_ =  (int (*)[3*3*3])(&(VamSysCamWorker2::relation_up_vec_[13][13])); //13 �� 3*3*3=27 �̐^�񒆂̗v�f�A_relation_up_vec[-13�`13][-13�`13]�ŃA�N�Z�X�����
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1,-1,-1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1,-1, 0)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1,-1, 1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 0,-1)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 0, 1)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 1,-1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 1, 0)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26( 1, 1, 1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1,-1,-1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1,-1, 0)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1,-1, 1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 0,-1)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 0, 1)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 1,-1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 1, 0)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 0)][DIR26(-1, 1, 1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1,-1,-1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1,-1, 0)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1,-1, 1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 0,-1)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 0, 1)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 1,-1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 1, 0)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26(-1, 1, 1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1,-1,-1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1,-1, 0)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1,-1, 1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 0,-1)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 0, 1)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 1,-1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 1, 0)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 0)][DIR26( 1, 1, 1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1, 1,-1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1, 1, 0)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1, 1, 1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0, 1,-1)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0, 1, 1)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1, 1,-1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1, 1, 0)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1, 1, 1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1,-1,-1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1,-1, 0)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26(-1,-1, 1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0,-1,-1)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 0,-1, 1)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1,-1,-1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1,-1, 0)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 0)][DIR26( 1,-1, 1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1,-1,-1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1,-1, 0)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1,-1, 1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0,-1,-1)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0,-1, 1)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1,-1,-1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1,-1, 0)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1,-1, 1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1, 1,-1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1, 1, 0)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26(-1, 1, 1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0, 1,-1)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 0, 1, 1)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1, 1,-1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1, 1, 0)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 0)][DIR26( 1, 1, 1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1,-1, 1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 0, 1)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 1, 1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0,-1, 1)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 0, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 1, 1)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1,-1, 1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 0, 1)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 1, 1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1,-1,-1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 0,-1)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26(-1, 1,-1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0,-1,-1)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 0,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 0, 1,-1)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1,-1,-1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 0,-1)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0, 1)][DIR26( 1, 1,-1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1,-1,-1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 0,-1)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 1,-1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0,-1,-1)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 0,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 1,-1)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1,-1,-1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 0,-1)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 1,-1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1,-1, 1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 0, 1)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26(-1, 1, 1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0,-1, 1)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 0, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 0, 1, 1)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1,-1, 1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 0, 1)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 0,-1)][DIR26( 1, 1, 1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0, 1,-1)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0, 1, 1)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 0,-1)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 0, 1)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 1,-1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 1, 1, 1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1,-1,-1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1,-1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1,-1, 1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1, 0,-1)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26(-1, 0, 1)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0,-1,-1)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 0)][DIR26( 0,-1, 1)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1,-1,-1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1,-1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1,-1, 1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1, 0,-1)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26(-1, 0, 1)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0,-1,-1)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0,-1, 1)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0, 1,-1)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 0, 1, 1)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 0,-1)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 0, 1)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 1,-1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 0)][DIR26( 1, 1, 1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0,-1, 1)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 0, 1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 1, 1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1,-1, 0)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 1, 0)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1,-1, 1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 0, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 1, 1, 1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1,-1,-1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 0,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 1,-1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1,-1, 0)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26(-1, 1, 0)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0,-1,-1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 0,-1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0, 1)][DIR26( 0, 1,-1)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1,-1,-1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 0,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 1,-1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1,-1, 0)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26(-1, 1, 0)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0,-1,-1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 0,-1)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 1,-1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0,-1, 1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 0, 1)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 0, 1, 1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1,-1, 0)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 0, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 1, 0)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1,-1, 1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 0, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0,-1)][DIR26( 1, 1, 1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 0, 1)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 0, 1)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 0, 1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 1, 0)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 1, 0)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 1, 1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 1, 1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1,-1,-1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0,-1,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1,-1,-1)] = DIR26( 1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1,-1, 0)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1,-1, 0)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26(-1, 0,-1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 0, 0,-1)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1, 1)][DIR26( 1, 0,-1)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1,-1,-1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0,-1,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1,-1,-1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1,-1, 0)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0,-1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1,-1, 0)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 0,-1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 0,-1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 0,-1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 0, 1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 0, 1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 0, 1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 1, 0)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 1, 0)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26(-1, 1, 1)] = DIR26(-1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 0, 1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1,-1)][DIR26( 1, 1, 1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0, 1,-1)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0, 1, 1)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 0,-1)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 0, 1)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 1,-1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26(-1, 1, 1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1,-1,-1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1,-1, 1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1, 0,-1)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 1, 0, 1)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0,-1,-1)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 0)][DIR26( 0,-1, 1)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1, 0,-1)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1, 0, 1)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0,-1,-1)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0,-1, 1)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1,-1,-1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 1,-1, 1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 1,-1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 1, 1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0, 1,-1)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26( 0, 1, 1)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 0,-1)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 0)][DIR26(-1, 0, 1)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0,-1, 1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 0, 1)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 1, 1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1,-1, 0)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 1, 0)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1,-1, 1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 0, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26(-1, 1, 1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1,-1,-1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 0,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 1,-1)] = DIR26(-1, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1,-1, 0)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 1, 1, 0)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0,-1,-1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 0,-1)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 0, 1)][DIR26( 0, 1,-1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1,-1, 0)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 0, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 1, 0)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0,-1,-1)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 0,-1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 1,-1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1,-1,-1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 0,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 1, 1,-1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1,-1, 1)] = DIR26( 1,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 0, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 1, 1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0,-1, 1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 0, 1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26( 0, 1, 1)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1,-1, 0)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 0,-1)][DIR26(-1, 1, 0)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 0, 1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 0, 1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 0, 1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1,-1, 0)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0,-1, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1,-1, 0)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1,-1, 1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0,-1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1,-1, 1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 1,-1)] = DIR26(-1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 1,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 1,-1)] = DIR26( 1,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 1, 0)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 1, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 1, 0)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26(-1, 0,-1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 0, 0,-1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0,-1, 1)][DIR26( 1, 0,-1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 1, 0)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 1, 0)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 0,-1)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 0,-1)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 0,-1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 1,-1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 1,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 1,-1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1,-1, 1)] = DIR26(-1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0,-1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1,-1, 1)] = DIR26( 1, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1, 0, 1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0, 0, 1)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1, 0, 1)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26(-1,-1, 0)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 0,-1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 0, 1,-1)][DIR26( 1,-1, 0)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0, 0, 1)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0, 1, 1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 0, 1)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 1, 1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26( 0,-1,-1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1, 0,-1)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1,-1, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1, 1)][DIR26(-1,-1,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0, 0,-1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0,-1,-1)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1, 0, 0)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1, 0,-1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1,-1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26(-1,-1,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0, 0, 1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 0, 1, 0)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 0, 0)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 0, 1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1,-1)][DIR26( 1, 1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 0,-1)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 1, 0)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 1,-1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 1, 0,-1)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 1, 1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 1, 1,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0, 0, 1)] = DIR26( 1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0,-1, 0)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26( 0,-1, 1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26(-1,-1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1, 1,-1)][DIR26(-1,-1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 0, 1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0,-1, 1)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26(-1, 0, 1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26(-1,-1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 0,-1)] = DIR26(-1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 0, 1,-1)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 0,-1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 1, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1,-1, 1)][DIR26( 1, 1,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 0, 1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0,-1, 0)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0,-1, 1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1, 0, 0)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1, 0, 1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 1,-1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 0,-1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 1, 0)] = DIR26( 1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26( 0, 1,-1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 0, 0)] = DIR26( 0,-1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 0,-1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1, 1)][DIR26(-1, 1,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 0,-1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 1, 0)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 1,-1)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 0, 0)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 0,-1)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26(-1, 1,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0, 0, 1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0,-1, 0)] = DIR26(-1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 0,-1, 1)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1, 0, 0)] = DIR26( 0, 1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1, 0, 1)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1,-1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1,-1)][DIR26( 1,-1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 0,-1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0,-1, 0)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0,-1,-1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1, 0, 0)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1, 0,-1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1,-1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 1,-1,-1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 0, 1)] = DIR26( 1,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 1, 0)] = DIR26( 1, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26( 0, 1, 1)] = DIR26( 1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 0, 0)] = DIR26( 0,-1,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 0, 1)] = DIR26( 0,-1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 1, 0)] = DIR26( 0, 0,-1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26( 1,-1,-1)][DIR26(-1, 1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 0, 1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 1, 0)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 1, 1)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 0, 0)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 0, 1)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 1, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26(-1, 1, 1)] = DIR26( 0, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0, 0,-1)] = DIR26(-1, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0,-1, 0)] = DIR26(-1, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 0,-1,-1)] = DIR26(-1, 0, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1, 0, 0)] = DIR26( 0, 1, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1, 0,-1)] = DIR26( 0, 1, 0);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1,-1, 0)] = DIR26( 0, 0, 1);
//    VamSysCamWorker2::relation_up_by_vec_[DIR26(-1, 1, 1)][DIR26( 1,-1,-1)] = DIR26( 0, 0, 0);
