#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

RankUp001::RankUp001(const char* prm_name) : RankUpScene(prm_name) {
    _class_name = "RankUp001";

    Sleep(2);
    _pWorldBoundSpace  = NEW WorldBoundSpace001("BG_SPACE");
    _pWorldBoundSpace->inactivateTree();
    getDirector()->addSubGroup(KIND_EFFECT, _pWorldBoundSpace);

    _pHoshiBoshi = NEW HoshiBoshi001("HoshiBoshi001");
    _pHoshiBoshi->inactivateTree();
    getDirector()->addSubGroup(KIND_EFFECT, _pHoshiBoshi);

    _pMessage = NEW LabelGecchi16Font("RankUp001Msg");
    getDirector()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

    fadeoutScene(0); //�ŏ��͔�\��
    useProgress(10);
}

void RankUp001::initialize() {
    RankUpScene::initialize();
}

void RankUp001::processBehavior() {
    RankUpScene::processBehavior();

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
            if (_pProg->getFrameInProgress() == 60) { //�X�e�[�W�P�J�n�I
                _pMessage->update(300*1000, 300*1000, "SCENE 01 START!");
                _pMessage->inactivateDelay(240);
            }
            //EVENT_STG01_CONTROLLER_WAS_END�C�x���g�҂�
            break;
        }
        case STAGESCENE_PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("RankUp001::processBehavior()  STAGESCENE_PROG_END�ɂȂ�܂����I");
                throwEventToUpperTree(EVENT_PREPARE_NEXT_STAGE, this); //���X�e�[�W������
            }

            if (_pProg->getFrameInProgress() == 60) {
                _pMessage->activateImmediately();
                _pMessage->update(300*1000, 300*1000, "SCENE 01 CLEAR!!");
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

void RankUp001::processJudgement() {
}


void RankUp001::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_CONTROLLER_WAS_END ) {
        _TRACE_("RankUp001::onCatchEvent() STAGEXXCONTROLLER_ENDING ���L���b�`�B�X�e�[�^�X��STAGESCENE_PROG_END��");
        _pProg->change(STAGESCENE_PROG_END);
    } else {

    }
}


RankUp001::~RankUp001() {

}
