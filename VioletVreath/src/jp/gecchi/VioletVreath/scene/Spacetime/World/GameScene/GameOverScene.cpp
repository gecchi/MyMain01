#include "GameOverScene.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameOverScene/NameEntryScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT     ,
    PROG_DISP     ,
    PROG_NAMEENTRY,
    PROG_FINISH   ,
    PROG_BANPEI,
};

GameOverScene::GameOverScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameOverScene";
    pNameEntryScene_ = nullptr;
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    bringSceneMediator()->appendGroupChild(pLabel01_);
    useProgress(PROG_BANPEI);
    need_name_entry_ = false;
}

void GameOverScene::onReset() {
    fadeoutSceneWithBgm(0);
    pLabel01_->update("");
    pNameEntryScene_ = nullptr;
    getProgress()->reset(PROG_INIT);
}
void GameOverScene::initialize() {
    _TRACE_(FUNC_NAME<<"");
}

void GameOverScene::processBehavior() {

//    switch (pProg->getFromProgOnChange()) {
//        case PROG_DISP: {
//            fadeoutSceneWithBgm(FADE_FRAMES);
//            inactivateDelay(FADE_FRAMES);
//            break;
//        }
//
//        default:
//            break;
//    }

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_DISP);
            break;
        }

        case PROG_DISP: {
            if (pProg->hasJustChanged()) {
                pLabel01_->update(500*1000, 300*1000, "GAME OVER (-_-;)");
                fadeinScene(FADE_FRAMES);

                if (G_RANKING_TABLE.isRankIn(G_SCORE)) {
                    _TRACE_("ランクイン!!!!");
                    //ランクインのため、ネームエントリーシーン準備
                    requestScene(ORDER_ID_NAMEENTRYSCENE, NameEntryScene);
                    need_name_entry_ = true;
                } else {
                    _TRACE_("ランクインではない!!!!");
                    need_name_entry_ = false;
                }
            }
            if (pProg->hasArrivedAt(420)) {
                pGOD->getSpacetime()->resetCamWorker();
                if (need_name_entry_) {
                    _TRACE_("pProg->change(PROG_NAMEENTRY);");
                    pProg->change(PROG_NAMEENTRY);
                } else {
                    pProg->change(PROG_FINISH);
                }
            }
            break;
        }

        case PROG_NAMEENTRY: {
             if (pProg->hasJustChanged()) {
                 pNameEntryScene_ = (NameEntryScene*)receiveScene(ORDER_ID_NAMEENTRYSCENE);
                 appendChild(pNameEntryScene_);
             }
             //EVENT_NAMEENTRYSCENE_FINISH イベント待ち
             break;
         }

        case PROG_FINISH: {
            if (pProg->hasJustChanged()) {
                if (pNameEntryScene_) {
                    pNameEntryScene_->sayonara();
                }
                throwEventUpperTree(EVENT_GAMEOVERSCENE_FINISH);
            }
            break;
        }

        default: {
            break;
        }
     }
}
void GameOverScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_NAMEENTRYSCENE_FINISH) {
        //ネームエントリーシーン終了時
        _TRACE_("GameOverScene::onCatchEvent(EVENT_NAMEENTRYSCENE_FINISH)");
        getProgress()->change(PROG_FINISH);
    }
}
GameOverScene::~GameOverScene() {
}
