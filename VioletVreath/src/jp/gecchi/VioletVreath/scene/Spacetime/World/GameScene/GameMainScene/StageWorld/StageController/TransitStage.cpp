#include "TransitStage.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "../StageController.h"
#include "jp/gecchi/VioletVreath/actor/VVEnemysHeader.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundTransit.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiTransit.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

TransitStage::TransitStage(const char* prm_name) : Stage(prm_name) {
    _class_name = "TransitStage";
    _TRACE_("TransitStage::TransitStage("<<prm_name<<")");
    teansit_stage_ = 0;
    next_main_stage_ = 1;
    pWorldBound_ = NEW WorldBoundTransit("WBSTransit");
    bringSceneMediator()->appendGroupChild(pWorldBound_);

    pHoshiBoshi_ = NEW HoshiBoshiTransit("HoshiBoshiTransit");
    bringSceneMediator()->appendGroupChild(KIND_EFFECT, pHoshiBoshi_);

    pMessage_ = NEW LabelGecchi16Font("TransitStageMsg");
    pMessage_->update(300*1000, 300*1000, "");
    bringSceneMediator()->appendGroupChild(KIND_EFFECT, pMessage_);
}

void TransitStage::initialize() {
    Stage::initialize();
}

void TransitStage::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    pMessage_->update("");
    getPhase()->reset(Stage::PHASE_INIT);
}

void TransitStage::onActive() {
    _TRACE_(FUNC_NAME<<"");
    reset();
}
void TransitStage::processBehavior() {
    Stage::processBehavior();
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case Stage::PHASE_INIT: {
            _TRACE_(FUNC_NAME<<" Phase is Stage::PHASE_INIT");
            _TRACE_(FUNC_NAME<<" 直後 STAGE="<<teansit_stage_<<"→?");
            pPhase->change(Stage::PHASE_BEGIN);
            break;
        }
        case Stage::PHASE_BEGIN: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to Stage::PHASE_BEGIN)");
                _TRACE_(FUNC_NAME<<" 直後 STAGE="<<teansit_stage_<<"→?");
            }

            //始まって少し猶予

            if (pPhase->hasArrivedFrameAt(180)) { //通過ステージ開始
                pPhase->change(Stage::PHASE_PLAYING);
            }
            break;
        }
        case Stage::PHASE_PLAYING: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to Stage::PHASE_PLAYING)");
                _TRACE_(FUNC_NAME<<" 直後 STAGE="<<teansit_stage_<<"→?");
            }
            if (pPhase->hasArrivedFrameAt(120)) { //次ステージ開始！
                pMessage_->update("SELECT NEXT STAGE!");
//                pMessage_->inactivateDelay(240);
            }

            processBehaviorProgPlaying();  //次ステージ選択

            break;
        }

        case Stage::PHASE_END: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to Stage::PHASE_END)");
                _TRACE_(FUNC_NAME<<" 直後 STAGE="<<teansit_stage_<<"→"<<next_main_stage_);
                throwEventUpperTree(EVENT_PREPARE_NEXT_STAGE, (void*)(&next_main_stage_)); //次ステージ準備へ
            }

            if (pPhase->hasArrivedFrameAt(120)) {
                pMessage_->update("GOOD LUCK!");
            }

            if (pPhase->hasArrivedFrameAt(300)) {
                _TRACE_(FUNC_NAME<<" Phase(=Stage::PHASE_END) and throwEventUpperTree(EVENT_TRANSIT_WAS_END).");
                _TRACE_(FUNC_NAME<<" 直後 STAGE="<<teansit_stage_<<"→"<<next_main_stage_);
                throwEventUpperTree(EVENT_TRANSIT_WAS_END);
            }
            break;
        }

        default: {
            break;
        }

    }

}

void TransitStage::processJudgement() {
}

void TransitStage::onInactive() {

}
void TransitStage::onCatchEvent(hashval prm_no, void* prm_pSource) {
    //if (prm_no == EVENT_STAGE01_CTRLER_WAS_END ) {
    //    _TRACE_("TransitStage::onCatchEvent(EVENT_STAGE01_CTRLER_WAS_END)");
    //    pPhase->change(Stage::PHASE_END);
    //} else {
    //
    //}
}
void TransitStage::ready(int prm_stage) {
    next_main_stage_ = -1; //次のステージは何か？

    switch (prm_stage) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }
}
void TransitStage::processBehaviorProgPlaying() {
    ScenePhase* pPhase = getPhase();
    switch (teansit_stage_) {
        case 0: //DEBUGステージ
            if (pPhase->hasArrivedFrameAt(SEC_F(5))) {
                //５秒経ったら渡島氏
                pMessage_->update("DEBUG STAGE DONE!! NEXT STAGE 1????");
                next_main_stage_ = 1;
                _TRACE_(FUNC_NAME<<" GOTO NEXT STAGE="<<teansit_stage_<<"→"<<next_main_stage_);
                 pPhase->change(Stage::PHASE_END);
            }
            break;

        case 1:
             if (pPhase->hasArrivedFrameAt(SEC_F(5))) {
                //５秒経ったら渡島氏
                pMessage_->update("OKOKOK!! NEXT STAGE 2");
                next_main_stage_ = 2;
                _TRACE_(FUNC_NAME<<" GOTO NEXT STAGE="<<teansit_stage_<<"→"<<next_main_stage_);
                 pPhase->change(Stage::PHASE_END);
            }
            break;
        case 2:
            if (pPhase->hasArrivedFrameAt(SEC_F(5))) {
               //５秒経ったら渡島氏
                pMessage_->update("OKOKOK!! NEXT STAGE 3?");
               next_main_stage_ = 3;
               _TRACE_(FUNC_NAME<<" GOTO NEXT STAGE="<<teansit_stage_<<"→"<<next_main_stage_);
                pPhase->change(Stage::PHASE_END);
           }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }
}

TransitStage::~TransitStage() {


}
