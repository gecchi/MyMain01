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
    _pBackGround01 = NEW BackGround01("BACKGOROUND01", "");
    _pBackGround01->inactivateTree();
    getLordActor()->addSubGroup(KIND_EFFECT, _pBackGround01);
//    _pBackGroundStar =  NEW BackGroundStar("BackGroundStarP");
//    _pBackGroundStar->inactivateTree();
//    getLordActor()->addSubGroup(KIND_EFFECT, _pBackGroundStar);

    _pHoshiBoshi001 = NEW HoshiBoshi001("HoshiBoshi001");
    getLordActor()->addSubGroup(KIND_EFFECT, _pHoshiBoshi001);

    _angCamZX_prev = 0;
    _angCamXY_prev = 0;

    //GameMainSceneが解除してくれる
    setProgress(STAGE01_PROG_INIT);


    _pBgmPerformer = NEW GgafDx9BgmPerformer();
	_pBgmPerformer->useBgm(2);
    _pBgmPerformer->set(0, "VIRTUAL_ON_11");
    _pBgmPerformer->set(1, "VIRTUAL_ON_09");

//    prepareBgm(0, "VIRTUAL_ON_11");
//    prepareBgm(1, "VIRTUAL_ON_09");

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
        //タイトル活動ループ
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 180) { //ステージ１開始！
            _pBackGround01->activateTree();
//            _pBackGroundStar->activateTree();
            _pScene_Stage01Main->activate();
            setProgress(STAGE01_PROG_PLAY);
        }
    } else if (getProgress() == STAGE01_PROG_PLAY) {
        angle angCamXZ = GgafDx9Util::getAngle2D(
                             pCAM->_X - pCAM->_pViewPoint->_X,
                             pCAM->_Z - pCAM->_pViewPoint->_Z
                         );
        angle angCamXY = GgafDx9Util::getAngle2D(
                             pCAM->_X - pCAM->_pViewPoint->_X,
                             pCAM->_Y - pCAM->_pViewPoint->_Y
                         );
        _pBackGround01->_inc_x = GgafDx9Util::getDiffAng(_angCamZX_prev, angCamXZ) * (1.0*GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH)/(ANGLE90*0.5));
        _pBackGround01->_inc_y = GgafDx9Util::getDiffAng(_angCamXY_prev, angCamXY) * (1.0*GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT)/(ANGLE90*0.5));
        //* (1.0*GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH)/ANGLE90 で 90度カメラを回すと背景が１周する計算(1画面分動く）。
        //実際には2画面ほど背景は動くと思うので×0.5
        _angCamZX_prev = angCamXZ;
        _angCamXY_prev = angCamXY;

        if (pWORLD->_pos_camera == CAM_POS_RIGHT) {
            _pBackGround01->_x -= 0.05; //背景スクロール
        } else if (pWORLD->_pos_camera == CAM_POS_LEFT) {
            _pBackGround01->_x += 0.05;
        } else if (pWORLD->_pos_camera == CAM_POS_TOP) {
            _pBackGround01->_y += 0.05;
        } else if (pWORLD->_pos_camera == CAM_POS_BOTTOM) {
            _pBackGround01->_y -= 0.05;
        }


    }
    if (getPartFrame() == 60*60) {

        _pBgmPerformer->fadeout(0, 420);
        //fadeoutBgm(0, 420);

        _pBgmPerformer->play(1, DSBVOLUME_MIN, true);
        _pBgmPerformer->fadein(1, 420);
    }

    _pBgmPerformer->behave();


}

void Stage01Scene::processJudgement() {
}

void Stage01Scene::processFinal() {

}

Stage01Scene::~Stage01Scene() {

    DELETE_IMPOSSIBLE_NULL(_pBgmPerformer);

}
