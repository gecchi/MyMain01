#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

enum {
    STAGECONTROLLER_PROG_INIT = 1,
    STAGECONTROLLER_PROG_BEGIN   ,
    STAGECONTROLLER_PROG_PLAY    ,
    STAGECONTROLLER_PROG_FINISH  ,
};
#define ORDER_ID_STAGESCENE 11
//StageController* StageController::_pStageController = NULL;

StageController::StageController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageController";

    _pSceneMainCannnel = NULL;
    _had_ready_stage = false;
    _stage = 1;
//    StageController::_pStageController = this;
    useProgress(STAGECONTROLLER_PROG_FINISH);
}

void StageController::onReset() {
//    VB_UI->clear();
//    VB_PLAY->clear();
//    P_GOD->setVB(VB_PLAY); //保存のためプレイ用に変更

//    _pFont1601->update("");
//    _pFont1602->update("");
    if (_pSceneMainCannnel) {
        _pSceneMainCannnel->inactivate();
    }
    P_COMMON_SCENE->resetTree();
    P_MYSHIP_SCENE->resetTree();
    P_COMMON_SCENE->activateImmediately();
    P_MYSHIP_SCENE->activateImmediately();

    addSubLast(P_COMMON_SCENE->extract());
    addSubLast(P_MYSHIP_SCENE->extract());

    _pProg->set(STAGECONTROLLER_PROG_INIT);
}
void StageController::readyNextStage() {
    _stage++;
    readyStage(_stage);
}

void StageController::readyStage(int prm_stage) {
    if (_had_ready_stage) {
        _TRACE_("＜警告＞StageController::readyStage 既に準備済みのステージがありますので無視します。_stage="<<_stage<<" prm_stage="<<prm_stage);
        return;
    }

    _stage = prm_stage;
    _had_ready_stage = true;
//    _frame_ready_stage = 0;
    switch (prm_stage) {
        case 1:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage01Scene, "Stage01");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage02Scene, "Stage02");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage03Scene, "Stage03");
            break;
        case 4:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage04Scene, "Stage04");
            break;
        case 5:
            orderSceneToFactory(ORDER_ID_STAGESCENE, Stage05Scene, "Stage05");
            break;
        default:
            break;
    }
}

void StageController::initialize() {

//    if (!pGameMainScene->_had_ready_stage) {
//        pGameMainScene->readyStage(_stage);
//    }
//    GgafScene* pCommon = P_COMMON_SCENE->extract();
//    addSubLast(pCommon); // 共通シーンを配下に移動（一時停止をうまく制御させるため！）
    //initialize()時はinactive()であることに注意する事
}

void StageController::processBehavior() {
    //SCORE表示
    switch (_pProg->get()) {
        case STAGECONTROLLER_PROG_INIT: {
            readyStage(_stage);
            _pProg->change(STAGECONTROLLER_PROG_BEGIN);
            break;
        }

        case STAGECONTROLLER_PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                if (_pSceneMainCannnel && !_pSceneMainCannnel->wasDeclaredEnd()) {
                    //2面目以降はこのタイミングで前ステージをend
                    _TRACE_("_pSceneMainCannnel="<<_pSceneMainCannnel->getName()<<" end()");
                    _pSceneMainCannnel->end();
                }
            }
            if (_pProg->getFrameInProgress() == 120) { //deleteを考慮し２秒遊ぶ
                _pProg->change(STAGECONTROLLER_PROG_PLAY);
            }
            break;
        }

        case STAGECONTROLLER_PROG_PLAY: {
            if (_pProg->isJustChanged()) {
                if (_had_ready_stage) {
                    _had_ready_stage = false;
                    _pSceneMainCannnel = (StageScene*)obtainSceneFromFactory(ORDER_ID_STAGESCENE);
                    addSubLast(_pSceneMainCannnel); //ステージシーン追加

                } else {
                    throwGgafCriticalException("StageController::processBehavior STAGECONTROLLER_PROG_BEGIN 準備済みステージがありません。_stage="<<_stage);
                }
            }
            break;
        }

        case STAGECONTROLLER_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        default:
            break;
    }

}




void StageController::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_PREPARE_NEXT_STAGE) {
        //次のステージを工場に注文していいよというイベント
        _TRACE_("StageController::onCatchEvent() EVENT_PREPARE_NEXT_STAGE 準備きた");
        if (_stage < 5) {
            readyNextStage();
        } else {
//            _TRACE_("最終面クリア");
//            _pProg->change(STAGECONTROLLER_PROG_END);
            //TODO:エデニング？
        }
    }

}

void StageController::processFinal() {
}

StageController::~StageController() {
}

