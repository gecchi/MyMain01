#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GameOverScene::GameOverScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameOverScene";
    pNameEntryScene_ = nullptr;
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(pLabel01_);
    useProgress(10);
    need_name_entry_ = false;
}

void GameOverScene::onReset() {
    fadeoutSceneWithBgm(0);
    pLabel01_->update("");
    pNameEntryScene_ = nullptr;
    _pProg->set(GameOverScene::PROG_INIT);
}
void GameOverScene::initialize() {
    _TRACE_("GameOverScene::initialize()");
}

void GameOverScene::processBehavior() {

//    switch (_pProg->getFromProgOnChange()) {
//        case GameOverScene::PROG_DISP: {
//            fadeoutSceneWithBgm(FADE_FRAMES);
//            inactivateDelay(FADE_FRAMES);
//            break;
//        }
//
//        default:
//            break;
//    }


    switch (_pProg->get()) {
        case GameOverScene::PROG_INIT: {
            _pProg->change(GameOverScene::PROG_DISP);
            break;
        }

        case GameOverScene::PROG_DISP: {
            if (_pProg->isJustChanged()) {
                pLabel01_->update(500*1000, 300*1000, "GAME OVER (-_-;)");
                fadeinScene(FADE_FRAMES);

                if (GameGlobal::qryRanking_.isRankIn(_SCORE_)) {
                    _TRACE_("ランクイン!!!!");
                    //ランクインのため、ネームエントリーシーン準備
                    orderSceneToFactory(ORDER_ID_NAMEENTRYSCENE, NameEntryScene, "NameEntryScene");
                    need_name_entry_ = true;
                } else {
                    _TRACE_("ランクインではない!!!!");
                    need_name_entry_ = false;
                }
            }
            if (_pProg->getFrameInProgress() == 420) {
                P_UNIVERSE->resetCamWorker();
                if (need_name_entry_) {
                    _TRACE_("_pProg->change(GameOverScene::PROG_NAMEENTRY);");
                    _pProg->change(GameOverScene::PROG_NAMEENTRY);
                } else {
                    _pProg->change(GameOverScene::PROG_FINISH);
                }
            }
            break;
        }

        case GameOverScene::PROG_NAMEENTRY: {
             if (_pProg->isJustChanged()) {
                 pNameEntryScene_ = (NameEntryScene*)obtainSceneFromFactory(ORDER_ID_NAMEENTRYSCENE);
                 addSubLast(pNameEntryScene_);
             }
             //EVENT_NAMEENTRYSCENE_FINISH イベント待ち
             break;
         }

        case GameOverScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                if (pNameEntryScene_) {
                    pNameEntryScene_->sayonara();
                }
                throwEventUpperTree(EVENT_GAMEOVERSCENE_FINISH);
            }
            break;
        }

        default:
            break;
     }
}
void GameOverScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_NAMEENTRYSCENE_FINISH) {
        //ネームエントリーシーン終了時
        _TRACE_("GameOverScene::onCatchEvent(EVENT_NAMEENTRYSCENE_FINISH)");
        _pProg->change(PROG_FINISH);
    }
}
GameOverScene::~GameOverScene() {
}
