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
void GameDemoScene::initialize() {

}

void GameDemoScene::processBehavior() {
	if (_dwFrame == getFrameAtProgress(GAMEDEMO_PROG_INIT)+2) {
		//���@�\��
		GameGlobal::_pSceneCommon->_pMyShip->actAlone(); //���ʂɃI�v�V�����������邵
		setProgress(GAMEDEMO_PROG_BEGIN);
		_TRACE_("GameDemoScene:OK�ғ����܂������I");
	}

	if (_dwFrame == getFrameAtProgress(GAMEDEMO_PROG_BEGIN)+50) {
		setProgress(GAMEDEMO_PROG_TITLE_BEGIN);
	}
//���[�v----->

	if (getProgress() == GAMEDEMO_PROG_TITLE_BEGIN) {
		//�^�C�g���\��
		_pFontPlate01->setString(100,100,"TITLE�FMYSTG2nd");
		_pFontPlate02->setString(100,150,"PUSH HIT UI_EXECUTE KEY!");
		setProgress(GAMEDEMO_PROG_TITLE_DISP);
	} else if (_dwFrame == getFrameAtProgress(GAMEDEMO_PROG_TITLE_DISP)+100) {
		setProgress(GAMEDEMO_PROG_DEMOPLAY_BEGIN);
	} else if (getProgress() == GAMEDEMO_PROG_DEMOPLAY_BEGIN) {
		//�f���v���C�\��
		_pFontPlate01->setString(100,100,"DEMOPLAY!�FMYSTG2nd");
		setProgress(GAMEDEMO_PROG_DEMOPLAY_DISP);
	} else if (_dwFrame == getFrameAtProgress(GAMEDEMO_PROG_DEMOPLAY_DISP)+300) {
		setProgress(GAMEDEMO_PROG_RANKING_BEGIN);
	} else if (getProgress() == GAMEDEMO_PROG_RANKING_BEGIN) {
		//�����L���O�\��
		_pFontPlate01->setString(100,100,"RANKING!!!�FMYSTG2nd");
		setProgress(GAMEDEMO_PROG_RANKING_BEGIN_DISP);
	} else if (_dwFrame == getFrameAtProgress(GAMEDEMO_PROG_RANKING_BEGIN_DISP)+300) {
		setProgress(GAMEDEMO_PROG_TITLE_BEGIN);
	}
//<-----���[�v
	//�f���v���C�������L���O��
	if (GAMEDEMO_PROG_DEMOPLAY_BEGIN <= getProgress() || getProgress() <= GAMEDEMO_PROG_RANKING_DISP) {
		if (VB::isPushedDown(VB_UI_EXECUTE)) {
			_TRACE_("GameDemoScene �^�C�g����");
			setProgress(GAMEDEMO_PROG_TITLE_BEGIN);
		}
	}

	//�^�C�g����ʎ�
	if (getProgress() == GAMEDEMO_PROG_TITLE_DISP) {
		if (VB::isPushedDown(VB_UI_EXECUTE)) {
			_TRACE_("GameDemoScene �X�^�[�g�����܂����I�I");
			setProgress(GAMEDEMO_PROG_GAMESTART_BEGIN);
		}
	}

	//�Q�[���X�^�[�g
	if (getProgress() == GAMEDEMO_PROG_GAMESTART_BEGIN) {
		_pFontPlate01->setString(100,100,"GAME START!");
		setProgress(GAMEDEMO_PROG_GAMESTART_AFTER);
	}

	//�Q�[���X�^�[�g��
	if (getProgress() == GAMEDEMO_PROG_GAMESTART_AFTER) {
		//
	}


}

void GameDemoScene::processFinal() {

}


GameDemoScene::~GameDemoScene() {
}
