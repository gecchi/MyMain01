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
}

void MyShipScene::initialize() {
    _TRACE_("MyShipScene initialize()");
}

void MyShipScene::onActive() {
    _TRACE_("MyShipScene onActive()");
    setProgress(MYSHIPSCENE_PROG_BEGIN);
}

void MyShipScene::processBehavior() {

//    _TRACE_("_progress="<<_progress<<" _progress_prev="<<_progress_prev);
//    if (_progress != _progress_prev) {
//        if (MYSHIPSCENE_PROG_BEGIN == _progress) {
//            _TRACE_("YES");
//        }
//    }

    if (onInactiveProgressAt(MYSHIPSCENE_PROG_BEGIN)) {
        _TRACE_("MyShipScene onInactiveProgressAt(MYSHIPSCENE_PROG_BEGIN)");
    } else if (onInactiveProgressAt(MYSHIPSCENE_PROG_APPEARANCE_NOMAL)) {
        _TRACE_("MyShipScene onInactiveProgressAt(MYSHIPSCENE_PROG_APPEARANCE_NOMAL)");
        P_UNIVERSE->popCameraWork();
    } else if (onInactiveProgressAt(MYSHIPSCENE_PROG_PLAY)) {
        _TRACE_("MyShipScene onInactiveProgressAt(MYSHIPSCENE_PROG_PLAY)");
        P_UNIVERSE->popCameraWork();
    } else if (onInactiveProgressAt(MYSHIPSCENE_PROG_DESTROY)) {
        _TRACE_("MyShipScene onInactiveProgressAt(MYSHIPSCENE_PROG_DESTROY)");
    }

    if (onActiveProgressAt(MYSHIPSCENE_PROG_BEGIN)) {
        _TRACE_("MyShipScene onActiveProgressAt(MYSHIPSCENE_PROG_BEGIN)");
        fadeinSceneTree(60);
        _pMyShip->_X = Universe::_X_goneLeft;
        _pMyShip->_isNoControl = true;
    } else if (getProgress() == MYSHIPSCENE_PROG_BEGIN) {
        setProgress(MYSHIPSCENE_PROG_APPEARANCE_NOMAL);
    }


    if (onActiveProgressAt(MYSHIPSCENE_PROG_APPEARANCE_NOMAL)) {
        _TRACE_("MyShipScene onActiveProgressAt(MYSHIPSCENE_PROG_APPEARANCE_NOMAL)");
        P_UNIVERSE->pushCameraWork("MyShipDivingCamWorker");
        _pMyShipDivingCamWorker->setMoveTargetCam(-1000000, 1000000, 1000000);
        _pMyShipDivingCamWorker->setMoveTargetCamVpBy(_pMyShip);
    } else if (getProgress() == MYSHIPSCENE_PROG_APPEARANCE_NOMAL) {
        _pMyShip->_X += 10000;

        if (_pMyShip->_X > 0) {
            setProgress(MYSHIPSCENE_PROG_PLAY);
        }
    } 


    if (onActiveProgressAt(MYSHIPSCENE_PROG_PLAY)) {
        _TRACE_("MyShipScene onActiveProgressAt(MYSHIPSCENE_PROG_PLAY)");
        P_UNIVERSE->pushCameraWork("VamSysCamWorker");
        _pMyShip->_isNoControl = false;
    } else if (getProgress() == MYSHIPSCENE_PROG_PLAY) {

    } 

    if (onActiveProgressAt(MYSHIPSCENE_PROG_DESTROY)) {
        _TRACE_("MyShipScene onActiveProgressAt(MYSHIPSCENE_PROG_DESTROY)");
        _pMyShip->_pEffectMyShipExplosion->activate();
        _pMyShip->_isNoControl = true;
        fadeoutSceneTree(180);
    } else if (getProgress() == MYSHIPSCENE_PROG_DESTROY) {
        if (getActivePartFrameInProgress() == 240) {
            throwEventToUpperTree(MY_SHIP_WAS_DESTROYED_FINISH);
            setProgress(MYSHIPSCENE_PROG_BEGIN);
        }
    } 
}

void MyShipScene::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == MY_SHIP_WAS_DESTROYED_BEGIN) {
        _TRACE_("MyShipScene MY_SHIP_WAS_DESTROYED_BEGIN was Catch!!");

        setProgress(MYSHIPSCENE_PROG_DESTROY);
    } else if (prm_no == MY_SHIP_WAS_DESTROYED_FINISH) {
        _TRACE_("MyShipScene MY_SHIP_WAS_DESTROYED_FINISH was Catch!!");
        //setProgress()
    }
}

MyShipScene::~MyShipScene() {
}
