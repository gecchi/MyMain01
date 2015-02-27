#include "GamePreTitleScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/gecchi/VioletVreath/actor/title/TitleBoard.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GamePreTitleScene::GamePreTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GamePreTitleScene";
    useProgress(PROG_BANPEI);
    getProgress()->change(GamePreTitleScene::PROG_INIT);
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getSceneDirector()->addSubGroup(pLabel01_);
    pLabel02_ = NEW LabelGecchi16Font("STR02");
    getSceneDirector()->addSubGroup(pLabel02_);
    pTitleBoard_ = NEW TitleBoard("TitleBoard4Pre");
    getSceneDirector()->addSubGroup(pTitleBoard_);

//    papSpriteLabel_ = NEW SpriteLabelTest*[9];
//    for (int i = 0; i < 9; i++) {
//        papSpriteLabel_[i] = NEW SpriteLabelTest("tst");
//        getSceneDirector()->addSubGroup(papSpriteLabel_[i]);
//    }
}
void GamePreTitleScene::onReset() {
    _TRACE_("GamePreTitleScene::onReset()");
    pTitleBoard_->position(PX_C(100), PX_C(600));
    pLabel01_->update(PX_C(100), PX_C(50), "");
    pLabel02_->update("");
    getProgress()->reset(PROG_INIT);
}

void GamePreTitleScene::onActive() {
}

void GamePreTitleScene::initialize() {
    _TRACE_("GamePreTitleScene::initialize()");
}

void GamePreTitleScene::processBehavior() {
    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_EXEC);
            break;
        }

        case PROG_EXEC: {
            if (pProg->isJustChanged()) {
//                fadeinScene(FADE_FRAMES);
            }
            if (pProg->arriveAtFrameOf(1)) {
                pLabel01_->update("[STORY]");
            } else if (pProg->arriveAtFrameOf(120)) {
                pLabel01_->update("MUKASHI MUKASHI ARU TOKORONI...");
            } else if (pProg->arriveAtFrameOf(240)) {
                pLabel01_->update("OITOITE...");
            } else if (pProg->arriveAtFrameOf(360)) {
                pLabel01_->update("PRESENTED BY GECCHI.");
            } else if (pProg->getFrame() > 361) {
                //タイトルが下からニューっと
                pTitleBoard_->_y -= PX_C(1);
                if (pTitleBoard_->_y <= PX_C(90)) {
                    pTitleBoard_->_y = PX_C(90);
                    pProg->change(PROG_FINISH);
                }
            }
            break;
        }

        case PROG_FINISH: {
            if (pProg->isJustChanged()) {
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
