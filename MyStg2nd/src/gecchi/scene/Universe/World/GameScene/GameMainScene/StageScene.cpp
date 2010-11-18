#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

bool StageScene::_pause = false;

StageScene::StageScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageScene";
    useProgress(10);
}

void StageScene::initialize() {
    _pProgress->change(STAGE_SCENE_PROG_INIT);
}
void StageScene::processBehavior() {
    if (_pProgress->onActive(STAGE_SCENE_PROG_INIT)) {
    } else if (_pProgress->get() == STAGE_SCENE_PROG_INIT) {
    }

    if (_pProgress->onActive(STAGE_SCENE_PROG_BEGIN)) {
        _frame_Begin = 0;
    } else if (_pProgress->get() == STAGE_SCENE_PROG_BEGIN) {
        //�������[�v
        _frame_Begin++;
    }

    if (_pProgress->onActive(STAGE_SCENE_PROG_PLAYING)) {
        _frame_Play = 0;
    } else if (_pProgress->get() == STAGE_SCENE_PROG_PLAYING) {
        _frame_Play++;
    }

    if (_pProgress->onActive(STAGE_SCENE_PROG_END)) {
        _frame_End = 0;
        throwEventToUpperTree(EVENT_PREPARE_NEXT_STAGE, this); //���X�e�[�W������
    } else if (_pProgress->get() == STAGE_SCENE_PROG_END) {
        _frame_End++;
    }

}

void StageScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STAGE01CONTROLLER_WAS_END ||
        prm_no == EVENT_STAGE02CONTROLLER_WAS_END
    ) {
        _TRACE_("StageScene::onCatchEvent() STAGEXXCONTROLLER_ENDING ���L���b�`�B�X�e�[�^�X��STAGE_SCENE_PROG_END��");
        _pProgress->change(STAGE_SCENE_PROG_END);
    } else {

    }
}


//
//void StageScene::initialize() {
//}
//
//
//void StageScene::processJudgement() {
//}
//
//void StageScene::processFinal() {
//    //�ꎞ��~
//    if (VB->isPushedDown(VB_UI_CANCEL)) {
//        if (_pause) {
//            pauseTree();
//        } else {
//            unpauseTree();
//        }
//    }
//}

StageScene::~StageScene() {
}
