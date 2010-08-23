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
//    _pBackGround01 = NEW BackGround01("BACKGOROUND01", "");
//    _pBackGround01->inactivateTree();
//    getLordActor()->addSubGroup(KIND_EFFECT, _pBackGround01);
    _pWorldBoundSpace001  = NEW WorldBoundSpace001("BG_SPACE");
    _pWorldBoundSpace001->inactivateTree();
    getLordActor()->addSubGroup(KIND_EFFECT, _pWorldBoundSpace001);

    _pHoshiBoshi001 = NEW HoshiBoshi001("HoshiBoshi001");
    getLordActor()->addSubGroup(KIND_EFFECT, _pHoshiBoshi001);


    //GameMainSceneが解除してくれる
    setProgress(STAGE_PROG_INIT);

    _pMessage = NEW LabelGecchi16Font("Stage01Msg");
    getLordActor()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

}

void Stage01Scene::initialize() {
    setProgress(STAGE_PROG_INIT);
}

void Stage01Scene::processBehavior() {


    if (getProgress() == STAGE_PROG_INIT) {
        setProgress(STAGE_PROG_BEGIN);
    }


    if (onChangeProgressAt(STAGE_PROG_BEGIN)) {
        //playBgm(0, DSBVOLUME_MIN, true); //音量無し
        //fadeinBgm(0, 420);               //フェードイン
        _frame_Begin = 0;
    } else if (getProgress() == STAGE_PROG_BEGIN) {
        //活動ループ
        _frame_Begin++;

        if (_frame_Begin == 180) { //ステージ１開始！
            _pMessage->activateImmediately();
            _pMessage->update(300, 300, "SCENE 01 START!");
            _pMessage->inactivateAfter(120);
            _pWorldBoundSpace001->activateTree();
            _pScene_Stage01Controller->activate();
            setProgress(STAGE_PROG_PLAY);
        }
    }

    if (onChangeProgressAt(STAGE_PROG_PLAY)) {
        _frame_Play = 0;
    } else if (getProgress() == STAGE_PROG_PLAY) {
        //活動ループ
        _frame_Play++;
    }


    if (getActivePartFrame() == 60*60) {
        //fadeoutBgm(0, 420);

    }


    if (onChangeProgressAt(STAGE_PROG_END)) {
        _TRACE_("Stage01Scene::processBehavior()  STAGE_PROG_ENDになりますた！");
        _pMessage->activateImmediately();
        _pMessage->update(300, 300, "SCENE 01 CLEAR!!");
        _pMessage->inactivateAfter(120);
    } else if (getProgress() == STAGE_PROG_END) {

    }


}

void Stage01Scene::processJudgement() {
}

void Stage01Scene::processFinal() {

}

Stage01Scene::~Stage01Scene() {

}
