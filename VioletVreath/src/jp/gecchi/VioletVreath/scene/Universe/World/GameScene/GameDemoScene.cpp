#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


#define ORDER_ID_DEMOSTAGE 12
GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameDemoScene";
    useProgress(GameDemoScene::PROG_FINISH);
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(pLabel01_);
    pLabel02_ = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(pLabel02_);
    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "OGG_BGM_DEMO");

    demo_stage_ = 1;

    papLabel_Ranking_ = NEW LabelRankingFont*[GameGlobal::qryRanking_.getCount()];
    for (int i = 0; i < GameGlobal::qryRanking_.getCount(); i++) {
        papLabel_Ranking_[i] = NEW LabelRankingFont("RANK_INFO");
        getDirector()->addSubGroup(papLabel_Ranking_[i]);
    }

}
void GameDemoScene::onReset() {
    _pProg->set(GameDemoScene::PROG_INIT);
    pLabel01_->update("");
    pLabel02_->update("");
    for (int i = 0; i < GameGlobal::qryRanking_.getCount(); i++) {
        papLabel_Ranking_[i]->update("");
        papLabel_Ranking_[i]->inactivateImmed();
    }
//    fadeinScene(0);
}

void GameDemoScene::onActive() {
}

void GameDemoScene::initialize() {
}

void GameDemoScene::processBehavior() {

    switch (_pProg->get()) {
        case GameDemoScene::PROG_INIT: {
            _TRACE_("GameDemoScene::processBehavior() Prog has Just Changed (to GameDemoScene::PROG_INIT)");
            addSubLast(P_STAGE_WORLD->extract());
            P_STAGE_WORLD->reset();
            P_STAGE_WORLD->activateImmed();
            _pProg->change(GameDemoScene::PROG_DEMOPLAY);
            break;
        }

        case GameDemoScene::PROG_DEMOPLAY: {
            if (_pProg->hasJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog has Just Changed (to GameDemoScene::PROG_DEMOPLAY)");
                pLabel01_->update(100*1000, 100*1000, "DEMOPLAY NOW");
                pLabel02_->update(100*1000, 150*1000, "GAME OVER");
                pLabel02_->_pFader->setAlphaToTop();
                pLabel02_->_pFader->beat(60,3,27,27,-1);
            }

//            if (_pProg->getFrameInProgress() % 60 == 0) {
//                pLabel02_->update("");
//            } else if (_pProg->getFrameInProgress() % 60 == 30) {
//                pLabel02_->update("GAME OVER");
//            }


            if (_pProg->getFrameInProgress() == 600) {
                _pProg->change(GameDemoScene::PROG_RANKING);
            }
            break;
        }

        case GameDemoScene::PROG_RANKING: {
            int ranking_num = GameGlobal::qryRanking_.getCount();
            if (_pProg->hasJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog has Just Changed (to GameDemoScene::PROG_RANKING)");
                pLabel01_->update(PX_C(100), PX_C(100), "RANKING NOW");
                char buf[60];
                for (int i = 0; i < ranking_num; i++) {
                    sprintf(buf, "NO.%02d  %-12s  %10s  %s",
                            i+1,
                            GameGlobal::qryRanking_.getVal("NAME"   , i).c_str(),
                            GameGlobal::qryRanking_.getVal("SCORE"  , i).c_str(),
                            GameGlobal::qryRanking_.getVal("REGDATE", i).c_str());
                    papLabel_Ranking_[i]->update(buf);
                    papLabel_Ranking_[i]->locate(PX_C(400), PX_C(50+(i*22)));
                    papLabel_Ranking_[i]->_pFader->setAlphaToBottom();
                    papLabel_Ranking_[i]->_pFader->beat(25*60, 2*60, 20*60, 1*60, 1); //フェードイン・しばらくしてフェードアウト
                    papLabel_Ranking_[i]->activateDelay((i+1)*12); //上から順番にぼやーっと表示していく
                }
            }

            if (papLabel_Ranking_[ranking_num-1]->_pFader->isWorking()) {
                //一番最後のFaderがまだ動いてるならば
                for (int i = 0; i < ranking_num; i++) {
                    if (papLabel_Ranking_[i]->isActive()) {
                        papLabel_Ranking_[i]->_pFader->behave();
                    }
                }
            } else {
                //一番最後のFaderが動いてない＝表示終了
                for (int i = 0; i < ranking_num; i++) {
                    papLabel_Ranking_[i]->inactivate();
                }
                _pProg->change(GameDemoScene::PROG_FINISH);
            }
            break;
        }

        case GameDemoScene::PROG_FINISH: {
            if (_pProg->hasJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog has Just Changed (to GameDemoScene::PROG_FINISH)");
            }
            if (_pProg->getFrameInProgress() == 600) {
                _TRACE_("GameDemoScene::processBehavior() throwEventUpperTree(EVENT_GAMEDEMOSCENE_FINISH)");
                throwEventUpperTree(EVENT_GAMEDEMOSCENE_FINISH); //終わったイベント発動
            }

            break;
        }

        default:
            break;
    }
    pLabel02_->_pFader->behave();

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
}

GameDemoScene::~GameDemoScene() {
    DELETEARR_IMPOSSIBLE_NULL(papLabel_Ranking_);
}
