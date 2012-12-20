#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;

//DWORD GgafDxMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
DWORD GgafDxMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX3 |
                                    D3DFVF_TEXCOORDSIZE2(0) | // real texture coord
                                    D3DFVF_TEXCOORDSIZE3(1) | // tangent
                                    D3DFVF_TEXCOORDSIZE3(2)   // binormal
                                    );
GgafDxMeshModel::GgafDxMeshModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxMeshModel::GgafDxMeshModel(" << _model_name << ")");
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;

    _pIDirect3DVertexBuffer9 = nullptr;
    _pIDirect3DIndexBuffer9 = nullptr;
    _paVtxBuffer_org = nullptr;
    _paIdxBuffer_org = nullptr;
    _paIndexParam = nullptr;
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;
    _nMaterialListGrp = 0;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _obj_model |= Obj_GgafDxMeshModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreMeshModel(GgafDxMeshModel*)
    //で行うようにした。要参照。
}

//描画
HRESULT GgafDxMeshModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    //対象アクター
    //GgafDxMeshActor* pTargetActor = (GgafDxMeshActor*)prm_pActor_Target;
    GgafDxDrawableActor* pTargetActor = prm_pActor_Target;
    //対象MeshActorのエフェクトラッパ
    GgafDxMeshEffect* pMeshEffect = (GgafDxMeshEffect*)prm_pActor_Target->_pEffect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        //頂点バッファとインデックスバッファを設定
        GgafDxGod::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9,  0, _size_vertex_unit);
        GgafDxGod::_pID3DDevice9->SetFVF(GgafDxMeshModel::FVF);
        GgafDxGod::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) に失敗しました。");
    }

    //描画
    for (UINT i = 0; i < _nMaterialListGrp; i++) {
        INDEXPARAM& idxparam = _paIndexParam[i];
        material_no = idxparam.MaterialNo;
        if (GgafDxModelManager::_pModelLastDraw != this || _nMaterialListGrp != 1) {
            if (_papTextureCon[material_no]) {
                //テクスチャをs0レジスタにセット
                GgafDxGod::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->fetch()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDxMeshModel::draw("<<prm_pActor_Target->getName()<<") テクスチャがありません。white.pngが設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                GgafDxGod::_pID3DDevice9->SetTexture(0, nullptr);
            }
        }
        hr = pID3DXEffect->SetValue(pMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");

        if ((GgafDxEffectManager::_pEffect_Active != pMeshEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            //本モデル描画初回
            if (GgafDxEffectManager::_pEffect_Active) {
                TRACE4("前回_pEffect_Active != pMeshEffect (" <<(GgafDxEffectManager::_pEffect_Active->_effect_name)<<"!="<<(pMeshEffect->_effect_name)<<")");
                TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() EndPass() に失敗しました。");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() End() に失敗しました。");

#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name<<"("<<pMeshEffect<<")");
            hr = pID3DXEffect->Begin( &_numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pMeshEffect->_begin == true) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_Active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pMeshEffect->_begin = true;
            }
#endif

        } else {
            //前回描画と同じモデル
            hr = pID3DXEffect->CommitChanges(); //マテリアルをコミットしなければいけない。
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() CommitChanges() に失敗しました。");
        }
        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
        GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                       idxparam.BaseVertexIndex,
                                                       idxparam.MinIndex,
                                                       idxparam.NumVertices,
                                                       idxparam.StartIndex,
                                                       idxparam.PrimitiveCount);
        if (_numPass >= 2) { //２パス目以降が存在
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() １パス目 EndPass() に失敗しました。");
            for (UINT pass = 1; pass < _numPass; pass++) {
                hr = pID3DXEffect->BeginPass(pass);
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() "<<pass+1<<"パス目 BeginPass("<<pass<<") に失敗しました。");
                GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                               idxparam.BaseVertexIndex,
                                                               idxparam.MinIndex,
                                                               idxparam.NumVertices,
                                                               idxparam.StartIndex,
                                                               idxparam.PrimitiveCount);
                hr = pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() "<<pass+1<<"パス目 EndPass() に失敗しました。");
            }
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() １パス目 BeginPass(0) に失敗しました。");
        }
        GgafGod::_num_actor_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pMeshEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    return D3D_OK;
}

void GgafDxMeshModel::restore() {
    TRACE3("GgafDxMeshModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreMeshModel(this);
    TRACE3("GgafDxMeshModel::restore() " << _model_name << " end");
}

void GgafDxMeshModel::onDeviceLost() {
    TRACE3("GgafDxMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDxMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMeshModel::release() {
    TRACE3("GgafDxMeshModel::release() " << _model_name << " start");

    //テクスチャを解放
    if (_papTextureCon) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureCon[i]) {
                TRACE3("close() _papTextureCon["<<i<<"]->"<<(_papTextureCon[i]->getIdStr()));
                _papTextureCon[i]->close();
            }
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //テクスチャの配列

    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);

    DELETEARR_IMPOSSIBLE_NULL(_paVtxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_paIdxBuffer_org);
    DELETE_IMPOSSIBLE_NULL(_pModel3D);
    //_pMeshesFront は _pModel3D をDELETEしているのでする必要は無い
    _pMeshesFront = nullptr;
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    DELETEARR_IMPOSSIBLE_NULL(_paMaterial_default);


    TRACE3("GgafDxMeshModel::release() " << _model_name << " end");

}
GgafDxMeshModel::~GgafDxMeshModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}


