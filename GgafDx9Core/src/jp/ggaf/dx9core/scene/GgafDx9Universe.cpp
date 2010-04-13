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
int GgafDx9Universe::_Z_goneFar   = 0;
int GgafDx9Universe::_Z_goneNear  = 0;

GgafDx9Universe::GgafDx9Universe(const char* prm_name) : GgafUniverse(prm_name) {
    _class_name = "GgafDx9Universe";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
        _apAlphaActorList_DrawDepthLevel[i] = NULL;
    }
    //先にカメラはNEWしておかないといけない。
    _pCamera = NEW GgafDx9Camera("CAMERA", PI * 80.0f / 180.0f, GGAFDX9_PROPERTY(GAME_SPACE_DEPTH));    //FovX視野角80度、深さ×15.0
    getLordActor()->addSubGroup(_pCamera);
    _pActor_DrawActive = NULL;

    //カメラの写すちょっと余裕をもった範囲。
    _X_goneLeft   = GgafDx9Camera::_X_ScreenLeft * 4;
    _X_goneRight  = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Y_goneTop    = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Y_goneBottom = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Z_goneFar   = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Z_goneNear  = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _TRACE_("Gone=X ("<<_X_goneLeft<<" ~ "<<_X_goneRight<<") Y("<<_Y_goneBottom<<" ~ "<<_Y_goneTop<<") Z("<<_Z_goneFar<<" ~ "<<_Z_goneNear<<")");

    _pRing_pSeArray = NEW GgafLinkedListRing<SeArray>();
    for (int i = 0; i < GGAF_SAYONARA_DELAY; i++) { //GGAF_SAYONARA_DELAY = 180
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }

}

void GgafDx9Universe::registSe(GgafDx9Se* prm_pSe, DWORD prm_delay) {
    _pRing_pSeArray->getNext(prm_delay+1)->add(prm_pSe);
}

void GgafDx9Universe::processPreJudgement() {
    GgafUniverse::processPreJudgement();
    //SEを鳴らす
    SeArray* pSeArray = _pRing_pSeArray->next(); //一つ進めてSE配列取得
    if (pSeArray->_p > 0) {
        for (int p = 0; p > pSeArray->_p; p++) {
            pSeArray->_apSe[p]->play(DSBPAN_CENTER, DSBPAN_CENTER);
        }
        pSeArray->_p = 0; //リセット
    }
}

void GgafDx9Universe::draw() {
    GgafDx9ModelConnection* pModelCon = GgafDx9God::_pModelManager->getFirstConnection();
    while (pModelCon != NULL) {
        pModelCon->view()->_pTextureBlinker->behave();
        pModelCon = (GgafDx9ModelConnection*)(pModelCon->getNext());
    }


    //段階レンダリング不要（最深部等、背景、最善面の文字等）の描画。
    //※TODO:本来は手前から描画のほうが効率良い。が、その内最適化
    _pActor_DrawActive = _pActors_DrawMaxDrawDepth;
    while (_pActor_DrawActive != NULL && _pActor_DrawActive->_is_active_flg && _pActor_DrawActive->_can_live_flg) {
        if (_pActor_DrawActive->_fAlpha < 1.0) {
            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //半透明要素ありということでカリングを一時OFF
            //但し、段階レンダリング不要であるにもかかわらず、半透明表示は、前後がうまく表示されないので避けるべき。
        }
        _pActor_DrawActive->processDraw();
        if (_pActor_DrawActive->_fAlpha < 1.0) {
            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  //カリング有りに戻す
        }
        _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
    }
    _pActors_DrawMaxDrawDepth = NULL; //次回のためにリセット

    //段階レンダリングが必要なオブジェクトを描画
    //float tmpAlpah;
    //int alphapoint = MAX_DRAW_DEPTH_LEVEL/4*3;
    for (int i = MAX_DRAW_DEPTH_LEVEL - 1; i >= 0; i--) {
        _pActor_DrawActive = _apAlphaActorList_DrawDepthLevel[i];
        while (_pActor_DrawActive != NULL && _pActor_DrawActive->_is_active_flg && _pActor_DrawActive->_can_live_flg) {
            if (_pActor_DrawActive->_fAlpha < 1.0) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //半透明要素ありということでカリングを一時OFF
            }
            //TODO:奥は暗く
//            if (alphapoint < i) {
//                tmpAlpah = _pActor_DrawActive->getAlpha();
//                _pActor_DrawActive->addAlpha((1.0/(MAX_DRAW_DEPTH_LEVEL - alphapoint))*i - 3.0);
//            }
            _pActor_DrawActive->processDraw();
//            if (alphapoint < i) {
//                _pActor_DrawActive->setAlpha(tmpAlpah);
//            }
            if (_pActor_DrawActive->_fAlpha < 1.0) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);  //カリング有りに戻す
            }
            _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
        _apAlphaActorList_DrawDepthLevel[i] = NULL; //次回のためにリセット
    }

    //最後のEndPass
    HRESULT hr;
    if (GgafDx9EffectManager::_pEffect_Active != NULL) {
        TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDx9Universe::processDraw() EndPass() に失敗しました。");
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "GgafDx9Universe::processDraw() End() に失敗しました。");
        GgafDx9EffectManager::_pEffect_Active = NULL;
        GgafDx9ModelManager::_pModelLastDraw = NULL;
        GgafDx9DrawableActor::_hash_technique_last_draw = 0;
    }
}

//void GgafDx9Universe::setDrawDepthMaxLevel(GgafDx9DrawableActor* prm_pActor) {
//    static GgafDx9DrawableActor* pActorTmp;
//    if (_pActors_DrawMaxDrawDepth == NULL) {
//        //最初のアクターの場合
//        prm_pActor->_pNext_TheSameDrawDepthLevel = NULL;
//        _pActors_DrawMaxDrawDepth = prm_pActor;
//        return;
//    } else {
//        //既にアクター登録済みだった場合
//        pActorTmp = _pActors_DrawMaxDrawDepth;
//        prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
//        _pActors_DrawMaxDrawDepth = prm_pActor;
//        return;
//    }
//}
int GgafDx9Universe::setDrawDepthLevel(int prm_draw_depth_level, GgafDx9DrawableActor* prm_pActor) {
    int draw_depth_level;
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
        //固まらないように、お尻から追加(キュー)、或いは、前に積み上げ(スタック)を、フレームよって交互に行う。
        //何故ならば、テクスチャに半透明が存在するZバッファ有りの半透明オブジェクトが交差した場合、
        //同一深度なので、描画順によっては透けない部分が生じ、おかしな表示となる。これを高速交互表示で若干のごまかしを行う。
        if ((GgafGod::_pGod->_pUniverse->_frame_of_behaving & 1) == 1) {
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
    return draw_depth_level;

}


GgafDx9Universe::~GgafDx9Universe() {

    DELETE_IMPOSSIBLE_NULL(_pRing_pSeArray);
}
