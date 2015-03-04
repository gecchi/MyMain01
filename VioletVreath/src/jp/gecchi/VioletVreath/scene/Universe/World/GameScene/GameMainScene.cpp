#include "GameMainScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/scene/GgafScene.h"
#include <stdio.h>
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelScoreFont.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define ORDER_ID_STAGE 11

//GameMainScene* GameMainScene::pGameMainScene_ = nullptr;

GameMainScene::GameMainScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameMainScene";

    pLabel_SCORE_ = NEW LabelScoreFont("SCORE");
    pLabel_SCORE_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pLabel_SCORE_->position(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(1));
    getSceneDirector()->addSubGroup(pLabel_SCORE_);

    pLabel_RANK_ = NEW LabelGecchi16Font("RANK");
    pLabel_RANK_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pLabel_RANK_->position(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(30));
    getSceneDirector()->addSubGroup(pLabel_RANK_);

    pLabel_STAMINA_ = NEW LabelGecchi16Font("STAMINA");
    pLabel_STAMINA_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pLabel_STAMINA_->position(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(50));
    getSceneDirector()->addSubGroup(pLabel_STAMINA_);

    pLabel_JIKI_x_ = NEW LabelGecchi8Font("JIKI_x");
    pLabel_JIKI_y_ = NEW LabelGecchi8Font("JIKI_y");
    pLabel_JIKI_z_ = NEW LabelGecchi8Font("JIKI_z");
    pLabel_JIKI_x_->position(PX_C(1), PX_C(PROPERTY::GAME_BUFFER_HEIGHT - 8*3-1));
    pLabel_JIKI_y_->position(PX_C(1), PX_C(PROPERTY::GAME_BUFFER_HEIGHT - 8*2-1));
    pLabel_JIKI_z_->position(PX_C(1), PX_C(PROPERTY::GAME_BUFFER_HEIGHT - 8*1-1));
    getSceneDirector()->addSubGroup(pLabel_JIKI_x_);
    getSceneDirector()->addSubGroup(pLabel_JIKI_y_);
    getSceneDirector()->addSubGroup(pLabel_JIKI_z_);

    pRankFont_ = NEW LabelRankFont("RankFont"); //LabelRankFont‚Í ALIGN_RIGHT,VALIGN_BOTTOM ŒÅ’è
    pRankFont_->position(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(PROPERTY::GAME_BUFFER_HEIGHT));
    getSceneDirector()->addSubGroup(pRankFont_);

    useProgress(GameMainScene::PROG_BANPEI-1);
}

void GameMainScene::onReset() {
    _TRACE_("GameMainScene::onReset() "<<NODE_INFO<<"");
    getProgress()->reset(GameMainScene::PROG_INIT);
}

void GameMainScene::initialize() {
}

void GameMainScene::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    //SCORE•\Ž¦
    //sprintf(buf_, "SCORE %07u", G_SCORE);
    sprintf(buf_, "%07u", G_SCORE);
    pLabel_SCORE_->update(buf_);
    sprintf(buf_, "RANK %.7f", G_RANK);
    pLabel_RANK_->update(buf_);
    sprintf(buf_, "STAMINA %7d", pMyShip->getStatus()->get(STAT_Stamina));
    pLabel_STAMINA_->update(buf_);

    sprintf(buf_, "X:%8d", pMyShip->_x);
    pLabel_JIKI_x_->update(buf_);
    sprintf(buf_, "Y:%8d", pMyShip->_y);
    pLabel_JIKI_y_->update(buf_);
    sprintf(buf_, "Z:%8d", pMyShip->_z);
    pLabel_JIKI_z_->update(buf_);

    SceneProgress* pProg = getProgress();
    switch (pProg->get()) {
        case GameMainScene::PROG_INIT: {
            _TRACE_("GameMainScene::processBehavior() Prog is GameMainScene::PROG_INIT");
            addSubLast(P_STAGE_WORLD->extract());
            P_STAGE_WORLD->resetTree();
            P_STAGE_WORLD->inactivateImmed();
            P_STAGE_WORLD->activate();
            pProg->change(GameMainScene::PROG_BEGIN);
            break;
        }

        case GameMainScene::PROG_BEGIN: {
            if (pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog has Just Changed (to GameMainScene::PROG_BEGIN)");
                pProg->change(GameMainScene::PROG_PLAY);
            }
            break;
        }

        case GameMainScene::PROG_PLAY: {
            if (pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog has Just Changed (to GameMainScene::PROG_PLAY)");
            }
            break;
        }

        case GameMainScene::PROG_FINISH: {
            if (pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog has Just Changed (to GameMainScene::PROG_FINISH)");
            }
            break;
        }

        default: {
            break;
        }
    }

}

void GameMainScene::onInactive() {
    if (P_STAGE_CTRLER->pStageMainCannel_) {
        _TRACE_("GameMainScene::onInactive() P_STAGE_CTRLER->pStageMainCannel_("<<
                P_STAGE_CTRLER->pStageMainCannel_->getName()<<") sayonara()");
        P_STAGE_CTRLER->pStageMainCannel_->sayonara();
        P_STAGE_CTRLER->pStageMainCannel_ = nullptr;
    }
    if (P_RANKUP_CONTROLLER->pNowRankUpStage_) {
        _TRACE_("GameMainScene::onInactive() P_RANKUP_CONTROLLER->sayonaraRankUpStages()");
        P_RANKUP_CONTROLLER->sayonaraRankUpStages();
        P_RANKUP_CONTROLLER->pNowRankUpStage_ = nullptr;
    }
}


void GameMainScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

GameMainScene::~GameMainScene() {
}

