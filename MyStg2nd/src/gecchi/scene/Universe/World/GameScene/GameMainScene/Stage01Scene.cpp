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

    _pBgmCon_st1 = (GgafDx9BgmConnection*)GgafDx9Sound::_pBgmManager->getConnection("JM5");
    //GameMainSceneが解除してくれる
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::initialize() {
    setProgress(STAGE01_PROG_INIT);
}

void Stage01Scene::processBehavior() {

    static int dx,dy,dz = 0;





    if (VB::isBeingPressed(VB_BUTTON4)) {
        dz = (GameGlobal::_pMyShip->_Z - 200000) - GgafDx9Universe::_pCamera->_Z;
        dx = (GameGlobal::_pMyShip->_X - 500000) - GgafDx9Universe::_pCamera->_X;
    } else {
        dz = (GameGlobal::_pMyShip->_Z - 500000) - GgafDx9Universe::_pCamera->_Z;
        dx = (GameGlobal::_pMyShip->_X - 100000) - GgafDx9Universe::_pCamera->_X;

    }
    if (-20000 < dz && dz < 20000) {
        GgafDx9Universe::_pCamera->_pMover->_veloVzMove /= 1.3;
        GgafDx9Universe::_pCamera->_pMover->setVzMoveAcceleration(0);
    } else {
        GgafDx9Universe::_pCamera->_pMover->setVzMoveAcceleration(dz/100);
    }
    if (-20000 < dx && dx < 20000) {
        GgafDx9Universe::_pCamera->_pMover->_veloVxMove /= 1.3;
        GgafDx9Universe::_pCamera->_pMover->setVxMoveAcceleration(0);
    } else {
        GgafDx9Universe::_pCamera->_pMover->setVxMoveAcceleration(dx/100);
    }

    GgafDx9Universe::_pCamera->setGaze(GameGlobal::_pMyShip->_X, 0, GameGlobal::_pMyShip->_Z);




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
    }

}

void Stage01Scene::processJudgement() {
}

void Stage01Scene::processFinal() {

}

Stage01Scene::~Stage01Scene() {
    _pBgmCon_st1->close();
}
