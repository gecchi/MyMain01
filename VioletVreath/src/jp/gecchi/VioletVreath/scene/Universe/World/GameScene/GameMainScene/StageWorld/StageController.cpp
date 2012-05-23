#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


#define ORDER_ID_STAGE 11

StageController::StageController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "StageController";

    _TRACE_("StageController::StageController("<<prm_name<<")");
//    had_ready_main_stage_ = false;
    loop_ = 1;
    main_stage_ = 1;
    pStageMainCannel_ = NULL;

    pTransitStage_ = NEW TransitStage("TransitStage");
    pTransitStage_->inactivateImmed();
    addSubLast(pTransitStage_);

    useProgress(StageController::PROG_FINISH);
}

void StageController::onReset() {
    _TRACE_("StageController::onReset()");
    if (pStageMainCannel_) {
        pStageMainCannel_->inactivate();
    }
    //共通シーン、自機シーンを配下に引っ張ってくる
    P_COMMON_SCENE->resetTree();
    P_COMMON_SCENE->activateImmed();
    addSubLast(P_COMMON_SCENE->extract());
    _pProg->set(StageController::PROG_INIT);
}
//void StageController::readyNextStage() {
//    main_stage_++;
//    readyStage(main_stage_);
//}


void StageController::readyStage(int prm_main_stage) {
    _TRACE_("StageController::readyStage("<<prm_main_stage<<")");
    switch (prm_main_stage) {
        case 1:
            orderSceneToFactory(ORDER_ID_STAGE+prm_main_stage, Stage01, "Stage01");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_STAGE+prm_main_stage, Stage02, "Stage02");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_STAGE+prm_main_stage, Stage03, "Stage03");
            break;
        case 4:
            orderSceneToFactory(ORDER_ID_STAGE+prm_main_stage, Stage04, "Stage04");
            break;
        case 5:
            orderSceneToFactory(ORDER_ID_STAGE+prm_main_stage, Stage05, "Stage05");
            break;
        default:
            break;
    }
}

void StageController::initialize() {
}

void StageController::processBehavior() {
    //SCORE表示
    switch (_pProg->get()) {
        case StageController::PROG_INIT: {
            readyStage(main_stage_);
            _pProg->change(StageController::PROG_BEGIN);
            break;
        }

        case StageController::PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog(=StageController::PROG_BEGIN) is Just Changed");
            }
            if (_pProg->getFrameInProgress() == 120) { //２秒遊ぶ
                _pProg->change(StageController::PROG_PLAY_STAGE);
            }
            break;
        }

        case StageController::PROG_PLAY_STAGE: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog(=StageController::PROG_PLAY_STAGE) is Just Changed. main_stage_="<<main_stage_);
                readyStage(main_stage_); //念のために呼ぶ。通常はもう準備できているハズ。
                //ステージシーン追加
                if (pStageMainCannel_) {
                    _TRACE_("いいのか！ StageController::PROG_PLAY_STAGE: 旧 pStageMainCannel_="<<pStageMainCannel_->getName()<<"");
                }
                pStageMainCannel_ = (Stage*)obtainSceneFromFactory(ORDER_ID_STAGE+main_stage_);
                _TRACE_("StageController::PROG_PLAY_STAGE: 新 pStageMainCannel_="<<pStageMainCannel_->getName()<<"");
                pStageMainCannel_->fadeoutScene(0);
                addSubLast(pStageMainCannel_);
                pStageMainCannel_->fadeinSceneTree(180);
            }
            break;
        }

        case StageController::PROG_PLAY_TRANSIT: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog(=StageController::PROG_PLAY_TRANSIT) is Just Changed. main_stage_="<<main_stage_);
                pTransitStage_->fadeoutSceneTree(0);
                _TRACE_("StageController::processBehavior() pTransitStage_->setStage("<<main_stage_<<")");
                pTransitStage_->setStage(main_stage_);
                pTransitStage_->reset();
                pTransitStage_->activate();
                pTransitStage_->fadeinSceneTree(180);
            }
            //EVENT_TRANSIT_WAS_ENDイベント待ち
            break;
        }

        case StageController::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog(=StageController::PROG_FINISH) is Just Changed pTransitStage_->next_main_stage_="<<pTransitStage_->next_main_stage_);
                main_stage_ = pTransitStage_->next_main_stage_; //次のステージ
                _pProg->change(StageController::PROG_BEGIN); //ループ
            }
            break;
        }

        default:
            break;
    }


/*
    //ランクアップシーン差し込み
    if (_RANK_DISP_ % 10 == 0) {
        if (can_rank_up_) {
            can_rank_up_ = false;
            _RANK_UP_LEVEL_++;
            pRankUpStageCtrlr_->execute();
        } else {
            //スルー
        }
    } else {
        can_rank_up_ = false;
    }
*/
//    _non_rtti_object_
//    http://msdn.microsoft.com/en-us/library/cby9kycs.aspx

}
void StageController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_PREPARE_TRANSIT_STAGE) {
        _TRACE_("StageController::onCatchEvent(EVENT_PREPARE_TRANSIT_STAGE)");
        pTransitStage_->ready(main_stage_);
    }

    if (prm_no == EVENT_PREPARE_NEXT_STAGE) {
        _TRACE_("StageController::onCatchEvent(EVENT_PREPARE_NEXT_STAGE)");
        readyStage(pTransitStage_->next_main_stage_);//次のステージ準備
//            _TRACE_("最終面クリア");
//            _pProg->change(StageController::PROG_END);
            //TODO:エデニング？
//        }
    }

    if (prm_no == EVENT_STG01_WAS_END) {
        _TRACE_("StageController::onCatchEvent(EVENT_STG01_WAS_END)");
        pStageMainCannel_->end(180);
        pStageMainCannel_->fadeoutSceneTree(180);
        _pProg->change(StageController::PROG_PLAY_TRANSIT);
    }
    if (prm_no == EVENT_STG02_WAS_END) {
        _TRACE_("StageController::onCatchEvent(EVENT_STG02_WAS_END)");
        pStageMainCannel_->end(180);
        pStageMainCannel_->fadeoutSceneTree(180);
        _pProg->change(StageController::PROG_PLAY_TRANSIT);
    }
    if (prm_no == EVENT_TRANSIT_WAS_END) {
        _TRACE_("StageController::onCatchEvent(EVENT_TRANSIT_WAS_END)");
        pTransitStage_->inactivateDelay(180);
        pTransitStage_->fadeoutSceneTree(180);
        _pProg->change(StageController::PROG_FINISH);
    }

}

StageController::~StageController() {
}

