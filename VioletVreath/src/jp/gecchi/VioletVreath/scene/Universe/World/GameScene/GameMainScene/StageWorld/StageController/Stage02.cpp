#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Stage02::Stage02(const char* prm_name) : Stage(prm_name) {
    _class_name = "Stage02";

    pScene_Stage02PartCtrlr_ = NEW Stage02PartController("Stage02Ctrl");
    pScene_Stage02PartCtrlr_->inactivate();
    addSubLast(pScene_Stage02PartCtrlr_);
    Sleep(2);
    pWorldBoundSpace_  = NEW WorldBoundSpace002("BG_SPACE_TEST");
    getDirector()->addSubGroup(KIND_EFFECT, pWorldBoundSpace_);

    pHoshiBoshi_ = NEW HoshiBoshi001("HoshiBoshi001");
    getDirector()->addSubGroup(KIND_EFFECT, pHoshiBoshi_);

    pMessage_ = NEW LabelGecchi16Font("Stage02Msg");
    getDirector()->addSubGroup(KIND_EFFECT, pMessage_);
    pMessage_->inactivate();

    fadeoutScene(0); //最初は非表示
    useProgress(10);
}

void Stage02::initialize() {
    Stage::initialize();
    CmRandomNumberGenerator::getInstance()->changeSeed(P_MYSHIP->_Y);
}

void Stage02::processBehavior() {
    Stage::processBehavior();
    if (_pProg->get() == Stage::PROG_INIT) {
       _pProg->change(Stage::PROG_BEGIN);
    }

    if (_pProg->get() == Stage::PROG_BEGIN) {
        if (_pProg->getFrameInProgress() == 180) { //ステージ2開始！
            pMessage_->activateImmed();
            pMessage_->update(300*1000, 300*1000, "SCENE 02 START!");
            pMessage_->inactivateDelay(240);
            pWorldBoundSpace_->activateTree();
            pScene_Stage02PartCtrlr_->activate();
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
            pMessage_->activateImmed();
            pMessage_->update(300*1000, 300*1000, "SCENE 02 CLEAR!!");
            pMessage_->inactivateDelay(120);
            fadeoutScene(300);
        }
        if (_pProg->getFrameInProgress() == 300) {
            throwEventToUpperTree(EVENT_STG02_WAS_END);
        }
    }
}

void Stage02::processJudgement() {
}

void Stage02::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == EVENT_STG02_CTRLER_WAS_END ) {
        _TRACE_("Stage02::onCatchEvent() STAGEXXCONTROLLER_ENDING をキャッチ。ステータスをStage::PROG_ENDへ");
        pScene_Stage02PartCtrlr_->end(60*60);
        _pProg->change(Stage::PROG_END);
    } else {

    }
}


Stage02::~Stage02() {

}
