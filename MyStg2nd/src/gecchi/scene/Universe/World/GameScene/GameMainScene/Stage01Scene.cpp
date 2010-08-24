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
    _pWorldBoundSpace001  = NEW WorldBoundSpace001("BG_SPACE");
    _pWorldBoundSpace001->inactivateTree();
    getLordActor()->addSubGroup(KIND_EFFECT, _pWorldBoundSpace001);

    _pHoshiBoshi001 = NEW HoshiBoshi001("HoshiBoshi001");
    getLordActor()->addSubGroup(KIND_EFFECT, _pHoshiBoshi001);

    //GameMainSceneが解除してくれる
    setProgress(STAGE01_PROG_INIT);

    _pMessage = NEW LabelGecchi16Font("Stage01Msg");
    getLordActor()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

}

void Stage01Scene::initialize() {
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::processBehavior() {


    if (getProgress() == STAGE01_PROG_INIT) {
        //
        setProgress(STAGE01_PROG_BEGIN);
    }

    if (onChangeProgressAt(STAGE01_PROG_BEGIN)) {
        _frame_Begin = 0;
    } else if (getProgress() == STAGE01_PROG_BEGIN) {
        //活動ループ
        _frame_Begin++;

        if (_frame_Begin == 180) { //ステージ１開始！
            _pMessage->activateImmediately();
            _pMessage->update(300, 300, "SCENE 01 START!");
            _pMessage->inactivateAfter(120);
            _pWorldBoundSpace001->activateTree();
            _pScene_Stage01Controller->activate();
            setProgress(STAGE01_PROG_PLAYING);
        }
    }

    if (onChangeProgressAt(STAGE01_PROG_PLAYING)) {
        _frame_Play = 0;
    } else if (getProgress() == STAGE01_PROG_PLAYING) {
        //活動ループ
        _frame_Play++;
    }

    if (onChangeProgressAt(STAGE01_PROG_END)) {
        _TRACE_("Stage01Scene::processBehavior()  STAGE01_PROG_ENDになりますた！");
        _pMessage->activateImmediately();
        _pMessage->update(300, 300, "SCENE 01 CLEAR!!");
        _pMessage->inactivateAfter(120);
        //_pScene_Stage01Controller
        throwUpEvent(READY_NEXT_STAGE, this); //次ステージ準備へ
    } else if (getProgress() == STAGE01_PROG_END) {

    }


}

void Stage01Scene::processJudgement() {
}

void Stage01Scene::processFinal() {

}


void Stage01Scene::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == STAGE01CONTROLLER_WAS_END) {
        _TRACE_("Stage01Scene::catchEvent() STAGE01CONTROLLER_ENDING をキャッチ");
        setProgress(STAGE01_PROG_END);
    } else {

    }
}

Stage01Scene::~Stage01Scene() {

}
