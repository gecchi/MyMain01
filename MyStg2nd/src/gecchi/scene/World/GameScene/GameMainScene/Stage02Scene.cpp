#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Stage02Scene::Stage02Scene(string prm_name) : DefaultScene(prm_name) {
}

void Stage02Scene::initialize() {
}

void Stage02Scene::processBehavior() {
}

void Stage02Scene::processFinal() {
	if (_dwFrame == 1) {
		_TRACE_("Stage02Scene::Finally 私はいきなり自分停止。GameMainSceneが解除してくれるまで待つす");
		this->declareStop(); //GameMainSceneが解除してくれる
	}
}


Stage02Scene::~Stage02Scene() {
}
