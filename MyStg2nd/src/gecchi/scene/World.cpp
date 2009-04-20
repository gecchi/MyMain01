#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultWorld(prm_name) {
    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずは世界を作ることを優先しないと、いろいろと不都合がある。
}

void World::initialize() {
    GameScene* pGameScene = NEW GameScene("Game");
    addSubLast(pGameScene);
#ifdef OREDEBUG
    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "B/moji");
    getLordActor()->accept(KIND_EFFECT, pDispFpsActor);
#endif
    _pCamera->_pGeoMover->setRotAngle(0,0,0);
    _pCamera->_pGeoMover->setMoveVelocity(0);
    _pCamera->_pGeoMover->_auto_move_angle_rz_target_flg = true;
    _pCamera->_pGeoMover->_auto_move_angle_ry_target_flg = true;

}
void World::processDrawPrior() {

//    _pCamera->_pGeoMover->setAutoTargetMoveAngle(0,0,0);


    //	GgafDx9World::_pCamera->setGaze(GameGlobal::_pMyShip);
    //
    //
    //
    //	GgafDx9World::_pCamera->_pGeoMover->
    //	GgafDx9World::_pCamera->Z = GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini;

//    if (GgafDx9World::_pCamera->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini) {
//        GgafDx9World::_pCamera->_Z = GgafDx9World::_pCamera->_Z + 2000;
//    }
//    if (GgafDx9World::_pCamera->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini) {
//        GgafDx9World::_pCamera->_Z = GgafDx9World::_pCamera->_Z - 2000;
//    }

}
void World::processBehavior() {
    VB::update(); //入力情報更新

    //一時停止
    //TODO:止めてもframeは進む＿？
    if (VB::isPushedDown(VB_PAUSE)) {
        if (getSubFirst()->isBehaving()) {
            _TRACE_("PAUSE!");
            getSubFirst()->pause();
        } else {
            _TRACE_("UNPAUSE!");
            getSubFirst()->unpause();
        }
    }


    if (VB::isBeingPressed(DIK_T)) {
        _pCamera->_pGeoMover->setRyMoveAngleVelocity(-4000);
    }
    if (VB::isBeingPressed(DIK_G)) {
        _pCamera->_pGeoMover->setRyMoveAngleVelocity(4000);
    }
    if (VB::isBeingPressed(DIK_F)) {
        _pCamera->_pGeoMover->setRzMoveAngleVelocity(4000);
    }
    if (VB::isBeingPressed(DIK_H)) {
        _pCamera->_pGeoMover->setRzMoveAngleVelocity(-4000);
    }
    if (VB::isBeingPressed(DIK_L)) {
        _pCamera->_pGeoMover->setMoveVelocity(4000);
    } else {
        _pCamera->_pGeoMover->setMoveVelocity(0);
    }
    _pCamera->_pGeoMover->behave();
    _pCamera->setGaze (
               _pCamera->_X + (_pCamera->_pGeoMover->_vX * LEN_UNIT * PX_UNIT),
               _pCamera->_Y + (_pCamera->_pGeoMover->_vY * LEN_UNIT * PX_UNIT),
               _pCamera->_Z + (_pCamera->_pGeoMover->_vZ * LEN_UNIT * PX_UNIT)
              );

}

World::~World() {
}
