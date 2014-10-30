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
    _DTRACE_("GameBeginningScene::onReset()");
    getProgress()->change(GameBeginningScene::PROG_INIT);
//    fadeinScene(0);
    pLabel01_->update("");
    pLabel02_->update("");
    pLabel02_->pAFader_->stop();
    pLabel02_->setAlpha(pLabel02_->pAFader_->getTop());
}
//void GameBeginningScene::ready() {
//    _DTRACE_("GameBeginningScene::ready()");
//}
void GameBeginningScene::onActive() {
}

void GameBeginningScene::initialize() {
}

void GameBeginningScene::processBehavior() {
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case GameBeginningScene::PROG_INIT: {
            pProg->change(GameBeginningScene::PROG_SELECT_MODE);
            break;
        }

        case GameBeginningScene::PROG_SELECT_MODE: {
            if (pProg->isJustChanged()) {
                pLabel01_->update(PX_C(200), PX_C(200), "GAME_BEGINNING_SCENE BEGIN");
                pLabel02_->update(PX_C(200), PX_C(250), "SELECT MODE!");
            }
            if (pProg->get() == GameBeginningScene::PROG_SELECT_MODE) {
                if (VB->isPushedDown(VB_UI_EXECUTE) || pProg->getFrameInProgress() == 300) {
                    pProg->change(GameBeginningScene::PROG_DECIDE);
                }
            }
            break;
        }

        case GameBeginningScene::PROG_DECIDE: {
            if (pProg->isJustChanged()) {
                pLabel02_->update(PX_C(300), PX_C(300), "OK OK OK");
                pLabel02_->pAFader_->beat(20, 3, 7, 3, -1);
//                fadeoutScene(FADE_FRAMES);
            }
            if (pProg->getFrameInProgress() == 20) {
                throwEventUpperTree(EVENT_GAMEMODE_DECIDE);
            }

//
//            if (pProg->getFrameInProgress() == FADE_FRAMES) {
//                pProg->change(GameBeginningScene::PROG_FINISH);
//            }
            break;
        }

        case GameBeginningScene::PROG_FINISH: {
            if (pProg->isJustChanged()) {
                //inactivate();
            }
            break;
        }

        default: {
            break;
        }
    }
    pLabel02_->pAFader_->behave();
}

GameBeginningScene::~GameBeginningScene() {
}
