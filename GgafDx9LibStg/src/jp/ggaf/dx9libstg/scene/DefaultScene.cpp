#include "stdafx.h"

DefaultScene::DefaultScene(string prm_name) : GgafDx9Scene(prm_name) {
	_class_name = "DefaultScene";
	_paFrame_NextEvent = NULL;
	_iCnt_Event = 0;
}


DefaultScene::~DefaultScene() {
	DELETEARR_POSSIBLE_NULL(_paFrame_NextEvent);
}
