#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxSpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_TEX1);
GgafDxSpriteSetModel::GgafDxSpriteSetModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxSpriteSetModel::GgafDxSpriteSetModel(" << _model_name << ")");

    _fSize_SpriteSetModelWidthPx = 32.0f;
    _fSize_SpriteSetModelHeightPx = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pIDirect3DVertexBuffer9 = nullptr;
    _pIDirect3DIndexBuffer9 = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _paIndexParam = nullptr;

    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, nullptr, 10);
    pT = strtok(nullptr, "/");
    if (pT == nullptr) {
        _TRACE_("GgafDxSpriteSetModel("<<prm_model_name<<") の同時描画セット数省略。最大の18セットが設定されます。");
        _set_num = 18;
    } else {
        _set_num = num;
        if (_set_num > 18) {
            _TRACE_("GgafDxSpriteSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大の18セットですがそれ以上のセット数です。意図していますか？ _set_num="<<_set_num<<"。");
        }
    }
    _obj_model |= Obj_GgafDxSpriteSetModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreSpriteSetModel(GgafDxSpriteSetModel*)
    //で行うようにした。要参照。
}

//描画
HRESULT GgafDxSpriteSetModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxSpriteSetModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        throwGgafCriticalException("GgafDxSpriteSetModel::draw() "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    //対象Actor
    GgafDxSpriteSetActor* pTargetActor = (GgafDxSpriteSetActor*)prm_pActor_Target;
    //対象SpriteSetActorのエフェクトラッパ
    GgafDxSpriteSetEffect* pSpriteSetEffect = (GgafDxSpriteSetEffect*)prm_pActor_Target->_pEffect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pSpriteSetEffect->_pID3DXEffect;

    static HRESULT hr;
    //モデルが同じならば頂点バッファ等、の設定はスキップできる
    if (GgafDxModelManager::_pModelLastDraw  != this) {
        GgafDxGod::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertex_unit);
        GgafDxGod::_pID3DDevice9->SetFVF(GgafDxSpriteSetModel::FVF);
        GgafDxGod::_pID3DDevice9->SetTexture(0, _papTextureConnection[0]->peek()->_pIDirect3DBaseTexture9);
        GgafDxGod::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }

    if (GgafDxEffectManager::_pEffect_Active != pSpriteSetEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)  {
        if (GgafDxEffectManager::_pEffect_Active) {
            TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
            hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() EndPass() に失敗しました。");
            hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() End() に失敗しました。");

#ifdef MY_DEBUG
            if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                GgafDxEffectManager::_pEffect_Active->_begin = false;
            }
#endif

        }
        TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxSpriteSetActor::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name<<"("<<pSpriteSetEffect<<")");
        hr = pID3DXEffect->Begin( &_numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pSpriteSetEffect->_begin == true) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
        } else {
            pSpriteSetEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() CommitChanges() に失敗しました。");
    }
    TRACE4("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteSetEffect->_effect_name);
    INDEXPARAM& idxparam = _paIndexParam[prm_draw_set_num - 1];
    GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                   idxparam.BaseVertexIndex,
                                                   idxparam.MinIndex,
                                                   idxparam.NumVertices,
                                                   idxparam.StartIndex,
                                                   idxparam.PrimitiveCount);
    if (_numPass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() １パス目 EndPass() に失敗しました。");

        for (UINT pass = 1; pass < _numPass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() "<<pass+1<<"パス目 BeginPass("<<pass<<") に失敗しました。");
            GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                           idxparam.BaseVertexIndex,
                                                           idxparam.MinIndex,
                                                           idxparam.NumVertices,
                                                           idxparam.StartIndex,
                                                           idxparam.PrimitiveCount);
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() "<<pass+1<<"パス目 EndPass() に失敗しました。");
        }

        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxSpriteSetModel::draw() １パス目 BeginPass(0) に失敗しました。");
    }

    //前回描画モデル保持
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pSpriteSetEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDxSpriteSetModel::restore() {
    TRACE3("GgafDxSpriteSetModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreSpriteSetModel(this);
    TRACE3("GgafDxSpriteSetModel::restore() " << _model_name << " end");
}

void GgafDxSpriteSetModel::onDeviceLost() {
    TRACE3("GgafDxSpriteSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDxSpriteSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxSpriteSetModel::release() {
    TRACE3("GgafDxSpriteSetModel::release() " << _model_name << " start");
    GGAF_RELEASE(_pIDirect3DVertexBuffer9);
    GGAF_RELEASE(_pIDirect3DIndexBuffer9);
    if (_papTextureConnection) {
        if (_papTextureConnection[0]) {
            _papTextureConnection[0]->close();
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    GGAF_DELETEARR(_paIndexParam);
    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);
    TRACE3("GgafDxSpriteSetModel::release() " << _model_name << " end");
}

GgafDxSpriteSetModel::~GgafDxSpriteSetModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

