#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9DrawableActor* GgafDx9Universe::_apAlphaActorList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL];
GgafDx9DrawableActor* GgafDx9Universe::_pActors_DrawMaxDrawDepth = NULL;
GgafDx9DrawableActor* GgafDx9Universe::_pActor_DrawActive = NULL;

int GgafDx9Universe::_X_goneLeft   = 0;
int GgafDx9Universe::_X_goneRight  = 0;
int GgafDx9Universe::_Y_goneTop    = 0;
int GgafDx9Universe::_Y_goneBottom = 0;
int GgafDx9Universe::_Z_goneFar   = 0;
int GgafDx9Universe::_Z_goneNear  = 0;


GgafDx9Universe::SeArray::SeArray() {
    _p = 0;
    for (int i = 0; i < MAX_SE_AT_ONCE; i++) {
        _apSe[i] = NULL;
    }
}

void GgafDx9Universe::SeArray::add(GgafDx9Se* prm_pSe, LONG prm_volume, LONG prm_pan, float prm_rate_frequency) {
    if (_p < MAX_SE_AT_ONCE) {
        _apSe[_p] = prm_pSe;
        _rate_frequency[_p] = prm_rate_frequency;
        _volume[_p] = prm_volume;
        _pan[_p] = prm_pan;
        _p++;
    }
}

void GgafDx9Universe::SeArray::play(int index) {
    _apSe[index]->play(_volume[index], _pan[index], _rate_frequency[index]);
    _apSe[index] = NULL;
}

GgafDx9Universe::GgafDx9Universe(const char* prm_name, GgafDx9Camera* prm_pCamera) : GgafUniverse(prm_name) {
    _obj_class |= Obj_GgafDx9Universe;
    _class_name = "GgafDx9Universe";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL; i++) {
        _apAlphaActorList_DrawDepthLevel[i] = NULL;
    }
    //先にカメラはNEWしておかないといけない。
    _pCamera = prm_pCamera;


    getLordActor()->addSubGroup(_pCamera);
    _pActor_DrawActive = NULL;

    //カメラの写すちょっと余裕をもった範囲。
    _X_goneRight  = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _X_goneLeft   = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Y_goneTop    = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Y_goneBottom = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Z_goneFar   = +_pCamera->_zf*PX_UNIT*LEN_UNIT + (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _Z_goneNear  = -_pCamera->_zf*PX_UNIT*LEN_UNIT - (abs(_pCamera->_cameraZ)*PX_UNIT*LEN_UNIT);
    _TRACE_("Gone=X ("<<_X_goneLeft<<" ~ "<<_X_goneRight<<") Y("<<_Y_goneBottom<<" ~ "<<_Y_goneTop<<") Z("<<_Z_goneFar<<" ~ "<<_Z_goneNear<<")");

    _pRing_pSeArray = NEW GgafLinkedListRing<SeArray>();
    for (int i = 0; i < MAX_SE_DELAY; i++) { //GGAF_SAYONARA_DELAYは最大解放遅れフレームだが、遠方SEの遅延の最高フレーム数としても使う
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }
    GgafRepeatSeq::create("_SE_D_", 0, 8); //ズレSE再生フレーム
}

void GgafDx9Universe::registSe(GgafDx9Se* prm_pSe, LONG prm_volume, LONG prm_pan, int prm_delay, float prm_rate_frequency) {
    int bpm = GgafDx9BgmPerformer::_active_bgm_bpm;
    //ズレフレーム数計算
    //1分間は60*60=3600フレーム
    //4分音符タイミングは 3600/_bpm
    //8分音符タイミングは 3600/(_bpm*2) = 1800/_bpm
    //16分音符タイミングは 3600/(_bpm*4) = 900/_bpm
    //0フレームからBGMが鳴ったとして、現在のフレームをfとすると、直近未来の16分音符タイミングは
    //F = f%(900/_bpm)
    //F = 0の場合、今がそう f
    //F != 0 の場合 {f/(900/_bpm)の商 * (900/_bpm)} + (900/_bpm) が直近未来の16分音符タイミング
    //TODO:温めていたのにインベーダーエクストリームに先をこされてしまった！！＋α新要素が欲しい。！！




    //SEの鳴るタイミングを 0～8フレームをずらしてバラつかせる
    _pRing_pSeArray->getNext(prm_delay+1+(GgafRepeatSeq::nextVal("_SE_D_")))->add(prm_pSe, prm_volume, prm_pan, prm_rate_frequency);
    //_pRing_pSeArray->getNext(prm_delay+1)->add(prm_pSe, prm_volume, prm_pan, prm_rate_frequency);
}

void GgafDx9Universe::processSettlementBehavior() {

    GgafUniverse::processSettlementBehavior();
    //SEを鳴らす
    SeArray* pSeArray = _pRing_pSeArray->next(); //一つ進めてSE配列取得
    if (pSeArray->_p > 0) {
        for (int p = 0; p < pSeArray->_p; p++) {
            pSeArray->play(p);
        }
        pSeArray->_p = 0; //リセット
    }

}

void GgafDx9Universe::draw() {
    GgafDx9ModelConnection* pModelCon = GgafDx9God::_pModelManager->getFirstConnection();
    while (pModelCon != NULL) {
        pModelCon->refer()->_pTextureBlinker->behave();
        pModelCon = (GgafDx9ModelConnection*)(pModelCon->getNext());
    }

    ここでEffectManagerで回してVew変換をいっかい設定するようにする

    //段階レンダリング不要（最深部等、背景、最善面の文字等）の描画。
    //※TODO:本来は手前から描画のほうが効率良い。が、その内最適化
    _pActor_DrawActive = _pActors_DrawMaxDrawDepth;
    while (_pActor_DrawActive != NULL && _pActor_DrawActive->isActive()) {
        if (_pActor_DrawActive->_fAlpha < 1.0) {
            GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //半透明要素ありということでカリングを一時OFF
            //但し、段階レンダリング不要であるにもかかわらず、半透明表示は、前後がうまく表示されないので避けるべき。
        }
        //マスターαを設定する。
#ifdef MY_DEBUG
            if (_pActor_DrawActive->getPlatformScene()->_obj_class & Obj_GgafDx9Scene) {
                //OK
            } else {
                throwGgafCriticalException("GgafDx9Universe::draw() err1. _pActor_DrawActive["<<(_pActor_DrawActive->getName())<<"->getPlatformScene()["<<(_pActor_DrawActive->getPlatformScene()->getName())<<"]が、GgafDx9Scene に変換不可です。this="<<getName());
            }
#endif
        GgafDx9Scene* pScene = (GgafDx9Scene*)_pActor_DrawActive->getPlatformScene();
        _pActor_DrawActive->_pGgafDx9Effect->_pID3DXEffect->SetFloat(
                _pActor_DrawActive->_pGgafDx9Effect->_h_alpha_master, pScene->_pAlphaCurtain->_alpha);
        //描画
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
        while (_pActor_DrawActive != NULL && _pActor_DrawActive->isActive()) {


            //半透明要素ありの場合カリングを一時OFF
            if (_pActor_DrawActive->_fAlpha < 1.0) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
            }
            //Zバッファを考慮無効設定
            if (!_pActor_DrawActive->_zenable) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
            }
            // Zバッファ書き込み不可設定
            if (!_pActor_DrawActive->_zwriteenable) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
            }

#ifdef MY_DEBUG
            if (_pActor_DrawActive->getPlatformScene()->_obj_class & Obj_GgafDx9Scene) {
                //OK
            } else {
                throwGgafCriticalException("GgafDx9Universe::draw() err2. _pActor_DrawActive["<<(_pActor_DrawActive->getName())<<"->getPlatformScene()["<<(_pActor_DrawActive->getPlatformScene()->getName())<<"]が、GgafDx9Scene に変換不可です。this="<<getName());
            }
#endif
            //各所属シーンのαカーテンを設定する。
            GgafDx9Scene* pScene = (GgafDx9Scene*)_pActor_DrawActive->getPlatformScene();
            _pActor_DrawActive->_pGgafDx9Effect->_pID3DXEffect->SetFloat(
                    _pActor_DrawActive->_pGgafDx9Effect->_h_alpha_master, pScene->_pAlphaCurtain->_alpha);
            _pActor_DrawActive->processDraw();

            //カリング有りに戻す
            if (_pActor_DrawActive->_fAlpha < 1.0) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
            }
            //Zバッファを考慮無効設定
            if (!_pActor_DrawActive->_zenable) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
            }
            // Zバッファ書き込み不可設定
            if (!_pActor_DrawActive->_zwriteenable) {
                GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
            }



            _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
        _apAlphaActorList_DrawDepthLevel[i] = NULL; //次回のためにリセット
    }

    //最後のEndPass
    HRESULT hr;
    if (GgafDx9EffectManager::_pEffect_Active != NULL) {

        TRACE4("EndPass("<<GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name<<"("<<GgafDx9EffectManager::_pEffect_Active<<")");
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDx9Universe::processDraw() EndPass() に失敗しました。");
        hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "GgafDx9Universe::processDraw() End() に失敗しました。");
#ifdef MY_DEBUG
        if (GgafDx9EffectManager::_pEffect_Active->_begin == false) {
            throwGgafCriticalException("begin していません "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            GgafDx9EffectManager::_pEffect_Active->_begin = false;
        }
#endif
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
        //表示順が固定にならないように、お尻から追加(キュー)、或いは、前に積み上げ(スタック)を、フレームよって交互に行う。
        //何故そんなことをするかというと、Zバッファ有りのテクスチャに透明があるオブジェクトや、半透明オブジェクトが交差した場合、
        //同一深度なので、プライオリティ（描画順）によって透けない部分が生じてしまう。
        //これを描画順を毎フレーム変化させることで、交互表示でちらつかせ若干のごまかしを行う。
        //TODO:(課題)２、３のオブジェクトの交差は場合は見た目にも許容できるが、たくさん固まると本当にチラチラする。
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
