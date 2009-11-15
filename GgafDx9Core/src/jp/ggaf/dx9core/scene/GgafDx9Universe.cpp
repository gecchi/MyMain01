#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9DrawableActor* GgafDx9Universe::_apAlphaActorList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL];
GgafDx9DrawableActor* GgafDx9Universe::_pActors_DrawMaxDrawDepth = NULL;
GgafDx9DrawableActor* GgafDx9Universe::_pActor_DrawActive = NULL;
GgafDx9Camera* GgafDx9Universe::_pCamera = NULL;

int GgafDx9Universe::_X_goneLeft   = 0;
int GgafDx9Universe::_X_goneRight  = 0;
int GgafDx9Universe::_Y_goneTop    = 0;
int GgafDx9Universe::_Y_goneBottom = 0;
int GgafDx9Universe::_Z_goneBack   = 0;
int GgafDx9Universe::_Z_goneFront  = 0;

GgafDx9Universe::GgafDx9Universe(const char* prm_name) : GgafUniverse(prm_name) {
    _class_name = "GgafDx9Universe";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
        _apAlphaActorList_DrawDepthLevel[i] = NULL;
    }
    _pCamera = NEW GgafDx9Camera("CAMERA", PI * 7.0f / 18.0f );
    getLordActor()->accept(_pCamera);
    _pActor_DrawActive = NULL;


    _X_goneLeft   = GgafDx9Camera::_X_ScreenLeft * 4;
    _X_goneRight  = GgafDx9Camera::_X_ScreenRight * 10;
    _Y_goneTop    = GgafDx9Camera::_Y_ScreenTop * 10;
    _Y_goneBottom = GgafDx9Camera::_Y_ScreenBottom * 10;
    _Z_goneBack   = GgafDx9Camera::_X_ScreenRight * 10;
    _Z_goneFront  = GgafDx9Camera::_X_ScreenLeft * 10;


}

void GgafDx9Universe::draw() {
    //不透明アクターなど、段階レンダリングが不要なオブジェクトを描画
    //※TODO:本来は手前から描画のほうが効率良いが、とりあえず。

    _pActor_DrawActive = _pActors_DrawMaxDrawDepth;
    while (_pActor_DrawActive != NULL && _pActor_DrawActive->_is_active_flg && _pActor_DrawActive->_can_live_flg) {
        if (_pActor_DrawActive->_fAlpha < 1.0) {
            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //半透明要素ありということでカリング無し
        } else {
            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  //左（反時計回り）回りにカリング ∵左手座標系
        }
        _pActor_DrawActive->processDraw();
        _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
    }
    _pActors_DrawMaxDrawDepth = NULL; //次回のためにリセット

    //αがあるなど、段階レンダリングが必要なオブジェクトを描画
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //カリングなし
    for (int i = MAX_DRAW_DEPTH_LEVEL - 1; i >= 0; i--) {
        _pActor_DrawActive = _apAlphaActorList_DrawDepthLevel[i];
        while (_pActor_DrawActive != NULL && _pActor_DrawActive->_is_active_flg && _pActor_DrawActive->_can_live_flg) {
            if (_pActor_DrawActive->_fAlpha < 1.0) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //半透明要素ありということでカリング無し
            } else {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  //左（反時計回り）回りにカリング ∵左手座標系
            }
            _pActor_DrawActive->processDraw();
            _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
        _apAlphaActorList_DrawDepthLevel[i] = NULL; //次回のためにリセット
    }

    //最後のEndPass
    HRESULT hr;
    if (GgafDx9EffectManager::_pEffect_Active != NULL) {
        TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
        mightDx9Exception(hr, D3D_OK, "GgafDx9Universe::processDraw() EndPass() に失敗しました。");
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
        mightDx9Exception(hr, D3D_OK, "GgafDx9Universe::processDraw() End() に失敗しました。");
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
        //お尻から追加(キュー)、或いは、前に積み上げ(スタック)を、フレームよって交互に行う。
        //何故ならば、半透明オブジェクトが交差した場合、ぼやかしたいため
        if ((GgafGod::_pGod->_pUniverse->_lifeframe & 1) == 1) {
            //お尻に追加
            pActorTmp = _apAlphaActorList_DrawDepthLevel[draw_depth_level];
            prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
            _apAlphaActorList_DrawDepthLevel[draw_depth_level] = prm_pActor;
        } else {
            //前に追加
            pActorTmp = _apAlphaActorList_DrawDepthLevel[draw_depth_level];
            while(pActorTmp->_pNext_TheSameDrawDepthLevel != NULL) {
                pActorTmp = pActorTmp->_pNext_TheSameDrawDepthLevel;
            }
            pActorTmp->_pNext_TheSameDrawDepthLevel = prm_pActor;
            prm_pActor->_pNext_TheSameDrawDepthLevel = NULL;
        }
    }

}

GgafDx9Universe::~GgafDx9Universe() {
}
