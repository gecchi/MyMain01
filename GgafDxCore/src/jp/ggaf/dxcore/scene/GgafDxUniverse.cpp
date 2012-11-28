#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxDrawableActor* GgafDxUniverse::_apAlphaActorFirstList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL+1];
GgafDxDrawableActor* GgafDxUniverse::_apAlphaActorLastList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL+1];
//GgafDxDrawableActor* GgafDxUniverse::_pActors_DrawMaxDrawDepth = nullptr;
GgafDxDrawableActor* GgafDxUniverse::_pActor_DrawActive = nullptr;
std::string GgafDxUniverse::_seqkey_se_delay = "_SE_D_";

coord GgafDxUniverse::_X_goneLeft   = 0;
coord GgafDxUniverse::_X_goneRight  = 0;
coord GgafDxUniverse::_Y_goneTop    = 0;
coord GgafDxUniverse::_Y_goneBottom = 0;
coord GgafDxUniverse::_Z_goneFar   = 0;
coord GgafDxUniverse::_Z_goneNear  = 0;


GgafDxUniverse::SeArray::SeArray() {
    _p = 0;
    for (int i = 0; i < MAX_SE_AT_ONCE; i++) {
        _apSe[i] = nullptr;
    }
}

void GgafDxUniverse::SeArray::add(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency) {
    if (_p < MAX_SE_AT_ONCE) {
        _apSe[_p] = prm_pSe;
        _rate_frequency[_p] = prm_rate_frequency;
        _volume[_p] = prm_volume;
        _pan[_p] = prm_pan;
        _p++;
    }
}

void GgafDxUniverse::SeArray::play(int index) {
    _apSe[index]->play(_volume[index], _pan[index], _rate_frequency[index]);
    _apSe[index] = nullptr;
}

GgafDxUniverse::GgafDxUniverse(const char* prm_name, GgafDxCamera* prm_pCamera) : GgafUniverse(prm_name) {
    _obj_class |= Obj_GgafDxUniverse;
    _class_name = "GgafDxUniverse";
    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL+1; i++) {
        _apAlphaActorFirstList_DrawDepthLevel[i] = nullptr;
        _apAlphaActorLastList_DrawDepthLevel[i] = nullptr;
    }
    //先にカメラはNEWしておかないといけない。
    _pCamera = prm_pCamera;


    getDirector()->addSubGroup(_pCamera);
    _pActor_DrawActive = nullptr;

    //カメラの写す範囲。
    coord F = DX_C(_pCamera->_zf);
    _X_goneRight  = +F;
    _X_goneLeft   = -F;
    _Y_goneTop    = +F;
    _Y_goneBottom = -F;
    _Z_goneFar    = +F;
    _Z_goneNear   = -F;
    _TRACE_("Gone=X ("<<_X_goneLeft<<" ~ "<<_X_goneRight<<") Y("<<_Y_goneBottom<<" ~ "<<_Y_goneTop<<") Z("<<_Z_goneFar<<" ~ "<<_Z_goneNear<<")");

    _pRing_pSeArray = NEW GgafLinkedListRing<SeArray>();
    for (int i = 0; i < MAX_SE_DELAY; i++) { //GGAF_SAYONARA_DELAYは最大解放遅れフレームだが、遠方SEの遅延の最高フレーム数としても使う
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }
    GgafRepeatSeq::create(_seqkey_se_delay, 0, 8); //ズレSE再生フレーム
}

void GgafDxUniverse::registSe(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency, int prm_delay ) {
//    int bpm = GgafDxBgmPerformer::_active_bgm_bpm;
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

    _pRing_pSeArray->getNext(prm_delay+1+(GgafRepeatSeq::nextVal(_seqkey_se_delay)))->add(prm_pSe, prm_volume, prm_pan, prm_rate_frequency);
    //_pRing_pSeArray->getNext(prm_delay+1)->add(prm_pSe, prm_volume, prm_pan, prm_rate_frequency);
}

void GgafDxUniverse::processSettlementBehavior() {

    GgafUniverse::processSettlementBehavior();
    //SEを鳴らす
    SeArray* pSeArray = _pRing_pSeArray->next(); //一つ進めてSE配列取得
    if (pSeArray->_p > 0) {
        for (int p = 0; p < pSeArray->_p; p++) {
            pSeArray->play(p);
        }
        pSeArray->_p = 0; //リセット
    }

    GgafRepeatSeq::setMax(_seqkey_se_delay); //次のnextValで0を返す為
}

void GgafDxUniverse::draw() {
    GgafDxModelConnection* pModelCon = GgafDxGod::_pModelManager->getFirstConnection();
    while (pModelCon) {
        pModelCon->fetch()->_pTextureBlinker->behave();
        pModelCon = (GgafDxModelConnection*)(pModelCon->getNext());
    }

    //ここでEffectManagerで回してVew変換をいっかい設定するようにする
    GgafDxGod::_pEffectManager->setParamPerFrameAll();

    //段階レンダリング描画
    GgafDxScene* pScene;
    for (int i = MAX_DRAW_DEPTH_LEVEL; i >= 0; i--) {
        _pActor_DrawActive = _apAlphaActorFirstList_DrawDepthLevel[i];
        while (_pActor_DrawActive) {
#ifdef MY_DEBUG
            if (_pActor_DrawActive->getPlatformScene()->instanceOf(Obj_GgafDxScene)) {
                //OK
            } else {
                throwGgafCriticalException("GgafDxUniverse::draw() err2. _pActor_DrawActive["<<(_pActor_DrawActive->getName())<<"->getPlatformScene()["<<(_pActor_DrawActive->getPlatformScene()->getName())<<"]が、GgafDxScene に変換不可です。this="<<getName());
            }
#endif
            //各所属シーンのαカーテンを設定する。
            pScene = (GgafDxScene*)_pActor_DrawActive->getPlatformScene();
            _pActor_DrawActive->_pEffect->_pID3DXEffect->SetFloat(
                    _pActor_DrawActive->_pEffect->_h_alpha_master, pScene->_master_alpha);

            //半透明要素ありの場合カリングを一時OFF
            if (_pActor_DrawActive->_alpha < 1.0f) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
            }
            //Zバッファを考慮無効設定
            if (!_pActor_DrawActive->_zenable) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
            }
            // Zバッファ書き込み不可設定
            if (!_pActor_DrawActive->_zwriteenable) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
            }

            _pActor_DrawActive->processDraw(); //描画！！！

            //カリング有りに戻す
            if (_pActor_DrawActive->_alpha < 1.0f) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
            }
            //Zバッファを考慮無効設定
            if (!_pActor_DrawActive->_zenable) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
            }
            // Zバッファ書き込み不可設定
            if (!_pActor_DrawActive->_zwriteenable) {
                GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
            }

            _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
        _apAlphaActorFirstList_DrawDepthLevel[i] = nullptr; //次回のためにリセット
        _apAlphaActorLastList_DrawDepthLevel[i] = nullptr;
    }

    //最後のEndPass
    HRESULT hr;
    if (GgafDxEffectManager::_pEffect_Active) {

        TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
        hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxUniverse::processDraw() EndPass() に失敗しました。");
        hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "GgafDxUniverse::processDraw() End() に失敗しました。");
#ifdef MY_DEBUG
        if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
            throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            GgafDxEffectManager::_pEffect_Active->_begin = false;
        }
#endif
        GgafDxEffectManager::_pEffect_Active = nullptr;
        GgafDxModelManager::_pModelLastDraw = nullptr;
        GgafDxDrawableActor::_hash_technique_last_draw = 0;
    }

}

int GgafDxUniverse::setDrawDepthLevel(int prm_draw_depth_level, GgafDxDrawableActor* prm_pActor) {
    int draw_depth_level;
    GgafDxDrawableActor* pActorTmp;
    //上限下限カット
    if (prm_draw_depth_level > MAX_DRAW_DEPTH_LEVEL - 4) {
        draw_depth_level = MAX_DRAW_DEPTH_LEVEL - 4;
    } else if (prm_draw_depth_level < 1) {
        draw_depth_level = 1;
    } else {
        draw_depth_level = prm_draw_depth_level;
    }

    if (_apAlphaActorFirstList_DrawDepthLevel[draw_depth_level] == nullptr) {
        //そのprm_draw_depth_levelで最初のアクターの場合
        prm_pActor->_pNext_TheSameDrawDepthLevel = nullptr;
        _apAlphaActorFirstList_DrawDepthLevel[draw_depth_level] = prm_pActor;
        _apAlphaActorLastList_DrawDepthLevel[draw_depth_level] = prm_pActor;
    } else {
        if (prm_pActor->_is2DActor) {
            //前に追加
            pActorTmp = _apAlphaActorFirstList_DrawDepthLevel[draw_depth_level];
            prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
            _apAlphaActorFirstList_DrawDepthLevel[draw_depth_level] = prm_pActor;
        } else {
            //そのprm_draw_depth_levelで既にアクター登録済みだった場合
            //表示順が固定にならないように、お尻から追加(キュー)、或いは、前に積み上げ(スタック)を、フレームよって交互に行う。
            //何故そんなことをするかというと、Zバッファ有りのテクスチャに透明があるオブジェクトや、半透明オブジェクトが交差した場合、
            //同一深度なので、プライオリティ（描画順）によって透けない部分が生じてしまう。
            //これを描画順を毎フレーム変化させることで、交互表示でちらつかせ若干のごまかしを行う。
            //TODO:(課題)２、３のオブジェクトの交差は場合は見た目にも許容できるが、たくさん固まると本当にチラチラする。

            if ((GgafGod::_pGod->_pUniverse->_frame_of_behaving & 1) == 1) {
                //前に追加
                pActorTmp = _apAlphaActorFirstList_DrawDepthLevel[draw_depth_level];
                prm_pActor->_pNext_TheSameDrawDepthLevel = pActorTmp;
                _apAlphaActorFirstList_DrawDepthLevel[draw_depth_level] = prm_pActor;
            } else {
                //お尻に追加
                pActorTmp = _apAlphaActorLastList_DrawDepthLevel[draw_depth_level];
                pActorTmp->_pNext_TheSameDrawDepthLevel = prm_pActor;
                prm_pActor->_pNext_TheSameDrawDepthLevel = nullptr;
                _apAlphaActorLastList_DrawDepthLevel[draw_depth_level] = prm_pActor;
            }
        }
    }
    return draw_depth_level;

}


GgafDxUniverse::~GgafDxUniverse() {
    DELETE_IMPOSSIBLE_NULL(_pRing_pSeArray);
}
