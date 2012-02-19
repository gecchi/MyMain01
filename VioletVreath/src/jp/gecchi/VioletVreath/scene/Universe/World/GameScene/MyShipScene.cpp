#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MyShipScene::MyShipScene(const char* prm_name) : DefaultScene(prm_name) ,
_pMyShip(NULL),
_pMyOptionController(NULL) {
    _class_name = "MyShipScene";
    _pMyShip = NEW MyShip("MYSHIP");
    _pMyShip->inactivateImmed(); //�z���ɉ��o�^�̃A�N�^�[�����҂Ƃ����邵
    _pMyOptionController = NEW MyOptionController("MY_OPTION_PARENT");
    getDirector()->addSubLast(_pMyOptionController);

    getDirector()->addSubGroup(KIND_MY_BODY_NOMAL, _pMyShip);

    _pEffectMyShipExplosion = NEW EffectMyShipExplosion("EffectMyShipExplosion");
    _pEffectMyShipExplosion->inactivateImmed();
    getDirector()->addSubGroup(_pEffectMyShipExplosion);
    _pVamSysCamWorker = NULL;
//    _pCon_VamSysCamWorker = connectCameraWorkerManager("VamSysCamWorker");
//    _pCon_MyShipDivingCamWorker = connectCameraWorkerManager("MyShipDivingCamWorker");
//    _pMyShipDivingCamWorker = (MyShipDivingCamWorker*)_pCon_MyShipDivingCamWorker->use();
    //_z = 0.99;//���Ԃ�Ŕw�� �i0 <= _z < 1.0�jZ=(0�`+1)
    //_z = 0.9999999f;
    //���@���[�^�[�ݒu
    _pMagicMeter = NEW MagicMeter("MagicMeter");
    _pMagicMeter->locate(PX2CO(100), PX2CO(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 100.0f), 0.00000001f );
    getDirector()->addSubGroup(_pMagicMeter);

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
    _pProg->set(MyShipScene::PROG_INIT);
}

void MyShipScene::onActive() {
}

void MyShipScene::processBehavior() {

    switch (_pProg->getPrev_WhenJustChanged()) {
        case MyShipScene::PROG_BEGIN: {
            P_UNIVERSE->undoCameraWork(); //MyShipDivingCamWorker����
            break;
        }
        default:
            break;
    }

    switch (_pProg->get()) {
        case MyShipScene::PROG_INIT: {
            _pProg->change(MyShipScene::PROG_BEGIN);
            if (P_UNIVERSE->_pActiveCameraWorker != _pVamSysCamWorker) {
                _pVamSysCamWorker = (VamSysCamWorker*)P_UNIVERSE->switchCameraWork("VamSysCamWorker");
                _pVamSysCamWorker->_pMyShip = _pMyShip;
            }
            break;
        }

        case MyShipScene::PROG_BEGIN: {
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
                _pProg->change(MyShipScene::PROG_PLAY);
            }
            break;
        }

        case MyShipScene::PROG_PLAY: {
            if (_pProg->isJustChanged()) {
//                _pMyShip->_can_control = true;
            }
            //�C�x���g EVENT_MY_SHIP_WAS_DESTROYED_BEGIN �҂�
            break;
        }

        case MyShipScene::PROG_DESTROY: {
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
                   P_UNIVERSE->undoCameraWork(); //VamSysCamWorker����
                   _pProg->changeNothing();
                   inactivate();
                } else {
                   throwEventToUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
                   _pProg->change(MyShipScene::PROG_BEGIN);
                }
            }
            break;
        }

        default:
            break;
    }

}

void MyShipScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_MY_SHIP_WAS_DESTROYED_BEGIN) {
        _TRACE_("MyShipScene EVENT_MY_SHIP_WAS_DESTROYED_BEGIN was Catch!!");
       _pProg->change(MyShipScene::PROG_DESTROY);
    }
}

MyShipScene::~MyShipScene() {
    //P_UNIVERSE->undoCameraWork();
//    _pCon_VamSysCamWorker->close();
//    _pCon_MyShipDivingCamWorker->close();
}
