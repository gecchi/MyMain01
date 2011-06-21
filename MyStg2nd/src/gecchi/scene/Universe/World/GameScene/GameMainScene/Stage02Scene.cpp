#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage02Scene::Stage02Scene(const char* prm_name) : StageScene(prm_name) {
    _class_name = "Stage02Scene";

    _pScene_Stage02Controller = NEW Stage02Controller("Stage02Ctrl");
    _pScene_Stage02Controller->inactivate();
    addSubLast(_pScene_Stage02Controller);
    Sleep(2);
    _pWorldBoundSpace  = NEW WorldBoundSpace002("BG_SPACE_TEST");
    _pWorldBoundSpace->inactivateTree();
    getLordActor()->addSubGroup(KIND_EFFECT, _pWorldBoundSpace);

    _pHoshiBoshi = NEW HoshiBoshi001("HoshiBoshi001");
    getLordActor()->addSubGroup(KIND_EFFECT, _pHoshiBoshi);


    _pMessage = NEW LabelGecchi16Font("Stage02Msg");
    getLordActor()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

    fadeoutScene(0); //最初は非表示
    useProgress(10);
}

void Stage02Scene::initialize() {
    StageScene::initialize();
}

void Stage02Scene::processBehavior() {
    StageScene::processBehavior();
    if (_pProg->get() == STAGE_SCENE_PROG_INIT) {
       _pProg->change(STAGE_SCENE_PROG_BEGIN);
    }

    if (_pProg->get() == STAGE_SCENE_PROG_BEGIN) {
        if (_frame_Begin == 180) { //ステージ2開始！
            _pMessage->activateImmediately();
            _pMessage->update(300*1000, 300*1000, "SCENE 02 START!");
            _pMessage->inactivateDelay(240);
            _pWorldBoundSpace->activateTree();
            _pScene_Stage02Controller->activate();
            fadeinScene(240);
            _pProg->change(STAGE_SCENE_PROG_PLAYING);
        }
    }

    if (_pProg->isJustChangedTo(STAGE_SCENE_PROG_END)) {
        _TRACE_("Stage02Scene::processBehavior()  STAGE_SCENE_PROG_ENDになりますた！");
        _pMessage->activateImmediately();
        _pMessage->update(300*1000, 300*1000, "SCENE 02 CLEAR!!");
        _pMessage->inactivateDelay(120);
        fadeoutScene(120);
    }
}

void Stage02Scene::processJudgement() {
}

void Stage02Scene::processFinal() {
}

void Stage02Scene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STAGE02CONTROLLER_WAS_END ) {
        _TRACE_("Stage02Scene::onCatchEvent() STAGEXXCONTROLLER_ENDING をキャッチ。ステータスをSTAGE_SCENE_PROG_ENDへ");
        _pProg->change(STAGE_SCENE_PROG_END);
    } else {

    }
}


Stage02Scene::~Stage02Scene() {

}
