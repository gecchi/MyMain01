#include "stdafx.h"


Stage04Scene::Stage04Scene(string prm_name) : DefaultScene(prm_name) {
}

void Stage04Scene::initialize() {

}

void Stage04Scene::processBehavior() {
	//DWORD frame = _dwFrame;

	// �ȉ��� gen start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B�ύX�̓}�N������s���ĉ������B
	// gen start
	// gen end

}

void Stage04Scene::processFinal() {

	if (_dwFrame == 1) {
		_TRACE_("Stage04Scene::Finally ���͂����Ȃ莩����~�BGameMainScene���������Ă����܂ő҂�");
		this->declareStop(); //GameMainScene���������Ă����
	}
}

Stage04Scene::~Stage04Scene() {
}
