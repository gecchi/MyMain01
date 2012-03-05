#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define ORDER_ID_STAGE 11

//GameMainScene* GameMainScene::pGameMainScene_ = NULL;

GameMainScene::GameMainScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameMainScene";

    pFont16_SCORE_ = NEW LabelGecchi16Font("SCORE");
    pFont16_SCORE_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pFont16_SCORE_->locate(PX2CO(GGAF_PROPERTY(GAME_BUFFER_WIDTH)), PX2CO(1));
    getDirector()->addSubGroup(pFont16_SCORE_);

    pFont16_RANK_ = NEW LabelGecchi16Font("RANK");
    pFont16_RANK_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pFont16_RANK_->locate(PX2CO(GGAF_PROPERTY(GAME_BUFFER_WIDTH)), PX2CO(20));
    getDirector()->addSubGroup(pFont16_RANK_);

    pFont16_STAMINA_ = NEW LabelGecchi16Font("STAMINA");
    pFont16_STAMINA_->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    pFont16_STAMINA_->locate(PX2CO(GGAF_PROPERTY(GAME_BUFFER_WIDTH)), PX2CO(40));
    getDirector()->addSubGroup(pFont16_STAMINA_);

    pFont8_JIKI_X_ = NEW LabelGecchi8Font("JIKI_X");
    pFont8_JIKI_Y_ = NEW LabelGecchi8Font("JIKI_Y");
    pFont8_JIKI_Z_ = NEW LabelGecchi8Font("JIKI_Z");
    pFont8_JIKI_X_->locate(PX2CO(1), PX2CO(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 8*3-1));
    pFont8_JIKI_Y_->locate(PX2CO(1), PX2CO(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 8*2-1));
    pFont8_JIKI_Z_->locate(PX2CO(1), PX2CO(GGAF_PROPERTY(GAME_BUFFER_HEIGHT) - 8*1-1));
    getDirector()->addSubGroup(pFont8_JIKI_X_);
    getDirector()->addSubGroup(pFont8_JIKI_Y_);
    getDirector()->addSubGroup(pFont8_JIKI_Z_);

    pRankFont_ = NEW LabelRankFont("RankFont"); //LabelRankFont‚Í ALIGN_RIGHT,VALIGN_BOTTOM ŒÅ’è
    pRankFont_->locate(PX2CO(GGAF_PROPERTY(GAME_BUFFER_WIDTH)), PX2CO(GGAF_PROPERTY(GAME_BUFFER_HEIGHT)));
    getDirector()->addSubGroup(pRankFont_);

    useProgress(GameMainScene::PROG_FINISH);
}

void GameMainScene::onReset() {
    _TRACE_("GameMainScene::onReset()");
    _pProg->set(GameMainScene::PROG_INIT);
}

void GameMainScene::initialize() {
}

void GameMainScene::processBehavior() {
    //SCORE•\Ž¦
    sprintf(buf_, "SCORE %07u", _SCORE_);
    pFont16_SCORE_->update(buf_);
    sprintf(buf_, "RANK %.7f", _RANK_);
    pFont16_RANK_->update(buf_);
    sprintf(buf_, "STAMINA %7d", P_MYSHIP->_pStatus->get(STAT_Stamina));
    pFont16_STAMINA_->update(buf_);

    sprintf(buf_, "X:%8d", P_MYSHIP->_X);
    pFont8_JIKI_X_->update(buf_);
    sprintf(buf_, "Y:%8d", P_MYSHIP->_Y);
    pFont8_JIKI_Y_->update(buf_);
    sprintf(buf_, "Z:%8d", P_MYSHIP->_Z);
    pFont8_JIKI_Z_->update(buf_);

    switch (_pProg->get()) {
        case GameMainScene::PROG_INIT: {
            _TRACE_("GameMainScene::processBehavior() Prog(=GameMainScene::PROG_INIT)");
            addSubLast(P_STAGE_WORLD->extract());
            P_STAGE_WORLD->resetTree();
            P_STAGE_WORLD->activateImmed();
            _pProg->change(GameMainScene::PROG_BEGIN);
            break;
        }

        case GameMainScene::PROG_BEGIN: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog(=GameMainScene::PROG_BEGIN) is Just Changed");
                _pProg->change(GameMainScene::PROG_PLAY);
            }
            break;
        }

        case GameMainScene::PROG_PLAY: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog(=GameMainScene::PROG_PLAY) is Just Changed");
            }
            break;
        }

        case GameMainScene::PROG_FINISH: {
            if (_pProg->isJustChanged()) {
                _TRACE_("GameMainScene::processBehavior() Prog(=GameMainScene::PROG_FINISH) is Just Changed");
            }
            break;
        }

        default:
            break;
    }

}

void GameMainScene::onInactive() {
    if (P_STAGE_CONTROLLER->pStageMainCannel_) {
        P_STAGE_CONTROLLER->pStageMainCannel_->end();
        P_STAGE_CONTROLLER->pStageMainCannel_ = NULL;
    }
}


void GameMainScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

GameMainScene::~GameMainScene() {
}

