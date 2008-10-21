#include "stdafx.h"

GgafDummyActor*  GgafWorld::_apActorDrawOrder[MAX_DEPTH_LEVEL];

GgafWorld::GgafWorld(string prm_name) : GgafMainScene(prm_name) {
	_class_name = "GgafWorld";
	for (int i = 0; i < MAX_DEPTH_LEVEL; i++) {
		_apActorDrawOrder[i] = new GgafDummyActor("DRAWORDER");
	}
}

void GgafWorld::drawMain() {
	//順番にレンダがあればそれを先に行う
	for (int i = 0; i < MAX_DEPTH_LEVEL; i++) {
		_apActorDrawOrder[i]->drawMain();
		_apActorDrawOrder[i]->_pSubFirst = NULL;
	}
	//残りも全部レンダリング
	GgafMainScene::drawMain();
}


GgafWorld::~GgafWorld() {
	for (int i = 0; i < MAX_DEPTH_LEVEL; i++) {
		delete _apActorDrawOrder[i];
	}
}
