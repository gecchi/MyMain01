#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;
#define ORDER_ID_DEMOSTAGESCENE 12
GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameDemoScene";
    useProgress(10);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard02);
    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");

    _demo_stage = 1;
    _had_ready_demo_stage = false;
    _pSceneDemoMainCannnel = NULL;
}
//void GameDemoScene::readyDemoStage(int prm_stage) {
//    if (_had_ready_demo_stage) {
//        throwGgafCriticalException("GameMainScene::readyStage 既に準備済みのステージがあります。_demo_stage="<<_demo_stage<<" prm_stage="<<_had_ready_demo_stage);
//    }
//
//    _demo_stage = prm_stage;
//    _had_ready_demo_stage = true;
////    _frame_ready_stage = 0;
//    switch (_demo_stage) {
//        case 1:
//            orderSceneToFactory(ORDER_ID_DEMOSTAGESCENE, Stage01Scene, "Stage01");
//            break;
//        case 2:
//            orderSceneToFactory(ORDER_ID_DEMOSTAGESCENE, Stage02Scene, "Stage02");
//            break;
//        case 3:
//            orderSceneToFactory(ORDER_ID_DEMOSTAGESCENE, Stage03Scene, "Stage03");
//            break;
//        case 4:
//            orderSceneToFactory(ORDER_ID_DEMOSTAGESCENE, Stage04Scene, "Stage04");
//            break;
//        case 5:
//            orderSceneToFactory(ORDER_ID_DEMOSTAGESCENE, Stage05Scene, "Stage05");
//            break;
//        default:
//            break;
//    }
//}
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
            _pProg->change(GAMEDEMOSCENE_PROG_DEMOPLAY);
            break;
        }

        case GAMEDEMOSCENE_PROG_DEMOPLAY: {
            if (_pProg->isJustChanged()) {
//                readyDemoStage(1);
                _pStringBoard01->update(100*1000, 100*1000, "DEMOPLAY NOW");
                _pStringBoard02->update(100*1000, 150*1000, "GAME OVER");

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
            if (_pProg->getFrameInProgress() == 180) {
                _pProg->change(GAMEDEMOSCENE_PROG_FINISH);
            }
            break;
        }

        case GAMEDEMOSCENE_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
//                fadeoutSceneTree(FADE_FRAMES);
//                inactivateDelay(FADE_FRAMES);
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
