﻿#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameBeginningScene::GameBeginningScene(const char* prm_name) : DefaultScene(prm_name) {
    _pStringBoard01 = NEW GgafDx9StringBoardActor("STR01", "moji");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW GgafDx9StringBoardActor("STR02", "moji");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard02);
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

    //ゲーム開始直前の自機選択等、導入部
    if (onChangeProgressAt(GAMEBEGINNING_PROG_BEGIN)) {
        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE BEGIN");
        _pStringBoard02->update(200, 250, "YOKUKITANA!");
        _dwFrame_Begin = 0;
    } else if (getProgress() == GAMEBEGINNING_PROG_BEGIN) {
        //活動ループ
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 120) {
            setProgress(GAMEBEGINNING_PROG_OPE); //タイトルへ
        }
    }

    //ゲーム開始直前の自機選択等
    if (onChangeProgressAt(GAMEBEGINNING_PROG_OPE)) {
        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE OPE");
        _pStringBoard02->update(200, 250, "SELECT YOUR EQ!");
        _dwFrame_Ope = 0;
    } else if (getProgress() == GAMEBEGINNING_PROG_OPE) {
        //活動ループ
        _dwFrame_Ope++;

        if (VB::isPushedDown(VB_UI_EXECUTE)) {
            _selected_stage = 1;
            setProgress(GAMEBEGINNING_PROG_DECIDE);
        }
    }

    //ゲーム開始直前の自機選択等、決定後のフェードアウト部
    if (onChangeProgressAt(GAMEBEGINNING_PROG_DECIDE)) {
        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE DECIDE");
        _pStringBoard02->update(200, 250, "OK. ARE YOU READY!");
        _dwFrame_Decide = 0;
    } else if (getProgress() == GAMEBEGINNING_PROG_DECIDE) {
        //活動ループ
        _dwFrame_Decide++;

        if (_dwFrame_Decide == 60*5) { //5秒（ここでステージを作ってるはず
            setProgress(GAMEBEGINNING_PROG_END); //お終い
        }
    }

    if (onChangeProgressAt(GAMEBEGINNING_PROG_END)) {
        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE END");
        _pStringBoard02->update(200, 250, "GOOD LUCK");
        inactivateAfter(140);
    }
}

void GameBeginningScene::processFinal() {
}

GameBeginningScene::~GameBeginningScene() {
}
