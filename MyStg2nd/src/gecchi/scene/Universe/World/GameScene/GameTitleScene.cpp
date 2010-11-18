#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameTitleScene::GameTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GameTitleScene";
    useProgress(10);
    _pProgress->change(GAMEDEMO_SCENE_PROG_INIT);
    _pStringBoard01 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(_pStringBoard01);
    _pStringBoard02 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(_pStringBoard02);
    _pTitleBoard = NEW TitleBoard("TitleBoard");
    getLordActor()->addSubGroup(_pTitleBoard);

    _pBgmPerformer->useBgm(1);
    _pBgmPerformer->set(0, "BGM_DEMO");

}
void GameTitleScene::reset() {
    _TRACE_("GameTitleScene::reset()");
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    _pTitleBoard->setCoordinate(200, 150);
    _pProgress->change(GAMETITLE_SCENE_PROG_INIT);
    unblindScene();
}

void GameTitleScene::onActive() {
}

void GameTitleScene::initialize() {
    _TRACE_("GameTitleScene::initialize()");
    reset();
}

void GameTitleScene::processBehavior() {

    switch (_pProgress->getChangedFrom()) {
        default:
            break;
    }


    switch (_pProgress->get()) {
        case GAMETITLE_SCENE_PROG_INIT:
            _pProgress->change(GAMETITLE_SCENE_PROG_TITLE);
            break;

        case GAMETITLE_SCENE_PROG_TITLE:
            if (_pProgress->isJustChanged()) {
                _pStringBoard02->update(400, 500, "PUSH UI_EXECUTE TO START!");
            }
            if (VB->isPushedDown(VB_UI_EXECUTE)) {
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMESTART)");
                _pProgress->change(GAMETITLE_SCENE_PROG_GAMESTART);
            } else if (_pProgress->getActivePartFrameInProgress() == 240) {
                //�{�[���ƌ��Ă��ꍇ
                _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH)");
                throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH); //���ʂɏI���C�x���g
                _pProgress->change(GAMETITLE_SCENE_PROG_FINISH); //�^�C�g���V�[���I����
            }
            break;

        case GAMETITLE_SCENE_PROG_GAMESTART:
            if (_pProgress->isJustChanged()) {
            }
            if (_pProgress->getActivePartFrameInProgress() == 90) {
                throwEventToUpperTree(EVENT_GAMESTART);      //�X�^�[�g�łɏI���C�x���g
                _pProgress->change(GAMETITLE_SCENE_PROG_FINISH); //�^�C�g���V�[���I����
            }
            //�_��
            if (_pProgress->getActivePartFrameInProgress() % 10 < 5 ) {
                _pStringBoard02->update(400, 500, "READY GO!");
            } else {
                _pStringBoard02->update(400, 500, "");
            }
            break;

        case GAMETITLE_SCENE_PROG_FINISH:
            if (_pProgress->isJustChanged()) {
                fadeoutSceneTree(FADE_FRAME);
                inactivateDelay(FADE_FRAME);
            }
            //�����܂��҂��ڂ������[�v
            break;

        default:
            break;
    }


//
//
//
//
//
//    //GAMETITLE_SCENE_PROG_INIT ���̏���
//    if (_pProgress->wasChangedTo(GAMETITLE_SCENE_PROG_INIT)) {
//        _TRACE_("GameTitleScene _pProgress->wasChangedTo(GAMETITLE_SCENE_PROG_INIT)");
//    }
//    if (_pProgress->get() == GAMETITLE_SCENE_PROG_INIT) {
//        _pProgress->change(GAMETITLE_SCENE_PROG_TITLE);
//    }
//    if (_pProgress->wasChangedFrom(GAMETITLE_SCENE_PROG_INIT)) {
//        _TRACE_("GameTitleScene _pProgress->wasChangedFrom(GAMETITLE_SCENE_PROG_INIT)");
//    }
//
//
//    //�^�C�g�� GAMETITLE_SCENE_PROG_TITLE ���̏���
//    if (_pProgress->wasChangedTo(GAMETITLE_SCENE_PROG_TITLE)) {
//        _TRACE_("GameTitleScene _pProgress->wasChangedTo(GAMETITLE_SCENE_PROG_TITLE)");
//        _pStringBoard02->update(400, 500, "PUSH UI_EXECUTE TO START!");
//    }
//    if (_pProgress->get() == GAMETITLE_SCENE_PROG_TITLE) {
//
//        if (VB->isPushedDown(VB_UI_EXECUTE)) {
//            _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMESTART)");
//            _pProgress->change(GAMETITLE_SCENE_PROG_GAMESTART);
//        } else if (_pProgress->getActivePartFrameInProgress() == 240) {
//            //�{�[���ƌ��Ă��ꍇ
//            _TRACE_("GameTitleScene throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH)");
//            throwEventToUpperTree(EVENT_GAMETITLE_SCENE_FINISH); //���ʂɏI���C�x���g
//            _pProgress->change(GAMETITLE_SCENE_PROG_FINISH); //�^�C�g���V�[���I����
//        }
//    }
//    if (_pProgress->wasChangedFrom(GAMETITLE_SCENE_PROG_TITLE)) {
//        _TRACE_("GameTitleScene _pProgress->wasChangedFrom(GAMETITLE_SCENE_PROG_TITLE)");
//    }
//
//    //GAMETITLE_SCENE_PROG_GAMESTART
//    if (_pProgress->wasChangedTo(GAMETITLE_SCENE_PROG_GAMESTART)) {
//        _TRACE_("GameTitleScene throwEventToUpperTree(GAMETITLE_SCENE_PROG_GAMESTART)");
//    }
//    if (_pProgress->get() == GAMETITLE_SCENE_PROG_GAMESTART) {
//        if (_pProgress->getActivePartFrameInProgress() == 90) {
//            throwEventToUpperTree(EVENT_GAMESTART);      //�X�^�[�g�łɏI���C�x���g
//            _pProgress->change(GAMETITLE_SCENE_PROG_FINISH); //�^�C�g���V�[���I����
//        }
//        //�_��
//        if (_pProgress->getActivePartFrameInProgress() % 10 < 5 ) {
//            _pStringBoard02->update(400, 500, "READY GO!");
//        } else {
//            _pStringBoard02->update(400, 500, "");
//        }
//    }
//    if (_pProgress->wasChangedFrom(GAMETITLE_SCENE_PROG_GAMESTART)) {
//    }
//
//    //GAMETITLE_SCENE_PROG_FINISH �����܂�
//    if (_pProgress->wasChangedTo(GAMETITLE_SCENE_PROG_FINISH)) {
//        _TRACE_("GameTitleScene throwEventToUpperTree(GAMETITLE_SCENE_PROG_FINISH)");
//        fadeoutSceneTree(FADE_FRAME);
//        inactivateDelay(FADE_FRAME);
//    }
//    if (_pProgress->get() == GAMETITLE_SCENE_PROG_FINISH) {
//        //�����܂��҂��ڂ������[�v
//    }
//    if (_pProgress->wasChangedFrom(GAMETITLE_SCENE_PROG_FINISH)) {
//    }


}

void GameTitleScene::processFinal() {

}

GameTitleScene::~GameTitleScene() {
}
