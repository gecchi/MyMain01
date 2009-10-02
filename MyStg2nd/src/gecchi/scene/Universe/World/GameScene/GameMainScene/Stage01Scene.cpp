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
    _pBgmCon_st1 = (GgafDx9BgmConnection*)GgafDx9Sound::_pBgmManager->connect("VIRTUAL_ON_06");
    //GameMainSceneが解除してくれる
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::initialize() {

    float vx = pCAM->_pVecCamLookatPoint->x - pCAM->_pVecCamFromPoint->x;
    float vz = pCAM->_pVecCamLookatPoint->z - pCAM->_pVecCamFromPoint->z;
    _angCamXZ_prev = GgafDx9Util::getAngleFromXY(vx, vz);

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
        float vx = pCAM->_pVecCamLookatPoint->x - pCAM->_pVecCamFromPoint->x;
        float vz = pCAM->_pVecCamLookatPoint->z - pCAM->_pVecCamFromPoint->z;
        angle angCamXZ = GgafDx9Util::getAngleFromXY(vx, vz);
        _pBackGround01->_x += ((angCamXZ - _angCamXZ_prev)/70);
//		_TRACE_("pCAM->_pVecCamFromPoint_prev->x="<<pCAM->_pVecCamFromPoint_prev->x);
//		_TRACE_("pCAM->_pVecCamFromPoint_prev->z="<<pCAM->_pVecCamFromPoint_prev->z);
//		_TRACE_("fSlantCamXZ="<<fSlantCamXZ);
//		_TRACE_("_fSlantCamXZ_prev="<<_fSlantCamXZ_prev);
//		_TRACE_("fRateSlantXZ="<<fRateSlantXZ);

        if (pCAM->_pos_camera == 0) {
            _pBackGround01->_x -= 0.5; //背景スクロール
        } else if (pCAM->_pos_camera == 3) {
            _pBackGround01->_x += 0.5;
        }
        _angCamXZ_prev = angCamXZ;

    }



}

void Stage01Scene::processJudgement() {
}

void Stage01Scene::processFinal() {

}

Stage01Scene::~Stage01Scene() {
    _pBgmCon_st1->close();
}
