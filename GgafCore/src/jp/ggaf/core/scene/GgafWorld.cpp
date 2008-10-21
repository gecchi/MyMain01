#include "stdafx.h"

GgafActor*  GgafWorld::_apActorDrawDepthLevel_first[MAX_DEPTH_LEVEL];
GgafActor*  GgafWorld::_apActorDrawDepthLevel_last[MAX_DEPTH_LEVEL];
GgafWorld::GgafWorld(string prm_name) : GgafMainScene(prm_name) {
	_class_name = "GgafWorld";
	for (int i = 0; i < MAX_DEPTH_LEVEL; i++) {
		_apActorDrawDepthLevel_first[i] = NULL;
		_apActorDrawDepthLevel_last[i] = NULL;
	}
}

void GgafWorld::drawMain() {
	//���ԂɃ����_������΂�����ɍs��
	GgafActor* pActor;
	GgafActor* ptmp;
	for (int i = MAX_DEPTH_LEVEL-1; i >= 0; i--) {
		pActor = _apActorDrawDepthLevel_first[i];
		while(true) {
			if (pActor == NULL) {
				break;
			}
			pActor -> processDrawMain();
			ptmp = pActor;
			pActor = pActor -> _pNext2;
			ptmp -> _pNext2 = NULL;
		}
		_apActorDrawDepthLevel_first[i] = NULL;
		_apActorDrawDepthLevel_last[i] = NULL;
	}
	//�c����S�������_�����O
	GgafMainScene::drawMain();
}

void GgafWorld::setDrawDepthLevel(int prm_iDrawDepthLevel, GgafActor* prm_pActor) {
	int iDrawDepthLevel;
	if (prm_iDrawDepthLevel > MAX_DEPTH_LEVEL-1) {
		iDrawDepthLevel = MAX_DEPTH_LEVEL-1;
	} else if (prm_iDrawDepthLevel < 0) {
		iDrawDepthLevel = 0;
	} else {
		iDrawDepthLevel = prm_iDrawDepthLevel;
	}
	if (_apActorDrawDepthLevel_first[iDrawDepthLevel] == NULL) {
		_apActorDrawDepthLevel_first[iDrawDepthLevel] = prm_pActor;
		_apActorDrawDepthLevel_last[iDrawDepthLevel] = prm_pActor;
	} else {
		_apActorDrawDepthLevel_last[iDrawDepthLevel]->_pNext2 = prm_pActor;
		_apActorDrawDepthLevel_last[iDrawDepthLevel] = prm_pActor;
	}
}


GgafWorld::~GgafWorld() {
	for (int i = 0; i < MAX_DEPTH_LEVEL; i++) {
		if (_apActorDrawDepthLevel_first[i] != NULL) {
			delete _apActorDrawDepthLevel_first[i];
		}
		if (_apActorDrawDepthLevel_last[i] != NULL) {
			delete _apActorDrawDepthLevel_last[i];
		}

	}
}
