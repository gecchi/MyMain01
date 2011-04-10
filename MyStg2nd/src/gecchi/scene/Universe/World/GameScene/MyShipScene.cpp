#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

MyShipScene::MyShipScene(const char* prm_name) : DefaultScene(prm_name) ,
_pMyShip(NULL),
_pMyOptionController(NULL) {
    _class_name = "MyShipScene";
    _pMyShip = NEW MyShip("MYSHIP");
    _pMyShip->inactivateImmediately(); //配下に仮登録のアクター発送者とかあるし
    _pMyOptionController = NEW MyOptionController("MY_OPTION_PARENT");
    getLordActor()->addSubLast(_pMyOptionController);

    getLordActor()->addSubGroup(KIND_MY_BODY_NOMAL, _pMyShip);

    _pEffectMyShipExplosion = NEW EffectMyShipExplosion("EffectMyShipExplosion");
    _pEffectMyShipExplosion->inactivateImmediately();
    getLordActor()->addSubGroup(_pEffectMyShipExplosion);
    _pVamSysCamWorker = NULL;
//    _pCon_VamSysCamWorker = (CameraWorkerConnection*)P_UNIVERSE->_pCameraWorkerManager->getConnection("VamSysCamWorker");
//    _pCon_MyShipDivingCamWorker = (CameraWorkerConnection*)P_UNIVERSE->_pCameraWorkerManager->getConnection("MyShipDivingCamWorker");
//    _pMyShipDivingCamWorker = (MyShipDivingCamWorker*)_pCon_MyShipDivingCamWorker->refer();
    //_z = 0.99;//たぶん最背面 （0 <= _z < 1.0）Z=(0～+1)
    //_z = 0.9999999f;
    //魔法メーター設置
    _pMagicMeter = NEW MagicMeter("MagicMeter");
    _pMagicMeter->locate(100.0f, Properties::VIEW_SCREEN_HEIGHT - 100.0f,
                                0.00000001f );
    getLordActor()->addSubGroup(_pMagicMeter);

    //エネルギーバー設置
    _pEnagyBar = NEW EnagyBar("EnagyBar");
    _pEnagyBar->locate(100.0f, Properties::VIEW_SCREEN_HEIGHT - 50.0f,
                              0.00000001f );
    getLordActor()->addSubGroup(_pEnagyBar);
    _zanki = 3;
    useProgress(10);

}

void MyShipScene::initialize() {
    _TRACE_("MyShipScene initialize()");
}

void MyShipScene::onReset() {
    _TRACE_("MyShipScene onReset()");
    _zanki = 3;
    _pMyShip->resetTree();
    _pMyOptionController->resetTree();
    unblindScene();
    _pPrg->set(MYSHIPSCENE_SCENE_PROG_INIT);
}

void MyShipScene::onActive() {
}

void MyShipScene::processBehavior() {

    switch (_pPrg->getFromChange()) {
        case MYSHIPSCENE_SCENE_PROG_BEGIN: {
                P_UNIVERSE->undoCameraWork();
            break;
        }
        default:
            break;
    }

    switch (_pPrg->get()) {
        case MYSHIPSCENE_SCENE_PROG_INIT: {
            _pVamSysCamWorker = (VamSysCamWorker*)P_UNIVERSE->switchCameraWork("VamSysCamWorker");
            _pVamSysCamWorker->_pMyShip = _pMyShip;
            _pPrg->change(MYSHIPSCENE_SCENE_PROG_BEGIN);
            break;
        }

        case MYSHIPSCENE_SCENE_PROG_BEGIN: {
            if (_pPrg->isJustChanged()) {
                unblindScene();
                _pMyShip->reset();
                _pMyShip->activate();
                _pMyShip->_can_control = true;
                _pMyShip->_is_diving = true;
                MyShipDivingCamWorker* pCamWorker = (MyShipDivingCamWorker*)P_UNIVERSE->switchCameraWork("MyShipDivingCamWorker");
                pCamWorker->setMoveTargetCam(-1000000, 1000000, -1000000);
                pCamWorker->lockCamVp(_pMyShip);
            }
            _pMyShip->_X += 30000;
            if (_pMyShip->_X > 0) {
                _pMyShip->_X = 0;
                _pMyShip->_is_diving = false;
                _pPrg->change(MYSHIPSCENE_SCENE_PROG_PLAY);
            }
            break;
        }

        case MYSHIPSCENE_SCENE_PROG_PLAY: {
            if (_pPrg->isJustChanged()) {
                _pMyShip->_can_control = true;
            }
            //イベント EVENT_MY_SHIP_WAS_DESTROYED_BEGIN 待ち
            break;
        }

        case MYSHIPSCENE_SCENE_PROG_DESTROY: {
            if (_pPrg->isJustChanged()) {
                _pEffectMyShipExplosion->activate();
                _pMyShip->inactivateDelay(60);
                _pMyShip->_can_control = false;
                _pMyOptionController->_is_free_from_myship_mode = true;
                _zanki -= 1;
            }
            if (_pPrg->getFrameInProgress() == 120) {
                if (_zanki == 0) {
                   throwEventToUpperTree(EVENT_ALL_MY_SHIP_WAS_DESTROYED);
                   _pPrg->change(PROG_NOTHING);
                   P_UNIVERSE->undoCameraWork();
                   inactivate();
                } else {
                   throwEventToUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
                   _pPrg->change(MYSHIPSCENE_SCENE_PROG_BEGIN);
                }
            }
            break;
        }

        default:
            break;
    }

}

void MyShipScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_BEGIN) {
        _TRACE_("MyShipScene EVENT_MY_SHIP_WAS_DESTROYED_BEGIN was Catch!!");
       _pPrg->change(MYSHIPSCENE_SCENE_PROG_DESTROY);
    }
}

MyShipScene::~MyShipScene() {
    //P_UNIVERSE->undoCameraWork();
//    _pCon_VamSysCamWorker->close();
//    _pCon_MyShipDivingCamWorker->close();
}
