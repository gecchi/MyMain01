#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _TRACE_("World::World");
    pCAM->_pos_camera = 0;
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
    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "moji");
    getLordActor()->accept(KIND_EFFECT, pDispFpsActor);
#endif
    //初期カメラ位置
    int speed = pMYSHIP->_iMoveSpeed * 0.99;

    pCAM->_pos_camera = 0;
    _dZ_camera_init = -1 * pCAM->_cameraZ_org * LEN_UNIT * PX_UNIT;

    pCAM->_X = _dZ_camera_init / 10; //少し斜めめから見てる
    pCAM->_Y = 0; //４５度斜めから見る
    pCAM->_Z = -_dZ_camera_init;

    pCAM->setViewPoint(0,0,0);
    pCAM->_pMover->setMoveAngle(0,0,0);


    pCAM->_pMover->setVxMoveVelocityRenge(-speed, speed);
    pCAM->_pMover->setVxMoveVelocity(0);
    pCAM->_pMover->setVxMoveAcceleration(0);

    pCAM->_pMover->setVyMoveVelocityRenge(-speed, speed);
    pCAM->_pMover->setVyMoveVelocity(0);
    pCAM->_pMover->setVyMoveAcceleration(0);

    pCAM->_pMover->setVzMoveVelocityRenge(-speed, speed);
    pCAM->_pMover->setVzMoveVelocity(0);
    pCAM->_pMover->setVzMoveAcceleration(0);

    pCAM->_pViewPoint->_X = 0;
    pCAM->_pViewPoint->_Y = 0;
    pCAM->_pViewPoint->_Z = pMYSHIP->_Z;


    pCAM->_pViewPoint->_pMover->setMoveAngle(0,0,0);

    pCAM->_pViewPoint->_pMover->setVxMoveVelocityRenge(-speed, speed);
    pCAM->_pViewPoint->_pMover->setVxMoveVelocity(0);
    pCAM->_pViewPoint->_pMover->setVxMoveAcceleration(0);

    pCAM->_pViewPoint->_pMover->setVyMoveVelocityRenge(-speed, speed);
    pCAM->_pViewPoint->_pMover->setVyMoveVelocity(0);
    pCAM->_pViewPoint->_pMover->setVyMoveAcceleration(0);

    pCAM->_pViewPoint->_pMover->setVzMoveVelocityRenge(-speed, speed);
    pCAM->_pViewPoint->_pMover->setVzMoveVelocity(0);
    pCAM->_pViewPoint->_pMover->setVzMoveAcceleration(0);


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
        if (pCAM->_pos_camera == 0) {
            pCAM->_pos_camera = 1;
        } else if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
            if (VB::isBeingPressed(VB_RIGHT)) {
                pCAM->_pos_camera = 3;
            } else if (VB::isBeingPressed(VB_LEFT)) {
                pCAM->_pos_camera = 0;
            } else {
                if (pCAM->_Z > GameGlobal::_pMyShip->_Z) {
                    pCAM->_pos_camera = 3;
                } else {
                    pCAM->_pos_camera = 0;
                }
            }
        } else if (pCAM->_pos_camera == 3) {
            pCAM->_pos_camera = 2;
        }
        _frame_pushdown_zmove = _lifeframe;
    }


    if (VB::isReleasedUp(VB_ZMOVE)) {
        if (_frame_pushdown_zmove + 15 > _lifeframe) {
//            if (pCAM->_pos_camera == 0) {
//                pCAM->_pos_camera = 1;
//            } else if (pCAM->_pos_camera == 1) {
//                pCAM->_pos_camera = 0;
//            } else if (pCAM->_pos_camera == 2) {
//                pCAM->_pos_camera = 3;
//            } else if (pCAM->_pos_camera == 3) {
//                pCAM->_pos_camera = 2;
//            }
        } else {
            if (pCAM->_pos_camera == 0) {
                pCAM->_pos_camera = 0;
            } else if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
                if (VB::isBeingPressed(VB_RIGHT)) {
                    pCAM->_pos_camera = 3;
                } else if (VB::isBeingPressed(VB_LEFT)) {
                    pCAM->_pos_camera = 0;
                } else {
                    if (pCAM->_Z > GameGlobal::_pMyShip->_Z) {
                        pCAM->_pos_camera = 3;
                    } else {
                        pCAM->_pos_camera = 0;
                    }
                }
            } else if (pCAM->_pos_camera == 3) {
                pCAM->_pos_camera = 3;
            }
        }

    }






    static int dX_from, dY_from, dZ_from;
    static int dX_to, dY_to, dZ_to;
//    startc int X_MyShip_prev = pMYSHIP->_X;
//    startc int Y_MyShip_prev = pMYSHIP->_Y;
//    startc int Z_MyShip_prev = pMYSHIP->_Z;
    static GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;
    static int X_screen_left = (int)(-1 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2);
    static int Y_screen_top = (int)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * LEN_UNIT / 2);
    //if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
    if ( getSubFirst()->isBehaving() ) {
        if (pCAM->_pos_camera == 0) {
            dZ_from = (GameGlobal::_pMyShip->_Z - _dZ_camera_init) - pCAM->_Z;
            dX_from = (0 - (_dZ_camera_init / 4)) - pCAM->_X;
            dY_from = 0 - pCAM->_Y;

            dX_to = 0;
            dY_to = 0;
            dZ_to = pMYSHIP->_Z - pCAM->_pViewPoint->_Z;

        } else if (pCAM->_pos_camera == 1) {
            dZ_from = (GameGlobal::_pMyShip->_Z - (_dZ_camera_init / 128)) - pCAM->_Z;
            dX_from = X_screen_left + 100000 - pCAM->_X;
            dY_from = Y_screen_top + 200000 - pCAM->_Y;

            dX_to = 0;
            dY_to = 0;
            dZ_to = pMYSHIP->_Z - pVP->_Z;

        } else if (pCAM->_pos_camera == 2) {
            dZ_from = (GameGlobal::_pMyShip->_Z + (_dZ_camera_init / 128)) - pCAM->_Z;
            dX_from = X_screen_left + 100000 - pCAM->_X;
            dY_from = Y_screen_top + 200000 - pCAM->_Y;

            dX_to = 0;
            dY_to = 0;
            dZ_to = pMYSHIP->_Z - pVP->_Z;

        } else if (pCAM->_pos_camera == 3) {
            dZ_from = (GameGlobal::_pMyShip->_Z + _dZ_camera_init) - pCAM->_Z;
            dX_from = (0 - (_dZ_camera_init / 4)) - pCAM->_X;
            dY_from = 0 - pCAM->_Y;

            dX_to = 0;
            dY_to = 0;
            dZ_to = pMYSHIP->_Z - pVP->_Z;
        }

        static int slow_reng_from = 30000;

        if (-slow_reng_from < dZ_from && dZ_from < slow_reng_from) {
            pCAM->_pMover->_veloVzMove *= 0.7;
            pCAM->_pMover->setVzMoveAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //上に回る時
                pCAM->_pMover->setVzMoveAcceleration(dZ_from/1000.0);
            } else {                                                //横に回るとき
                pCAM->_pMover->setVzMoveAcceleration(dZ_from/3.0);
            }
        }
        if (-slow_reng_from < dX_from && dX_from < slow_reng_from) {
            pCAM->_pMover->_veloVxMove *= 0.7;
            pCAM->_pMover->setVxMoveAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //上にに回る時
                pCAM->_pMover->setVxMoveAcceleration(dX_from/3.0);
            } else {                                                //横に回るとき
                pCAM->_pMover->setVxMoveAcceleration(dX_from/1000.0);
            }
        }

        if (-slow_reng_from < dY_from && dY_from < slow_reng_from) {
            pCAM->_pMover->_veloVyMove *= 0.7;
            pCAM->_pMover->setVyMoveAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //上にに回る時
                pCAM->_pMover->setVyMoveAcceleration(dY_from/3.01000.0);
            } else {                                                //横に回るとき
                pCAM->_pMover->setVyMoveAcceleration(dY_from/1000.0);
            }
        }


        static int slow_reng_to = 10000;

        if (-slow_reng_to < dZ_to && dZ_to < slow_reng_to) {
            pVP->_pMover->_veloVzMove *= 0.7;
            pVP->_pMover->setVzMoveAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //上に回る時
                pVP->_pMover->setVzMoveAcceleration(dZ_to/1000.0);
            } else {                                                //横に回るとき
                pVP->_pMover->setVzMoveAcceleration(dZ_to/3.0);
            }
        }
        if (-slow_reng_to < dX_to && dX_to < slow_reng_to) {
            pVP->_pMover->_veloVxMove *= 0.7;
            pVP->_pMover->setVxMoveAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //上にに回る時
                pVP->_pMover->setVxMoveAcceleration(dX_to/3.0);
            } else {                                                //横に回るとき
                pVP->_pMover->setVxMoveAcceleration(dX_to/1000.0);
            }
        }


        if (-slow_reng_to < dY_to && dY_to < slow_reng_to) {
            pCAM->_pMover->_veloVyMove *= 0.7;
            pCAM->_pMover->setVyMoveAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //上にに回る時
                pVP->_pMover->setVyMoveAcceleration(dY_to/1000.0);
            } else {                                                //横に回るとき
                pVP->_pMover->setVyMoveAcceleration(dY_to/3.0);
            }
        }

        pCAM->setViewPoint(0, 0, GameGlobal::_pMyShip->_Z);//
        //GameGlobal::_pMyShip->_Zこれを何とかすればいいはず
        //pCAM->setViewPoint(0, 0, 0);//


        pCAM->_pMover->behave();
        pVP->_pMover->behave();
    }

    //}


    //サブシーンが一時停止していれば、カメラ操作できる。
    if ( getSubFirst()->isBehaving() ) {
        //スルー
    } else {
        pCAM->_pMover->_move_angle_rz_target_flg = true;
        pCAM->_pMover->_move_angle_ry_target_flg = true;

        if (GgafDx9Input::isBeingPressedKey(DIK_SPACE)) {
            if (GgafDx9Input::isBeingPressedKey(DIK_T)) {
                pCAM->_Y += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_G)) {
                pCAM->_Y -= 2000;
            } else {

            }

            if (GgafDx9Input::isBeingPressedKey(DIK_H)) {
                pCAM->_X += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_F)) {
                pCAM->_X -= 2000;
            } else {
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_U)) {
                pCAM->_Z += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_J)) {
                pCAM->_Z -= 2000;
            } else {
            }

        } else {
            if (GgafDx9Input::isBeingPressedKey(DIK_T)) {
                pCAM->_pMover->addRzMoveAngle(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_G)) {
                pCAM->_pMover->addRzMoveAngle(-2000);
            } else {
                pCAM->_pMover->addRzMoveAngle(0);
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_H)) {
                pCAM->_pMover->addRyMoveAngle(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_F)) {
                pCAM->_pMover->addRyMoveAngle(-2000);
            } else {
                pCAM->_pMover->addRyMoveAngle(0);
            }
            if (GgafDx9Input::isBeingPressedKey(DIK_U)) {
                pCAM->_pMover->setMoveVelocity(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_J)) {
                pCAM->_pMover->setMoveVelocity(-2000);
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
