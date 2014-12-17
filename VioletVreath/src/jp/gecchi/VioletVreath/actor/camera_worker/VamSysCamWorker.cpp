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
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMoverAssistantA.h"

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
    pos_camera_prev_ = -1;
    pos_camera_ = VAM_POS_RIGHT;
    pos_camera_pressed_ = VAM_POS_RIGHT;
    cam_mv_frame_base_ = 50;
    cam_mv_frame_ = cam_mv_frame_base_;
    mv_t_x_CAM_prev_ = 0;
    mv_t_y_CAM_prev_ = 0;
    mv_t_z_CAM_prev_ = 0;
}
void VamSysCamWorker::initialize() {
    CameraWorker::initialize();

    //初期カメラZ位置
    dZ_camera_init_ = -DX_C(pCam_->_cameraZ_org);

    //画面背後用範囲差分
    //背後のZ座標はdZ_camera_init_/2
    correction_width_ = PX_C(30); //(PROPERTY::GAME_BUFFER_WIDTH*LEN_UNIT/2)/4;
    correction_height_ = PX_C(30); //(PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT/2)/4;
    pos_camera_ = VAM_POS_RIGHT;
    pos_camera_prev_ = -100;
    mv_t_x_CAM_prev_ = 0;
    mv_t_y_CAM_prev_ = 0;
    mv_t_z_CAM_prev_ = 0;
    _TRACE_("VamSysCamWorker::initialize() this="<<this);
    dump();
}
void VamSysCamWorker::onActive() {
    //CameraWorker::onActive();
    //cam_mv_frame_ = cam_mv_frame_base_;
}

void VamSysCamWorker::processBehavior() {
    VirtualButton* pVbPlay = VB_PLAY;
    //ゲーム内カメラワーク処理
    if (pMyShip_ == nullptr) {
        return; //MyShipSceneシーンが未だならカメラワーク禁止
    }
    Camera* pCam = pCam_;
    ViewPoint* pVP = (ViewPoint*)(pCam->getViewPoint());
    MyOptionController* pOptCtrler = P_MYSHIP_SCENE->papOptionCtrler_[0];

    //カメラ位置番号を決定処理
    is_cam_pos_option_back_ = false;
//    if (pVbPlay->isBeingPressed(VB_OPTION)) { //オプション操作時
//        if (MyOptionController::now_option_num_ >= 1 && pVbPlay->isBeingPressed(VB_VIEW)) {
//            is_cam_pos_option_back_ = true; //TODO:オプション操作中のオプション[0]の背面に回る
//        }
//    } else if (pVbPlay->isPushedDown(VB_VIEW)) { //ビューボタンプッシュ                              //オプション非操作時（通常時）
//        _TRACE_("VB_VIEW!! now pos_camera_="<<pos_camera_);
//        if (pos_camera_ < VAM_POS_TO_BEHIND) { //背面ビューポイントではない場合、
//            pos_camera_ += VAM_POS_TO_BEHIND;  //それぞれの対応背面ビューポイントへ
//        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {//背面ビューポイントの場合
//            //方向入力により新たなビューポイントへ
//            if (pVbPlay->isBeingPressed(VB_RIGHT)) {
//                pos_camera_ = VAM_POS_LEFT;
//            } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
//                pos_camera_ = VAM_POS_RIGHT;
//            } else if (pVbPlay->isBeingPressed(VB_UP)) {
//                pos_camera_ = VAM_POS_BOTTOM;
//            } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
//                pos_camera_ = VAM_POS_TOP;
//            } else {
//                //方向未入力の場合、元のビューポイントへ
//                pos_camera_ -= VAM_POS_TO_BEHIND;
//            }
//        }
//        _TRACE_("VB_VIEW!!  -> pos_camera_="<<pos_camera_);
//    }
    bool isBeingPressed_VB_VIEW_RIGHT = pVbPlay->isBeingPressed(VB_VIEW_RIGHT);
    bool isBeingPressed_VB_VIEW_LEFT = pVbPlay->isBeingPressed(VB_VIEW_LEFT);
    bool isBeingPressed_VB_VIEW_UP = pVbPlay->isBeingPressed(VB_VIEW_UP);
    bool isBeingPressed_VB_VIEW_DOWN = pVbPlay->isBeingPressed(VB_VIEW_DOWN);
    bool isBeingPressed_VB_VIEW = isBeingPressed_VB_VIEW_RIGHT || isBeingPressed_VB_VIEW_LEFT || isBeingPressed_VB_VIEW_UP || isBeingPressed_VB_VIEW_DOWN;


    bool isReleasedUp_VB_VIEW_RIGHT = pVbPlay->isReleasedUp(VB_VIEW_RIGHT);
    bool isReleasedUp_VB_VIEW_LEFT = pVbPlay->isReleasedUp(VB_VIEW_LEFT);
    bool isReleasedUp_VB_VIEW_UP = pVbPlay->isReleasedUp(VB_VIEW_UP);
    bool isReleasedUp_VB_VIEW_DOWN = pVbPlay->isReleasedUp(VB_VIEW_DOWN);
    bool isReleasedUp_VB_VIEW = isReleasedUp_VB_VIEW_RIGHT || isReleasedUp_VB_VIEW_LEFT || isReleasedUp_VB_VIEW_UP || isReleasedUp_VB_VIEW_DOWN;

    bool isPushedDown_VB_VIEW_RIGHT = pVbPlay->isPushedDown(VB_VIEW_RIGHT);
    bool isPushedDown_VB_VIEW_LEFT = pVbPlay->isPushedDown(VB_VIEW_LEFT);
    bool isPushedDown_VB_VIEW_UP = pVbPlay->isPushedDown(VB_VIEW_UP);
    bool isPushedDown_VB_VIEW_DOWN = pVbPlay->isPushedDown(VB_VIEW_DOWN);
    bool isPushedDown_VB_VIEW = isPushedDown_VB_VIEW_RIGHT || isPushedDown_VB_VIEW_LEFT || isPushedDown_VB_VIEW_UP || isPushedDown_VB_VIEW_DOWN;

    if (isPushedDown_VB_VIEW_LEFT) {
        pos_camera_pressed_ = pos_camera_;
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
                //出来ない
            } else if (pos_camera_ == VAM_POS_LEFT) {
                pos_camera_ = VAM_POS_BEHIND_LEFT;
            } else if (pos_camera_ == VAM_POS_TOP) {
                pos_camera_ = VAM_POS_RIGHT;
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                pos_camera_ = VAM_POS_RIGHT;
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            pos_camera_ = VAM_POS_RIGHT;
        }
    } else if (isPushedDown_VB_VIEW_RIGHT) {
        pos_camera_pressed_ = pos_camera_;
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
                pos_camera_ = VAM_POS_BEHIND_RIGHT;
            } else if (pos_camera_ == VAM_POS_LEFT) {
                //出来ない
            } else if (pos_camera_ == VAM_POS_TOP) {
                pos_camera_ = VAM_POS_LEFT;
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                pos_camera_ = VAM_POS_LEFT;
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            pos_camera_ = VAM_POS_LEFT;
        }
    } else if (isPushedDown_VB_VIEW_DOWN) {
        pos_camera_pressed_ = pos_camera_;
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
                pos_camera_ = VAM_POS_TOP;
            } else if (pos_camera_ == VAM_POS_LEFT) {
                pos_camera_ = VAM_POS_TOP;
            } else if (pos_camera_ == VAM_POS_TOP) {
                //出来ない
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                pos_camera_ = VAM_POS_BEHIND_BOTTOM;
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            pos_camera_ = VAM_POS_TOP;
        }
    } else if (isPushedDown_VB_VIEW_UP) {
        pos_camera_pressed_ = pos_camera_;
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
                pos_camera_ = VAM_POS_BOTTOM;
            } else if (pos_camera_ == VAM_POS_LEFT) {
                pos_camera_ = VAM_POS_BOTTOM;
            } else if (pos_camera_ == VAM_POS_TOP) {
                pos_camera_ = VAM_POS_BEHIND_TOP;
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                //出来ない
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            pos_camera_ = VAM_POS_BOTTOM;
        }
    }


    if (isReleasedUp_VB_VIEW_UP) {
        if (pVbPlay->isPushedUp(VB_VIEW_UP, 20)) {
            //チョン押しの場合、なにもしない（普通にビューポイント移動となる）
        } else {
            //長押し後離した場合、元のビューポイントへ戻る
            pos_camera_ = pos_camera_pressed_;
        }
    }
    if (isReleasedUp_VB_VIEW_DOWN) {
        if (pVbPlay->isPushedUp(VB_VIEW_DOWN, 20)) {
            //チョン押しの場合、なにもしない（普通にビューポイント移動となる）
        } else {
            //長押し後離した場合、元のビューポイントへ戻る
            pos_camera_ = pos_camera_pressed_;
        }
    }
    if (isReleasedUp_VB_VIEW_LEFT) {
        if (pVbPlay->isPushedUp(VB_VIEW_LEFT, 20)) {
            //チョン押しの場合、なにもしない（普通にビューポイント移動となる）
        } else {
            //長押し後離した場合、元のビューポイントへ戻る
            pos_camera_ = pos_camera_pressed_;
        }
    }
    if (isReleasedUp_VB_VIEW_RIGHT) {
        if (pVbPlay->isPushedUp(VB_VIEW_RIGHT, 20)) {
            //チョン押しの場合、なにもしない（普通にビューポイント移動となる）
        } else {
            //長押し後離した場合、元のビューポイントへ戻る
            pos_camera_ = pos_camera_pressed_;
        }
    }

//    //VB_VIEW離した時の処理
//    if (pVbPlay->isReleasedUp(VB_VIEW)) {
//        if (pVbPlay->isPushedUp(VB_VIEW, 20)) {
//            //チョン押しの場合、なにもしない（普通にビューポイント移動となる）
//        } else {
//            //長押し後離した場合、元のビューポイントへ戻る
//            if (pos_camera_ < VAM_POS_TO_BEHIND) { //背面ビューポイント以外への移動途中だった場合
//                //背面ビューポイントへ戻る。
//                pos_camera_ += VAM_POS_TO_BEHIND;
//            } else if (pos_camera_ > VAM_POS_TO_BEHIND) {//背面ビューポイントへの途中だった場合
//                //それぞれの元の対応ビューポイントへ戻る。
//                pos_camera_ -= VAM_POS_TO_BEHIND;
//            }
//        }
//    }

    //カメラの移動目標座標
    coord mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM;
    //カメラのビューポイントの移動目標座標
    coord mv_t_x_VP, mv_t_y_VP, mv_t_z_VP;

    //カメラの目標座標、ビューポイントの目標座標を設定
    static const coord Dx = PX_C(PROPERTY::GAME_BUFFER_WIDTH/4);
    static const int Ddx_hw = (int)((PROPERTY::GAME_BUFFER_WIDTH*LEN_UNIT/2) - (PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT/2));

    if (is_cam_pos_option_back_) { //TODO:オプション操作中のオプション[0]背面に回る
        coord d = dZ_camera_init_*0.6;
        GgafDxKuroko* pOptCtrler_pKuroko = pOptCtrler->getKuroko();
        mv_t_x_CAM = pOptCtrler->_x + pOptCtrler_pKuroko->_vX*-d;
        mv_t_y_CAM = pOptCtrler->_y + pOptCtrler_pKuroko->_vY*-d;
        mv_t_z_CAM = pOptCtrler->_z + pOptCtrler_pKuroko->_vZ*-d;
        mv_t_x_VP = pOptCtrler->_x + pOptCtrler_pKuroko->_vX*d;
        mv_t_y_VP = pOptCtrler->_y + pOptCtrler_pKuroko->_vY*d;
        mv_t_z_VP = pOptCtrler->_z + pOptCtrler_pKuroko->_vZ*d;

    } else {//通常時VAM
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
    //            mv_t_x_CAM = 0;
    //            mv_t_y_CAM = 0;
    //            mv_t_z_CAM = -dZ_camera_init_;
    //            mv_t_x_VP = 0;
    //            mv_t_y_VP = 0;
    //            mv_t_z_VP = 0;

                mv_t_x_CAM = -Dx + (-pMyShip_->_x-200000)*2;
                //↑ -200000 はカメラ移動位置、
                //   *2 は自機が後ろに下がった時のカメラのパン具合。
                //   この辺りの数値は納得いくまで調整を繰した。
                //   TODO:本当はゲーム領域の大きさから動的に計算できる。いつかそうしたい。
                if (-Dx > mv_t_x_CAM) {
                    mv_t_x_CAM = -Dx;
                } else if (mv_t_x_CAM > Dx/2) {
                    mv_t_x_CAM = Dx/2;
                }
                mv_t_y_CAM = pMyShip_->_y;
                mv_t_z_CAM = pMyShip_->_z - dZ_camera_init_;

                mv_t_x_VP = Dx - (-pMyShip_->_x-200000)*2;
                if (Dx < mv_t_x_VP) {
                    mv_t_x_VP = Dx;
                } else if ( mv_t_x_VP < -Dx/2) {
                    mv_t_x_VP = -Dx/2;
                }
                mv_t_y_VP = pMyShip_->_y;
                mv_t_z_VP = pMyShip_->_z-100000;
            } else if (pos_camera_ == VAM_POS_LEFT) {
                mv_t_x_CAM = -Dx + (-pMyShip_->_x-200000)*2;
                if (-Dx > mv_t_x_CAM) {
                    mv_t_x_CAM = -Dx;
                } else if (mv_t_x_CAM > Dx/2) {
                    mv_t_x_CAM = Dx/2;
                }
                mv_t_y_CAM = pMyShip_->_y;
                mv_t_z_CAM = pMyShip_->_z + dZ_camera_init_;
                mv_t_x_VP = Dx - (-pMyShip_->_x-200000)*2;
                if (Dx < mv_t_x_VP) {
                    mv_t_x_VP = Dx;
                } else if ( mv_t_x_VP < -Dx/2) {
                    mv_t_x_VP = -Dx/2;
                }
                mv_t_y_VP = pMyShip_->_y;
                mv_t_z_VP = pMyShip_->_z+100000;
            } else if (pos_camera_ == VAM_POS_TOP) {
                mv_t_x_CAM = -Dx - Ddx_hw + (-pMyShip_->_x-125000)*2;
                if ((-Dx - Ddx_hw) > mv_t_x_CAM) {
                    mv_t_x_CAM = -Dx - Ddx_hw;
                } else if (mv_t_x_CAM > (Dx + Ddx_hw)/2) {
                    mv_t_x_CAM = (Dx + Ddx_hw)/2;
                }
                mv_t_y_CAM = pMyShip_->_y + dZ_camera_init_ + Ddx_hw;
                mv_t_z_CAM = pMyShip_->_z;
                mv_t_x_VP = Dx + Ddx_hw - (-pMyShip_->_x-125000)*2;
                if (Dx + Ddx_hw < mv_t_x_VP) {
                    mv_t_x_VP = Dx + Ddx_hw;
                } else if ( mv_t_x_VP < -(Dx + Ddx_hw)/2) {
                    mv_t_x_VP = -(Dx + Ddx_hw)/2;
                }
                mv_t_y_VP = pMyShip_->_y;
                mv_t_z_VP = pMyShip_->_z;
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                mv_t_x_CAM = -Dx - Ddx_hw + (-pMyShip_->_x-125000)*2;
                if ((-Dx - Ddx_hw) > mv_t_x_CAM) {
                    mv_t_x_CAM = -Dx - Ddx_hw;
                } else if (mv_t_x_CAM > (Dx + Ddx_hw)/2) {
                    mv_t_x_CAM = (Dx + Ddx_hw)/2;
                }
                mv_t_y_CAM = pMyShip_->_y - dZ_camera_init_ - Ddx_hw;
                mv_t_z_CAM = pMyShip_->_z;
                mv_t_x_VP = Dx + Ddx_hw - (-pMyShip_->_x-125000)*2;
                if (Dx + Ddx_hw < mv_t_x_VP) {
                    mv_t_x_VP = Dx + Ddx_hw;
                } else if ( mv_t_x_VP < -(Dx + Ddx_hw)/2) {
                    mv_t_x_VP = -(Dx + Ddx_hw)/2;
                }
                mv_t_y_VP = pMyShip_->_y;
                mv_t_z_VP = pMyShip_->_z;
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            mv_t_x_CAM = pMyShip_->_x - (dZ_camera_init_*0.6);
            mv_t_y_CAM = pMyShip_->_y;
            mv_t_z_CAM = pMyShip_->_z;
            mv_t_x_VP = pMyShip_->_x + (dZ_camera_init_*2);
            mv_t_y_VP = pMyShip_->_y;
            mv_t_z_VP = pMyShip_->_z;
    //        if (pos_camera_ == VAM_POS_BEHIND_RIGHT) {
    //            mv_t_z_CAM -= Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_LEFT) {
    //            mv_t_z_CAM += Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_TOP) {
    //            mv_t_y_CAM += Dd;
    //        } else if (pos_camera_ == VAM_POS_BEHIND_BOTTOM) {
    //            mv_t_y_CAM -= Dd;
    //        }
        } else {
            throwGgafCriticalException("VamSysCamWorker::processBehavior() 不正なpos_camera_="<<pos_camera_);
        }
        //カメラの目標座標、ビューポイントの目標座標について、現在の動いている方向への若干画面寄りを行う。（ﾅﾝﾉｺｯﾁｬ）
        mv_t_z_CAM -= (pMyShip_->_z*0.08);
        mv_t_y_CAM -= (pMyShip_->_y*0.08);
    }

    //カメラ移動座標を制限。
    //自機移動範囲に応じて、画面端の感じを演出するため。(無くとも問題ない？)
    if (pos_camera_ < VAM_POS_TO_BEHIND) {
        if (pos_camera_ == VAM_POS_RIGHT) {
            if (mv_t_y_CAM > lim_CAM_top_) {
                mv_t_y_CAM = lim_CAM_top_;
            }
            if (mv_t_y_CAM < lim_CAM_bottom_ ) {
                mv_t_y_CAM = lim_CAM_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_LEFT) {
            if (mv_t_y_CAM > lim_CAM_top_) {
                mv_t_y_CAM = lim_CAM_top_;
            }
            if (mv_t_y_CAM < lim_CAM_bottom_ ) {
                mv_t_y_CAM = lim_CAM_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_TOP) {
            if (mv_t_z_CAM > lim_CAM_zleft_) {
                mv_t_z_CAM = lim_CAM_zleft_;
            }
            if (mv_t_z_CAM < lim_CAM_zright_) {
                mv_t_z_CAM = lim_CAM_zright_;
            }
        } else if (pos_camera_ == VAM_POS_BOTTOM) {
            if (mv_t_z_CAM > lim_CAM_zleft_) {
                mv_t_z_CAM = lim_CAM_zleft_;
            }
            if (mv_t_z_CAM < lim_CAM_zright_) {
                mv_t_z_CAM = lim_CAM_zright_;
            }
        }
    } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
        if (mv_t_y_CAM > lim_CAM_top_ - correction_height_) {
            mv_t_y_CAM = lim_CAM_top_ - correction_height_;
        }
        if (mv_t_y_CAM < lim_CAM_bottom_ + correction_height_) {
            mv_t_y_CAM = lim_CAM_bottom_ + correction_height_;
        }
        if (mv_t_z_CAM > lim_CAM_zleft_ - correction_width_) {
            mv_t_z_CAM = lim_CAM_zleft_ - correction_width_;
        }
        if (mv_t_z_CAM < lim_CAM_zright_ + correction_width_) {
            mv_t_z_CAM = lim_CAM_zright_ + correction_width_;
        }
    }
    //ビューポイントの移動座標を制限
    if (pos_camera_ < VAM_POS_TO_BEHIND) {
        if (pos_camera_ == VAM_POS_RIGHT) {
            if (mv_t_y_VP > lim_VP_top_) {
                mv_t_y_VP = lim_VP_top_;
            }
            if (mv_t_y_VP < lim_VP_bottom_ ) {
                mv_t_y_VP = lim_VP_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_LEFT) {
            if (mv_t_y_VP > lim_VP_top_) {
                mv_t_y_VP = lim_VP_top_;
            }
            if (mv_t_y_VP < lim_VP_bottom_ ) {
                mv_t_y_VP = lim_VP_bottom_;
            }
        } else if (pos_camera_ == VAM_POS_TOP) {
            if (mv_t_z_VP > lim_VP_zleft_) {
                mv_t_z_VP = lim_VP_zleft_;
            }
            if (mv_t_z_VP < lim_VP_zright_) {
                mv_t_z_VP = lim_VP_zright_;
            }
        } else if (pos_camera_ == VAM_POS_BOTTOM) {
            if (mv_t_z_VP > lim_VP_zleft_) {
                mv_t_z_VP = lim_VP_zleft_;
            }
            if (mv_t_z_VP < lim_VP_zright_) {
                mv_t_z_VP = lim_VP_zright_;
            }
        }
    } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
        if (mv_t_y_VP > lim_VP_top_ - correction_height_) {
            mv_t_y_VP = lim_VP_top_ - correction_height_;
        }
        if (mv_t_y_VP < lim_VP_bottom_ + correction_height_) {
            mv_t_y_VP = lim_VP_bottom_ + correction_height_;
        }
        if (mv_t_z_VP > lim_VP_zleft_ - correction_width_) {
            mv_t_z_VP = lim_VP_zleft_ - correction_width_;
        }
        if (mv_t_z_VP < lim_VP_zright_ + correction_width_) {
            mv_t_z_VP = lim_VP_zright_ + correction_width_;
        }
    }

    //ターゲットへ移動
    if (onChangeToActive() ||
        isPushedDown_VB_VIEW || isReleasedUp_VB_VIEW ||
        mv_t_x_CAM_prev_ != mv_t_x_CAM ||
        mv_t_y_CAM_prev_ != mv_t_y_CAM ||
        mv_t_z_CAM_prev_ != mv_t_z_CAM ) {


        //VB_VIEW押した時の処理
//        if (pVbPlay->isBeingPressed(VB_VIEW)) {
        if (isBeingPressed_VB_VIEW) {
            //VB_VIEWを押しっぱなし中は、ゆっくりな移動速度に制限
            GgafDxAxesMover* pCamAxMvr = pCam_->pAxsMver_;
            pCamAxMvr->setZeroVxyzMvAcce();
            pCamAxMvr->setVxyzMvVelo(
                    pCamAxMvr->_velo_vx_mv*0.1,
                    pCamAxMvr->_velo_vy_mv*0.1,
                    pCamAxMvr->_velo_vz_mv*0.1);
            GgafDxAxesMover* pVpAxMvr = pVp_->pAxsMver_;
            pVpAxMvr->setZeroVxyzMvAcce();
            pVpAxMvr->setVxyzMvVelo(
                    pVpAxMvr->_velo_vx_mv*0.1,
                    pVpAxMvr->_velo_vy_mv*0.1,
                    pVpAxMvr->_velo_vz_mv*0.1);
            cam_mv_frame_ = cam_mv_frame_base_ * 20;
        } else {
            cam_mv_frame_ = cam_mv_frame_base_;
            if (MAX3(ABS(mv_t_x_CAM - pCam_->_x),
                     ABS(mv_t_y_CAM - pCam_->_y),
                     ABS(mv_t_z_CAM - pCam_->_z) ) > PX_C(4000)) {
                cam_mv_frame_ = cam_mv_frame_base_ * 3; //遠方の場合、到達時間に少し余裕を持つ
            } else if ( pos_camera_ > VAM_POS_TO_BEHIND &&
                mv_t_x_CAM_prev_ == mv_t_x_CAM &&
                    (   mv_t_y_CAM_prev_ != mv_t_y_CAM ||
                        mv_t_z_CAM_prev_ != mv_t_z_CAM   )
            ) {
                cam_mv_frame_ = cam_mv_frame_base_ * 0.2 + 1;
            }
        }

//        _TRACE_("VamSysCamWorker::processBehavior() ターゲットへ移動 cam_mv_frame_="<<cam_mv_frame_<<" pos_camera_="<<pos_camera_);
        //ターゲットへカメラ移動
        if (pos_camera_ < VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_RIGHT) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.9, 0.5, 0.1); //円弧を描くようなスライド
            } else if (pos_camera_ == VAM_POS_LEFT) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.9, 0.5, 0.1);
            } else if (pos_camera_ == VAM_POS_TOP) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.9, 0.1, 0.5);
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.9, 0.1, 0.5);
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            if (pos_camera_ == VAM_POS_BEHIND_RIGHT) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.1, 0.5, 0.9);
            } else if (pos_camera_ == VAM_POS_BEHIND_LEFT) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.1, 0.5, 0.9);
            } else if (pos_camera_ == VAM_POS_BEHIND_TOP) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.1, 0.9, 0.5);
            } else if (pos_camera_ == VAM_POS_BEHIND_BOTTOM) {
                slideMvCamTo(mv_t_x_CAM, mv_t_y_CAM, mv_t_z_CAM,
                             cam_mv_frame_,
                             0.1, 0.9, 0.5);
            }
        } else {
            throwGgafCriticalException("VamSysCamWorker::processBehavior() どこにカメラが行ったのかわかりません(1)");
        }
        //ターゲットへVP移動
        slideMvVpTo(mv_t_x_VP,
                    mv_t_y_VP,
                    mv_t_z_VP, cam_mv_frame_);

        //UPを補正
        if (onChangeToActive() || isPushedDown_VB_VIEW || isReleasedUp_VB_VIEW) {
            if (pos_camera_ == VAM_POS_RIGHT || pos_camera_ == VAM_POS_LEFT || pos_camera_ > VAM_POS_TO_BEHIND) {
                pCam_->slideUpCamTo(Camera::FACE_TOP, cam_mv_frame_/2);
            } else if (pos_camera_ == VAM_POS_TOP) {
                if (pCam_->vcv_face_ == Camera::FACE_NZZ) {
                    pCam_->slideUpCamTo(Camera::FACE_BOTTOM, cam_mv_frame_/2);
                } else {
                    pCam_->slideUpCamTo(Camera::FACE_PZZ, cam_mv_frame_/2);
                }
            } else if (pos_camera_ == VAM_POS_BOTTOM) {
                if (pCam_->vcv_face_ == Camera::FACE_NZZ) {
                    pCam_->slideUpCamTo(Camera::FACE_BOTTOM, cam_mv_frame_/2);
                } else {
                    pCam_->slideUpCamTo(Camera::FACE_NZZ, cam_mv_frame_/2);
                }
            } else {
                throwGgafCriticalException("VamSysCamWorker::processBehavior() どこにカメラが行ったのかわかりません(2)");
            }
        }
    }


    pos_camera_prev_ = pos_camera_;
    mv_t_x_CAM_prev_ = mv_t_x_CAM;
    mv_t_y_CAM_prev_ = mv_t_y_CAM;
    mv_t_z_CAM_prev_ = mv_t_z_CAM;
}
VamSysCamWorker::~VamSysCamWorker() {
}
