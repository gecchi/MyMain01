#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameBeginningScene::GameBeginningScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameBeginningScene";

    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(KIND_EFFECT, _pStringBoard02);
    _selected_stage = 0;
    useProgress(10);
}


void GameBeginningScene::reset() {
    _TRACE_("GamePreTitleScene::reset()");
    _pProgress->change(GAMEBEGINNING_SCENE_PROG_INIT);
    unblindScene();
    _pStringBoard01->update("");
    _pStringBoard02->update("");
}
//void GameBeginningScene::ready() {
//    _TRACE_("GameBeginningScene::ready()");
//}
void GameBeginningScene::onActive() {
}

void GameBeginningScene::initialize() {
    reset();
}

void GameBeginningScene::processBehavior() {

    //GAMEPRETITLE_SCENE_PROG_INIT 時の処理
    if (_pProgress->onActive(GAMEBEGINNING_SCENE_PROG_INIT)) {
        _TRACE_("GameBeginningScene _pProgress->onActive(GAMEBEGINNING_SCENE_PROG_INIT)");
    }
    if (_pProgress->get() == GAMEBEGINNING_SCENE_PROG_INIT) {
        _pProgress->change(GAMEBEGINNING_SCENE_PROG_SELECT_MODE);
    }
    if (_pProgress->onInactive(GAMEBEGINNING_SCENE_PROG_INIT)) {
        _TRACE_("GameBeginningScene _pProgress->onInactive(GAMEPRETITLE_SCENE_PROG_INIT)");
    }


    //GAMEBEGINNING_SCENE_PROG_SELECT_MODE 時の処理
    if (_pProgress->onActive(GAMEBEGINNING_SCENE_PROG_SELECT_MODE)) {
        _TRACE_("GameBeginningScene _pProgress->onActive(GAMEBEGINNING_SCENE_PROG_SELECT_MODE)");
        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE BEGIN");
        _pStringBoard02->update(200, 250, "SELECT MODE!");
    }
    if (_pProgress->get() == GAMEBEGINNING_SCENE_PROG_SELECT_MODE) {
        if (VB->isPushedDown(VB_UI_EXECUTE) || _pProgress->getActivePartFrameIn() == 300) {
            _pProgress->change(GAMEBEGINNING_SCENE_PROG_DECIDE);
        }
    }
    if (_pProgress->onInactive(GAMEBEGINNING_SCENE_PROG_SELECT_MODE)) {
        _TRACE_("GameBeginningScene _pProgress->onInactive(GAMEBEGINNING_SCENE_PROG_SELECT_MODE)");
    }

    //GAMEBEGINNING_SCENE_PROG_DECIDE 時の処理
    if (_pProgress->onActive(GAMEBEGINNING_SCENE_PROG_DECIDE)) {
        _TRACE_("GameBeginningScene _pProgress->onActive(GAMEBEGINNING_SCENE_PROG_DECIDE)");
        fadeoutScene(FADE_FRAME);
        throwEventToUpperTree(EVENT_GAMEMODE_DECIDE);
    }
    if (_pProgress->get() == GAMEBEGINNING_SCENE_PROG_DECIDE) {
        if (_pProgress->getActivePartFrameIn() % 10 < 5 ) {
            _pStringBoard02->update(400, 500, "OK OK OK");
        } else {
            _pStringBoard02->update(400, 500, "");
        }
        if (_pProgress->getActivePartFrameIn() == FADE_FRAME) {
            _pProgress->change(GAMEBEGINNING_SCENE_PROG_FINISH); //タイトルシーン終了へ
        }
    }
    if (_pProgress->onInactive(GAMEBEGINNING_SCENE_PROG_DECIDE)) {
        _TRACE_("GameBeginningScene _pProgress->onInactive(GAMEBEGINNING_SCENE_PROG_DECIDE)");

    }

    //GAMEBEGINNING_SCENE_PROG_FINISH 時の処理
    if (_pProgress->onActive(GAMEBEGINNING_SCENE_PROG_FINISH)) {
        _TRACE_("GameBeginningScene _pProgress->onActive(GAMEBEGINNING_SCENE_PROG_FINISH)");
        inactivate();
    }
    if (_pProgress->get() == GAMEBEGINNING_SCENE_PROG_FINISH) {
    }
    if (_pProgress->onInactive(GAMEBEGINNING_SCENE_PROG_FINISH)) {
        _TRACE_("GameBeginningScene _pProgress->onInactive(GAMEBEGINNING_SCENE_PROG_FINISH)");
    }








//    if (_pProgress->get() == GAMEBEGINNING_SCENE_PROG_INIT) {
////        P_CAM->setDefaultPosition();
//        _pProgress->change(GAMEBEGINNING_SCENE_PROG_BEGIN);
//    }
//
//    //ゲーム開始直前の自機選択等、導入部
//    if (_pProgress->onActive(GAMEBEGINNING_SCENE_PROG_BEGIN)) {
//        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE BEGIN");
//        _pStringBoard02->update(200, 250, "YOKUKITANA!");
//        _frame_Begin = 0;
//    } else if (_pProgress->get() == GAMEBEGINNING_SCENE_PROG_BEGIN) {
//        //活動ループ
//        _frame_Begin++;
//
//        if (_frame_Begin == 120) {
//            _pProgress->change(GAMEBEGINNING_SCENE_PROG_OPE); //自機選択
//        }
//    }
//
//    //ゲーム開始直前の自機選択等
//    if (_pProgress->onActive(GAMEBEGINNING_SCENE_PROG_OPE)) {
//        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE OPE");
//        _pStringBoard02->update(200, 250, "SELECT YOUR EQ!");
//        _frame_Ope = 0;
//    } else if (_pProgress->get() == GAMEBEGINNING_SCENE_PROG_OPE) {
//        //活動ループ
//        _frame_Ope++;
//
//        if (VB->isPushedDown(VB_UI_EXECUTE)) {
//            _selected_stage += 1; //テスト
//            _pProgress->change(GAMEBEGINNING_SCENE_PROG_DECIDE);
//        }
//    }
//
//    //ゲーム開始直前の自機選択等、決定後のフェードアウト部
//    if (_pProgress->onActive(GAMEBEGINNING_SCENE_PROG_DECIDE)) {
//        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE DECIDE");
//        _pStringBoard02->update(200, 250, "OK. ARE YOU READY!");
//        _frame_Decide = 0;
//    } else if (_pProgress->get() == GAMEBEGINNING_SCENE_PROG_DECIDE) {
//        //活動ループ
//        _frame_Decide++;
//
//        if (_frame_Decide == 60*5) { //5秒（ここでステージを作ってるはず
//            _pProgress->change(GAMEBEGINNING_SCENE_PROG_END); //お終い
//        }
//    }
//
//    if (_pProgress->onActive(GAMEBEGINNING_SCENE_PROG_END)) {
//        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE END");
//        _pStringBoard02->update(200, 250, "GOOD LUCK");
//        inactivateDelay(140);
//    }
}

void GameBeginningScene::processFinal() {
}

GameBeginningScene::~GameBeginningScene() {
}
