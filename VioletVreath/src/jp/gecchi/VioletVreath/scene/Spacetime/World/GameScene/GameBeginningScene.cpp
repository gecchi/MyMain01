#include "GameBeginningScene.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT       ,
    PHASE_SELECT_MODE,
    PHASE_DECIDE     ,
    PHASE_FINISH     ,
    PHASE_BANPEI,
};

GameBeginningScene::GameBeginningScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "GameBeginningScene";

    pLabel01_ = NEW LabelGecchi16Font("STR01");
    bringSceneMediator()->appendGroupChild(KIND_EFFECT, pLabel01_);
    pLabel02_ = NEW LabelGecchi16Font("STR02");
    bringSceneMediator()->appendGroupChild(KIND_EFFECT, pLabel02_);
    selected_stage_ = 0;
}

void GameBeginningScene::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    getPhase()->change(PHASE_INIT);
//    fadeinScene(0);
    pLabel01_->update("");
    pLabel02_->update("");
    pLabel02_->getAlphaFader()->stop();
    pLabel02_->setAlpha(pLabel02_->getAlphaFader()->getTop());
}
//void GameBeginningScene::ready() {
//    _TRACE_(FUNC_NAME<<"");
//}
void GameBeginningScene::onActive() {
}

void GameBeginningScene::initialize() {
}

void GameBeginningScene::processBehavior() {
    ScenePhase* pPhase = getPhase();
    switch (pPhase->get()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_SELECT_MODE);
            break;
        }

        case PHASE_SELECT_MODE: {
            if (pPhase->hasJustChanged()) {
                pLabel01_->update(PX_C(200), PX_C(200), "GAME_BEGINNING_SCENE BEGIN");
                pLabel02_->update(PX_C(200), PX_C(250), "SELECT MODE!");
            }
            if (pPhase->get() == PHASE_SELECT_MODE) {
                if (VB->isPushedDown(VB_UI_EXECUTE) || pPhase->hasArrivedFrameAt(300)) {
                    pPhase->change(PHASE_DECIDE);
                }
            }
            break;
        }

        case PHASE_DECIDE: {
            if (pPhase->hasJustChanged()) {
                pLabel02_->update(PX_C(300), PX_C(300), "OK OK OK");
                pLabel02_->getAlphaFader()->beat(20, 3, 7, 3, -1);
//                fadeoutScene(FADE_FRAMES);
            }
            if (pPhase->hasArrivedFrameAt(20)) {
                throwEventUpperTree(EVENT_GAMEMODE_DECIDE);
            }

//
//            if (pPhase->hasArrivedFrameAt(FADE_FRAMES)) {
//                pPhase->change(PHASE_FINISH);
//            }
            break;
        }

        case PHASE_FINISH: {
            if (pPhase->hasJustChanged()) {
                //inactivate();
            }
            break;
        }

        default: {
            break;
        }
    }
    pLabel02_->getAlphaFader()->behave();
}

GameBeginningScene::~GameBeginningScene() {
}
