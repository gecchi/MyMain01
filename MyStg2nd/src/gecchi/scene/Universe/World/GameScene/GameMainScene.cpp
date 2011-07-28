#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

enum {
    GAMEMAINSCENE_PROG_INIT = 1,
    GAMEMAINSCENE_PROG_BEGIN   ,
    GAMEMAINSCENE_PROG_PLAY    ,
    GAMEMAINSCENE_PROG_FINISH  ,
};

#define ORDER_ID_STAGESCENE 11

//GameMainScene* GameMainScene::_pGameMainScene = NULL;

GameMainScene::GameMainScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameMainScene";

    _pFont16_SCORE = NEW LabelGecchi16Font("SCORE");
    _pFont16_SCORE->locate(550*1000, 1*1000);
    getLordActor()->addSubGroup(_pFont16_SCORE);
    _pFont16_RANK = NEW LabelGecchi16Font("RANK");
    _pFont16_RANK->locate(550*1000, 20*1000);
    getLordActor()->addSubGroup(_pFont16_RANK);
    _pFont16_STAMINA = NEW LabelGecchi16Font("STAMINA");
    _pFont16_STAMINA->locate(550*1000, 40*1000);
    getLordActor()->addSubGroup(_pFont16_STAMINA);
    _pFont8_JIKI_X = NEW LabelGecchi8Font("JIKI_X");
    _pFont8_JIKI_Y = NEW LabelGecchi8Font("JIKI_Y");
    _pFont8_JIKI_Z = NEW LabelGecchi8Font("JIKI_Z");
    _pFont8_JIKI_X->locate(1*1000, (CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 8*3-1)*1000);
    _pFont8_JIKI_Y->locate(Pix2App(1), Pix2App(CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 8*2-1));
    _pFont8_JIKI_Z->locate(1*1000, (CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 8*1-1)*1000);
    getLordActor()->addSubGroup(_pFont8_JIKI_X);
    getLordActor()->addSubGroup(_pFont8_JIKI_Y);
    getLordActor()->addSubGroup(_pFont8_JIKI_Z);

    _pRankFont = NEW LabelRankFont("RankFont");
    _pRankFont->locate(1000*1000, (CFG_PROPERTY(GAME_BUFFER_HEIGHT) - 100*1-1)*1000);
    getLordActor()->addSubGroup(_pRankFont);

    useProgress(GAMEMAINSCENE_PROG_FINISH);
}

void GameMainScene::onReset() {
    _pProg->set(GAMEMAINSCENE_PROG_INIT);
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
        case GAMEMAINSCENE_PROG_INIT: {
            addSubLast(P_STAGE_CONTROLLER->extract());
            P_STAGE_CONTROLLER->reset();
            P_STAGE_CONTROLLER->activateImmediately();
            _pProg->change(GAMEMAINSCENE_PROG_BEGIN);
            break;
        }

        case GAMEMAINSCENE_PROG_BEGIN: {
            _pProg->change(GAMEMAINSCENE_PROG_PLAY);
            break;
        }

        case GAMEMAINSCENE_PROG_PLAY: {
            break;
        }

        case GAMEMAINSCENE_PROG_FINISH: {
            if (_pProg->isJustChanged()) {
            }
            break;
        }

        default:
            break;
    }

}




void GameMainScene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
}

void GameMainScene::processFinal() {
}

GameMainScene::~GameMainScene() {
}

