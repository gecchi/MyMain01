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
    _pTitleBoard->inactivateImmediately();
    getLordActor()->addSubGroup(_pTitleBoard);

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");
}
void GameTitleScene::reset() {
    _TRACE_("GameTitleScene::reset()");
    _pTitleBoard->inactivate();
    changeProgress(GAMETITLE_SCENE_PROG_INIT);
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
        changeProgress(GAMETITLE_SCENE_PROG_PRE_TITLE);
    }
    if (onInactiveProgress(GAMETITLE_SCENE_PROG_INIT)) {
        _TRACE_("GameTitleScene onInactiveProgress(GAMETITLE_SCENE_PROG_INIT)");
    }


    //�^�C�g���O�f�� GAMETITLE_SCENE_PROG_PRE_TITLE ���̏���
    if (onActiveProgress(GAMETITLE_SCENE_PROG_PRE_TITLE)) {
        closeCurtainTree();
        fadeinSceneTree(100);
        _TRACE_("GameTitleScene onActiveProgress(GAMETITLE_SCENE_PROG_PRE_TITLE)");
    }
    if (getProgress() == GAMETITLE_SCENE_PROG_PRE_TITLE) {
        if (getActivePartFrameInProgress() == 1) {
            _pStringBoard01->update(100, 50, "[STORY]");
        } else if (getActivePartFrameInProgress() == 120) {
            _pStringBoard01->update(100, 50, "MUKASHI MUKASHI ARU TOKORONI.");
        } else if (getActivePartFrameInProgress() == 240) {
            _pStringBoard01->update(100, 50, "MA SORE HA OITOITE...");
        } else if (getActivePartFrameInProgress() == 360) {
            _pStringBoard01->update(100, 50, "TORIAEZU TEKI WO TAOSINI IKOUZE !");
        } else if (getActivePartFrameInProgress() == 480) {
            _pStringBoard01->update(100, 50, "GANBARE!!! BY GECCHI");
        } else if (getActivePartFrameInProgress() == 600) {
            _pTitleBoard->activate();
            _pTitleBoard->changeProgress(TITLEBOARD_PROG_INIT); //�v�����o����^�C�g���\��
        }

        //�^�C�g���\���A�j���[�V�����I���Ń^�C�g����
        if (_pTitleBoard->onActiveProgress(TITLEBOARD_PROG_DISP)) {
            changeProgress(GAMEDEMO_SCENE_PROG_TITLE);
        }

        //VB_UI_EXECUTE�ő��^�C�g����
        if (VB->isPushedDown(VB_UI_EXECUTE)) {
            changeProgress(GAMEDEMO_SCENE_PROG_TITLE);
        }
    }
    if (onInactiveProgress(GAMETITLE_SCENE_PROG_PRE_TITLE)) {
        _TRACE_("GameTitleScene onInactiveProgress(GAMETITLE_SCENE_PROG_PRE_TITLE)");
        _pStringBoard01->update(100, 50, "");
    }

    //�^�C�g�� GAMETITLE_SCENE_PROG_TITLE ���̏���
    if (onActiveProgress(GAMETITLE_SCENE_PROG_TITLE)) {
        _TRACE_("GameTitleScene onActiveProgress(GAMETITLE_SCENE_PROG_TITLE)");
         _pTitleBoard->activate();
         _pTitleBoard->changeProgress(TITLEBOARD_PROG_DISP); //�^�C�g�������\��

        _pStringBoard02->update(400, 500, "PUSH UI_EXECUTE TO START!");
    }
    if (getProgress() == GAMETITLE_SCENE_PROG_TITLE) {
        //�Q�[���X�^�[�g�I
        if (VB->isPushedDown(VB_UI_EXECUTE)) {
            _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLE_SCENE_GAMESTART)");
            throwEventToUpperTree(EVENT_GAMETITLE_SCENE_GAMESTART);
            changeProgress(GAMETITLE_SCENE_PROG_FINISH); //�^�C�g���V�[���I��
        }

        //�{�[���ƌ��Ă��ꍇ
        if (getActivePartFrameInProgress() == 240) {
            _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH)");
            throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH);
            changeProgress(GAMETITLE_SCENE_PROG_FINISH); //�^�C�g���V�[���I��
        }
    }
    if (onInactiveProgress(GAMETITLE_SCENE_PROG_TITLE)) {
        _TRACE_("GameTitleScene onInactiveProgress(GAMETITLE_SCENE_PROG_TITLE)");
        fadeoutSceneTree(100);
        inactivateDelay(100);
        _pTitleBoard->inactivateDelay(100);
    }

    //GAMETITLE_SCENE_PROG_FINISH �����܂�
    if (onActiveProgress(GAMETITLE_SCENE_PROG_FINISH)) {
        _TRACE_("GameTitleScene throwEventToUpperTree(GAMETITLE_SCENE_PROG_FINISH)");
    }
    if (getProgress() == GAMETITLE_SCENE_PROG_FINISH) {
    }
    if (onInactiveProgress(GAMETITLE_SCENE_PROG_FINISH)) {
    }


}

void GameTitleScene::processFinal() {

}

GameTitleScene::~GameTitleScene() {
}
