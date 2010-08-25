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

    //GameMainSceneが解除してくれる
    setProgress(STAGE02_PROG_INIT);

    _pMessage = NEW LabelGecchi16Font("Stage02Msg");
    getLordActor()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

}

void Stage02Scene::initialize() {
    setProgress(STAGE02_PROG_INIT);
}

void Stage02Scene::processBehavior() {


    if (onChangeProgressAt(STAGE02_PROG_INIT)) {
        //
    } else if (getProgress() == STAGE02_PROG_INIT) {
        addSubLast(pCOMMONSCENE->extract()); // 共通シーンを配下に移動（一時停止をうまく制御させるため！）
        setProgress(STAGE02_PROG_BEGIN);
    }

    if (onChangeProgressAt(STAGE02_PROG_BEGIN)) {
        _frame_Begin = 0;
    } else if (getProgress() == STAGE02_PROG_BEGIN) {
        //活動ループ
        _frame_Begin++;

        if (_frame_Begin == 180) { //ステージ2開始！
            _pMessage->activateImmediately();
            _pMessage->update(300, 300, "SCENE 02 START!");
            _pMessage->inactivateAfter(120);
            _pWorldBoundSpace001->activateTree();
            _pScene_Stage02Controller->activate();
            setProgress(STAGE02_PROG_PLAYING);
        }
    }

    if (onChangeProgressAt(STAGE02_PROG_PLAYING)) {
        _frame_Play = 0;
    } else if (getProgress() == STAGE02_PROG_PLAYING) {
        //活動ループ
        _frame_Play++;
    }

    if (onChangeProgressAt(STAGE02_PROG_END)) {
        _TRACE_("Stage02Scene::processBehavior()  STAGE02_PROG_ENDになりますた！");
        _pMessage->activateImmediately();
        _pMessage->update(300, 300, "SCENE 01 CLEAR!!");
        _pMessage->inactivateAfter(120);
        //_pScene_Stage02Controller
        throwUpEvent(READY_NEXT_STAGE, this); //次ステージ準備へ
    } else if (getProgress() == STAGE02_PROG_END) {

    }


}

void Stage02Scene::processJudgement() {
}

void Stage02Scene::processFinal() {

}


void Stage02Scene::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == STAGE02CONTROLLER_WAS_END) {
        _TRACE_("Stage02Scene::catchEvent() STAGE02CONTROLLER_ENDING をキャッチ");
        setProgress(STAGE02_PROG_END);
    } else {

    }
}

Stage02Scene::~Stage02Scene() {

}
