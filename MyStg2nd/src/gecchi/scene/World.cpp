#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultWorld(prm_name) {
    GameScene* pGameScene = NEW GameScene("Game");
    addSubLast(pGameScene);
#ifdef OREDEBUG
//    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "P/moji");
//    getLordActor()->accept(KIND_EFFECT, pDispFpsActor);
#endif
    _pTestBoard = NEW DefaultBoardActor("BOARD", "B/hoge", "DefaultBoardTechnique");
    _pTestBoard->_x = 50;
    _pTestBoard->_y = 50;
    getLordActor()->accept(KIND_EFFECT, _pTestBoard);


}

void World::processDrawPrior() {
    _pTestBoard->_x = _pTestBoard->_x + 1.0;
    _pTestBoard->_x = _pTestBoard->_y + 1.0;

    //	GgafDx9World::_pCamera->setGaze(GameGlobal::_pMyShip);
    //
    //
    //
    //	GgafDx9World::_pCamera->_pGeoMover->
    //	GgafDx9World::_pCamera->Z = GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini;

    if (GgafDx9World::_pCamera->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini) {
        GgafDx9World::_pCamera->_Z = GgafDx9World::_pCamera->_Z + 2000;
    }
    if (GgafDx9World::_pCamera->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini) {
        GgafDx9World::_pCamera->_Z = GgafDx9World::_pCamera->_Z - 2000;
    }

}

World::~World() {
}
