#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    RANKUPCONTROLLER_PROG_INIT = 1,
    RANKUPCONTROLLER_PROG_BEGIN   ,
    RANKUPCONTROLLER_PROG_PLAY    ,
    RANKUPCONTROLLER_PROG_FINISH  ,
};
#define ORDER_ID_RANKUP 111

RankUpController::RankUpController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "RankUpController";

    _pSceneMainCannnel = NULL;
//    _had_ready_stage = false;
    _loop = 1;
    _stage = 1;
    useProgress(RANKUPCONTROLLER_PROG_FINISH);
}

void RankUpController::onReset() {
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

    _pProg->set(RANKUPCONTROLLER_PROG_INIT);
}
//void RankUpController::readyNextStage() {
//    _stage++;
//    readyStage(_stage);
//}

void RankUpController::readyStage(int prm_stage) {
//    if (_had_ready_stage) {
//        _TRACE_("＜警告＞RankUpController::readyStage 既に準備済みのステージがありますので無視します。_stage="<<_stage<<" prm_stage="<<prm_stage);
//        return;
//    }
//
//    _stage = prm_stage;
//    _had_ready_stage = true;
    switch (prm_stage) {
        case 1:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_stage, Stage01, "Stage01");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_stage, Stage02, "Stage02");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_stage, Stage03, "Stage03");
            break;
        case 4:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_stage, Stage04, "Stage04");
            break;
        case 5:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_stage, Stage05, "Stage05");
            break;
        default:
            break;
    }
}

void RankUpController::initialize() {
}

void RankUpController::processBehavior() {
    //SCORE表示
    switch (_pProg->get()) {
        case RANKUPCONTROLLER_PROG_INIT: {
            readyStage(_stage);
            _pProg->change(RANKUPCONTROLLER_PROG_BEGIN);
            break;
        }

        case RANKUPCONTROLLER_PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
            }
            if (_pProg->getFrameInProgress() == 120) { //deleteを考慮し２秒遊ぶ
                _pProg->change(RANKUPCONTROLLER_PROG_PLAY);
            }
            break;
        }

        case RANKUPCONTROLLER_PROG_PLAY: {
            if (_pProg->isJustChanged()) {
                readyStage(_stage);
                _pSceneMainCannnel = (RankUpScene*)obtainSceneFromFactory(ORDER_ID_RANKUP+_stage);
                addSubLast(_pSceneMainCannnel); //ステージシーン追加
            }
            break;
        }

        case RANKUPCONTROLLER_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _stage++;
                _pProg->change(RANKUPCONTROLLER_PROG_BEGIN); //ループ
            }
            break;
        }

        default:
            break;
    }

}
void RankUpController::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_PREPARE_NEXT_STAGE) {
        //次のステージを工場に注文していいよというイベント
        _TRACE_("RankUpController::onCatchEvent() EVENT_PREPARE_NEXT_STAGE 準備きた");
        if (_stage <= 5) {
            readyStage(_stage+1);
        } else {
//            _TRACE_("最終面クリア");
//            _pProg->change(RANKUPCONTROLLER_PROG_END);
            //TODO:エデニング？
        }
    }

    if (prm_no == EVENT_STG01_WAS_END) {
        _TRACE_("RankUpController::onCatchEvent() EVENT_STG01_WAS_END");
        _pSceneMainCannnel->end(60*60);
        _pProg->change(RANKUPCONTROLLER_PROG_FINISH);
    }
    if (prm_no == EVENT_STG02_WAS_END) {
        _TRACE_("RankUpController::onCatchEvent() EVENT_STG01_WAS_END");
        _pSceneMainCannnel->end(60*60);
        _pProg->change(RANKUPCONTROLLER_PROG_FINISH);
    }


}
void RankUpController::processFinal() {
}

RankUpController::~RankUpController() {
}

