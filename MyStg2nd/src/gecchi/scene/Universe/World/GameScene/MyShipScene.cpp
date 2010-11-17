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
    reset();
}

void MyShipScene::reset() {
    _TRACE_("MyShipScene reset()");
    _zanki = 2;
    unblindScene();
    changeProgress(MYSHIPSCENE_SCENE_PROG_INIT);
}
void MyShipScene::onActive() {
}

void MyShipScene::processBehavior() {

    //MYSHIPSCENE_SCENE_PROG_INIT 時の処理
    if (onActiveProgress(MYSHIPSCENE_SCENE_PROG_INIT)) {
    }
    if (getProgress() == MYSHIPSCENE_SCENE_PROG_INIT) {
        changeProgress(MYSHIPSCENE_SCENE_PROG_BEGIN);
    }
    if (onInactiveProgress(MYSHIPSCENE_SCENE_PROG_INIT)) {
    }

    //MYSHIPSCENE_SCENE_PROG_BEGIN 時の処理
    if (onActiveProgress(MYSHIPSCENE_SCENE_PROG_BEGIN)) {
        unblindScene();
        _pMyShip->reset();
        _pMyShip->activate();
        _TRACE_("MyShipScene onActiveProgress(MYSHIPSCENE_SCENE_PROG_BEGIN)");
//        fadeinSceneTree(60);
        _pMyShip->_X = Universe::_X_goneLeft;
        _pMyShip->_isNoControl = true;
    }
    if (getProgress() == MYSHIPSCENE_SCENE_PROG_BEGIN) {
        changeProgress(MYSHIPSCENE_SCENE_PROG_APPEARANCE_NOMAL);
    }
    if (onInactiveProgress(MYSHIPSCENE_SCENE_PROG_BEGIN)) {
        _TRACE_("MyShipScene onInactiveProgress(MYSHIPSCENE_SCENE_PROG_BEGIN)");
    }

    //MYSHIPSCENE_SCENE_PROG_APPEARANCE_NOMAL 時の処理
    if (onActiveProgress(MYSHIPSCENE_SCENE_PROG_APPEARANCE_NOMAL)) {
        _TRACE_("MyShipScene onActiveProgress(MYSHIPSCENE_SCENE_PROG_APPEARANCE_NOMAL)");
        P_UNIVERSE->pushCameraWork("MyShipDivingCamWorker");
        _pMyShipDivingCamWorker->setMoveTargetCam(-1000000, 1000000, 1000000);
        _pMyShipDivingCamWorker->setMoveTargetCamVpBy(_pMyShip);
    }
    if (getProgress() == MYSHIPSCENE_SCENE_PROG_APPEARANCE_NOMAL) {
        _pMyShip->_X += 30000;
        _pMyShipDivingCamWorker->setMoveTargetCamVpBy(_pMyShip);
        if (_pMyShip->_X > 0) {
            _pMyShip->_X = 0;
            changeProgress(MYSHIPSCENE_SCENE_PROG_PLAY);
        }
    }
    if (onInactiveProgress(MYSHIPSCENE_SCENE_PROG_APPEARANCE_NOMAL)) {
        _TRACE_("MyShipScene onInactiveProgress(MYSHIPSCENE_SCENE_PROG_APPEARANCE_NOMAL)");
        P_UNIVERSE->popCameraWork();
    }

    //MYSHIPSCENE_SCENE_PROG_PLAY 時の処理
    if (onActiveProgress(MYSHIPSCENE_SCENE_PROG_PLAY)) {
        _TRACE_("MyShipScene onActiveProgress(MYSHIPSCENE_SCENE_PROG_PLAY)");
        P_UNIVERSE->pushCameraWork("VamSysCamWorker");
        _pMyShip->_isNoControl = false;
    }
    if (getProgress() == MYSHIPSCENE_SCENE_PROG_PLAY) {

    }
    if (onInactiveProgress(MYSHIPSCENE_SCENE_PROG_PLAY)) {
        _TRACE_("MyShipScene onInactiveProgress(MYSHIPSCENE_SCENE_PROG_PLAY)");
        P_UNIVERSE->popCameraWork();
    }

    //MYSHIPSCENE_SCENE_PROG_DESTROY 時の処理
    if (onActiveProgress(MYSHIPSCENE_SCENE_PROG_DESTROY)) {
        _TRACE_("MyShipScene onActiveProgress(MYSHIPSCENE_SCENE_PROG_DESTROY)");
        _pMyShip->_pEffectMyShipExplosion->activate();
        _pMyShip->_isNoControl = true;
        fadeoutSceneTree(60);
        _zanki -= 1;
    }
    if (getProgress() == MYSHIPSCENE_SCENE_PROG_DESTROY) {
        if (getActivePartFrameInProgress() == 120) {
            if (_zanki == 0) {
                throwEventToUpperTree(EVENT_ALL_MY_SHIP_WAS_DESTROYED);
                changeProgress(PROG_NOTHING);
                inactivate();
            } else {
                throwEventToUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
                changeProgress(MYSHIPSCENE_SCENE_PROG_BEGIN);
            }
        }
    }
    if (onInactiveProgress(MYSHIPSCENE_SCENE_PROG_DESTROY)) {
        _TRACE_("MyShipScene onInactiveProgress(MYSHIPSCENE_SCENE_PROG_DESTROY)");
    }
}

void MyShipScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_BEGIN) {
        _TRACE_("MyShipScene EVENT_MY_SHIP_WAS_DESTROYED_BEGIN was Catch!!");
        changeProgress(MYSHIPSCENE_SCENE_PROG_DESTROY);
    }
}

MyShipScene::~MyShipScene() {
}
