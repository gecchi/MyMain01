#include "GameMainScene.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/core/scene/Scene.h"
#include <stdio.h>
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelScoreFont.h"

using namespace GgafLib;
using namespace VioletVreath;

#define ORDER_ID_STAGE 11

enum {
    PHASE_INIT    ,
    PHASE_BEGIN   ,
    PHASE_PLAY    ,
    PHASE_FINISH  ,
    PHASE_BANPEI,
};

//GameMainScene* GameMainScene::pGameMainScene_ = nullptr;

GameMainScene::GameMainScene(const char* prm_name) : VvScene<DefaultScene>(prm_name) {
    _class_name = "GameMainScene";

    pLabel_SCORE_ = NEW LabelScoreFont("SCORE");
    pLabel_SCORE_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pLabel_SCORE_->setPosition(PX_C(CONFIG::GAME_BUFFER_WIDTH), PX_C(1));
    getSceneChief()->appendGroupChild(pLabel_SCORE_);

    pLabel_RANK_ = NEW LabelGecchi16Font("RANK");
    pLabel_RANK_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pLabel_RANK_->setPosition(PX_C(CONFIG::GAME_BUFFER_WIDTH), PX_C(30));
    getSceneChief()->appendGroupChild(pLabel_RANK_);

    pLabel_STAMINA_ = NEW LabelGecchi16Font("STAMINA");
    pLabel_STAMINA_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pLabel_STAMINA_->setPosition(PX_C(CONFIG::GAME_BUFFER_WIDTH), PX_C(50));
    getSceneChief()->appendGroupChild(pLabel_STAMINA_);

    pLabel_JIKI_x_ = NEW LabelGecchi8Font("JIKI_x");
    pLabel_JIKI_y_ = NEW LabelGecchi8Font("JIKI_y");
    pLabel_JIKI_z_ = NEW LabelGecchi8Font("JIKI_z");
    pLabel_JIKI_x_->setPosition(PX_C(1), PX_C(CONFIG::GAME_BUFFER_HEIGHT - 8*3-1));
    pLabel_JIKI_y_->setPosition(PX_C(1), PX_C(CONFIG::GAME_BUFFER_HEIGHT - 8*2-1));
    pLabel_JIKI_z_->setPosition(PX_C(1), PX_C(CONFIG::GAME_BUFFER_HEIGHT - 8*1-1));
    getSceneChief()->appendGroupChild(pLabel_JIKI_x_);
    getSceneChief()->appendGroupChild(pLabel_JIKI_y_);
    getSceneChief()->appendGroupChild(pLabel_JIKI_z_);

    pRankFont_ = NEW LabelRankFont("RankFont"); //LabelRankFont‚Í ALIGN_RIGHT,VALIGN_BOTTOM ŒÅ’è
    pRankFont_->setPosition(PX_C(CONFIG::GAME_BUFFER_WIDTH), PX_C(CONFIG::GAME_BUFFER_HEIGHT));
    getSceneChief()->appendGroupChild(pRankFont_);
}

void GameMainScene::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    getPhase()->reset(PHASE_INIT);
}

void GameMainScene::initialize() {
}

void GameMainScene::processBehavior() {
    MyShip* pMyShip = pMYSHIP;
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

    ScenePhase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            _TRACE_(FUNC_NAME<<" Phase is PHASE_INIT");
            appendChild(pSTAGE_WORLD->extract());
            pSTAGE_WORLD->resetTree();
            pSTAGE_WORLD->inactivateImmed();
            pSTAGE_WORLD->activate();
            pPhase->change(PHASE_BEGIN);
            break;
        }

        case PHASE_BEGIN: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_BEGIN)");
                pPhase->change(PHASE_PLAY);
            }
            break;
        }

        case PHASE_PLAY: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_PLAY)");
            }
            break;
        }

        case PHASE_FINISH: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Phase has Just Changed (to PHASE_FINISH)");
            }
            break;
        }

        default: {
            break;
        }
    }
}

void GameMainScene::onInactive() {
    if (pSTAGE_CTRLER->pStageMainCannel_) {
        _TRACE_(FUNC_NAME<<" pSTAGE_CTRLER->pStageMainCannel_("<<
                pSTAGE_CTRLER->pStageMainCannel_->getName()<<") sayonara()");
        pSTAGE_CTRLER->pStageMainCannel_->sayonara();
        pSTAGE_CTRLER->pStageMainCannel_ = nullptr;
    }
    if (pRANKUP_CONTROLLER->pNowRankUpStage_) {
        _TRACE_(FUNC_NAME<<" pRANKUP_CONTROLLER->sayonaraRankUpStages()");
        pRANKUP_CONTROLLER->sayonaraRankUpStages();
        pRANKUP_CONTROLLER->pNowRankUpStage_ = nullptr;
    }
}


void GameMainScene::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
}

GameMainScene::~GameMainScene() {
}

