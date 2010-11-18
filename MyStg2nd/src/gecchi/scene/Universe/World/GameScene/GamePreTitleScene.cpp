#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GamePreTitleScene::GamePreTitleScene(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "GamePreTitleScene";
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
void GamePreTitleScene::reset() {
    _TRACE_("GamePreTitleScene::reset()");
    _pTitleBoard->setCoordinate(200, 600);
    _pStringBoard01->update("");
    _pStringBoard02->update("");
    blindScene();
    _pProgress->change(GAMEPRETITLE_SCENE_PROG_INIT);
}

void GamePreTitleScene::onActive() {
}

void GamePreTitleScene::initialize() {
    _TRACE_("GamePreTitleScene::initialize()");
    reset();
}

void GamePreTitleScene::processBehavior() {

    switch (_pProgress->getChangedFrom()) {
        default:
            break;
    }


    switch (_pProgress->get()) {
        case GAMEPRETITLE_SCENE_PROG_INIT:
            _pProgress->change(GAMEPRETITLE_SCENE_PROG_EXEC);
            break;

        case GAMEPRETITLE_SCENE_PROG_EXEC:
            if (_pProgress->isJustChanged()) {
                fadeinScene(FADE_FRAME);
            }
            if (_pProgress->getActivePartFrameInProgress() == 1) {
                _pStringBoard01->update(100, 50, "[STORY]");
            } else if (_pProgress->getActivePartFrameInProgress() == 120) {
                _pStringBoard01->update(100, 50, "MUKASHI MUKASHI ARU TOKORONI.");
            } else if (_pProgress->getActivePartFrameInProgress() == 240) {
                _pStringBoard01->update(100, 50, "MA SORE HA OITOITE...");
            } else if (_pProgress->getActivePartFrameInProgress() == 360) {
                _pStringBoard01->update(100, 50, "TORIAEZU TEKI WO TAOSINI IKOUZE ! BY GECCHI");
            } else if (_pProgress->getActivePartFrameInProgress() > 600) {
                //�^�C�g����������j���[����
                _pTitleBoard->_y -= 2;
                if (_pTitleBoard->_y <= 150) {
                    throwEventToUpperTree(EVENT_PREGAMETITLE_SCENE_FINISH);
                    _pProgress->change(GAMEPRETITLE_SCENE_PROG_FINISH);
                }
            }
            break;

        case GAMEPRETITLE_SCENE_PROG_FINISH:
            if (_pProgress->isJustChanged()) {
                inactivate();
            }
            //�����܂��҂��ڂ������[�v
            break;

        default:
             break;
     }


//    //GAMEPRETITLE_SCENE_PROG_INIT ���̏���
//    if (_pProgress->wasChangedTo(GAMEPRETITLE_SCENE_PROG_INIT)) {
//        _TRACE_("GamePreTitleScene _pProgress->wasChangedTo(GAMEPRETITLE_SCENE_PROG_INIT)");
//    }
//    if (_pProgress->get() == GAMEPRETITLE_SCENE_PROG_INIT) {
//        _pProgress->change(GAMEPRETITLE_SCENE_PROG_EXEC);
//    }
//    if (_pProgress->wasChangedFrom(GAMEPRETITLE_SCENE_PROG_INIT)) {
//        _TRACE_("GamePreTitleScene _pProgress->wasChangedFrom(GAMEPRETITLE_SCENE_PROG_INIT)");
//    }
//
//
//    //�^�C�g���O�f�� GAMEPRETITLE_SCENE_PROG_EXEC ���̏���
//    if (_pProgress->wasChangedTo(GAMEPRETITLE_SCENE_PROG_EXEC)) {
//        fadeinScene(FADE_FRAME);
//        _TRACE_("GamePreTitleScene _pProgress->wasChangedTo(GAMEPRETITLE_SCENE_PROG_EXEC)");
//    }
//    if (_pProgress->get() == GAMEPRETITLE_SCENE_PROG_EXEC) {
//        if (_pProgress->getActivePartFrameInProgress() == 1) {
//            _pStringBoard01->update(100, 50, "[STORY]");
//        } else if (_pProgress->getActivePartFrameInProgress() == 120) {
//            _pStringBoard01->update(100, 50, "MUKASHI MUKASHI ARU TOKORONI.");
//        } else if (_pProgress->getActivePartFrameInProgress() == 240) {
//            _pStringBoard01->update(100, 50, "MA SORE HA OITOITE...");
//        } else if (_pProgress->getActivePartFrameInProgress() == 360) {
//            _pStringBoard01->update(100, 50, "TORIAEZU TEKI WO TAOSINI IKOUZE ! BY GECCHI");
//        } else if (_pProgress->getActivePartFrameInProgress() > 600) {
//            //�^�C�g����������j���[����
//            _pTitleBoard->_y -= 2;
//            if (_pTitleBoard->_y <= 150) {
//                throwEventToUpperTree(EVENT_PREGAMETITLE_SCENE_FINISH);
//                _pProgress->change(GAMEPRETITLE_SCENE_PROG_FINISH);
//            }
//        }
//    }
//    if (_pProgress->wasChangedFrom(GAMEPRETITLE_SCENE_PROG_EXEC)) {
//        _TRACE_("GamePreTitleScene _pProgress->wasChangedFrom(GAMEPRETITLE_SCENE_PROG_EXEC)");
//    }
//
//    //GAMEPRETITLE_SCENE_PROG_FINISH �����܂�
//    if (_pProgress->wasChangedTo(GAMEPRETITLE_SCENE_PROG_FINISH)) {
//        _TRACE_("GamePreTitleScene throwEventToUpperTree(GAMEPRETITLE_SCENE_PROG_FINISH)");
//        inactivate();
//    }
//    if (_pProgress->get() == GAMEPRETITLE_SCENE_PROG_FINISH) {
//        //�����܂��҂��ڂ������[�v
//    }
//    if (_pProgress->wasChangedFrom(GAMEPRETITLE_SCENE_PROG_FINISH)) {
//    }


}

void GamePreTitleScene::processFinal() {

}

GamePreTitleScene::~GamePreTitleScene() {
}
