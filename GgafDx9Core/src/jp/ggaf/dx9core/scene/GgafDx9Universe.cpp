#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9DrawableActor* GgafDx9Universe::_apAlphaActorList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL];
GgafDx9DrawableActor* GgafDx9Universe::_pActors_DrawMaxDrawDepth = NULL;
GgafDx9DrawableActor* GgafDx9Universe::_pActor_DrawActive = NULL;
GgafDx9Camera* GgafDx9Universe::_pCamera = NULL;

GgafDx9Universe::GgafDx9Universe(const char* prm_name) : GgafUniverse(prm_name) {
    _class_name = "GgafDx9Universe";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
        _apAlphaActorList_DrawDepthLevel[i] = NULL;
    }
    _pCamera = NEW GgafDx9Camera("CAMERA");
    getLordActor()->accept(_pCamera);
    _pActor_DrawActive = NULL;
}

void GgafDx9Universe::drawMain() {
    //不透明アクターなど、段階レンダリングが不要なオブジェクトを描画
    //※TODO:本来は手前から描画のほうが効率良いが、とりあえず。
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); //左（反時計回り）回りにカリング ∵左手座標系
    _pActor_DrawActive = _pActors_DrawMaxDrawDepth;
    while (_pActor_DrawActive != NULL && _pActor_DrawActive->_is_active_flg && _pActor_DrawActive->_can_live_flg) {
        _pActor_DrawActive->processDrawMain();
        _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
    }
    _pActors_DrawMaxDrawDepth = NULL; //次回のためにリセット

    //αがあるなど、段階レンダリングが必要なオブジェクトを描画
    //＜メモ＞VIEWの注視方向がが正のZ軸に向いているっぽいことが前提。Z軸でしか深度を測ってません。
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //カリングしない
    for (int i = MAX_DRAW_DEPTH_LEVEL - 1; i >= 0; i--) {
        _pActor_DrawActive = _apAlphaActorList_DrawDepthLevel[i];
        while (_pActor_DrawActive != NULL && _pActor_DrawActive->_is_active_flg && _pActor_DrawActive->_can_live_flg) {
            _pActor_DrawActive->processDrawMain();
            _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
        _apAlphaActorList_DrawDepthLevel[i] = NULL; //次回のためにリセット
    }

    HRESULT hr;
    if (GgafDx9EffectManager::_pEffect_Active != NULL) {
        TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
        mightDx9Exception(hr, D3D_OK, "GgafDx9Universe::processDrawMain() EndPass() に失敗しました。");
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
        mightDx9Exception(hr, D3D_OK, "GgafDx9Universe::processDrawMain() End() に失敗しました。");
        GgafDx9EffectManager::_pEffect_Active = NULL;
        GgafDx9ModelManager::_pModelLastDraw = NULL;
    }
}

void GgafDx9Universe::setDrawDepthMaxLevel(GgafDx9DrawableActor* prm_pActor) {
    static GgafDx9DrawableActor* pActorTmp;
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
void GgafDx9Universe::setDrawDepthLevel(int prm_draw_depth_level, GgafDx9DrawableActor* prm_pActor) {
    static int draw_depth_level;
    static GgafDx9DrawableActor* pActorTmp;
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
//    GgafActor* pActor;
//    for (int i = MAX_DRAW_DEPTH_LEVEL - 1; i >= 0; i--) {
//        pActor = _apAlphaActorList_DrawDepthLevel[i];
//        while (pActor != NULL) {
//            _TRACE_pActor->getName();
//            _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
//        }
//        _apAlphaActorList_DrawDepthLevel[i] = NULL; //次回のためにリセット
//    }



}
