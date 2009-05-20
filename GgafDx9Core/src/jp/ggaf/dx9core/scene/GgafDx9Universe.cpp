#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafActor* GgafDx9Universe::_apAlphaActorList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL];
GgafActor* GgafDx9Universe::_pActors_DrawMaxDrawDepth = NULL;
GgafDx9Camera* GgafDx9Universe::_pCamera = NULL;

GgafDx9Universe::GgafDx9Universe(const char* prm_name) : GgafUniverse(prm_name) {
    _class_name = "GgafDx9Universe";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
        _apAlphaActorList_DrawDepthLevel[i] = NULL;
    }
    _pCamera = NEW GgafDx9Camera("CAMERA");
    getLordActor()->accept(_pCamera);
}

void GgafDx9Universe::drawMain() {
    static GgafActor* pActor;

    //不透明アクターなど、段階レンダリングが不要なオブジェクトを描画
    //※TODO:本来は手前から描画のほうが効率良いが、とりあえずこれで。
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //左（反時計回り）回りにカリング ∵左手座標系
    pActor = _pActors_DrawMaxDrawDepth;
    while (pActor != NULL && pActor->_is_active_flg && pActor->_can_live_flg) {
        pActor->processDrawMain();
        pActor = pActor->_pNext_TheSameDrawDepthLevel;
    }
    _pActors_DrawMaxDrawDepth = NULL; //次回のためにリセット

    //αがあるなど、段階レンダリングが必要なオブジェクトを描画
    //＜メモ＞VIEWの注視方向がが正のZ軸に向いているっぽいことが前提。Z軸でしか深度を測ってません。
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //カリングしない
    for (int i = MAX_DRAW_DEPTH_LEVEL - 1; i >= 0; i--) {
        pActor = _apAlphaActorList_DrawDepthLevel[i];
        while (pActor != NULL && pActor->_is_active_flg && pActor->_can_live_flg) {
            pActor->processDrawMain();
            pActor = pActor->_pNext_TheSameDrawDepthLevel;
        }
        _apAlphaActorList_DrawDepthLevel[i] = NULL; //次回のためにリセット
    }

    HRESULT hr;
    if (GgafDx9EffectManager::_pEffect_Active != NULL) {
        TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
        mightDx9Exception(hr, D3D_OK, "GgafDx9MorphMeshActor::processDrawMain() EndPass() に失敗しました。");
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
        mightDx9Exception(hr, D3D_OK, "GgafDx9MorphMeshActor::processDrawMain() End() に失敗しました。");
        GgafDx9EffectManager::_pEffect_Active = NULL;
        GgafDx9ModelManager::_pModelLastDraw = NULL;
    }
}

void GgafDx9Universe::setDrawDepthMaxLevel(GgafActor* prm_pActor) {
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
void GgafDx9Universe::setDrawDepthLevel(int prm_draw_depth_level, GgafActor* prm_pActor) {
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

GgafDx9Universe::~GgafDx9Universe() {
}
