#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
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
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/dxcore/sound/GgafDxSe.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxFigureActor* GgafDxSpacetime::_pActor_draw_active = nullptr;
int GgafDxSpacetime::render_depth_index_active = 0;
std::string GgafDxSpacetime::_seqkey_se_delay = "_SE_D_";

GgafDxSpacetime::SeArray::SeArray() {
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

void GgafDxSpacetime::SeArray::add(GgafDxSe* prm_pSe, int prm_volume, float prm_pan, float prm_frequency_rate, GgafDxGeometricActor* prm_pActor) {
    if (_p < PROPERTY::MAX_SE_AT_ONCE) {
        _apSe[_p] = prm_pSe;
        _frequency_rate[_p] = prm_frequency_rate;
        _volume[_p] = prm_volume;
        _pan[_p] = prm_pan;
        _apActor[_p] = prm_pActor;
        _p++;
    }
#ifdef MY_DEBUG
    else {
        _TRACE_("SEがあぶれて無視されました。"
                "発声元="<<prm_pActor->getName()<<"("<<prm_pActor<<") SE="<<prm_pSe->_wave_key<<"("<<prm_pSe->_wave_file_name<<")");
    }
#endif
}

void GgafDxSpacetime::SeArray::play(int index) {
    _apSe[index]->setVolume(_volume[index] );
    _apSe[index]->setPan(_pan[index]);
    _apSe[index]->setFrequencyRate(_frequency_rate[index]);
    _apSe[index]->play(false);
    _apSe[index]->_pActor_last_played = _apActor[index];
    _apActor[index] = nullptr;
    _apSe[index] = nullptr;
}

GgafDxSpacetime::GgafDxSpacetime(const char* prm_name, GgafDxCamera* prm_pCamera) : GgafSpacetime(prm_name),
_x_bound_left  (-DX_C(prm_pCamera->getZFar())), //カメラの写す範囲＝Spacetimeの範囲
_x_bound_right (+DX_C(prm_pCamera->getZFar())),
_y_bound_bottom(-DX_C(prm_pCamera->getZFar())),
_y_bound_top   (+DX_C(prm_pCamera->getZFar())),
_z_bound_near  (-DX_C(prm_pCamera->getZFar())),
_z_bound_far   (+DX_C(prm_pCamera->getZFar()))
{
    _obj_class |= Obj_GgafDxSpacetime;
    _class_name = "GgafDxSpacetime";

    _TRACE_("Spacetime Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");

//TODO:フォグいつか
//    _colFog.r = 0.0;
//    _colFog.g = 0.0;
//    _colFog.b = 0.0;
//    _colFog.a = 1.0;
    _papFirstActor_in_render_depth = NEW GgafDxFigureActor*[ALL_RENDER_DEPTH_INDEXS_NUM];
    _papLastActor_in_render_depth = NEW GgafDxFigureActor*[ALL_RENDER_DEPTH_INDEXS_NUM];
    for (int i = 0; i < ALL_RENDER_DEPTH_INDEXS_NUM; i++) {
        _papFirstActor_in_render_depth[i] = nullptr;
        _papLastActor_in_render_depth[i] = nullptr;
    }
    //先にカメラはNEWしておかないといけない。
    _pCamera = prm_pCamera;
    GgafDxUtil::_pCam = prm_pCamera;

    bringSceneMediator()->addSubGroup(_pCamera);

    _pRing_pSeArray = NEW GgafLinkedListRing<SeArray>();
    for (int i = 0; i < PROPERTY::MAX_SE_DELAY; i++) { //GGAF_END_DELAYは最大解放遅れフレームだが、遠方SEの遅延の最高フレーム数としても使う
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }
    _pRing_pSeArray->createIndex();

    GgafRepeatSeq::create(_seqkey_se_delay, 0, 8); //ズレSE再生フレーム

    //実際の深度と、描画の段階レンダリングの深度要素の関係
    //画面に近い場合は細く段階レンダリングするが
    //奥になればなるほどだんだんアバウトな段階にしていく

    // y = sin(x^(e/pi))
    // 0 <= x <= (pi^(pi/e)) / (2^(pi/e))
    //                               ↑ y=1で接する箇所
    const double e = 2.7182818284590452354;
    const double period = pow(PI, (PI/e)) / pow(2,(PI/e));

    _dep_resolution = prm_pCamera->getZFar() * PROPERTY::RENDER_DEPTH_STAGE_RATIO;  //段階レンダ考慮範囲
    pixcoord px_dep_resolution = DX_PX(_dep_resolution);
    _paDep2Lv = NEW int[px_dep_resolution+1];

    _paDep2Lv[0] = 0;
    for (int z = 1; z <= px_dep_resolution; z++) {
        double ang = RCNV(0, px_dep_resolution, z, 0, period);
        _paDep2Lv[z] = (int) ( sin( pow(ang, e/PI) ) * (REGULAR_RENDER_DEPTH_INDEXS_NUM-1) );
    }
    //ハマったことメモ
    //pow(x,y)は
    //double ang = RCNV(0, px_dep_resolution, z, 0, period); → z = 0 の場合 ang = -0; になる
    //GCCの場合は底が負と解釈されるのか、 pow(ang, e/PI) = -1.#IND となってしまう時が環境によりある。
    //VCは 0 になった。
    //powを使うときは気をつけよう。

    _TRACE_("通常の段階レンダリング深度数："<<REGULAR_RENDER_DEPTH_INDEXS_NUM);
    _TRACE_("通常の段階レンダリング距離範囲："<<DX_C(prm_pCamera->getZFar())<<" * "<<PROPERTY::RENDER_DEPTH_STAGE_RATIO <<
                                             " = "<< DX_C(_dep_resolution)   );
    _TRACE_("カメラからの距離  0 ~ "<<DX_C(_dep_resolution)<< " のActorは、 深度が考慮されて遠くのオブジェクトから順にレンダリングを行います。");
    _TRACE_(DX_C(_dep_resolution)<<" より遠いオブジェクトは全て同一深度として最初にレンダリングされます。");
}

void GgafDxSpacetime::registerSe(GgafDxSe* prm_pSe,
                                 int prm_volume,
                                 float prm_pan,
                                 float prm_frequency_rate,
                                 int prm_delay,
                                 GgafDxGeometricActor* prm_pActor) {
//    int bpm = GgafDxBgmConductor::_active_bgm_bpm;
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
    _pRing_pSeArray->getNext(delay)->add(prm_pSe, prm_volume, prm_pan, prm_frequency_rate, prm_pActor);
}

void GgafDxSpacetime::processSettlementBehavior() {
    GgafSpacetime::processSettlementBehavior();
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

void GgafDxSpacetime::draw() {
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;

    //ここで、全 Model に対してGgafDxTextureBlinkerの状態を進行させる
    GgafDxModelConnection* pModelCon = GgafDxGod::_pModelManager->getFirstConnection();
    while (pModelCon) {
        pModelCon->peek()->_pTexBlinker->behave();
        pModelCon = (GgafDxModelConnection*)(pModelCon->getNext());
    }

    //ここで、全 Effect に対してVew変換行列を設定するようにする
    GgafDxGod::_pEffectManager->setParamPerFrameAll();

    //段階レンダリング描画
    //描画順アクターリストを構築
    GgafDxFigureActor* pDrawLastActor_in_render_depth = nullptr;
    GgafDxFigureActor* pDrawNextActor_in_render_depth = nullptr;
    GgafDxFigureActor* pDrawActor = nullptr; //リストの先頭アクターが入る
    for (int i = ALL_RENDER_DEPTH_INDEXS_NUM - 1; i >= 0; i--) { //奥から
        pDrawLastActor_in_render_depth = _papLastActor_in_render_depth[i];
        if (pDrawLastActor_in_render_depth) {
            if (!pDrawActor) {
                pDrawActor = _papFirstActor_in_render_depth[i];  //一番最初に表示するアクター
            }
            _papFirstActor_in_render_depth[i] = nullptr;   //次回のためにリセット
            _papLastActor_in_render_depth[i]  = nullptr;   //次回のためにリセット
            for (i-- ; i >= 0; i--) {
                pDrawNextActor_in_render_depth = _papFirstActor_in_render_depth[i];
                if (pDrawNextActor_in_render_depth) {
                    pDrawLastActor_in_render_depth->_pNextRenderActor = pDrawNextActor_in_render_depth;
                    i++;
                    break;
                }
            }
        }
    }

    while (pDrawActor) {
        GgafDxSpacetime::_pActor_draw_active = pDrawActor;

#ifdef MY_DEBUG
        if (pDrawActor->getPlatformScene()->instanceOf(Obj_GgafDxScene)) {
            //OK
        } else {
            throwGgafCriticalException("err2. 描画アクターの所属シーン _pActor_draw_active["<<(pDrawActor->getName())<<"->getPlatformScene()["<<(pDrawActor->getPlatformScene()->getName())<<"]が、GgafDxScene に変換不可です。this="<<getName()<<" \n"
                    "pDrawActor->getPlatformScene()->_obj_class="<<pDrawActor->getPlatformScene()->_obj_class<< " Obj_GgafDxScene="<<Obj_GgafDxScene<<" \n"
                    "(pDrawActor->getPlatformScene()->_obj_class & Obj_GgafDxScene)="<<((pDrawActor->getPlatformScene()->_obj_class) & Obj_GgafDxScene) <<" ==?? Obj_GgafDxScene("<<Obj_GgafDxScene<<")");
        }
#endif
        //各所属シーンのαカーテンを設定する。
        pDrawActor->getEffect()->setAlphaMaster(
                                    ((GgafDxScene*)pDrawActor->getPlatformScene())->_scene_alpha_from_top
                                 );

        if (pDrawActor->_alpha < 1.0f) {
            //半透明要素ありの場合カリングを一時OFF
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
            if (!pDrawActor->_zenable) {
                //Zバッファを考慮無効設定
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
                if (!pDrawActor->_zwriteenable) {
                    // Zバッファ書き込み不可設定
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    // Zバッファ書き込み可に戻す
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                } else {
                    pDrawActor->processDraw();
                }
                //Zバッファを考慮有りに戻す
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
            } else {
                if (!pDrawActor->_zwriteenable) {
                    // Zバッファ書き込み不可設定
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    // Zバッファ書き込み可に戻す
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                } else {
                    pDrawActor->processDraw();
                }
            }
            //カリング有りに戻す
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        } else {
            if (!pDrawActor->_zenable) {
                //Zバッファを考慮無効設定
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
                if (!pDrawActor->_zwriteenable) {
                    // Zバッファ書き込み不可設定
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    // Zバッファ書き込み可に戻す
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                } else {
                    pDrawActor->processDraw();
                }
                //Zバッファを考慮有りに戻す
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
            } else {
                if (!pDrawActor->_zwriteenable) {
                    // Zバッファ書き込み不可設定
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    // Zバッファ書き込み可に戻す
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                } else {
                    pDrawActor->processDraw();
                }
            }
        }

        pDrawActor = GgafDxSpacetime::_pActor_draw_active->_pNextRenderActor;
        //set系描画の場合は、pDrawActor->processDraw() 処理内で、
        //GgafDxSpacetime::_pActor_draw_active が、set系の最終描画アクターに更新されている。
        //_pNextRenderActor で表示が飛ばされることはない。
    }

    //最後のEndPass
    HRESULT hr;
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (pEffect_active) {
        _TRACE4_("最後の EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
        hr = pEffect_active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
        hr = pEffect_active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "End()に失敗しました。");
#ifdef MY_DEBUG
        if (pEffect_active->_begin == false) {
            throwGgafCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
        } else {
            pEffect_active->_begin = false;
        }
#endif
        GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        GgafDxEffectManager::_pEffect_active = nullptr;
        GgafDxModelManager::_pModelLastDraw = nullptr;
        GgafDxFigureActor::_hash_technique_last_draw = 0;
    }
}

int GgafDxSpacetime::registerFigureActor2D(GgafDxFigureActor* prm_pActor) {
    int render_depth_index;
    int specal_render_depth_index = prm_pActor->_specal_render_depth_index;
    if (specal_render_depth_index < 0) {
        //＊＊＊ 2Dで特別な描画深度指定無し ＊＊＊
        render_depth_index = EX_RENDER_DEPTH_INDEXS_FRONT_NUM + prm_pActor->_z; //_z値がプライオリティ件描画深度。
        //上限下限カット
        if (render_depth_index > RENDER_DEPTH_INDEX_BACK) {
            render_depth_index = RENDER_DEPTH_INDEX_BACK;
        } else if (render_depth_index < RENDER_DEPTH_INDEX_FRONT) {
            render_depth_index = RENDER_DEPTH_INDEX_FRONT;
        }
        if (_papFirstActor_in_render_depth[render_depth_index] == nullptr) {
            //2Dでそのprm_render_depth_indexで最初のアクターの場合
            prm_pActor->_pNextRenderActor = nullptr;
            _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
            _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
        } else {
            //2Dで同一深度で2Dの場合、連結リストのお尻に追加していく
            //つまり、最後に addSubLast() すればするほど、描画順が後になり、プライオリティが高いくなる。
            GgafDxFigureActor* pActorTmp = _papLastActor_in_render_depth[render_depth_index];
            pActorTmp->_pNextRenderActor = prm_pActor;
            prm_pActor->_pNextRenderActor = nullptr;
            _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
        }
    } else {
        //＊＊＊ 2Dで特別な描画深度指定有り ＊＊＊
        render_depth_index = specal_render_depth_index;
        if (_papFirstActor_in_render_depth[render_depth_index] == nullptr) {
            //そのprm_render_depth_indexで最初のアクターの場合
            prm_pActor->_pNextRenderActor = nullptr;
            _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
            _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
        } else {
            //手前に追加
            GgafDxFigureActor* pActorTmp = _papFirstActor_in_render_depth[render_depth_index];
            prm_pActor->_pNextRenderActor = pActorTmp;
            _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
        }
    }
    return render_depth_index;
}

int GgafDxSpacetime::registerFigureActor3D(GgafDxFigureActor* prm_pActor) {
    int render_depth_index;
    int specal_render_depth_index = prm_pActor->_specal_render_depth_index;
    //＊＊＊３Dの場合
    if (prm_pActor->isOutOfView()) {
        //描画しないので登録なし
        render_depth_index = -1;
    } else {

        if (specal_render_depth_index < 0) { //特別な描画深度指定無し
            //＊＊＊ 3Dで特別な描画深度指定無し ＊＊＊
            dxcoord dep = -prm_pActor->_dest_from_vppln_infront; //オブジェクトの視点からの距離(DIRECTX距離)
            if (dep < 0.0) {
                render_depth_index = RENDER_DEPTH_INDEX_FRONT;
            } else if (0.0 <= dep && dep < _dep_resolution) {
                render_depth_index = RENDER_DEPTH_INDEX_FRONT + _paDep2Lv[DX_PX(dep)];
            } else {
                render_depth_index = RENDER_DEPTH_INDEX_BACK;
            }
            if (_papFirstActor_in_render_depth[render_depth_index] == nullptr) {
                //そのprm_render_depth_indexで最初のアクターの場合
                prm_pActor->_pNextRenderActor = nullptr;
                _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
                _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
            } else {
                if (!prm_pActor->_zwriteenable) {
                    //Z値を書き込ま無いオブジェクトはお尻に追加。
                    //深度の深い順に表示は行われるが。
                    //同一の深度の「前」に追加   ＝ その深度で始めに描画される
                    //同一の深度の「お尻」に追加 ＝ その深度で後に描画される
                    //となっていることに注意。
                    //Z値を書き込むのアクターは始めの方に描画するほうがいいかなぁ～と思って。
                    //レーザー等が綺麗に描画される可能性が高い。
                    GgafDxFigureActor* pActorTmp = _papLastActor_in_render_depth[render_depth_index];
                    pActorTmp->_pNextRenderActor = prm_pActor;
                    prm_pActor->_pNextRenderActor = nullptr;
                    _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
                } else {
                    //同一深度で3Dの場合、前に追加と、お尻に追加を交互に行う。
                    //何故そんなことをするかというと、Zバッファ有りのオブジェクトに半透明オブジェクトと交差した場合、
                    //同一深度なので、プライオリティ（描画順）によって透けない部分が生じてしまう。
                    //これを描画順を毎フレーム変化させることで、交互表示でちらつかせ若干のごまかしを行う。
                    //TODO:(課題)２、３のオブジェクトの交差は場合は見た目にも許容できるが、たくさん固まると本当にチラチラする。
                    if ((_frame_of_behaving & 1) == 1) { //奇数
                        //前に追加
                        GgafDxFigureActor* pActorTmp = _papFirstActor_in_render_depth[render_depth_index];
                        prm_pActor->_pNextRenderActor = pActorTmp;
                        _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
                    } else {
                        //お尻に追加
                        GgafDxFigureActor* pActorTmp = _papLastActor_in_render_depth[render_depth_index];
                        pActorTmp->_pNextRenderActor = prm_pActor;
                        prm_pActor->_pNextRenderActor = nullptr;
                        _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
                    }
                }
            }

        } else {
            //＊＊＊ 3Dで特別な描画深度指定有り
            render_depth_index = specal_render_depth_index;
            if (_papFirstActor_in_render_depth[render_depth_index] == nullptr) {
                //そのprm_render_depth_indexで最初のアクターの場合
                prm_pActor->_pNextRenderActor = nullptr;
                _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
                _papLastActor_in_render_depth[render_depth_index] = prm_pActor;
            } else {
                //前に追加
                GgafDxFigureActor* pActorTmp = _papFirstActor_in_render_depth[render_depth_index];
                prm_pActor->_pNextRenderActor = pActorTmp;
                _papFirstActor_in_render_depth[render_depth_index] = prm_pActor;
            }
        }
    }
    return render_depth_index;
}

GgafDxSpacetime::~GgafDxSpacetime() {
    GGAF_DELETE(_pRing_pSeArray);
    GGAF_DELETEARR(_paDep2Lv);
    GGAF_DELETEARR(_papFirstActor_in_render_depth);
    GGAF_DELETEARR(_papLastActor_in_render_depth);
}
