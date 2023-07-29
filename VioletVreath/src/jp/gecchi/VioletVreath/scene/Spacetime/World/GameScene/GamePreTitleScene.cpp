#include "GamePreTitleScene.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/gecchi/VioletVreath/actor/title/TitleBoard.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_EXEC   ,
    PHASE_FINISH ,
    PHASE_BANPEI,
};

GamePreTitleScene::GamePreTitleScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "GamePreTitleScene";
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getSceneChief()->appendGroupChild(pLabel01_);
    pLabel02_ = NEW LabelGecchi16Font("STR02");
    getSceneChief()->appendGroupChild(pLabel02_);
    pTitleBoard_ = NEW TitleBoard("TitleBoard4Pre");
    getSceneChief()->appendGroupChild(pTitleBoard_);

//    papSpriteLabel_ = NEW SpriteLabelTest*[9];
//    for (int i = 0; i < 9; i++) {
//        papSpriteLabel_[i] = NEW SpriteLabelTest("tst");
//        getSceneChief()->appendGroupChild(papSpriteLabel_[i]);
//    }
}
void GamePreTitleScene::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    pTitleBoard_->setPosition(PX_C(100), PX_C(600));
    pLabel01_->update(PX_C(100), PX_C(50), "");
    pLabel02_->update("");
    getPhase()->reset(PHASE_INIT);
}

void GamePreTitleScene::onActive() {
}

void GamePreTitleScene::initialize() {
    _TRACE_(FUNC_NAME<<"");
}

void GamePreTitleScene::processBehavior() {
    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_EXEC);
            break;
        }

        case PHASE_EXEC: {
            if (pPhase->hasJustChanged()) {
//                fadeinScene(FADE_FRAMES);
            }
            if (pPhase->hasArrivedFrameAt(1)) {
                pLabel01_->update("[STORY]");
            } else if (pPhase->hasArrivedFrameAt(120)) {
                pLabel01_->update("MUKASHI MUKASHI ARU TOKORONI...");
            } else if (pPhase->hasArrivedFrameAt(240)) {
                pLabel01_->update("OITOITE...");
            } else if (pPhase->hasArrivedFrameAt(360)) {
                pLabel01_->update("PRESENTED BY GECCHI.");
            } else if (pPhase->getFrame() > 361) {
                //タイトルが下からニューっと
                pTitleBoard_->_y -= PX_C(1);
                if (pTitleBoard_->_y <= PX_C(90)) {
                    pTitleBoard_->_y = PX_C(90);
                    pPhase->change(PHASE_FINISH);
                }
            }
            break;
        }

        case PHASE_FINISH: {
            if (pPhase->hasJustChanged()) {
                throwEventUpperTree(EVENT_PREGAMETITLESCENE_FINISH);
            }
            //おしまい待ちぼうけループ
            break;
        }

        default: {
            break;
        }
     }
}

GamePreTitleScene::~GamePreTitleScene() {
}
