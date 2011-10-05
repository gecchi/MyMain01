#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

bool StageScene::_pause = false;

StageScene::StageScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageScene";
    useProgress(STAGESCENE_PROG_END);
}

void StageScene::initialize() {
    _pProg->set(STAGESCENE_PROG_INIT);
}

void StageScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_CONTROLLER_WAS_END ||
        prm_no == EVENT_STG02_CONTROLLER_WAS_END
    ) {
        _TRACE_("StageScene::onCatchEvent() STAGEXXCONTROLLER_ENDING をキャッチ。ステータスをSTAGESCENE_PROG_ENDへ");
        _pProg->change(STAGESCENE_PROG_END);
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
