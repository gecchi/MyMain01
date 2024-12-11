#include "RankUpStageController.h"

#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp001.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp002.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp003.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp100.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/manager/SeConnection.h"

using namespace GgafLib;
using namespace VioletVreath;

#define ORDER_ID_RANKUP (80)

enum {
    PHASE_INIT  ,
    PHASE_PLAY  ,
    PHASE_FINISH,
    PHASE_BANPEI,
};

RankUpStageController::RankUpStageController(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "RankUpStageController";
    _TRACE_("RankUpStageController::RankUpStageController("<<prm_name<<")");

    for (int i = 0; i < MAX_RANKUP_SCENE; i ++) {
        apRankUpStage_[i] = nullptr;
    }

    pSeConn_RankUpStageExec_ = connectToSeManager("SE_RANK_UP_STAGE_EXEC");
    ready(G_RANKUP_LEVEL + 1);
}
void RankUpStageController::startRunkUpStage(int prm_rank_up_level) {
    pSeConn_RankUpStageExec_->peek()->play(); //ランクアップステージ開始SE！
    ready(prm_rank_up_level);     //これはパスされるはずであるが、念のため。
    ready(prm_rank_up_level + 1); //次のシーンを先行予約
    pNowRankUpStage_ = (RankUpStage*)receiveScene(ORDER_ID_RANKUP+prm_rank_up_level);
    _TRACE_(FUNC_NAME<<" pNowRankUpStage_="<<pNowRankUpStage_);
    GgafCore::Scene* pRankUpStage = getChildFirst();
    if (pRankUpStage) {
        //他のランクアップ中
        //既存ランクアップシーンをさらにスローにする
        while (1) {
            ((RankUpStage*)pRankUpStage)->addRunFrameOnce(SLOW_FRAME_RANKUP);
            if (pRankUpStage->isLast()) {
                break;
            } else {
                pRankUpStage = pRankUpStage->getNext();
            }
        }
    }
    appendChild(pNowRankUpStage_);
    pNowRankUpStage_->fadeoutSceneWithBgm(0);
    pNowRankUpStage_->fadeinScene(240);
    apRankUpStage_[prm_rank_up_level-1] = pNowRankUpStage_;
    //スローダウン
}

void RankUpStageController::onReset() {
    getPhase()->reset(PHASE_INIT);
}

void RankUpStageController::ready(int prm_rank_up_level) {
    switch (prm_rank_up_level) {
        case 1:
            requestScene(ORDER_ID_RANKUP+prm_rank_up_level, RankUp001);
            break;
        case 2:
            requestScene(ORDER_ID_RANKUP+prm_rank_up_level, RankUp002);
            break;
        case 3:
            requestScene(ORDER_ID_RANKUP+prm_rank_up_level, RankUp003);
            break;
//        case 100:
//            requestScene(ORDER_ID_RANKUP+prm_rank_up_level, RankUp100);
//            break;
        default:
            requestScene(ORDER_ID_RANKUP+prm_rank_up_level, RankUp100);
            break;
    }
}

void RankUpStageController::initialize() {
    getPhase()->reset(PHASE_INIT);
}

void RankUpStageController::processBehavior() {
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->changeNext();
            break;
        }

        case PHASE_PLAY: {
            if (pPhase->hasJustChanged()) {
            }
            break;
        }

        case PHASE_FINISH: {
            if (pPhase->hasJustChanged()) {
            }
            break;
        }

        default:
            break;
    }

}
void RankUpStageController::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    if (prm_event_val == EVENT_RANKUP_WAS_END) {
        _TRACE_(FUNC_NAME<<" EVENT_RANKUP_WAS_END prm_pSource="<<prm_pSource);
        RankUpStage* pScene = (RankUpStage*)prm_pSource; //終了宣言したRankUpStage
        pScene->fadeoutSceneWithBgm(SEC_F(4));
        pScene->sayonara(SEC_F(4));

        //スロー回復
        GgafCore::Scene* pRankUpStage = getChildFirst();
        if (pRankUpStage) {
            //他のランクアップ中
            //既存ランクアップシーンをスロー回復
            while (1) {
                if (pRankUpStage == pScene) {
                    break;
                } else {
                    ((RankUpStage*)pRankUpStage)->addRunFrameOnce(-SLOW_FRAME_RANKUP); //スロー回復
                    _TRACE_("pRankUpStage="<<pRankUpStage->getName()<<"をスロー回復");
                    pRankUpStage = pRankUpStage->getNext();
                }
            }
        } else {
            throwCriticalException("EVENT_RANKUP_WAS_END 子がnullptr。"
                                       "this="<<NODE_INFO<<" prm_pSource="<<prm_pSource);
        }
    }
}

void RankUpStageController::sayonaraRankUpStages(frame prm_offset_frames) {
    if (getChildFirst()) {
        RankUpStage* pRankUpStage = (RankUpStage*)getChildFirst()->getPrev();//last
        if (pRankUpStage) {
            while (1) {
                _TRACE_(FUNC_NAME<<" pRankUpStage("<<pRankUpStage->getName()<<")->sayonara()");
                pRankUpStage->fadeoutSceneWithBgmTree(prm_offset_frames);
                pRankUpStage->sayonara(prm_offset_frames);
                if (pRankUpStage == getChildFirst()) {
                    break;
                } else {
                    pRankUpStage = (RankUpStage*)pRankUpStage->getPrev();
                }
            }
        }
    }
}

RankUpStageController::~RankUpStageController() {
    pSeConn_RankUpStageExec_->close();
}

