#include "stdafx.h"


Stage01MainScene::Stage01MainScene(string prm_name) : DefaultScene(prm_name) {

	// �ȉ��� gen start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B�ύX�̓}�N������s���ĉ������B
	// gen01 start
	DWORD dw[] = {1,40,90,200};
	_paFrame_NextEvent = new DWORD[4];
	for (int i = 0; i < 4; i++) {
		_paFrame_NextEvent[i] = dw[i];
	}
	// gen01 end
	stopImmediately(); //GameMainScene���������Ă����
}

void Stage01MainScene::initialize() {

}

void Stage01MainScene::processBehavior() {
	// �ȉ��� gen start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B�ύX�̓}�N������s���ĉ������B
	// gen02 start
	if (_dwFrame == _paFrame_NextEvent[_iCnt_Event]) {
		switch (_dwFrame) {
			case 1:
				MyFactory::orderActor("[109-6]40", MyFactory::createFormationCeres001, NULL);
				break;
			case 40:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[109-6]40"));
				break;
			case 90:
				MyFactory::orderActor("[110-6]200", MyFactory::createFormationCeres001, NULL);
				break;
			case 200:
				getLordActor()->accept(KIND_ENEMY, MyFactory::obtainActor("[110-6]200"));
				break;
			default :
				break;
		}
		_iCnt_Event++;
	}
	// gen02 end

	if (_dwFrame == 2) {
		_TRACE_("Stage01MainScene::processBehavior �͂��͂�Demo���񂠂肪�Ƃ��A�����N�����܂�����");
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
