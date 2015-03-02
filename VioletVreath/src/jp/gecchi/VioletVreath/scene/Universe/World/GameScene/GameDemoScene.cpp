#include "GameDemoScene.h"

#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include <stdio.h>
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


#define ORDER_ID_DEMOSTAGE 12
GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameDemoScene";
    useProgress(GameDemoScene::PROG_BANPEI-1);
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getSceneDirector()->addSubGroup(pLabel01_);
    pLabel02_ = NEW LabelGecchi16Font("STR02");
    getSceneDirector()->addSubGroup(pLabel02_);
    demo_stage_ = 1;

    papLabel_ranking_ = NEW LabelRankingFont*[G_RANKING_TABLE.getCount()];
    int cnt = (int)(G_RANKING_TABLE.getCount());
    for (int i = 0; i < cnt; i++) {
        papLabel_ranking_[i] = NEW LabelRankingFont("RANK_INFO");
        getSceneDirector()->addSubGroup(papLabel_ranking_[i]);
    }

}
void GameDemoScene::onReset() {
    getProgress()->reset(GameDemoScene::PROG_INIT);
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
        case GameDemoScene::PROG_INIT: {
            _TRACE_("GameDemoScene::processBehavior() Prog has Just Changed (to GameDemoScene::PROG_INIT)");
            addSubLast(P_STAGE_WORLD->extract());
            P_STAGE_WORLD->resetTree();
            P_STAGE_WORLD->inactivateImmed();
            P_STAGE_WORLD->activate();
            pProg->change(GameDemoScene::PROG_DEMOPLAY);
            break;
        }

        case GameDemoScene::PROG_DEMOPLAY: {
            if (pProg->isJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog has Just Changed (to GameDemoScene::PROG_DEMOPLAY)");
                pLabel01_->update(100*1000, 100*1000, "DEMOPLAY NOW");
                pLabel02_->update(100*1000, 150*1000, "GAME OVER");
                pLabel02_->setAlpha(pLabel02_->pAFader_->getTop());
                pLabel02_->pAFader_->beat(60, 3, 27, 3,-1);
            }

//            if (pProg->getFrame() % 60 == 0) {
//                pLabel02_->update("");
//            } else if (pProg->getFrame() % 60 == 30) {
//                pLabel02_->update("GAME OVER");
//            }


            if (pProg->arriveAt(600)) {
                pProg->change(GameDemoScene::PROG_RANKING_TABLE);
            }
            break;
        }

        case GameDemoScene::PROG_RANKING_TABLE: {
            int ranking_num = G_RANKING_TABLE.getCount();
            if (pProg->isJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog has Just Changed (to GameDemoScene::PROG_RANKING_TABLE)");
                pLabel01_->update(PX_C(100), PX_C(100), "RANKING NOW");
                char buf[60];
                for (int i = 0; i < ranking_num; i++) {
                    sprintf(buf, "NO.%02d  %-12s  %10s  %s",
                            i+1,
                            G_RANKING_TABLE.getVal("NAME"   , i).c_str(),
                            G_RANKING_TABLE.getVal("SCORE"  , i).c_str(),
                            G_RANKING_TABLE.getVal("REGDATE", i).c_str());
                    papLabel_ranking_[i]->update(buf);
                    papLabel_ranking_[i]->position(PX_C(400), PX_C(50+(i*22)));
                    papLabel_ranking_[i]->setAlpha(papLabel_ranking_[i]->pAFader_->getBottom());
                    papLabel_ranking_[i]->pAFader_->beat(25*60, 2*60, 20*60, 2*60, 1); //フェードイン・しばらくしてフェードアウト
                    papLabel_ranking_[i]->activateDelay((i+1)*12); //上から順番にぼやーっと表示していく
                }
            }

            if (papLabel_ranking_[ranking_num-1]->pAFader_->isTransitioning()) {
                //一番最後のFaderがまだ動いてるならば
                for (int i = 0; i < ranking_num; i++) {
                    if (papLabel_ranking_[i]->isActive()) {
                        papLabel_ranking_[i]->pAFader_->behave();
                    }
                }
            } else {
                //一番最後のFaderが動いてない＝表示終了
                for (int i = 0; i < ranking_num; i++) {
                    papLabel_ranking_[i]->inactivate();
                }
                pProg->change(GameDemoScene::PROG_FINISH);
            }
            break;
        }

        case GameDemoScene::PROG_FINISH: {
            if (pProg->isJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog has Just Changed (to GameDemoScene::PROG_FINISH)");
            }
            if (pProg->arriveAt(600)) {
                _TRACE_("GameDemoScene::processBehavior() throwEventUpperTree(EVENT_GAMEDEMOSCENE_FINISH)");
                throwEventUpperTree(EVENT_GAMEDEMOSCENE_FINISH); //終わったイベント発動
            }

            break;
        }

        default: {
            break;
        }
    }
    pLabel02_->pAFader_->behave();
}

void GameDemoScene::onInactive() {
    _TRACE_("GameDemoScene::onInactive() ");
    if (P_STAGE_CTRLER->pStageMainCannel_) {
        _TRACE_("GameDemoScene::onInactive() P_STAGE_CTRLER->pStageMainCanne_("<<
                P_STAGE_CTRLER->pStageMainCannel_->getName()<<") sayonara()");
        P_STAGE_CTRLER->pStageMainCannel_->sayonara();
        P_STAGE_CTRLER->pStageMainCannel_ = nullptr;
    } else {
        //throwGgafCriticalException("GameDemoScene::onInactive() デモシーンのシーンが無い。あり得ないよ");
    }

    if (P_RANKUP_CONTROLLER->pNowRankUpStage_) {
        _TRACE_("GameDemoScene::onInactive() P_RANKUP_CONTROLLER->sayonaraRankUpStages()");
        P_RANKUP_CONTROLLER->sayonaraRankUpStages();
        P_RANKUP_CONTROLLER->pNowRankUpStage_ = nullptr;
    }
}

GameDemoScene::~GameDemoScene() {
    GGAF_DELETEARR(papLabel_ranking_);
}

