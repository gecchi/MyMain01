#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameTitleScene::GameTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameTitleScene";

    changeProgress(GAMEDEMO_SCENE_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(_pStringBoard02);
    _pTitleBoard = NEW TitleBoard("TitleBoard");
    _pTitleBoard->setCoordinate(200, 150);
    getLordActor()->addSubGroup(_pTitleBoard);

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");
}
void GameTitleScene::reset() {
    _TRACE_("GameTitleScene::reset()");
    changeProgress(GAMETITLE_SCENE_PROG_INIT);
    unblindScene();
}

void GameTitleScene::onActive() {
    reset();
}

void GameTitleScene::initialize() {
}

void GameTitleScene::processBehavior() {

    //GAMETITLE_SCENE_PROG_INIT ���̏���
    if (onActiveProgress(GAMETITLE_SCENE_PROG_INIT)) {
        _TRACE_("GameTitleScene onActiveProgress(GAMETITLE_SCENE_PROG_INIT)");
    }
    if (getProgress() == GAMETITLE_SCENE_PROG_INIT) {
        changeProgress(GAMETITLE_SCENE_PROG_TITLE);
    }
    if (onInactiveProgress(GAMETITLE_SCENE_PROG_INIT)) {
        _TRACE_("GameTitleScene onInactiveProgress(GAMETITLE_SCENE_PROG_INIT)");
    }


    //�^�C�g�� GAMETITLE_SCENE_PROG_TITLE ���̏���
    if (onActiveProgress(GAMETITLE_SCENE_PROG_TITLE)) {
        _TRACE_("GameTitleScene onActiveProgress(GAMETITLE_SCENE_PROG_TITLE)");
        _pStringBoard02->update(400, 500, "PUSH UI_EXECUTE TO START!");
    }
    if (getProgress() == GAMETITLE_SCENE_PROG_TITLE) {

        if (VB->isPushedDown(VB_UI_EXECUTE)) {
            _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMESTART)");
            changeProgress(GAMETITLE_SCENE_PROG_GAMESTART);
        } else if (getActivePartFrameInProgress() == 240) {
            //�{�[���ƌ��Ă��ꍇ
            _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH)");
            throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH); //���ʂɏI���C�x���g
            changeProgress(GAMETITLE_SCENE_PROG_FINISH); //�^�C�g���V�[���I����
        }
    }
    if (onInactiveProgress(GAMETITLE_SCENE_PROG_TITLE)) {
        _TRACE_("GameTitleScene onInactiveProgress(GAMETITLE_SCENE_PROG_TITLE)");
    }

    //GAMETITLE_SCENE_PROG_GAMESTART
    if (onActiveProgress(GAMETITLE_SCENE_PROG_GAMESTART)) {
        _TRACE_("GameTitleScene throwEventToUpperTree(GAMETITLE_SCENE_PROG_GAMESTART)");

    }
    if (getProgress() == GAMETITLE_SCENE_PROG_GAMESTART) {
        if (getActivePartFrameInProgress() == 90) {
            throwEventToUpperTree(EVENT_GAMESTART);      //�X�^�[�g�łɏI���C�x���g
            changeProgress(GAMETITLE_SCENE_PROG_FINISH); //�^�C�g���V�[���I����
        }
        //�_��
        if (getActivePartFrameInProgress() % 10 < 5 ) {
            _pStringBoard02->update(400, 500, "READY GO!");
        } else {
            _pStringBoard02->update(400, 500, "");
        }
    }
    if (onInactiveProgress(GAMETITLE_SCENE_PROG_GAMESTART)) {
    }

    //GAMETITLE_SCENE_PROG_FINISH �����܂�
    if (onActiveProgress(GAMETITLE_SCENE_PROG_FINISH)) {
        _TRACE_("GameTitleScene throwEventToUpperTree(GAMETITLE_SCENE_PROG_FINISH)");
        fadeoutSceneTree(FADE_FRAME);
    }
    if (getProgress() == GAMETITLE_SCENE_PROG_FINISH) {
        //�����܂��҂��ڂ������[�v
    }
    if (onInactiveProgress(GAMETITLE_SCENE_PROG_FINISH)) {
    }


}

void GameTitleScene::processFinal() {

}

GameTitleScene::~GameTitleScene() {
}
