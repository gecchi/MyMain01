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

void Universe::processPreDraw() {

//    _pCamera->_pMover->setTargetRzRyMoveAngle(0,0,0);


    //	pCAM->setGaze(GameGlobal::_pMyShip);
    //
    //
    //
    //	pCAM->_pMover->
    //	pCAM->Z = GameGlobal::_pMyShip->_Z - GgafDx9God::_cameraZ_org;

//    if (pCAM->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_cameraZ_org) {
//        pCAM->_Z = pCAM->_Z + 2000;
//    }
//    if (pCAM->_Z < GameGlobal::_pMyShip->_Z - GgafDx9God::_cameraZ_org) {
//        pCAM->_Z = pCAM->_Z - 2000;
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
