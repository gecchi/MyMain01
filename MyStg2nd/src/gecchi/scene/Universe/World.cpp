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

    GgafDx9Universe::_pCamera->_X = GgafDx9Universe::_pCamera->_Z; //‚S‚T“xŽÎ‚ß‚©‚çŒ©‚é
    GgafDx9Universe::_pCamera->setGaze(0,0,0);
    GgafDx9Universe::_pCamera->_pMover->setMoveAngle(0,0,0);
//

_TRACE_("GgafDx9Universe::_pCamera="<<GgafDx9Universe::_pCamera);

}



void World::processBehavior() {
    VB::update(); //“ü—Íî•ñXV


    //TODO:Ž~‚ß‚Ä‚àframe‚Íi‚ÞQH
    if (VB::isPushedDown(VB_PAUSE)) {
        if (getSubFirst()->isBehaving()) {
            _TRACE_("PAUSE!");
            getSubFirst()->pause();     //ˆêŽž’âŽ~
        } else {
            _TRACE_("UNPAUSE!");
            getSubFirst()->unpause();   //ˆêŽž’âŽ~‰ðœ
        }
    }

    //ƒTƒuƒV[ƒ“‚ªˆêŽž’âŽ~‚µ‚Ä‚¢‚ê‚ÎAƒJƒƒ‰‘€ì‚Å‚«‚éB
    if ( getSubFirst()->isBehaving() ) {
        //ƒXƒ‹[
    } else {
        GgafDx9Universe::_pCamera->_pMover->_move_angle_rz_target_flg = true;
        GgafDx9Universe::_pCamera->_pMover->_move_angle_ry_target_flg = true;

        if (GgafDx9Input::isBeingPressedKey(DIK_SPACE)) {
            if (GgafDx9Input::isBeingPressedKey(DIK_T)) {
                GgafDx9Universe::_pCamera->_Y += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_G)) {
                GgafDx9Universe::_pCamera->_Y -= 2000;
            } else {

            }

            if (GgafDx9Input::isBeingPressedKey(DIK_H)) {
                GgafDx9Universe::_pCamera->_X += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_F)) {
                GgafDx9Universe::_pCamera->_X -= 2000;
            } else {
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_U)) {
                GgafDx9Universe::_pCamera->_Z += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_J)) {
                GgafDx9Universe::_pCamera->_Z -= 2000;
            } else {
            }

        } else {
            if (GgafDx9Input::isBeingPressedKey(DIK_T)) {
                GgafDx9Universe::_pCamera->_pMover->addRzMoveAngle(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_G)) {
                GgafDx9Universe::_pCamera->_pMover->addRzMoveAngle(-2000);
            } else {
                GgafDx9Universe::_pCamera->_pMover->addRzMoveAngle(0);
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_H)) {
                GgafDx9Universe::_pCamera->_pMover->addRyMoveAngle(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_F)) {
                GgafDx9Universe::_pCamera->_pMover->addRyMoveAngle(-2000);
            } else {
                GgafDx9Universe::_pCamera->_pMover->addRyMoveAngle(0);
            }
            if (GgafDx9Input::isBeingPressedKey(DIK_U)) {
                GgafDx9Universe::_pCamera->_pMover->setMoveVelocity(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_J)) {
                GgafDx9Universe::_pCamera->_pMover->setMoveVelocity(-2000);
            } else {
                GgafDx9Universe::_pCamera->_pMover->setMoveVelocity(0);
            }
        }
    }


    if ( getSubFirst()->isBehaving() ) {
        //ƒXƒ‹[
    } else {
        //ƒJƒƒ‰’Ž‹•ûŒüÝ’è
        GgafDx9Universe::_pCamera->setGaze (
                   GgafDx9Universe::_pCamera->_X + (GgafDx9Universe::_pCamera->_pMover->_vX * LEN_UNIT * PX_UNIT),
                   GgafDx9Universe::_pCamera->_Y + (GgafDx9Universe::_pCamera->_pMover->_vY * LEN_UNIT * PX_UNIT),
                   GgafDx9Universe::_pCamera->_Z + (GgafDx9Universe::_pCamera->_pMover->_vZ * LEN_UNIT * PX_UNIT)
                  );

        if (GgafDx9Input::isBeingPressedKey(DIK_O)) {
            GgafDx9Universe::_pCamera->_pMover->setMoveAngle(0,0,0);
            _TRACE_("GgafDx9Universe Camera=("<<GgafDx9Universe::_pCamera->_X<<","<<GgafDx9Universe::_pCamera->_Y<<","<<GgafDx9Universe::_pCamera->_Z<<")");
        }
    }

}

void World::processJudgement() {
}

World::~World() {
}
