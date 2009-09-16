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
    int speed = pMYSHIP->_iMoveSpeed * 0.9;

    pCAM->_pos_camera = 0;
    _dZ_camera_init = -1 * pCAM->_cameraZ_org * LEN_UNIT * PX_UNIT;

    pCAM->_X = _dZ_camera_init / 10; //少し斜めめから見てる
    pCAM->_Y = 0; //４５度斜めから見る
    pCAM->_Z = -_dZ_camera_init;

    pCAM->setGaze(0,0,0);
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
}



void World::processBehavior() {
    VB::update(); //入力情報更新


    //TODO:止めてもframeは進む＿？
    if (VB::isPushedDown(VB_PAUSE)) {
        if (getSubFirst()->isBehaving()) {
            _TRACE_("PAUSE!");
            //カメラ注視方向設定
            pCAM->_pMover->setMoveAngle(
                                pCAM->_gazeX,
                                pCAM->_gazeY,
                                pCAM->_gazeZ
                           );

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
//			if (VB::isBeingPressed(VB_RIGHT)) {
//				pCAM->_pos_camera = 3;
//			} else if (VB::isBeingPressed(VB_LEFT)) {
//				pCAM->_pos_camera = 0;
//			} else {
                if (pCAM->_Z > GameGlobal::_pMyShip->_Z) {
                    pCAM->_pos_camera = 3;
                } else {
                    pCAM->_pos_camera = 0;
                }
//			}
        } else if (pCAM->_pos_camera == 3) {
            pCAM->_pos_camera = 2;
        }
        _frame_pushdown_zmove = _lifeframe;
    }


    if (VB::isReleasedUp(VB_ZMOVE)) {
        if (_frame_pushdown_zmove + 15 > _lifeframe) {
            if (pCAM->_pos_camera == 0) {
                pCAM->_pos_camera = 1;
            } else if (pCAM->_pos_camera == 1) {
                pCAM->_pos_camera = 0;
            } else if (pCAM->_pos_camera == 2) {
                pCAM->_pos_camera = 3;
            } else if (pCAM->_pos_camera == 3) {
                pCAM->_pos_camera = 2;
            }
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






    static int dX, dY, dZ;
    static int X_screen_left = (int)(-1 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2);

    //if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
    if ( getSubFirst()->isBehaving() ) {
        if (pCAM->_pos_camera == 0) {
            dZ = (GameGlobal::_pMyShip->_Z - _dZ_camera_init) - pCAM->_Z;
            dX = (0 - (_dZ_camera_init / 6)) - pCAM->_X;
        } else if (pCAM->_pos_camera == 1) {
            dZ = (GameGlobal::_pMyShip->_Z - (_dZ_camera_init / 10)) - pCAM->_Z;
            dX = X_screen_left - 200000 - pCAM->_X;
        } else if (pCAM->_pos_camera == 2) {
            dZ = (GameGlobal::_pMyShip->_Z + (_dZ_camera_init / 10)) - pCAM->_Z;
            dX = X_screen_left - 200000 - pCAM->_X;
        } else if (pCAM->_pos_camera == 3) {
            dZ = (GameGlobal::_pMyShip->_Z + _dZ_camera_init) - pCAM->_Z;
            dX = (0 - (_dZ_camera_init / 6)) - pCAM->_X;
        }

        if (-30000 < dZ && dZ < 30000) {
            pCAM->_pMover->_veloVzMove *= 0.8;
            pCAM->_pMover->setVzMoveAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //後ろに回る時
                pCAM->_pMover->setVzMoveAcceleration(dZ/1000);
            } else {                                                //横に回るとき
                pCAM->_pMover->setVzMoveAcceleration(dZ/700);
            }
        }
        if (-30000 < dX && dX < 30000) {
            pCAM->_pMover->_veloVxMove *= 0.8;
            pCAM->_pMover->setVxMoveAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //後ろに回る時
                pCAM->_pMover->setVxMoveAcceleration(dX/800);
            } else {                                                //横に回るとき
                pCAM->_pMover->setVxMoveAcceleration(dX/4000);
            }
    }
        pCAM->setGaze(0, 0, GameGlobal::_pMyShip->_Z);

        pCAM->_pMover->behave();
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

    if ( getSubFirst()->isBehaving() ) {
        //スルー
    } else {
        //カメラ注視方向設定
        pCAM->setGaze (
                   pCAM->_X + (pCAM->_pMover->_vX * LEN_UNIT * PX_UNIT),
                   pCAM->_Y + (pCAM->_pMover->_vY * LEN_UNIT * PX_UNIT),
                   pCAM->_Z + (pCAM->_pMover->_vZ * LEN_UNIT * PX_UNIT)
                  );
        pCAM->_pMover->setMoveAngle(0,0,0);
    }

}

void World::processJudgement() {
}

World::~World() {
}
