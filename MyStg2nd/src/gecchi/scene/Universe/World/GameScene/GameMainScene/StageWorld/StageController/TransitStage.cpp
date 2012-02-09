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
    _next_main_stage = 1;
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
    _pProg->set(Stage::PROG_INIT);
}

void TransitStage::onActive() {
    _TRACE_("TransitStage::onActive()");
    reset();
}
void TransitStage::processBehavior() {
    Stage::processBehavior();

    switch (_pProg->get()) {
        case Stage::PROG_INIT: {
            _TRACE_("TransitStage::processBehavior() Prog(=Stage::PROG_INIT) is Just Changed. STAGE="<<_teansit_stage<<"→?");
            _pProg->change(Stage::PROG_BEGIN);
            break;
        }
        case Stage::PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("TransitStage::processBehavior() Prog(=Stage::PROG_BEGIN) is Just Changed. STAGE="<<_teansit_stage<<"→?");
            }

            if (_pProg->getFrameInProgress() == 180) { //通過ステージ開始
                _pProg->change(Stage::PROG_PLAYING);
            }
            break;
        }
        case Stage::PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("TransitStage::processBehavior() Prog(=Stage::PROG_PLAYING) is Just Changed. STAGE="<<_teansit_stage<<"→?");
            }

            if (_pProg->getFrameInProgress() == 120) { //次ステージ開始！
                _pMessage->update("SELECT NEXT STAGE!");
//                _pMessage->inactivateDelay(240);
            }

            processBehaviorProgPlaying();

            break;
        }

        case Stage::PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("TransitStage::processBehavior() Prog(=Stage::PROG_END) is Just Changed. STAGE="<<_teansit_stage<<"→"<<_next_main_stage);
                throwEventToUpperTree(EVENT_PREPARE_NEXT_STAGE, (void*)_next_main_stage); //次ステージ準備へ
            }

            if (_pProg->getFrameInProgress() == 120) {
                _pMessage->update("GOOD LUCK!");
            }

            if (_pProg->getFrameInProgress() == 300) {
                _TRACE_("TransitStage::processBehavior() Prog(=Stage::PROG_END) throwEventToUpperTree(EVENT_TRANSIT_WAS_END). STAGE="<<_teansit_stage<<"→"<<_next_main_stage);
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

void TransitStage::onInactive() {

}
void TransitStage::onCatchEvent(hashval prm_no, void* prm_pSource) {
    //if (prm_no == EVENT_STG01_CONTROLLER_WAS_END ) {
    //    _TRACE_("TransitStage::onCatchEvent(EVENT_STG01_CONTROLLER_WAS_END)");
    //    _pProg->change(Stage::PROG_END);
    //} else {
    //
    //}
}
void TransitStage::ready(int prm_stage) {
    _next_main_stage = -1; //次のステージは何か？

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
                _TRACE_("TransitStage::processBehaviorProgPlaying() 1 GOTO NEXT STAGE="<<_teansit_stage<<"→"<<_next_main_stage);
                 _pProg->change(Stage::PROG_END);
            }
            break;
        case 2:
            if (_pProg->getFrameInProgress() == 5*60) {

               //５秒経ったら渡島氏
                _pMessage->update("OKOKOK!! NEXT STAGE 3?");
               _next_main_stage = 3;
               _TRACE_("TransitStage::processBehaviorProgPlaying() 2 GOTO NEXT STAGE="<<_teansit_stage<<"→"<<_next_main_stage);
                _pProg->change(Stage::PROG_END);
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
