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
    _pStringBoard_SCORE = NEW GgafDx9StringBoardActor("SCORE", "moji");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard_SCORE);
    _pStringBoard01 = NEW GgafDx9StringBoardActor("STR01", "moji");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW GgafDx9StringBoardActor("STR02", "moji");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard02);
    _pStage01 = NULL;
    _pStage02 = NULL;
    _pStage03 = NULL;
    _pStage04 = NULL;
    _pStage05 = NULL;

    _pSceneMainCannnel = NULL;
    setProgress(GAMEMAIN_PROG_INIT);
}
void GameMainScene::reset() {
    setProgress(GAMEMAIN_PROG_INIT);
}
void GameMainScene::ready(int prm_stage) {
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
    if (getProgress() == GAMEMAIN_PROG_INIT) {
        setProgress(GAMEMAIN_PROG_BEGIN);
    }

    if (onChangeProgressAt(GAMEMAIN_PROG_BEGIN)) {
        _pStringBoard01->update(300, 300, "GameMainScene BEGIN");
        _pStringBoard02->update(300, 350, "DESTOROY ALL!");
        addSubLast(obtainSceneFromFactory(11)); //ステージシーン追加
        _dwFrame_Begin = 0;
    } else if (getProgress() == GAMEMAIN_PROG_BEGIN) {
        //活動ループ
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 180) {
            setProgress(GAMEMAIN_PROG_PLAY); //
        }
    }

    if (onChangeProgressAt(GAMEMAIN_PROG_PLAY)) {
        _pStringBoard01->update(300, 300, "");
        _pStringBoard02->update(300, 350, "");

    }

    //SCORE表示
    sprintf(_buf, "Src:%07u", GameGlobal::_dwScore);
    _pStringBoard_SCORE->update(600, 0, _buf);
}

void GameMainScene::processFinal() {
}

GameMainScene::~GameMainScene() {
}

