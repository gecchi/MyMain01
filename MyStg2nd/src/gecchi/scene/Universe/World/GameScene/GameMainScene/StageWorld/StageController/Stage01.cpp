#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Stage01::Stage01(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage01";

    _pScene_Stage01PartController = NEW Stage01PartController("Stage01Ctrl");
    _pScene_Stage01PartController->inactivate();
    addSubLast(_pScene_Stage01PartController);
    Sleep(2);
    _pWorldBoundSpace  = NEW WorldBoundSpace001("BG_SPACE");
    getDirector()->addSubGroup(KIND_EFFECT, _pWorldBoundSpace);

    _pHoshiBoshi = NEW HoshiBoshi001("HoshiBoshi001");
    getDirector()->addSubGroup(KIND_EFFECT, _pHoshiBoshi);

    _pMessage = NEW LabelGecchi16Font("Stage01Msg");
    getDirector()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

    fadeoutScene(0); //�ŏ��͔�\��
    useProgress(10);
}

void Stage01::initialize() {
    Stage::initialize();
}

void Stage01::processBehavior() {
    Stage::processBehavior();

    switch (_pProg->get()) {
        case STAGE_PROG_INIT: {
            _pProg->change(STAGE_PROG_BEGIN);
            break;
        }
        case STAGE_PROG_BEGIN: {
            if (_pProg->getFrameInProgress() == 180) { //�X�e�[�W�P�J�n�I
                _pMessage->activateImmediately();
                _pWorldBoundSpace->activateTree();    //�w�iON
                _pHoshiBoshi->activateTree();    //�w�iON
                _pScene_Stage01PartController->activate();
                fadeinSceneTree(360);
                _pProg->change(STAGE_PROG_PLAYING);
            }
            break;
        }
        case STAGE_PROG_PLAYING: {
            if (_pProg->getFrameInProgress() == 60) { //�X�e�[�W�P�J�n�I
                _pMessage->update(PX2CO(300), PX2CO(300), "SCENE 01 START!");
                _pMessage->inactivateDelay(240);
            }
            //EVENT_STG01_CONTROLLER_WAS_END�C�x���g�҂�
            break;
        }
        case STAGE_PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("Stage01::processBehavior()  STAGE_PROG_END�ɂȂ�܂����I");
                throwEventToUpperTree(EVENT_PREPARE_TRANSIT_STAGE, this); //�ʉ߃X�e�[�W������
            }

            if (_pProg->getFrameInProgress() == 60) {
                _pMessage->activateImmediately();
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

void Stage01::processJudgement() {
}

void Stage01::processFinal() {

}

void Stage01::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_CONTROLLER_WAS_END ) {
        _TRACE_("Stage01::onCatchEvent() STAGEXXCONTROLLER_ENDING ���L���b�`�B�X�e�[�^�X��STAGE_PROG_END��");
        _pScene_Stage01PartController->end(60*60);
        _pProg->change(STAGE_PROG_END);
    } else {

    }
}


Stage01::~Stage01() {

}