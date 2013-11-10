#include "stdafx.h"
#include "MyShipScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/MyShipDivingCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/VamSysCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectMyShipExplosion.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/VreathMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor002.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MyShipScene::MyShipScene(const char* prm_name) : DefaultScene(prm_name) ,
pMyShip_(nullptr),
papOptionCtrler_(nullptr) {
    _class_name = "MyShipScene";
    pMyShip_ = NEW MyShip("MYSHIP");
    pMyShip_->inactivate(); //配下に仮登録のアクター発送者とかあるし
    papOptionCtrler_ = NEW MyOptionController*[MyOptionController::max_option_num_];
    for (int i = 0; i < MyOptionController::max_option_num_; i ++) {
        std::string name = "MyOpCtrler("+XTOS(i)+")";
        papOptionCtrler_[i] = NEW MyOptionController(name.c_str(), i);
        getSceneDirector()->addSubLast(papOptionCtrler_[i]);
    }

    papOptionCtrler_[0]->pOption_->config(60000, D0ANG, 0, 1000);
    papOptionCtrler_[0]->pOption_->setMaterialColor(1.0, 1.0, 1.0);
    papOptionCtrler_[0]->pOption_->setAlpha(0.7);
    papOptionCtrler_[1]->pOption_->config(60000, D90ANG, 0, 1000);
    papOptionCtrler_[1]->pOption_->setMaterialColor(0.8, 1.0, 1.0);
    papOptionCtrler_[1]->pOption_->setAlpha(0.7);
    papOptionCtrler_[2]->pOption_->config(60000, D180ANG, 0, 1000);
    papOptionCtrler_[2]->pOption_->setMaterialColor(1.0, 0.8, 0.8);
    papOptionCtrler_[2]->pOption_->setAlpha(0.7);
    papOptionCtrler_[3]->pOption_->config(60000, D270ANG, 0, 1000);
    papOptionCtrler_[3]->pOption_->setMaterialColor(0.8, 1.0, 0.8);
    papOptionCtrler_[3]->pOption_->setAlpha(0.7);

    papOptionCtrler_[4]->pOption_->config(120000, D_ANG(72*0), 0, -1500);
    papOptionCtrler_[4]->pOption_->setMaterialColor(0.8, 0.8, 1.0);
    papOptionCtrler_[4]->pOption_->setAlpha(0.7);
    papOptionCtrler_[5]->pOption_->config(120000, D_ANG(72*1), 0, -1500);
    papOptionCtrler_[5]->pOption_->setMaterialColor(0.8, 1.0, 0.8);
    papOptionCtrler_[5]->pOption_->setAlpha(0.7);
    papOptionCtrler_[6]->pOption_->config(120000, D_ANG(72*2), 0, -1500);
    papOptionCtrler_[6]->pOption_->setMaterialColor(1.0, 0.8, 0.8);
    papOptionCtrler_[6]->pOption_->setAlpha(0.7);
    papOptionCtrler_[7]->pOption_->config(120000, D_ANG(72*3), 0, -1500);
    papOptionCtrler_[7]->pOption_->setMaterialColor(1.0, 1.0, 0.0);
    papOptionCtrler_[7]->pOption_->setAlpha(0.7);
    papOptionCtrler_[8]->pOption_->config(120000, D_ANG(72*4), 0, -1500);
    papOptionCtrler_[8]->pOption_->setMaterialColor(1.0, 0.0, 1.0);
    papOptionCtrler_[8]->pOption_->setAlpha(0.7);

    getSceneDirector()->addSubGroup(pMyShip_);

    pEffectMyShipExplosion_ = NEW EffectMyShipExplosion("EffectMyShipExplosion");
    pEffectMyShipExplosion_->inactivate();
    getSceneDirector()->addSubGroup(pEffectMyShipExplosion_);
    pVamSysCamWorker_ = nullptr;
    //z_ = 0.99;//たぶん最背面 （0 <= z_ < 1.0）Z=(0～+1)
    //z_ = 0.9999999f;

    zanki_ = 0;
    pLabelZanki_ = NEW LabelGecchi16Font("zankdisp");
    getSceneDirector()->addSubGroup(pLabelZanki_);

    useProgress(PROG_BANPEI-1);

}

void MyShipScene::initialize() {
    pLabelZanki_->position(0, PX_C(20));
    pLabelZanki_->update("");
    _TRACE_("MyShipScene initialize()");
}

void MyShipScene::onReset() {
    _TRACE_("MyShipScene onReset()");
    zanki_ = 3;
    std::string z(zanki_, '*');
    pLabelZanki_->update(z.c_str());

    pMyShip_->resetTree();
    for (int i = 0; i < MyOptionController::max_option_num_; i ++) {
        papOptionCtrler_[i]->resetTree();
    }
    fadeoutSceneWithBgm(0);
    _pProg->reset(MyShipScene::PROG_INIT);
    P_UNIVERSE->resetCamWorker();
}

void MyShipScene::onActive() {
    _TRACE_("MyShipScene onActive()");
}

void MyShipScene::processBehavior() {

    switch (_pProg->getFromProgOnChange()) {
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
            if (P_UNIVERSE->getActiveCamWorker() != pVamSysCamWorker_) {
                pVamSysCamWorker_ = (VamSysCamWorker*)(P_UNIVERSE->switchCameraWork("VamSysCamWorker"));
                pVamSysCamWorker_->pMyShip_ = pMyShip_;
            }
            break;
        }

        case MyShipScene::PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
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
                    throwGgafCriticalException("VreathMagicがありません。");
                }

                pMyShip_->_x = Universe::_x_gone_left + 1000;
                pMyShip_->can_control_ = true;
                pMyShip_->is_diving_ = true;
                pMyShip_->activate();
                MyShipDivingCamWorker* pCamWorker =
                        (MyShipDivingCamWorker*)(P_UNIVERSE->switchCameraWork("MyShipDivingCamWorker"));
            }
            pMyShip_->_x += PX_C(30); //30000;
            if (pMyShip_->_x > 0) {
                pMyShip_->_x = 0;
                pMyShip_->is_diving_ = false;
                _pProg->change(MyShipScene::PROG_PLAY);
            }
            break;
        }

        case MyShipScene::PROG_PLAY: {
            if (_pProg->isJustChanged()) {
            }
            //イベント EVENT_MY_SHIP_WAS_DESTROYED_BEGIN 待ち
            break;
        }

        case MyShipScene::PROG_DESTROY: {
            if (_pProg->isJustChanged()) {
                pEffectMyShipExplosion_->activate(); //爆発
                pMyShip_->can_control_ = false;
                for (int i = 0; i < MyOptionController::max_option_num_; i ++) {
                    papOptionCtrler_[i]->is_free_from_myship_mode_ = true;
                }
                zanki_ -= 1;
                std::string z(zanki_, '*');
                pLabelZanki_->update(z.c_str());
            }
            if (_pProg->getFrameInProgress() == 120) {
                fadeoutScene(120);
                pMyShip_->inactivateDelay(120);
            }
            if (_pProg->getFrameInProgress() == 240) {
                if (zanki_ == 0) {
                   throwEventUpperTree(EVENT_ALL_MY_SHIP_WAS_DESTROYED);
                   P_UNIVERSE->undoCameraWork(); //VamSysCamWorker解除
                   _pProg->changeNothing();
                   inactivate();
                } else {
                   throwEventUpperTree(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);//←現在未使用
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
    GGAF_DELETEARR(papOptionCtrler_);
}
