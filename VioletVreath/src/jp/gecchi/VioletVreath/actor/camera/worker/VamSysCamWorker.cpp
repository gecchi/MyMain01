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
#include "jp/ggaf/dxcore/sound/GgafDxSeTransmitter.h"
#include <math.h>

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


VamSysCamWorker::VamSysCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "VamSysCamWorker";
    pMyShip_ = nullptr; //MyShipSceneに設定してもらう

    //初期カメラ移動範囲制限
    float revise = 0.7; //斜めから見るので補正値を掛ける。1.0の場合は原点からでドンピシャ。これは微調整を繰り返した
    lim_CAM_top_     = MyShip::lim_y_top_     - (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_CAM_bottom_  = MyShip::lim_y_bottom_  + (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_CAM_infront_ = MyShip::lim_x_infront_ - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_CAM_behaind_ = MyShip::lim_x_behaind_ + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_CAM_zleft_   = MyShip::lim_z_left_    - (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_CAM_zright_  = MyShip::lim_z_right_   + (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;

    lim_VP_top_     = MyShip::lim_y_top_     - (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_VP_bottom_  = MyShip::lim_y_bottom_  + (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_VP_infront_ = MyShip::lim_x_infront_ - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_VP_behaind_ = MyShip::lim_x_behaind_ + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_VP_zleft_   = MyShip::lim_z_left_    - (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_VP_zright_  = MyShip::lim_z_right_   + (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    pos_camera_ = VAM_POS_ZRIGHT;
    pos_camera_prev_ = VAM_POS_NON;
    cam_mv_frame_base_ = 20;
    cam_mv_frame_ = cam_mv_frame_base_;
    ang_cam_around_base_ = D180ANG;
    ang_cam_around_ = ang_cam_around_base_;
    returnning_cam_pos_ = false;
    returnning_cam_pos_frames_ = 0;
    is_just_changed_pos_cam_ = false;

    pSe_ = NEW GgafDxSeTransmitter();
    pSe_->set(SE_RETURNNING_CAM_POS, "WAVE_MY_RETURNNING_CAM_POS" ,0);
}

void VamSysCamWorker::initialize() {
    CameraWorker::initialize();
    pos_camera_ = VAM_POS_ZRIGHT;
    pos_camera_prev_ = VAM_POS_NON;
    ang_cam_around_ = ang_cam_around_base_;
    returnning_cam_pos_frames_ = 0;
    Camera* pCam = pCam_;
    static const double H_FOVX = pCam->_rad_half_fovX;
    static const double DZ = ABS(pCam->_cameraZ_org);
    static const double X_BOUND = pCam->_zf;
    //視野右境界線と、X軸が、ゲーム領域右端で交わる場合のCAMとVPのスライド具合Dx（求め方はコード末尾のメモ）
    static const double DX = (sqrt((cos(H_FOVX)*cos(H_FOVX)-8*sin(H_FOVX)*sin(H_FOVX))*DZ*DZ+12*cos(H_FOVX)*sin(H_FOVX)*X_BOUND*DZ+4*sin(H_FOVX)*sin(H_FOVX)*X_BOUND*X_BOUND)-cos(H_FOVX)*DZ-2*sin(H_FOVX)*X_BOUND)/(4*sin(H_FOVX));
    //視野左境界線と、X軸の交点P(X_P, 0, 0) 求め方はコード末尾のメモ）
    static const double X_P = -((DZ*DZ+2*DX*DX)*sin(-H_FOVX)+DX*DZ*cos(-H_FOVX))/(2*DX*sin(-H_FOVX)-DZ*cos(-H_FOVX));
    static const double X_BEHAIND = C_DX(MyShip::lim_x_behaind_);
    static const double DX2 = (sqrt((cos(-H_FOVX)*cos(-H_FOVX)-8*sin(-H_FOVX)*sin(-H_FOVX))*DZ*DZ+12*cos(-H_FOVX)*sin(-H_FOVX)*X_BEHAIND*DZ+4*sin(-H_FOVX)*sin(-H_FOVX)*X_BEHAIND*X_BEHAIND)-cos(-H_FOVX)*DZ-2*sin(-H_FOVX)*X_BEHAIND)/(4*sin(-H_FOVX));

    DZC_ = DX_C(DZ);
    DXC_ = DX_C(DX);
    DX2_C_ = DX_C(DX2);
    X_P_C_ = DX_C(X_P);

    _TRACE_("VamSysCamWorker::initialize() this="<<NODE_INFO);
    dump();
}
void VamSysCamWorker::onActive() {
    //CameraWorker::onActive();
    cam_mv_frame_ = cam_mv_frame_base_;
}

void VamSysCamWorker::processBehavior() {
    VirtualButton* pVbPlay = VB_PLAY;
    //ゲーム内カメラワーク処理
    if (pMyShip_ == nullptr) {
        return; //MyShipSceneシーンが未だならカメラワーク禁止
    }
    Camera* pCam = pCam_;
    CameraViewPoint* pVP = (CameraViewPoint*)(pCam->getCameraViewPoint());

    //カメラの移動目標座標設定( mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM)
    coord mv_t_x_CAM = -DXC_ + ((X_P_C_*0.85) - pMyShip_->_x)*2;
                             //↑ X_P_C_ はカメラ移動開始位置、*0.85 は自機キャラの横幅を考慮
                             //   最後の *2 は自機が後ろに下がった時のカメラのパンの速さ具合。
    if (-DXC_ > mv_t_x_CAM) {
        mv_t_x_CAM = -DXC_;
    } else if (mv_t_x_CAM > -DX2_C_) {
        mv_t_x_CAM = -DX2_C_;
    }

    if (returnning_cam_pos_) {
        if (returnning_cam_pos_frames_ == 0) {
            returnning_cam_pos_ = false;
        } else {
            returnning_cam_pos_frames_--;
        }
    }

    if (!returnning_cam_pos_) {
        if (pVbPlay->arePushedDownAtOnce(VB_VIEW_UP, VB_VIEW_DOWN) ) {
            pSe_->play(SE_RETURNNING_CAM_POS);
            angle d = UTIL::getAngDiff(ang_cam_around_, ang_cam_around_base_, TURN_CLOSE_TO);
            ang_cam_around_ = ang_cam_around_base_;
            cam_mv_frame_ = (frame)(ANG_D(ABS(d))/3);
            returnning_cam_pos_frames_ = cam_mv_frame_;
            returnning_cam_pos_ = true;
        }
    }
    if (!returnning_cam_pos_) {
        if (pVbPlay->isBeingPressed(VB_VIEW_UP) && !pVbPlay->isBeingPressed(VB_VIEW_DOWN)) {
            ang_cam_around_ = UTIL::simplifyAng(ang_cam_around_-D_ANG(2));
            cam_mv_frame_ = 2;
        } else if (pVbPlay->isBeingPressed(VB_VIEW_DOWN) && !pVbPlay->isBeingPressed(VB_VIEW_UP)) {
            ang_cam_around_ = UTIL::simplifyAng(ang_cam_around_+D_ANG(2));
            cam_mv_frame_ = 2;
        } else {
            cam_mv_frame_ = cam_mv_frame_base_;
        }
    }
    coord mv_t_y_CAM = pMyShip_->_y + (ANG_SIN(ang_cam_around_) * DZC_);
    coord mv_t_z_CAM = pMyShip_->_z + (ANG_COS(ang_cam_around_) * DZC_);

    //カメラのビューポイントの移動目標座標設定(mv_t_x_VP, mv_t_y_VP, mv_t_z_VP, cam_mv_frame_)
    coord mv_t_x_VP = DXC_ - ((X_P_C_*0.85) - pMyShip_->_x)*2;
    if (DXC_ < mv_t_x_VP) {
        mv_t_x_VP = DXC_;
    } else if ( mv_t_x_VP < DX2_C_) {
        mv_t_x_VP = DX2_C_;
    }

    coord mv_t_y_VP = pMyShip_->_y;
    coord mv_t_z_VP = pMyShip_->_z;

    //カメラ移動座標を制限。
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

    //ビューポイントの移動座標を制限
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
    if (t_x_CAM_ != mv_t_x_CAM || t_y_CAM_ != mv_t_y_CAM || t_z_CAM_ != mv_t_z_CAM ) {
    	slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM, cam_mv_frame_);
    }
    if (t_x_VP_ != mv_t_x_VP || t_y_VP_ != mv_t_y_VP || t_z_VP_ != mv_t_z_VP ) {
    	slideMvVpTo(mv_t_x_VP, mv_t_y_VP, mv_t_z_VP, cam_mv_frame_);
    }

//_TRACE_("mv_t_CAM=("<<mv_t_x_CAM<<","<<mv_t_y_CAM<<","<<mv_t_z_CAM<<")");
//_TRACE_("mv_t_VP=("<<mv_t_x_VP<<","<<mv_t_y_VP<<","<<mv_t_z_VP<<")");
//_TRACE_("X_P_C_="<<X_P_C_);

    //カメラのUPを設定
    angle up_ang = UTIL::simplifyAng(ang_cam_around_ - D45ANG);
    static const coord cDz_sqrt2 = DZC_ * sqrt(2.0);  //計算用定数、カメラが45度斜め上の初期Z軸距離
    coord up_y = pMyShip_->_y  + (ANG_SIN(up_ang) * cDz_sqrt2);
    coord up_z = pMyShip_->_z  + (ANG_COS(up_ang) * cDz_sqrt2);
    slideMvUpVecTo(0, up_y - mv_t_y_CAM, up_z - mv_t_z_CAM, cam_mv_frame_);

    //カメラの pos_camera_ 設定
    int x_cam_sgn, y_cam_sgn;
    GgafDx8DirectionUtil::cnvAng2Sgn(ang_cam_around_, x_cam_sgn, y_cam_sgn);
    pos_camera_ = DIR26(0, y_cam_sgn, x_cam_sgn);
    if (pos_camera_prev_ != pos_camera_) {
        is_just_changed_pos_cam_ = true;
    } else {
        is_just_changed_pos_cam_ = false;
    }
    pos_camera_prev_ = pos_camera_;
}

VamSysCamWorker::~VamSysCamWorker() {
    GGAF_DELETE(pSe_);
}

//2015/10/08 メモ
//＜Dxの求め方＞
//                         z+
//                        ^
//                        |
//                        |  /        ┐ 視線ベクトル
//                    DX  | /       ／
//                   <--->|/ DX   ／        →
//                        /<--->／          Ａ = カメラの表示の右の境界線ベクトル
// ----------------------/+---／--------＿─
//              ^      P/ | ／ vp   ＿─    ↑
//              :      /  ／    ＿─        画面の端っことX軸の交点
//           DZ :     / ／| ＿─
//              v    /／＿─
//                 ∀cam  |  X_BOUND
//                        |<-------------->
//                        |
//                        |z-
//
// cam = (-DX, 0, -DZ)
// vp  = (DX, 0, 0)
//                            | DX - (-DX) |   | 2*DX |
// 視線ベクトル = vp -  cam = | 0  -  0    | = |   0  |
//                            | 0  - (-DZ) |   |  DZ  |
//
//ｙ軸で、r 回転（r = θ/2 回転（視野角はθ））
// →    | 2*DX*cos(r)  + DZ*sin(r) |
// Ａ =  | 0                        |    ・・・①
//       | 2*DX*-sin(r) + DZ*cos(r) |
//
//
//  →                                       | X_BOUND - (-DX) |    | X_BOUND + DX |
//  Ａ =   画面の端っことX軸の交点 -  cam  = |  0      -  0    |  = |   0          |
//                                           |  0      - (-DZ) |    |  DZ          |
//
//これが平行なので
// (2*DX*cos(r)  + DZ*sin(r)) / (X_BOUND + DX) =  (2*DX*-sin(r) + DZ*cos(r)) / DZ
//or
//  (X_BOUND + DX) / DZ = ( 2*DX*cos(r) + DZ*sin(r)) / (2*DX*-sin(r) + DZ*cos(r))
//これを解くと
//
//DX=-(sqrt((cos(r)^2-8*sin(r)^2)*DZ^2+12*cos(r)*sin(r)*X_BOUND*DZ+4*sin(r)^2*X_BOUND^2)+cos(r)*DZ+2*sin(r)*X_BOUND)/(4*sin(r))
//DX=(sqrt((cos(r)^2-8*sin(r)^2)*DZ^2+12*cos(r)*sin(r)*X_BOUND*DZ+4*sin(r)^2*X_BOUND^2)-cos(r)*DZ-2*sin(r)*X_BOUND)/(4*sin(r))
//下のほうが正解


//＜pxの求め方＞
//視野左境界線と、X軸の交点Pを求める
// cam = (-DX, 0, -DZ)
// vp  = (DX, 0, 0)
//                            | DX - (-DX) |   | 2*DX |
// 視線ベクトル = vp -  cam = | 0  -  0    | = |   0  |
//                            | 0  - (-DZ) |   |  DZ  |
//ｙ軸で、r = -(θ/2) 回転（視野角はθ）
// →    | 2*DX*cos(r)  + DZ*sin(r) |
// Ａ =  | 0                        |    ・・・①
//       | 2*DX*-sin(r) + DZ*cos(r) |
//
//XZ平面上の直線の方程式 Z = aX + b の傾き
// a = (2*DX*-sin(r) + DZ*cos(r)) / (2*DX*cos(r)  + DZ*sin(r))
//また、 cam = (-DX, 0, -DZ) を通るので。
//
//Z = aX + b
//-DZ = ((2*DX*-sin(r) + DZ*cos(r)) / (2*DX*cos(r)  + DZ*sin(r))) * -DX + b
//bについて解くと
//b=-((DZ^2+2*DX^2)*sin(r)+DX*DZ*cos(r))/(DZ*sin(r)+2*DX*cos(r))
//
//よって直線の方程式は
//Z = ((2*DX*-sin(r) + DZ*cos(r)) / (2*DX*cos(r)  + DZ*sin(r)))*X + (-((DZ^2+2*DX^2)*sin(r)+DX*DZ*cos(r))/(DZ*sin(r)+2*DX*cos(r)))
//
//これが、Z=0のときのXを求める
//0 = ((2*DX*-sin(r) + DZ*cos(r)) / (2*DX*cos(r)  + DZ*sin(r)))*X + (-((DZ^2+2*DX^2)*sin(r)+DX*DZ*cos(r))/(DZ*sin(r)+2*DX*cos(r)))
//をXについて解くと
//X=-((DZ^2+2*DX^2)*sin(r)+DX*DZ*cos(r))/(2*DX*sin(r)-DZ*cos(r))

