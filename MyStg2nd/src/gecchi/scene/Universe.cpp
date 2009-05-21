#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Universe::Universe(const char* prm_name) : DefaultUniverse(prm_name) {
	_TRACE_("Universe::Universe()");
    //y‚ß‚àz
    //‚±‚±‚ÅActor‚âScene‚ÌNEW‚ğ‚Í‚µ‚Ä‚Í‚È‚ç‚È‚¢B
    //‚Ü‚¸‚Í‚±‚Ì¢‚ğì‚é‚±‚Æ‚ğ—Dæ‚µ‚È‚¢‚ÆA‚¢‚ë‚¢‚ë‚Æ•s“s‡‚ª‚ ‚éB
}

void Universe::initialize() {
	_TRACE_("Universe::initialize()");
}

void Universe::processJudgement() {
}

void Universe::processDrawPrior() {

//    _pCamera->_pGeoMover->setTargetRzRyMoveAngle(0,0,0);


    //	GgafDx9Universe::_pCamera->setGaze(GameGlobal::_pMyShip);
    //
    //
    //
    //	GgafDx9Universe::_pCamera->_pGeoMover->
    //	GgafDx9Universe::_pCamera->Z = GameGlobal::_pMyShip->_Z - GgafDx9God::_cameraZ_org;

//    if (GgafDx9Universe::_pCamera->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_cameraZ_org) {
//        GgafDx9Universe::_pCamera->_Z = GgafDx9Universe::_pCamera->_Z + 2000;
//    }
//    if (GgafDx9Universe::_pCamera->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_cameraZ_org) {
//        GgafDx9Universe::_pCamera->_Z = GgafDx9Universe::_pCamera->_Z - 2000;
//    }

}
void Universe::processBehavior() {
    if (_lifeframe == 2) {
        //¢ŠE‚ğì¬
        World* pWorld = NEW World("WORLD");
        addSubLast(pWorld);
    }


}

Universe::~Universe() {
}
