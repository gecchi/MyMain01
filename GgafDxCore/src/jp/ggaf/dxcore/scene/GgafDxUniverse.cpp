#include "stdafx.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/util/GgafRepeatSeq.h"
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"
#include "jp/ggaf/dxcore/effect/GgafDxEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/dxcore/scene/GgafDxScene.h"
#include "jp/ggaf/dxcore/sound/GgafDxSe.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxDrawableActor* GgafDxUniverse::_apAlphaActorFirstList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL+1];
GgafDxDrawableActor* GgafDxUniverse::_apAlphaActorLastList_DrawDepthLevel[MAX_DRAW_DEPTH_LEVEL+1];
//GgafDxDrawableActor* GgafDxUniverse::_pActors_DrawMaxDrawDepth = nullptr;
GgafDxDrawableActor* GgafDxUniverse::_pActor_DrawActive = nullptr;
std::string GgafDxUniverse::_seqkey_se_delay = "_SE_D_";

coord GgafDxUniverse::_X_gone_left   = 0;
coord GgafDxUniverse::_X_gone_right  = 0;
coord GgafDxUniverse::_Y_gone_top    = 0;
coord GgafDxUniverse::_Y_gone_bottom = 0;
coord GgafDxUniverse::_Z_gone_far   = 0;
coord GgafDxUniverse::_Z_gone_near  = 0;


GgafDxUniverse::SeArray::SeArray() {
    _p = 0;
    for (int i = 0; i < PROPERTY::MAX_SE_AT_ONCE; i++) {
        _apSe[i] = nullptr;
        _apActor[i] = nullptr;
    }
}

void GgafDxUniverse::SeArray::add(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_rate_frequency, GgafDxGeometricActor* prm_pActor) {
    if (_p < PROPERTY::MAX_SE_AT_ONCE) {
        _apSe[_p] = prm_pSe;
        _rate_frequency[_p] = prm_rate_frequency;
        _volume[_p] = prm_volume;
        _pan[_p] = prm_pan;
        _apActor[_p] = prm_pActor;
        _p++;
    }
#ifdef MY_DEBUG
    else {
        _TRACE_("GgafDxUniverse::SeArray::add() SEがあぶれて無視されました。"<<
                "発声元="<<prm_pActor->getName()<<"("<<prm_pActor<<") SE="<<prm_pSe->_wave_key<<"("<<prm_pSe->_wave_file_name<<")");
    }
#endif
}

void GgafDxUniverse::SeArray::play(int index) {
    _apSe[index]->play(_volume[index], _pan[index], _rate_frequency[index]);
    _apSe[index]->_pActor_LastPlayed = _apActor[index];

    _apActor[index] = nullptr;
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
    GgafDxUtil::_pCam = prm_pCamera;

    getSceneDirector()->addSubGroup(_pCamera);
    _pActor_DrawActive = nullptr;

    //カメラの写す範囲。
    coord F = DX_C(_pCamera->_zf);
    _X_gone_right  = +F;
    _X_gone_left   = -F;
    _Y_gone_top    = +F;
    _Y_gone_bottom = -F;
    _Z_gone_far    = +F;
    _Z_gone_near   = -F;
    _TRACE_("Gone=X ("<<_X_gone_left<<" ~ "<<_X_gone_right<<") Y("<<_Y_gone_bottom<<" ~ "<<_Y_gone_top<<") Z("<<_Z_gone_far<<" ~ "<<_Z_gone_near<<")");

    _pRing_pSeArray = NEW GgafLinkedListRing<SeArray>();
    for (int i = 0; i < PROPERTY::MAX_SE_DELAY; i++) { //GGAF_SAYONARA_DELAYは最大解放遅れフレームだが、遠方SEの遅延の最高フレーム数としても使う
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }
    GgafRepeatSeq::create(_seqkey_se_delay, 0, 8); //ズレSE再生フレーム
}

void GgafDxUniverse::registerSe(GgafDxSe* prm_pSe,
                                int prm_volume,
                                float prm_pan,
                                float prm_rate_frequency,
                                int prm_delay,
                                GgafDxGeometricActor* prm_pActor) {
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

    //SEの鳴るタイミングを 0〜8フレームをずらしてバラつかせる

    _pRing_pSeArray->getNext(prm_delay+1+(GgafRepeatSeq::nextVal(_seqkey_se_delay)))->add(prm_pSe, prm_volume, prm_pan, prm_rate_frequency, prm_pActor);
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
        pModelCon->peek()->_pTexBlinker->behave();
        pModelCon = (GgafDxModelConnection*)(pModelCon->getNext());
    }

    //ここでEffectManagerで回してVew変換をいっかい設定するようにする
    GgafDxGod::_pEffectManager->setParamPerFrameAll();

    //段階レンダリング描画
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    GgafDxScene* pScene;
    GgafDxDrawableActor* pDrawActor;
    for (int i = MAX_DRAW_DEPTH_LEVEL; i >= 0; i--) {
        pDrawActor = _pActor_DrawActive = _apAlphaActorFirstList_DrawDepthLevel[i];
        while (pDrawActor) {
#ifdef MY_DEBUG
            if (pDrawActor->getPlatformScene()->instanceOf(Obj_GgafDxScene)) {
                //OK
            } else {
                throwGgafCriticalException("GgafDxUniverse::draw() err2. _pActor_DrawActive["<<(pDrawActor->getName())<<"->getPlatformScene()["<<(_pActor_DrawActive->getPlatformScene()->getName())<<"]が、GgafDxScene に変換不可です。this="<<getName());
            }
#endif
            //各所属シーンのαカーテンを設定する。
            pScene = (GgafDxScene*)pDrawActor->getPlatformScene();
            pDrawActor->_pEffect->_pID3DXEffect->SetFloat(
                    pDrawActor->_pEffect->_h_alpha_master, pScene->_master_alpha);

            //半透明要素ありの場合カリングを一時OFF
            if (pDrawActor->_alpha < 1.0f) {
                pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
            }
            //Zバッファを考慮無効設定
            if (!pDrawActor->_zenable) {
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
            }
            // Zバッファ書き込み不可設定
            if (!pDrawActor->_zwriteenable) {
                pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
            }

            pDrawActor->processDraw(); //描画！！！

            //カリング有りに戻す
            if (pDrawActor->_alpha < 1.0f) {
                pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
            }
            //Zバッファを考慮無効設定
            if (!pDrawActor->_zenable) {
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
            }
            // Zバッファ書き込み不可設定
            if (!pDrawActor->_zwriteenable) {
                pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
            }

            pDrawActor = _pActor_DrawActive = _pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
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
        GgafDxDrawableActor* pActorTmp;
        if (prm_pActor->_is_2D) {
            //同一深度で2Dの場合、連結リストのお尻に追加していく
            //つまり、最後に addSubLast() すればするほど、描画順が後になり、プライオリティが高い。
            pActorTmp = _apAlphaActorLastList_DrawDepthLevel[draw_depth_level];
            pActorTmp->_pNext_TheSameDrawDepthLevel = prm_pActor;
            prm_pActor->_pNext_TheSameDrawDepthLevel = nullptr;
            _apAlphaActorLastList_DrawDepthLevel[draw_depth_level] = prm_pActor;
        } else {
            //同一深度で3Dの場合、前に追加と、お尻に追加を交互に行う。
            //何故そんなことをするかというと、Zバッファ有りのテクスチャに透明があるオブジェクトや、半透明オブジェクトが交差した場合、
            //同一深度なので、プライオリティ（描画順）によって透けない部分が生じてしまう。
            //これを描画順を毎フレーム変化させることで、交互表示でちらつかせ若干のごまかしを行う。
            //TODO:(課題)２、３のオブジェクトの交差は場合は見た目にも許容できるが、たくさん固まると本当にチラチラする。
            if ((GgafGod::_pGod->_pUniverse->_frame_of_behaving & 1) == 1) { //奇数
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
    GGAF_DELETE(_pRing_pSeArray);
}
