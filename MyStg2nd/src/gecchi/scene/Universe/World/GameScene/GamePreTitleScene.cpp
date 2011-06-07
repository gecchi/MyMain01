#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GamePreTitleScene::GamePreTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GamePreTitleScene";
    useProgress(10);
    _pPrg->change(GAMEDEMO_SCENE_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(_pStringBoard02);
    _pTitleBoard = NEW TitleBoard("TitleBoard");
    getLordActor()->addSubGroup(_pTitleBoard);
}
void GamePreTitleScene::onReset() {
    _TRACE_("GamePreTitleScene::onReset()");
    _pTitleBoard->locate(200000, 600000);
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    blindScene();
    _pPrg->change(GAMEPRETITLE_SCENE_PROG_INIT);
}

void GamePreTitleScene::onActive() {
}

void GamePreTitleScene::initialize() {
    _TRACE_("GamePreTitleScene::initialize()");
}

void GamePreTitleScene::processBehavior() {

    switch (_pPrg->get()) {
        case GAMEPRETITLE_SCENE_PROG_INIT: {
            _pPrg->change(GAMEPRETITLE_SCENE_PROG_EXEC);
            break;
        }

        case GAMEPRETITLE_SCENE_PROG_EXEC: {
            if (_pPrg->isJustChanged()) {
                fadeinScene(FADE_FRAME);
            }
            if (_pPrg->getFrameInProgress() == 1) {
                _pStringBoard01->update(100*1000, 50*1000, "[STORY]");
            } else if (_pPrg->getFrameInProgress() == 120) {
                _pStringBoard01->update(100*1000, 50*1000, "MUKASHI MUKASHI ARU TOKORONI.");
            } else if (_pPrg->getFrameInProgress() == 240) {
                _pStringBoard01->update(100*1000, 50*1000, "MA SORE HA OITOITE...");
            } else if (_pPrg->getFrameInProgress() == 360) {
                _pStringBoard01->update(100*1000, 50*1000, "TORIAEZU TEKI WO TAOSINI IKOUZE ! BY GECCHI");
            } else if (_pPrg->getFrameInProgress() > 600) {
                //タイトルが下からニューっと
                _pTitleBoard->_Y -= 2*LEN_UNIT;
                if (_pTitleBoard->_Y <= 150*LEN_UNIT) {
                    throwEventToUpperTree(EVENT_PREGAMETITLE_SCENE_FINISH);
                    _pPrg->change(GAMEPRETITLE_SCENE_PROG_FINISH);
                }
            }
            break;
        }

        case GAMEPRETITLE_SCENE_PROG_FINISH: {
            if (_pPrg->isJustChanged()) {
                inactivate();
            }
            //おしまい待ちぼうけループ
            break;
        }

        default:
            break;
     }
}

void GamePreTitleScene::processFinal() {

}

GamePreTitleScene::~GamePreTitleScene() {
}
