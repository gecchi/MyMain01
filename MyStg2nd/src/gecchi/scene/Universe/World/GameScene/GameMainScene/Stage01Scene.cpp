#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01Scene::Stage01Scene(const char* prm_name) : StageScene(prm_name) {
    _pScene_Stage01Main = NEW Stage01MainScene("Stage01Main");
    _pScene_Stage01Main->inactivate();
    addSubLast(_pScene_Stage01Main);
    Sleep(2);
//    _pBackGround01 = NEW BackGround01("BACKGOROUND01", "");
//    _pBackGround01->inactivateTree();
//    getLordActor()->addSubGroup(KIND_EFFECT, _pBackGround01);
    _pWorldBoundSpace001  = NEW WorldBoundSpace001("BG_SPACE");
    _pWorldBoundSpace001->inactivateTree();
    getLordActor()->addSubGroup(KIND_EFFECT, _pWorldBoundSpace001);

    _pHoshiBoshi001 = NEW HoshiBoshi001("HoshiBoshi001");
    getLordActor()->addSubGroup(KIND_EFFECT, _pHoshiBoshi001);

    _angCamZX_prev = 0;
    _angCamXY_prev = 0;

    //GameMainSceneが解除してくれる
    setProgress(STAGE01_PROG_INIT);

    _pBgmPerformer->useBgm(2);
    _pBgmPerformer->set(0, "VIRTUAL_ON_06");
    _pBgmPerformer->set(1, "PLANETES");

    _pMessage = NEW LabelGecchi16Font("Stage01Msg");
    getLordActor()->addSubGroup(KIND_EFFECT, _pMessage);
    _pMessage->inactivate();

}

void Stage01Scene::initialize() {
    _angCamZX_prev = GgafDx9Util::getAngle2D(-(pCAM->_pVecCamLookatPoint->x - pCAM->_pVecCamFromPoint->x),
                                                     -(pCAM->_pVecCamLookatPoint->z - pCAM->_pVecCamFromPoint->z)
                                                    );
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::processBehavior() {


    if (getProgress() == STAGE01_PROG_INIT) {
        setProgress(STAGE01_PROG_BEGIN);
    }


    if (onChangeProgressAt(STAGE01_PROG_BEGIN)) {
        _pBgmPerformer->play(0, DSBVOLUME_MIN, true); //音量無し
        _pBgmPerformer->fadein(0, 420);
        //playBgm(0, DSBVOLUME_MIN, true); //音量無し
        //fadeinBgm(0, 420);               //フェードイン
        _dwFrame_Begin = 0;
    } else if (getProgress() == STAGE01_PROG_BEGIN) {
        //活動ループ
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 180) { //ステージ１開始！
            _pMessage->activateImmediately();
            _pMessage->update(300, 300, "SCENE 01 START!");
            _pMessage->inactivateAfter(120);
            _pWorldBoundSpace001->activateTree();
            _pScene_Stage01Main->activate();
            setProgress(STAGE01_PROG_PLAY);
        }
    }

    if (onChangeProgressAt(STAGE01_PROG_PLAY)) {
        _dwFrame_Play = 0;
    } else if (getProgress() == STAGE01_PROG_PLAY) {
        //活動ループ
        _dwFrame_Play++;

    }



    if (getActivePartFrame() == 60*60) {

        _pBgmPerformer->fadeout_stop(0, 420);
        //fadeoutBgm(0, 420);

        _pBgmPerformer->play(1, DSBVOLUME_MIN, true);
        _pBgmPerformer->fadein(1, 420);
    }

}

void Stage01Scene::processJudgement() {
}

void Stage01Scene::processFinal() {

}

Stage01Scene::~Stage01Scene() {

}
