#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameBeginningScene::GameBeginningScene(const char* prm_name) : DefaultScene(prm_name) {
    _pFontBoard01 = NEW FontBoardActor("STR01", "B/moji");
    getLordActor()->accept(KIND_EFFECT, _pFontBoard01);
    _pFontBoard02 = NEW FontBoardActor("STR02", "B/moji");
    getLordActor()->accept(KIND_EFFECT, _pFontBoard02);
}


void GameBeginningScene::reset() {
    _TRACE_("GameBeginningScene::reset()");
    setProgress(GAMEBEGINNING_PROG_INIT);
}
void GameBeginningScene::ready() {
    _TRACE_("GameBeginningScene::ready()");
}

void GameBeginningScene::initialize() {
    setProgress(GAMEBEGINNING_PROG_INIT);
}

void GameBeginningScene::processBehavior() {
    if (getProgress() == GAMEBEGINNING_PROG_INIT) {
        setProgress(GAMEBEGINNING_PROG_BEGIN);
    }

    if (onChangeProgress(GAMEBEGINNING_PROG_BEGIN)) {
        _pFontBoard01->setString(200, 200, "GameBeginningScene BEGIN");
        _pFontBoard02->setString(200, 250, "YOKUKITANA!");
        _dwFrame_Begin = 0;
    } else if (getProgress() == GAMEBEGINNING_PROG_BEGIN) {
        //活動ループ
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 120) {
            setProgress(GAMEBEGINNING_PROG_OPE); //タイトルへ
        }
    }


    if (onChangeProgress(GAMEBEGINNING_PROG_OPE)) {
        _pFontBoard01->setString(200, 200, "GameBeginningScene OPE");
        _pFontBoard02->setString(200, 250, "SELECT YOUR HOGEHOGE!");
        _dwFrame_Ope = 0;
    } else if (getProgress() == GAMEBEGINNING_PROG_OPE) {
        //活動ループ
        _dwFrame_Ope++;

        if (VB::isPushedDown(VB_UI_EXECUTE)) {
            _selected_stage = 1;
            setProgress(GAMEBEGINNING_PROG_DECIDE);
        }
    }

    if (onChangeProgress(GAMEBEGINNING_PROG_DECIDE)) {
        _pFontBoard01->setString(200, 200, "GameBeginningScene DECIDE");
        _pFontBoard02->setString(200, 250, "OK . ARE YOU READY!");
        _dwFrame_Decide = 0;
    } else if (getProgress() == GAMEBEGINNING_PROG_DECIDE) {
        //活動ループ
        _dwFrame_Decide++;

        if (_dwFrame_Decide == 60*5) { //5秒（ここでステージを作ってるはず
            setProgress(GAMEBEGINNING_PROG_END); //お終い
        }
    }

    if (onChangeProgress(GAMEBEGINNING_PROG_END)) {
        _pFontBoard01->setString(200, 200, "GameBeginningScene END");
        _pFontBoard02->setString(200, 250, "KENTO WO INORU");
        inactAfter(140);
    }
}

void GameBeginningScene::processFinal() {
}

GameBeginningScene::~GameBeginningScene() {
}
