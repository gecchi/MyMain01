#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Universe::Universe(const char* prm_name) : DefaultUniverse(prm_name) {
    //y‚ß‚àz
    //‚±‚±‚ÅActor‚âScene‚ÌNEW‚ð‚Í‚µ‚Ä‚Í‚È‚ç‚È‚¢B
    //‚Ü‚¸‚Í‚±‚Ì¢‚ðì‚é‚±‚Æ‚ð—Dæ‚µ‚È‚¢‚ÆA‚¢‚ë‚¢‚ë‚Æ•s“s‡‚ª‚ ‚éB
}

void Universe::initialize() {
    World* pWorld = NEW World("WORLD");
    addSubLast(pWorld);

}

void Universe::processJudgement() {
}

void Universe::processDrawPrior() {

//    _pCamera->_pGeoMover->setAutoTargetMoveAngle(0,0,0);


    //	GgafDx9Universe::_pCamera->setGaze(GameGlobal::_pMyShip);
    //
    //
    //
    //	GgafDx9Universe::_pCamera->_pGeoMover->
    //	GgafDx9Universe::_pCamera->Z = GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini;

//    if (GgafDx9Universe::_pCamera->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini) {
//        GgafDx9Universe::_pCamera->_Z = GgafDx9Universe::_pCamera->_Z + 2000;
//    }
//    if (GgafDx9Universe::_pCamera->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_dCamZ_ini) {
//        GgafDx9Universe::_pCamera->_Z = GgafDx9Universe::_pCamera->_Z - 2000;
//    }

}
void Universe::processBehavior() {

}

Universe::~Universe() {
}
