#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameBeginningScene::GameBeginningScene(const char* prm_name) : DefaultScene(prm_name) {
    _pFontPlate01 = NEW FontPlateActor("STR01", "P/moji");
    getLordActor()->accept(KIND_EFFECT, _pFontPlate01);
    _pFontPlate02 = NEW FontPlateActor("STR02", "P/moji");
    getLordActor()->accept(KIND_EFFECT, _pFontPlate02);
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

    if (isChangeProgress(GAMEBEGINNING_PROG_BEGIN)) {
        _pFontPlate01->setString(200, 200, "GameBeginningScene BEGIN");
        _pFontPlate02->setString(200, 250, "YOKUKITANA!");
        _dwFrame_Begin = 0;
    } else if (getProgress() == GAMEBEGINNING_PROG_BEGIN) {
        //�������[�v
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 120) {
            setProgress(GAMEBEGINNING_PROG_OPE); //�^�C�g����
        }
    }


    if (isChangeProgress(GAMEBEGINNING_PROG_OPE)) {
        _pFontPlate01->setString(200, 200, "GameBeginningScene OPE");
        _pFontPlate02->setString(200, 250, "SELECT YOUR HOGEHOGE!");
        _dwFrame_Ope = 0;
    } else if (getProgress() == GAMEBEGINNING_PROG_OPE) {
        //�������[�v
        _dwFrame_Ope++;

        if (VB::isPushedDown(VB_UI_EXECUTE)) {
            _selected_stage = 1;
            setProgress(GAMEBEGINNING_PROG_DECIDE);
        }
    }

    if (isChangeProgress(GAMEBEGINNING_PROG_DECIDE)) {
        _pFontPlate01->setString(200, 200, "GameBeginningScene DECIDE");
        _pFontPlate02->setString(200, 250, "OK . ARE YOU READY!");
        _dwFrame_Decide = 0;
    } else if (getProgress() == GAMEBEGINNING_PROG_DECIDE) {
        //�������[�v
        _dwFrame_Decide++;

        if (_dwFrame_Decide == 120) {
            setProgress(GAMEBEGINNING_PROG_END); //���I��
        }
    }

    if (isChangeProgress(GAMEBEGINNING_PROG_END)) {
        _pFontPlate01->setString(200, 200, "GameBeginningScene END");
        _pFontPlate02->setString(200, 250, "KENTO WO INORU");
        inactAfter(140);
    }
}

void GameBeginningScene::processFinal() {
}

GameBeginningScene::~GameBeginningScene() {
}
