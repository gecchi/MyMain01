#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01Scene::Stage01Scene(const char* prm_name) : StageScene(prm_name) {
    _pScene_Stage01Controller = NEW Stage01Controller("Stage01Ctrl");
    _pScene_Stage01Controller->inactivate();
    addSubLast(_pScene_Stage01Controller);
    Sleep(2);
    _pWorldBoundSpace  = NEW WorldBoundSpace001("BG_SPACE");
    _pWorldBoundSpace->inactivateTree();
    getLordActor()->addSubGroup(KIND_EFFECT, _pWorldBoundSpace);

    _pHoshiBoshi = NEW HoshiBoshi001("HoshiBoshi001");
    getLordActor()->addSubGroup(KIND_EFFECT, _pHoshiBoshi);

    _pMessage = NEW LabelGecchi16Font("Stage01Msg");
    getLordActor()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

    fadeoutScene(0); //最初は非表示
}

void Stage01Scene::initialize() {
    StageScene::initialize();
}

void Stage01Scene::processBehavior() {
    StageScene::processBehavior();
    if (getProgress() == STAGE_PROG_INIT) {
       setProgress(STAGE_PROG_BEGIN);
    }

    if (getProgress() == STAGE_PROG_BEGIN) {
        if (_frame_Begin == 180) { //ステージ１開始！
            _pMessage->activateImmediately();
            _pMessage->update(300, 300, "SCENE 01 START!");
            _pMessage->inactivateAfter(240);
            _pWorldBoundSpace->activateTree();
            _pScene_Stage01Controller->activate();
            fadeinScene(240);
            setProgress(STAGE_PROG_PLAYING);
        }
    }

    if (onChangeProgressAt(STAGE_PROG_END)) {
        _TRACE_("Stage01Scene::processBehavior()  STAGE_PROG_ENDになりますた！");
        _pMessage->activateImmediately();
        _pMessage->update(300, 300, "SCENE 01 CLEAR!!");
        _pMessage->inactivateAfter(120);
        fadeoutScene(120);
    }

}

void Stage01Scene::processJudgement() {
}

void Stage01Scene::processFinal() {

}

void Stage01Scene::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == STAGE01CONTROLLER_WAS_END ) {
        _TRACE_("Stage01Scene::catchEvent() STAGEXXCONTROLLER_ENDING をキャッチ。ステータスをSTAGE_PROG_ENDへ");
        setProgress(STAGE_PROG_END);
    } else {

    }
}


Stage01Scene::~Stage01Scene() {

}
