#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxBoardSetModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_TEX1);
int GgafDxBoardSetModel::_draw_set_num_LastDraw = -1;
GgafDxBoardSetModel::GgafDxBoardSetModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxBoardSetModel::GgafDxBoardSetModel(" << _model_name << ")");

    _fSize_BoardSetModelWidthPx = 32.0f;
    _fSize_BoardSetModelHeightPx = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _obj_model |= Obj_GgafDxBoardSetModel;

    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, NULL, 10);
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        _TRACE_("GgafDxBoardSetModel("<<prm_model_name<<") の同時描画セット数省略のため、最大の28がセットされます。");
        _set_num = 28;
    } else {
        _set_num = num;
        if (_set_num > 28) {
            _TRACE_("GgafDxBoardSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大の28がセットですが、それ以上のセット数です。意図していますか？_set_num="<<_set_num);
        }
    }
    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreBoardSetModel(GgafDxBoardSetModel*)
    //で行うようにした。要参照。
}

//描画
HRESULT GgafDxBoardSetModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxBoardSetModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_("GgafDxBoardSetModel::draw() "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    //対象Actor
    GgafDxBoardSetActor* pTargetActor = (GgafDxBoardSetActor*)prm_pActor_Target;
    //対象BoardSetActorのエフェクトラッパ
    GgafDxBoardSetEffect* pBoardSetEffect = (GgafDxBoardSetEffect*)prm_pActor_Target->_pEffect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pBoardSetEffect->_pID3DXEffect;

    HRESULT hr;
    //モデルが同じならば頂点バッファ等、の設定はスキップできる
    if (GgafDxModelManager::_pModelLastDraw  != this) {
        GgafDxGod::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertex_unit);
        GgafDxGod::_pID3DDevice9->SetFVF(GgafDxBoardSetModel::FVF);
        GgafDxGod::_pID3DDevice9->SetTexture(0, _papTextureCon[0]->fetch()->_pIDirect3DBaseTexture9);
        GgafDxGod::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }

    if (GgafDxEffectManager::_pEffect_Active != pBoardSetEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)  {
        if (GgafDxEffectManager::_pEffect_Active) {
           TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
            hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() EndPass() に失敗しました。");
            hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() End() に失敗しました。");

#ifdef MY_DEBUG
            if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                GgafDxEffectManager::_pEffect_Active->_begin = false;
            }
#endif

        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxBoardSetActor::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name<<"("<<pBoardSetEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pBoardSetEffect->_begin == true) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            pBoardSetEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxBoardSetModel::draw() CommitChanges() に失敗しました。");
    }
    TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
    GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                   _paIndexParam[prm_draw_set_num-1].BaseVertexIndex,
                                                   _paIndexParam[prm_draw_set_num-1].MinIndex,
                                                   _paIndexParam[prm_draw_set_num-1].NumVertices,
                                                   _paIndexParam[prm_draw_set_num-1].StartIndex,
                                                   _paIndexParam[prm_draw_set_num-1].PrimitiveCount);

    //前回描画モデル保持
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxBoardSetModel::_draw_set_num_LastDraw = prm_draw_set_num;
    GgafDxEffectManager::_pEffect_Active = pBoardSetEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDxBoardSetModel::restore() {
    TRACE3("GgafDxBoardSetModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreBoardSetModel(this);
    TRACE3("GgafDxBoardSetModel::restore() " << _model_name << " end");
}

void GgafDxBoardSetModel::onDeviceLost() {
    TRACE3("GgafDxBoardSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDxBoardSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxBoardSetModel::release() {
    TRACE3("GgafDxBoardSetModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);
    if (_papTextureCon) {
        if (_papTextureCon[0]) {
            _papTextureCon[0]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon);
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);
    //TODO:親クラスメンバをDELETEするのはややきたないか
    DELETEARR_IMPOSSIBLE_NULL(_paMaterial_default);
    TRACE3("GgafDxBoardSetModel::release() " << _model_name << " end");
}

GgafDxBoardSetModel::~GgafDxBoardSetModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

