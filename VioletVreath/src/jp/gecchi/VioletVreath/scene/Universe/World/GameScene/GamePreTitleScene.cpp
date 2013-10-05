#include "stdafx.h"
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
    useProgress(_BANPEI_-1);
    _pProg->change(GamePreTitleScene::PROG_INIT);
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
    pLabel01_->update("");
    pLabel02_->update("");
    _pProg->change(GamePreTitleScene::PROG_INIT);
//    //TEST
//    for (int i = 0; i < 9; i++) {
//        papSpriteLabel_[i]->update("ABC");
//        papSpriteLabel_[i]->position(PX_C(((i % 3) * 100) - 100), PX_C(((i / 3) * 20) - 20));
//    }
//    papSpriteLabel_[0]->setAlign(ALIGN_LEFT, VALIGN_BOTTOM);
//    papSpriteLabel_[1]->setAlign(ALIGN_CENTER, VALIGN_BOTTOM);
//    papSpriteLabel_[2]->setAlign(ALIGN_RIGHT, VALIGN_BOTTOM);
//    papSpriteLabel_[3]->setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
//    papSpriteLabel_[4]->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
//    papSpriteLabel_[5]->setAlign(ALIGN_RIGHT, VALIGN_MIDDLE);
//    papSpriteLabel_[6]->setAlign(ALIGN_LEFT, VALIGN_TOP);
//    papSpriteLabel_[7]->setAlign(ALIGN_CENTER, VALIGN_TOP);
//    papSpriteLabel_[8]->setAlign(ALIGN_RIGHT, VALIGN_TOP);
//    //TEST
}

void GamePreTitleScene::onActive() {
}

void GamePreTitleScene::initialize() {
    _TRACE_("GamePreTitleScene::initialize()");
}

void GamePreTitleScene::processBehavior() {
//    //TEST
//    if (GgafDxInput::isBeingPressedKey(DIK_Y)) {
//        for (int i = 0; i < 9; i++) {
//            papSpriteLabel_[i]->_Z -= PX_C(2);
//        }
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_U)) {
//        for (int i = 0; i < 9; i++) {
//            papSpriteLabel_[i]->_Z += PX_C(2);
//        }
//    }
//    //TEST

    switch (_pProg->get()) {
        case GamePreTitleScene::PROG_INIT: {
            _pProg->change(GamePreTitleScene::PROG_EXEC);
            break;
        }

        case GamePreTitleScene::PROG_EXEC: {
            if (_pProg->isJustChanged()) {
//                fadeinScene(FADE_FRAMES);
            }
            if (_pProg->getFrameInProgress() == 1) {
                pLabel01_->update(PX_C(100), PX_C(50), "[STORY]");
            } else if (_pProg->getFrameInProgress() == 120) {
                pLabel01_->update(PX_C(100), PX_C(50), "MUKASHI MUKASHI ARU TOKORONI.");
            } else if (_pProg->getFrameInProgress() == 240) {
                pLabel01_->update(PX_C(100), PX_C(50), "MA SORE HA OITOITE...");
            } else if (_pProg->getFrameInProgress() == 360) {
                pLabel01_->update(PX_C(100), PX_C(50), "TORIAEZU TEKI WO TAOSINI IKOUZE ! BY GECCHI");
            } else if (_pProg->getFrameInProgress() > 361) {
                //タイトルが下からニューっと
                pTitleBoard_->_Y -= PX_C(1);
                if (pTitleBoard_->_Y <= PX_C(90)) {
                    pTitleBoard_->_Y = PX_C(90);
                    _pProg->change(GamePreTitleScene::PROG_FINISH);
                }
            }
            break;
        }

        case GamePreTitleScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                throwEventUpperTree(EVENT_PREGAMETITLESCENE_FINISH);
            }
            //おしまい待ちぼうけループ
            break;
        }

        default:
            break;
     }
}

GamePreTitleScene::~GamePreTitleScene() {
}
