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
#ifdef OREDEBUG
    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "28/moji");
    getLordActor()->accept(KIND_EFFECT, pDispFpsActor);
#endif
    //初期カメラ位置
    int speed = pMYSHIP->_iMoveSpeed * 0.99;
    _dZ_camera_init = -1 * pCAM->_cameraZ_org * LEN_UNIT * PX_UNIT;

    _lim_CAM_top     = GameGlobal::_lim_MyShip_top     - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_CAM_bottom  = GameGlobal::_lim_MyShip_bottom  + (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_CAM_front   = GameGlobal::_lim_MyShip_front   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_CAM_behaind = GameGlobal::_lim_MyShip_behaind + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_CAM_zleft   = GameGlobal::_lim_MyShip_zleft   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_CAM_zright  = GameGlobal::_lim_MyShip_zright  + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);

    _lim_VP_top     = GameGlobal::_lim_MyShip_top     - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_VP_bottom  = GameGlobal::_lim_MyShip_bottom  + (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_VP_front   = GameGlobal::_lim_MyShip_front   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_VP_behaind = GameGlobal::_lim_MyShip_behaind + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_VP_zleft   = GameGlobal::_lim_MyShip_zleft   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_VP_zright  = GameGlobal::_lim_MyShip_zright  + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);

    _pos_camera = CAM_POS_RIGHT;

    pCAM->_X = _dZ_camera_init / 10; //少し斜めめから見てる
    pCAM->_Y = 0; //４５度斜めから見る
    pCAM->_Z = -_dZ_camera_init;

    pCAM->setViewPoint(0,0,0);
    pCAM->_pMover->setMoveAngle(0,0,0);


    pCAM->_pMover->setVxMoveVeloRenge(-speed, speed);
    pCAM->_pMover->setVxMoveVelocity(0);
    pCAM->_pMover->setVxMoveVeloAcceleration(0);

    pCAM->_pMover->setVyMoveVeloRenge(-speed, speed);
    pCAM->_pMover->setVyMoveVelocity(0);
    pCAM->_pMover->setVyMoveVeloAcceleration(0);

    pCAM->_pMover->setVzMoveVeloRenge(-speed, speed);
    pCAM->_pMover->setVzMoveVelocity(0);
    pCAM->_pMover->setVzMoveVeloAcceleration(0);

    pCAM->_pViewPoint->_X = 0;
    pCAM->_pViewPoint->_Y = 0;
    pCAM->_pViewPoint->_Z = pMYSHIP->_Z;


    pCAM->_pViewPoint->_pMover->setMoveAngle(0,0,0);

    pCAM->_pViewPoint->_pMover->setVxMoveVeloRenge(-speed, speed);
    pCAM->_pViewPoint->_pMover->setVxMoveVelocity(0);
    pCAM->_pViewPoint->_pMover->setVxMoveVeloAcceleration(0);

    pCAM->_pViewPoint->_pMover->setVyMoveVeloRenge(-speed, speed);
    pCAM->_pViewPoint->_pMover->setVyMoveVelocity(0);
    pCAM->_pViewPoint->_pMover->setVyMoveVeloAcceleration(0);

    pCAM->_pViewPoint->_pMover->setVzMoveVeloRenge(-speed, speed);
    pCAM->_pViewPoint->_pMover->setVzMoveVelocity(0);
    pCAM->_pViewPoint->_pMover->setVzMoveVeloAcceleration(0);


}



void World::processBehavior() {
    VB::update(); //入力情報更新


    //TODO:止めてもframeは進む＿？
    if (VB::isPushedDown(VB_PAUSE)) {
        if (getSubFirst()->isBehaving()) {
            _TRACE_("PAUSE!");
//            //カメラ注視方向設定
//            pCAM->_pMover->setMoveAngle(
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

    static int Dx = (int)(_dZ_camera_init / 4);
    static int Dd = (int)(_dZ_camera_init / 100);
    static int X_screen_left = (int)(-1 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2);
    static int Y_screen_top = (int)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * LEN_UNIT / 2);
    static int slow_range_CAM = 70000;
    static int slow_range_VP = 70000;
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
        move_target_X_CAM = pMYSHIP->_X - _dZ_camera_init;
        move_target_Y_CAM = pMYSHIP->_Y;
        move_target_Z_CAM = pMYSHIP->_Z;
        move_target_X_VP = pMYSHIP->_X + _dZ_camera_init;
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
        if (move_target_Y_CAM > _lim_CAM_top) {
            move_target_Y_CAM = _lim_CAM_top;
        }
        if (move_target_Y_CAM < _lim_CAM_bottom ) {
            move_target_Y_CAM = _lim_CAM_bottom;
        }
        if (move_target_Z_CAM > _lim_CAM_zleft) {
            move_target_Z_CAM = _lim_CAM_zleft;
        }
        if (move_target_Z_CAM < _lim_CAM_zright) {
            move_target_Z_CAM = _lim_CAM_zright;
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
        if (move_target_Y_VP > _lim_VP_top) {
            move_target_Y_VP = _lim_VP_top;
        }
        if (move_target_Y_VP < _lim_VP_bottom ) {
            move_target_Y_VP = _lim_VP_bottom;
        }
        if (move_target_Z_VP > _lim_VP_zleft) {
            move_target_Z_VP = _lim_VP_zleft;
        }
        if (move_target_Z_VP < _lim_VP_zright) {
            move_target_Z_VP = _lim_VP_zright;
        }
    }



    //目標地点までの各軸距離
    dX_CAM = move_target_X_CAM - pCAM->_X;
    dY_CAM = move_target_Y_CAM - pCAM->_Y;
    dZ_CAM = move_target_Z_CAM - pCAM->_Z;
    dX_VP = move_target_X_VP - pVP->_X;
    dY_VP = move_target_Y_VP - pVP->_Y;
    dZ_VP = move_target_Z_VP - pVP->_Z;

    if ( getSubFirst()->isBehaving() ) {

        int speed =
                ( pMYSHIP->_iMoveSpeed +
                  ( GgafDx9Util::abs(pMYSHIP->_pMover->_veloVxMove) +
                    GgafDx9Util::abs(pMYSHIP->_pMover->_veloVyMove) +
                    GgafDx9Util::abs(pMYSHIP->_pMover->_veloVzMove)
                  )
                 ) * 2; //0.7の意味は 1/√2 よりわずかに小さい
                          //これは自機が斜め移動時カメラがわずかに追いつかないようにするため
        pCAM->_pMover->setVxMoveVeloRenge(-speed, speed);
        pCAM->_pMover->setVyMoveVeloRenge(-speed, speed);
        pCAM->_pMover->setVzMoveVeloRenge(-speed, speed);
		static double acc_rate = 800.0;
        if (-slow_range_CAM < dX_CAM && dX_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVxMove *= 0.9;
            pCAM->_pMover->setVxMoveVeloAcceleration(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVxMoveVeloAcceleration(dX_CAM/acc_rate);//背後に回る時
            } else {
                pCAM->_pMover->setVxMoveVeloAcceleration(dX_CAM/acc_rate);
            }
        }
        if (-slow_range_CAM < dY_CAM && dY_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVyMove *= 0.9;
            pCAM->_pMover->setVyMoveVeloAcceleration(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVyMoveVeloAcceleration(dY_CAM/acc_rate);//背後に回る時
            } else {
                pCAM->_pMover->setVyMoveVeloAcceleration(dY_CAM/acc_rate);
            }
        }
        if (-slow_range_CAM < dZ_CAM && dZ_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVzMove *= 0.9;
            pCAM->_pMover->setVzMoveVeloAcceleration(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVzMoveVeloAcceleration(dZ_CAM/acc_rate);//背後に回る時
            } else {
                pCAM->_pMover->setVzMoveVeloAcceleration(dZ_CAM/acc_rate);
            }
        }
        pVP->_pMover->setVxMoveVeloRenge(-speed, speed);
        pVP->_pMover->setVyMoveVeloRenge(-speed, speed);
        pVP->_pMover->setVzMoveVeloRenge(-speed, speed);

        if (-slow_range_VP < dX_VP && dX_VP < slow_range_VP) {
            pVP->_pMover->_veloVxMove *= 0.9;
            pVP->_pMover->setVxMoveVeloAcceleration(0);
        } else {
            pVP->_pMover->setVxMoveVeloAcceleration(dX_VP/acc_rate);
        }
        if (-slow_range_VP < dY_VP && dY_VP < slow_range_VP) {
            pVP->_pMover->_veloVyMove *= 0.9;
            pVP->_pMover->setVyMoveVeloAcceleration(0);
        } else {
            pVP->_pMover->setVyMoveVeloAcceleration(dY_VP/acc_rate);
        }
        if (-slow_range_VP < dZ_VP && dZ_VP < slow_range_VP) {
            pVP->_pMover->_veloVzMove *= 0.9;
            pVP->_pMover->setVzMoveVeloAcceleration(0);
        } else {
            pVP->_pMover->setVzMoveVeloAcceleration(dZ_VP/acc_rate);
        }


        pCAM->_pMover->behave();
        pVP->_pMover->behave();
    }

    //サブシーンが一時停止していれば、カメラ操作できる。
    if ( getSubFirst()->isBehaving() ) {
        //スルー
    } else {
        pCAM->_pMover->_move_angle_rz_target_flg = true;
        pCAM->_pMover->_move_angle_ry_target_flg = true;

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
                pCAM->_pMover->addRzMoveAngle(4000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
                pCAM->_pMover->addRzMoveAngle(-4000);
            } else {
                pCAM->_pMover->addRzMoveAngle(0);
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
                pCAM->_pMover->addRyMoveAngle(4000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
                pCAM->_pMover->addRyMoveAngle(-4000);
            } else {
                pCAM->_pMover->addRyMoveAngle(0);
            }
            if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
                pCAM->_pMover->setMoveVelocity(4000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
                pCAM->_pMover->setMoveVelocity(-4000);
            } else {
                pCAM->_pMover->setMoveVelocity(0);
            }
        }
    }

    if (GgafDx9Input::isBeingPressedKey(DIK_O)) {
        pCAM->_pMover->setMoveAngle(0,0,0);
        _TRACE_("GgafDx9Universe Camera=("<<pCAM->_X<<","<<pCAM->_Y<<","<<pCAM->_Z<<")");
    }

//    if ( getSubFirst()->isBehaving() ) {
//        //スルー
//    } else {
//        //カメラ注視方向設定
//        pCAM->setViewPoint (
//                   pCAM->_X + (pCAM->_pMover->_vX * LEN_UNIT * PX_UNIT),
//                   pCAM->_Y + (pCAM->_pMover->_vY * LEN_UNIT * PX_UNIT),
//                   pCAM->_Z + (pCAM->_pMover->_vZ * LEN_UNIT * PX_UNIT)
//                  );
//        pCAM->_pMover->setMoveAngle(0,0,0);
//    }

}

void World::processJudgement() {
}

World::~World() {
}



