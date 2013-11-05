#include "stdafx.h"
#include "GameBeginningScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


GameBeginningScene::GameBeginningScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameBeginningScene";

    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getSceneDirector()->addSubGroup(KIND_EFFECT, pLabel01_);
    pLabel02_ = NEW LabelGecchi16Font("STR02");
    getSceneDirector()->addSubGroup(KIND_EFFECT, pLabel02_);
    selected_stage_ = 0;
    useProgress(GameBeginningScene::PROG_BANPEI-1);
}

void GameBeginningScene::onReset() {
    _TRACE_("GameBeginningScene::onReset()");
    _pProg->change(GameBeginningScene::PROG_INIT);
//    fadeinScene(0);
    pLabel01_->update("");
    pLabel02_->update("");
    pLabel02_->_pAFader->stopImmed();
    pLabel02_->_pAFader->setToTop();
}
//void GameBeginningScene::ready() {
//    _TRACE_("GameBeginningScene::ready()");
//}
void GameBeginningScene::onActive() {
}

void GameBeginningScene::initialize() {
}

void GameBeginningScene::processBehavior() {

    switch (_pProg->get()) {
        case GameBeginningScene::PROG_INIT: {
            _pProg->change(GameBeginningScene::PROG_SELECT_MODE);
            break;
        }

        case GameBeginningScene::PROG_SELECT_MODE: {
            if (_pProg->isJustChanged()) {
                pLabel01_->update(PX_C(200), PX_C(200), "GAME_BEGINNING_SCENE BEGIN");
                pLabel02_->update(PX_C(200), PX_C(250), "SELECT MODE!");
            }
            if (_pProg->get() == GameBeginningScene::PROG_SELECT_MODE) {
                if (VB->isPushedDown(VB_UI_EXECUTE) || _pProg->getFrameInProgress() == 300) {
                    _pProg->change(GameBeginningScene::PROG_DECIDE);
                }
            }
            break;
        }

        case GameBeginningScene::PROG_DECIDE: {
            if (_pProg->isJustChanged()) {
                pLabel02_->update(PX_C(300), PX_C(300), "OK OK OK");
                pLabel02_->_pAFader->beat(20,3,7,3,-1);
//                fadeoutScene(FADE_FRAMES);
            }
            if (_pProg->getFrameInProgress() == 20) {
                throwEventUpperTree(EVENT_GAMEMODE_DECIDE);
            }

//
//            if (_pProg->getFrameInProgress() == FADE_FRAMES) {
//                _pProg->change(GameBeginningScene::PROG_FINISH);
//            }
            break;
        }

        case GameBeginningScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                //inactivate();
            }
            break;
        }

        default:
            break;
    }
    pLabel02_->_pAFader->behave();
}

GameBeginningScene::~GameBeginningScene() {
}
