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
    _pBgmPerformer->set(0, "BGM_DEMO");

    demo_stage_ = 1;
    ranking_num_ = 10;

    int  rank[] = {1, 2, 3, 4, 5, 6,7,8,9,10};
    std::string name[] = {"AAAXXX", "BBBXXX", "CCCXXX", "DDDXXX", "EEEXXX", "FFFXXX", "GGGXXX", "HHHXXX", "IIIXXX","JJJXXX"};
    int  score[] = {1000000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
    std::string date[] = {"2011/08/01", "2011/08/02", "2011/08/03", "2011/08/04", "2011/08/05", "2011/08/06", "2011/08/07", "2011/08/08", "2011/08/09", "2011/08/10"};
    for (int i = 0; i < ranking_num_; i++) {
        ScoreInfo r = {
            rank[i],
            name[i],
            score[i],
            date[i]
        };
        ranking.push_back(r);
    }
    char buf[80];
    papLabel_Ranking_ = NEW LabelRankingFont*[10];
    for (int i = 0; i < ranking_num_; i++) {
        papLabel_Ranking_[i] = NEW LabelRankingFont("RANK_INFO");
        sprintf(buf, "NO.%02d...%8s...%010d...%10s", ranking[i].rank,
                                                     ranking[i].name.c_str(),
                                                     ranking[i].score,
                                                     ranking[i].date.c_str());
        papLabel_Ranking_[i]->update(buf);
        papLabel_Ranking_[i]->inactivateImmed();
        getDirector()->addSubGroup(papLabel_Ranking_[i]);
    }

}
void GameDemoScene::onReset() {
    _pProg->set(GameDemoScene::PROG_INIT);
    pLabel01_->update("");
    pLabel02_->update("");
//    fadeinScene(0);
}

void GameDemoScene::onActive() {
}

void GameDemoScene::initialize() {
}

void GameDemoScene::processBehavior() {

    switch (_pProg->get()) {
        case GameDemoScene::PROG_INIT: {
            _TRACE_("GameDemoScene::processBehavior() Prog(=GameDemoScene::PROG_INIT) is Just Changed");
            addSubLast(P_STAGE_WORLD->extract());
            P_STAGE_WORLD->reset();
            P_STAGE_WORLD->activateImmed();
            _pProg->change(GameDemoScene::PROG_DEMOPLAY);
            break;
        }

        case GameDemoScene::PROG_DEMOPLAY: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog(=GameDemoScene::PROG_DEMOPLAY) is Just Changed");
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
            if (_pProg->isJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog(=GameDemoScene::PROG_RANKING) is Just Changed");
                pLabel01_->update(100*1000, 100*1000, "RANKING NOW");
                for (int i = 0; i < 10; i++) {
                    papLabel_Ranking_[i]->locate(400*1000, 50*1000+(i*22*1000));
                    papLabel_Ranking_[i]->activate();
                    papLabel_Ranking_[i]->_pFader->setAlphaToBottom();
                    papLabel_Ranking_[i]->_pFader->beat(25*60, 2*60, 20*60, 1*60, 1);
                }
            }
            if (papLabel_Ranking_[0]->_pFader->isWorking()) {
                for (int i = 0; i < 10; i++) {
                    papLabel_Ranking_[i]->_pFader->behave();
                }
            } else {
                for (int i = 0; i < 10; i++) {
                    papLabel_Ranking_[i]->inactivate();
                }
                _pProg->change(GameDemoScene::PROG_FINISH);
            }
            break;
        }

        case GameDemoScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog(=GameDemoScene::PROG_FINISH) is Just Changed");
            }
            if (_pProg->getFrameInProgress() == 600) {
                throwEventToUpperTree(EVENT_GAMEDEMOSCENE_FINISH); //終わったイベント発動
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
                P_STAGE_CTRLER->pStageMainCannel_->getName()<<") をend()");
        P_STAGE_CTRLER->pStageMainCannel_->end();
        P_STAGE_CTRLER->pStageMainCannel_ = NULL;
    } else {
        //throwGgafCriticalException("GameDemoScene::onInactive() デモシーンのシーンが無い。あり得ないよ");
    }
}

GameDemoScene::~GameDemoScene() {
    DELETEARR_IMPOSSIBLE_NULL(papLabel_Ranking_);
}
