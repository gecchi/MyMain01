#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MyShipScene::MyShipScene(const char* prm_name) : DefaultScene(prm_name) ,
pMyShip_(NULL),
papMyOptionController_(NULL) {
    _class_name = "MyShipScene";
    pMyShip_ = NEW MyShip("MYSHIP");
    pMyShip_->inactivateImmed(); //配下に仮登録のアクター発送者とかあるし
    papMyOptionController_ = NEW MyOptionController*[MyOptionController::max_option_num_];
    for (int i = 0; i < MyOptionController::max_option_num_; i ++) {
        papMyOptionController_[i] = NEW MyOptionController("MyOpCtrl", i);
        getDirector()->addSubLast(papMyOptionController_[i]);
    }

    papMyOptionController_[0]->pMyOption_->config(60000, D0ANG, 0, 1000);
    papMyOptionController_[0]->pMyOption_->setMaterialColor(1.0, 1.0, 1.0);
    papMyOptionController_[0]->pMyOption_->setAlpha(0.7);
    papMyOptionController_[1]->pMyOption_->config(60000, D90ANG, 0, 1000);
    papMyOptionController_[1]->pMyOption_->setMaterialColor(0.8, 1.0, 1.0);
    papMyOptionController_[1]->pMyOption_->setAlpha(0.7);
    papMyOptionController_[2]->pMyOption_->config(60000, D180ANG, 0, 1000);
    papMyOptionController_[2]->pMyOption_->setMaterialColor(1.0, 0.8, 0.8);
    papMyOptionController_[2]->pMyOption_->setAlpha(0.7);
    papMyOptionController_[3]->pMyOption_->config(60000, D270ANG, 0, 1000);
    papMyOptionController_[3]->pMyOption_->setMaterialColor(0.8, 1.0, 0.8);
    papMyOptionController_[3]->pMyOption_->setAlpha(0.7);
    papMyOptionController_[4]->pMyOption_->config(120000, D0ANG, 0, -1500);
    papMyOptionController_[4]->pMyOption_->setMaterialColor(0.8, 0.8, 1.0);
    papMyOptionController_[4]->pMyOption_->setAlpha(0.7);
    papMyOptionController_[5]->pMyOption_->config(120000, D90ANG, 0, -1500);
    papMyOptionController_[5]->pMyOption_->setMaterialColor(0.8, 1.0, 0.8);
    papMyOptionController_[5]->pMyOption_->setAlpha(0.7);
    papMyOptionController_[6]->pMyOption_->config(120000, D180ANG, 0, -1500);
    papMyOptionController_[6]->pMyOption_->setMaterialColor(1.0, 0.8, 0);
    papMyOptionController_[6]->pMyOption_->setAlpha(0.7);
    papMyOptionController_[7]->pMyOption_->config(120000, D270ANG, 0, -1500);
    papMyOptionController_[7]->pMyOption_->setMaterialColor(1.0, 1.0, 1.0);
    papMyOptionController_[7]->pMyOption_->setAlpha(0.7);




    getDirector()->addSubGroup(KIND_MY_BODY_NOMAL, pMyShip_);

    pEffectMyShipExplosion_ = NEW EffectMyShipExplosion("EffectMyShipExplosion");
    pEffectMyShipExplosion_->inactivateImmed();
    getDirector()->addSubGroup(pEffectMyShipExplosion_);
    pVamSysCamWorker_ = NULL;
//    pCon_VamSysCamWorker_ = connectCameraWorkerManager("VamSysCamWorker");
//    pCon_MyShipDivingCamWorker_ = connectCameraWorkerManager("MyShipDivingCamWorker");
//    pMyShip_DivingCamWorker = (MyShipDivingCamWorker*)pCon_MyShipDivingCamWorker_->use();
    //z_ = 0.99;//たぶん最背面 （0 <= z_ < 1.0）Z=(0～+1)
    //z_ = 0.9999999f;
    //魔法メーター設置
    pMagicMeter_ = NEW MagicMeter("MagicMeter");
    pMagicMeter_->locate(PX2CO(100), PX2CO(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 100.0f), 0.00000001f );
    getDirector()->addSubGroup(pMagicMeter_);

    zanki_ = 3;
    useProgress(10);

}

void MyShipScene::initialize() {
    _TRACE_("MyShipScene initialize()");
}

void MyShipScene::onReset() {
    _TRACE_("MyShipScene onReset()");
    zanki_ = 3;
    pMyShip_->resetTree();
    for (int i = 0; i < MyOptionController::max_option_num_; i ++) {
        papMyOptionController_[i]->resetTree();
    }
    fadeinScene(0);
    _pProg->set(MyShipScene::PROG_INIT);
}

void MyShipScene::onActive() {
}

void MyShipScene::processBehavior() {

    switch (_pProg->getPrev_WhenJustChanged()) {
        case MyShipScene::PROG_BEGIN: {
            P_UNIVERSE->undoCameraWork(); //MyShipDivingCamWorker解除
            break;
        }
        default:
            break;
    }

    switch (_pProg->get()) {
        case MyShipScene::PROG_INIT: {
            _pProg->change(MyShipScene::PROG_BEGIN);
            if (P_UNIVERSE->pActiveCameraWorker_ != pVamSysCamWorker_) {
                pVamSysCamWorker_ = (VamSysCamWorker*)P_UNIVERSE->switchCameraWork("VamSysCamWorker");
                pVamSysCamWorker_->pMyShip_ = pMyShip_;
            }
            break;
        }

        case MyShipScene::PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                fadeinScene(0);
                pMyShip_->reset();
                pMyShip_->_X = Universe::_X_goneLeft + 1000;
                pMyShip_->can_control_ = true;
                pMyShip_->is_diving_ = true;
                pMyShip_->activate();
                MyShipDivingCamWorker* pCamWorker =
                        (MyShipDivingCamWorker*)P_UNIVERSE->switchCameraWork("MyShipDivingCamWorker");
                pCamWorker->setMoveTargetCam(-1000000, 1000000, -1000000);
                pCamWorker->lockCamVp(pMyShip_);
            }
            pMyShip_->_X += 30000;
            if (pMyShip_->_X > 0) {
                pMyShip_->_X = 0;
                pMyShip_->is_diving_ = false;
                //P_UNIVERSE->undoCameraWork();
                _pProg->change(MyShipScene::PROG_PLAY);
            }
            break;
        }

        case MyShipScene::PROG_PLAY: {
            if (_pProg->isJustChanged()) {
//                pMyShip_->can_control_ = true;
            }
            //イベント EVENT_MY_SHIP_WAS_DESTROYED_BEGIN 待ち
            break;
        }

        case MyShipScene::PROG_DESTROY: {
            if (_pProg->isJustChanged()) {
                pEffectMyShipExplosion_->activate();
                pMyShip_->inactivateDelay(60);
                pMyShip_->can_control_ = false;
                for (int i = 0; i < MyOptionController::max_option_num_; i ++) {
                    papMyOptionController_[i]->is_free_from_myship_mode_ = true;
                }
                zanki_ -= 1;
            }
            if (_pProg->getFrameInProgress() == 120) {
                if (zanki_ == 0) {
                   throwEventToUpperTree(EVENT_ALL_MY_SHIP_WAS_DESTROYED);
                   P_UNIVERSE->undoCameraWork(); //VamSysCamWorker解除
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
    DELETEARR_IMPOSSIBLE_NULL(papMyOptionController_);

    //P_UNIVERSE->undoCameraWork();
//    pCon_VamSysCamWorker_->close();
//    pCon_MyShipDivingCamWorker_->close();
}
