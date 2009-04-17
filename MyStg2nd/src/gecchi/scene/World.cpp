#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultWorld(prm_name) {
    //y‚ß‚àz
    //‚±‚±‚ÅActor‚âScene‚ÌNEW‚ğ‚Í‚µ‚Ä‚Í‚È‚ç‚È‚¢B
    //‚Ü‚¸‚Í¢ŠE‚ğì‚é‚±‚Æ‚ğ—Dæ‚µ‚È‚¢‚ÆA‚¢‚ë‚¢‚ë‚Æ•s“s‡‚ª‚ ‚éB
}

void World::initialize() {
    GameScene* pGameScene = NEW GameScene("Game");
    addSubLast(pGameScene);
#ifdef OREDEBUG
    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "B/moji");
    getLordActor()->accept(KIND_EFFECT, pDispFpsActor);
#endif
//    _pCamera->setGaze(0,0,0);
//    _pCamera->_pGeoMover->setRyMoveAngleVelocity(1000);
//    _pCamera->_pGeoMover->setMoveVelocity(3000);
//    _pCamera->_pGeoMover->setRzRyMoveAngle(0,0);
//    _pCamera->_pGeoMover->setRyMoveAngleVelocityRenge(-100, 100);
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
    VB::update(); //“ü—Íî•ñXV

    //ˆê’â~
    //TODO:~‚ß‚Ä‚àframe‚Íi‚ŞQH
    if (VB::isPushedDown(VB_PAUSE)) {
        if (getSubFirst()->isBehaving()) {
            _TRACE_("PAUSE!");
            getSubFirst()->pause();
        } else {
            _TRACE_("UNPAUSE!");
            getSubFirst()->unpause();
        }
    }
}

World::~World() {
}
