#include "StageController.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/Stage01PartController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage02.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage02/Stage02PartController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage03.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage04.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage05.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

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
    pStageMainCannel_ = nullptr;

    pTransitStage_ = NEW TransitStage("TransitStage");
    pTransitStage_->inactivate();
    addSubLast(pTransitStage_);

    _pSceneSymbol = NEW LabelSceneSymbol("LabelSceneSymbol");
    getSceneDirector()->addSubGroup(_pSceneSymbol);


    useProgress(StageController::PROG_BANPEI-1);
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
    getProgress()->reset(StageController::PROG_INIT);
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
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case StageController::PROG_INIT: {
            _TRACE_("StageController::processBehavior() Prog is StageController::PROG_INIT");

            readyStage(main_stage_);
            pProg->change(StageController::PROG_BEGIN);
            break;
        }

        case StageController::PROG_BEGIN: {
            if (pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog has Just Changed (to StageController::PROG_BEGIN)");
                _TRACE_("StageController::processBehavior() 直後 main_stage_="<<main_stage_);
            }
            if (pProg->arriveAtFrameOf(120)) { //２秒遊ぶ
                pProg->change(StageController::PROG_PLAY_STAGE);
            }
            break;
        }

        case StageController::PROG_PLAY_STAGE: {
            if (pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog has Just Changed (to StageController::PROG_PLAY_STAGE)");
                _TRACE_("StageController::processBehavior() 直後 main_stage_="<<main_stage_);
                readyStage(main_stage_); //念のために呼ぶ。通常はもう準備できているハズ。
                //ステージシーン追加
                if (pStageMainCannel_) {
                    _TRACE_("いいのか！ StageController::PROG_PLAY_STAGE: 旧 pStageMainCannel_="<<pStageMainCannel_->getName()<<"");
                }
                pStageMainCannel_ = (Stage*)obtainSceneFromFactory(ORDER_ID_STAGE+main_stage_);
                _TRACE_("StageController::PROG_PLAY_STAGE: 新 pStageMainCannel_="<<pStageMainCannel_->getName()<<"");
                pStageMainCannel_->fadeoutSceneWithBgm(0);

                addSubLast(pStageMainCannel_);
                pStageMainCannel_->fadeinSceneTree(180);
            }
            break;
        }

        case StageController::PROG_PLAY_TRANSIT: {
            if (pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog has Just Changed (to StageController::PROG_PLAY_TRANSIT)");
                _TRACE_("StageController::processBehavior() 直後 main_stage_="<<main_stage_);
                pTransitStage_->fadeoutSceneWithBgmTree(0);
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
            if (pProg->isJustChanged()) {
                _TRACE_("StageController::processBehavior() Prog has Just Changed (to StageController::PROG_FINISH)");
                _TRACE_("StageController::processBehavior() 直後 main_stage_="<<main_stage_);
                main_stage_ = pTransitStage_->next_main_stage_; //次のステージ
                _TRACE_("StageController::processBehavior() main_stage_ = pTransitStage_->next_main_stage_;");
                _TRACE_("StageController::processBehavior() 更新された main_stage_="<<main_stage_);
                pProg->change(StageController::PROG_BEGIN); //ループ
            }
            break;
        }

        default: {
            break;
        }
    }


/*
    //ランクアップシーン差し込み
    if (G_RANK_DISP % 10 == 0) {
        if (can_rank_up_) {
            can_rank_up_ = false;
            G_RANKUP_LEVEL++;
            pRankUpStageCtrler_->execute();
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
        int next_stage = *((int*)(prm_pSource));
        readyStage(next_stage);//次のステージ準備
//            _TRACE_("最終面クリア");
//            pProg->change(StageController::PROG_END);
            //TODO:エデニング？
//        }
    }
    SceneProgress* pProg = getProgress();
    if (prm_no == EVENT_STG01_WAS_END) {
        _TRACE_("StageController::onCatchEvent(EVENT_STG01_WAS_END)");
        pStageMainCannel_->sayonara(180);
        pStageMainCannel_->fadeoutSceneWithBgmTree(180);
        pProg->change(StageController::PROG_PLAY_TRANSIT);
    }
    if (prm_no == EVENT_STG02_WAS_END) {
        _TRACE_("StageController::onCatchEvent(EVENT_STG02_WAS_END)");
        pStageMainCannel_->sayonara(180);
        pStageMainCannel_->fadeoutSceneWithBgmTree(180);
        pProg->change(StageController::PROG_PLAY_TRANSIT);
    }
    if (prm_no == EVENT_TRANSIT_WAS_END) {
        _TRACE_("StageController::onCatchEvent(EVENT_TRANSIT_WAS_END)");
        pTransitStage_->inactivateDelay(180);
        pTransitStage_->fadeoutSceneWithBgmTree(180);
        pProg->change(StageController::PROG_FINISH);
    }

}

StageController::~StageController() {
}

