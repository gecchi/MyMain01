#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define ORDER_ID_CREATESTAGE01SCENE 11
#define ORDER_ID_CREATESTAGE02SCENE 12
#define ORDER_ID_CREATESTAGE03SCENE 13
#define ORDER_ID_CREATESTAGE04SCENE 14
#define ORDER_ID_CREATESTAGE05SCENE 15

GameMainScene::GameMainScene(const char* prm_name) : DefaultScene(prm_name) {
    _pFontPlate_SCORE = NEW FontPlateActor("STR01", "P/moji");
    getLordActor()->accept(KIND_EFFECT, _pFontPlate_SCORE);
    _pFontPlate01 = NEW FontPlateActor("STR01", "P/moji");
    getLordActor()->accept(KIND_EFFECT, _pFontPlate01);
    _pFontPlate02 = NEW FontPlateActor("STR02", "P/moji");
    getLordActor()->accept(KIND_EFFECT, _pFontPlate02);

    _pStage01 = NULL;
    _pStage02 = NULL;
    _pStage03 = NULL;
    _pStage04 = NULL;
    _pStage05 = NULL;

    _pSceneMainCannnel = NULL;
    setProgress(GAMEMAIN_PROG_INIT);
}
void GameMainScene::reset() {
    _TRACE_("GameMainScene::reset()");
    setProgress(GAMEMAIN_PROG_INIT);
}
void GameMainScene::ready(int prm_stage) {
	 _TRACE_("GameMainScene::ready("<<prm_stage<<")");
    _stage = prm_stage;
    switch (prm_stage) {
        case 1:
            orderSceneToFactory(11, Stage01Scene, "Stage01");
            _pSceneMainCannnel = _pStage01;
            break;
        case 2:
            orderSceneToFactory(11, Stage02Scene, "Stage02");
            _pSceneMainCannnel = _pStage02;
            break;
        case 3:
            orderSceneToFactory(11, Stage03Scene, "Stage03");
            _pSceneMainCannnel = _pStage03;
            break;
        case 4:
            orderSceneToFactory(11, Stage04Scene, "Stage04");
            _pSceneMainCannnel = _pStage04;
            break;
        case 5:
            orderSceneToFactory(11, Stage05Scene, "Stage05");
            _pSceneMainCannnel = _pStage05;
            break;
        default:
            break;
    }
}

void GameMainScene::initialize() {
}


void GameMainScene::processBehavior() {
    if (isChangeProgress(GAMEMAIN_PROG_INIT)) {
        setProgress(GAMEMAIN_PROG_BEGIN);
    }

    if (isChangeProgress(GAMEMAIN_PROG_BEGIN)) {
        _pFontPlate01->setString(300, 300, "GameMainScene BEGIN");
        _pFontPlate02->setString(200, 250, "DESTOROY ALL!");
        addSubLast(obtainSceneFromFactory(11));
        _dwFrame_Begin = 0;
    } else if (getProgress() == GAMEMAIN_PROG_BEGIN) {
        //Šˆ“®ƒ‹[ƒv
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 120) {
            setProgress(GAMEMAIN_PROG_PLAY); //
        }
    }


    //SCORE•\Ž¦
    sprintf(_buf, "SCORE:%07u", GameGlobal::_dwScore);
    _pFontPlate_SCORE->setString(500, 0, _buf);
}

void GameMainScene::processFinal() {
}

GameMainScene::~GameMainScene() {
}

