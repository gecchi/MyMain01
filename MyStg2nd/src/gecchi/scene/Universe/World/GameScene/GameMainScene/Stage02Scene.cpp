#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage02Scene::Stage02Scene(const char* prm_name) : StageScene(prm_name) {
    _pScene_Stage02Controller = NEW Stage02Controller("Stage02Ctrl");
    _pScene_Stage02Controller->inactivate();
    addSubLast(_pScene_Stage02Controller);
    Sleep(2);
    _pWorldBoundSpace001  = NEW WorldBoundSpace001("BG_SPACE");
    _pWorldBoundSpace001->inactivateTree();
    getLordActor()->addSubGroup(KIND_EFFECT, _pWorldBoundSpace001);

    _pHoshiBoshi001 = NEW HoshiBoshi001("HoshiBoshi001");
    getLordActor()->addSubGroup(KIND_EFFECT, _pHoshiBoshi001);


    _pMessage = NEW LabelGecchi16Font("Stage02Msg");
    getLordActor()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

}

void Stage02Scene::initialize() {
    StageScene::initialize();
}

void Stage02Scene::processBehavior() {
    StageScene::processBehavior();

    if (getProgress() == STAGE_PROG_BEGIN) {
        if (_frame_Begin == 180) { //ステージ2開始！
            _pMessage->activateImmediately();
            _pMessage->update(300, 300, "SCENE 02 START!");
            _pMessage->inactivateAfter(120);
            _pWorldBoundSpace001->activateTree();
            _pScene_Stage02Controller->activate();
            setProgress(STAGE_PROG_PLAYING);
        }
    }

    if (onChangeProgressAt(STAGE_PROG_END)) {
        _TRACE_("Stage02Scene::processBehavior()  STAGE_PROG_ENDになりますた！");
        _pMessage->activateImmediately();
        _pMessage->update(300, 300, "SCENE 01 CLEAR!!");
        _pMessage->inactivateAfter(120);
    }
}

void Stage02Scene::processJudgement() {
}

void Stage02Scene::processFinal() {
}

void Stage02Scene::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == STAGE02CONTROLLER_WAS_END ) {
        _TRACE_("Stage02Scene::catchEvent() STAGEXXCONTROLLER_ENDING をキャッチ。ステータスをSTAGE_PROG_ENDへ");
        setProgress(STAGE_PROG_END);
    } else {

    }
}


Stage02Scene::~Stage02Scene() {

}
