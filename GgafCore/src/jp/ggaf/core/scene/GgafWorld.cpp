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
	//GgafMainScene::drawMain();
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
