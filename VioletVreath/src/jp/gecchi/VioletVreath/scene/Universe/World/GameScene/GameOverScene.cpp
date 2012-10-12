#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GameOverScene::GameOverScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameOverScene";
    pNameEntryScene_ = NULL;
    pLabel01_ = NEW LabelGecchi16Font("STR01");
    getDirector()->addSubGroup(pLabel01_);
    useProgress(10);
    need_name_entry_ = false;
}

void GameOverScene::onReset() {
    fadeoutScene(0);
    pLabel01_->update("");
    pNameEntryScene_ = NULL;
    _pProg->set(GameOverScene::PROG_INIT);
}
void GameOverScene::initialize() {
    _TRACE_("GameOverScene::initialize()");
}

void GameOverScene::processBehavior() {

//    switch (_pProg->getFromProgOnChange()) {
//        case GameOverScene::PROG_DISP: {
//            fadeoutScene(FADE_FRAMES);
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
            if (_pProg->hasJustChanged()) {
                pLabel01_->update(500*1000, 300*1000, "GAME OVER (-_-;)");
                fadeinScene(FADE_FRAMES);
                std::string str_last_score = GameGlobal::qryScoreRanking_.getVal("SCORE", GameGlobal::qryScoreRanking_.getCount()-1);  //現在のハイスコアの最低スコア
                int last_score = STOI(str_last_score);
                _TRACE_("GameGlobal::score_="<<GameGlobal::score_<<" ? last_score="<<last_score);
                if (GameGlobal::score_ > last_score) {
                    _TRACE_("HIGHSCORE!!!!");
                    //ランクインのため、ネームエントリーシーン準備
                    orderSceneToFactory(ORDER_ID_NAMEENTRYSCENE, NameEntryScene, "NameEntryScene");
                    need_name_entry_ = true;
                } else {
                    need_name_entry_ = false;
                }
            }
            if (VB->isPushedDown(VB_UI_EXECUTE) || _pProg->getFrameInProgress() == 420) {
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
             if (_pProg->hasJustChanged()) {
                 pNameEntryScene_ = (NameEntryScene*)obtainSceneFromFactory(ORDER_ID_NAMEENTRYSCENE);
                 addSubLast(pNameEntryScene_);
             }
             //EVENT_NAMEENTRYSCENE_FINISH イベント待ち
             break;
         }

        case GameOverScene::PROG_FINISH: {
            if (_pProg->hasJustChanged()) {
                if (pNameEntryScene_) {
                    pNameEntryScene_->sayonara();
                }
                throwEventToUpperTree(EVENT_GAMEOVERSCENE_FINISH);
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
