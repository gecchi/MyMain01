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
    useProgress(10);
}

void MyShipScene::initialize() {
    _TRACE_("MyShipScene initialize()");
    reset();
}

void MyShipScene::reset() {
    _TRACE_("MyShipScene reset()");
    _zanki = 2;
    unblindScene();
    _pProgress->change(MYSHIPSCENE_SCENE_PROG_INIT);
}
void MyShipScene::onActive() {
}

void MyShipScene::processBehavior() {

    switch (_pProgress->getChangedFrom()) {
        case MYSHIPSCENE_SCENE_PROG_BEGIN:
            P_UNIVERSE->popCameraWork();
            break;
        case MYSHIPSCENE_SCENE_PROG_PLAY:
            P_UNIVERSE->popCameraWork();
            break;
        default:
            break;
    }

    switch (_pProgress->get()) {
        case MYSHIPSCENE_SCENE_PROG_INIT:
            _pProgress->change(MYSHIPSCENE_SCENE_PROG_BEGIN);
            break;

        case MYSHIPSCENE_SCENE_PROG_BEGIN:
            if (_pProgress->isJustChanged()) {
                unblindScene();
                _pMyShip->reset();
                _pMyShip->activate();
                _pMyShip->_X = Universe::_X_goneLeft;
                _pMyShip->_isNoControl = true;
                P_UNIVERSE->pushCameraWork("MyShipDivingCamWorker");
                _pMyShipDivingCamWorker->setMoveTargetCam(-1000000, 1000000, 1000000);
                _pMyShipDivingCamWorker->setMoveTargetCamVpBy(_pMyShip);
            }
            _pMyShip->_X += 30000;
            _pMyShipDivingCamWorker->setMoveTargetCamVpBy(_pMyShip);
            if (_pMyShip->_X > 0) {
                _pMyShip->_X = 0;
                _pProgress->change(MYSHIPSCENE_SCENE_PROG_PLAY);
            }
            break;

        case MYSHIPSCENE_SCENE_PROG_PLAY:
            if (_pProgress->isJustChanged()) {
                P_UNIVERSE->pushCameraWork("VamSysCamWorker");
                _pMyShip->_isNoControl = false;
            }
            //イベント EVENT_MY_SHIP_WAS_DESTROYED_BEGIN 待ち
            break;

        case MYSHIPSCENE_SCENE_PROG_DESTROY:
            if (_pProgress->isJustChanged()) {
                _pMyShip->_pEffectMyShipExplosion->activate();
                _pMyShip->_isNoControl = true;
                fadeoutSceneTree(60);
                _zanki -= 1;
            }
            if (_pProgress->getActivePartFrameInProgress() == 120) {
                if (_zanki == 0) {
                   throwEventToUpperTree(EVENT_ALL_MY_SHIP_WAS_DESTROYED);
                   _pProgress->change(PROG_NOTHING);
                   inactivate();
                } else {
                   throwEventToUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
                   _pProgress->change(MYSHIPSCENE_SCENE_PROG_BEGIN);
                }
            }
            break;

        default:
            break;
    }

}

void MyShipScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_BEGIN) {
        _TRACE_("MyShipScene EVENT_MY_SHIP_WAS_DESTROYED_BEGIN was Catch!!");
       _pProgress->change(MYSHIPSCENE_SCENE_PROG_DESTROY);
    }
}

MyShipScene::~MyShipScene() {
}
