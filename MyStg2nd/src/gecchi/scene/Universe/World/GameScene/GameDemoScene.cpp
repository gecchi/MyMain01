#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameDemoScene";
    useProgress(10);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard02);
    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");

}
void GameDemoScene::onReset() {
    _pPrg->set(GAMEDEMO_SCENE_PROG_INIT);
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    unblindScene();
}

void GameDemoScene::onActive() {
}

void GameDemoScene::initialize() {
}

void GameDemoScene::processBehavior() {

    switch (_pPrg->get()) {
        case GAMEDEMO_SCENE_PROG_INIT: {
            _pPrg->change(GAMEDEMO_SCENE_PROG_DEMOPLAY);
            break;
        }

        case GAMEDEMO_SCENE_PROG_DEMOPLAY: {
            if (_pPrg->isJustChanged()) {
                _pStringBoard01->update(100, 100, "DEMOPLAY NOW");
                _pStringBoard02->update(100, 150, "GAME OVER");
            }
            if (_pPrg->getFrameInProgress() == 180) {
                _pPrg->change(GAMEDEMO_SCENE_PROG_RANKING);
            }
            break;
        }

        case GAMEDEMO_SCENE_PROG_RANKING: {
            if (_pPrg->isJustChanged()) {
                _pStringBoard01->update(100, 100, "RANKING NOW");
                _pStringBoard02->update(100, 150, "GAME OVER");
            }
            if (_pPrg->getFrameInProgress() == 180) {
                _pPrg->change(GAMEDEMO_SCENE_PROG_FINISH);
            }
            break;
        }

        case GAMEDEMO_SCENE_PROG_FINISH: {
            if (_pPrg->isJustChanged()) {
                fadeoutSceneTree(FADE_FRAME);
                inactivateDelay(FADE_FRAME);
                throwEventToUpperTree(EVENT_GAMEDEMO_SCENE_FINISH); //終わったイベント発動
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
