#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Stage05Scene::Stage05Scene(string prm_name) : DefaultScene(prm_name) {
}

void Stage05Scene::initialize() {

}

void Stage05Scene::processBehavior() {
}

void Stage05Scene::processFinal() {

	if (_dwFrame == 1) {
		_TRACE_("Stage05Scene::Finally ���͂����Ȃ莩����~�BGameMainScene���������Ă����܂ő҂�");
		this->declareStop(); //GameMainScene���������Ă����
	}
}

Stage05Scene::~Stage05Scene() {
}
