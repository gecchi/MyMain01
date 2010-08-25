#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

bool StageScene::_pause = false;

StageScene::StageScene(const char* prm_name) : DefaultScene(prm_name) {
    setProgress(STAGE_PROG_INIT);
}

void StageScene::initialize() {

}
void StageScene::processBehavior() {
    if (onChangeProgressAt(STAGE_PROG_INIT)) {
        addSubLast(pCOMMONSCENE->extract()); // ���ʃV�[����z���Ɉړ��i�ꎞ��~�����܂����䂳���邽�߁I�j
    } else if (getProgress() == STAGE_PROG_INIT) {
    }

    if (onChangeProgressAt(STAGE_PROG_BEGIN)) {
        _frame_Begin = 0;
    } else if (getProgress() == STAGE_PROG_BEGIN) {
        //�������[�v
        _frame_Begin++;
    }

    if (onChangeProgressAt(STAGE_PROG_PLAYING)) {
        _frame_Play = 0;
    } else if (getProgress() == STAGE_PROG_PLAYING) {
        _frame_Play++;
    }

    if (onChangeProgressAt(STAGE_PROG_END)) {
        _frame_End = 0;
        throwUpEvent(READY_NEXT_STAGE, this); //���X�e�[�W������
    } else if (getProgress() == STAGE_PROG_END) {
        _frame_End++;
    }

}

void StageScene::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == STAGE01CONTROLLER_WAS_END ||
        prm_no == STAGE02CONTROLLER_WAS_END
    ) {
        _TRACE_("StageScene::catchEvent() STAGEXXCONTROLLER_ENDING ���L���b�`�B�X�e�[�^�X��STAGE_PROG_END��");
        setProgress(STAGE_PROG_END);
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
