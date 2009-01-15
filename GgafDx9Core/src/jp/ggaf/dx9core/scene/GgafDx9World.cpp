#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;


GgafActor*  GgafDx9World::_apActorDrawDepthLevel_first[MAX_DRAW_DEPTH_LEVEL];
GgafActor*  GgafDx9World::_apActorDrawDepthLevel_last[MAX_DRAW_DEPTH_LEVEL];
GgafDx9CameraActor* GgafDx9World::_pCamera = NULL;

GgafDx9World::GgafDx9World(string prm_name) : GgafWorld(prm_name) {
	_class_name = "GgafDx9World";
	for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
		_apActorDrawDepthLevel_first[i] = NULL;
		_apActorDrawDepthLevel_last[i] = NULL;
	}

	_pCamera = NEW GgafDx9CameraActor("CAMERA");
	getLordActor()->accept(_pCamera);

}
void GgafDx9World::drawMain() {
	//順番にレンダがあればそれを先に行う
	static GgafActor* pActor;
	static GgafActor* ptmp;
	for (int i = MAX_DRAW_DEPTH_LEVEL-1; i >= 0; i--) {
		pActor = _apActorDrawDepthLevel_first[i];
		while(true) {
			if (pActor == NULL) {
				break;
			}
			pActor -> processDrawMain();
			pActor -> _wasExecuted_processDrawMain = true; //２重描画防止フラグ
			ptmp = pActor;
			pActor = pActor -> _pNext_TheSameDrawDepthLevel;
			ptmp -> _pNext_TheSameDrawDepthLevel = NULL;
		}
		_apActorDrawDepthLevel_first[i] = NULL;
		_apActorDrawDepthLevel_last[i] = NULL;
	}
	//残りも全部レンダリング
	GgafMainScene::drawMain();
}

void GgafDx9World::setDrawDepthLevel(int prm_iDrawDepthLevel, GgafActor* prm_pActor) {
	static int iDrawDepthLevel;
	if (prm_iDrawDepthLevel > MAX_DRAW_DEPTH_LEVEL-1) {
		iDrawDepthLevel = MAX_DRAW_DEPTH_LEVEL-1;
	} else if (prm_iDrawDepthLevel < 0) {
		iDrawDepthLevel = 0;
	} else {
		iDrawDepthLevel = prm_iDrawDepthLevel;
	}
	if (_apActorDrawDepthLevel_first[iDrawDepthLevel] == NULL) {
		_apActorDrawDepthLevel_first[iDrawDepthLevel] = prm_pActor;
		_apActorDrawDepthLevel_last[iDrawDepthLevel] = prm_pActor;
	} else {
		_apActorDrawDepthLevel_last[iDrawDepthLevel]->_pNext_TheSameDrawDepthLevel = prm_pActor;
		_apActorDrawDepthLevel_last[iDrawDepthLevel] = prm_pActor;
	}
}


GgafDx9World::~GgafDx9World() {
	for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
		if (_apActorDrawDepthLevel_first[i] != NULL) {
			DELETE_IMPOSSIBLE_NULL(_apActorDrawDepthLevel_first[i]);
		}
		if (_apActorDrawDepthLevel_last[i] != NULL) {
			DELETE_IMPOSSIBLE_NULL(_apActorDrawDepthLevel_last[i]);
		}

	}
}
