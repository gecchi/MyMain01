#include "jp/ggaf/dx/scene/Spacetime.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/core/util/RepeatSeq.h"
#include "jp/ggaf/core/util/lineartree/LinearOctree.hpp"
#include "jp/ggaf/core/util/lineartree/LinearQuadtree.hpp"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelConnection.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/dx/scene/Scene.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/dx/sound/Se.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/dx/model/MassModel.h"

using namespace GgafDx;

int Spacetime::render_depth_index_active = 0;
std::string Spacetime::_seqkey_se_delay = "_SE_D_";

WorldOctree* Spacetime::_pWorldOctree = nullptr;
WorldOctreeRounder* Spacetime::_pWorldOctreeRounder = nullptr;
WorldQuadtree* Spacetime::_pWorldQuadtree = nullptr;
WorldQuadtreeRounder* Spacetime::_pWorldQuadtreeRounder = nullptr;
ViewQuadtree* Spacetime::_pViewQuadtree = nullptr;
ViewQuadtreeRounder* Spacetime::_pViewQuadtreeRounder = nullptr;

Spacetime::SeArray::SeArray() {
#ifdef MY_DEBUG
    if (CONFIG::MAX_SE_AT_ONCE > 64) {
        throwCriticalException("プロパティ値 MAX_SE_AT_ONCE が、上限(64)を超えています。プロパティファイルを確認してください。CONFIG::MAX_SE_AT_ONCE="<<CONFIG::MAX_SE_AT_ONCE);
    }
#endif
    _p = 0;
    for (int i = 0; i < CONFIG::MAX_SE_AT_ONCE; i++) {
        _apSe[i] = nullptr;
        _apActor[i] = nullptr;
    }
}

void Spacetime::SeArray::add(Se* prm_pSe, int prm_volume, float prm_pan, float prm_frequency_rate, bool prm_can_looping, GeometricActor* prm_pActor) {
    if (_p < CONFIG::MAX_SE_AT_ONCE) {
        _apSe[_p] = prm_pSe;
        _frequency_rate[_p] = prm_frequency_rate;
        _volume[_p] = prm_volume;
        _pan[_p] = prm_pan;
        _can_looping[_p] = prm_can_looping;
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

void Spacetime::SeArray::play(int index) {
    _apSe[index]->setVolume(_volume[index] );
    _apSe[index]->setPan(_pan[index]);
    _apSe[index]->setFrequencyRate(_frequency_rate[index]);
    _apSe[index]->play(_can_looping[index]);
    _apSe[index]->_pActor_last_played = _apActor[index];
    _apActor[index] = nullptr;
    _apSe[index] = nullptr;
}

Spacetime::Spacetime(const char* prm_name, Camera* prm_pCamera) : GgafCore::Spacetime(prm_name),
_x_bound_left  (-DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())), //カメラの写す範囲＝Spacetimeの範囲
_x_bound_right (+DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())),
_y_bound_bottom(-DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())),
_y_bound_top   (+DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())),
_z_bound_near  (-DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())),
_z_bound_far   (+DX_C(-prm_pCamera->getZOrigin()*prm_pCamera->getDep())),
_x_bound_left_b   (_x_bound_left    + PX_C(CONFIG::GAME_BUFFER_WIDTH  / 2)),
_x_bound_right_b  (_x_bound_right   + PX_C(CONFIG::GAME_BUFFER_WIDTH  / 2)),
_y_bound_bottom_b (-_y_bound_bottom + PX_C(CONFIG::GAME_BUFFER_HEIGHT / 2)),
_y_bound_top_b    (-_y_bound_top    + PX_C(CONFIG::GAME_BUFFER_HEIGHT / 2))
{
    _obj_class |= Obj_GgafDx_Spacetime;
    _class_name = "Spacetime";

    _TRACE_("Spacetime World  Bound = X("<<_x_bound_left<<" ~ "<<_x_bound_right<<") Y("<<_y_bound_bottom<<" ~ "<<_y_bound_top<<") Z("<<_z_bound_near<<" ~ "<<_z_bound_far<<")");
    _TRACE_("Spacetime Screen Bound = X("<<_x_bound_left_b<<" ~ "<<_x_bound_right_b<<") Y("<<_y_bound_top_b<<" ~ "<<_y_bound_bottom_b<<")");

    _w_r =  1.0 * CONFIG::GAME_BUFFER_WIDTH / CONFIG::RENDER_TARGET_BUFFER_WIDTH;
    _h_r =  1.0 * CONFIG::GAME_BUFFER_HEIGHT / CONFIG::RENDER_TARGET_BUFFER_HEIGHT;

    _primary_buffer_source_left = CONFIG::PRIMARY_VIEW_RENDER_BUFFER_SOURCE_LEFT*_w_r;
    _primary_buffer_source_top = CONFIG::PRIMARY_VIEW_RENDER_BUFFER_SOURCE_TOP*_h_r;
    _primary_buffer_source_width = CONFIG::PRIMARY_VIEW_RENDER_BUFFER_SOURCE_WIDTH*_w_r;
    _primary_buffer_source_height = CONFIG::PRIMARY_VIEW_RENDER_BUFFER_SOURCE_HEIGHT*_h_r;

    _secondary_buffer_source_left = CONFIG::SECONDARY_VIEW_RENDER_BUFFER_SOURCE_LEFT*_w_r;
    _secondary_buffer_source_top = CONFIG::SECONDARY_VIEW_RENDER_BUFFER_SOURCE_TOP*_h_r;
    _secondary_buffer_source_width = CONFIG::SECONDARY_VIEW_RENDER_BUFFER_SOURCE_WIDTH*_w_r;
    _secondary_buffer_source_height = CONFIG::SECONDARY_VIEW_RENDER_BUFFER_SOURCE_HEIGHT*_h_r;

//TODO:フォグいつか
//    _colFog.r = 0.0;
//    _colFog.g = 0.0;
//    _colFog.b = 0.0;
//    _colFog.a = 1.0;
    _papFirstRenderActor = NEW FigureActor*[ALL_RENDER_DEPTH_INDEXS_NUM];
    _papLastRenderActor = NEW FigureActor*[ALL_RENDER_DEPTH_INDEXS_NUM];
    for (int i = 0; i < ALL_RENDER_DEPTH_INDEXS_NUM; i++) {
        _papFirstRenderActor[i] = nullptr;
        _papLastRenderActor[i] = nullptr;
    }
    //先にカメラはNEWしておかないといけない。
    _pCamera = prm_pCamera;
    Util::_pCam = prm_pCamera;

    bringSceneMediator()->appendGroupChild(_pCamera);

    _pRing_pSeArray = NEW GgafCore::RingLinkedList<SeArray>();
    for (int i = 0; i < SeTransmitterForActor::_se_delay_max_depth; i++) { //GGAF_END_DELAYは最大解放遅れフレームだが、遠方SEの遅延の最高フレーム数としても使う
        _pRing_pSeArray->addLast(NEW SeArray(), true);
    }
    _pRing_pSeArray->createIndex();

    GgafCore::RepeatSeq::create(_seqkey_se_delay, 0, 8); //ズレSE再生フレーム

    //実際の深度と、描画の段階レンダリングの深度要素の関係
    //画面に近い場合は細く段階レンダリングするが
    //奥になればなるほどだんだんアバウトな段階にしていく

    // y = sin(x^(e/pi))
    // 0 <= x <= (pi^(pi/e)) / (2^(pi/e))
    //                               ↑ y=1で接する箇所
    static const double e = 2.7182818284590452354;
    static const double period = pow(PI, (PI/e)) / pow(2,(PI/e));

    _dep_resolution = prm_pCamera->getZFar() * CONFIG::RENDER_DEPTH_STAGE_RATIO;  //段階レンダ考慮範囲
    pixcoord px_dep_resolution = DX_PX(_dep_resolution);
    _paDep2Lv = NEW int[px_dep_resolution+1];

    _paDep2Lv[0] = 0;
    for (int z = 1; z <= px_dep_resolution; z++) {
        double ang = RCNV(0, px_dep_resolution, z, 0, period);
        _paDep2Lv[z] = (int) ( sin( pow(ang, e/PI) ) * (CONFIG::RENDER_DEPTH_INDEXS_NUM-1) );
    }
    //ハマったことメモ
    //pow(x,y)は
    //double ang = RCNV(0, px_dep_resolution, z, 0, period); → z = 0 の場合 ang = -0; になる
    //GCCの場合は底が負と解釈されるのか、 pow(ang, e/PI) = -1.#IND となってしまう時が環境によりある。
    //VCは 0 になった。
    //powを使うときは気をつけよう。

    _TRACE_("通常の段階レンダリング深度数："<<CONFIG::RENDER_DEPTH_INDEXS_NUM);
    _TRACE_("通常の段階レンダリング距離範囲："<<DX_C(prm_pCamera->getZFar())<<" * "<<CONFIG::RENDER_DEPTH_STAGE_RATIO <<
                                             " = "<< DX_C(_dep_resolution)   );
    _TRACE_("カメラからの距離  0 ~ "<<DX_C(_dep_resolution)<< " のActorは、 深度が考慮されて遠くのオブジェクトから順にレンダリングを行います。");
    _TRACE_(DX_C(_dep_resolution)<<" より遠いオブジェクトは全て同一深度として最初にレンダリングされます。");

    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        //四分木作成
        _TRACE_("四分木作成開始");
        Spacetime::_pWorldQuadtree = NEW WorldQuadtree(CONFIG::WORLD_HIT_CHECK_QUADTREE_LEVEL,
                                                              _x_bound_left  ,_y_bound_bottom,
                                                              _x_bound_right ,_y_bound_top    );
        Spacetime::_pWorldQuadtreeRounder =
                _pWorldQuadtree->createRounder(&GgafCore::Actor::executeHitChk_MeAnd);
        _TRACE_("四分木作成終了");
    } else {
        //八分木作成
        _TRACE_("八分木作成開始");
        Spacetime::_pWorldOctree = NEW WorldOctree(CONFIG::WORLD_HIT_CHECK_OCTREE_LEVEL,
                                                          _x_bound_left  ,_y_bound_bottom, _z_bound_near ,
                                                          _x_bound_right ,_y_bound_top   , _z_bound_far   );
        Spacetime::_pWorldOctreeRounder =
                _pWorldOctree->createRounder(&GgafCore::Actor::executeHitChk_MeAnd);
        _TRACE_("八分木作成終了");
    }

    //Board用四分木作成
    _TRACE_("Board用四分木作成開始");
    Spacetime::_pViewQuadtree = NEW ViewQuadtree(CONFIG::VIEW_HIT_CHECK_QUADTREE_LEVEL,
                                                        _x_bound_left_b  ,_y_bound_top_b,
                                                        _x_bound_right_b , _y_bound_bottom_b   );
    Spacetime::_pViewQuadtreeRounder =
            _pViewQuadtree->createRounder(&GgafCore::Actor::executeHitChk_MeAnd);
    _TRACE_("Board用四分木作成終了");
}

void Spacetime::registerSe(Se* prm_pSe,
                           int prm_volume,
                           float prm_pan,
                           float prm_frequency_rate,
                           int prm_delay,
                           bool prm_can_looping,
                           GeometricActor* prm_pActor) {
//    int bpm = BgmConductor::_active_bgm_bpm;
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
    int delay = prm_delay+1+(GgafCore::RepeatSeq::nextVal(_seqkey_se_delay));
    if (delay > SeTransmitterForActor::_se_delay_max_depth-1) {
        delay = SeTransmitterForActor::_se_delay_max_depth-1;
    }
    _pRing_pSeArray->getNext(delay)->add(prm_pSe, prm_volume, prm_pan, prm_frequency_rate, prm_can_looping, prm_pActor);
}

void Spacetime::processSettlementBehavior() {
    GgafCore::Spacetime::processSettlementBehavior();
    //SEを鳴らす
    SeArray* pSeArray = _pRing_pSeArray->next(); //一つ進めてSE配列取得
    if (pSeArray->_p > 0) {
        int se_p = pSeArray->_p;
        for (int p = 0; p < se_p; p++) {
            pSeArray->play(p);
        }
        pSeArray->_p = 0; //リセット
    }
    GgafCore::RepeatSeq::setMin(_seqkey_se_delay); //次のnextValで0を返す為
}

void Spacetime::draw() {
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;

    //ここで、全 Model に対してTextureBlinkerの状態を進行させる
    ModelConnection* pModelCon = pCARETAKER->_pModelManager->getFirstConnection();
    while (pModelCon) {
        pModelCon->peek()->_pTexBlinker->behave();
        pModelCon = (ModelConnection*)(pModelCon->getNext());
    }

    //ここで、全 Effect に対してVew変換行列を設定するようにする
    pCARETAKER->_pEffectManager->setParamPerFrameAll();

    //段階レンダリング描画
    //描画順アクターリストを構築
    // データイメージ
    // ○ は アクター
    // [0]～[3] は レンダリング深度（ [0]：手前 ～ [3]：奥）※全要素数は：ALL_RENDER_DEPTH_INDEXS_NUM
    //
    // [0] => [ ① -> ② -> ③ -> ④ -> ⑤ -> nullptr ]
    // [1] => [ nullptr ]
    // [2] => [ ⑥ -> ⑦ -> nullptr ]
    // [3] => [ ⑧ -> nullptr ]
    //
    // 上図のような場合、下記のようにアクター（のポインタ）が設定されている
    //  _papFirstRenderActor[0] = ①     , _papLastRenderActor[0]  = ⑤
    //  _papFirstRenderActor[1] = nullptr, _papLastRenderActor[1]  = nullptr
    //  _papFirstRenderActor[2] = ⑥     , _papLastRenderActor[2]  = ⑦
    //  _papFirstRenderActor[3] = ⑧     , _papLastRenderActor[3]  = ⑧
    //  「->」 の連結はメンバ変数 _pNextRenderActor による単方向連結リスト
    //【描画時順序】
    // 最後の _papLastRenderActor[n] が、ひとつ手前の _papFirstRenderActor[n-1] のアクターに連結されて描画
    // ⑧ -> ⑥ -> ⑦ -> ① -> ② -> ③ -> ④ -> ⑤
#ifdef MY_DEBUG
    if (GgafDx::Input::isPushedDownKey(DIK_R)) {
        _TRACE_("段階レンダリング状態 ---->");
        dumpRenderDepthOrder();
        _TRACE_("<---- 段階レンダリング状態");
    }
#endif
    FigureActor* pDrawLastActor_in_render_depth = nullptr;
    FigureActor* pDrawNextActor_in_render_depth = nullptr;
    FigureActor* pDrawActor = nullptr; //リストの先頭アクターが入る
    for (int i = ALL_RENDER_DEPTH_INDEXS_NUM - 1; i >= 0; i--) { //奥から
        pDrawLastActor_in_render_depth = _papLastRenderActor[i];
        if (pDrawLastActor_in_render_depth) {
            if (!pDrawActor) {
                pDrawActor = _papFirstRenderActor[i];  //一番最初に表示するアクター
            }
            _papFirstRenderActor[i] = nullptr;   //次回のためにリセット
            _papLastRenderActor[i]  = nullptr;   //次回のためにリセット
            for (i-- ; i >= 0; i--) {
                pDrawNextActor_in_render_depth = _papFirstRenderActor[i];
                if (pDrawNextActor_in_render_depth) {
                    //奥の最後のアクターを、直近の手前のアクターの先頭にリンク
                    pDrawLastActor_in_render_depth->_pNextRenderActor = pDrawNextActor_in_render_depth;
                    i++;
                    break;
                }
            }
        }
    }

    while (pDrawActor) {
        GgafCore::Scene* pPlatformScene = pDrawActor->getSceneMediator()->getPlatformScene();

#ifdef MY_DEBUG
        if (pPlatformScene->instanceOf(Obj_GgafDx_Scene)) {
            //OK
        } else {
            throwCriticalException("err2. 描画アクターの所属シーン pDrawActor["<<(pDrawActor->getName())<<"->getPlatformScene()["<<(pPlatformScene->getName())<<"]が、Scene に変換不可です。this="<<getName()<<" \n"
                    "pDrawActor->getPlatformScene()->_obj_class="<<pPlatformScene->_obj_class<< " Obj_GgafDx_Scene="<<Obj_GgafDx_Scene<<" \n"
                    "(pDrawActor->getPlatformScene()->_obj_class & Obj_GgafDx_Scene)="<<((pPlatformScene->_obj_class) & Obj_GgafDx_Scene) <<" ==?? Obj_GgafDx_Scene("<<Obj_GgafDx_Scene<<")");
        }
#endif
        //各所属シーンのαカーテンを設定する。
        pDrawActor->getEffect()->setAlphaMaster(
                                    ((GgafDx::Scene*)pPlatformScene)->_scene_alpha_from_top
                                 );
        //デフォルト
        //SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        //SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
        //SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
        //の場合は、一切 SetRenderState したくない・・・
        if (pDrawActor->_cull_mode == D3DCULL_CCW) {
            if (pDrawActor->_zenable) {
                if (pDrawActor->_zwriteenable) {
                    pDrawActor->processDraw(); //デフォルト画
                } else {
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                }
            } else {
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
                if (pDrawActor->_zwriteenable) {
                    pDrawActor->processDraw();
                } else {
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                }
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
            }
        } else {
            pDevice->SetRenderState(D3DRS_CULLMODE, pDrawActor->_cull_mode);
            if (pDrawActor->_zenable) {
                if (pDrawActor->_zwriteenable) {
                    pDrawActor->processDraw();
                } else {
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                }
            } else {
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
                if (pDrawActor->_zwriteenable) {
                    pDrawActor->processDraw();
                } else {
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                    pDrawActor->processDraw();
                    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
                }
                pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
            }
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        }

        pDrawActor = pDrawActor->_pNextRenderActor;
        //set系描画の場合は、pDrawActor->processDraw() 処理内で、
        //pDrawActor->_pNextRenderActor が、最終描画アクターに更新されている。
        //_pNextRenderActor で表示が飛ばされることはない。
    }

    //最後のEndPass
    HRESULT hr;
    Effect* pEffect_active = EffectManager::_pEffect_active;
    if (pEffect_active) {
        _TRACE4_("最後の EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
        hr = pEffect_active->_pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
        hr = pEffect_active->_pID3DXEffect->End();
        checkDxException(hr, D3D_OK, "End()に失敗しました。");
#ifdef MY_DEBUG
        if (pEffect_active->_begin == false) {
            throwCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
        } else {
            pEffect_active->_begin = false;
        }
#endif
        Model* pModelLastDraw = ModelManager::_pModelLastDraw;
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        EffectManager::_pEffect_active = nullptr;
        ModelManager::_pModelLastDraw = nullptr;
        FigureActor::_hash_technique_last_draw = 0;
    }
}

int Spacetime::registerDrawActor(FigureActor* prm_pActor) {
    int render_depth_index = -1;
    int specal_render_depth_index = prm_pActor->_specal_render_depth_index;
    if (prm_pActor->_is_fix_2D) {
        if (specal_render_depth_index < 0) {
            //＊＊＊ 2Dで特別な描画深度指定無し ＊＊＊
            render_depth_index = RENDER_DEPTH_NEAR_INDEX + prm_pActor->_z; //_z値がプライオリティ兼描画深度。
            //上限下限カット
            if (render_depth_index > RENDER_DEPTH_FAR_INDEX) {
                render_depth_index = RENDER_DEPTH_FAR_INDEX;
            } else if (render_depth_index < RENDER_DEPTH_NEAR_INDEX) {
                render_depth_index = RENDER_DEPTH_NEAR_INDEX;
            }
        } else {
            //＊＊＊ 2Dで特別な描画深度指定有り ＊＊＊
            render_depth_index = specal_render_depth_index + prm_pActor->_z; //_z値がプライオリティ兼描画深度;
            //下限カット
            if (render_depth_index > ALL_RENDER_DEPTH_INDEXS_NUM-1) {
                render_depth_index = ALL_RENDER_DEPTH_INDEXS_NUM-1;
            }
        }

        if (_papFirstRenderActor[render_depth_index] == nullptr) {
            //2Dでそのprm_render_depth_indexで最初のアクターの場合
            prm_pActor->_pNextRenderActor = nullptr;
            _papFirstRenderActor[render_depth_index] = prm_pActor;
            _papLastRenderActor[render_depth_index] = prm_pActor;
        } else {
            //2Dで同一深度で2Dの場合、連結リストのお尻に追加していく(その深度で後に描画される)
            //つまり、最後に appendChild() すればするほど、描画順が後になり、プライオリティが高いくなる設計
            FigureActor* pActorTmp = _papLastRenderActor[render_depth_index];
            pActorTmp->_pNextRenderActor = prm_pActor;
            prm_pActor->_pNextRenderActor = nullptr;
            _papLastRenderActor[render_depth_index] = prm_pActor;
        }

    } else {
        //＊＊＊３Dの場合
        if (specal_render_depth_index < 0) { //特別な描画深度指定無し
            //＊＊＊ 3Dで特別な描画深度指定無し ＊＊＊
            dxcoord dep = -prm_pActor->_dest_from_vppln_infront; //オブジェクトの視点からの距離(DIRECTX距離)
            if (dep < 0.0) {
                render_depth_index = RENDER_DEPTH_NEAR_INDEX;
            } else if (0.0 <= dep && dep < _dep_resolution) {
                render_depth_index = RENDER_DEPTH_NEAR_INDEX + _paDep2Lv[DX_PX(dep)];
            } else {
                render_depth_index = RENDER_DEPTH_FAR_INDEX;
            }
            if (_papFirstRenderActor[render_depth_index] == nullptr) {
                //そのprm_render_depth_indexで最初のアクターの場合
                prm_pActor->_pNextRenderActor = nullptr;
                _papFirstRenderActor[render_depth_index] = prm_pActor;
                _papLastRenderActor[render_depth_index] = prm_pActor;
            } else {
                if (!prm_pActor->_zwriteenable) {
                    //Z値を書き込ま無いオブジェクトはお尻に追加。
                    //深度の深い順に表示は行われるが。
                    //同一の深度の「先頭」に追加 ＝ その深度で始めに描画される => 背面に描画される
                    //同一の深度の「お尻」に追加 ＝ その深度で後に描画される   => 手前に描画される
                    //レーザー等が綺麗に描画される可能性が高い。
                    FigureActor* pActorTmp = _papLastRenderActor[render_depth_index];
                    pActorTmp->_pNextRenderActor = prm_pActor;
                    prm_pActor->_pNextRenderActor = nullptr;
                    _papLastRenderActor[render_depth_index] = prm_pActor;
                } else {
                    //Z値を書き込むオブジェクト
                    //Z値を書き込むアクターは基本は「先頭」に追加したい。
                    //透明でない場合は、背後に隠れるオブジェクトの描画処理が省略さ、描画効率が上がるため。
                    //しかし、半透明の場合は、自然に見えるためには、より「お尻」に追加するべきなのか
                    if (prm_pActor->getAlpha() < 1.0f) {
                        //同一深度で半透明の場合、前に追加と、お尻に追加を交互に行う。
                        //なんでまたそんなことをするかというと、Zバッファ有りのオブジェクトに半透明オブジェクトと交差した場合、
                        //同一深度なので、プライオリティ（描画順）によって透けない部分が生じてしまう。
                        //これを描画順を毎フレーム変化させることで、交互表示でちらつかせ若干のごまかしを行う。
                        //TODO:(課題)２、３のオブジェクトの交差は場合は見た目にも許容できるが、たくさん固まると本当にチラチラする。
                        if ((_frame_of_behaving & 1) == 1) { //奇数
                            //前に追加
                            FigureActor* pActorTmp = _papFirstRenderActor[render_depth_index];
                            prm_pActor->_pNextRenderActor = pActorTmp;
                            _papFirstRenderActor[render_depth_index] = prm_pActor;
                        } else {
                            //お尻に追加
                            FigureActor* pActorTmp = _papLastRenderActor[render_depth_index];
                            pActorTmp->_pNextRenderActor = prm_pActor;
                            prm_pActor->_pNextRenderActor = nullptr;
                            _papLastRenderActor[render_depth_index] = prm_pActor;
                        }
                    } else {
                        //半透明ではない場合、深度を＋１して「先頭」に追加。
                        //CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_FAR > 0 が保証されているので、
                        //_papFirstRenderActor[render_depth_index+1] は要素オーバーにならない
                        render_depth_index++;
                        if (_papFirstRenderActor[render_depth_index] == nullptr) {
                            //そのprm_render_depth_indexで最初のアクターの場合
                            prm_pActor->_pNextRenderActor = nullptr;
                            _papFirstRenderActor[render_depth_index] = prm_pActor;
                            _papLastRenderActor[render_depth_index] = prm_pActor;
                        } else {
                            FigureActor* pActorTmp = _papFirstRenderActor[render_depth_index];
                            prm_pActor->_pNextRenderActor = pActorTmp;
                            _papFirstRenderActor[render_depth_index] = prm_pActor;
                        }
                    }
                }
            }

        } else {
            //＊＊＊ 3Dで特別な描画深度指定有り
            render_depth_index = specal_render_depth_index;
            if (_papFirstRenderActor[render_depth_index] == nullptr) {
                //そのprm_render_depth_indexで最初のアクターの場合
                prm_pActor->_pNextRenderActor = nullptr;
                _papFirstRenderActor[render_depth_index] = prm_pActor;
                _papLastRenderActor[render_depth_index] = prm_pActor;
            } else {
                //お尻に追加
                FigureActor* pActorTmp = _papLastRenderActor[render_depth_index];
                pActorTmp->_pNextRenderActor = prm_pActor;
                prm_pActor->_pNextRenderActor = nullptr;
                _papLastRenderActor[render_depth_index] = prm_pActor;
//                    //前に追加
//                    FigureActor* pActorTmp = _papFirstRenderActor[render_depth_index];
//                    prm_pActor->_pNextRenderActor = pActorTmp;
//                    _papFirstRenderActor[render_depth_index] = prm_pActor;
            }
        }
    }
    return render_depth_index;
}

void Spacetime::cnvViewCoordToWorld(coord prm_view_x, coord prm_view_y, coord prm_depth,
                                    coord& out_world_x, coord& out_world_y, coord& out_world_z) {
    Camera* pCam = getCamera();
    dxcoord target_dep_d = C_DX(prm_depth); //オブジェクトの距離
    dxcoord zt_rate = RCNV_to_0_1(pCam->_zn, pCam->_zf, target_dep_d);
    D3DXMATRIX matScreen = D3DXMATRIX(
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        C_PX(prm_view_x), C_PX(prm_view_y), 0, 1.0f,  //Near Z=0
        C_PX(prm_view_x), C_PX(prm_view_y), 1, 1.0f   //Far  Z=1
    );
    D3DXMATRIX matWorldCoords = matScreen * pCam->_matInvViewPort_Proj_View;
    //下記を計算最適化
    //    const float near_W = out._34;
    //    const float far_W = out._44;
    //    const float MinZ = pCam->_viewport.MinZ; // = 0
    //    const float MaxZ = pCam->_viewport.MaxZ; // = 1
    //    dxcoord x = RCNV(MinZ, MaxZ, zt_rate, out._31 / near_W, out._41 / far_W);
    //    dxcoord y = RCNV(MinZ, MaxZ, zt_rate, out._32 / near_W, out._42 / far_W);
    //    dxcoord z = RCNV(MinZ, MaxZ, zt_rate, out._33 / near_W, out._43 / far_W);
    const float near_W = matWorldCoords._34;
    const float far_W = matWorldCoords._44;
    const float W = (far_W*near_W);
    const float near_W_zt_rate = (near_W * zt_rate);
    dxcoord x = (near_W_zt_rate*matWorldCoords._41 - ((zt_rate - 1) * (far_W*matWorldCoords._31))) / W;
    dxcoord y = (near_W_zt_rate*matWorldCoords._42 - ((zt_rate - 1) * (far_W*matWorldCoords._32))) / W;
    dxcoord z = (near_W_zt_rate*matWorldCoords._43 - ((zt_rate - 1) * (far_W*matWorldCoords._33))) / W;
    out_world_x = DX_C(x);
    out_world_y = DX_C(y);
    out_world_z = DX_C(z);
}

void Spacetime::cnvWorldCoordToView(coord prm_world_x, coord prm_world_y, coord prm_world_z,
                                    coord& out_view_x, coord& out_view_y) {
    //視錐台面からの距離の割合で求める
    const dxcoord fX = C_DX(prm_world_x);
    const dxcoord fY = C_DX(prm_world_y);
    const dxcoord fZ = C_DX(prm_world_z);
    Camera *pCam = getCamera();
    const D3DXPLANE *pPlnTop = &(pCam->_plnTop);
    dxcoord len_top = -(pPlnTop->a*fX + pPlnTop->b*fY + pPlnTop->c*fZ + pPlnTop->d);
    const D3DXPLANE *pPlnBottom = &(pCam->_plnBottom);
    dxcoord len_bottom = -(pPlnBottom->a*fX + pPlnBottom->b*fY + pPlnBottom->c*fZ + pPlnBottom->d);
    const D3DXPLANE *pPlnLeft = &(pCam->_plnLeft);
    dxcoord len_left = -(pPlnLeft->a*fX + pPlnLeft->b*fY + pPlnLeft->c*fZ + pPlnLeft->d);
    const D3DXPLANE *pPlnRight = &(pCam->_plnRight);
    dxcoord len_rigth = -(pPlnRight->a*fX + pPlnRight->b*fY + pPlnRight->c*fZ + pPlnRight->d);
    dxcoord x =  PX_DX(_primary_buffer_source_width ) * (len_left / (len_left+len_rigth ) );
    dxcoord y =  PX_DX(_primary_buffer_source_height) * (len_top  / (len_top +len_bottom) );
    out_view_x = DX_C(x);
    out_view_y = DX_C(y);
}

void Spacetime::executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
#ifdef MY_DEBUG
    if (_is_running_processHitCheck == false) {
        throwCriticalException("executeWorldHitCheck() は、processHitCheck() 内でしか実行できません。");
    }
#endif
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        Spacetime::_pWorldQuadtreeRounder->executeAll(prm_kind_groupA, prm_kind_groupB);
    } else {
        Spacetime::_pWorldOctreeRounder->executeAll(prm_kind_groupA, prm_kind_groupB);
    }
}

void Spacetime::executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
#ifdef MY_DEBUG
    if (_is_running_processHitCheck == false) {
        throwCriticalException("executeViewHitCheck() は、processHitCheck() 内でしか実行できません。");
    }
#endif
    Spacetime::_pViewQuadtreeRounder->executeAll(prm_kind_groupA, prm_kind_groupB);
}
void Spacetime::processFinal() {
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        Spacetime::_pWorldQuadtree->clearAllElem();
    } else {
        Spacetime::_pWorldOctree->clearAllElem();
    }
    Spacetime::_pViewQuadtree->clearAllElem();
}
void Spacetime::dumpRenderDepthOrder() {
    for (int i = 0; i < ALL_RENDER_DEPTH_INDEXS_NUM; i++) {
        FigureActor* pDrawActor = _papFirstRenderActor[i];
        if (!pDrawActor) {
            continue;
        }
        if (i < RENDER_DEPTH_NEAR_INDEX) {
            _TRACE_N_("EX_NEAR_DEP["<<i<<"]");
        } else if (RENDER_DEPTH_NEAR_INDEX <= i && i <= RENDER_DEPTH_FAR_INDEX) {
            _TRACE_N_("NORMAL_DEP ["<<i<<"]");
        } else if (i > RENDER_DEPTH_FAR_INDEX) {
            _TRACE_N_("EX_FAR_DEP ["<<i<<"]");
        }
        while(pDrawActor) {
            _TRACE_N_("->["<<pDrawActor->getName()<<"]"<<(pDrawActor->_id)<<"");
            pDrawActor = pDrawActor->_pNextRenderActor;
        }
        _TRACE_N_("\n");
    }
}

Spacetime::~Spacetime() {
    GGAF_DELETE(_pRing_pSeArray);
    GGAF_DELETEARR(_paDep2Lv);
    GGAF_DELETEARR(_papFirstRenderActor);
    GGAF_DELETEARR(_papLastRenderActor);

#ifdef MY_DEBUG
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        _TRACE_("World四分木 -->");
        Spacetime::_pWorldQuadtree->putTree();
        _TRACE_("<--World四分木");
    } else {
        _TRACE_("World八分木 -->");
        Spacetime::_pWorldOctree->putTree();
        _TRACE_("<--World八分木");
    }
    _TRACE_("View四分木 -->");
    Spacetime::_pViewQuadtree->putTree();
    _TRACE_("<--View四分木");
#endif
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        GGAF_DELETE(Spacetime::_pWorldQuadtree);
        GGAF_DELETE(Spacetime::_pWorldQuadtreeRounder);
    } else {
        GGAF_DELETE(Spacetime::_pWorldOctree);
        GGAF_DELETE(Spacetime::_pWorldOctreeRounder);
    }
    GGAF_DELETE(Spacetime::_pViewQuadtree);
    GGAF_DELETE(Spacetime::_pViewQuadtreeRounder);
}
