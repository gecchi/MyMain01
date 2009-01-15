#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


World::World(string prm_name) : DefaultWorld(prm_name) {
	GameScene* pGameScene = NEW GameScene("Game");
	addSubLast(pGameScene);
#ifdef OREDEBUG
	DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "moji");
	getLordActor()->accept(KIND_EFFECT, pDispFpsActor);
#endif
}

void World::processDrawPrior() {

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
