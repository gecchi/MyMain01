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

    _pBgmCon_st1 = (GgafDx9BgmConnection*)GgafDx9Sound::_pBgmManager->getConnection("JM5");
    //GameMainScene���������Ă����
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
        //�^�C�g���������[�v
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 120) {
        	_pBackGround01->activateTree();
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
