#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

GamePreTitleScene::GamePreTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GamePreTitleScene";
    useProgress(10);
    _pProg->change(GamePreTitleScene::PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getDirector()->addSubGroup(_pStringBoard02);
    _pTitleBoard = NEW TitleBoard("TitleBoard");
    getDirector()->addSubGroup(_pTitleBoard);
}
void GamePreTitleScene::onReset() {
    _TRACE_("GamePreTitleScene::onReset()");
    _pTitleBoard->locate(PX2CO(100), PX2CO(600));
    _pStringBoard01->update("");
    _pStringBoard02->update("");
//    fadeoutScene(0);
    _pProg->change(GamePreTitleScene::PROG_INIT);
}

void GamePreTitleScene::onActive() {
}

void GamePreTitleScene::initialize() {
    _TRACE_("GamePreTitleScene::initialize()");
}

void GamePreTitleScene::processBehavior() {

    switch (_pProg->get()) {
        case GamePreTitleScene::PROG_INIT: {
            _pProg->change(GamePreTitleScene::PROG_EXEC);
            break;
        }

        case GamePreTitleScene::PROG_EXEC: {
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
            } else if (_pProg->getFrameInProgress() > 361) {
                //タイトルが下からニューっと
                _pTitleBoard->_Y -= PX2CO(1);
                if (_pTitleBoard->_Y <= PX2CO(90)) {
                    _pTitleBoard->_Y = PX2CO(90);
                    _pProg->change(GamePreTitleScene::PROG_FINISH);
                }
            }
            break;
        }

        case GamePreTitleScene::PROG_FINISH: {
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
