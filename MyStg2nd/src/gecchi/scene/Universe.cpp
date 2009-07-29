#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Universe::Universe(const char* prm_name) : DefaultUniverse(prm_name) {
	_TRACE_("Universe::Universe()");
    //【めも】
    //ここでActorやSceneのNEWをはしてはならない。
    //まずはこの世を作ることを優先しないと、いろいろと不都合がある。
}

void Universe::initialize() {
	_TRACE_("Universe::initialize()");
}

void Universe::processJudgement() {
}

void Universe::processDrawPrior() {

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
        //世界を作成
        World* pWorld = NEW World("WORLD");
        addSubLast(pWorld);
    }


}

Universe::~Universe() {
}
