#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

enum {
    GAMEPRETITLESCENE_PROG_INIT = 1,
    GAMEPRETITLESCENE_PROG_EXEC    ,
    GAMEPRETITLESCENE_PROG_FINISH  ,
};

GamePreTitleScene::GamePreTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GamePreTitleScene";
    useProgress(10);
    _pProg->change(GAMEPRETITLESCENE_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(_pStringBoard02);
    _pTitleBoard = NEW TitleBoard("TitleBoard");
    getDirector()->addSubGroup(_pTitleBoard);
}
void GamePreTitleScene::onReset() {
    _TRACE_("GamePreTitleScene::onReset()");
    _pTitleBoard->locate(200000, 600000);
    _pStringBoard01->update("");
    _pStringBoard02->update("");
//    fadeoutScene(0);
    _pProg->change(GAMEPRETITLESCENE_PROG_INIT);
}

void GamePreTitleScene::onActive() {
}

void GamePreTitleScene::initialize() {
    _TRACE_("GamePreTitleScene::initialize()");
}

void GamePreTitleScene::processBehavior() {

    switch (_pProg->get()) {
        case GAMEPRETITLESCENE_PROG_INIT: {
            _pProg->change(GAMEPRETITLESCENE_PROG_EXEC);
            break;
        }

        case GAMEPRETITLESCENE_PROG_EXEC: {
            if (_pProg->isJustChanged()) {
//                fadeinScene(FADE_FRAMES);
            }
            if (_pProg->getFrameInProgress() == 1) {
                _pStringBoard01->update(PX2CO(100), PX2CO(50), "[STORY]");
            } else if (_pProg->getFrameInProgress() == 120) {
                _pStringBoard01->update(PX2CO(100), PX2CO(50), "MUKASHI MUKASHI ARU TOKORONI.");
            } else if (_pProg->getFrameInProgress() == 240) {
                _pStringBoard01->update(PX2CO(100), PX2CO(50), "MA SORE HA OITOITE...");
            } else if (_pProg->getFrameInProgress() == 360) {
                _pStringBoard01->update(PX2CO(100), PX2CO(50), "TORIAEZU TEKI WO TAOSINI IKOUZE ! BY GECCHI");
            } else if (_pProg->getFrameInProgress() > 600) {
                //タイトルが下からニューっと
                _pTitleBoard->_Y -= 2*LEN_UNIT;
                if (_pTitleBoard->_Y <= 100*LEN_UNIT) {
                    _pProg->change(GAMEPRETITLESCENE_PROG_FINISH);
                }
            }
            break;
        }

        case GAMEPRETITLESCENE_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                throwEventToUpperTree(EVENT_PREGAMETITLESCENE_FINISH);
//                inactivate();
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
