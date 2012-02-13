#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define ORDER_ID_STAGE 11

//GameMainScene* GameMainScene::_pGameMainScene = NULL;

GameMainScene::GameMainScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameMainScene";

    _pFont16_SCORE = NEW LabelGecchi16Font("SCORE");
    _pFont16_SCORE->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    _pFont16_SCORE->locate(PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH)), PX2CO(1));
    getDirector()->addSubGroup(_pFont16_SCORE);

    _pFont16_RANK = NEW LabelGecchi16Font("RANK");
    _pFont16_RANK->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    _pFont16_RANK->locate(PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH)), PX2CO(20));
    getDirector()->addSubGroup(_pFont16_RANK);

    _pFont16_STAMINA = NEW LabelGecchi16Font("STAMINA");
    _pFont16_STAMINA->setAlign(ALIGN_RIGHT, VALIGN_TOP);
    _pFont16_STAMINA->locate(PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH)), PX2CO(40));
    getDirector()->addSubGroup(_pFont16_STAMINA);

    _pFont8_JIKI_X = NEW LabelGecchi8Font("JIKI_X");
    _pFont8_JIKI_Y = NEW LabelGecchi8Font("JIKI_Y");
    _pFont8_JIKI_Z = NEW LabelGecchi8Font("JIKI_Z");
    _pFont8_JIKI_X->locate(PX2CO(1), PX2CO(CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 8*3-1));
    _pFont8_JIKI_Y->locate(PX2CO(1), PX2CO(CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 8*2-1));
    _pFont8_JIKI_Z->locate(PX2CO(1), PX2CO(CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 8*1-1));
    getDirector()->addSubGroup(_pFont8_JIKI_X);
    getDirector()->addSubGroup(_pFont8_JIKI_Y);
    getDirector()->addSubGroup(_pFont8_JIKI_Z);

    _pRankFont = NEW LabelRankFont("RankFont"); //LabelRankFont‚Í ALIGN_RIGHT,VALIGN_BOTTOM ŒÅ’è
    _pRankFont->locate(PX2CO(CFG_PROPERTY(GAME_BUFFER_WIDTH)), PX2CO(CFG_PROPERTY(GAME_BUFFER_HEIGHT)));
    getDirector()->addSubGroup(_pRankFont);

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
    sprintf(_buf, "SCORE %07u", _SCORE_);
    _pFont16_SCORE->update(_buf);
    sprintf(_buf, "RANK %.7f", _RANK_);
    _pFont16_RANK->update(_buf);
    sprintf(_buf, "STAMINA %7d", P_MYSHIP->_pStatus->get(STAT_Stamina));
    _pFont16_STAMINA->update(_buf);

    sprintf(_buf, "X:%8d", P_MYSHIP->_X);
    _pFont8_JIKI_X->update(_buf);
    sprintf(_buf, "Y:%8d", P_MYSHIP->_Y);
    _pFont8_JIKI_Y->update(_buf);
    sprintf(_buf, "Z:%8d", P_MYSHIP->_Z);
    _pFont8_JIKI_Z->update(_buf);

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
    if (P_STAGE_CONTROLLER->_pStageMainCannel) {
        P_STAGE_CONTROLLER->_pStageMainCannel->end();
        P_STAGE_CONTROLLER->_pStageMainCannel = NULL;
    }
}


void GameMainScene::onCatchEvent(hashval prm_no, void* prm_pSource) {
}

GameMainScene::~GameMainScene() {
}

