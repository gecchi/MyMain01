#include "GameMainScene.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/scene/GgafScene.h"
#include <stdio.h>
#include "jp/gecchi/VioletVreath/actor/VVCommonActorsHeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
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
    pLabel_SCORE_->locate(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(1));
    bringDirector()->addSubGroup(pLabel_SCORE_);

    pLabel_RANK_ = NEW LabelGecchi16Font("RANK");
    pLabel_RANK_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pLabel_RANK_->locate(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(30));
    bringDirector()->addSubGroup(pLabel_RANK_);

    pLabel_STAMINA_ = NEW LabelGecchi16Font("STAMINA");
    pLabel_STAMINA_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pLabel_STAMINA_->locate(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(50));
    bringDirector()->addSubGroup(pLabel_STAMINA_);

    pLabel_JIKI_x_ = NEW LabelGecchi8Font("JIKI_x");
    pLabel_JIKI_y_ = NEW LabelGecchi8Font("JIKI_y");
    pLabel_JIKI_z_ = NEW LabelGecchi8Font("JIKI_z");
    pLabel_JIKI_x_->locate(PX_C(1), PX_C(PROPERTY::GAME_BUFFER_HEIGHT - 8*3-1));
    pLabel_JIKI_y_->locate(PX_C(1), PX_C(PROPERTY::GAME_BUFFER_HEIGHT - 8*2-1));
    pLabel_JIKI_z_->locate(PX_C(1), PX_C(PROPERTY::GAME_BUFFER_HEIGHT - 8*1-1));
    bringDirector()->addSubGroup(pLabel_JIKI_x_);
    bringDirector()->addSubGroup(pLabel_JIKI_y_);
    bringDirector()->addSubGroup(pLabel_JIKI_z_);

    pRankFont_ = NEW LabelRankFont("RankFont"); //LabelRankFont‚Í ALIGN_RIGHT,VALIGN_BOTTOM ŒÅ’è
    pRankFont_->locate(PX_C(PROPERTY::GAME_BUFFER_WIDTH), PX_C(PROPERTY::GAME_BUFFER_HEIGHT));
    bringDirector()->addSubGroup(pRankFont_);

    useProgress(PROG_BANPEI-1);
}

void GameMainScene::onReset() {
    _TRACE_(FUNC_NAME<<" "<<NODE_INFO<<"");
    getProgress()->reset(PROG_INIT);
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
        case PROG_INIT: {
            _TRACE_(FUNC_NAME<<" Prog is PROG_INIT");
            addSubLast(P_STAGE_WORLD->extract());
            P_STAGE_WORLD->resetTree();
            P_STAGE_WORLD->inactivateImmed();
            P_STAGE_WORLD->activate();
            pProg->change(PROG_BEGIN);
            break;
        }

        case PROG_BEGIN: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_BEGIN)");
                pProg->change(PROG_PLAY);
            }
            break;
        }

        case PROG_PLAY: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_PLAY)");
            }
            break;
        }

        case PROG_FINISH: {
            if (pProg->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" Prog has Just Changed (to PROG_FINISH)");
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
        _TRACE_(FUNC_NAME<<" P_STAGE_CTRLER->pStageMainCannel_("<<
                P_STAGE_CTRLER->pStageMainCannel_->getName()<<") sayonara()");
        P_STAGE_CTRLER->pStageMainCannel_->sayonara();
        P_STAGE_CTRLER->pStageMainCannel_ = nullptr;
    }
    if (P_RANKUP_CONTROLLER->pNowRankUpStage_) {
        _TRACE_(FUNC_NAME<<" P_RANKUP_CONTROLLER->sayonaraRankUpStages()");
        P_RANKUP_CONTROLLER->sayonaraRankUpStages();
        P_RANKUP_CONTROLLER->pNowRankUpStage_ = nullptr;
    }
}


void GameMainScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

GameMainScene::~GameMainScene() {
}

