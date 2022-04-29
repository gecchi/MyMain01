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
    switch (pPhase->get()) {
        case Stage::PHASE_INIT: {
            _TRACE_(FUNC_NAME<<" Prog is Stage::PHASE_INIT");
            _TRACE_(FUNC_NAME<<" ���� STAGE="<<teansit_stage_<<"��?");
            pPhase->change(Stage::PHASE_BEGIN);
            break;
        }
        case Stage::PHASE_BEGIN: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to Stage::PHASE_BEGIN)");
                _TRACE_(FUNC_NAME<<" ���� STAGE="<<teansit_stage_<<"��?");
            }

            //�n�܂��ď����P�\

            if (pPhase->hasArrivedFrameAt(180)) { //�ʉ߃X�e�[�W�J�n
                pPhase->change(Stage::PHASE_PLAYING);
            }
            break;
        }
        case Stage::PHASE_PLAYING: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to Stage::PHASE_PLAYING)");
                _TRACE_(FUNC_NAME<<" ���� STAGE="<<teansit_stage_<<"��?");
            }
            if (pPhase->hasArrivedFrameAt(120)) { //���X�e�[�W�J�n�I
                pMessage_->update("SELECT NEXT STAGE!");
//                pMessage_->inactivateDelay(240);
            }

            processBehaviorProgPlaying();  //���X�e�[�W�I��

            break;
        }

        case Stage::PHASE_END: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to Stage::PHASE_END)");
                _TRACE_(FUNC_NAME<<" ���� STAGE="<<teansit_stage_<<"��"<<next_main_stage_);
                throwEventUpperTree(EVENT_PREPARE_NEXT_STAGE, (void*)(&next_main_stage_)); //���X�e�[�W������
            }

            if (pPhase->hasArrivedFrameAt(120)) {
                pMessage_->update("GOOD LUCK!");
            }

            if (pPhase->hasArrivedFrameAt(300)) {
                _TRACE_(FUNC_NAME<<" Prog(=Stage::PHASE_END) and throwEventUpperTree(EVENT_TRANSIT_WAS_END).");
                _TRACE_(FUNC_NAME<<" ���� STAGE="<<teansit_stage_<<"��"<<next_main_stage_);
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
    next_main_stage_ = -1; //���̃X�e�[�W�͉����H

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
        case 0: //DEBUG�X�e�[�W
            if (pPhase->hasArrivedFrameAt(5*60)) {
                //�T�b�o������n����
                pMessage_->update("DEBUG STAGE DONE!! NEXT STAGE 1????");
                next_main_stage_ = 1;
                _TRACE_(FUNC_NAME<<" GOTO NEXT STAGE="<<teansit_stage_<<"��"<<next_main_stage_);
                 pPhase->change(Stage::PHASE_END);
            }
            break;

        case 1:
             if (pPhase->hasArrivedFrameAt(5*60)) {
                //�T�b�o������n����
                pMessage_->update("OKOKOK!! NEXT STAGE 2");
                next_main_stage_ = 2;
                _TRACE_(FUNC_NAME<<" GOTO NEXT STAGE="<<teansit_stage_<<"��"<<next_main_stage_);
                 pPhase->change(Stage::PHASE_END);
            }
            break;
        case 2:
            if (pPhase->hasArrivedFrameAt(5*60)) {
               //�T�b�o������n����
                pMessage_->update("OKOKOK!! NEXT STAGE 3?");
               next_main_stage_ = 3;
               _TRACE_(FUNC_NAME<<" GOTO NEXT STAGE="<<teansit_stage_<<"��"<<next_main_stage_);
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
