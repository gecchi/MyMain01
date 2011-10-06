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

#define ORDER_ID_RANKUP 80

RankUpSceneController::RankUpSceneController(const char* prm_name) : StageScene(prm_name) {
    _class_name = "RankUpSceneController";
    _TRACE_("RankUpSceneController::RankUpSceneController("<<prm_name<<")");
    _pRankUpSceneMainCannel = NULL;
//    _had_ready_rank = false;
//    _loop = 1;
    _rank = 1;
    useProgress(RANKUPCONTROLLER_PROG_FINISH);
}

void RankUpSceneController::onReset() {
    if (_pRankUpSceneMainCannel) {
        _pRankUpSceneMainCannel->inactivate();
    }
//    //共通シーン、自機シーンを配下に引っ張ってくる
//    P_COMMON_SCENE->resetTree();
//    P_MYSHIP_SCENE->resetTree();
//    P_COMMON_SCENE->activateImmediately();
//    P_MYSHIP_SCENE->activateImmediately();
//    addSubLast(P_COMMON_SCENE->extract());
//    addSubLast(P_MYSHIP_SCENE->extract());

    _pProg->set(RANKUPCONTROLLER_PROG_INIT);
}
//void RankUpSceneController::readyNextStage() {
//    _rank++;
//    readyStage(_rank);
//}

void RankUpSceneController::readyStage(int prm_rank) {
//    if (_had_ready_rank) {
//        _TRACE_("＜警告＞RankUpSceneController::readyStage 既に準備済みのステージがありますので無視します。_rank="<<_rank<<" prm_rank="<<prm_rank);
//        return;
//    }
//
//    _rank = prm_rank;
//    _had_ready_rank = true;
    switch (prm_rank) {
        case 1:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank, RankUp001, "RankUp001");
            break;
//        case 2:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank, Stage02, "Stage02");
//            break;
//        case 3:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank, Stage03, "Stage03");
//            break;
//        case 4:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank, Stage04, "Stage04");
//            break;
//        case 5:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank, Stage05, "Stage05");
//            break;
        default:
            break;
    }
}

void RankUpSceneController::initialize() {
}

void RankUpSceneController::processBehavior() {
    //SCORE表示
    switch (_pProg->get()) {
        case RANKUPCONTROLLER_PROG_INIT: {
            readyStage(_rank);
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
                readyStage(_rank);
                _pRankUpSceneMainCannel = (RankUpScene*)obtainSceneFromFactory(ORDER_ID_RANKUP+_rank);
                addSubLast(_pRankUpSceneMainCannel); //ステージシーン追加
            }
            break;
        }

        case RANKUPCONTROLLER_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _rank++;
                _pProg->change(RANKUPCONTROLLER_PROG_BEGIN); //ループ
            }
            break;
        }

        default:
            break;
    }

}
void RankUpSceneController::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
//    if (prm_no == EVENT_PREPARE_NEXT_STAGE) {
//        //次のステージを工場に注文していいよというイベント
//        _TRACE_("RankUpSceneController::onCatchEvent() EVENT_PREPARE_NEXT_STAGE 準備きた");
//        if (_rank <= 5) {
//            readyStage(_rank+1);
//        } else {
////            _TRACE_("最終面クリア");
////            _pProg->change(RANKUPCONTROLLER_PROG_END);
//            //TODO:エデニング？
//        }
//    }
//
//    if (prm_no == EVENT_STG01_WAS_END) {
//        _TRACE_("RankUpSceneController::onCatchEvent() EVENT_STG01_WAS_END");
//        _pRankUpSceneMainCannel->end(60*60);
//        _pProg->change(RANKUPCONTROLLER_PROG_FINISH);
//    }
//    if (prm_no == EVENT_STG02_WAS_END) {
//        _TRACE_("RankUpSceneController::onCatchEvent() EVENT_STG01_WAS_END");
//        _pRankUpSceneMainCannel->end(60*60);
//        _pProg->change(RANKUPCONTROLLER_PROG_FINISH);
//    }


}
void RankUpSceneController::processFinal() {
}

RankUpSceneController::~RankUpSceneController() {
}

