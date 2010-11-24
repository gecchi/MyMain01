#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9BoardSetModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_TEX1);
int GgafDx9BoardSetModel::_draw_set_num_LastDraw = -1;
GgafDx9BoardSetModel::GgafDx9BoardSetModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE3("GgafDx9BoardSetModel::GgafDx9BoardSetModel(" << _model_name << ")");

    _fSize_BoardSetModelWidthPx = 32.0f;
    _fSize_BoardSetModelHeightPx = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pattno_max = 1;

    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _paRectUV = NULL;

    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, NULL, 10);
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        _TRACE_("GgafDx9BoardSetModel("<<prm_model_name<<") の同時描画セット数省略のため、最大の28がセットされます。");
        _set_num = 28;
    } else {
        _set_num = num;
        if (_set_num > 28) {
            _TRACE_("GgafDx9BoardSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大の28がセットですが、それ以上のセット数です。意図していますか？_set_num="<<_set_num);
        }
    }
    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDx9ModelManager::restoreBoardSetModel(GgafDx9BoardSetModel*)
    //で行うようにした。要参照。
}

//描画
HRESULT GgafDx9BoardSetModel::draw(GgafDx9DrawableActor* prm_pActor_Target) {
    TRACE4("GgafDx9BoardSetModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());

    //対象Actor
    static GgafDx9BoardSetActor* pTargetActor;
    pTargetActor = (GgafDx9BoardSetActor*)prm_pActor_Target;
    //対象BoardSetActorのエフェクトラッパ
    static GgafDx9BoardSetEffect* pBoardSetEffect;
    pBoardSetEffect = pTargetActor->_pBoardSetEffect;
    //対象エフェクト
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pBoardSetEffect->_pID3DXEffect;



	    _TRACE_("1 GgafDx9BoardSetModel::draw pBoardSetEffect->_begin="<<pBoardSetEffect->_begin);


    int draw_set_num = pTargetActor->_draw_set_num;

    static HRESULT hr;
    //モデルが同じならば頂点バッファ等、の設定はスキップできる
    if (GgafDx9ModelManager::_pModelLastDraw  != this) {
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertex_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9BoardSetModel::FVF);
        GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[0]->refer()->_pIDirect3DTexture9);
        GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_power, _fPowerBlink);
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetActor::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_threshold, _fBlinkThreshold);
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetActor::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }

    if (GgafDx9EffectManager::_pEffect_Active != pBoardSetEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)  {
        if (GgafDx9EffectManager::_pEffect_Active != NULL) {
           TRACE4("EndPass("<<GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name<<"("<<GgafDx9EffectManager::_pEffect_Active<<")");
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDx9BoardSetActor::draw() EndPass() に失敗しました。");
            hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDx9BoardSetActor::draw() End() に失敗しました。");

            ////
            if (GgafDx9EffectManager::_pEffect_Active->_begin == false) {
                throwGgafCriticalException("begin していません "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                GgafDx9EffectManager::_pEffect_Active->_begin = false;

//					    _TRACE_("2 GgafDx9BoardSetModel::draw pBoardSetEffect("<<pBoardSetEffect<<")->_begin="<<pBoardSetEffect->_begin);
//						_TRACE_("2 GgafDx9EffectManager::_pEffect_Active("<<GgafDx9EffectManager::_pEffect_Active<<")->_begin="<<GgafDx9EffectManager::_pEffect_Active->_begin);
            }
            ////

        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDx9BoardSetActor::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name<<"("<<pBoardSetEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetActor::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetActor::draw() BeginPass(0) に失敗しました。");

        ////
        if (pBoardSetEffect->_begin == true) {
            throwGgafCriticalException("End していません "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            pBoardSetEffect->_begin = true;

//					    _TRACE_("3 GgafDx9BoardSetModel::draw pBoardSetEffect("<<pBoardSetEffect<<")->_begin="<<pBoardSetEffect->_begin);
//						if (GgafDx9EffectManager::_pEffect_Active) {
//						_TRACE_("3 GgafDx9EffectManager::_pEffect_Active("<<GgafDx9EffectManager::_pEffect_Active<<")->_begin="<<GgafDx9EffectManager::_pEffect_Active->_begin);
//							} else {
//						_TRACE_("3 GgafDx9EffectManager::_pEffect_Active("<<GgafDx9EffectManager::_pEffect_Active<<")");
//							}
        }
        ////

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw() CommitChanges() に失敗しました。");
    }
    TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
    GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                    _paIndexParam[draw_set_num-1].BaseVertexIndex,
                                                    _paIndexParam[draw_set_num-1].MinIndex,
                                                    _paIndexParam[draw_set_num-1].NumVertices,
                                                    _paIndexParam[draw_set_num-1].StartIndex,
                                                    _paIndexParam[draw_set_num-1].PrimitiveCount);

    //前回描画モデル保持
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9BoardSetModel::_draw_set_num_LastDraw = draw_set_num;
    GgafDx9EffectManager::_pEffect_Active = pBoardSetEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDx9BoardSetModel::restore() {
    TRACE3("GgafDx9BoardSetModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreBoardSetModel(this);
    TRACE3("GgafDx9BoardSetModel::restore() " << _model_name << " end");
}

void GgafDx9BoardSetModel::onDeviceLost() {
    TRACE3("GgafDx9BoardSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9BoardSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9BoardSetModel::release() {
    TRACE3("GgafDx9BoardSetModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);
    if (_papTextureCon) {
        if (_papTextureCon[0]) {
            _papTextureCon[0]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon);
    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);
    //TODO:親クラスメンバをDELETEするのはややきたないか
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    TRACE3("GgafDx9BoardSetModel::release() " << _model_name << " end");
}

GgafDx9BoardSetModel::~GgafDx9BoardSetModel() {
    //release();
    //はGgafDx9ModelConnection::processReleaseResource(GgafDx9Model* prm_pResource) で呼び出される
}

