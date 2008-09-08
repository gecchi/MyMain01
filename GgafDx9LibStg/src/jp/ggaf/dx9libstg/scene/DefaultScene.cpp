#include "stdafx.h"

DefaultScene::DefaultScene(string prm_name) : GgafDx9Scene(prm_name) {
	_class_name = "DefaultScene";
	_paFrame_NextEvent = NULL;
	_iCnt_Event = 0;
}


DefaultScene::~DefaultScene() {
	if (_paFrame_NextEvent != NULL) {
		delete [] _paFrame_NextEvent;
	}
}
