#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Stage02Scene::Stage02Scene(const char* prm_name) : StageScene(prm_name) {
    _class_name = "Stage02Scene";

    _pScene_Stage02Controller = NEW Stage02Controller("Stage02Ctrl");
    _pScene_Stage02Controller->inactivate();
    addSubLast(_pScene_Stage02Controller);
    Sleep(2);
    _pWorldBoundSpace  = NEW WorldBoundSpace002("BG_SPACE_TEST");
    _pWorldBoundSpace->inactivateTree();
    getDirector()->addSubGroup(KIND_EFFECT, _pWorldBoundSpace);

    _pHoshiBoshi = NEW HoshiBoshi001("HoshiBoshi001");
    getDirector()->addSubGroup(KIND_EFFECT, _pHoshiBoshi);


    _pMessage = NEW LabelGecchi16Font("Stage02Msg");
    getDirector()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

    fadeoutScene(0); //最初は非表示
    useProgress(10);
}

void Stage02Scene::initialize() {
    StageScene::initialize();
}

void Stage02Scene::processBehavior() {
    StageScene::processBehavior();
    if (_pProg->get() == STAGESCENE_PROG_INIT) {
       _pProg->change(STAGESCENE_PROG_BEGIN);
    }

    if (_pProg->get() == STAGESCENE_PROG_BEGIN) {
        if (_pProg->getFrameInProgress() == 180) { //ステージ2開始！
            _pMessage->activateImmediately();
            _pMessage->update(300*1000, 300*1000, "SCENE 02 START!");
            _pMessage->inactivateDelay(240);
            _pWorldBoundSpace->activateTree();
            _pScene_Stage02Controller->activate();
            fadeinScene(240);
            _pProg->change(STAGESCENE_PROG_PLAYING);
        }
    }

    if (_pProg->get() == STAGESCENE_PROG_END) {
        if (_pProg->isJustChanged()) {
            _TRACE_("Stage01Scene::processBehavior()  STAGESCENE_PROG_ENDになりますた！");
            throwEventToUpperTree(EVENT_PREPARE_NEXT_STAGE, this); //次ステージ準備へ
        }

        if (_pProg->getFrameInProgress() == 60) {
            _pMessage->activateImmediately();
            _pMessage->update(300*1000, 300*1000, "SCENE 02 CLEAR!!");
            _pMessage->inactivateDelay(120);
            fadeoutScene(300);
        }
        if (_pProg->getFrameInProgress() == 300) {
            throwEventToUpperTree(EVENT_STAGE02_WAS_END);
        }
    }
}

void Stage02Scene::processJudgement() {
}

void Stage02Scene::processFinal() {
}

void Stage02Scene::onCatchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STAGE02_CONTROLLER_WAS_END ) {
        _TRACE_("Stage02Scene::onCatchEvent() STAGEXXCONTROLLER_ENDING をキャッチ。ステータスをSTAGESCENE_PROG_ENDへ");
        _pScene_Stage02Controller->end(60*60);
        _pProg->change(STAGESCENE_PROG_END);
    } else {

    }


}


Stage02Scene::~Stage02Scene() {

}
