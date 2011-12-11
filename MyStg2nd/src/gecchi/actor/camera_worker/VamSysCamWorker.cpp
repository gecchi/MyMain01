#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

VamSysCamWorker::VamSysCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "VamSysCamWorker";
    _pMyShip = NULL; //MyShipSceneに設定してもらう

    //初期カメラ移動範囲制限
    float revise = 0.7; //斜めから見るので補正値を掛ける。1.0の場合は原点からでドンピシャ。これは微調整を繰り返した
    _lim_CAM_top     = MyShip::_lim_top     - (PX2CO(CFG_PROPERTY(GAME_BUFFER_HEIGHT))/2)*revise;
    _lim_CAM_bottom  = MyShip::_lim_bottom  + (PX2CO(CFG_PROPERTY(GAME_BUFFER_HEIGHT))/2)*revise;
    _lim_CAM_front   = MyShip::_lim_front   - (PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    _lim_CAM_behaind = MyShip::_lim_behaind + (PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    _lim_CAM_zleft   = MyShip::_lim_zleft   - (PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    _lim_CAM_zright  = MyShip::_lim_zright  + (PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;

    _lim_VP_top     = MyShip::_lim_top     - (PX2CO(CFG_PROPERTY(GAME_BUFFER_HEIGHT))/2)*revise;
    _lim_VP_bottom  = MyShip::_lim_bottom  + (PX2CO(CFG_PROPERTY(GAME_BUFFER_HEIGHT))/2)*revise;
    _lim_VP_front   = MyShip::_lim_front   - (PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    _lim_VP_behaind = MyShip::_lim_behaind + (PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    _lim_VP_zleft   = MyShip::_lim_zleft   - (PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
    _lim_VP_zright  = MyShip::_lim_zright  + (PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH))/2)*revise;
}
void VamSysCamWorker::initialize() {
    GgafDxCamera* pCam = P_CAM;
    GgafDxGeometricActor* pVP = pCam->_pViewPoint;

    //初期カメラZ位置
    _dZ_camera_init = -DX2CO(pCam->_cameraZ_org);


    //画面背後用範囲差分
    //背後のZ座標は_dZ_camera_init/2
    _correction_width = 0;//(CFG_PROPERTY(GAME_BUFFER_WIDTH)*LEN_UNIT/2)/4;
    _correction_height = 0;//(CFG_PROPERTY(GAME_BUFFER_HEIGHT)*LEN_UNIT/2)/4;

    _pos_camera = VAM_POS_RIGHT;

//    pCam->_X = 0;
//    pCam->_Y = 0;
//    pCam->_Z = 0;
//    pCam->setViewPoint(0,0,0);
//    pCam->_pKurokoB->setMvAng(0,0,0);

    _cam_velo_renge = 30000;
    pCam->_pKurokoB->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pCam->_pKurokoB->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pCam->_pKurokoB->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pKurokoB->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pKurokoB->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pKurokoB->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);

    _stop_renge = 60000;
    _angXY_nowCamUp = GgafDxUtil::getAngle2D(P_CAM->_pVecCamUp->x, P_CAM->_pVecCamUp->y);
    _stop_dZ = 0;
    _stop_dY = 0;
    _TRACE_("VamSysCamWorker::initialize() this="<<this);
    dump();
}

void VamSysCamWorker::processBehavior() {

    //DefaultVamSysCamWorker::processBehavior();

    //ゲーム内カメラワーク処理
    if (_pMyShip == NULL) {
        return; //MyShipSceneシーンが未だならカメラワーク禁止
    }

    GgafDxCamera* pCam = P_CAM;
    GgafDxGeometricActor* pVP = pCam->_pViewPoint;
    MyOptionController* pOptionController = P_MYOPTIONCON;

    //カメラ位置番号を決定処理
//    if (VB_PLAY->isPushedDown(VB_VIEW)) {
//        if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
//            _pos_camera = VAM_POS_RIGHT;
//        } else if (VB_PLAY->isBeingPressed(VB_LEFT)) {
//            _pos_camera = VAM_POS_LEFT;
//        } else if (VB_PLAY->isBeingPressed(VB_UP)) {
//            _pos_camera = VAM_POS_TOP;
//        } else if (VB_PLAY->isBeingPressed(VB_DOWN)) {
//            _pos_camera = VAM_POS_BOTTOM;
//        } else {
//            _pos_camera += VAM_POS_TO_BEHIND;  //それぞれの対応背面ビューポイントへ
//        }
//    } else if (VB_PLAY->isBeingPressed(VB_VIEW)) {
//        if (VB_PLAY->isPushedDown(VB_RIGHT)) {
//            _pos_camera = VAM_POS_RIGHT;
//        } else if (VB_PLAY->isPushedDown(VB_LEFT)) {
//            _pos_camera = VAM_POS_LEFT;
//        } else if (VB_PLAY->isPushedDown(VB_UP)) {
//            _pos_camera = VAM_POS_TOP;
//        } else if (VB_PLAY->isPushedDown(VB_DOWN)) {
//            _pos_camera = VAM_POS_BOTTOM;
//        }
//    }



    if (VB_PLAY->isPushedDown(VB_VIEW)) {
        _TRACE_("VB_VIEW!! now _pos_camera="<<_pos_camera);
        if (_pos_camera < VAM_POS_TO_BEHIND) { //背面ビューポイントではない場合、
            _pos_camera += VAM_POS_TO_BEHIND;  //それぞれの対応背面ビューポイントへ
        } else if (_pos_camera > VAM_POS_TO_BEHIND) {//背面ビューポイントの場合
            //方向入力により新たなビューポイントへ
            if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                _pos_camera = VAM_POS_LEFT;
            } else if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                _pos_camera = VAM_POS_RIGHT;
            } else if (VB_PLAY->isBeingPressed(VB_UP)) {
                _pos_camera = VAM_POS_BOTTOM;
            } else if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                _pos_camera = VAM_POS_TOP;
            } else {
                //方向未入力の場合、そのまま

//                //方向未入力の場合、元のビューポイントへ
//                _pos_camera -= VAM_POS_TO_BEHIND;
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
    static int Dx = (int)((CFG_PROPERTY(GAME_BUFFER_WIDTH)*LEN_UNIT/2)/4*2);
    static int Ddx_hw = (int)((CFG_PROPERTY(GAME_BUFFER_WIDTH)*LEN_UNIT/2) - (CFG_PROPERTY(GAME_BUFFER_HEIGHT)*LEN_UNIT/2));

//    static coord Dx = PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH)/2)/4*2;
//    static coord Ddx_hw = (PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH)/2) - (PX2CO(CFG_PROPERTY(GAME_BUFFER_HEIGHT)/2));


    //static int Dd = 30000;

    //オプション操作中
    if (VB_PLAY->isBeingPressed(VB_OPTION) && VB_PLAY->isPushedDown(VB_VIEW)) {
        //オプション操作中にポンと VB_VIEW を押す
        //オプション背後に回る
        coord d = _dZ_camera_init*0.6;
        move_target_X_CAM = pOptionController->_X + pOptionController->_pKurokoA->_vX*-d;
        move_target_Y_CAM = pOptionController->_Y + pOptionController->_pKurokoA->_vY*-d;
        move_target_Z_CAM = pOptionController->_Z + pOptionController->_pKurokoA->_vZ*-d;
        move_target_X_VP = pOptionController->_X + pOptionController->_pKurokoA->_vX*d;
        move_target_Y_VP = pOptionController->_Y + pOptionController->_pKurokoA->_vY*d;
        move_target_Z_VP = pOptionController->_Z + pOptionController->_pKurokoA->_vZ*d;
        move_target_XY_CAM_UP = GgafDxUtil::simplifyAng(pOptionController->_pKurokoA->_angRzMv+D90ANG);

    } else {//通常時
        if (_pos_camera < VAM_POS_TO_BEHIND) {
            if (_pos_camera == VAM_POS_RIGHT) {
    //            move_target_X_CAM = 0;
    //            move_target_Y_CAM = 0;
    //            move_target_Z_CAM = -_dZ_camera_init;
    //            move_target_X_VP = 0;
    //            move_target_Y_VP = 0;
    //            move_target_Z_VP = 0;

                move_target_X_CAM = -Dx + (-_pMyShip->_X-200000)*2;
                //↑ -200000 はカメラ移動位置、
                //   *2 は自機が後ろに下がった時のカメラのパン具合。
                //   この辺りの数値は納得いくまで調整を繰した。
                //   TODO:本当はゲーム領域の大きさから動的に計算できる。いつかそうしたい。
                if (-Dx > move_target_X_CAM) {
                    move_target_X_CAM = -Dx;
                } else if (move_target_X_CAM > Dx/2) {
                    move_target_X_CAM = Dx/2;
                }
                move_target_Y_CAM = _pMyShip->_Y;
                move_target_Z_CAM = _pMyShip->_Z - _dZ_camera_init;
                move_target_X_VP = Dx - (-_pMyShip->_X-200000)*2;
                if (Dx < move_target_X_VP) {
                    move_target_X_VP = Dx;
                } else if ( move_target_X_VP < -Dx/2) {
                    move_target_X_VP = -Dx/2;
                }
                move_target_Y_VP = _pMyShip->_Y;
                move_target_Z_VP = _pMyShip->_Z-100000;
                move_target_XY_CAM_UP = D90ANG;
            } else if (_pos_camera == VAM_POS_LEFT) {
                move_target_X_CAM = -Dx + (-_pMyShip->_X-200000)*2;
                if (-Dx > move_target_X_CAM) {
                    move_target_X_CAM = -Dx;
                } else if (move_target_X_CAM > Dx/2) {
                    move_target_X_CAM = Dx/2;
                }
                move_target_Y_CAM = _pMyShip->_Y;
                move_target_Z_CAM = _pMyShip->_Z + _dZ_camera_init;
                move_target_X_VP = Dx - (-_pMyShip->_X-200000)*2;
                if (Dx < move_target_X_VP) {
                    move_target_X_VP = Dx;
                } else if ( move_target_X_VP < -Dx/2) {
                    move_target_X_VP = -Dx/2;
                }
                move_target_Y_VP = _pMyShip->_Y;
                move_target_Z_VP = _pMyShip->_Z+100000;
                move_target_XY_CAM_UP = D90ANG;
            } else if (_pos_camera == VAM_POS_TOP) {
                move_target_X_CAM = -Dx - Ddx_hw + (-_pMyShip->_X-125000)*2;
                if ((-Dx - Ddx_hw) > move_target_X_CAM) {
                    move_target_X_CAM = -Dx - Ddx_hw;
                } else if (move_target_X_CAM > (Dx + Ddx_hw)/2) {
                    move_target_X_CAM = (Dx + Ddx_hw)/2;
                }
                move_target_Y_CAM = _pMyShip->_Y + _dZ_camera_init + Ddx_hw;
                move_target_Z_CAM = _pMyShip->_Z;
                move_target_X_VP = Dx + Ddx_hw - (-_pMyShip->_X-125000)*2;
                if (Dx + Ddx_hw < move_target_X_VP) {
                    move_target_X_VP = Dx + Ddx_hw;
                } else if ( move_target_X_VP < -(Dx + Ddx_hw)/2) {
                    move_target_X_VP = -(Dx + Ddx_hw)/2;
                }
                move_target_Y_VP = _pMyShip->_Y;
                move_target_Z_VP = _pMyShip->_Z;
                if (pCam->_X < pVP->_X) {
                    move_target_XY_CAM_UP = D45ANG;
                } else {
                    move_target_XY_CAM_UP = D315ANG;
                }
            } else if (_pos_camera == VAM_POS_BOTTOM) {
                move_target_X_CAM = -Dx - Ddx_hw + (-_pMyShip->_X-125000)*2;
                if ((-Dx - Ddx_hw) > move_target_X_CAM) {
                    move_target_X_CAM = -Dx - Ddx_hw;
                } else if (move_target_X_CAM > (Dx + Ddx_hw)/2) {
                    move_target_X_CAM = (Dx + Ddx_hw)/2;
                }
                move_target_Y_CAM = _pMyShip->_Y - _dZ_camera_init - Ddx_hw;
                move_target_Z_CAM = _pMyShip->_Z;
                move_target_X_VP = Dx + Ddx_hw - (-_pMyShip->_X-125000)*2;
                if (Dx + Ddx_hw < move_target_X_VP) {
                    move_target_X_VP = Dx + Ddx_hw;
                } else if ( move_target_X_VP < -(Dx + Ddx_hw)/2) {
                    move_target_X_VP = -(Dx + Ddx_hw)/2;
                }
                move_target_Y_VP = _pMyShip->_Y;
                move_target_Z_VP = _pMyShip->_Z;
                if (pCam->_X < pVP->_X) {
                    move_target_XY_CAM_UP = D135ANG;
                } else {
                    move_target_XY_CAM_UP = D255ANG;
                }
            }
        } else if (_pos_camera > VAM_POS_TO_BEHIND) {
            move_target_X_CAM = _pMyShip->_X - (_dZ_camera_init*0.6);
            move_target_Y_CAM = _pMyShip->_Y;
            move_target_Z_CAM = _pMyShip->_Z;
            move_target_X_VP = _pMyShip->_X + (_dZ_camera_init*2);
            move_target_Y_VP = _pMyShip->_Y;
            move_target_Z_VP = _pMyShip->_Z;
            move_target_XY_CAM_UP = D90ANG;
    //        if (_pos_camera == VAM_POS_BEHIND_RIGHT) {
    //            move_target_Z_CAM -= Dd;
    //        } else if (_pos_camera == VAM_POS_BEHIND_LEFT) {
    //            move_target_Z_CAM += Dd;
    //        } else if (_pos_camera == VAM_POS_BEHIND_TOP) {
    //            move_target_Y_CAM += Dd;
    //        } else if (_pos_camera == VAM_POS_BEHIND_BOTTOM) {
    //            move_target_Y_CAM -= Dd;
    //        }
        } else {
            throwGgafCriticalException("World::processBehavior() 不正な_pos_camera="<<_pos_camera);
        }
        //カメラの目標座標、ビューポイントの目標座標について、現在の動いている方向への若干画面寄りを行う。（ﾅﾝﾉｺｯﾁｬ）
        move_target_Z_CAM -= (_pMyShip->_Z*0.05);
        move_target_Y_CAM -= (_pMyShip->_Y*0.05);
    }

//
//    GgafDxGeoElem* pGeoMyShip = _pMyShip->_pRing_GeoHistory->getCurrent(); //現在の自機座標
//    GgafDxGeoElem* pGeoMyShip_prev= _pMyShip->_pRing_GeoHistory->getPrev(); //現在のひとつ前のフレームの自機座標
//    _stop_dZ += (pGeoMyShip_prev->_Z - pGeoMyShip->_Z)*0.1; //自機の移動量の1割の移動量を
//    _stop_dY += (pGeoMyShip_prev->_Y - pGeoMyShip->_Y)*0.1; //カメラの目標座標に加算してます。
//    move_target_Z_CAM += _stop_dZ;
//    move_target_Y_CAM += _stop_dY;


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
            if (_pos_camera < VAM_POS_TO_BEHIND) { //背面ビューポイントではない場合、
                //それぞれの元の対応ビューポイントへ戻る。
                _pos_camera += VAM_POS_TO_BEHIND;
            } else if (_pos_camera > VAM_POS_TO_BEHIND) {//背面ビューポイントだった場合
                //そのまま

                //それぞれの元の対応背面ビューポイントへ戻る。
                //_pos_camera -= VAM_POS_TO_BEHIND;
            }
        }
    }
    //カメラの移動速度の最大、最小制限を設定
    pCam->_pKurokoB->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pKurokoB->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pKurokoB->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKurokoB->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKurokoB->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKurokoB->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);

    //カメラとビューポイントの移動座標を制限。
    //自機移動範囲に応じて、画面端の感じを演出するため。(無くとも問題ない？)
    if (_pos_camera < VAM_POS_TO_BEHIND) {
        if (_pos_camera == VAM_POS_RIGHT) {
            if (move_target_Y_CAM > _lim_CAM_top) {
                move_target_Y_CAM = _lim_CAM_top;
            }
            if (move_target_Y_CAM < _lim_CAM_bottom ) {
                move_target_Y_CAM = _lim_CAM_bottom;
            }
        } else if (_pos_camera == VAM_POS_LEFT) {
            if (move_target_Y_CAM > _lim_CAM_top) {
                move_target_Y_CAM = _lim_CAM_top;
            }
            if (move_target_Y_CAM < _lim_CAM_bottom ) {
                move_target_Y_CAM = _lim_CAM_bottom;
            }
        } else if (_pos_camera == VAM_POS_TOP) {
            if (move_target_Z_CAM > _lim_CAM_zleft) {
                move_target_Z_CAM = _lim_CAM_zleft;
            }
            if (move_target_Z_CAM < _lim_CAM_zright) {
                move_target_Z_CAM = _lim_CAM_zright;
            }
        } else if (_pos_camera == VAM_POS_BOTTOM) {
            if (move_target_Z_CAM > _lim_CAM_zleft) {
                move_target_Z_CAM = _lim_CAM_zleft;
            }
            if (move_target_Z_CAM < _lim_CAM_zright) {
                move_target_Z_CAM = _lim_CAM_zright;
            }
        }
    } else if (_pos_camera > VAM_POS_TO_BEHIND) {
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
    if (_pos_camera < VAM_POS_TO_BEHIND) {
        if (_pos_camera == VAM_POS_RIGHT) {
            if (move_target_Y_VP > _lim_VP_top) {
                move_target_Y_VP = _lim_VP_top;
            }
            if (move_target_Y_VP < _lim_VP_bottom ) {
                move_target_Y_VP = _lim_VP_bottom;
            }
        } else if (_pos_camera == VAM_POS_LEFT) {
            if (move_target_Y_VP > _lim_VP_top) {
                move_target_Y_VP = _lim_VP_top;
            }
            if (move_target_Y_VP < _lim_VP_bottom ) {
                move_target_Y_VP = _lim_VP_bottom;
            }
        } else if (_pos_camera == VAM_POS_TOP) {
            if (move_target_Z_VP > _lim_VP_zleft) {
                move_target_Z_VP = _lim_VP_zleft;
            }
            if (move_target_Z_VP < _lim_VP_zright) {
                move_target_Z_VP = _lim_VP_zright;
            }
        } else if (_pos_camera == VAM_POS_BOTTOM) {
            if (move_target_Z_VP > _lim_VP_zleft) {
                move_target_Z_VP = _lim_VP_zleft;
            }
            if (move_target_Z_VP < _lim_VP_zright) {
                move_target_Z_VP = _lim_VP_zright;
            }
        }
    } else if (_pos_camera > VAM_POS_TO_BEHIND) {
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
    int dX_CAM = move_target_X_CAM - pCam->_X;
    int dY_CAM = move_target_Y_CAM - pCam->_Y;
    int dZ_CAM = move_target_Z_CAM - pCam->_Z;
    //ビューポイントの目標座標までの各軸の距離（座標差分）
    int dX_VP = move_target_X_VP - pVP->_X;
    int dY_VP = move_target_Y_VP - pVP->_Y;
    int dZ_VP = move_target_Z_VP - pVP->_Z;
    velo veloVxRenge = 4000;
    velo veloVyRenge = 4000;
    velo veloVzRenge = 4000;
    if (_pos_camera == VAM_POS_BEHIND_RIGHT || _pos_camera == VAM_POS_BEHIND_LEFT) {
        if (_pMyShip->_X > -Dx) {
            //ややZ軸移動を早くする
            veloVzRenge *= 1.8;
            veloVxRenge *= 0.2;
        } else {
            //ややZ軸移動を遅くする
            veloVzRenge *= 0.2;
            veloVxRenge *= 1.8;
        }
    } else if (_pos_camera == VAM_POS_BEHIND_TOP || _pos_camera == VAM_POS_BEHIND_BOTTOM) {
        if (_pMyShip->_X > -Dx) {
            //ややY軸移動を早くする
            veloVyRenge *= 1.8;
            veloVxRenge *= 0.2;
        } else {
            //ややY軸移動を遅くする
            veloVyRenge *= 0.2;
            veloVxRenge *= 1.8;
        }
    } else if (_pos_camera == VAM_POS_RIGHT || _pos_camera == VAM_POS_LEFT) {
        if (_pMyShip->_X > -Dx) {
            //ややX軸移動を早くする
            veloVxRenge *= 1.8;
            veloVzRenge *= 0.2;
        } else {
            //ややX軸移動を遅くする
            veloVxRenge *= 0.2;
            veloVzRenge *= 1.8;
        }
    } else if (_pos_camera == VAM_POS_TOP || _pos_camera == VAM_POS_BOTTOM) {
        if (_pMyShip->_X > -Dx) {
            //ややX軸移動を早くする
            veloVxRenge *= 1.8;
            veloVyRenge *= 0.2;
        } else {
            //ややX軸移動を遅くする
            veloVxRenge *= 0.2;
            veloVyRenge *= 1.8;
        }
    }

    velo last_CAM_veloVxMv = pCam->_pKurokoB->_veloVxMv;
    velo  new_CAM_veloVxMv = _pMyShip->_iMoveSpeed*(dX_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVxMv-veloVxRenge <= new_CAM_veloVxMv && new_CAM_veloVxMv <= last_CAM_veloVxMv+veloVxRenge) {
        pCam->_pKurokoB->setVxMvVelo(new_CAM_veloVxMv);
    } else {
        if (last_CAM_veloVxMv-veloVxRenge > new_CAM_veloVxMv) {
            pCam->_pKurokoB->setVxMvVelo(last_CAM_veloVxMv-veloVxRenge);
        } else if (new_CAM_veloVxMv > last_CAM_veloVxMv+veloVxRenge) {
            pCam->_pKurokoB->setVxMvVelo(last_CAM_veloVxMv+veloVxRenge);
        }
    }
    velo last_VP_veloVxMv = pVP->_pKurokoB->_veloVxMv;
    velo  new_VP_veloVxMv = _pMyShip->_iMoveSpeed*(dX_VP*1.0 / _stop_renge);
    if (last_VP_veloVxMv-veloVxRenge <= new_VP_veloVxMv && new_VP_veloVxMv <= last_VP_veloVxMv+veloVxRenge) {
        pVP->_pKurokoB->setVxMvVelo(new_VP_veloVxMv);
    } else {
        if (last_VP_veloVxMv-veloVxRenge > new_VP_veloVxMv) {
            pVP->_pKurokoB->setVxMvVelo(last_VP_veloVxMv-veloVxRenge);
        } else if (new_VP_veloVxMv > last_VP_veloVxMv+veloVxRenge) {
            pVP->_pKurokoB->setVxMvVelo(last_VP_veloVxMv+veloVxRenge);
        }
    }

    velo last_CAM_veloVyMv = pCam->_pKurokoB->_veloVyMv;
    velo  new_CAM_veloVyMv = _pMyShip->_iMoveSpeed*(dY_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVyMv-veloVyRenge <= new_CAM_veloVyMv && new_CAM_veloVyMv <= last_CAM_veloVyMv+veloVyRenge) {
        pCam->_pKurokoB->setVyMvVelo(new_CAM_veloVyMv);
    } else {
        if (last_CAM_veloVyMv-veloVyRenge > new_CAM_veloVyMv) {
            pCam->_pKurokoB->setVyMvVelo(last_CAM_veloVyMv-veloVyRenge);
        } else if (new_CAM_veloVyMv > last_CAM_veloVyMv+veloVyRenge) {
            pCam->_pKurokoB->setVyMvVelo(last_CAM_veloVyMv+veloVyRenge);
        }
    }
    velo last_VP_veloVyMv = pVP->_pKurokoB->_veloVyMv;
    velo  new_VP_veloVyMv = _pMyShip->_iMoveSpeed*(dY_VP*1.0 / _stop_renge);
    if (last_VP_veloVyMv-veloVyRenge <= new_VP_veloVyMv && new_VP_veloVyMv <= last_VP_veloVyMv+veloVyRenge) {
        pVP->_pKurokoB->setVyMvVelo(new_VP_veloVyMv);
    } else {
        if (last_VP_veloVyMv-veloVyRenge > new_VP_veloVyMv) {
            pVP->_pKurokoB->setVyMvVelo(last_VP_veloVyMv-veloVyRenge);
        } else if (new_VP_veloVyMv > last_VP_veloVyMv+veloVyRenge) {
            pVP->_pKurokoB->setVyMvVelo(last_VP_veloVyMv+veloVyRenge);
        }
    }

    velo last_CAM_veloVzMv = pCam->_pKurokoB->_veloVzMv;
    velo  new_CAM_veloVzMv = _pMyShip->_iMoveSpeed*(dZ_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVzMv-veloVzRenge <= new_CAM_veloVzMv && new_CAM_veloVzMv <= last_CAM_veloVzMv+veloVzRenge) {
        pCam->_pKurokoB->setVzMvVelo(new_CAM_veloVzMv);
    } else {
        if (last_CAM_veloVzMv-veloVzRenge > new_CAM_veloVzMv) {
            pCam->_pKurokoB->setVzMvVelo(last_CAM_veloVzMv-veloVzRenge);
        } else if (new_CAM_veloVzMv > last_CAM_veloVzMv+veloVzRenge) {
            pCam->_pKurokoB->setVzMvVelo(last_CAM_veloVzMv+veloVzRenge);
        }
    }

    velo last_VP_veloVzMv = pVP->_pKurokoB->_veloVzMv;
    velo  new_VP_veloVzMv = _pMyShip->_iMoveSpeed*(dZ_VP*1.0 / _stop_renge);
    if (last_VP_veloVzMv-veloVzRenge <= new_VP_veloVzMv && new_VP_veloVzMv <= last_VP_veloVzMv+veloVzRenge) {
        pVP->_pKurokoB->setVzMvVelo(new_VP_veloVzMv);
    } else {
        if (last_VP_veloVzMv-veloVzRenge > new_VP_veloVzMv) {
            pVP->_pKurokoB->setVzMvVelo(last_VP_veloVzMv-veloVzRenge);
        } else if (new_VP_veloVzMv > last_VP_veloVzMv+veloVzRenge) {
            pVP->_pKurokoB->setVzMvVelo(last_VP_veloVzMv+veloVzRenge);
        }
    }

    //カメラのUPを計算
    ang_velo ang_velo_cam_up = cam_velo_renge/20; //cam_velo_rengeはVB_VIEW押しっぱで超低速になる方の速度
    if (_angXY_nowCamUp != move_target_XY_CAM_UP) {
        angle da = GgafDxUtil::getAngDiff(_angXY_nowCamUp, move_target_XY_CAM_UP);
        if (-ang_velo_cam_up < da && da < ang_velo_cam_up) {
            _angXY_nowCamUp = move_target_XY_CAM_UP;
        } else {
            _angXY_nowCamUp += (ang_velo_cam_up * sgn(da));
        }
        _angXY_nowCamUp = GgafDxUtil::simplifyAng(_angXY_nowCamUp);
        pCam->_pVecCamUp->x = GgafDxUtil::COS[_angXY_nowCamUp/SANG_RATE];
        pCam->_pVecCamUp->y = GgafDxUtil::SIN[_angXY_nowCamUp/SANG_RATE];
        pCam->_pVecCamUp->z = 0.0f;
    }

    pCam->_pKurokoB->behave();
    pVP->_pKurokoB->behave();

//    _TRACE_(getActivePartFrame()<<","<<dX_CAM<<","<<dY_CAM<<","<<dZ_CAM<<","<<pCam->_X<<","<<pCam->_Y<<","<<pCam->_Z<<","<<last_CAM_veloVxMv<<","<<new_CAM_veloVxMv<<","<<last_CAM_veloVyMv<<","<<new_CAM_veloVyMv<<","<<last_CAM_veloVzMv<<","<<new_CAM_veloVzMv<<","<<pCam->_pKurokoB->_veloVxMv<<","<<pCam->_pKurokoB->_veloVyMv<<","<<pCam->_pKurokoB->_veloVzMv);

}
VamSysCamWorker::~VamSysCamWorker() {
}
