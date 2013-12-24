#include "stdafx.h"
#include "VamSysCamWorker.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/Camera.h"
#include "jp/gecchi/VioletVreath/actor/ViewPoint.h"

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
    lim_CAM_front_   = MyShip::lim_x_front_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_CAM_behaind_ = MyShip::lim_x_behaind_ + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_CAM_zleft_   = MyShip::lim_z_left_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_CAM_zright_  = MyShip::lim_z_right_  + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;

    lim_VP_top_     = MyShip::lim_y_top_     - (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_VP_bottom_  = MyShip::lim_y_bottom_  + (PX_C(PROPERTY::GAME_BUFFER_HEIGHT)/2)*revise;
    lim_VP_front_   = MyShip::lim_x_front_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_VP_behaind_ = MyShip::lim_x_behaind_ + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_VP_zleft_   = MyShip::lim_z_left_   - (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    lim_VP_zright_  = MyShip::lim_z_right_  + (PX_C(PROPERTY::GAME_BUFFER_WIDTH)/2)*revise;
    is_cam_pos_option_back_ = false;
    move_target_x_CAM_prev_ = 0;
    move_target_y_CAM_prev_ = 0;
    move_target_z_CAM_prev_ = 0;
    move_target_x_VP_prev_ = 0;
    move_target_y_VP_prev_ = 0;
    move_target_z_VP_prev_ = 0;
    pos_camera_prev_ = -1;
    pos_camera_ = VAM_POS_RIGHT;
}
void VamSysCamWorker::initialize() {
    CameraWorker::initialize();

    //初期カメラZ位置
    dZ_camera_init_ = -DX_C(pCam_->_cameraZ_org);

    target_up_face_no_prev_ = pCam_->up_face_;
    //画面背後用範囲差分
    //背後のZ座標はdZ_camera_init_/2
    correction_width_ = 0;//(PROPERTY::GAME_BUFFER_WIDTH*LEN_UNIT/2)/4;
    correction_height_ = 0;//(PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT/2)/4;
    pos_camera_ = VAM_POS_RIGHT;
    pos_camera_prev_ = -100;
    stop_dZ_ = 0;
    stop_dY_ = 0;
    _TRACE_("VamSysCamWorker::initialize() this="<<this);
    dump();
}
void VamSysCamWorker::onActive() {
    CameraWorker::onActive();
    if (pos_camera_ == VAM_POS_RIGHT || pos_camera_ == VAM_POS_LEFT || pos_camera_ > VAM_POS_TO_BEHIND) {
        pCam_->setCamUpFace(2, 40/2);
    }
    move_target_x_CAM_prev_ -= 1; //ブレイクさせて、座標を以前の状態に補正させる
    move_target_x_VP_prev_ -= 1;  //ブレイクさせて、座標を以前の状態に補正させる
}

void VamSysCamWorker::processBehavior() {
    VirtualButton* pVbPlay = VB_PLAY;
    //DefaultVamSysCamWorker::processBehavior();

    //ゲーム内カメラワーク処理
    if (pMyShip_ == nullptr) {
        return; //MyShipSceneシーンが未だならカメラワーク禁止
    }
    Camera* pCam = P_CAM;
    ViewPoint* pVP = (ViewPoint*)(pCam->getViewPoint());
    MyOptionController* pOptCtrler = P_MYSHIP_SCENE->papOptionCtrler_[0];

    //カメラ位置番号を決定処理
    is_cam_pos_option_back_ = false;
    if (pVbPlay->isBeingPressed(VB_OPTION)) { //オプション操作時
        //if (pVbPlay->isBeingPressed(VB_VIEW)) {
        //    is_cam_pos_option_back_ = true; //TODO:オプション操作中のオプション[0]の背面に回る
        //}
    } else if (pVbPlay->isPushedDown(VB_VIEW)) { //ビューボタンプッシュ                              //オプション非操作時（通常時）
        _TRACE_("VB_VIEW!! now pos_camera_="<<pos_camera_);
        if (pos_camera_ < VAM_POS_TO_BEHIND) { //背面ビューポイントではない場合、
            pos_camera_ += VAM_POS_TO_BEHIND;  //それぞれの対応背面ビューポイントへ
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {//背面ビューポイントの場合
            //方向入力により新たなビューポイントへ
            if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                pos_camera_ = VAM_POS_LEFT;
            } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                pos_camera_ = VAM_POS_RIGHT;
            } else if (pVbPlay->isBeingPressed(VB_UP)) {
                pos_camera_ = VAM_POS_BOTTOM;
            } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                pos_camera_ = VAM_POS_TOP;
            } else {
                //方向未入力の場合、元のビューポイントへ
                pos_camera_ -= VAM_POS_TO_BEHIND;
            }
        }
        _TRACE_("VB_VIEW!!  -> pos_camera_="<<pos_camera_);
    }

    //カメラの移動目標座標
    coord move_target_x_CAM, move_target_y_CAM, move_target_z_CAM;
    //カメラのビューポイントの移動目標座標
    coord move_target_x_VP, move_target_y_VP, move_target_z_VP;
//    //カメラの目標UPアングル値
    int target_up_face_no;
//    angle move_target_XY_CAM_UP;

    //カメラの目標座標、ビューポイントの目標座標を設定
    static coord Dx = PX_C(PROPERTY::GAME_BUFFER_WIDTH/4);
    static int Ddx_hw = (int)((PROPERTY::GAME_BUFFER_WIDTH*LEN_UNIT/2) - (PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT/2));

    if (is_cam_pos_option_back_) { //TODO:オプション操作中のオプション[0]背面に回る
        coord d = dZ_camera_init_*0.6;
        move_target_x_CAM = pOptCtrler->_x + pOptCtrler->_pKuroko->_vX*-d;
        move_target_y_CAM = pOptCtrler->_y + pOptCtrler->_pKuroko->_vY*-d;
        move_target_z_CAM = pOptCtrler->_z + pOptCtrler->_pKuroko->_vZ*-d;
        move_target_x_VP = pOptCtrler->_x + pOptCtrler->_pKuroko->_vX*d;
        move_target_y_VP = pOptCtrler->_y + pOptCtrler->_pKuroko->_vY*d;
        move_target_z_VP = pOptCtrler->_z + pOptCtrler->_pKuroko->_vZ*d;
//        move_target_XY_CAM_UP = UTIL::simplifyAng(pOptCtrler->_pKuroko->_angRzMv+D90ANG);

    } else {//通常時VAM
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
    //            move_target_x_CAM = 0;
    //            move_target_y_CAM = 0;
    //            move_target_z_CAM = -dZ_camera_init_;
    //            move_target_x_VP = 0;
    //            move_target_y_VP = 0;
    //            move_target_z_VP = 0;

                move_target_x_CAM = -Dx + (-pMyShip_->_x-200000)*2;
                //↑ -200000 はカメラ移動位置、
                //   *2 は自機が後ろに下がった時のカメラのパン具合。
                //   この辺りの数値は納得いくまで調整を繰した。
                //   TODO:本当はゲーム領域の大きさから動的に計算できる。いつかそうしたい。
                if (-Dx > move_target_x_CAM) {
                    move_target_x_CAM = -Dx;
                } else if (move_target_x_CAM > Dx/2) {
                    move_target_x_CAM = Dx/2;
                }
                move_target_y_CAM = pMyShip_->_y;
                move_target_z_CAM = pMyShip_->_z - dZ_camera_init_;

                move_target_x_VP = Dx - (-pMyShip_->_x-200000)*2;
                if (Dx < move_target_x_VP) {
                    move_target_x_VP = Dx;
                } else if ( move_target_x_VP < -Dx/2) {
                    move_target_x_VP = -Dx/2;
                }
                move_target_y_VP = pMyShip_->_y;
                move_target_z_VP = pMyShip_->_z-100000;
            } else if (pos_camera_ == VAM_POS_LEFT) {
                move_target_x_CAM = -Dx + (-pMyShip_->_x-200000)*2;
                if (-Dx > move_target_x_CAM) {
                    move_target_x_CAM = -Dx;
                } else if (move_target_x_CAM > Dx/2) {
                    move_target_x_CAM = Dx/2;
                }
                move_target_y_CAM = pMyShip_->_y;
                move_target_z_CAM = pMyShip_->_z + dZ_camera_init_;
                move_target_x_VP = Dx - (-pMyShip_->_x-200000)*2;
                if (Dx < move_target_x_VP) {
                    move_target_x_VP = Dx;
                } else if ( move_target_x_VP < -Dx/2) {
                    move_target_x_VP = -Dx/2;
                }
                move_target_y_VP = pMyShip_->_y;
                move_target_z_VP = pMyShip_->_z+100000;
            } else if (pos_camera_ == VAM_POS_TOP) {
                move_target_x_CAM = -Dx - Ddx_hw + (-pMyShip_->_x-125000)*2;
                if ((-Dx - Ddx_hw) > move_target_x_CAM) {
                    move_target_x_CAM = -Dx - Ddx_hw;
                } else if (move_target_x_CAM > (Dx + Ddx_hw)/2) {
                    move_target_x_CAM = (Dx + Ddx_hw)/2;
                }
                move_target_y_CAM = pMyShip_->_y + dZ_camera_init_ + Ddx_hw;
                move_target_z_CAM = pMyShip_->_z;
                move_target_x_VP = Dx + Ddx_hw - (-pMyShip_->_x-125000)*2;
                if (Dx + Ddx_hw < move_target_x_VP) {
                    move_target_x_VP = Dx + Ddx_hw;
                } else if ( move_target_x_VP < -(Dx + Ddx_hw)/2) {
                    move_target_x_VP = -(Dx + Ddx_hw)/2;
                }
                move_target_y_VP = pMyShip_->_y;
                move_target_z_VP = pMyShip_->_z;
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                move_target_x_CAM = -Dx - Ddx_hw + (-pMyShip_->_x-125000)*2;
                if ((-Dx - Ddx_hw) > move_target_x_CAM) {
                    move_target_x_CAM = -Dx - Ddx_hw;
                } else if (move_target_x_CAM > (Dx + Ddx_hw)/2) {
                    move_target_x_CAM = (Dx + Ddx_hw)/2;
                }
                move_target_y_CAM = pMyShip_->_y - dZ_camera_init_ - Ddx_hw;
                move_target_z_CAM = pMyShip_->_z;
                move_target_x_VP = Dx + Ddx_hw - (-pMyShip_->_x-125000)*2;
                if (Dx + Ddx_hw < move_target_x_VP) {
                    move_target_x_VP = Dx + Ddx_hw;
                } else if ( move_target_x_VP < -(Dx + Ddx_hw)/2) {
                    move_target_x_VP = -(Dx + Ddx_hw)/2;
                }
                move_target_y_VP = pMyShip_->_y;
                move_target_z_VP = pMyShip_->_z;
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            move_target_x_CAM = pMyShip_->_x - (dZ_camera_init_*0.6);
            move_target_y_CAM = pMyShip_->_y;
            move_target_z_CAM = pMyShip_->_z;
            move_target_x_VP = pMyShip_->_x + (dZ_camera_init_*2);
            move_target_y_VP = pMyShip_->_y;
            move_target_z_VP = pMyShip_->_z;
//            move_target_XY_CAM_UP = D90ANG;
    //        if (pos_camera_ == VAM_POS_BEHIND_RIGHT) {
    //            move_target_z_CAM -= Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_LEFT) {
    //            move_target_z_CAM += Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_TOP) {
    //            move_target_y_CAM += Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_BOTTOM) {
    //            move_target_y_CAM -= Dd;
    //        }
        } else {
            throwGgafCriticalException("World::processBehavior() 不正なpos_camera_="<<pos_camera_);
        }
        //カメラの目標座標、ビューポイントの目標座標について、現在の動いている方向への若干画面寄りを行う。（ﾅﾝﾉｺｯﾁｬ）
        move_target_z_CAM -= (pMyShip_->_z*0.05);
        move_target_y_CAM -= (pMyShip_->_y*0.05);
    }

//    int cam_velo_renge;  //カメラの移動速度の最大、最小敷居値
//    //VB_VIEW押した時の処理
//    if (pVbPlay->isBeingPressed(VB_VIEW)) {
//        //VB_VIEWを押しっぱなし中は、ゆっくりな移動速度に制限
//        cam_velo_renge = cam_velo_renge_ * 0.02;
//    } else {
//        //通常のカメラ移動速度制限にする
//        cam_velo_renge = cam_velo_renge_;
//    }

    //VB_VIEW離した時の処理
    if (pVbPlay->isReleasedUp(VB_VIEW)) {
        if (pVbPlay->isPushedUp(VB_VIEW, 20)) {
            //チョン押しの場合、なにもしない（普通にビューポイント移動となる）
        } else {
            //長押しをしたた後、VB_VIEW離した時
            if (pos_camera_ < VAM_POS_TO_BEHIND) { //背面ビューポイントではない場合、
                //それぞれの元の対応ビューポイントへ戻る。
                pos_camera_ += VAM_POS_TO_BEHIND;
            } else if (pos_camera_ > VAM_POS_TO_BEHIND) {//背面ビューポイントだった場合
                //そのまま

                //それぞれの元の対応背面ビューポイントへ戻る。
                //pos_camera_ -= VAM_POS_TO_BEHIND;
            }
        }
    }

    //カメラとビューポイントの移動座標を制限。
    //自機移動範囲に応じて、画面端の感じを演出するため。(無くとも問題ない？)
    if (pos_camera_ < VAM_POS_TO_BEHIND) {
        if (pos_camera_ == VAM_POS_RIGHT) {
            if (move_target_y_CAM > lim_CAM_top_) {
                move_target_y_CAM = lim_CAM_top_;
            }
            if (move_target_y_CAM < lim_CAM_bottom_ ) {
                move_target_y_CAM = lim_CAM_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_LEFT) {
            if (move_target_y_CAM > lim_CAM_top_) {
                move_target_y_CAM = lim_CAM_top_;
            }
            if (move_target_y_CAM < lim_CAM_bottom_ ) {
                move_target_y_CAM = lim_CAM_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_TOP) {
            if (move_target_z_CAM > lim_CAM_zleft_) {
                move_target_z_CAM = lim_CAM_zleft_;
            }
            if (move_target_z_CAM < lim_CAM_zright_) {
                move_target_z_CAM = lim_CAM_zright_;
            }
        } else if (pos_camera_ == VAM_POS_BOTTOM) {
            if (move_target_z_CAM > lim_CAM_zleft_) {
                move_target_z_CAM = lim_CAM_zleft_;
            }
            if (move_target_z_CAM < lim_CAM_zright_) {
                move_target_z_CAM = lim_CAM_zright_;
            }
        }
    } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
        if (move_target_y_CAM > lim_CAM_top_ - correction_height_) {
            move_target_y_CAM = lim_CAM_top_ - correction_height_;
        }
        if (move_target_y_CAM < lim_CAM_bottom_ + correction_height_) {
            move_target_y_CAM = lim_CAM_bottom_ + correction_height_;
        }
        if (move_target_z_CAM > lim_CAM_zleft_ - correction_width_) {
            move_target_z_CAM = lim_CAM_zleft_ - correction_width_;
        }
        if (move_target_z_CAM < lim_CAM_zright_ + correction_width_) {
            move_target_z_CAM = lim_CAM_zright_ + correction_width_;
        }
    }
    if (pos_camera_ < VAM_POS_TO_BEHIND) {
        if (pos_camera_ == VAM_POS_RIGHT) {
            if (move_target_y_VP > lim_VP_top_) {
                move_target_y_VP = lim_VP_top_;
            }
            if (move_target_y_VP < lim_VP_bottom_ ) {
                move_target_y_VP = lim_VP_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_LEFT) {
            if (move_target_y_VP > lim_VP_top_) {
                move_target_y_VP = lim_VP_top_;
            }
            if (move_target_y_VP < lim_VP_bottom_ ) {
                move_target_y_VP = lim_VP_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_TOP) {
            if (move_target_z_VP > lim_VP_zleft_) {
                move_target_z_VP = lim_VP_zleft_;
            }
            if (move_target_z_VP < lim_VP_zright_) {
                move_target_z_VP = lim_VP_zright_;
            }
        } else if (pos_camera_ == VAM_POS_BOTTOM) {
            if (move_target_z_VP > lim_VP_zleft_) {
                move_target_z_VP = lim_VP_zleft_;
            }
            if (move_target_z_VP < lim_VP_zright_) {
                move_target_z_VP = lim_VP_zright_;
            }
        }
    } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
        if (move_target_y_VP > lim_VP_top_ - correction_height_) {
            move_target_y_VP = lim_VP_top_ - correction_height_;
        }
        if (move_target_y_VP < lim_VP_bottom_ + correction_height_) {
            move_target_y_VP = lim_VP_bottom_ + correction_height_;
        }
        if (move_target_z_VP > lim_VP_zleft_ - correction_width_) {
            move_target_z_VP = lim_VP_zleft_ - correction_width_;
        }
        if (move_target_z_VP < lim_VP_zright_ + correction_width_) {
            move_target_z_VP = lim_VP_zright_ + correction_width_;
        }
    }


    if ( move_target_x_CAM_prev_ != move_target_x_CAM  ||
         move_target_y_CAM_prev_ != move_target_y_CAM  ||
         move_target_z_CAM_prev_ != move_target_z_CAM    ) {
        slideMvCamTo(move_target_x_CAM,
                     move_target_y_CAM,
                     move_target_z_CAM, 40);
    }
    if ( move_target_x_VP_prev_ != move_target_x_VP    ||
         move_target_y_VP_prev_ != move_target_y_VP    ||
         move_target_z_VP_prev_ != move_target_z_VP      ) {
        slideMvVpTo(move_target_x_VP,
                    move_target_y_VP,
                    move_target_z_VP, 40);
    }

    if (getBehaveingFrame() % 30 == 0) {
        if (pos_camera_ == VAM_POS_RIGHT || pos_camera_ == VAM_POS_LEFT || pos_camera_ > VAM_POS_TO_BEHIND) {
            pCam_->setCamUpFace(2, 40/2);
        }
    }

    pos_camera_prev_ = pos_camera_;
    move_target_x_CAM_prev_ = move_target_x_CAM;
    move_target_y_CAM_prev_ = move_target_y_CAM;
    move_target_z_CAM_prev_ = move_target_z_CAM;
    move_target_x_VP_prev_ = move_target_x_VP;
    move_target_y_VP_prev_ = move_target_y_VP;
    move_target_z_VP_prev_ = move_target_z_VP;

    CameraWorker::processBehavior();
}
VamSysCamWorker::~VamSysCamWorker() {
}
