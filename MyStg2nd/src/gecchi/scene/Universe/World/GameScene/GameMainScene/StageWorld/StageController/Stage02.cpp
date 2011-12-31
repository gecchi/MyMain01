#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Stage02::Stage02(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage02";

    _pScene_Stage02PartController = NEW Stage02PartController("Stage02Ctrl");
    _pScene_Stage02PartController->inactivate();
    addSubLast(_pScene_Stage02PartController);
    Sleep(2);
    _pWorldBoundSpace  = NEW WorldBoundSpace002("BG_SPACE_TEST");
    getDirector()->addSubGroup(KIND_EFFECT, _pWorldBoundSpace);

    _pHoshiBoshi = NEW HoshiBoshi001("HoshiBoshi001");
    getDirector()->addSubGroup(KIND_EFFECT, _pHoshiBoshi);

    _pMessage = NEW LabelGecchi16Font("Stage02Msg");
    getDirector()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

    fadeoutScene(0); //最初は非表示
    useProgress(10);
}

void Stage02::initialize() {
    Stage::initialize();
}

void Stage02::processBehavior() {
    Stage::processBehavior();
    if (_pProg->get() == Stage::PROG_INIT) {
       _pProg->change(Stage::PROG_BEGIN);
    }

    if (_pProg->get() == Stage::PROG_BEGIN) {
        if (_pProg->getFrameInProgress() == 180) { //ステージ2開始！
            _pMessage->activateImmed();
            _pMessage->update(300*1000, 300*1000, "SCENE 02 START!");
            _pMessage->inactivateDelay(240);
            _pWorldBoundSpace->activateTree();
            _pScene_Stage02PartController->activate();
            fadeinScene(240);
            _pProg->change(Stage::PROG_PLAYING);
        }
    }

    if (_pProg->get() == Stage::PROG_END) {
        if (_pProg->isJustChanged()) {
            _TRACE_("Stage01::processBehavior()  Stage::PROG_ENDになりますた！");
            throwEventToUpperTree(EVENT_PREPARE_TRANSIT_STAGE, this); //通過ステージ準備へ
        }

        if (_pProg->getFrameInProgress() == 60) {
            _pMessage->activateImmed();
            _pMessage->update(300*1000, 300*1000, "SCENE 02 CLEAR!!");
            _pMessage->inactivateDelay(120);
            fadeoutScene(300);
        }
        if (_pProg->getFrameInProgress() == 300) {
            throwEventToUpperTree(EVENT_STG02_WAS_END);
        }
    }
}

void Stage02::processJudgement() {
}

void Stage02::processFinal() {
}

void Stage02::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG02_CONTROLLER_WAS_END ) {
        _TRACE_("Stage02::onCatchEvent() STAGEXXCONTROLLER_ENDING をキャッチ。ステータスをStage::PROG_ENDへ");
        _pScene_Stage02PartController->end(60*60);
        _pProg->change(Stage::PROG_END);
    } else {

    }


}


Stage02::~Stage02() {

}
