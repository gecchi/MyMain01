#include "RankUpStageController.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp001.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp002.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp003.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp100.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/manager/GgafDxSeConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define ORDER_ID_RANKUP (80)

RankUpStageController::RankUpStageController(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "RankUpStageController";
    _TRACE_("RankUpStageController::RankUpStageController("<<prm_name<<")");

    for (int i = 0; i < MAX_RANKUP_SCENE; i ++) {
        apRankUpStage_[i] = nullptr;
    }

    pSeConn_RankUpStageExec_ = connectToSeManager("WAVE_RANK_UP_STAGE_EXEC");

    useProgress(RankUpStageController::PROG_BANPEI-1);
    ready(G_RANKUP_LEVEL + 1);
    useProgress(PROG_BANPEI);
}
void RankUpStageController::startRunkUpStage(int prm_rank_up_level) {
    pSeConn_RankUpStageExec_->peek()->play(); //ランクアップステージ開始SE！
    ready(prm_rank_up_level);     //これはパスされるはずであるが、念のため。
    ready(prm_rank_up_level + 1); //次のシーンを先行予約
    pNowRankUpStage_ = (RankUpStage*)obtainSceneFromFactory(ORDER_ID_RANKUP+prm_rank_up_level);
    _TRACE_(FUNC_NAME<<" pNowRankUpStage_="<<pNowRankUpStage_);
    GgafScene* pRankUpStage = getSubFirst();
    if (pRankUpStage) {
        //他のランクアップ中
        //既存ランクアップシーンをさらにスローにする
        while (1) {
            pRankUpStage->addRunFrameOnce(SLOW_FRAME_RANKUP);
            if (pRankUpStage->isLast()) {
                break;
            } else {
                pRankUpStage = pRankUpStage->getNext();
            }
        }
    }
    addSubLast(pNowRankUpStage_);
    pNowRankUpStage_->fadeoutSceneWithBgm(0);
    pNowRankUpStage_->fadeinScene(240);
    apRankUpStage_[prm_rank_up_level-1] = pNowRankUpStage_;
    //スローダウン
}

void RankUpStageController::onReset() {
    getProgress()->reset(PROG_INIT);
}

void RankUpStageController::ready(int prm_rank_up_level) {
    switch (prm_rank_up_level) {
        case 1:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp001, "RankUp001");
            break;
        case 2:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp002, "RankUp002");
            break;
        case 3:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp003, "RankUp003");
            break;
//        case 100:
//            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp100, "RankUp100");
//            break;
        default:
            orderSceneToFactory(ORDER_ID_RANKUP+prm_rank_up_level, RankUp100, "RankUp100");
            break;
    }
}

void RankUpStageController::initialize() {
    getProgress()->reset(PROG_INIT);
}

void RankUpStageController::processBehavior() {
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->changeNext();
            break;
        }

        case PROG_PLAY: {
            if (pProg->hasJustChanged()) {
            }
            break;
        }

        case PROG_FINISH: {
            if (pProg->hasJustChanged()) {
            }
            break;
        }

        default:
            break;
    }

}
void RankUpStageController::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_RANKUP_WAS_END) {
        _TRACE_(FUNC_NAME<<" EVENT_RANKUP_WAS_END prm_pSource="<<prm_pSource);
        RankUpStage* pScene = (RankUpStage*)prm_pSource; //終了宣言したRankUpStage
        pScene->fadeoutSceneWithBgm(240);
        pScene->sayonara(240);

        //スロー回復
        GgafScene* pRankUpStage = getSubFirst();
        if (pRankUpStage) {
            //他のランクアップ中
            //既存ランクアップシーンをスロー回復
            while (1) {
                if (pRankUpStage == pScene) {
                    break;
                } else {
                    pRankUpStage->addRunFrameOnce(-SLOW_FRAME_RANKUP); //スロー回復
                    _TRACE_("pRankUpStage="<<pRankUpStage->getName()<<"をスロー回復");
                    pRankUpStage = pRankUpStage->getNext();
                }
            }
        } else {
            throwGgafCriticalException("EVENT_RANKUP_WAS_END サブがnullptr。"
                                       "this="<<NODE_INFO<<" prm_pSource="<<prm_pSource);
        }
    }
}

void RankUpStageController::sayonaraRankUpStages() {
    if (getSubFirst()) {
        GgafScene* pRankUpStage = getSubFirst()->getPrev();//last
        if (pRankUpStage) {
            while (1) {
                pRankUpStage->sayonara();
                if (pRankUpStage == getSubFirst()) {
                    break;
                } else {
                    pRankUpStage = pRankUpStage->getPrev();
                }
            }
        }
    }
}

RankUpStageController::~RankUpStageController() {
    pSeConn_RankUpStageExec_->close();
}

