#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _TRACE_("World::World");
    _pos_camera = 0;
    _frame_pushdown_zmove = 0;

    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void World::initialize() {
        _TRACE_("World::initialize()");
    GameScene* pGameScene = NEW GameScene("Game");
    addSubLast(pGameScene);
#ifdef MY_DEBUG
    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "28/moji");
    getLordActor()->addSubGroup(KIND_EFFECT, pDispFpsActor);
#endif
    //初期カメラ位置
    int cam_MvVeloRenge = pMYSHIP->_iMoveSpeed * 0.99;
    _dZ_camera_init = -1 * pCAM->_cameraZ_org * LEN_UNIT * PX_UNIT;

    _lim_CAM_top     = MyShip::_lim_top     - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_CAM_bottom  = MyShip::_lim_bottom  + (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_CAM_front   = MyShip::_lim_front   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_CAM_behaind = MyShip::_lim_behaind + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_CAM_zleft   = MyShip::_lim_zleft   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_CAM_zright  = MyShip::_lim_zright  + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);

    _lim_VP_top     = MyShip::_lim_top     - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_VP_bottom  = MyShip::_lim_bottom  + (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_VP_front   = MyShip::_lim_front   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_VP_behaind = MyShip::_lim_behaind + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_VP_zleft   = MyShip::_lim_zleft   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_VP_zright  = MyShip::_lim_zright  + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);

    _correction_width = (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)/2;
    _correction_height = (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2)/2;

    _pos_camera = CAM_POS_RIGHT;

    pCAM->_X = _dZ_camera_init / 10; //少し斜めめから見てる
    pCAM->_Y = 0; //４５度斜めから見る
    pCAM->_Z = -_dZ_camera_init;

    pCAM->setViewPoint(0,0,0);
    pCAM->_pMover->setMvAng(0,0,0);


    pCAM->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pMover->setVxMvVelo(0);
    pCAM->_pMover->setVxMvAcce(0);

    pCAM->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pMover->setVyMvVelo(0);
    pCAM->_pMover->setVyMvAcce(0);

    pCAM->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pMover->setVzMvVelo(0);
    pCAM->_pMover->setVzMvAcce(0);

    pCAM->_pViewPoint->_X = 0;
    pCAM->_pViewPoint->_Y = 0;
    pCAM->_pViewPoint->_Z = pMYSHIP->_Z;


    pCAM->_pViewPoint->_pMover->setMvAng(0,0,0);

    pCAM->_pViewPoint->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pViewPoint->_pMover->setVxMvVelo(0);
    pCAM->_pViewPoint->_pMover->setVxMvAcce(0);

    pCAM->_pViewPoint->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pViewPoint->_pMover->setVyMvVelo(0);
    pCAM->_pViewPoint->_pMover->setVyMvAcce(0);

    pCAM->_pViewPoint->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pViewPoint->_pMover->setVzMvVelo(0);
    pCAM->_pViewPoint->_pMover->setVzMvAcce(0);


}



void World::processBehavior() {
    VB::update(); //入力情報更新


    //TODO:止めてもframeは進む＿？
    if (VB::isPushedDown(VB_PAUSE)) {
        if (getSubFirst()->canBehave()) {
            _TRACE_("PAUSE!");
//            //カメラ注視方向設定
//            pCAM->_pMover->setMvAng(
//                                pCAM->_gazeX,
//                                pCAM->_gazeY,
//                                pCAM->_gazeZ
//                           );

            getSubFirst()->pause();     //一時停止
        } else {
            _TRACE_("UNPAUSE!");
            getSubFirst()->unpause();   //一時停止解除
        }
    }

    //カメラ位置を行ったり来たり
    if (VB::isPushedDown(VB_ZMOVE)) {
        if (_pos_camera < CAM_POS_TO_BEHIND) { //背面視点ではない場合、
            _pos_camera += CAM_POS_TO_BEHIND;  //それぞれの対応背面視点へ
        } else if (_pos_camera > CAM_POS_TO_BEHIND) {//背面視点の場合
            //方向入力により新たな視点へ
            if (VB::isBeingPressed(VB_RIGHT)) {
                _pos_camera = CAM_POS_LEFT;
            } else if (VB::isBeingPressed(VB_LEFT)) {
                _pos_camera = CAM_POS_RIGHT;
            } else if (VB::isBeingPressed(VB_UP)) {
                _pos_camera = CAM_POS_BOTTOM;
            } else if (VB::isBeingPressed(VB_DOWN)) {
                _pos_camera = CAM_POS_TOP;
            } else {
                //方向未入力の場合、元の視点へ
                _pos_camera -= CAM_POS_TO_BEHIND;
            }
        }

    }

    static GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;

    //カメラの移動目標点
    int move_target_X_CAM, move_target_Y_CAM, move_target_Z_CAM;
    //カメラの注視点の移動目標点
    int move_target_X_VP, move_target_Y_VP, move_target_Z_VP;
    //カメラ（始点）の目標地点までの距離（座標差分）
    int dX_CAM, dY_CAM, dZ_CAM;
    //ビューポイント（終点）の目標地点までの距離（座標差分）
    int dX_VP, dY_VP, dZ_VP;

    static int Dx = (int)(_dZ_camera_init / 2);
    static int Dd = (int)(_dZ_camera_init / 100);
    static int slow_range_CAM = 50000;
    static int slow_range02_CAM = slow_range_CAM * 1.1;
    static int slow_range_VP = 50000;
    static int slow_range02_VP = slow_range_VP * 1.1;
    //カメラと視点の移動目標設定
    if (_pos_camera < CAM_POS_TO_BEHIND) {
        if (_pos_camera == CAM_POS_RIGHT) {
            move_target_X_CAM = -Dx;
            move_target_Y_CAM = pMYSHIP->_Y;
            move_target_Z_CAM = pMYSHIP->_Z - _dZ_camera_init;
            move_target_X_VP = Dx;
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
        } else if (_pos_camera == CAM_POS_LEFT) {
            move_target_X_CAM = -Dx;
            move_target_Y_CAM = pMYSHIP->_Y;
            move_target_Z_CAM = pMYSHIP->_Z + _dZ_camera_init;
            move_target_X_VP = Dx;
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
        } else if (_pos_camera == CAM_POS_TOP) {
            move_target_X_CAM = -Dx * pCAM->_screen_aspect;
            move_target_Y_CAM = pMYSHIP->_Y + _dZ_camera_init;
            move_target_Z_CAM = pMYSHIP->_Z;
            move_target_X_VP = Dx;
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
        } else if (_pos_camera == CAM_POS_BOTTOM) {
            move_target_X_CAM = -Dx * pCAM->_screen_aspect;
            move_target_Y_CAM = pMYSHIP->_Y - _dZ_camera_init;
            move_target_Z_CAM = pMYSHIP->_Z;
            move_target_X_VP = Dx;
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
        }
    } else if (_pos_camera > CAM_POS_TO_BEHIND) {
        move_target_X_CAM = pMYSHIP->_X - (_dZ_camera_init/2);
        move_target_Y_CAM = pMYSHIP->_Y;
        move_target_Z_CAM = pMYSHIP->_Z;
        move_target_X_VP = pMYSHIP->_X + (_dZ_camera_init);
        move_target_Y_VP = pMYSHIP->_Y;
        move_target_Z_VP = pMYSHIP->_Z;
        if (_pos_camera == CAM_POS_BEHIND_RIGHT) {
            move_target_Z_CAM -= Dd;
        } else if (_pos_camera == CAM_POS_BEHIND_LEFT) {
            move_target_Z_CAM += Dd;
        } else if (_pos_camera == CAM_POS_BEHIND_TOP) {
            move_target_Y_CAM -= Dd;
        } else if (_pos_camera > CAM_POS_BEHIND_BOTTOM) {
            move_target_Y_CAM += Dd;
        }
    }
    //カメラと視点の移動目標補正
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
        if (move_target_Y_CAM > _lim_CAM_top + _correction_height) {
            //(_lim_CAM_top/2) は
            //move_target_X_CAM = pMYSHIP->_X - (_dZ_camera_init/2);
            //により近づいたため
            move_target_Y_CAM = _lim_CAM_top + _correction_height;
        }
        if (move_target_Y_CAM < _lim_CAM_bottom - _correction_height) {
            move_target_Y_CAM = _lim_CAM_bottom - _correction_height;
        }
        if (move_target_Z_CAM > _lim_CAM_zleft + _correction_width) {
            move_target_Z_CAM = _lim_CAM_zleft + _correction_width;
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
        if (move_target_Y_VP > _lim_VP_top + _correction_height) {
            move_target_Y_VP = _lim_VP_top + _correction_height;
        }
        if (move_target_Y_VP < _lim_VP_bottom - _correction_height) {
            move_target_Y_VP = _lim_VP_bottom - _correction_height;
        }
        if (move_target_Z_VP > _lim_VP_zleft + _correction_width) {
            move_target_Z_VP = _lim_VP_zleft + _correction_width;
        }
        if (move_target_Z_VP < _lim_VP_zright + _correction_width) {
            move_target_Z_VP = _lim_VP_zright + _correction_width;
        }
    }


    //目標地点までの各軸距離
    dX_CAM = move_target_X_CAM - pCAM->_X;
    dY_CAM = move_target_Y_CAM - pCAM->_Y;
    dZ_CAM = move_target_Z_CAM - pCAM->_Z;
    dX_VP = move_target_X_VP - pVP->_X;
    dY_VP = move_target_Y_VP - pVP->_Y;
    dZ_VP = move_target_Z_VP - pVP->_Z;

    if ( getSubFirst()->canBehave() ) {

        int cam_MvVeloRenge;//カメラ移動スピード
        int moveway_num = 0; //自機移動方向数
        if (VB::isBeingPressed(VB_LEFT)) {
            moveway_num++;
        }
        if (VB::isBeingPressed(VB_UP)) {
            moveway_num++;
        }
        if (VB::isBeingPressed(VB_RIGHT)) {
            moveway_num++;
        }
        if (VB::isBeingPressed(VB_DOWN)) {
            moveway_num++;
        }
        if (moveway_num >= 2) {
            cam_MvVeloRenge = pMYSHIP->_iMoveSpeed*NANAME +
                                  ( GgafDx9Util::abs(pMYSHIP->_pMover->_veloVxMv) +
                                    GgafDx9Util::abs(pMYSHIP->_pMover->_veloVyMv) +
                                    GgafDx9Util::abs(pMYSHIP->_pMover->_veloVzMv)*1.5  ); //カメラ移動スピード（自機斜め移動時）

        } else {
            cam_MvVeloRenge = pMYSHIP->_iMoveSpeed +
                                    ( GgafDx9Util::abs(pMYSHIP->_pMover->_veloVxMv) +
                                      GgafDx9Util::abs(pMYSHIP->_pMover->_veloVyMv) +
                                      GgafDx9Util::abs(pMYSHIP->_pMover->_veloVzMv)*1.5  ); //カメラ移動スピード（標準）
        }

//                +
//                  ( GgafDx9Util::abs(pMYSHIP->_pMover->_veloVxMv) +
//                    GgafDx9Util::abs(pMYSHIP->_pMover->_veloVyMv) +
//                    GgafDx9Util::abs(pMYSHIP->_pMover->_veloVzMv)
//                  )
//                 ) * 0.7;//どうするか????0.7; //0.7の意味は 1/√2 よりわずかに小さい
                          //これは自機が斜め移動時カメラがわずかに追いつかないようにするため
//        if (GgafDx9Util::abs(dX_CAM) > slow_range_CAM*1.2 ||
//            GgafDx9Util::abs(dY_CAM) > slow_range_CAM*1.2 ||
//            GgafDx9Util::abs(dZ_CAM) > slow_range_CAM*1.2) {
//            cam_MvVeloRenge = cam_MvVeloRenge * 2;
//        }


        //カメラがスロー範囲（ちょっと広め）時とそうでない時の処理
        if (-slow_range02_CAM > dX_CAM && dX_CAM > slow_range02_CAM) {
            pCAM->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pCAM->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }
        if (-slow_range02_CAM > dY_CAM && dY_CAM > slow_range02_CAM) {
            pCAM->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pCAM->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }
        if (-slow_range02_CAM > dZ_CAM && dZ_CAM > slow_range02_CAM) {
            pCAM->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pCAM->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }


        //カメラがスロー範囲時とそうでない時の処理
        static double acc_rate = 500.0;
        if (-slow_range_CAM < dX_CAM && dX_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVxMv *= 0.9;
            pCAM->_pMover->setVxMvAcce(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVxMvAcce(dX_CAM/acc_rate);//背後に回る時
            } else {
                pCAM->_pMover->setVxMvAcce(dX_CAM/acc_rate);
            }
        }
        if (-slow_range_CAM < dY_CAM && dY_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVyMv *= 0.9;
            pCAM->_pMover->setVyMvAcce(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVyMvAcce(dY_CAM/acc_rate);//背後に回る時
            } else {
                pCAM->_pMover->setVyMvAcce(dY_CAM/acc_rate);
            }
        }
        if (-slow_range_CAM < dZ_CAM && dZ_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVzMv *= 0.9;
            pCAM->_pMover->setVzMvAcce(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVzMvAcce(dZ_CAM/acc_rate);//背後に回る時
            } else {

                pCAM->_pMover->setVzMvAcce(dZ_CAM/acc_rate);
            }
        }






        if (-slow_range02_VP > dX_VP && dX_VP > slow_range02_VP) {
            pVP->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pVP->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }
        if (-slow_range02_VP > dY_VP && dY_VP > slow_range02_VP) {
            pVP->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pVP->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }
        if (-slow_range02_VP > dZ_VP && dZ_VP > slow_range02_VP) {
            pVP->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pVP->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }

        if (-slow_range_VP < dX_VP && dX_VP < slow_range_VP) {
            pVP->_pMover->_veloVxMv *= 0.9;
            pVP->_pMover->setVxMvAcce(0);
        } else {
            pVP->_pMover->setVxMvAcce(dX_VP/acc_rate);
        }
        if (-slow_range_VP < dY_VP && dY_VP < slow_range_VP) {
            pVP->_pMover->_veloVyMv *= 0.9;
            pVP->_pMover->setVyMvAcce(0);
        } else {
            pVP->_pMover->setVyMvAcce(dY_VP/acc_rate);
        }
        if (-slow_range_VP < dZ_VP && dZ_VP < slow_range_VP) {
            pVP->_pMover->_veloVzMv *= 0.9;
            pVP->_pMover->setVzMvAcce(0);
        } else {
            pVP->_pMover->setVzMvAcce(dZ_VP/acc_rate);
        }



        pCAM->_pMover->behave();
        pVP->_pMover->behave();
    }

    //サブシーンが一時停止していれば、カメラ操作できる。
    if ( getSubFirst()->canBehave() ) {
        //スルー
    } else {
        pCAM->_pMover->_mv_ang_rz_target_flg = true;
        pCAM->_pMover->_mv_ang_ry_target_flg = true;

        if (GgafDx9Input::isBeingPressedKey(DIK_SPACE)) {
            if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
                pCAM->_Y += 4000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
                pCAM->_Y -= 4000;
            } else {

            }

            if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
                pCAM->_X += 4000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
                pCAM->_X -= 4000;
            } else {
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
                pCAM->_Z += 4000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
                pCAM->_Z -= 4000;
            } else {
            }

        } else {
            if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
                pCAM->_pMover->addRzMvAng(4000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
                pCAM->_pMover->addRzMvAng(-4000);
            } else {
                pCAM->_pMover->addRzMvAng(0);
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
                pCAM->_pMover->addRyMvAng(4000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
                pCAM->_pMover->addRyMvAng(-4000);
            } else {
                pCAM->_pMover->addRyMvAng(0);
            }
            if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
                pCAM->_pMover->setMvVelo(4000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
                pCAM->_pMover->setMvVelo(-4000);
            } else {
                pCAM->_pMover->setMvVelo(0);
            }
        }
    }

    if (GgafDx9Input::isBeingPressedKey(DIK_O)) {
        pCAM->_pMover->setMvAng(0,0,0);
        _TRACE_("GgafDx9Universe Camera=("<<pCAM->_X<<","<<pCAM->_Y<<","<<pCAM->_Z<<")");
    }

//    if ( getSubFirst()->canBehave() ) {
//        //スルー
//    } else {
//        //カメラ注視方向設定
//        pCAM->setViewPoint (
//                   pCAM->_X + (pCAM->_pMover->_vX * LEN_UNIT * PX_UNIT),
//                   pCAM->_Y + (pCAM->_pMover->_vY * LEN_UNIT * PX_UNIT),
//                   pCAM->_Z + (pCAM->_pMover->_vZ * LEN_UNIT * PX_UNIT)
//                  );
//        pCAM->_pMover->setMvAng(0,0,0);
//    }

}

void World::processJudgement() {
}

World::~World() {
}



