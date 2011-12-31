#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

RankUp100::RankUp100(const char* prm_name) : RankUpStage(prm_name) {
    _class_name = "RankUp100";

    Sleep(2);
    _pWorldBoundSpace  = NEW WorldBoundSpace001("BG_SPACE");
    _pWorldBoundSpace->inactivateTree();
    getDirector()->addSubGroup(KIND_EFFECT, _pWorldBoundSpace);

    _pHoshiBoshi = NEW HoshiBoshi001("HoshiBoshi001");
    _pHoshiBoshi->inactivateTree();
    getDirector()->addSubGroup(KIND_EFFECT, _pHoshiBoshi);

    _pMessage = NEW LabelGecchi16Font("RankUp100Msg");
    getDirector()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

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
                _pMessage->activateImmed();
                _pWorldBoundSpace->activateTree();    //�w�iON
                _pHoshiBoshi->activateTree();    //�w�iON
                fadeinSceneTree(360);
                _pProg->change(Stage::PROG_PLAYING);
            }
            break;
        }
        case Stage::PROG_PLAYING: {
            if (_pProg->getFrameInProgress() == 60) { //�X�e�[�W�P�J�n�I
                _pMessage->update(PX2CO(300),PX2CO(300), "SCENE 01 START!");
                _pMessage->inactivateDelay(240);
            }
            //EVENT_STG01_CONTROLLER_WAS_END�C�x���g�҂�
            break;
        }
        case Stage::PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUp100::processBehavior()  Stage::PROG_END�ɂȂ�܂����I");
                throwEventToUpperTree(EVENT_PREPARE_NEXT_STAGE, this); //���X�e�[�W������
            }

            if (_pProg->getFrameInProgress() == 60) {
                _pMessage->activateImmed();
                _pMessage->update(PX2CO(300), PX2CO(300), "SCENE 01 CLEAR!!");
                _pMessage->inactivateDelay(120);
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
    if (prm_no == EVENT_STG01_CONTROLLER_WAS_END ) {
        _TRACE_("RankUp100::onCatchEvent() STAGEXXCONTROLLER_ENDING ���L���b�`�B�X�e�[�^�X��Stage::PROG_END��");
        _pProg->change(Stage::PROG_END);
    } else {

    }
}


RankUp100::~RankUp100() {

}
