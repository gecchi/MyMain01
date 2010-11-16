#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GamePreTitleScene::GamePreTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GamePreTitleScene";

    changeProgress(GAMEDEMO_SCENE_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(_pStringBoard02);
    _pTitleBoard = NEW TitleBoard("TitleBoard");
    getLordActor()->addSubGroup(_pTitleBoard);

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");
}
void GamePreTitleScene::reset() {
    _TRACE_("GamePreTitleScene::reset()");
    _pTitleBoard->setCoordinate(200, 600);
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    changeProgress(GAMEPRETITLE_SCENE_PROG_INIT);
}

void GamePreTitleScene::onActive() {
    reset();
}

void GamePreTitleScene::initialize() {
}

void GamePreTitleScene::processBehavior() {

    //GAMEPRETITLE_SCENE_PROG_INIT ���̏���
    if (onActiveProgress(GAMEPRETITLE_SCENE_PROG_INIT)) {
        _TRACE_("GamePreTitleScene onActiveProgress(GAMEPRETITLE_SCENE_PROG_INIT)");
    }
    if (getProgress() == GAMEPRETITLE_SCENE_PROG_INIT) {
        changeProgress(GAMEPRETITLE_SCENE_PROG_EXEC);
    }
    if (onInactiveProgress(GAMEPRETITLE_SCENE_PROG_INIT)) {
        _TRACE_("GamePreTitleScene onInactiveProgress(GAMEPRETITLE_SCENE_PROG_INIT)");
    }


    //�^�C�g���O�f�� GAMEPRETITLE_SCENE_PROG_EXEC ���̏���
    if (onActiveProgress(GAMEPRETITLE_SCENE_PROG_EXEC)) {
        blindSceneTree();
        fadeinSceneTree(FADE_FRAME);
        _TRACE_("GamePreTitleScene onActiveProgress(GAMEPRETITLE_SCENE_PROG_EXEC)");
    }
    if (getProgress() == GAMEPRETITLE_SCENE_PROG_EXEC) {
        if (getActivePartFrameInProgress() == 1) {
            _pStringBoard01->update(100, 50, "[STORY]");
        } else if (getActivePartFrameInProgress() == 120) {
            _pStringBoard01->update(100, 50, "MUKASHI MUKASHI ARU TOKORONI.");
        } else if (getActivePartFrameInProgress() == 240) {
            _pStringBoard01->update(100, 50, "MA SORE HA OITOITE...");
        } else if (getActivePartFrameInProgress() == 360) {
            _pStringBoard01->update(100, 50, "TORIAEZU TEKI WO TAOSINI IKOUZE ! BY GECCHI");
        } else if (getActivePartFrameInProgress() > 600) {
            //�^�C�g����������j���[����
            _pTitleBoard->_y -= 2;
            if (_pTitleBoard->_y <= 150) {
                throwEventToUpperTree(EVENT_PREGAMETITLE_SCENE_FINISH);
                changeProgress(GAMEPRETITLE_SCENE_PROG_FINISH);
            }
        }
    }
    if (onInactiveProgress(GAMEPRETITLE_SCENE_PROG_EXEC)) {
        _TRACE_("GamePreTitleScene onInactiveProgress(GAMEPRETITLE_SCENE_PROG_EXEC)");
    }

    //GAMEPRETITLE_SCENE_PROG_FINISH �����܂�
    if (onActiveProgress(GAMEPRETITLE_SCENE_PROG_FINISH)) {
        _TRACE_("GamePreTitleScene throwEventToUpperTree(GAMEPRETITLE_SCENE_PROG_FINISH)");
        inactivate();
    }
    if (getProgress() == GAMEPRETITLE_SCENE_PROG_FINISH) {
        //�����܂��҂��ڂ������[�v
    }
    if (onInactiveProgress(GAMEPRETITLE_SCENE_PROG_FINISH)) {
    }


}

void GamePreTitleScene::processFinal() {

}

GamePreTitleScene::~GamePreTitleScene() {
}
