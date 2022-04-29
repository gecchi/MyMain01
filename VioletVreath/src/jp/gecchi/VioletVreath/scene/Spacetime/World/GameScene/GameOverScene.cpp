#include "GameOverScene.h"

#include "jp/gecchi/VioletVreath/actor/camera/VVCameraWorkerChanger.h"
#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameOverScene/NameEntryScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"


using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT     ,
    PHASE_DISP     ,
    PHASE_NAMEENTRY,
    PHASE_FINISH   ,
    PHASE_BANPEI,
};

GameOverScene::GameOverScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "GameOverScene";
    pNameEntryScene_ = nullptr;
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    bringSceneMediator()->appendGroupChild(pLabel01_);
    need_name_entry_ = false;
}

void GameOverScene::onReset() {
    fadeoutSceneWithBgm(0);
    pLabel01_->update("");
    pNameEntryScene_ = nullptr;
    getPhase()->reset(PHASE_INIT);
}
void GameOverScene::initialize() {
    _TRACE_(FUNC_NAME<<"");
}

void GameOverScene::processBehavior() {

//    switch (pPhase->getFromPhaseOnChange()) {
//        case PHASE_DISP: {
//            fadeoutSceneWithBgm(FADE_FRAMES);
//            inactivateDelay(FADE_FRAMES);
//            break;
//        }
//
//        default:
//            break;
//    }

    ScenePhase* pPhase = getPhase();
    switch (pPhase->get()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_DISP);
            break;
        }

        case PHASE_DISP: {
            if (pPhase->hasJustChanged()) {
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
            if (pPhase->hasArrivedFrameAt(420)) {
                pGOD->getSpacetime()->getCameraWorkerChanger()->cleanCamWorker();
                if (need_name_entry_) {
                    _TRACE_("pPhase->change(PHASE_NAMEENTRY);");
                    pPhase->change(PHASE_NAMEENTRY);
                } else {
                    pPhase->change(PHASE_FINISH);
                }
            }
            break;
        }

        case PHASE_NAMEENTRY: {
             if (pPhase->hasJustChanged()) {
                 pNameEntryScene_ = (NameEntryScene*)receiveScene(ORDER_ID_NAMEENTRYSCENE);
                 appendChild(pNameEntryScene_);
             }
             //EVENT_NAMEENTRYSCENE_FINISH イベント待ち
             break;
         }

        case PHASE_FINISH: {
            if (pPhase->hasJustChanged()) {
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
        getPhase()->change(PHASE_FINISH);
    }
}
GameOverScene::~GameOverScene() {
}
