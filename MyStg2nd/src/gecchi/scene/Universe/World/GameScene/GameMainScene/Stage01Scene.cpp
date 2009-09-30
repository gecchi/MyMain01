#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Stage01Scene::Stage01Scene(const char* prm_name) : StageScene(prm_name) {
    _pStage01Main = NEW Stage01MainScene("Stage01Main");
    _pStage01Main->inactivate();
    addSubLast(_pStage01Main);
    Sleep(2);
    _pBackGround01 = NEW BackGround01("BACKGOROUND01", "");
    _pBackGround01->inactivateTree();
    getLordActor()->accept(KIND_EFFECT, _pBackGround01);
    _pBackGroundStar =  NEW BackGroundStar("BackGroundStarP");
    _pBackGroundStar->inactivateTree();
    getLordActor()->accept(KIND_EFFECT, _pBackGroundStar);

    _pBgmCon_st1 = (GgafDx9BgmConnection*)GgafDx9Sound::_pBgmManager->connect("VIRTUAL_ON_06");
    //GameMainSceneが解除してくれる
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::initialize() {
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::processBehavior() {


    if (getProgress() == STAGE01_PROG_INIT) {
        setProgress(STAGE01_PROG_BEGIN);
    }
    if (onChangeProgressAt(STAGE01_PROG_BEGIN)) {

        _pBgmCon_st1->view()->play(false);
        _dwFrame_Begin = 0;
    } else if (getProgress() == GAMEDEMO_PROG_BEGIN) {
        //タイトル活動ループ
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 120) { //ステージ１開始！
            _pBackGround01->activateTree();
            //_pBackGroundStar->activateTree();
            _pStage01Main->activate();
            setProgress(STAGE01_PROG_PLAY);
        }
    } else if (getProgress() == STAGE01_PROG_PLAY) {
        //pCAM->_plnBack の法泉の角度差を使おうぜ
        float vx = pCAM->_pVecCamFromPoint_prev->x - pCAM->_pVecCamFromPoint->x;
        float vz = pCAM->_pVecCamFromPoint_prev->z - pCAM->_pVecCamFromPoint->z;
        //          a1b1 + a2b2
        //cosθ  =  -----------------
        //          (√a1^2 + a2^2)(√b1^2 + b2^2)
        _pBackGround01->_x += (pCAM->_pMover->_veloVzMove/1000);
        if (pCAM->_pos_camera == 0) {
            _pBackGround01->_x -= 0.01; //背景スクロール
        } else if (pCAM->_pos_camera == 3) {
            _pBackGround01->_x += 0.01;
        }

    }



}

void Stage01Scene::processJudgement() {
}

void Stage01Scene::processFinal() {

}

Stage01Scene::~Stage01Scene() {
    _pBgmCon_st1->close();
}
