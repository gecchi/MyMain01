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
}


void GameBeginningScene::reset() {
    _TRACE_("GamePreTitleScene::reset()");
    changeProgress(GAMEBEGINNING_SCENE_PROG_INIT);
    unblindScene();
    _pStringBoard01->update("");
    _pStringBoard02->update("");
}
//void GameBeginningScene::ready() {
//    _TRACE_("GameBeginningScene::ready()");
//}
void GameBeginningScene::onActive() {
    reset();
}

void GameBeginningScene::initialize() {
}

void GameBeginningScene::processBehavior() {

    //GAMEPRETITLE_SCENE_PROG_INIT ���̏���
    if (onActiveProgress(GAMEBEGINNING_SCENE_PROG_INIT)) {
        _TRACE_("GameBeginningScene onActiveProgress(GAMEBEGINNING_SCENE_PROG_INIT)");
    }
    if (getProgress() == GAMEBEGINNING_SCENE_PROG_INIT) {
        changeProgress(GAMEBEGINNING_SCENE_PROG_SELECT_MODE);
    }
    if (onInactiveProgress(GAMEBEGINNING_SCENE_PROG_INIT)) {
        _TRACE_("GameBeginningScene onInactiveProgress(GAMEPRETITLE_SCENE_PROG_INIT)");
    }


    //GAMEBEGINNING_SCENE_PROG_SELECT_MODE ���̏���
    if (onActiveProgress(GAMEBEGINNING_SCENE_PROG_SELECT_MODE)) {
        _TRACE_("GameBeginningScene onActiveProgress(GAMEBEGINNING_SCENE_PROG_SELECT_MODE)");
        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE BEGIN");
        _pStringBoard02->update(200, 250, "SELECT MODE!");
    }
    if (getProgress() == GAMEBEGINNING_SCENE_PROG_INIT) {
        if (VB->isPushedDown(VB_UI_EXECUTE)) {
            changeProgress(GAMEBEGINNING_SCENE_PROG_DECIDE);
        }
        changeProgress(GAMEBEGINNING_SCENE_PROG_DECIDE);
    }
    if (onInactiveProgress(GAMEBEGINNING_SCENE_PROG_SELECT_MODE)) {
        _TRACE_("GameBeginningScene onInactiveProgress(GAMEBEGINNING_SCENE_PROG_SELECT_MODE)");
    }

    //GAMEBEGINNING_SCENE_PROG_DECIDE ���̏���
    if (onActiveProgress(GAMEBEGINNING_SCENE_PROG_DECIDE)) {
        _TRACE_("GameBeginningScene onActiveProgress(GAMEBEGINNING_SCENE_PROG_DECIDE)");
        fadeoutScene(FADE_FRAME);
        _pStringBoard01->inactivate(FADE_FRAME);
        _pStringBoard02->inactivate(FADE_FRAME);
        throwEventToUpperTree(EVENT_GAMEMODE_DECIDE);
    }
    if (getProgress() == GAMEBEGINNING_SCENE_PROG_DECIDE) {
        if (getActivePartFrameInProgress() % 10 < 5 ) {
            _pStringBoard02->update(400, 500, "OK OK OK");
        } else {
            _pStringBoard02->update(400, 500, "");
        }
        if (getActivePartFrameInProgress() == FADE_FRAME) {
            changeProgress(GAMEBEGINNING_SCENE_PROG_FINISH); //�^�C�g���V�[���I����
        }
    }
    if (onInactiveProgress(GAMEBEGINNING_SCENE_PROG_DECIDE)) {
        _TRACE_("GameBeginningScene onInactiveProgress(GAMEBEGINNING_SCENE_PROG_DECIDE)");

    }

    //GAMEBEGINNING_SCENE_PROG_FINISH ���̏���
    if (onActiveProgress(GAMEBEGINNING_SCENE_PROG_FINISH)) {
        _TRACE_("GameBeginningScene onActiveProgress(GAMEBEGINNING_SCENE_PROG_FINISH)");
    }
    if (getProgress() == GAMEBEGINNING_SCENE_PROG_FINISH) {
    }
    if (onInactiveProgress(GAMEBEGINNING_SCENE_PROG_FINISH)) {
        _TRACE_("GameBeginningScene onInactiveProgress(GAMEBEGINNING_SCENE_PROG_FINISH)");
    }








//    if (getProgress() == GAMEBEGINNING_SCENE_PROG_INIT) {
////        P_CAM->setDefaultPosition();
//        changeProgress(GAMEBEGINNING_SCENE_PROG_BEGIN);
//    }
//
//    //�Q�[���J�n���O�̎��@�I�𓙁A������
//    if (onActiveProgress(GAMEBEGINNING_SCENE_PROG_BEGIN)) {
//        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE BEGIN");
//        _pStringBoard02->update(200, 250, "YOKUKITANA!");
//        _frame_Begin = 0;
//    } else if (getProgress() == GAMEBEGINNING_SCENE_PROG_BEGIN) {
//        //�������[�v
//        _frame_Begin++;
//
//        if (_frame_Begin == 120) {
//            changeProgress(GAMEBEGINNING_SCENE_PROG_OPE); //���@�I��
//        }
//    }
//
//    //�Q�[���J�n���O�̎��@�I��
//    if (onActiveProgress(GAMEBEGINNING_SCENE_PROG_OPE)) {
//        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE OPE");
//        _pStringBoard02->update(200, 250, "SELECT YOUR EQ!");
//        _frame_Ope = 0;
//    } else if (getProgress() == GAMEBEGINNING_SCENE_PROG_OPE) {
//        //�������[�v
//        _frame_Ope++;
//
//        if (VB->isPushedDown(VB_UI_EXECUTE)) {
//            _selected_stage += 1; //�e�X�g
//            changeProgress(GAMEBEGINNING_SCENE_PROG_DECIDE);
//        }
//    }
//
//    //�Q�[���J�n���O�̎��@�I�𓙁A�����̃t�F�[�h�A�E�g��
//    if (onActiveProgress(GAMEBEGINNING_SCENE_PROG_DECIDE)) {
//        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE DECIDE");
//        _pStringBoard02->update(200, 250, "OK. ARE YOU READY!");
//        _frame_Decide = 0;
//    } else if (getProgress() == GAMEBEGINNING_SCENE_PROG_DECIDE) {
//        //�������[�v
//        _frame_Decide++;
//
//        if (_frame_Decide == 60*5) { //5�b�i�����ŃX�e�[�W������Ă�͂�
//            changeProgress(GAMEBEGINNING_SCENE_PROG_END); //���I��
//        }
//    }
//
//    if (onActiveProgress(GAMEBEGINNING_SCENE_PROG_END)) {
//        _pStringBoard01->update(200, 200, "GAME_BEGINNING_SCENE END");
//        _pStringBoard02->update(200, 250, "GOOD LUCK");
//        inactivateDelay(140);
//    }
}

void GameBeginningScene::processFinal() {
}

GameBeginningScene::~GameBeginningScene() {
}
