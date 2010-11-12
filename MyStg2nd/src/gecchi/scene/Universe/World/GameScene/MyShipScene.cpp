#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyShipScene::MyShipScene(const char* prm_name) : DefaultScene(prm_name) ,
_pMyShip(NULL),
_pVamSysCamWorker(NULL) {
    _class_name = "MyShipScene";
    _pMyShip = NEW MyShip("MYSHIP");
    _pMyShip->inactivateImmediately(); //配下に仮登録のアクター発送者とかあるし
    getLordActor()->addSubGroup(KIND_MY_BODY_NOMAL, _pMyShip);
    _pVamSysCamWorker = (VamSysCamWorker*)P_UNIVERSE->_pCameraWorkerManager->getConnection("VamSysCamWorker")->refer();
    _pVamSysCamWorker->_pMyShip = _pMyShip;
    _pMyShipDivingCamWorker = (MyShipDivingCamWorker*)P_UNIVERSE->_pCameraWorkerManager->getConnection("MyShipDivingCamWorker")->refer();
    _zanki = 2;

}

void MyShipScene::initialize() {
    _TRACE_("MyShipScene initialize()");
}

void MyShipScene::reset() {

    _TRACE_("MyShipScene initialize()");
}
void MyShipScene::onActive() {
    _TRACE_("MyShipScene onActive()");
    _zanki = 2;
    fadeinSceneTree(1);
    changeProgress(MYSHIPSCENE_PROG_BEGIN);
}

void MyShipScene::processBehavior() {

    //MYSHIPSCENE_PROG_BEGIN 時の処理
    if (onActiveProgress(MYSHIPSCENE_PROG_BEGIN)) {
        fadeinSceneTree(60);
        _pMyShip->_X = Universe::_X_goneLeft;
        _pMyShip->_isNoControl = true;
    }
    if (getProgress() == MYSHIPSCENE_PROG_BEGIN) {
        changeProgress(MYSHIPSCENE_PROG_APPEARANCE_NOMAL);
    }
    if (onInactiveProgress(MYSHIPSCENE_PROG_BEGIN)) {
    }

    //MYSHIPSCENE_PROG_APPEARANCE_NOMAL 時の処理
    if (onActiveProgress(MYSHIPSCENE_PROG_APPEARANCE_NOMAL)) {
        P_UNIVERSE->pushCameraWork("MyShipDivingCamWorker");
        _pMyShipDivingCamWorker->setMoveTargetCam(-1000000, 1000000, 1000000);
        _pMyShipDivingCamWorker->setMoveTargetCamVpBy(_pMyShip);
    }
    if (getProgress() == MYSHIPSCENE_PROG_APPEARANCE_NOMAL) {
        _pMyShip->_X += 30000;
        _pMyShipDivingCamWorker->setMoveTargetCamVpBy(_pMyShip);
        if (_pMyShip->_X > 0) {
            changeProgress(MYSHIPSCENE_PROG_PLAY);
        }
    }
    if (onInactiveProgress(MYSHIPSCENE_PROG_APPEARANCE_NOMAL)) {
        P_UNIVERSE->popCameraWork();
    }

    //MYSHIPSCENE_PROG_PLAY 時の処理
    if (onActiveProgress(MYSHIPSCENE_PROG_PLAY)) {
        P_UNIVERSE->pushCameraWork("VamSysCamWorker");
        _pMyShip->_isNoControl = false;
    }
    if (getProgress() == MYSHIPSCENE_PROG_PLAY) {

    }
    if (onInactiveProgress(MYSHIPSCENE_PROG_PLAY)) {
        P_UNIVERSE->popCameraWork();
    }

    //MYSHIPSCENE_PROG_DESTROY 時の処理
    if (onActiveProgress(MYSHIPSCENE_PROG_DESTROY)) {
        _pMyShip->_pEffectMyShipExplosion->activate();
        _pMyShip->_isNoControl = true;
        fadeoutSceneTree(120);
        _zanki -= 1;
    }
    if (getProgress() == MYSHIPSCENE_PROG_DESTROY) {
        if (getActivePartFrameInProgress() == 120) {

            if (_zanki == 0) {
                throwEventToUpperTree(EVENT_ALL_MY_SHIP_WAS_DESTROYED);
                changeProgress(PROG_NOTHING);
                inactivateDelay(180);
            } else {
                throwEventToUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
                changeProgress(MYSHIPSCENE_PROG_BEGIN);
            }
        }
    }
    if (onInactiveProgress(MYSHIPSCENE_PROG_DESTROY)) {

    }
}

void MyShipScene::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_BEGIN) {
        _TRACE_("MyShipScene EVENT_MY_SHIP_WAS_DESTROYED_BEGIN was Catch!!");

        changeProgress(MYSHIPSCENE_PROG_DESTROY);
    } else if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_FINISH) {
        _TRACE_("MyShipScene EVENT_MY_SHIP_WAS_DESTROYED_FINISH was Catch!!");
        //changeProgress()
    }
}

MyShipScene::~MyShipScene() {
}
