#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    STAGESCENECONTROLLER_PROG_INIT = 1,
    STAGESCENECONTROLLER_PROG_BEGIN   ,
    STAGESCENECONTROLLER_PROG_PLAY_STAGE,
    STAGESCENECONTROLLER_PROG_PLAY_TRANSIT,
    STAGESCENECONTROLLER_PROG_FINISH  ,
};
#define ORDER_ID_STAGESCENE 11
#define ORDER_ID_TRANSIT 111

StageSceneController::StageSceneController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageSceneController";

    _pSceneMainCannnel = NULL;
//    _had_ready_stage = false;
    _loop = 1;
    _stage = 1;
    useProgress(STAGESCENECONTROLLER_PROG_FINISH);
}

void StageSceneController::onReset() {
    if (_pSceneMainCannnel) {
        _pSceneMainCannnel->inactivate();
    }
    //共通シーン、自機シーンを配下に引っ張ってくる
    P_COMMON_SCENE->resetTree();
    P_MYSHIP_SCENE->resetTree();
    P_COMMON_SCENE->activateImmediately();
    P_MYSHIP_SCENE->activateImmediately();
    addSubLast(P_COMMON_SCENE->extract());
    addSubLast(P_MYSHIP_SCENE->extract());

    _pProg->set(STAGESCENECONTROLLER_PROG_INIT);
}
//void StageSceneController::readyNextStage() {
//    _stage++;
//    readyStage(_stage);
//}


void StageSceneController::readyStage(int prm_stage) {
    switch (prm_stage) {
        case 1:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_stage, Stage01, "Stage01");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_stage, Stage02, "Stage02");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_stage, Stage03, "Stage03");
            break;
        case 4:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_stage, Stage04, "Stage04");
            break;
        case 5:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_stage, Stage05, "Stage05");
            break;
        default:
            break;
    }
}

void StageSceneController::initialize() {
}

void StageSceneController::processBehavior() {
    //SCORE表示
    switch (_pProg->get()) {
        case STAGESCENECONTROLLER_PROG_INIT: {
            readyStage(_stage);
            _pProg->change(STAGESCENECONTROLLER_PROG_BEGIN);
            break;
        }

        case STAGESCENECONTROLLER_PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
            }
            if (_pProg->getFrameInProgress() == 120) { //deleteを考慮し２秒遊ぶ
                _pProg->change(STAGESCENECONTROLLER_PROG_PLAY_STAGE);
            }
            break;
        }

        case STAGESCENECONTROLLER_PROG_PLAY_STAGE: {
            if (_pProg->isJustChanged()) {
                readyStage(_stage);
                _pSceneMainCannnel = (StageScene*)obtainSceneFromFactory(ORDER_ID_STAGESCENE+_stage);
                addSubLast(_pSceneMainCannnel); //ステージシーン追加
            }
            break;
        }

        case STAGESCENECONTROLLER_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _stage++;
                _pProg->change(STAGESCENECONTROLLER_PROG_BEGIN); //ループ
            }
            break;
        }

        default:
            break;
    }

}
void StageSceneController::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_PREPARE_TRANSIT_STAGE) {

    }
    if (prm_no == EVENT_PREPARE_NEXT_STAGE) {
        //次のステージを工場に注文していいよというイベント
        _TRACE_("StageSceneController::onCatchEvent() EVENT_PREPARE_NEXT_STAGE 準備きた");
        if (_stage <= 5) {
            readyStage(_stage+1);
        } else {
//            _TRACE_("最終面クリア");
//            _pProg->change(STAGESCENECONTROLLER_PROG_END);
            //TODO:エデニング？
        }
    }

    if (prm_no == EVENT_STG01_WAS_END) {
        _TRACE_("StageSceneController::onCatchEvent() EVENT_STG01_WAS_END");
        _pSceneMainCannnel->end(60*60);
        _pProg->change(STAGESCENECONTROLLER_PROG_FINISH);
    }
    if (prm_no == EVENT_STG02_WAS_END) {
        _TRACE_("StageSceneController::onCatchEvent() EVENT_STG01_WAS_END");
        _pSceneMainCannnel->end(60*60);
        _pProg->change(STAGESCENECONTROLLER_PROG_FINISH);
    }


}
void StageSceneController::processFinal() {
}

StageSceneController::~StageSceneController() {
}

