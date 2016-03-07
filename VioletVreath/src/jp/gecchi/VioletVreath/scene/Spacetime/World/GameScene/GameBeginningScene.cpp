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
    bringDirector()->addSubGroup(KIND_EFFECT, pLabel01_);
    pLabel02_ = NEW LabelGecchi16Font("STR02");
    bringDirector()->addSubGroup(KIND_EFFECT, pLabel02_);
    selected_stage_ = 0;
    useProgress(PROG_BANPEI-1);
}

void GameBeginningScene::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    getProgress()->change(PROG_INIT);
//    fadeinScene(0);
    pLabel01_->update("");
    pLabel02_->update("");
    pLabel02_->pAFader_->stop();
    pLabel02_->setAlpha(pLabel02_->pAFader_->getTop());
}
//void GameBeginningScene::ready() {
//    _TRACE_(FUNC_NAME<<"");
//}
void GameBeginningScene::onActive() {
}

void GameBeginningScene::initialize() {
}

void GameBeginningScene::processBehavior() {
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_SELECT_MODE);
            break;
        }

        case PROG_SELECT_MODE: {
            if (pProg->hasJustChanged()) {
                pLabel01_->update(PX_C(200), PX_C(200), "GAME_BEGINNING_SCENE BEGIN");
                pLabel02_->update(PX_C(200), PX_C(250), "SELECT MODE!");
            }
            if (pProg->get() == PROG_SELECT_MODE) {
                if (VB->isPushedDown(VB_UI_EXECUTE) || pProg->hasArrivedAt(300)) {
                    pProg->change(PROG_DECIDE);
                }
            }
            break;
        }

        case PROG_DECIDE: {
            if (pProg->hasJustChanged()) {
                pLabel02_->update(PX_C(300), PX_C(300), "OK OK OK");
                pLabel02_->pAFader_->beat(20, 3, 7, 3, -1);
//                fadeoutScene(FADE_FRAMES);
            }
            if (pProg->hasArrivedAt(20)) {
                throwEventUpperTree(EVENT_GAMEMODE_DECIDE);
            }

//
//            if (pProg->hasArrivedAt(FADE_FRAMES)) {
//                pProg->change(PROG_FINISH);
//            }
            break;
        }

        case PROG_FINISH: {
            if (pProg->hasJustChanged()) {
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
