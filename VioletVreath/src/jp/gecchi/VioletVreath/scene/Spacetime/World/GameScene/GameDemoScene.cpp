#include "GameDemoScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include <stdio.h>
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT    ,
    PHASE_DEMOPLAY,
    PHASE_RANKING_TABLE ,
    PHASE_FINISH  ,
    PHASE_BANPEI,
};

#define ORDER_ID_DEMOSTAGE 12
GameDemoScene::GameDemoScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "GameDemoScene";
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    bringSceneMediator()->appendGroupChild(pLabel01_);
    pLabel02_ = NEW LabelGecchi16Font("STR02");
    bringSceneMediator()->appendGroupChild(pLabel02_);
    demo_stage_ = 1;

    papLabel_ranking_ = NEW LabelRankingFont*[G_RANKING_TABLE.getCount()];
    int cnt = (int)(G_RANKING_TABLE.getCount());
    for (int i = 0; i < cnt; i++) {
        papLabel_ranking_[i] = NEW LabelRankingFont("RANK_INFO");
        bringSceneMediator()->appendGroupChild(papLabel_ranking_[i]);
    }

}
void GameDemoScene::onReset() {
    getPhase()->reset(PHASE_INIT);
    pLabel01_->update("");
    pLabel02_->update("");
    int cnt = (int)(G_RANKING_TABLE.getCount());
    for (int i = 0; i < cnt; i++) {
        papLabel_ranking_[i]->update("");
        papLabel_ranking_[i]->inactivate();
    }
//    fadeinScene(0);
}

void GameDemoScene::onActive() {
}

void GameDemoScene::initialize() {
}

void GameDemoScene::processBehavior() {
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_INIT)");
            appendChild(pSTAGE_WORLD->extract());
            pSTAGE_WORLD->resetTree();
            pSTAGE_WORLD->inactivateImmed();
            pSTAGE_WORLD->activate();
            pPhase->change(PHASE_DEMOPLAY);
            break;
        }

        case PHASE_DEMOPLAY: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_DEMOPLAY)");
                pLabel01_->update(100*1000, 100*1000, "DEMOPLAY NOW");
                pLabel02_->update(100*1000, 150*1000, "GAME OVER");
                pLabel02_->setAlpha(pLabel02_->getAlphaFader()->getTop());
                pLabel02_->getAlphaFader()->beat(60, 3, 27, 3,-1);
            }

//            if (pPhase->getFrame() % 60 == 0) {
//                pLabel02_->update("");
//            } else if (pPhase->getFrame() % 60 == 30) {
//                pLabel02_->update("GAME OVER");
//            }


            if (pPhase->hasArrivedFrameAt(600)) {
                pPhase->change(PHASE_RANKING_TABLE);
            }
            break;
        }

        case PHASE_RANKING_TABLE: {
            int ranking_num = G_RANKING_TABLE.getCount();
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_RANKING_TABLE)");
                pLabel01_->update(PX_C(100), PX_C(100), "RANKING NOW");
                char buf[60];
                for (int i = 0; i < ranking_num; i++) {
                    sprintf(buf, "NO.%02d  %-12s  %10s  %s",
                            i+1,
                            G_RANKING_TABLE.getVal("NAME"   , i).c_str(),
                            G_RANKING_TABLE.getVal("SCORE"  , i).c_str(),
                            G_RANKING_TABLE.getVal("REGDATE", i).c_str());
                    papLabel_ranking_[i]->update(buf);
                    papLabel_ranking_[i]->setPosition(PX_C(400), PX_C(50+(i*22)));
                    papLabel_ranking_[i]->setAlpha(papLabel_ranking_[i]->getAlphaFader()->getBottom());
                    papLabel_ranking_[i]->getAlphaFader()->beat(SEC_F(25), SEC_F(2), SEC_F(20), SEC_F(2), 1); //フェードイン・しばらくしてフェードアウト
                    papLabel_ranking_[i]->activateDelay(SEC_F((i+1)*0.2)); //上から順番にぼやーっと表示していく
                }
            }

            if (papLabel_ranking_[ranking_num-1]->getAlphaFader()->isTransitioning()) {
                //一番最後のFaderがまだ動いてるならば
                for (int i = 0; i < ranking_num; i++) {
                    if (papLabel_ranking_[i]->isActive()) {
                        papLabel_ranking_[i]->getAlphaFader()->behave();
                    }
                }
            } else {
                //一番最後のFaderが動いてない＝表示終了
                for (int i = 0; i < ranking_num; i++) {
                    papLabel_ranking_[i]->inactivate();
                }
                pPhase->change(PHASE_FINISH);
            }
            break;
        }

        case PHASE_FINISH: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_FINISH)");
            }
            if (pPhase->hasArrivedFrameAt(SEC_F(6*60))) {
                _TRACE_(FUNC_NAME<<" throwEventUpperTree(EVENT_GAMEDEMOSCENE_FINISH)");
                throwEventUpperTree(EVENT_GAMEDEMOSCENE_FINISH); //終わったイベント発動
            }

            break;
        }

        default: {
            break;
        }
    }
    pLabel02_->getAlphaFader()->behave();
}

void GameDemoScene::onInactive() {
    _TRACE_(FUNC_NAME<<" ");
    if (pSTAGE_CTRLER->pStageMainCannel_) {
        _TRACE_(FUNC_NAME<<" pSTAGE_CTRLER->pStageMainCanne_("<<
                pSTAGE_CTRLER->pStageMainCannel_->getName()<<") sayonara()");
        pSTAGE_CTRLER->pStageMainCannel_->sayonara();
        pSTAGE_CTRLER->pStageMainCannel_ = nullptr;
    } else {
        //throwCriticalException("デモシーンのシーンが無い。あり得ないよ");
    }

    if (pRANKUP_CONTROLLER->pNowRankUpStage_) {
        _TRACE_(FUNC_NAME<<" pRANKUP_CONTROLLER->sayonaraRankUpStages()");
        pRANKUP_CONTROLLER->sayonaraRankUpStages();
        pRANKUP_CONTROLLER->pNowRankUpStage_ = nullptr;
    }
}

GameDemoScene::~GameDemoScene() {
    GGAF_DELETEARR(papLabel_ranking_);
}

