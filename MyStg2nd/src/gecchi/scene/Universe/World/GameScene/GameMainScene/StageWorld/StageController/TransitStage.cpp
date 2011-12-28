#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

TransitStage::TransitStage(const char* prm_name) : Stage(prm_name) {
    _class_name = "TransitStage";
    _TRACE_("TransitStage::TransitStage("<<prm_name<<")");
    _teansit_stage = 0;
    _next_main_stage = 0;
    _pWorldBoundSpace = NEW WorldBoundSpaceTransit("WBSTransit");
    getDirector()->addSubGroup(_pWorldBoundSpace);

    _pHoshiBoshi = NEW HoshiBoshiTransit("HoshiBoshiTransit");
    getDirector()->addSubGroup(KIND_EFFECT, _pHoshiBoshi);

    _pMessage = NEW LabelGecchi16Font("TransitStageMsg");
    _pMessage->update(300*1000, 300*1000, "");
    getDirector()->addSubGroup(KIND_EFFECT, _pMessage);
    useProgress(10);
}

void TransitStage::initialize() {
    Stage::initialize();
}

void TransitStage::onReset() {
    _TRACE_("TransitStage::onReset()");
    _pMessage->update("");
}

void TransitStage::onActive() {
    _TRACE_("TransitStage::onActive()");
    reset();
}
void TransitStage::processBehavior() {
    Stage::processBehavior();

    switch (_pProg->get()) {
        case STAGE_PROG_INIT: {
            _TRACE_("TransitStage::processBehavior() Prog(=STAGE_PROG_INIT) is Just Changed");
            _pProg->change(STAGE_PROG_BEGIN);
            break;
        }
        case STAGE_PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("TransitStage::processBehavior() Prog(=STAGE_PROG_BEGIN) is Just Changed");
            }

            if (_pProg->getFrameInProgress() == 180) { //ステージ１開始！
                _pProg->change(STAGE_PROG_PLAYING);
            }
            break;
        }
        case STAGE_PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("TransitStage::processBehavior() Prog(=STAGE_PROG_PLAYING) is Just Changed");
            }

            if (_pProg->getFrameInProgress() == 60) { //ステージ開始！
                _pMessage->update("SELECT NEXT STAGE!");
//                _pMessage->inactivateDelay(240);
            }

            processBehaviorProgPlaying();

            break;
        }

        case STAGE_PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("TransitStage::processBehavior() Prog(=STAGE_PROG_END) is Just Changed");
                throwEventToUpperTree(EVENT_PREPARE_NEXT_STAGE, (void*)_next_main_stage); //次ステージ準備へ
            }

            if (_pProg->getFrameInProgress() == 120) {
                _pMessage->update("GOOD LUCK!");
            }

            if (_pProg->getFrameInProgress() == 300) {
                _TRACE_("TransitStage::processBehavior() Prog(=STAGE_PROG_END) throwEventToUpperTree(EVENT_TRANSIT_WAS_END)");
                throwEventToUpperTree(EVENT_TRANSIT_WAS_END);
            }

            break;
        }
        default:
            break;

    }

}

void TransitStage::processJudgement() {
}

void TransitStage::processFinal() {

}
void TransitStage::onInactive() {

}
void TransitStage::onCatchEvent(hashval prm_no, void* prm_pSource) {
    //if (prm_no == EVENT_STG01_CONTROLLER_WAS_END ) {
    //    _TRACE_("TransitStage::onCatchEvent(EVENT_STG01_CONTROLLER_WAS_END)");
    //    _pProg->change(STAGE_PROG_END);
    //} else {
    //
    //}
}
void TransitStage::ready(int prm_stage) {
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
    switch (_teansit_stage) {
        case 1:
             if (_pProg->getFrameInProgress() == 5*60) {

                //５秒経ったら渡島氏
                _pMessage->update("OKOKOK!! NEXT STAGE 2");
                _next_main_stage = 2;
                _TRACE_("TransitStage::processBehaviorProgPlaying() GOTO NEXT STAGE="<<_next_main_stage);
                 _pProg->change(STAGE_PROG_END);
            }
            break;
        case 2:
            if (_pProg->getFrameInProgress() == 5*60) {

               //５秒経ったら渡島氏
                _pMessage->update("OKOKOK!! NEXT STAGE 3?");
               _next_main_stage = 3;
               _TRACE_("TransitStage::processBehaviorProgPlaying() GOTO NEXT STAGE="<<_next_main_stage);
                _pProg->change(STAGE_PROG_END);
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
