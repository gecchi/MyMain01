#include "stdafx.h"
#include "GameMainScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/scene/GgafScene.h"
#include <stdio.h>
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define ORDER_ID_STAGE 11

//GameMainScene* GameMainScene::pGameMainScene_ = nullptr;

GameMainScene::GameMainScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameMainScene";

    pLabel_SCORE_ = NEW LabelGecchi16Font("SCORE");
    pLabel_SCORE_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pLabel_SCORE_->locate(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(1));
    getSceneDirector()->addSubGroup(pLabel_SCORE_);

    pLabel_RANK_ = NEW LabelGecchi16Font("RANK");
    pLabel_RANK_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pLabel_RANK_->locate(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(20));
    getSceneDirector()->addSubGroup(pLabel_RANK_);

    pLabel_STAMINA_ = NEW LabelGecchi16Font("STAMINA");
    pLabel_STAMINA_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pLabel_STAMINA_->locate(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(40));
    getSceneDirector()->addSubGroup(pLabel_STAMINA_);

    pLabel_JIKI_X_ = NEW LabelGecchi8Font("JIKI_X");
    pLabel_JIKI_Y_ = NEW LabelGecchi8Font("JIKI_Y");
    pLabel_JIKI_Z_ = NEW LabelGecchi8Font("JIKI_Z");
    pLabel_JIKI_X_->locate(PX_C(1), PX_C(PROPERTY::GAME_BUFFER_HEIGHT - 8*3-1));
    pLabel_JIKI_Y_->locate(PX_C(1), PX_C(PROPERTY::GAME_BUFFER_HEIGHT - 8*2-1));
    pLabel_JIKI_Z_->locate(PX_C(1), PX_C(PROPERTY::GAME_BUFFER_HEIGHT - 8*1-1));
    getSceneDirector()->addSubGroup(pLabel_JIKI_X_);
    getSceneDirector()->addSubGroup(pLabel_JIKI_Y_);
    getSceneDirector()->addSubGroup(pLabel_JIKI_Z_);

    pRankFont_ = NEW LabelRankFont("RankFont"); //LabelRankFont‚Í ALIGN_RIGHT,VALIGN_BOTTOM ŒÅ’è
    pRankFont_->locate(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(PROPERTY::GAME_BUFFER_HEIGHT));
    getSceneDirector()->addSubGroup(pRankFont_);

    useProgress(GameMainScene::PROG_FINISH);
}

void GameMainScene::onReset() {
    _TRACE_("GameMainScene::onReset()");
    _pProg->reset(GameMainScene::PROG_INIT);
}

void GameMainScene::initialize() {
}

void GameMainScene::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    //SCORE•\Ž¦
    sprintf(buf_, "SCORE %07u", _SCORE_);
    pLabel_SCORE_->update(buf_);
    sprintf(buf_, "RANK %.7f", _RANK_);
    pLabel_RANK_->update(buf_);
    sprintf(buf_, "STAMINA %7d", pMyShip->_pStatus->get(STAT_Stamina));
    pLabel_STAMINA_->update(buf_);

    sprintf(buf_, "X:%8d", pMyShip->_X);
    pLabel_JIKI_X_->update(buf_);
    sprintf(buf_, "Y:%8d", pMyShip->_Y);
    pLabel_JIKI_Y_->update(buf_);
    sprintf(buf_, "Z:%8d", pMyShip->_Z);
    pLabel_JIKI_Z_->update(buf_);

    switch (_pProg->get()) {
        case GameMainScene::PROG_INIT: {
            _TRACE_("GameMainScene::processBehavior() Prog is GameMainScene::PROG_INIT");
            addSubLast(P_STAGE_WORLD->extract());
            P_STAGE_WORLD->resetTree();
            P_STAGE_WORLD->activateImmed();
            _pProg->change(GameMainScene::PROG_BEGIN);
            break;
        }

        case GameMainScene::PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog has Just Changed (to GameMainScene::PROG_BEGIN)");
                _pProg->change(GameMainScene::PROG_PLAY);
            }
            break;
        }

        case GameMainScene::PROG_PLAY: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog has Just Changed (to GameMainScene::PROG_PLAY)");
            }
            break;
        }

        case GameMainScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog has Just Changed (to GameMainScene::PROG_FINISH)");
            }
            break;
        }

        default:
            break;
    }

}

void GameMainScene::onInactive() {
    if (P_STAGE_CTRLER->pStageMainCannel_) {
        P_STAGE_CTRLER->pStageMainCannel_->sayonara();
        P_STAGE_CTRLER->pStageMainCannel_ = nullptr;
    }
}


void GameMainScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

GameMainScene::~GameMainScene() {
}

