#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxMeshSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
int GgafDxMeshSetModel::_draw_set_num_LastDraw = -1;
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDxMeshSetModel::GgafDxMeshSetModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxMeshSetModel::GgafDxMeshSetModel(" << _model_name << ")");
    _pModel3D = NULL;
    _pMeshesFront = NULL;
    // prm_model_name には "xxxxxx" or "8/xxxxx" が、渡ってくる。
    // 同時描画セット数が8という意味です。
    // モーフターゲット数が違うモデルは、別モデルという扱いにするため、モデル名に数値を残そうかな。
    // モデル名から同時描画セット数指定があれば取り出す。無ければ8
    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, NULL, 10);
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        _TRACE_("GgafDxMeshSetModel("<<prm_model_name<<") のセット数省略のため、標準の最大の15セットが設定されます。");
        _set_num = 15;
    } else {
        _set_num = num;
        if (_set_num > 15) {
            _TRACE_("GgafDxMeshSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大は15セットがですがそれ以上が設定されています。意図していますか？ _set_num="<<_set_num<<"。");
        }
    }
    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _pa_nMaterialListGrp = NULL;
    _paVtxBuffer_org = NULL;
    _paIdxBuffer_org = NULL;
    _papaIndexParam = NULL;
    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどのメンバー初期化は
    //void GgafDxModelManager::restoreMeshSetModel(GgafDxMeshSetModel*)
    //で行うようにした。要参照。
    _TRACE_("GgafDxMeshSetModel::GgafDxMeshSetModel(" << _model_name << ") End");
}

//描画
HRESULT GgafDxMeshSetModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxMeshSetModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
    //対象アクター
    GgafDxMeshSetActor* pTargetActor = (GgafDxMeshSetActor*)prm_pActor_Target;
    //対象MeshSetActorのエフェクトラッパ
    GgafDxMeshSetEffect* pMeshSetEffect = (GgafDxMeshSetEffect*)prm_pActor_Target->_pEffect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;

    //モデルが同じでかつ、セット数も同じならば頂点バッファ、インデックスバッファの設定はスキップできる
    if (GgafDxModelManager::_pModelLastDraw  != this) {
        //頂点バッファとインデックスバッファを設定
        GgafDxGod::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9,  0, _size_vertex_unit);
        GgafDxGod::_pID3DDevice9->SetFVF(GgafDxMeshSetModel::FVF);
        GgafDxGod::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) に失敗しました。");
    }

    //描画
    for (UINT material_grp_index = 0; material_grp_index < _pa_nMaterialListGrp[prm_draw_set_num-1]; material_grp_index++) {
        // TODO
        //モデルが同じでかつ、セット数も同じかつ、マテリアルNOが１つしかないならば、テクスチャ設定もスキップできる
        if (GgafDxModelManager::_pModelLastDraw  != this      ||
            //GgafDxMeshSetModel::_draw_set_num_LastDraw != draw_set_num ||
            _pa_nMaterialListGrp[prm_draw_set_num-1] != 1)
        {
            material_no = _papaIndexParam[prm_draw_set_num-1][material_grp_index].MaterialNo;
            if (_papTextureCon[material_no]) {
                //テクスチャをs0レジスタにセット
                GgafDxGod::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->fetch()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDxMeshSetModel::draw("<<prm_pActor_Target->getName()<<") テクスチャがありません。white.pngが設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                GgafDxGod::_pID3DDevice9->SetTexture(0, NULL);
            }
            //MaterialDiffuseはGgafDxMeshSetActor側でマテリアルを設定する。マテリアル色は単色とする。
            //理由はGgafDxMeshSetActorのメモ【GgafDxMeshSetActorのマテリアルカラーについて】を参照
        }

        if (material_grp_index == 0 && (GgafDxEffectManager::_pEffect_Active != pMeshSetEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)) {
            if (GgafDxEffectManager::_pEffect_Active) {
                TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() EndPass() に失敗しました。");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() End() に失敗しました。");
#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_Active->_begin = false;
                }
#endif
            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxMeshSetModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name<<"("<<pMeshSetEffect<<")");
            //UINT numPass;
            hr = pID3DXEffect->Begin(&_numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pMeshSetEffect->_begin == true) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pMeshSetEffect->_begin = true;
            }
#endif
        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() CommitChanges() に失敗しました。");
        }
        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
        GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                       _papaIndexParam[prm_draw_set_num-1][material_grp_index].BaseVertexIndex,
                                                       _papaIndexParam[prm_draw_set_num-1][material_grp_index].MinIndex,
                                                       _papaIndexParam[prm_draw_set_num-1][material_grp_index].NumVertices,
                                                       _papaIndexParam[prm_draw_set_num-1][material_grp_index].StartIndex,
                                                       _papaIndexParam[prm_draw_set_num-1][material_grp_index].PrimitiveCount);
        if (_numPass >= 2) { //２パス目以降が存在
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() １パス目 EndPass() に失敗しました。");
            for (UINT i = 1; i < _numPass; i++) {
                hr = pID3DXEffect->BeginPass(i);
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() "<<i+1<<"パス目 BeginPass("<<i<<") に失敗しました。");
                GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                               _papaIndexParam[prm_draw_set_num-1][material_grp_index].BaseVertexIndex,
                                                               _papaIndexParam[prm_draw_set_num-1][material_grp_index].MinIndex,
                                                               _papaIndexParam[prm_draw_set_num-1][material_grp_index].NumVertices,
                                                               _papaIndexParam[prm_draw_set_num-1][material_grp_index].StartIndex,
                                                               _papaIndexParam[prm_draw_set_num-1][material_grp_index].PrimitiveCount);
                hr = pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() "<<i+1<<"パス目 EndPass() に失敗しました。");
            }
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() １パス目 BeginPass(0) に失敗しました。");
        }
        GgafGod::_num_actor_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxMeshSetModel::_draw_set_num_LastDraw = prm_draw_set_num;
    GgafDxEffectManager::_pEffect_Active = pMeshSetEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    return D3D_OK;
}

void GgafDxMeshSetModel::restore() {
    TRACE3("GgafDxMeshSetModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreMeshSetModel(this);
    TRACE3("GgafDxMeshSetModel::restore() " << _model_name << " end");
}

void GgafDxMeshSetModel::onDeviceLost() {
    TRACE3("GgafDxMeshSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDxMeshSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMeshSetModel::release() {
    TRACE3("GgafDxMeshSetModel::release() " << _model_name << " start");

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
    _pMeshesFront = NULL;
    for (int i = 0; i < _set_num; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaIndexParam[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaIndexParam);
    DELETEARR_IMPOSSIBLE_NULL(_pa_nMaterialListGrp);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    DELETEARR_IMPOSSIBLE_NULL(_paMaterial_default);

    TRACE3("GgafDxMeshSetModel::release() " << _model_name << " end");

}
GgafDxMeshSetModel::~GgafDxMeshSetModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

