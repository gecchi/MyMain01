#include "MyShipScene.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/camera/VVCameraWorkerChanger.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/MyShipDivingCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/VamSysCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectMyShipExplosion.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/VreathMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor002.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshinBase.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT    ,
    PHASE_BEGIN   ,
    PHASE_PLAY    ,
    PHASE_DESTROY ,
    PHASE_END     ,
    PHASE_BANPEI,
};

MyShipScene::MyShipScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) ,
pMyShip_(nullptr),
papBunshinBase_(nullptr) {
    _class_name = "MyShipScene";
    pMyShip_ = NEW MyShip("MYSHIP");
    pMyShip_->inactivate(); //配下に仮登録のアクター発送者とかあるし
    bringSceneMediator()->appendGroupChild(pMyShip_);

    papBunshinBase_ = NEW MyBunshinBase*[MAX_BUNSHIN_NUM];
    for (int i = 0; i < MAX_BUNSHIN_NUM; i ++) {
        std::string name = "BunshinBase("+XTOS(i)+")";
        papBunshinBase_[i] = NEW MyBunshinBase(name.c_str(), i+1);
        papBunshinBase_[i]->inactivate();
        bringSceneMediator()->appendGroupChild(papBunshinBase_[i]);
    }
    /*
    papBunshinBase_[0]->pBunshin_->setMaterialColor(1.0, 1.0, 1.0);
    papBunshinBase_[1]->pBunshin_->setMaterialColor(0.8, 1.0, 1.0);
    papBunshinBase_[2]->pBunshin_->setMaterialColor(1.0, 0.8, 0.8);
    papBunshinBase_[3]->pBunshin_->setMaterialColor(0.8, 1.0, 0.8);

    papBunshinBase_[4]->pBunshin_->setMaterialColor(0.8, 0.8, 1.0);
    papBunshinBase_[5]->pBunshin_->setMaterialColor(0.8, 1.0, 0.8);
    papBunshinBase_[6]->pBunshin_->setMaterialColor(1.0, 0.8, 0.8);
    papBunshinBase_[7]->pBunshin_->setMaterialColor(1.0, 1.0, 0.0);
    papBunshinBase_[8]->pBunshin_->setMaterialColor(1.0, 0.0, 1.0);
    */

    pEffectMyShipExplosion_ = NEW EffectMyShipExplosion("EffectMyShipExplosion");
    pEffectMyShipExplosion_->inactivate();
    bringSceneMediator()->appendGroupChild(pEffectMyShipExplosion_);
    pVamSysCamWorker_ = nullptr;
    //z_ = 0.99;//たぶん最背面 （0 <= z_ < 1.0）Z=(0～+1)
    //z_ = 0.9999999f;

    pLabelZanki_ = NEW LabelGecchi16Font("zankdisp");
    bringSceneMediator()->appendGroupChild(pLabelZanki_);
}

void MyShipScene::initialize() {
    pLabelZanki_->setPosition(0, PX_C(20));
    pLabelZanki_->update("");
    _TRACE_("MyShipScene initialize()");
}

void MyShipScene::onReset() {
    _TRACE_("MyShipScene onReset() "<<NODE_INFO<<"");
    G_ZANKI = 3;
    std::string z(G_ZANKI, '*');
    pLabelZanki_->update(z.c_str());

    pMyShip_->resetTree();
    for (int i = 0; i < MAX_BUNSHIN_NUM; i ++) {
        papBunshinBase_[i]->resetTree();
    }

    fadeoutSceneWithBgm(0);
    getPhase()->reset(PHASE_INIT);
    pCARETAKER->getSpacetime()->getCameraWorkerChanger()->cleanCamWorker();
}

void MyShipScene::onActive() {
    _TRACE_("MyShipScene onActive()");
}

void MyShipScene::processBehavior() {
    Spacetime* pSpacetime = pCARETAKER->getSpacetime();
     ScenePhase* pPhase = getPhase();
    switch (pPhase->getPrevWhenChanged()) {
        case PHASE_BEGIN: {
            pSpacetime->getCameraWorkerChanger()->undoCameraWork(); //MyShipDivingCamWorker解除
            break;
        }
        default: {
            break;
        }
    }

    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_BEGIN);
            if (pSpacetime->getCameraWorkerChanger()->getActiveCamWorker() != pVamSysCamWorker_) {
                pVamSysCamWorker_ = (VamSysCamWorker*)(pSpacetime->getCameraWorkerChanger()->changeCameraWork("VamSysCamWorker"));
                pVamSysCamWorker_->pMyShip_ = pMyShip_;
            }
            break;
        }

        case PHASE_BEGIN: {
            if (pPhase->hasJustChanged()) {
                fadeinScene(120);
                pMyShip_->resetTree();

                //VreathMagicをデフォルトでレベル１に設定
                MagicMeter* pMM = pMyShip_->pMagicMeter_;
                int idx = pMM->lstMagic_.indexOf(pMM->pVreathMagic_);
                if (idx >= 0) {
                    pMyShip_->mp_ += pMM->pVreathMagic_->level_up_cost_[0][1]; //VreathMagicレベル１分のMP増やす。
                    pMM->pVreathMagic_->effect(1);
                    pMM->papLvTgtMvCur_[idx]->moveSmoothTo(1); //カーソル
                    pMM->papLvNowCur_[idx]->moveSmoothTo(1); //カーソル
                } else {
                    throwCriticalException("VreathMagicがありません。");
                }
                pMyShip_->_x = pSpacetime->_x_bound_left;
                pMyShip_->can_control_ = true;
                pMyShip_->is_diving_ = true;
                pMyShip_->activate();
                pSpacetime->getCameraWorkerChanger()->changeCameraWork("MyShipDivingCamWorker");
            }
            pMyShip_->_x += PX_C(30); //30000;
            if (pMyShip_->_x > 0) {
                pMyShip_->_x = 0;
                pMyShip_->is_diving_ = false;
                pPhase->change(PHASE_PLAY);
            }
            break;
        }

        case PHASE_PLAY: {
            if (pPhase->hasJustChanged()) {
            }
            //イベント EVENT_MY_SHIP_WAS_DESTROYED_BEGIN 待ち
            break;
        }

        case PHASE_DESTROY: {
            if (pPhase->hasJustChanged()) {
                pEffectMyShipExplosion_->activate(); //爆発
                pMyShip_->can_control_ = false;
                for (int i = 0; i < MAX_BUNSHIN_NUM; i ++) {
                    papBunshinBase_[i]->is_isolate_mode_ = true;
                }
                G_ZANKI -= 1;
                std::string z(G_ZANKI, '*');
                pLabelZanki_->update(z.c_str());
            }
            if (pPhase->hasArrivedFrameAt(120)) {
                fadeoutScene(120);
                pMyShip_->inactivateDelay(121);
            }
            if (pPhase->hasArrivedFrameAt(240)) {
                if (G_ZANKI == 0) {
                   throwEventUpperTree(EVENT_ALL_MY_SHIP_WAS_DESTROYED);
                   pSpacetime->getCameraWorkerChanger()->undoCameraWork(); //VamSysCamWorker解除
                   pPhase->changeNothing();
                   inactivate();
                } else {
                   throwEventUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);//←現在未使用
                   pPhase->change(PHASE_BEGIN);
                }
            }
            break;
        }
        default: {
            break;
        }
    }

}

void MyShipScene::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    ScenePhase* pPhase = getPhase();
    if (prm_event_val == EVENT_MY_SHIP_WAS_DESTROYED_BEGIN) {
        _TRACE_("MyShipScene EVENT_MY_SHIP_WAS_DESTROYED_BEGIN was Catch!!");
       pPhase->change(PHASE_DESTROY);
    }
}

MyShipScene::~MyShipScene() {
    GGAF_DELETEARR(papBunshinBase_);
}
