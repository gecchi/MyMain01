#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafActor* GgafDx9World::_apActorDrawDepthLevel_first[MAX_DRAW_DEPTH_LEVEL];
GgafActor* GgafDx9World::_apActorDrawDepthLevel_last[MAX_DRAW_DEPTH_LEVEL];
GgafDx9Camera* GgafDx9World::_pCamera = NULL;

GgafDx9World::GgafDx9World(const char* prm_name) : GgafWorld(prm_name) {
    _class_name = "GgafDx9World";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
        _apActorDrawDepthLevel_first[i] = NULL;
        _apActorDrawDepthLevel_last[i] = NULL;
    }
    _pCamera = NEW GgafDx9Camera("CAMERA");
    getLordActor()->accept(_pCamera);
}

void GgafDx9World::drawMain() {
    //順番にレンダがあればそれを先に行う
    static GgafActor* pActor;
    static GgafActor* ptmp;
    for (int i = MAX_DRAW_DEPTH_LEVEL - 1; i >= 0; i--) {
        pActor = _apActorDrawDepthLevel_first[i];
        while (true) {
            if (pActor == NULL) {
                break;
            }
            pActor->processDrawMain();
            pActor->setExecutedProcessDrawMainFlg(true); //２重描画防止フラグ
            ptmp = pActor;
            pActor = pActor->_pNext_TheSameDrawDepthLevel;
            ptmp->_pNext_TheSameDrawDepthLevel = NULL;
        }
        _apActorDrawDepthLevel_first[i] = NULL;
        _apActorDrawDepthLevel_last[i] = NULL;
    }
    //残りも全部レンダリング
    //GgafMainScene::drawMain();
}

void GgafDx9World::setDrawDepthLevel(int prm_draw_depth_level, GgafActor* prm_pActor) {
    static int draw_depth_level;
    if (prm_draw_depth_level > MAX_DRAW_DEPTH_LEVEL - 1) {
        draw_depth_level = MAX_DRAW_DEPTH_LEVEL - 1;
    } else if (prm_draw_depth_level < 0) {
        draw_depth_level = 0;
    } else {
        draw_depth_level = prm_draw_depth_level;
    }
    if (_apActorDrawDepthLevel_first[draw_depth_level] == NULL) {
        _apActorDrawDepthLevel_first[draw_depth_level] = prm_pActor;
        _apActorDrawDepthLevel_last[draw_depth_level] = prm_pActor;
    } else {
        _apActorDrawDepthLevel_last[draw_depth_level]->_pNext_TheSameDrawDepthLevel = prm_pActor;
        _apActorDrawDepthLevel_last[draw_depth_level] = prm_pActor;
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
