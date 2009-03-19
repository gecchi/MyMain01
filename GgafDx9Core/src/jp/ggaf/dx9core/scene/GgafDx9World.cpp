#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafActor* GgafDx9World::_apAlphaActorList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL];
GgafActor* GgafDx9World::_pActors_DrawMaxDrawDepth = NULL;
GgafDx9Camera* GgafDx9World::_pCamera = NULL;

GgafDx9World::GgafDx9World(const char* prm_name) : GgafWorld(prm_name) {
    _class_name = "GgafDx9World";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
        _apAlphaActorList_DrawDepthLevel[i] = NULL;
    }
    _pCamera = NEW GgafDx9Camera("CAMERA");
    getLordActor()->accept(_pCamera);
}

void GgafDx9World::drawMain() {
    static GgafActor* pActor;

    //不透明アクターなど、段階レンダリングが不要なオブジェクトを描画
    //※TODO：本来は手前から描画のほうが効率良いが、とりあえずこれで。
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //左（反時計回り）回りにカリング ∵左手座標系
    pActor = _pActors_DrawMaxDrawDepth;
    while (pActor != NULL) {
        pActor->processDrawMain();
        pActor = pActor->_pNext_TheSameDrawDepthLevel;
    }
    _pActors_DrawMaxDrawDepth = NULL; //次回のためにリセット

    //αがあるなど、段階レンダリングが必要なオブジェクトを描画
    //※TODO：VIEWの注視方向がが正のZ軸に向いているっぽいことが前提。Z軸でしか深度を測ってません。
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //カリングしない
    for (int i = MAX_DRAW_DEPTH_LEVEL - 1; i >= 0; i--) {
        pActor = _apAlphaActorList_DrawDepthLevel[i];
        while (pActor != NULL) {
            pActor->processDrawMain();
            pActor = pActor->_pNext_TheSameDrawDepthLevel;
        }
        _apAlphaActorList_DrawDepthLevel[i] = NULL; //次回のためにリセット
    }
}

void GgafDx9World::setDrawDepthMaxLevel(GgafActor* prm_pActor) {
    static GgafActor* pActorTmp;
    if (_pActors_DrawMaxDrawDepth == NULL) {
        //最初のアクターの場合
        prm_pActor->_pNext_TheSameDrawDepthLevel = NULL;
        _pActors_DrawMaxDrawDepth = prm_pActor;
        return;
    } else {
        //既にアクター登録済みだった場合
        pActorTmp = _pActors_DrawMaxDrawDepth;
        prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
        _pActors_DrawMaxDrawDepth = prm_pActor;
        return;
    }
}
void GgafDx9World::setDrawDepthLevel(int prm_draw_depth_level, GgafActor* prm_pActor) {
    static int draw_depth_level;
    static GgafActor* pActorTmp;
    //上限下限カット
    if (prm_draw_depth_level > MAX_DRAW_DEPTH_LEVEL - 1) {
        draw_depth_level = MAX_DRAW_DEPTH_LEVEL - 1;
    } else if (prm_draw_depth_level < 0) {
        draw_depth_level = 0;
    } else {
        draw_depth_level = prm_draw_depth_level;
    }

    if (_apAlphaActorList_DrawDepthLevel[draw_depth_level] == NULL) {
        //そのprm_draw_depth_levelで最初のアクターの場合
        prm_pActor->_pNext_TheSameDrawDepthLevel = NULL;
        _apAlphaActorList_DrawDepthLevel[draw_depth_level] = prm_pActor;
    } else {
        //そのprm_draw_depth_levelで既にアクター登録済みだった場合
        pActorTmp = _apAlphaActorList_DrawDepthLevel[draw_depth_level];
        prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
        _apAlphaActorList_DrawDepthLevel[draw_depth_level] = prm_pActor;
    }
}

GgafDx9World::~GgafDx9World() {
//不用
//    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
//        if (_apAlphaActorList_DrawDepthLevel[i] != NULL) {
//            DELETE_IMPOSSIBLE_NULL(_apAlphaActorList_DrawDepthLevel[i]);
//        }
//    }
}
