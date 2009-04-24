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
    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "B/moji");
    getLordActor()->accept(KIND_EFFECT, pDispFpsActor);
#endif
_TRACE_("GgafDx9Universe::_pCamera="<<GgafDx9Universe::_pCamera);
    GgafDx9Universe::_pCamera->_pGeoMover->setMoveAngle(0,0,0);
    GgafDx9Universe::_pCamera->_pGeoMover->setMoveVelocity(0);
    GgafDx9Universe::_pCamera->_pGeoMover->setRzMoveAngleVelocity(0);
    GgafDx9Universe::_pCamera->_pGeoMover->setRyMoveAngleVelocity(0);
    GgafDx9Universe::_pCamera->_pGeoMover->_auto_move_angle_rz_target_flg = true;
    GgafDx9Universe::_pCamera->_pGeoMover->_auto_move_angle_ry_target_flg = true;

}

void World::processJudgement() {
}

void World::processDrawPrior() {

//    GgafDx9Universe::_pCamera->_pGeoMover->setAutoTargetMoveAngle(0,0,0);


    //	GgafDx9World::GgafDx9Universe::_pCamera->setGaze(GameGlobal::_pMyShip);
    //
    //
    //
    //	GgafDx9World::GgafDx9Universe::_pCamera->_pGeoMover->
    //	GgafDx9World::GgafDx9Universe::_pCamera->Z = GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini;

//    if (GgafDx9World::GgafDx9Universe::_pCamera->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini) {
//        GgafDx9World::GgafDx9Universe::_pCamera->_Z = GgafDx9World::GgafDx9Universe::_pCamera->_Z + 2000;
//    }
//    if (GgafDx9World::GgafDx9Universe::_pCamera->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini) {
//        GgafDx9World::GgafDx9Universe::_pCamera->_Z = GgafDx9World::GgafDx9Universe::_pCamera->_Z - 2000;
//    }

}
void World::processBehavior() {
    VB::update(); //“ü—Íî•ñXV

    //ˆêŽž’âŽ~
    //TODO:Ž~‚ß‚Ä‚àframe‚Íi‚ÞQH
    if (VB::isPushedDown(VB_PAUSE)) {
        if (getSubFirst()->isBehaving()) {
            _TRACE_("PAUSE!");
            getSubFirst()->pause();
        } else {
            _TRACE_("UNPAUSE!");
            getSubFirst()->unpause();
        }
    }

    if ( getSubFirst()->isBehaving() ) {
        //ƒXƒ‹[
    } else {
        GgafDx9Universe::_pCamera->_pGeoMover->_auto_move_angle_rz_target_flg = true;
        GgafDx9Universe::_pCamera->_pGeoMover->_auto_move_angle_ry_target_flg = true;

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
                GgafDx9Universe::_pCamera->_pGeoMover->addRzMoveAngle(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_G)) {
                GgafDx9Universe::_pCamera->_pGeoMover->addRzMoveAngle(-2000);
            } else {
                GgafDx9Universe::_pCamera->_pGeoMover->addRzMoveAngle(0);
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_H)) {
                GgafDx9Universe::_pCamera->_pGeoMover->addRyMoveAngle(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_F)) {
                GgafDx9Universe::_pCamera->_pGeoMover->addRyMoveAngle(-2000);
            } else {
                GgafDx9Universe::_pCamera->_pGeoMover->addRyMoveAngle(0);
            }
            if (GgafDx9Input::isBeingPressedKey(DIK_U)) {
                GgafDx9Universe::_pCamera->_pGeoMover->setMoveVelocity(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_J)) {
                GgafDx9Universe::_pCamera->_pGeoMover->setMoveVelocity(-2000);
            } else {
                GgafDx9Universe::_pCamera->_pGeoMover->setMoveVelocity(0);
            }
        }
    }

    GgafDx9Universe::_pCamera->_pGeoMover->behave();
    GgafDx9Universe::_pCamera->setGaze (
               GgafDx9Universe::_pCamera->_X + (GgafDx9Universe::_pCamera->_pGeoMover->_vX * LEN_UNIT * PX_UNIT),
               GgafDx9Universe::_pCamera->_Y + (GgafDx9Universe::_pCamera->_pGeoMover->_vY * LEN_UNIT * PX_UNIT),
               GgafDx9Universe::_pCamera->_Z + (GgafDx9Universe::_pCamera->_pGeoMover->_vZ * LEN_UNIT * PX_UNIT)
              );


}

World::~World() {
}
