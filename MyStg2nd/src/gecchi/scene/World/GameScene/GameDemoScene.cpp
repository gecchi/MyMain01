#include "stdafx.h"


GameDemoScene::GameDemoScene(string prm_name) : DefaultScene(prm_name) {
}

void GameDemoScene::initialize() {

}

void GameDemoScene::processBehavior() {
	DWORD frame = _dwFrame;
	// �ȉ��� gen start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B�ύX�̓}�N������s���ĉ������B
	// gen start
	// gen end

	if (frame == 2) {
		_TRACE_("GameDemoScene:OK�ғ����܂������I");
	}

	if (frame == 60) {
		_TRACE_("GameDemoScene:STAGE1�����J�n�I");
		((GameMainScene*)getNext())->readyStage01();
	}


}

void GameDemoScene::processFinal() {
	if (_dwFrame > 300) {
		if (VirtualButton::isPushedDown(VB_UI_EXECUTE)) {

			_TRACE_("GameDemoScene::processFinally STAGE1�X�^�[�g�I�I����STOP");
			((GameMainScene*)getNext())->enableStage01();

			//_pMyShipScene�̈ړ�
			((GameMainScene*)getNext())->_pStage01Scene->addSubLast(((GameScene*)getParent())->_pMyShipScene->becomeIndependent()); //�V�[����play���Ă���ǉ����Ȃ��Ƌʂ���юU��
			declareStop();
		}
	}

}


GameDemoScene::~GameDemoScene() {
}
