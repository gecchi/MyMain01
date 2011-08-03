#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
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
    getDirector()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(KIND_EFFECT, _pStringBoard02);
    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");

    _demo_stage = 1;
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
            addSubLast(P_STAGE_CONTROLLER->extract());
            P_STAGE_CONTROLLER->reset();
            P_STAGE_CONTROLLER->activateImmediately();
            _pProg->change(GAMEDEMOSCENE_PROG_DEMOPLAY);

            break;
        }

        case GAMEDEMOSCENE_PROG_DEMOPLAY: {
            if (_pProg->isJustChanged()) {
                _pStringBoard01->update(100*1000, 100*1000, "DEMOPLAY NOW");
                _pStringBoard02->update(100*1000, 150*1000, "GAME OVER");
            }

            if (_pProg->getFrameInProgress() % 60 == 0) {
                _pStringBoard02->update("");
            } else if (_pProg->getFrameInProgress() % 60 == 30) {
                _pStringBoard02->update("GAME OVER");
            }


            if (_pProg->getFrameInProgress() == 180) {
                _pProg->change(GAMEDEMOSCENE_PROG_RANKING);
            }
            break;
        }

        case GAMEDEMOSCENE_PROG_RANKING: {
            if (_pProg->isJustChanged()) {
                _pStringBoard01->update(100*1000, 100*1000, "RANKING NOW");
                _pStringBoard02->update(100*1000, 150*1000, "GAME OVER");
            }
            if (_pProg->getFrameInProgress() % 60 == 0) {
                _pStringBoard02->update("");
            } else if (_pProg->getFrameInProgress() % 60 == 30) {
                _pStringBoard02->update("GAME OVER");
            }


            if (_pProg->getFrameInProgress() == 60*60) {
                _pProg->change(GAMEDEMOSCENE_PROG_FINISH);
            }
            break;
        }

        case GAMEDEMOSCENE_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                throwEventToUpperTree(EVENT_GAMEDEMOSCENE_FINISH); //終わったイベント発動
            }
            break;
        }

        default:
            break;
    }

}

void GameDemoScene::processFinal() {

}

GameDemoScene::~GameDemoScene() {
}
