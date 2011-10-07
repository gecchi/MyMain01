#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    GAMEDEMOSCENE_PROG_INIT = 1,
    GAMEDEMOSCENE_PROG_DEMOPLAY,
    GAMEDEMOSCENE_PROG_RANKING ,
    GAMEDEMOSCENE_PROG_FINISH  ,
};

#define ORDER_ID_DEMOSTAGESCENE 12
GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameDemoScene";
    useProgress(GAMEDEMOSCENE_PROG_FINISH);
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
        _papLabelRanking[i]->inactivateImmediately();
        getDirector()->addSubGroup(_papLabelRanking[i]);
    }

}
void GameDemoScene::onReset() {
    _pProg->set(GAMEDEMOSCENE_PROG_INIT);
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
        case GAMEDEMOSCENE_PROG_INIT: {
            _TRACE_("GameDemoScene::processBehavior() Prog(=GAMEDEMOSCENE_PROG_INIT) is Just Changed");
            addSubLast(P_STAGE_CONTROLLER->extract());
            P_STAGE_CONTROLLER->reset();
            P_STAGE_CONTROLLER->activateImmediately();
            _pProg->change(GAMEDEMOSCENE_PROG_DEMOPLAY);
            break;
        }

        case GAMEDEMOSCENE_PROG_DEMOPLAY: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog(=GAMEDEMOSCENE_PROG_DEMOPLAY) is Just Changed");
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
                _pProg->change(GAMEDEMOSCENE_PROG_RANKING);
            }
            break;
        }

        case GAMEDEMOSCENE_PROG_RANKING: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog(=GAMEDEMOSCENE_PROG_RANKING) is Just Changed");
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
                _pProg->change(GAMEDEMOSCENE_PROG_FINISH);
            }
            break;
        }

        case GAMEDEMOSCENE_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameDemoScene::processBehavior() Prog(=GAMEDEMOSCENE_PROG_FINISH) is Just Changed");
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

GameDemoScene::~GameDemoScene() {
    DELETEARR_IMPOSSIBLE_NULL(_papLabelRanking);
}
