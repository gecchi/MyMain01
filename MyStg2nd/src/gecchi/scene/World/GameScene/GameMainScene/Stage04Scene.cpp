#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Stage04Scene::Stage04Scene(string prm_name) : DefaultScene(prm_name) {
}

void Stage04Scene::initialize() {

}

void Stage04Scene::processBehavior() {
}

void Stage04Scene::processFinal() {

	if (_dwFrame == 1) {
		_TRACE_("Stage04Scene::Finally ���͂����Ȃ莩����~�BGameMainScene���������Ă����܂ő҂�");
		this->declareStop(); //GameMainScene���������Ă����
	}
}

Stage04Scene::~Stage04Scene() {
}
