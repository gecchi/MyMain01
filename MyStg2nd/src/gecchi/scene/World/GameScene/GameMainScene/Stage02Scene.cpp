#include "stdafx.h"


Stage02Scene::Stage02Scene(string prm_name) : DefaultScene(prm_name) {
}

void Stage02Scene::initialize() {
}

void Stage02Scene::processBehavior() {
}

void Stage02Scene::processFinal() {
	if (_dwFrame == 1) {
		_TRACE_("Stage02Scene::Finally ���͂����Ȃ莩����~�BGameMainScene���������Ă����܂ő҂�");
		this->declareStop(); //GameMainScene���������Ă����
	}
}


Stage02Scene::~Stage02Scene() {
}
