#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// �ȉ��� gen01 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
	// gen01 start
	DWORD dw[] = {1,101};
	_paFrame_NextEvent = new DWORD[2];
	for (int i = 0; i < 2; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	orderActorFactory("ID1096101", FormationCeres002, "F_Ceres002_1", "Ceres");
	// gen01 end

	stopImmediately(); //GameMainScene���������Ă����
}

void Stage01MainScene::initialize() {
}

void Stage01MainScene::processBehavior() {
	// �ȉ��� gen02 start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
	// gen02 start
	if (_dwFrame == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_dwFrame) {
			case 1:
				break;
			case 101:
				getLordActor()->accept(KIND_ENEMY, obtainActorFactory("ID1096101"));
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
	// gen02 end

	if (_dwFrame == 2) {

		_TRACE_("Stage01MainScene::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
		// ���ʃV�[����z���Ɉړ�
		addSubLast(GameGlobal::_pSceneCommon->tear());

	}


}

void Stage01MainScene::processFinal() {
//	if (_dwFrame == 1) {
//		_TRACE_("Stage01MainScene::processFinally ���͂����Ȃ��~���܂��BGameMainScene���������Ă����͂��[");
//		this->declareStop(); //GameMainScene���������Ă����
//	}
}

Stage01MainScene::~Stage01MainScene() {
}
