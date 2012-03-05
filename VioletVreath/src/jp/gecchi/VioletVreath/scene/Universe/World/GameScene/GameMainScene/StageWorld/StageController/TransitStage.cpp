#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

TransitStage::TransitStage(const char* prm_name) : Stage(prm_name) {
    _class_name = "TransitStage";
    _TRACE_("TransitStage::TransitStage("<<prm_name<<")");
    teansit_stage_ = 0;
    next_main_stage_ = 1;
    pWorldBoundSpace_ = NEW WorldBoundSpaceTransit("WBSTransit");
    getDirector()->addSubGroup(pWorldBoundSpace_);

    pHoshiBoshi_ = NEW HoshiBoshiTransit("HoshiBoshiTransit");
    getDirector()->addSubGroup(KIND_EFFECT, pHoshiBoshi_);

    pMessage_ = NEW LabelGecchi16Font("TransitStageMsg");
    pMessage_->update(300*1000, 300*1000, "");
    getDirector()->addSubGroup(KIND_EFFECT, pMessage_);
    useProgress(10);
}

void TransitStage::initialize() {
    Stage::initialize();
}

void TransitStage::onReset() {
    _TRACE_("TransitStage::onReset()");
    pMessage_->update("");
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
            _TRACE_("TransitStage::processBehavior() Prog(=Stage::PROG_INIT) is Just Changed. STAGE="<<teansit_stage_<<"��?");
            _pProg->change(Stage::PROG_BEGIN);
            break;
        }
        case Stage::PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("TransitStage::processBehavior() Prog(=Stage::PROG_BEGIN) is Just Changed. STAGE="<<teansit_stage_<<"��?");
            }

            if (_pProg->getFrameInProgress() == 180) { //�ʉ߃X�e�[�W�J�n
                _pProg->change(Stage::PROG_PLAYING);
            }
            break;
        }
        case Stage::PROG_PLAYING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("TransitStage::processBehavior() Prog(=Stage::PROG_PLAYING) is Just Changed. STAGE="<<teansit_stage_<<"��?");
            }

            if (_pProg->getFrameInProgress() == 120) { //���X�e�[�W�J�n�I
                pMessage_->update("SELECT NEXT STAGE!");
//                pMessage_->inactivateDelay(240);
            }

            processBehaviorProgPlaying();

            break;
        }

        case Stage::PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("TransitStage::processBehavior() Prog(=Stage::PROG_END) is Just Changed. STAGE="<<teansit_stage_<<"��"<<next_main_stage_);
                throwEventToUpperTree(EVENT_PREPARE_NEXT_STAGE, (void*)next_main_stage_); //���X�e�[�W������
            }

            if (_pProg->getFrameInProgress() == 120) {
                pMessage_->update("GOOD LUCK!");
            }

            if (_pProg->getFrameInProgress() == 300) {
                _TRACE_("TransitStage::processBehavior() Prog(=Stage::PROG_END) throwEventToUpperTree(EVENT_TRANSIT_WAS_END). STAGE="<<teansit_stage_<<"��"<<next_main_stage_);
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
    switch (teansit_stage_) {
        case 1:
             if (_pProg->getFrameInProgress() == 5*60) {

                //�T�b�o������n����
                pMessage_->update("OKOKOK!! NEXT STAGE 2");
                next_main_stage_ = 2;
                _TRACE_("TransitStage::processBehaviorProgPlaying() 1 GOTO NEXT STAGE="<<teansit_stage_<<"��"<<next_main_stage_);
                 _pProg->change(Stage::PROG_END);
            }
            break;
        case 2:
            if (_pProg->getFrameInProgress() == 5*60) {

               //�T�b�o������n����
                pMessage_->update("OKOKOK!! NEXT STAGE 3?");
               next_main_stage_ = 3;
               _TRACE_("TransitStage::processBehaviorProgPlaying() 2 GOTO NEXT STAGE="<<teansit_stage_<<"��"<<next_main_stage_);
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
