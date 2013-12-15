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
}
void VamSysCamWorker::initialize() {
    Camera* pCam = P_CAM;
    ViewPoint* pVP = (ViewPoint*)(pCam->getViewPoint());

    //初期カメラZ位置
    dZ_camera_init_ = -DX_C(pCam->_cameraZ_org);


    //画面背後用範囲差分
    //背後のZ座標はdZ_camera_init_/2
    correction_width_ = 0;//(PROPERTY::GAME_BUFFER_WIDTH*LEN_UNIT/2)/4;
    correction_height_ = 0;//(PROPERTY::GAME_BUFFER_HEIGHT*LEN_UNIT/2)/4;

    pos_camera_ = VAM_POS_RIGHT;

    cam_velo_renge_ = 30000;
    pCam->pAxsMver_->forceVxyzMvVeloRange(-cam_velo_renge_, cam_velo_renge_);
    pVP->pAxsMver_->forceVxyzMvVeloRange(-cam_velo_renge_, cam_velo_renge_);

    stop_renge_ = 60000;
    angXY_nowCamUp_ = UTIL::getAngle2D(pCam->_pVecCamUp->x, pCam->_pVecCamUp->y);
    stop_dZ_ = 0;
    stop_dY_ = 0;
    _TRACE_("VamSysCamWorker::initialize() this="<<this);
    dump();
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
    GgafDxAxesMover* const pCamAxesMover = pCam->pAxsMver_;
    GgafDxAxesMover* const pVpAxesMover = pVP->pAxsMver_;

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
    //カメラの目標UPアングル値
    angle move_target_XY_CAM_UP;

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
        move_target_XY_CAM_UP = UTIL::simplifyAng(pOptCtrler->_pKuroko->_angRzMv+D90ANG);

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
                move_target_XY_CAM_UP = D90ANG;
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
                move_target_XY_CAM_UP = D90ANG;
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
                if (pCam->_x < pVP->_x) {
                    move_target_XY_CAM_UP = D45ANG;
                } else {
                    move_target_XY_CAM_UP = D315ANG;
                }
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
                if (pCam->_x < pVP->_x) {
                    move_target_XY_CAM_UP = D135ANG;
                } else {
                    move_target_XY_CAM_UP = D255ANG;
                }
            }
        } else if (pos_camera_ > VAM_POS_TO_BEHIND) {
            move_target_x_CAM = pMyShip_->_x - (dZ_camera_init_*0.6);
            move_target_y_CAM = pMyShip_->_y;
            move_target_z_CAM = pMyShip_->_z;
            move_target_x_VP = pMyShip_->_x + (dZ_camera_init_*2);
            move_target_y_VP = pMyShip_->_y;
            move_target_z_VP = pMyShip_->_z;
            move_target_XY_CAM_UP = D90ANG;
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

//
//    GgafDxGeoElem* pGeoMyShip = pMyShip_->pRing_GeoHistory_->getCurrent(); //現在の自機座標
//    GgafDxGeoElem* pGeoMyShip_prev= pMyShip_->pRing_GeoHistory_->getPrev(); //現在のひとつ前のフレームの自機座標
//    stop_dZ_ += (pGeoMyShip_prev->_z - pGeoMyShip->_z)*0.1; //自機の移動量の1割の移動量を
//    stop_dY_ += (pGeoMyShip_prev->_y - pGeoMyShip->_y)*0.1; //カメラの目標座標に加算してます。
//    move_target_z_CAM += stop_dZ_;
//    move_target_y_CAM += stop_dY_;


    int cam_velo_renge;  //カメラの移動速度の最大、最小敷居値
    //VB_VIEW押した時の処理
    if (pVbPlay->isBeingPressed(VB_VIEW)) {
        //VB_VIEWを押しっぱなし中は、ゆっくりな移動速度に制限
        cam_velo_renge = cam_velo_renge_ * 0.02;
    } else {
        //通常のカメラ移動速度制限にする
        cam_velo_renge = cam_velo_renge_;
    }
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
    //カメラの移動速度の最大、最小制限を設定
    pCamAxesMover->forceVxyzMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVpAxesMover->forceVxyzMvVeloRange(-cam_velo_renge, cam_velo_renge);

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

    //カメラ、及びビューポイントの移動速度を求める。

    //カメラの目標座標までの各軸の距離（座標差分）
    int dX_CAM = move_target_x_CAM - pCam->_x;
    int dY_CAM = move_target_y_CAM - pCam->_y;
    int dZ_CAM = move_target_z_CAM - pCam->_z;
    //ビューポイントの目標座標までの各軸の距離（座標差分）
    int dX_VP = move_target_x_VP - pVP->_x;
    int dY_VP = move_target_y_VP - pVP->_y;
    int dZ_VP = move_target_z_VP - pVP->_z;
    velo veloVxRenge = 4000;
    velo veloVyRenge = 4000;
    velo veloVzRenge = 4000;
    if (pos_camera_ == VAM_POS_BEHIND_RIGHT || pos_camera_ == VAM_POS_BEHIND_LEFT) {
        if (pMyShip_->_x > -Dx) {
            //ややZ軸移動を早くする
            veloVzRenge *= 1.8;
            veloVxRenge *= 0.2;
        } else {
            //ややZ軸移動を遅くする
            veloVzRenge *= 0.2;
            veloVxRenge *= 1.8;
        }
    } else if (pos_camera_ == VAM_POS_BEHIND_TOP || pos_camera_ == VAM_POS_BEHIND_BOTTOM) {
        if (pMyShip_->_x > -Dx) {
            //ややY軸移動を早くする
            veloVyRenge *= 1.8;
            veloVxRenge *= 0.2;
        } else {
            //ややY軸移動を遅くする
            veloVyRenge *= 0.2;
            veloVxRenge *= 1.8;
        }
    } else if (pos_camera_ == VAM_POS_RIGHT || pos_camera_ == VAM_POS_LEFT) {
        if (pMyShip_->_x > -Dx) {
            //ややX軸移動を早くする
            veloVxRenge *= 1.8;
            veloVzRenge *= 0.2;
        } else {
            //ややX軸移動を遅くする
            veloVxRenge *= 0.2;
            veloVzRenge *= 1.8;
        }
    } else if (pos_camera_ == VAM_POS_TOP || pos_camera_ == VAM_POS_BOTTOM) {
        if (pMyShip_->_x > -Dx) {
            //ややX軸移動を早くする
            veloVxRenge *= 1.8;
            veloVyRenge *= 0.2;
        } else {
            //ややX軸移動を遅くする
            veloVxRenge *= 0.2;
            veloVyRenge *= 1.8;
        }
    }

    velo last_CAM_veloVxMv = pCamAxesMover->_veloVxMv;
    velo  new_CAM_veloVxMv = pMyShip_->iMoveSpeed_*(dX_CAM*1.0 / stop_renge_);
    if (last_CAM_veloVxMv-veloVxRenge <= new_CAM_veloVxMv && new_CAM_veloVxMv <= last_CAM_veloVxMv+veloVxRenge) {
        pCamAxesMover->setVxMvVelo(new_CAM_veloVxMv);
    } else {
        if (last_CAM_veloVxMv-veloVxRenge > new_CAM_veloVxMv) {
            pCamAxesMover->setVxMvVelo(last_CAM_veloVxMv-veloVxRenge);
        } else if (new_CAM_veloVxMv > last_CAM_veloVxMv+veloVxRenge) {
            pCamAxesMover->setVxMvVelo(last_CAM_veloVxMv+veloVxRenge);
        }
    }
    velo last_VP_veloVxMv = pVpAxesMover->_veloVxMv;
    velo  new_VP_veloVxMv = pMyShip_->iMoveSpeed_*(dX_VP*1.0 / stop_renge_);
    if (last_VP_veloVxMv-veloVxRenge <= new_VP_veloVxMv && new_VP_veloVxMv <= last_VP_veloVxMv+veloVxRenge) {
        pVpAxesMover->setVxMvVelo(new_VP_veloVxMv);
    } else {
        if (last_VP_veloVxMv-veloVxRenge > new_VP_veloVxMv) {
            pVpAxesMover->setVxMvVelo(last_VP_veloVxMv-veloVxRenge);
        } else if (new_VP_veloVxMv > last_VP_veloVxMv+veloVxRenge) {
            pVpAxesMover->setVxMvVelo(last_VP_veloVxMv+veloVxRenge);
        }
    }

    velo last_CAM_veloVyMv = pCamAxesMover->_veloVyMv;
    velo  new_CAM_veloVyMv = pMyShip_->iMoveSpeed_*(dY_CAM*1.0 / stop_renge_);
    if (last_CAM_veloVyMv-veloVyRenge <= new_CAM_veloVyMv && new_CAM_veloVyMv <= last_CAM_veloVyMv+veloVyRenge) {
        pCamAxesMover->setVyMvVelo(new_CAM_veloVyMv);
    } else {
        if (last_CAM_veloVyMv-veloVyRenge > new_CAM_veloVyMv) {
            pCamAxesMover->setVyMvVelo(last_CAM_veloVyMv-veloVyRenge);
        } else if (new_CAM_veloVyMv > last_CAM_veloVyMv+veloVyRenge) {
            pCamAxesMover->setVyMvVelo(last_CAM_veloVyMv+veloVyRenge);
        }
    }
    velo last_VP_veloVyMv = pVpAxesMover->_veloVyMv;
    velo  new_VP_veloVyMv = pMyShip_->iMoveSpeed_*(dY_VP*1.0 / stop_renge_);
    if (last_VP_veloVyMv-veloVyRenge <= new_VP_veloVyMv && new_VP_veloVyMv <= last_VP_veloVyMv+veloVyRenge) {
        pVpAxesMover->setVyMvVelo(new_VP_veloVyMv);
    } else {
        if (last_VP_veloVyMv-veloVyRenge > new_VP_veloVyMv) {
            pVpAxesMover->setVyMvVelo(last_VP_veloVyMv-veloVyRenge);
        } else if (new_VP_veloVyMv > last_VP_veloVyMv+veloVyRenge) {
            pVpAxesMover->setVyMvVelo(last_VP_veloVyMv+veloVyRenge);
        }
    }

    velo last_CAM_veloVzMv = pCamAxesMover->_veloVzMv;
    velo  new_CAM_veloVzMv = pMyShip_->iMoveSpeed_*(dZ_CAM*1.0 / stop_renge_);
    if (last_CAM_veloVzMv-veloVzRenge <= new_CAM_veloVzMv && new_CAM_veloVzMv <= last_CAM_veloVzMv+veloVzRenge) {
        pCamAxesMover->setVzMvVelo(new_CAM_veloVzMv);
    } else {
        if (last_CAM_veloVzMv-veloVzRenge > new_CAM_veloVzMv) {
            pCamAxesMover->setVzMvVelo(last_CAM_veloVzMv-veloVzRenge);
        } else if (new_CAM_veloVzMv > last_CAM_veloVzMv+veloVzRenge) {
            pCamAxesMover->setVzMvVelo(last_CAM_veloVzMv+veloVzRenge);
        }
    }

    velo last_VP_veloVzMv = pVpAxesMover->_veloVzMv;
    velo  new_VP_veloVzMv = pMyShip_->iMoveSpeed_*(dZ_VP*1.0 / stop_renge_);
    if (last_VP_veloVzMv-veloVzRenge <= new_VP_veloVzMv && new_VP_veloVzMv <= last_VP_veloVzMv+veloVzRenge) {
        pVpAxesMover->setVzMvVelo(new_VP_veloVzMv);
    } else {
        if (last_VP_veloVzMv-veloVzRenge > new_VP_veloVzMv) {
            pVpAxesMover->setVzMvVelo(last_VP_veloVzMv-veloVzRenge);
        } else if (new_VP_veloVzMv > last_VP_veloVzMv+veloVzRenge) {
            pVpAxesMover->setVzMvVelo(last_VP_veloVzMv+veloVzRenge);
        }
    }

    //カメラのUPを計算
    angvelo angvelo_cam_up = cam_velo_renge/20; //cam_velo_rengeはVB_VIEW押しっぱで超低速になる方の速度
    if (angXY_nowCamUp_ != move_target_XY_CAM_UP) {
        angle da = UTIL::getAngDiff(angXY_nowCamUp_, move_target_XY_CAM_UP);
        if (-angvelo_cam_up < da && da < angvelo_cam_up) {
            angXY_nowCamUp_ = move_target_XY_CAM_UP;
        } else {
            angXY_nowCamUp_ += (angvelo_cam_up * SGN(da));
        }
        angXY_nowCamUp_ = UTIL::simplifyAng(angXY_nowCamUp_);
        pCam->_pVecCamUp->x = ANG_COS(angXY_nowCamUp_);
        pCam->_pVecCamUp->y = ANG_SIN(angXY_nowCamUp_);
        pCam->_pVecCamUp->z = 0.0f;
    }

//    _TRACE_(getActiveFrame()<<","<<dX_CAM<<","<<dY_CAM<<","<<dZ_CAM<<","<<pCam->_x<<","<<pCam->_y<<","<<pCam->_z<<","<<last_CAM_veloVxMv<<","<<new_CAM_veloVxMv<<","<<last_CAM_veloVyMv<<","<<new_CAM_veloVyMv<<","<<last_CAM_veloVzMv<<","<<new_CAM_veloVzMv<<","<<pCamAxesMover->_veloVxMv<<","<<pCamAxesMover->_veloVyMv<<","<<pCamAxesMover->_veloVzMv);

}
VamSysCamWorker::~VamSysCamWorker() {
}
