#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

TransitStage::TransitStage(const char* prm_name) : StageScene(prm_name) {
    _class_name = "TransitStage";

    _pWorldBoundSpace  = NEW WorldBoundSpaceTransit("WBSTransit");
    _pWorldBoundSpace->inactivateTree();
    getDirector()->addSubGroup(_pWorldBoundSpace);

    _pHoshiBoshi = NEW HoshiBoshiTransit("HoshiBoshiTransit");
    _pHoshiBoshi->inactivateTree();
    getDirector()->addSubGroup(KIND_EFFECT, _pHoshiBoshi);

    _pMessage = NEW LabelGecchi16Font("TransitStageMsg");
    getDirector()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

    fadeoutScene(0); //�ŏ��͔�\��
    useProgress(10);
}

void TransitStage::initialize() {
    StageScene::initialize();
}

void TransitStage::processBehavior() {
    StageScene::processBehavior();

    switch (_pProg->get()) {
        case STAGESCENE_PROG_INIT: {
            _pProg->change(STAGESCENE_PROG_BEGIN);
            break;
        }
        case STAGESCENE_PROG_BEGIN: {
            if (_pProg->getFrameInProgress() == 180) { //�X�e�[�W�P�J�n�I
                _pMessage->activateImmediately();
                _pWorldBoundSpace->activateTree();    //�w�iON
                _pHoshiBoshi->activateTree();    //�w�iON
                fadeinSceneTree(360);
                _pProg->change(STAGESCENE_PROG_PLAYING);
            }
            break;
        }
        case STAGESCENE_PROG_PLAYING: {
            if (_pProg->getFrameInProgress() == 60) { //�X�e�[�W�J�n�I
                _pMessage->update(300*1000, 300*1000, "SELECT NEXT STAGE!");
                _pMessage->inactivateDelay(240);
            }

            //�X�e�[�W���菈���̓R�R

            if (_pProg->getFrameInProgress() == 5*60) {
                _pProg->change(STAGESCENE_PROG_END);
            }
            break;
        }
        case STAGESCENE_PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("TransitStage::processBehavior()  STAGESCENE_PROG_END�ɂȂ�܂����I");
                throwEventToUpperTree(EVENT_PREPARE_NEXT_STAGE, this); //���X�e�[�W������
            }

            if (_pProg->getFrameInProgress() == 60) {
                _pMessage->activateImmediately();
                _pMessage->update(300*1000, 300*1000, "GOOD LUCK!");
                _pMessage->inactivateDelay(120);
                fadeoutScene(300);
            }
            if (_pProg->getFrameInProgress() == 300) {
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

void TransitStage::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_CONTROLLER_WAS_END ) {
        _TRACE_("TransitStage::onCatchEvent() STAGEXXCONTROLLER_ENDING ���L���b�`�B�X�e�[�^�X��STAGESCENE_PROG_END��");
        _pProg->change(STAGESCENE_PROG_END);
    } else {

    }
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


TransitStage::~TransitStage() {

}
