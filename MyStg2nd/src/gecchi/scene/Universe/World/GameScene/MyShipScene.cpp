#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

enum {
    MYSHIPSCENE_PROG_INIT = 1,
    MYSHIPSCENE_PROG_BEGIN   ,
    MYSHIPSCENE_PROG_PLAY    ,
    MYSHIPSCENE_PROG_DESTROY ,
    MYSHIPSCENE_PROG_END
};

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
    _pMagicMeter->locate(100*1000, (CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 100.0f)*1000,
                                0.00000001f );
    getLordActor()->addSubGroup(_pMagicMeter);

    //エネルギーバー設置
    _pEnagyBar = NEW EnagyBar("EnagyBar");
    _pEnagyBar->locate(100*1000, (CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 50.0f)*1000,
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
    fadeinScene(0);
    _pProg->set(MYSHIPSCENE_PROG_INIT);
}

void MyShipScene::onActive() {
}

void MyShipScene::processBehavior() {

    switch (_pProg->getPrev_WhenJustChanged()) {
        case MYSHIPSCENE_PROG_BEGIN: {
            P_UNIVERSE->undoCameraWork(); //MyShipDivingCamWorker解除
            break;
        }
        default:
            break;
    }

    switch (_pProg->get()) {
        case MYSHIPSCENE_PROG_INIT: {
            _pProg->change(MYSHIPSCENE_PROG_BEGIN);
            if (P_UNIVERSE->_pActiveCameraWorker != _pVamSysCamWorker) {
                _pVamSysCamWorker = (VamSysCamWorker*)P_UNIVERSE->switchCameraWork("VamSysCamWorker");
                _pVamSysCamWorker->_pMyShip = _pMyShip;
            }
            break;
        }

        case MYSHIPSCENE_PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                fadeinScene(0);
                _pMyShip->reset();
                _pMyShip->_X = Universe::_X_goneLeft + 1000;
                _pMyShip->_can_control = true;
                _pMyShip->_is_diving = true;
                _pMyShip->activate();
                MyShipDivingCamWorker* pCamWorker =
                        (MyShipDivingCamWorker*)P_UNIVERSE->switchCameraWork("MyShipDivingCamWorker");
                pCamWorker->setMoveTargetCam(-1000000, 1000000, -1000000);
                pCamWorker->lockCamVp(_pMyShip);
            }
            _pMyShip->_X += 30000;
            if (_pMyShip->_X > 0) {
                _pMyShip->_X = 0;
                _pMyShip->_is_diving = false;
                //P_UNIVERSE->undoCameraWork();
                _pProg->change(MYSHIPSCENE_PROG_PLAY);
            }
            break;
        }

        case MYSHIPSCENE_PROG_PLAY: {
            if (_pProg->isJustChanged()) {
//                _pMyShip->_can_control = true;
            }
            //イベント EVENT_MY_SHIP_WAS_DESTROYED_BEGIN 待ち
            break;
        }

        case MYSHIPSCENE_PROG_DESTROY: {
            if (_pProg->isJustChanged()) {
                _pEffectMyShipExplosion->activate();
                _pMyShip->inactivateDelay(60);
                _pMyShip->_can_control = false;
                _pMyOptionController->_is_free_from_myship_mode = true;
                _zanki -= 1;
            }
            if (_pProg->getFrameInProgress() == 120) {
                if (_zanki == 0) {
                   throwEventToUpperTree(EVENT_ALL_MY_SHIP_WAS_DESTROYED);
                   P_UNIVERSE->undoCameraWork(); //VamSysCamWorker解除
                   _pProg->changeNothing();
                   inactivate();
                } else {
                   throwEventToUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
                   _pProg->change(MYSHIPSCENE_PROG_BEGIN);
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
       _pProg->change(MYSHIPSCENE_PROG_DESTROY);
    }
}

MyShipScene::~MyShipScene() {
    //P_UNIVERSE->undoCameraWork();
//    _pCon_VamSysCamWorker->close();
//    _pCon_MyShipDivingCamWorker->close();
}
