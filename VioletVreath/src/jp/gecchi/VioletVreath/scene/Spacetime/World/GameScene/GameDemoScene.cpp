#include "GameDemoScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include <stdio.h>
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT    ,
    PROG_DEMOPLAY,
    PROG_RANKING_TABLE ,
    PROG_FINISH  ,
    PROG_BANPEI,
};

#define ORDER_ID_DEMOSTAGE 12
GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameDemoScene";
    useProgress(PROG_BANPEI);
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
    getProgress()->reset(PROG_INIT);
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
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_INIT)");
            appendChild(pSTAGE_WORLD->extract());
            pSTAGE_WORLD->resetTree();
            pSTAGE_WORLD->inactivateImmed();
            pSTAGE_WORLD->activate();
            pProg->change(PROG_DEMOPLAY);
            break;
        }

        case PROG_DEMOPLAY: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_DEMOPLAY)");
                pLabel01_->update(100*1000, 100*1000, "DEMOPLAY NOW");
                pLabel02_->update(100*1000, 150*1000, "GAME OVER");
                pLabel02_->setAlpha(pLabel02_->getAlphaFader()->getTop());
                pLabel02_->getAlphaFader()->beat(60, 3, 27, 3,-1);
            }

//            if (pProg->getFrame() % 60 == 0) {
//                pLabel02_->update("");
//            } else if (pProg->getFrame() % 60 == 30) {
//                pLabel02_->update("GAME OVER");
//            }


            if (pProg->hasArrivedAt(600)) {
                pProg->change(PROG_RANKING_TABLE);
            }
            break;
        }

        case PROG_RANKING_TABLE: {
            int ranking_num = G_RANKING_TABLE.getCount();
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_RANKING_TABLE)");
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
                    papLabel_ranking_[i]->getAlphaFader()->beat(25*60, 2*60, 20*60, 2*60, 1); //フェードイン・しばらくしてフェードアウト
                    papLabel_ranking_[i]->activateDelay((i+1)*12); //上から順番にぼやーっと表示していく
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
                pProg->change(PROG_FINISH);
            }
            break;
        }

        case PROG_FINISH: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_FINISH)");
            }
            if (pProg->hasArrivedAt(60*60*6)) {
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
        //throwGgafCriticalException("デモシーンのシーンが無い。あり得ないよ");
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

