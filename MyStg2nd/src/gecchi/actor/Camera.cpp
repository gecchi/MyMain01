#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Camera::Camera(const char* prm_name, float prm_rad_fovX, float prm_dep) : DefaultCamera(prm_name, prm_rad_fovX, prm_dep) {
    _class_name = "Camera";
}
void Camera::initialize() {
    DefaultCamera::initialize();


    //初期カメラZ位置
    _dZ_camera_init = -1 * pCAM->_cameraZ_org * LEN_UNIT * PX_UNIT;


    //画面背後用範囲差分
    //背後のZ座標は_dZ_camera_init/2
    _correction_width = 0;//(GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)/4;
    _correction_height = 0;//(GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2)/4;

    _pos_camera = CAM_POS_RIGHT;
    GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;
//    pCAM->_X = 0;
//    pCAM->_Y = 0;
//    pCAM->_Z = 0;
//    pCAM->setViewPoint(0,0,0);
//    pCAM->_pMover->setMvAng(0,0,0);

    _cam_velo_renge = 30000;
    pCAM->_pMover->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pCAM->_pMover->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pCAM->_pMover->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pMover->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pMover->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pMover->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);

    _stop_renge = 60000;
    _angXY_nowCamUp = ANGLE90;
    _stop_dZ = 0;
    _stop_dY = 0;
}




void Camera::processBehavior() {

    DefaultCamera::processBehavior();

    //ゲーム内カメラワーク処理
    if (pMYSHIP == NULL) {
        return; //顧問シーンが未だならカメラワーク禁止
    } else {
        //初期カメラ移動範囲制限
        float revise = 0.7; //斜めから見るので補正値を掛ける。1.0の場合は原点からでドンピシャ。これは微調整を繰り返した
        _lim_CAM_top     = MyShip::_lim_top     - (GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2)*revise;
        _lim_CAM_bottom  = MyShip::_lim_bottom  + (GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2)*revise;
        _lim_CAM_front   = MyShip::_lim_front   - (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
        _lim_CAM_behaind = MyShip::_lim_behaind + (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
        _lim_CAM_zleft   = MyShip::_lim_zleft   - (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
        _lim_CAM_zright  = MyShip::_lim_zright  + (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;

        _lim_VP_top     = MyShip::_lim_top     - (GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2)*revise;
        _lim_VP_bottom  = MyShip::_lim_bottom  + (GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2)*revise;
        _lim_VP_front   = MyShip::_lim_front   - (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
        _lim_VP_behaind = MyShip::_lim_behaind + (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
        _lim_VP_zleft   = MyShip::_lim_zleft   - (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
        _lim_VP_zright  = MyShip::_lim_zright  + (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
    }
    GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;

    //カメラ位置番号を決定処理
    if (VB_PLAY->isPushedDown(VB_VIEW)) {
        _TRACE_("VB_VIEW!! now _pos_camera="<<_pos_camera);
        if (_pos_camera < CAM_POS_TO_BEHIND) { //背面ビューポイントではない場合、
            _pos_camera += CAM_POS_TO_BEHIND;  //それぞれの対応背面ビューポイントへ
        } else if (_pos_camera > CAM_POS_TO_BEHIND) {//背面ビューポイントの場合
            //方向入力により新たなビューポイントへ
            if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                _pos_camera = CAM_POS_LEFT;
            } else if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                _pos_camera = CAM_POS_RIGHT;
            } else if (VB_PLAY->isBeingPressed(VB_UP)) {
                _pos_camera = CAM_POS_BOTTOM;
            } else if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                _pos_camera = CAM_POS_TOP;
            } else {
                //方向未入力の場合、元のビューポイントへ
                _pos_camera -= CAM_POS_TO_BEHIND;
            }
        }
        _TRACE_("VB_VIEW!!  -> _pos_camera="<<_pos_camera);
    }

    //カメラの移動目標座標
    int move_target_X_CAM, move_target_Y_CAM, move_target_Z_CAM;
    //カメラのビューポイントの移動目標座標
    int move_target_X_VP, move_target_Y_VP, move_target_Z_VP;
    //カメラの目標UPアングル値
    angle move_target_XY_CAM_UP;

    //カメラの目標座標、ビューポイントの目標座標を設定
    static int Dx = (int)((GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)/4*2);
    static int Ddx_hw = (int)((GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2) - (GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2));
    static int Dd = 30000;
    if (_pos_camera < CAM_POS_TO_BEHIND) {
        if (_pos_camera == CAM_POS_RIGHT) {
//            move_target_X_CAM = 0;
//            move_target_Y_CAM = 0;
//            move_target_Z_CAM = -_dZ_camera_init;
//            move_target_X_VP = 0;
//            move_target_Y_VP = 0;
//            move_target_Z_VP = 0;

            move_target_X_CAM = -Dx + (-pMYSHIP->_X-180000)*2;
            //↑ -180000 はカメラ移動位置、
            //   *2 は自機が後ろに下がった時のカメラのパン具合。
            //   この辺りの数値は納得いくまで調整を繰した。
            //   TODO:ゲーム領域の大きさから計算で求ることは断念。いつかそうしたい。
            if (-Dx > move_target_X_CAM) {
                move_target_X_CAM = -Dx;
            } else if (move_target_X_CAM > Dx/2) {
                move_target_X_CAM = Dx/2;
            }
            move_target_Y_CAM = pMYSHIP->_Y;
            move_target_Z_CAM = pMYSHIP->_Z - _dZ_camera_init;
            move_target_X_VP = Dx - (-pMYSHIP->_X-180000)*2;
            if (Dx < move_target_X_VP) {
                move_target_X_VP = Dx;
            } else if ( move_target_X_VP < -Dx/2) {
                move_target_X_VP = -Dx/2;
            }
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
            move_target_XY_CAM_UP = ANGLE90;
        } else if (_pos_camera == CAM_POS_LEFT) {
            move_target_X_CAM = -Dx + (-pMYSHIP->_X-180000)*2;
            if (-Dx > move_target_X_CAM) {
                move_target_X_CAM = -Dx;
            } else if (move_target_X_CAM > Dx/2) {
                move_target_X_CAM = Dx/2;
            }
            move_target_Y_CAM = pMYSHIP->_Y;
            move_target_Z_CAM = pMYSHIP->_Z + _dZ_camera_init;
            move_target_X_VP = Dx - (-pMYSHIP->_X-180000)*2;
            if (Dx < move_target_X_VP) {
                move_target_X_VP = Dx;
            } else if ( move_target_X_VP < -Dx/2) {
                move_target_X_VP = -Dx/2;
            }
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
            move_target_XY_CAM_UP = ANGLE90;
        } else if (_pos_camera == CAM_POS_TOP) {
            move_target_X_CAM = -Dx - Ddx_hw + (-pMYSHIP->_X-125000)*2;
            if ((-Dx - Ddx_hw) > move_target_X_CAM) {
                move_target_X_CAM = -Dx - Ddx_hw;
            } else if (move_target_X_CAM > (Dx + Ddx_hw)/2) {
                move_target_X_CAM = (Dx + Ddx_hw)/2;
            }
            move_target_Y_CAM = pMYSHIP->_Y + _dZ_camera_init + Ddx_hw;
            move_target_Z_CAM = pMYSHIP->_Z;
            move_target_X_VP = Dx + Ddx_hw - (-pMYSHIP->_X-125000)*2;
            if (Dx + Ddx_hw < move_target_X_VP) {
                move_target_X_VP = Dx + Ddx_hw;
            } else if ( move_target_X_VP < -(Dx + Ddx_hw)/2) {
                move_target_X_VP = -(Dx + Ddx_hw)/2;
            }
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
            if (pCAM->_X < pVP->_X) {
                move_target_XY_CAM_UP = ANGLE45;
            } else {
                move_target_XY_CAM_UP = ANGLE315;
            }
        } else if (_pos_camera == CAM_POS_BOTTOM) {
            move_target_X_CAM = -Dx - Ddx_hw + (-pMYSHIP->_X-125000)*2;
            if ((-Dx - Ddx_hw) > move_target_X_CAM) {
                move_target_X_CAM = -Dx - Ddx_hw;
            } else if (move_target_X_CAM > (Dx + Ddx_hw)/2) {
                move_target_X_CAM = (Dx + Ddx_hw)/2;
            }
            move_target_Y_CAM = pMYSHIP->_Y - _dZ_camera_init - Ddx_hw;
            move_target_Z_CAM = pMYSHIP->_Z;
            move_target_X_VP = Dx + Ddx_hw - (-pMYSHIP->_X-125000)*2;
            if (Dx + Ddx_hw < move_target_X_VP) {
                move_target_X_VP = Dx + Ddx_hw;
            } else if ( move_target_X_VP < -(Dx + Ddx_hw)/2) {
                move_target_X_VP = -(Dx + Ddx_hw)/2;
            }
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
            if (pCAM->_X < pVP->_X) {
                move_target_XY_CAM_UP = ANGLE135;
            } else {
                move_target_XY_CAM_UP = ANGLE225;
            }
        }
    } else if (_pos_camera > CAM_POS_TO_BEHIND) {
        move_target_X_CAM = pMYSHIP->_X - (_dZ_camera_init*0.6);
        move_target_Y_CAM = pMYSHIP->_Y;
        move_target_Z_CAM = pMYSHIP->_Z;
        move_target_X_VP = pMYSHIP->_X + (_dZ_camera_init);
        move_target_Y_VP = pMYSHIP->_Y;
        move_target_Z_VP = pMYSHIP->_Z;
        move_target_XY_CAM_UP = ANGLE90;
//        if (_pos_camera == CAM_POS_BEHIND_RIGHT) {
//            move_target_Z_CAM -= Dd;
//        } else if (_pos_camera == CAM_POS_BEHIND_LEFT) {
//            move_target_Z_CAM += Dd;
//        } else if (_pos_camera == CAM_POS_BEHIND_TOP) {
//            move_target_Y_CAM += Dd;
//        } else if (_pos_camera == CAM_POS_BEHIND_BOTTOM) {
//            move_target_Y_CAM -= Dd;
//        }
    } else {
        throwGgafCriticalException("World::processBehavior() 不正な_pos_camera="<<_pos_camera);
    }
    //カメラの目標座標、ビューポイントの目標座標について、現在の動いている方向への若干画面寄りを行う。（ﾅﾝﾉｺｯﾁｬ）
    GeoElement* pGeoMyShip = pMYSHIP->_pRing_GeoHistory->getCurrent(); //現在の自機座標
    GeoElement* pGeoMyShip_prev= pMYSHIP->_pRing_GeoHistory->getPrev(); //現在のひとつ前のフレームの自機座標
    _stop_dZ += (pGeoMyShip_prev->_Z - pGeoMyShip->_Z)*0.1; //自機の移動量の1割の移動量を
    _stop_dY += (pGeoMyShip_prev->_Y - pGeoMyShip->_Y)*0.1; //カメラの目標座標に加算してます。
    move_target_Z_CAM += _stop_dZ;
    move_target_Y_CAM += _stop_dY;


    int cam_velo_renge;  //カメラの移動速度の最大、最小敷居値
    //VB_VIEW押した時の処理
    if (VB_PLAY->isBeingPressed(VB_VIEW)) {
        //VB_VIEWを押しっぱなし中は、ゆっくりな移動速度に制限
        cam_velo_renge = _cam_velo_renge / 100;
    } else {
        //通常のカメラ移動速度制限にする
        cam_velo_renge = _cam_velo_renge;
    }
    //VB_VIEW離した時の処理
    if (VB_PLAY->isReleasedUp(VB_VIEW)) {
        if (VB_PLAY->isPushedUp(VB_VIEW, 20)) {
            //チョン押しの場合、なにもしない（普通にビューポイント移動となる）
        } else {
            //長押しをしたた後、VB_VIEW離した時
            if (_pos_camera < CAM_POS_TO_BEHIND) { //背面ビューポイントではない場合、
                //それぞれの元の対応ビューポイントへ戻る。
                _pos_camera += CAM_POS_TO_BEHIND;
            } else if (_pos_camera > CAM_POS_TO_BEHIND) {//背面ビューポイントだった場合
                //それぞれの元の対応背面ビューポイントへ戻る。
                _pos_camera -= CAM_POS_TO_BEHIND;
            }
        }
    }
    //カメラの移動速度の最大、最小制限を設定
    pCAM->_pMover->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCAM->_pMover->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCAM->_pMover->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMover->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMover->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMover->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);

    //カメラとビューポイントの移動座標を制限。
    //自機移動範囲に応じて、画面端の感じを演出するため。(無くとも問題ない？)
    if (_pos_camera < CAM_POS_TO_BEHIND) {
        if (_pos_camera == CAM_POS_RIGHT) {
            if (move_target_Y_CAM > _lim_CAM_top) {
                move_target_Y_CAM = _lim_CAM_top;
            }
            if (move_target_Y_CAM < _lim_CAM_bottom ) {
                move_target_Y_CAM = _lim_CAM_bottom;
            }
        } else if (_pos_camera == CAM_POS_LEFT) {
            if (move_target_Y_CAM > _lim_CAM_top) {
                move_target_Y_CAM = _lim_CAM_top;
            }
            if (move_target_Y_CAM < _lim_CAM_bottom ) {
                move_target_Y_CAM = _lim_CAM_bottom;
            }
        } else if (_pos_camera == CAM_POS_TOP) {
            if (move_target_Z_CAM > _lim_CAM_zleft) {
                move_target_Z_CAM = _lim_CAM_zleft;
            }
            if (move_target_Z_CAM < _lim_CAM_zright) {
                move_target_Z_CAM = _lim_CAM_zright;
            }
        } else if (_pos_camera == CAM_POS_BOTTOM) {
            if (move_target_Z_CAM > _lim_CAM_zleft) {
                move_target_Z_CAM = _lim_CAM_zleft;
            }
            if (move_target_Z_CAM < _lim_CAM_zright) {
                move_target_Z_CAM = _lim_CAM_zright;
            }
        }
    } else if (_pos_camera > CAM_POS_TO_BEHIND) {
        if (move_target_Y_CAM > _lim_CAM_top - _correction_height) {
            move_target_Y_CAM = _lim_CAM_top - _correction_height;
        }
        if (move_target_Y_CAM < _lim_CAM_bottom + _correction_height) {
            move_target_Y_CAM = _lim_CAM_bottom + _correction_height;
        }
        if (move_target_Z_CAM > _lim_CAM_zleft - _correction_width) {
            move_target_Z_CAM = _lim_CAM_zleft - _correction_width;
        }
        if (move_target_Z_CAM < _lim_CAM_zright + _correction_width) {
            move_target_Z_CAM = _lim_CAM_zright + _correction_width;
        }
    }
    if (_pos_camera < CAM_POS_TO_BEHIND) {
        if (_pos_camera == CAM_POS_RIGHT) {
            if (move_target_Y_VP > _lim_VP_top) {
                move_target_Y_VP = _lim_VP_top;
            }
            if (move_target_Y_VP < _lim_VP_bottom ) {
                move_target_Y_VP = _lim_VP_bottom;
            }
        } else if (_pos_camera == CAM_POS_LEFT) {
            if (move_target_Y_VP > _lim_VP_top) {
                move_target_Y_VP = _lim_VP_top;
            }
            if (move_target_Y_VP < _lim_VP_bottom ) {
                move_target_Y_VP = _lim_VP_bottom;
            }
        } else if (_pos_camera == CAM_POS_TOP) {
            if (move_target_Z_VP > _lim_VP_zleft) {
                move_target_Z_VP = _lim_VP_zleft;
            }
            if (move_target_Z_VP < _lim_VP_zright) {
                move_target_Z_VP = _lim_VP_zright;
            }
        } else if (_pos_camera == CAM_POS_BOTTOM) {
            if (move_target_Z_VP > _lim_VP_zleft) {
                move_target_Z_VP = _lim_VP_zleft;
            }
            if (move_target_Z_VP < _lim_VP_zright) {
                move_target_Z_VP = _lim_VP_zright;
            }
        }
    } else if (_pos_camera > CAM_POS_TO_BEHIND) {
        if (move_target_Y_VP > _lim_VP_top - _correction_height) {
            move_target_Y_VP = _lim_VP_top - _correction_height;
        }
        if (move_target_Y_VP < _lim_VP_bottom + _correction_height) {
            move_target_Y_VP = _lim_VP_bottom + _correction_height;
        }
        if (move_target_Z_VP > _lim_VP_zleft - _correction_width) {
            move_target_Z_VP = _lim_VP_zleft - _correction_width;
        }
        if (move_target_Z_VP < _lim_VP_zright + _correction_width) {
            move_target_Z_VP = _lim_VP_zright + _correction_width;
        }
    }

    //カメラ、及びビューポイントの移動速度を求める。

    //カメラの目標座標までの各軸の距離（座標差分）
    int dX_CAM = move_target_X_CAM - pCAM->_X;
    int dY_CAM = move_target_Y_CAM - pCAM->_Y;
    int dZ_CAM = move_target_Z_CAM - pCAM->_Z;
    //ビューポイントの目標座標までの各軸の距離（座標差分）
    int dX_VP = move_target_X_VP - pVP->_X;
    int dY_VP = move_target_Y_VP - pVP->_Y;
    int dZ_VP = move_target_Z_VP - pVP->_Z;
    velo veloVxRenge = 4000;
    velo veloVyRenge = 4000;
    velo veloVzRenge = 4000;
    if (_pos_camera == CAM_POS_BEHIND_RIGHT || _pos_camera == CAM_POS_BEHIND_LEFT) {
        if (pMYSHIP->_X > -Dx) {
            //ややZ軸移動を早くする
            veloVzRenge *= 1.8;
            veloVxRenge *= 0.2;
        } else {
            //ややZ軸移動を遅くする
            veloVzRenge *= 0.2;
            veloVxRenge *= 1.8;
        }
    } else if (_pos_camera == CAM_POS_BEHIND_TOP || _pos_camera == CAM_POS_BEHIND_BOTTOM) {
        if (pMYSHIP->_X > -Dx) {
            //ややY軸移動を早くする
            veloVyRenge *= 1.8;
            veloVxRenge *= 0.2;
        } else {
            //ややY軸移動を遅くする
            veloVyRenge *= 0.2;
            veloVxRenge *= 1.8;
        }
    } else if (_pos_camera == CAM_POS_RIGHT || _pos_camera == CAM_POS_LEFT) {
        if (pMYSHIP->_X > -Dx) {
            //ややX軸移動を早くする
            veloVxRenge *= 1.8;
            veloVzRenge *= 0.2;
        } else {
            //ややX軸移動を遅くする
            veloVxRenge *= 0.2;
            veloVzRenge *= 1.8;
        }
    } else if (_pos_camera == CAM_POS_TOP || _pos_camera == CAM_POS_BOTTOM) {
        if (pMYSHIP->_X > -Dx) {
            //ややX軸移動を早くする
            veloVxRenge *= 1.8;
            veloVyRenge *= 0.2;
        } else {
            //ややX軸移動を遅くする
            veloVxRenge *= 0.2;
            veloVyRenge *= 1.8;
        }
    }
    velo last_CAM_veloVxMv = pCAM->_pMover->_veloVxMv;
    velo  new_CAM_veloVxMv = pMYSHIP->_iMoveSpeed*(dX_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVxMv-veloVxRenge <= new_CAM_veloVxMv && new_CAM_veloVxMv <= last_CAM_veloVxMv+veloVxRenge) {
        pCAM->_pMover->setVxMvVelo(new_CAM_veloVxMv);
    } else {
        if (last_CAM_veloVxMv-veloVxRenge > new_CAM_veloVxMv) {
            pCAM->_pMover->setVxMvVelo(last_CAM_veloVxMv-veloVxRenge);
        } else if (new_CAM_veloVxMv > last_CAM_veloVxMv+veloVxRenge) {
            pCAM->_pMover->setVxMvVelo(last_CAM_veloVxMv+veloVxRenge);
        }
    }
    velo last_VP_veloVxMv = pVP->_pMover->_veloVxMv;
    velo  new_VP_veloVxMv = pMYSHIP->_iMoveSpeed*(dX_VP*1.0 / _stop_renge);
    if (last_VP_veloVxMv-veloVxRenge <= new_VP_veloVxMv && new_VP_veloVxMv <= last_VP_veloVxMv+veloVxRenge) {
        pVP->_pMover->setVxMvVelo(new_VP_veloVxMv);
    } else {
        if (last_VP_veloVxMv-veloVxRenge > new_VP_veloVxMv) {
            pVP->_pMover->setVxMvVelo(last_VP_veloVxMv-veloVxRenge);
        } else if (new_VP_veloVxMv > last_VP_veloVxMv+veloVxRenge) {
            pVP->_pMover->setVxMvVelo(last_VP_veloVxMv+veloVxRenge);
        }
    }

    velo last_CAM_veloVyMv = pCAM->_pMover->_veloVyMv;
    velo  new_CAM_veloVyMv = pMYSHIP->_iMoveSpeed*(dY_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVyMv-veloVyRenge <= new_CAM_veloVyMv && new_CAM_veloVyMv <= last_CAM_veloVyMv+veloVyRenge) {
        pCAM->_pMover->setVyMvVelo(new_CAM_veloVyMv);
    } else {
        if (last_CAM_veloVyMv-veloVyRenge > new_CAM_veloVyMv) {
            pCAM->_pMover->setVyMvVelo(last_CAM_veloVyMv-veloVyRenge);
        } else if (new_CAM_veloVyMv > last_CAM_veloVyMv+veloVyRenge) {
            pCAM->_pMover->setVyMvVelo(last_CAM_veloVyMv+veloVyRenge);
        }
    }
    velo last_VP_veloVyMv = pVP->_pMover->_veloVyMv;
    velo  new_VP_veloVyMv = pMYSHIP->_iMoveSpeed*(dY_VP*1.0 / _stop_renge);
    if (last_VP_veloVyMv-veloVyRenge <= new_VP_veloVyMv && new_VP_veloVyMv <= last_VP_veloVyMv+veloVyRenge) {
        pVP->_pMover->setVyMvVelo(new_VP_veloVyMv);
    } else {
        if (last_VP_veloVyMv-veloVyRenge > new_VP_veloVyMv) {
            pVP->_pMover->setVyMvVelo(last_VP_veloVyMv-veloVyRenge);
        } else if (new_VP_veloVyMv > last_VP_veloVyMv+veloVyRenge) {
            pVP->_pMover->setVyMvVelo(last_VP_veloVyMv+veloVyRenge);
        }
    }

    velo last_CAM_veloVzMv = pCAM->_pMover->_veloVzMv;
    velo  new_CAM_veloVzMv = pMYSHIP->_iMoveSpeed*(dZ_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVzMv-veloVzRenge <= new_CAM_veloVzMv && new_CAM_veloVzMv <= last_CAM_veloVzMv+veloVzRenge) {
        pCAM->_pMover->setVzMvVelo(new_CAM_veloVzMv);
    } else {
        if (last_CAM_veloVzMv-veloVzRenge > new_CAM_veloVzMv) {
            pCAM->_pMover->setVzMvVelo(last_CAM_veloVzMv-veloVzRenge);
        } else if (new_CAM_veloVzMv > last_CAM_veloVzMv+veloVzRenge) {
            pCAM->_pMover->setVzMvVelo(last_CAM_veloVzMv+veloVzRenge);
        }
    }
    velo last_VP_veloVzMv = pVP->_pMover->_veloVzMv;
    velo  new_VP_veloVzMv = pMYSHIP->_iMoveSpeed*(dZ_VP*1.0 / _stop_renge);
    if (last_VP_veloVzMv-veloVzRenge <= new_VP_veloVzMv && new_VP_veloVzMv <= last_VP_veloVzMv+veloVzRenge) {
        pVP->_pMover->setVzMvVelo(new_VP_veloVzMv);
    } else {
        if (last_VP_veloVzMv-veloVzRenge > new_VP_veloVzMv) {
            pVP->_pMover->setVzMvVelo(last_VP_veloVzMv-veloVzRenge);
        } else if (new_VP_veloVzMv > last_VP_veloVzMv+veloVzRenge) {
            pVP->_pMover->setVzMvVelo(last_VP_veloVzMv+veloVzRenge);
        }
    }

    //カメラのUPを計算
    if (_angXY_nowCamUp != move_target_XY_CAM_UP) {
        //_TRACE_("_angXY_nowCamUp="<<_angXY_nowCamUp<<" / move_target_XY_CAM_UP="<<move_target_XY_CAM_UP);
        angle da = GgafDx9Util::getAngDiff(_angXY_nowCamUp, move_target_XY_CAM_UP);
        if (-1000 < da && da < 1000) {
            _angXY_nowCamUp = move_target_XY_CAM_UP;
        } else {
            _angXY_nowCamUp += (1000 * sgn(da));
        }
        _angXY_nowCamUp = GgafDx9Util::simplifyAng(_angXY_nowCamUp);
        pCAM->_pVecCamUp->x = GgafDx9Util::COS[_angXY_nowCamUp/ANGLE_RATE];
        pCAM->_pVecCamUp->y = GgafDx9Util::SIN[_angXY_nowCamUp/ANGLE_RATE];
        pCAM->_pVecCamUp->z = 0.0f;
    }

    pCAM->_pMover->behave();
    pVP->_pMover->behave();

}
Camera::~Camera() {
}
