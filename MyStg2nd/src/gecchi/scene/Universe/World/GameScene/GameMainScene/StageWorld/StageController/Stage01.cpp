#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

Stage01::Stage01(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage01";

    _pScene_Stage01PartController = NEW Stage01PartController("Stage01Ctrl");
    _pScene_Stage01PartController->inactivate();
    addSubLast(_pScene_Stage01PartController);
    Sleep(2);
    _pWorldBoundSpace  = NEW WorldBoundSpace001("BG_SPACE");
    getDirector()->addSubGroup(_pWorldBoundSpace);

    _pHoshiBoshi = NEW HoshiBoshi001("HoshiBoshi001");
    getDirector()->addSubGroup(_pHoshiBoshi);

    _pMessage = NEW LabelGecchi16Font("Stage01Msg");
    getDirector()->addSubGroup(_pMessage);
    _pMessage->inactivate();


    _pPlanets = NEW Planets001("Planets001");
    getDirector()->addSubGroup(KIND_EFFECT, _pPlanets);

    fadeoutScene(0); //最初は非表示
    useProgress(10);
}

void Stage01::initialize() {
    Stage::initialize();
}

void Stage01::processBehavior() {
    Stage::processBehavior();

    switch (_pProg->get()) {
        case Stage::PROG_INIT: {
            _pProg->change(Stage::PROG_BEGIN);
            break;
        }
        case Stage::PROG_BEGIN: {
            if (_pProg->getFrameInProgress() == 180) { //ステージ１開始！
                _pMessage->activateImmed();
                _pWorldBoundSpace->activateTree();    //背景ON
                _pHoshiBoshi->activateTree();    //背景ON
                _pScene_Stage01PartController->activate();

                _pPlanets->activate();

                fadeinSceneTree(360);
                _pProg->change(Stage::PROG_PLAYING);
            }
            break;
        }
        case Stage::PROG_PLAYING: {
            if (_pProg->getFrameInProgress() == 60) { //ステージ１開始！
                _pMessage->update(PX2CO(300), PX2CO(300), "SCENE 01 START!");
                _pMessage->inactivateDelay(240);
            }
            //EVENT_STG01_CONTROLLER_WAS_ENDイベント待ち
            break;
        }
        case Stage::PROG_END: {
            if (_pProg->isJustChanged()) {
                _TRACE_("Stage01::processBehavior()  Stage::PROG_ENDになりますた！");
                throwEventToUpperTree(EVENT_PREPARE_TRANSIT_STAGE, this); //通過ステージ準備へ
            }

            if (_pProg->getFrameInProgress() == 60) {
                _pMessage->activateImmed();
                _pMessage->update(PX2CO(300), PX2CO(300), "SCENE 01 CLEAR!!");
                _pMessage->inactivateDelay(120);
                fadeoutScene(300);
            }
            if (_pProg->getFrameInProgress() == 300) {
                throwEventToUpperTree(EVENT_STG01_WAS_END);
            }


            break;
        }
        default:
            break;

    }

}

void Stage01::processJudgement() {
}

void Stage01::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG01_CONTROLLER_WAS_END ) {
        _TRACE_("Stage01::onCatchEvent() STAGEXXCONTROLLER_ENDING をキャッチ。ステータスをStage::PROG_ENDへ");
        _pScene_Stage01PartController->end(60*60);
        _pProg->change(Stage::PROG_END);
    } else {

    }
}


Stage01::~Stage01() {

}
