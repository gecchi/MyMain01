#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/util/GgafRepeatSeq.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"
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

GgafDxFigureActor* GgafDxUniverse::_apFirstActor_draw_depth_level[MAX_DRAW_DEPTH_LEVEL+1];
GgafDxFigureActor* GgafDxUniverse::_apLastActor_draw_depth_level[MAX_DRAW_DEPTH_LEVEL+1];
//GgafDxFigureActor* GgafDxUniverse::_pActors_DrawMaxDrawDepth = nullptr;
GgafDxFigureActor* GgafDxUniverse::_pActor_draw_active = nullptr;
std::string GgafDxUniverse::_seqkey_se_delay = "_SE_D_";

coord GgafDxUniverse::_x_gone_left   = 0;
coord GgafDxUniverse::_x_gone_right  = 0;
coord GgafDxUniverse::_y_gone_top    = 0;
coord GgafDxUniverse::_y_gone_bottom = 0;
coord GgafDxUniverse::_z_gone_far   = 0;
coord GgafDxUniverse::_z_gone_near  = 0;


GgafDxUniverse::SeArray::SeArray() {
#ifdef MY_DEBUG
    if (PROPERTY::MAX_SE_AT_ONCE > 64) {
        throwGgafCriticalException("プロパティ値 MAX_SE_AT_ONCE が、上限(64)を超えています。プロパティファイルを確認してください。PROPERTY::MAX_SE_AT_ONCE="<<PROPERTY::MAX_SE_AT_ONCE);
    }
#endif
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
    _apSe[index]->_pActor_last_played = _apActor[index];
    _apActor[index] = nullptr;
    _apSe[index] = nullptr;
}

GgafDxUniverse::GgafDxUniverse(const char* prm_name, GgafDxCamera* prm_pCamera) : GgafUniverse(prm_name) {
    _obj_class |= Obj_GgafDxUniverse;
    _class_name = "GgafDxUniverse";
//TODO:フォグいつか
//    _colFog.r = 0.0;
//    _colFog.g = 0.0;
//    _colFog.b = 0.0;
//    _colFog.a = 1.0;

    for (int i = 0; i < MAX_DRAW_DEPTH_LEVEL+1; i++) {
        _apFirstActor_draw_depth_level[i] = nullptr;
        _apLastActor_draw_depth_level[i] = nullptr;
    }
    //先にカメラはNEWしておかないといけない。
    _pCamera = prm_pCamera;
    GgafDxUtil::_pCam = prm_pCamera;

    bringDirector()->addSubGroup(_pCamera);
    _pActor_draw_active = nullptr;

    //カメラの写す範囲。
    coord F = DX_C(_pCamera->getZFar());
    _x_gone_right  = +F;
    _x_gone_left   = -F;
    _y_gone_top    = +F;
    _y_gone_bottom = -F;
    _z_gone_far    = +F;
    _z_gone_near   = -F;
    _TRACE_("Gone=X ("<<_x_gone_left<<" ~ "<<_x_gone_right<<") Y("<<_y_gone_bottom<<" ~ "<<_y_gone_top<<") Z("<<_z_gone_near<<" ~ "<<_z_gone_far<<")");

    _pRing_pSeArray = NEW GgafLinkedListRing<SeArray>();
    for (int i = 0; i < PROPERTY::MAX_SE_DELAY; i++) { //GGAF_END_DELAYは最大解放遅れフレームだが、遠方SEの遅延の最高フレーム数としても使う
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }
    _pRing_pSeArray->indexedValue();

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
    //TODO:温めていたのにインベーダーエクストリームに先をこされてしまった(と思ってる)！！＋α新要素が欲しい。！！

    //SEの鳴るタイミングを 0～8フレームをずらしてバラつかせる
    int delay = prm_delay+1+(GgafRepeatSeq::nextVal(_seqkey_se_delay));
    if (delay > PROPERTY::MAX_SE_DELAY-1) {
        delay = PROPERTY::MAX_SE_DELAY-1;
    }
    _pRing_pSeArray->getNext(delay)->add(prm_pSe, prm_volume, prm_pan, prm_rate_frequency, prm_pActor);
}

void GgafDxUniverse::processSettlementBehavior() {
    GgafUniverse::processSettlementBehavior();
    //SEを鳴らす
    SeArray* pSeArray = _pRing_pSeArray->next(); //一つ進めてSE配列取得
    if (pSeArray->_p > 0) {
        int se_p = pSeArray->_p;
        for (int p = 0; p < se_p; p++) {
            pSeArray->play(p);
        }
        pSeArray->_p = 0; //リセット
    }
    GgafRepeatSeq::setMin(_seqkey_se_delay); //次のnextValで0を返す為
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
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    GgafDxFigureActor* pDrawActor;
    for (int i = MAX_DRAW_DEPTH_LEVEL; i >= 0; i--) {
        pDrawActor = GgafDxUniverse::_apFirstActor_draw_depth_level[i];
        if (pDrawActor) {
            while (pDrawActor) {
                GgafDxUniverse::_pActor_draw_active = pDrawActor;
#ifdef MY_DEBUG
                if (pDrawActor->getPlatformScene()->instanceOf(Obj_GgafDxScene)) {
                    //OK
                } else {
                    throwGgafCriticalException("GgafDxUniverse::draw() err2. 描画アクターの所属シーン _pActor_draw_active["<<(pDrawActor->getName())<<"->getPlatformScene()["<<(pDrawActor->getPlatformScene()->getName())<<"]が、GgafDxScene に変換不可です。this="<<getName()<<" \n"<<
                            "pDrawActor->getPlatformScene()->_obj_class="<<pDrawActor->getPlatformScene()->_obj_class<< " Obj_GgafDxScene="<<Obj_GgafDxScene<<" \n"<<
                            "(pDrawActor->getPlatformScene()->_obj_class & Obj_GgafDxScene)="<<((pDrawActor->getPlatformScene()->_obj_class) & Obj_GgafDxScene) <<" ==?? Obj_GgafDxScene("<<Obj_GgafDxScene<<")");
                }
#endif
                //各所属シーンのαカーテンを設定する。
                pDrawActor->getEffect()->setAlphaMaster(
                                            ((GgafDxScene*)pDrawActor->getPlatformScene())->_master_alpha
                                         );


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

                pDrawActor->processDraw(); //ここで描画。
                //setの描画等で、GgafDxUniverse::_pActor_draw_active が更新される

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

                pDrawActor = GgafDxUniverse::_pActor_draw_active->_pNextActor_in_draw_depth_level;
            }
            GgafDxUniverse::_apFirstActor_draw_depth_level[i] = nullptr; //次回のためにリセット
            GgafDxUniverse::_apLastActor_draw_depth_level[i] = nullptr;
        }
    }

    //最後のEndPass
    HRESULT hr;
    if (GgafDxEffectManager::_pEffect_active) {

        _TRACE4_("EndPass("<<GgafDxEffectManager::_pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<GgafDxEffectManager::_pEffect_active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_active<<")");
        hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxUniverse::processDraw() EndPass() に失敗しました。");
        hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "GgafDxUniverse::processDraw() End() に失敗しました。");
#ifdef MY_DEBUG
        if (GgafDxEffectManager::_pEffect_active->_begin == false) {
            throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            GgafDxEffectManager::_pEffect_active->_begin = false;
        }
#endif
        GgafDxEffectManager::_pEffect_active = nullptr;
        GgafDxModelManager::_pModelLastDraw = nullptr;
        GgafDxFigureActor::_hash_technique_last_draw = 0;
    }

}

int GgafDxUniverse::setDrawDepthLevel(int prm_draw_depth_level, GgafDxFigureActor* prm_pActor) {
    int draw_depth_level;
    //上限下限カット
    if (prm_draw_depth_level > MAX_DRAW_DEPTH_LEVEL - 4) {
        draw_depth_level = MAX_DRAW_DEPTH_LEVEL - 4;
    } else if (prm_draw_depth_level < 1) {
        draw_depth_level = 1;
    } else {
        draw_depth_level = prm_draw_depth_level;
    }

    if (GgafDxUniverse::_apFirstActor_draw_depth_level[draw_depth_level] == nullptr) {
        //そのprm_draw_depth_levelで最初のアクターの場合
        prm_pActor->_pNextActor_in_draw_depth_level = nullptr;
        GgafDxUniverse::_apFirstActor_draw_depth_level[draw_depth_level] = prm_pActor;
        GgafDxUniverse::_apLastActor_draw_depth_level[draw_depth_level] = prm_pActor;
    } else {
        if (prm_pActor->_is_2D) {
            //同一深度で2Dの場合、連結リストのお尻に追加していく
            //つまり、最後に addSubLast() すればするほど、描画順が後になり、プライオリティが高い。
            GgafDxFigureActor* pActorTmp = GgafDxUniverse::_apLastActor_draw_depth_level[draw_depth_level];
            pActorTmp->_pNextActor_in_draw_depth_level = prm_pActor;
            prm_pActor->_pNextActor_in_draw_depth_level = nullptr;
            GgafDxUniverse::_apLastActor_draw_depth_level[draw_depth_level] = prm_pActor;
        } else {
            //同一深度で3Dの場合、前に追加と、お尻に追加を交互に行う。
            //何故そんなことをするかというと、Zバッファ有りのテクスチャに透明があるオブジェクトや、半透明オブジェクトが交差した場合、
            //同一深度なので、プライオリティ（描画順）によって透けない部分が生じてしまう。
            //これを描画順を毎フレーム変化させることで、交互表示でちらつかせ若干のごまかしを行う。
            //TODO:(課題)２、３のオブジェクトの交差は場合は見た目にも許容できるが、たくさん固まると本当にチラチラする。
            if ((GgafGod::_pGod->_pUniverse->_frame_of_behaving & 1) == 1) { //奇数
                //前に追加
                GgafDxFigureActor* pActorTmp = GgafDxUniverse::_apFirstActor_draw_depth_level[draw_depth_level];
                prm_pActor->_pNextActor_in_draw_depth_level = pActorTmp;
                GgafDxUniverse::_apFirstActor_draw_depth_level[draw_depth_level] = prm_pActor;
            } else {
                //お尻に追加
                GgafDxFigureActor* pActorTmp = GgafDxUniverse::_apLastActor_draw_depth_level[draw_depth_level];
                pActorTmp->_pNextActor_in_draw_depth_level = prm_pActor;
                prm_pActor->_pNextActor_in_draw_depth_level = nullptr;
                GgafDxUniverse::_apLastActor_draw_depth_level[draw_depth_level] = prm_pActor;
            }
        }
    }
    return draw_depth_level;
}


GgafDxUniverse::~GgafDxUniverse() {
    GGAF_DELETE(_pRing_pSeArray);
}
