#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

RankUp100::RankUp100(const char* prm_name) : RankUpStage(prm_name) {
    _class_name = "RankUp100";

    Sleep(2);
    pWorldBoundSpace_  = NEW WorldBoundSpace001("BG_SPACE");
    pWorldBoundSpace_->inactivateTree();
    getDirector()->addSubGroup(KIND_EFFECT, pWorldBoundSpace_);

    pHoshiBoshi_ = NEW HoshiBoshi001("HoshiBoshi001");
    pHoshiBoshi_->inactivateTree();
    getDirector()->addSubGroup(KIND_EFFECT, pHoshiBoshi_);

    pMessage_ = NEW LabelGecchi16Font("RankUp100Msg");
    getDirector()->addSubGroup(KIND_EFFECT, pMessage_);
    pMessage_->inactivate();

    fadeoutScene(0); //�ŏ��͔�\��
    useProgress(10);
}

void RankUp100::initialize() {
    RankUpStage::initialize();
}

void RankUp100::processBehavior() {
    RankUpStage::processBehavior();

    switch (_pProg->get()) {
        case Stage::PROG_INIT: {
            _pProg->change(Stage::PROG_BEGIN);
            break;
        }
        case Stage::PROG_BEGIN: {
            if (_pProg->getFrameInProgress() == 180) { //�X�e�[�W�P�J�n�I
                pMessage_->activateImmed();
                pWorldBoundSpace_->activateTree();    //�w�iON
                pHoshiBoshi_->activateTree();    //�w�iON
                fadeinSceneTree(360);
                _pProg->change(Stage::PROG_PLAYING);
            }
            break;
        }
        case Stage::PROG_PLAYING: {
            if (_pProg->getFrameInProgress() == 60) { //�X�e�[�W�P�J�n�I
                pMessage_->update(PX_C(300),PX_C(300), "SCENE 01 START!");
                pMessage_->inactivateDelay(240);
            }
            //EVENT_STG01_CTRLER_WAS_END�C�x���g�҂�
            break;
        }
        case Stage::PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUp100::processBehavior()  Stage::PROG_END�ɂȂ�܂����I");
                throwEventToUpperTree(EVENT_PREPARE_NEXT_STAGE, this); //���X�e�[�W������
            }

            if (_pProg->getFrameInProgress() == 60) {
                pMessage_->activateImmed();
                pMessage_->update(PX_C(300), PX_C(300), "SCENE 01 CLEAR!!");
                pMessage_->inactivateDelay(120);
                fadeoutScene(300);
            }
            if (_pProg->getFrameInProgress() == 300) {
                throwEventToUpperTree(EVENT_STG01_WAS_END);
            }


            break;
        }
        default:
            break;

    }

}

void RankUp100::processJudgement() {
}


void RankUp100::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_CTRLER_WAS_END ) {
        _TRACE_("RankUp100::onCatchEvent() STAGEXXCONTROLLER_ENDING ���L���b�`�B�X�e�[�^�X��Stage::PROG_END��");
        _pProg->change(Stage::PROG_END);
    } else {

    }
}


RankUp100::~RankUp100() {

}
