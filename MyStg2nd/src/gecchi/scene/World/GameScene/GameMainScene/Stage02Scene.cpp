#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


Stage02Scene::Stage02Scene(const char* prm_name) : StageScene(prm_name) {
}

void Stage02Scene::initialize() {
}

void Stage02Scene::processBehavior() {
}

void Stage02Scene::processFinal() {
	if (_dwFrame == 1) {
		_TRACE_("Stage02Scene::Finally „‚Í‚¢‚«‚È‚è©•ª’â~BGameMainScene‚ª‰ğœ‚µ‚Ä‚­‚ê‚é‚Ü‚Å‘Ò‚Â‚·");
		this->refrain(); //GameMainScene‚ª‰ğœ‚µ‚Ä‚­‚ê‚é
	}
}


Stage02Scene::~Stage02Scene() {
}
