#include "stdafx.h"


Stage03Scene::Stage03Scene(string prm_name) : DefaultScene(prm_name) {
}

void Stage03Scene::initialize() {

}

void Stage03Scene::processBehavior() {
	//DWORD frame = _dwFrame;

	// �ȉ��� gen start �` end �̓}�N���ɂ�莩���������ꂽ�R�[�h�ł��B�ύX�̓}�N������s���ĉ������B
	// gen start
	// gen end
}

void Stage03Scene::processFinal() {

	if (_dwFrame == 1) {
		_TRACE_("Stage03Scene::Finally ���͂����Ȃ莩����~�BGameMainScene���������Ă����܂ő҂�");
		this->declareStop(); //GameMainScene���������Ă����
	}
}

Stage03Scene::~Stage03Scene() {
}
