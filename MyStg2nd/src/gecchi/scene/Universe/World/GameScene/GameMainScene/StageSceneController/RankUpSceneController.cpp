#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    RANKUPCONTROLLER_PROG_INIT = 1,
    RANKUPCONTROLLER_PROG_PLAY    ,
    RANKUPCONTROLLER_PROG_FINISH  ,
};
#define ORDER_ID_RANKUP 80

RankUpSceneController::RankUpSceneController(const char* prm_name) : StageScene(prm_name) {
    _class_name = "RankUpSceneController";
    _TRACE_("RankUpSceneController::RankUpSceneController("<<prm_name<<")");
    useProgress(RANKUPCONTROLLER_PROG_FINISH);
    readyStage(_RANK_LEVEL_ + 1);
}
void RankUpSceneController::execute() {
    readyStage(_RANK_LEVEL_ + 1); //次のシーンを先行予約
    _pLastRankUpScene = (RankUpScene*)obtainSceneFromFactory(ORDER_ID_RANKUP+_RANK_LEVEL_);
    _pLastRankUpScene->fadeoutScene(0);
    addSubLast(_pLastRankUpScene);
    _pLastRankUpScene->fadeinSceneTree(180);

    //スローダウン

}
void RankUpSceneController::slowdown(RankUpScene* prm_pLastAdded) {
    //スローダウン
    if (getSubFirst()) {
        //初回
        P_STAGE_CONTROLLER->setRunFrameOnceTree(2);
    } else {
        //連チャン
        P_STAGE_CONTROLLER->setRunFrameOnceTree(P_STAGE_CONTROLLER->_n_once*2);
        RankUpScene* pRankUpScene = (RankUpScene*)_pSubFirst;
        while(true) {
            pRankUpScene->setRunFrameOnceTree(pRankUpScene->_n_once*2);
            if (pRankUpScene == prm_pLastAdded) {
                //追加したてのシーンは等速
                break;
            } else {
                pRankUpScene = (RankUpScene*)(pRankUpScene->_pNext);
            }
        }
    }
}

void RankUpSceneController::slowRelease(RankUpScene* prm_pInactive) {
    RankUpScene* pRankUpScene = prm_pInactive;
    while(true) {
        pRankUpScene->setRunFrameOnceTree(pRankUpScene->_n_once/2);
        if (pRankUpScene->_is_first_flg) {
            //追加したてのシーンは等速
            ((RankUpScene*)(pRankUpScene->_pPrev))->setRunFrameOnceTree(pRankUpScene->_n_once/2);
            break;
        } else {
            pRankUpScene = (RankUpScene*)(pRankUpScene->_pPrev);
        }
    }
    P_STAGE_CONTROLLER->setRunFrameOnceTree(P_STAGE_CONTROLLER->_n_once/2);
}
void RankUpSceneController::onReset() {
    _pProg->set(RANKUPCONTROLLER_PROG_INIT);
}

void RankUpSceneController::readyStage(int prm_rank_level) {
    switch (prm_rank_level) {
        case 1:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_level, RankUp001, "RankUp001");
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
    switch (_pProg->get()) {
        case RANKUPCONTROLLER_PROG_INIT: {
            _pProg->change(RANKUPCONTROLLER_PROG_PLAY);
            break;
        }


        case RANKUPCONTROLLER_PROG_PLAY: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        case RANKUPCONTROLLER_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
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

