#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;


#define ORDER_ID_DEMOSTAGE 12
GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameDemoScene";
    useProgress(GameDemoScene::PROG_FINISH);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(_pStringBoard02);
    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");

    _demo_stage = 1;
    _ranking_num = 10;

    int  rank[] = {1, 2, 3, 4, 5, 6,7,8,9,10};
    string name[] = {"AAAXXX", "BBBXXX", "CCCXXX", "DDDXXX", "EEEXXX", "FFFXXX", "GGGXXX", "HHHXXX", "IIIXXX","JJJXXX"};
    int  score[] = {1000000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
    string date[] = {"2011/08/01", "2011/08/02", "2011/08/03", "2011/08/04", "2011/08/05", "2011/08/06", "2011/08/07", "2011/08/08", "2011/08/09", "2011/08/10"};
    for (int i = 0; i < _ranking_num; i++) {
        ScoreInfo r = {
            rank[i],
            name[i],
            score[i],
            date[i]
        };
        ranking.push_back(r);
    }
    char buf[80];
    _papLabelRanking = NEW LabelRankingFont*[10];
    for (int i = 0; i < _ranking_num; i++) {
        _papLabelRanking[i] = NEW LabelRankingFont("RANK_INFO");
        sprintf(buf, "NO.%02d...%8s...%010d...%10s", ranking[i].rank,
                                                     ranking[i].name.c_str(),
                                                     ranking[i].score,
                                                     ranking[i].date.c_str());
        _papLabelRanking[i]->update(buf);
        _papLabelRanking[i]->inactivateImmed();
        getDirector()->addSubGroup(_papLabelRanking[i]);
    }

}
void GameDemoScene::onReset() {
    _pProg->set(GameDemoScene::PROG_INIT);
    _pStringBoard01->update("");
    _pStringBoard02->update("");
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
                _pStringBoard01->update(100*1000, 100*1000, "DEMOPLAY NOW");
                _pStringBoard02->update(100*1000, 150*1000, "GAME OVER");
                _pStringBoard02->_pFader->setAlphaToTop();
                _pStringBoard02->_pFader->beat(60,3,27,27,-1);
            }

//            if (_pProg->getFrameInProgress() % 60 == 0) {
//                _pStringBoard02->update("");
//            } else if (_pProg->getFrameInProgress() % 60 == 30) {
//                _pStringBoard02->update("GAME OVER");
//            }


            if (_pProg->getFrameInProgress() == 600) {
                _pProg->change(GameDemoScene::PROG_RANKING);
            }
            break;
        }

        case GameDemoScene::PROG_RANKING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog(=GameDemoScene::PROG_RANKING) is Just Changed");
                _pStringBoard01->update(100*1000, 100*1000, "RANKING NOW");
                for (int i = 0; i < 10; i++) {
                    _papLabelRanking[i]->locate(800*1000, 50*1000+(i*22*1000));
                    _papLabelRanking[i]->activate();
                    _papLabelRanking[i]->_pFader->setAlphaToBottom();
                    _papLabelRanking[i]->_pFader->beat(25*60, 2*60, 20*60, 1*60, 1);
                }
            }
            if (_papLabelRanking[0]->_pFader->isWorking()) {
                for (int i = 0; i < 10; i++) {
                    _papLabelRanking[i]->_pFader->behave();
                }
            } else {
                for (int i = 0; i < 10; i++) {
                    _papLabelRanking[i]->inactivate();
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
    _pStringBoard02->_pFader->behave();

}

void GameDemoScene::processFinal() {

}
void GameDemoScene::onInactive() {
    if (P_STAGE_CONTROLLER->_pStageMainCannel) {
        P_STAGE_CONTROLLER->_pStageMainCannel->end();
        P_STAGE_CONTROLLER->_pStageMainCannel = NULL;
    }
}

GameDemoScene::~GameDemoScene() {
    DELETEARR_IMPOSSIBLE_NULL(_papLabelRanking);
}
