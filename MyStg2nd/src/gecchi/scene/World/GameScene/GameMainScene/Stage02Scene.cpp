#include "stdafx.h"


Stage02Scene::Stage02Scene(string prm_name) : DefaultScene(prm_name) {
}

void Stage02Scene::initialize() {

}

void Stage02Scene::processBehavior() {

	//DWORD frame = _dwFrame;
	// �ȉ��� gen start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B�ύX�̓}�N������s���ĉ������B
	// gen start
	// gen end
}

void Stage02Scene::processFinal() {

	if (_dwFrame == 1) {
		_TRACE_("Stage02Scene::Finally ���͂����Ȃ莩����~�BGameMainScene���������Ă����܂ő҂�");
		this->declareStop(); //GameMainScene���������Ă����
	}
}


Stage02Scene::~Stage02Scene() {
}
