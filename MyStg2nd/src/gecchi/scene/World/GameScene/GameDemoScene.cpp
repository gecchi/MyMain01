#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GameDemoScene::GameDemoScene(const char* prm_name) : DefaultScene(prm_name) {
    setProgress(GAMEDEMO_PROG_INIT);
    _pFontPlate01 = NEW FontPlateActor("STR01", "P/moji");
    getLordActor()->accept(KIND_EFFECT, _pFontPlate01);
    _pFontPlate02 = NEW FontPlateActor("STR02", "P/moji");
    getLordActor()->accept(KIND_EFFECT, _pFontPlate02);
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
        GameGlobal::_pSceneCommon->_pMyShip->actAlone(); //���ʂɃI�v�V�����������邵
        setProgress(GAMEDEMO_PROG_BEGIN);
    }

    if (onChangeProgress(GAMEDEMO_PROG_BEGIN)) {
        _pFontPlate01->setString(100, 100, "GameDemoScene BEGIN");
        _pFontPlate02->setString(100, 150, "HAJIMARI HAJIMARI!");
        _dwFrame_Begin = 0;
    } else if (getProgress() == GAMEDEMO_PROG_BEGIN) {
        //�^�C�g���������[�v
        _dwFrame_Begin++;

        if (_dwFrame_Begin == 120) {
            setProgress(GAMEDEMO_PROG_TITLE); //�^�C�g����
        }
    }


    //���[�v----->

    if (onChangeProgress(GAMEDEMO_PROG_TITLE)) {
    	 //�^�C�g���J�n
        _pFontPlate01->setString(100, 100, "GameDemoScene TITLE");
        _pFontPlate02->setString(100, 150, "PUSH A UI_EXECUTE BUTTON");
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

    if (onChangeProgress(GAMEDEMO_PROG_DEMOPLAY)) {
    	//�f���v���C�J�n
        _pFontPlate01->setString(100, 100, "GameDemoScene DEMOPLAY");
        _pFontPlate02->setString(100, 150, "GAME OVER");
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



    if (onChangeProgress(GAMEDEMO_PROG_RANKING)) {
        //�����L���O�\��
        _pFontPlate01->setString(100, 100, "GameDemoScene RANKING");
        _pFontPlate02->setString(100, 150, "1st GecchiraQ");
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
    if (onChangeProgress(GAMEDEMO_PROG_DECIDE)) {
        _pFontPlate01->setString(100, 100, "GameDemoScene DECIDE");
        _pFontPlate02->setString(100, 150, "OK HJIMARIMASU!");
        _dwFrame_Decide = 0;
    } else if (getProgress() == GAMEDEMO_PROG_DECIDE) {
        //�������[�v
        _dwFrame_Decide++;

        if (_dwFrame_Decide == 120) {
            setProgress(GAMEDEMO_PROG_END); //���I��
        }
    }

    if (onChangeProgress(GAMEDEMO_PROG_END)) {
        _pFontPlate01->setString(100, 100, "GameDemoScene END");
        _pFontPlate02->setString(100, 150, "SRABA");
        inactAfter(200);
    }



}

void GameDemoScene::processFinal() {

}

GameDemoScene::~GameDemoScene() {
}
