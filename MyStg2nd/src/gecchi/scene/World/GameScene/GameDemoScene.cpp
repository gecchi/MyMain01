#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    setProgress(GAMEDEMO_PROG_INIT);
    _pStringBoard01 = NEW GgafDx9StringBoardActor("STR01", "B/moji");
    getLordActor()->accept(KIND_EFFECT, _pStringBoard01);
    _pStringBoard02 = NEW GgafDx9StringBoardActor("STR02", "B/moji");
    getLordActor()->accept(KIND_EFFECT, _pStringBoard02);
}
void GameDemoScene::reset() {
    _TRACE_("GameDemoScene::reset()");
    setProgress(GAMEDEMO_PROG_INIT);
}
void GameDemoScene::ready() {
    _TRACE_("GameDemoScene::ready()");
}

void GameDemoScene::initialize() {
	setProgress(GAMEDEMO_PROG_INIT);
}

void GameDemoScene::processBehavior() {
    if (getProgress() == GAMEDEMO_PROG_INIT) {
        //���@�\��
        GameGlobal::_pSceneCommon->_pMyShip->activate(); //���ʂɃI�v�V�����������邵
        setProgress(GAMEDEMO_PROG_BEGIN);
    }

    if (onChangeProgressAt(GAMEDEMO_PROG_BEGIN)) {
        _pStringBoard01->update(100, 100, "GameDemoScene BEGIN");
        _pStringBoard02->update(100, 150, "HAJIMARI HAJIMARI!");
        _dwFrame_Begin = 0;
    } else if (getProgress() == GAMEDEMO_PROG_BEGIN) {
        //�^�C�g���������[�v
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 120) {
            setProgress(GAMEDEMO_PROG_TITLE); //�^�C�g����
        }
    }


    //���[�v----->

    if (onChangeProgressAt(GAMEDEMO_PROG_TITLE)) {
    	 //�^�C�g���J�n
        _pStringBoard01->update(100, 100, "GameDemoScene TITLE");
        _pStringBoard02->update(100, 150, "PUSH A UI_EXECUTE BUTTON");
        _dwFrame_Title = 0;
    } else if (getProgress() == GAMEDEMO_PROG_TITLE) {
        //�^�C�g���������[�v
        _dwFrame_Title++;

        //�����ɏ���
        if (VB::isPushedDown(VB_UI_EXECUTE)) {
            setProgress(GAMEDEMO_PROG_DECIDE);
        }

        if (_dwFrame_Title == 300) {
            setProgress(GAMEDEMO_PROG_DEMOPLAY); //�f����
        }
    }

    if (onChangeProgressAt(GAMEDEMO_PROG_DEMOPLAY)) {
    	//�f���v���C�J�n
        _pStringBoard01->update(100, 100, "GameDemoScene DEMOPLAY");
        _pStringBoard02->update(100, 150, "GAME OVER");
       setProgress(GAMEDEMO_PROG_DEMOPLAY);
        _dwFrame_Demoplay = 0;
    } else if (getProgress() == GAMEDEMO_PROG_DEMOPLAY) {
        //�f���v���C�������[�v
        _dwFrame_Demoplay++;

        //�����ɏ���
        if (_dwFrame_Demoplay == 300) {
            setProgress(GAMEDEMO_PROG_RANKING); //�����L���O��
        }
    }



    if (onChangeProgressAt(GAMEDEMO_PROG_RANKING)) {
        //�����L���O�\��
        _pStringBoard01->update(100, 100, "GameDemoScene RANKING");
        _pStringBoard02->update(100, 150, "1st GecchiraQ");
        _dwFrame_Ranking = 0;
    } else if (getProgress() == GAMEDEMO_PROG_RANKING) {
        //�����L���O�������[�v
        _dwFrame_Ranking++;

        //�����ɏ���


        if (_dwFrame_Ranking == 300) {
            setProgress(GAMEDEMO_PROG_TITLE); //�^�C�g����
        }
    }

    //<-----���[�v
    //�f���v���C�������L���O��
    if (GAMEDEMO_PROG_DEMOPLAY <= getProgress() && getProgress() <= GAMEDEMO_PROG_RANKING) {
        if (VB::isPushedDown(VB_UI_EXECUTE)) {
            setProgress(GAMEDEMO_PROG_TITLE);
        }
    }


    //�Q�[���X�^�[�g
    if (onChangeProgressAt(GAMEDEMO_PROG_DECIDE)) {
        _pStringBoard01->update(100, 100, "GameDemoScene DECIDE");
        _pStringBoard02->update(100, 150, "OK HJIMARIMASU!");
        _dwFrame_Decide = 0;
    } else if (getProgress() == GAMEDEMO_PROG_DECIDE) {
        //�������[�v
        _dwFrame_Decide++;

        if (_dwFrame_Decide == 120) {
            setProgress(GAMEDEMO_PROG_END); //���I��
        }
    }

    if (onChangeProgressAt(GAMEDEMO_PROG_END)) {
        _pStringBoard01->update(100, 100, "GameDemoScene END");
        _pStringBoard02->update(100, 150, "SRABA");
        inactivateTreeAfter(200);
    }



}

void GameDemoScene::processFinal() {

}

GameDemoScene::~GameDemoScene() {
}
