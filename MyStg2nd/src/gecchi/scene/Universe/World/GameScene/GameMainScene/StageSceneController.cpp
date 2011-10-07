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
    STAGESCENECONTROLLER_PROG_PLAY_RANKUP,
    STAGESCENECONTROLLER_PROG_FINISH  ,
};
#define ORDER_ID_STAGESCENE 11

StageSceneController::StageSceneController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageSceneController";

    _TRACE_("StageSceneController::StageSceneController("<<prm_name<<")");
//    _had_ready_main_stage = false;
    _loop = 1;
    _main_stage = 1;


    _pStageSceneMainCannel = NULL;

    _pTransitStage = NEW TransitStage("TransitStage");
    _pTransitStage->inactivateImmediately();
    addSubLast(_pTransitStage);

    _pRankUpSceneController = NEW RankUpSceneController("RankUpSceneController");
    _pRankUpSceneController->inactivateImmediately();
    addSubLast(_pRankUpSceneController);

    useProgress(STAGESCENECONTROLLER_PROG_FINISH);
}

void StageSceneController::onReset() {
    _TRACE_("StageSceneController::onReset()");
    if (_pStageSceneMainCannel) {
        _pStageSceneMainCannel->inactivate();
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
//    _main_stage++;
//    readyStage(_main_stage);
//}


void StageSceneController::readyStage(int prm_main_stage) {
    _TRACE_("StageSceneController::readyStage("<<prm_main_stage<<")");
    switch (prm_main_stage) {
        case 1:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_main_stage, Stage01, "Stage01");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_main_stage, Stage02, "Stage02");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_main_stage, Stage03, "Stage03");
            break;
        case 4:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_main_stage, Stage04, "Stage04");
            break;
        case 5:
            orderSceneToFactory(ORDER_ID_STAGESCENE+prm_main_stage, Stage05, "Stage05");
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
            readyStage(_main_stage);
            _pProg->change(STAGESCENECONTROLLER_PROG_BEGIN);
            break;
        }

        case STAGESCENECONTROLLER_PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageSceneController::processBehavior() Prog(=STAGESCENECONTROLLER_PROG_BEGIN) is Just Changed");
            }

            if (_pProg->getFrameInProgress() == 120) { //２秒遊ぶ
                _pProg->change(STAGESCENECONTROLLER_PROG_PLAY_STAGE);
            }
            break;
        }

        case STAGESCENECONTROLLER_PROG_PLAY_STAGE: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageSceneController::processBehavior() Prog(=STAGESCENECONTROLLER_PROG_PLAY_STAGE) is Just Changed");
                readyStage(_main_stage); //念のために呼ぶ。通常はもう準備できているハズ。
                //ステージシーン追加
                _pStageSceneMainCannel = (StageScene*)obtainSceneFromFactory(ORDER_ID_STAGESCENE+_main_stage);
                _pStageSceneMainCannel->fadeoutScene(0);
                addSubLast(_pStageSceneMainCannel);
                _pStageSceneMainCannel->fadeinSceneTree(180);
            }
            break;
        }

        case STAGESCENECONTROLLER_PROG_PLAY_TRANSIT: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageSceneController::processBehavior() Prog(=STAGESCENECONTROLLER_PROG_PLAY_TRANSIT) is Just Changed");
                _pTransitStage->fadeoutSceneTree(0);
                _pTransitStage->setStage(_main_stage);
                _pTransitStage->reset();
                _pTransitStage->activate();
                _pTransitStage->fadeinSceneTree(180);
            }
            //EVENT_TRANSIT_WAS_ENDイベント待ち

            break;
        }


        case STAGESCENECONTROLLER_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageSceneController::processBehavior() Prog(=STAGESCENECONTROLLER_PROG_FINISH) is Just Changed");
                _main_stage = _pTransitStage->_next_main_stage; //次のステージ
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
        _TRACE_("StageSceneController::onCatchEvent(EVENT_PREPARE_TRANSIT_STAGE)");
        _pTransitStage->ready(_main_stage);
    }

    if (prm_no == EVENT_PREPARE_NEXT_STAGE) {
        _TRACE_("StageSceneController::onCatchEvent(EVENT_PREPARE_NEXT_STAGE)");
        readyStage(_pTransitStage->_next_main_stage);//次のステージ準備
//            _TRACE_("最終面クリア");
//            _pProg->change(STAGESCENECONTROLLER_PROG_END);
            //TODO:エデニング？
//        }
    }

    if (prm_no == EVENT_STG01_WAS_END) {
        _TRACE_("StageSceneController::onCatchEvent(EVENT_STG01_WAS_END)");
        _pStageSceneMainCannel->end(180);
        _pStageSceneMainCannel->fadeoutSceneTree(180);
        _pProg->change(STAGESCENECONTROLLER_PROG_PLAY_TRANSIT);
    }
    if (prm_no == EVENT_STG02_WAS_END) {
        _TRACE_("StageSceneController::onCatchEvent(EVENT_STG02_WAS_END)");
        _pStageSceneMainCannel->end(180);
        _pStageSceneMainCannel->fadeoutSceneTree(180);
        _pProg->change(STAGESCENECONTROLLER_PROG_PLAY_TRANSIT);
    }
    if (prm_no == EVENT_TRANSIT_WAS_END) {
        _TRACE_("StageSceneController::onCatchEvent(EVENT_TRANSIT_WAS_END)");
        _pTransitStage->inactivateDelay(180);
        _pTransitStage->fadeoutSceneTree(180);
        _pProg->change(STAGESCENECONTROLLER_PROG_FINISH);
    }


}
void StageSceneController::processFinal() {
}

StageSceneController::~StageSceneController() {
}

