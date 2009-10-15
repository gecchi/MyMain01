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
    _angCamXZ_prev = 0;
    _angCamXY_prev = 0;

    _pBgmCon_st1 = (GgafDx9BgmConnection*)GgafDx9Sound::_pBgmManager->connect("VIRTUAL_ON_06");
    //GameMainSceneが解除してくれる
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::initialize() {
    _angCamXZ_prev = GgafDx9Util::getAngleFromXY(-(pCAM->_pVecCamLookatPoint->x - pCAM->_pVecCamFromPoint->x),
                                                     -(pCAM->_pVecCamLookatPoint->z - pCAM->_pVecCamFromPoint->z)
                                                    );
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
            _pBackGroundStar->activateTree();
            _pStage01Main->activate();
            setProgress(STAGE01_PROG_PLAY);
        }
    } else if (getProgress() == STAGE01_PROG_PLAY) {
        angle angCamXZ = GgafDx9Util::getAngleFromXY(
                             pCAM->_X - pCAM->_pViewPoint->_X,
                             pCAM->_Z - pCAM->_pViewPoint->_Z
                         );
        angle angCamXY = GgafDx9Util::getAngleFromXY(
                             pCAM->_X - pCAM->_pViewPoint->_X,
                             pCAM->_Y - pCAM->_pViewPoint->_Y
                         );
        _pBackGround01->_inc_x = -1.0 * GgafDx9Util::getDifferenceAngle(_angCamXZ_prev, angCamXZ)/100.0;
        _pBackGround01->_inc_y = -1.0 * GgafDx9Util::getDifferenceAngle(_angCamXY_prev, angCamXY)/100.0;
        _angCamXZ_prev = angCamXZ;
        _angCamXY_prev = angCamXY;

        if (pCAM->_pos_camera == 0) {
            _pBackGround01->_x -= 0.5; //背景スクロール
        } else if (pCAM->_pos_camera == 3) {
            _pBackGround01->_x += 0.5;
        } else {
            _pBackGround01->_y += 0.5;
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
