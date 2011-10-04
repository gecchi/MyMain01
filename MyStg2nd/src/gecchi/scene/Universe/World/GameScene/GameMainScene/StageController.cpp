#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    STAGECONTROLLER_PROG_INIT = 1,
    STAGECONTROLLER_PROG_BEGIN   ,
    STAGECONTROLLER_PROG_PLAY    ,
    STAGECONTROLLER_PROG_FINISH  ,
};
#define ORDER_ID_STAGESCENE 11

StageController::StageController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageController";

    _pSceneMainCannnel = NULL;
//    _had_ready_stage = false;
    _loop = 1;
    _stage = 1;
    useProgress(STAGECONTROLLER_PROG_FINISH);
}

void StageController::onReset() {
    if (_pSceneMainCannnel) {
        _pSceneMainCannnel->inactivate();
    }
    //���ʃV�[���A���@�V�[����z���Ɉ��������Ă���
    P_COMMON_SCENE->resetTree();
    P_MYSHIP_SCENE->resetTree();
    P_COMMON_SCENE->activateImmediately();
    P_MYSHIP_SCENE->activateImmediately();
    addSubLast(P_COMMON_SCENE->extract());
    addSubLast(P_MYSHIP_SCENE->extract());

    _pProg->set(STAGECONTROLLER_PROG_INIT);
}
//void StageController::readyNextStage() {
//    _stage++;
//    readyStage(_stage);
//}

void StageController::readyStage(int prm_stage) {
//    if (_had_ready_stage) {
//        _TRACE_("���x����StageController::readyStage ���ɏ����ς݂̃X�e�[�W������܂��̂Ŗ������܂��B_stage="<<_stage<<" prm_stage="<<prm_stage);
//        return;
//    }
//
//    _stage = prm_stage;
//    _had_ready_stage = true;
    switch (prm_stage) {
        case 1:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_stage, Stage01Scene, "Stage01");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_stage, Stage02Scene, "Stage02");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_stage, Stage03Scene, "Stage03");
            break;
        case 4:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_stage, Stage04Scene, "Stage04");
            break;
        case 5:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_stage, Stage05Scene, "Stage05");
            break;
        default:
            break;
    }
}

void StageController::initialize() {
}

void StageController::processBehavior() {
    //SCORE�\��
    switch (_pProg->get()) {
        case STAGECONTROLLER_PROG_INIT: {
            readyStage(_stage);
            _pProg->change(STAGECONTROLLER_PROG_BEGIN);
            break;
        }

        case STAGECONTROLLER_PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
//                if (_pSceneMainCannnel && !_pSceneMainCannnel->wasDeclaredEnd()) {
//                    //2�ʖڈȍ~�͂��̃^�C�~���O�őO�X�e�[�W��end
//                    _TRACE_("_pSceneMainCannnel="<<_pSceneMainCannnel->getName()<<" end()");
//                    _pSceneMainCannnel->end();
//                }
            }
            if (_pProg->getFrameInProgress() == 120) { //delete���l�����Q�b�V��
                _pProg->change(STAGECONTROLLER_PROG_PLAY);
            }
            break;
        }

        case STAGECONTROLLER_PROG_PLAY: {
            if (_pProg->isJustChanged()) {
                readyStage(_stage);
                _pSceneMainCannnel = (StageScene*)obtainSceneFromFactory(ORDER_ID_STAGESCENE+_stage);
                addSubLast(_pSceneMainCannnel); //�X�e�[�W�V�[���ǉ�
            }
            break;
        }

        case STAGECONTROLLER_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _stage++;
                _pProg->change(STAGECONTROLLER_PROG_BEGIN); //���[�v
            }
            break;
        }

        default:
            break;
    }

}
void StageController::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_PREPARE_NEXT_STAGE) {
        //���̃X�e�[�W���H��ɒ������Ă�����Ƃ����C�x���g
        _TRACE_("StageController::onCatchEvent() EVENT_PREPARE_NEXT_STAGE ��������");
        if (_stage <= 5) {
            readyStage(_stage+1);
        } else {
//            _TRACE_("�ŏI�ʃN���A");
//            _pProg->change(STAGECONTROLLER_PROG_END);
            //TODO:�G�f�j���O�H
        }
    }

    if (prm_no == EVENT_STAGE01_WAS_END) {
        _TRACE_("StageController::onCatchEvent() EVENT_STAGE01_WAS_END");
        _pSceneMainCannnel->end(60*60);
        _pProg->change(STAGECONTROLLER_PROG_FINISH);
    }
    if (prm_no == EVENT_STAGE02_WAS_END) {
        _TRACE_("StageController::onCatchEvent() EVENT_STAGE01_WAS_END");
        _pSceneMainCannnel->end(60*60);
        _pProg->change(STAGECONTROLLER_PROG_FINISH);
    }


}
void StageController::processFinal() {
}

StageController::~StageController() {
}

