#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _TRACE_("World::World");

    //y‚ß‚àz
    //‚±‚±‚ÅActor‚âScene‚ÌNEW‚ð‚Í‚µ‚Ä‚Í‚È‚ç‚È‚¢B
    //‚Ü‚¸‚Í‚±‚Ì¢‚ðì‚é‚±‚Æ‚ð—Dæ‚µ‚È‚¢‚ÆA‚¢‚ë‚¢‚ë‚Æ•s“s‡‚ª‚ ‚éB
}

void World::initialize() {
        _TRACE_("World::initialize()");
    GameScene* pGameScene = NEW GameScene("Game");
    addSubLast(pGameScene);
#ifdef OREDEBUG
    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "moji");
    getLordActor()->accept(KIND_EFFECT, pDispFpsActor);
#endif
    //‰ŠúƒJƒƒ‰ˆÊ’u

    pCAM->_X = (pCAM->_Z / 2); //‚S‚T“xŽÎ‚ß‚©‚çŒ©‚é
    pCAM->setGaze(0,0,0);
    pCAM->_pMover->setMoveAngle(0,0,0);


    pCAM->_pMover->setVxMoveVelocityRenge(-8000, 8000);
    pCAM->_pMover->setVxMoveVelocity(0);
    pCAM->_pMover->setVxMoveAcceleration(0);

    pCAM->_pMover->setVyMoveVelocityRenge(-4500, 4500);
    pCAM->_pMover->setVyMoveVelocity(0);
    pCAM->_pMover->setVyMoveAcceleration(0);

    pCAM->_pMover->setVzMoveVelocityRenge(-4500, 4500);
    pCAM->_pMover->setVzMoveVelocity(0);
    pCAM->_pMover->setVzMoveAcceleration(0);
}



void World::processBehavior() {
    VB::update(); //“ü—Íî•ñXV


    //TODO:Ž~‚ß‚Ä‚àframe‚Íi‚ÞQH
    if (VB::isPushedDown(VB_PAUSE)) {
        if (getSubFirst()->isBehaving()) {
            _TRACE_("PAUSE!");
            //ƒJƒƒ‰’Ž‹•ûŒüÝ’è
            pCAM->_pMover->setMoveAngle(
                                pCAM->_gazeX,
                                pCAM->_gazeY,
                                pCAM->_gazeZ
                           );

            getSubFirst()->pause();     //ˆêŽž’âŽ~
        } else {
            _TRACE_("UNPAUSE!");
            getSubFirst()->unpause();   //ˆêŽž’âŽ~‰ðœ
        }
    }



    static int dX, dY, dZ;
    static int X_screen_left = (int)(-1 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2);
    static int dZ_camera_init = -1 * pCAM->_cameraZ_org*2 * LEN_UNIT * PX_UNIT;

    //if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
    if ( getSubFirst()->isBehaving() ) {
        if (VB::isBeingPressed(VB_BUTTON4)) {
            dZ = (GameGlobal::_pMyShip->_Z - (dZ_camera_init / 2)) - pCAM->_Z;
            dX = X_screen_left - pCAM->_X;
        } else {
            dZ = (GameGlobal::_pMyShip->_Z - dZ_camera_init) - pCAM->_Z;
            dX = (0 - (dZ_camera_init / 8)) - pCAM->_X;
        }
        if (-40000 < dZ && dZ < 40000) {
            pCAM->_pMover->_veloVzMove *= 0.8;
            pCAM->_pMover->setVzMoveAcceleration(0);
        } else {
            pCAM->_pMover->setVzMoveAcceleration(dZ/200);
        }
        if (-40000 < dX && dX < 40000) {
            pCAM->_pMover->_veloVxMove *= 0.8;
            pCAM->_pMover->setVxMoveAcceleration(0);
        } else {
            pCAM->_pMover->setVxMoveAcceleration(dX/500);
        }
        pCAM->setGaze(0, 0, GameGlobal::_pMyShip->_Z);

        pCAM->_pMover->behave();
    }

    //}











    //ƒTƒuƒV[ƒ“‚ªˆêŽž’âŽ~‚µ‚Ä‚¢‚ê‚ÎAƒJƒƒ‰‘€ì‚Å‚«‚éB
    if ( getSubFirst()->isBehaving() ) {
        //ƒXƒ‹[
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


    if ( getSubFirst()->isBehaving() ) {
        //ƒXƒ‹[
    } else {
        //ƒJƒƒ‰’Ž‹•ûŒüÝ’è
        pCAM->setGaze (
                   pCAM->_X + (pCAM->_pMover->_vX * LEN_UNIT * PX_UNIT),
                   pCAM->_Y + (pCAM->_pMover->_vY * LEN_UNIT * PX_UNIT),
                   pCAM->_Z + (pCAM->_pMover->_vZ * LEN_UNIT * PX_UNIT)
                  );

        if (GgafDx9Input::isBeingPressedKey(DIK_O)) {
            pCAM->_pMover->setMoveAngle(0,0,0);
            _TRACE_("GgafDx9Universe Camera=("<<pCAM->_X<<","<<pCAM->_Y<<","<<pCAM->_Z<<")");
        }
    }

}

void World::processJudgement() {
}

World::~World() {
}
