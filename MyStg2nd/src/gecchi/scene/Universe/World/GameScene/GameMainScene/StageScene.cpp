#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

bool StageScene::_pause = false;

StageScene::StageScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageScene";
}

void StageScene::initialize() {
    changeProgress(STAGE_SCENE_PROG_INIT);
}
void StageScene::processBehavior() {
    if (onActiveProgress(STAGE_SCENE_PROG_INIT)) {
    } else if (getProgress() == STAGE_SCENE_PROG_INIT) {
    }

    if (onActiveProgress(STAGE_SCENE_PROG_BEGIN)) {
        _frame_Begin = 0;
    } else if (getProgress() == STAGE_SCENE_PROG_BEGIN) {
        //活動ループ
        _frame_Begin++;
    }

    if (onActiveProgress(STAGE_SCENE_PROG_PLAYING)) {
        _frame_Play = 0;
    } else if (getProgress() == STAGE_SCENE_PROG_PLAYING) {
        _frame_Play++;
    }

    if (onActiveProgress(STAGE_SCENE_PROG_END)) {
        _frame_End = 0;
        throwEventToUpperTree(EVENT_PREPARE_NEXT_STAGE, this); //次ステージ準備へ
    } else if (getProgress() == STAGE_SCENE_PROG_END) {
        _frame_End++;
    }

}

void StageScene::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STAGE01CONTROLLER_WAS_END ||
        prm_no == EVENT_STAGE02CONTROLLER_WAS_END
    ) {
        _TRACE_("StageScene::catchEvent() STAGEXXCONTROLLER_ENDING をキャッチ。ステータスをSTAGE_SCENE_PROG_ENDへ");
        changeProgress(STAGE_SCENE_PROG_END);
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
//    //一時停止
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
