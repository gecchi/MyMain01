#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9MeshSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
int GgafDx9MeshSetModel::_draw_set_num_LastDraw = -1;
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9MeshSetModel::GgafDx9MeshSetModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE3("GgafDx9MeshSetModel::GgafDx9MeshSetModel(" << _model_name << ")");
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
        _TRACE_("GgafDx9MeshSetModel("<<prm_model_name<<") のセット数省略のため、標準の最大の15セットが設定されます。");
        _set_num = 15;
    } else {
        _set_num = num;
        if (_set_num > 15) {
            _TRACE_("GgafDx9MeshSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大は15セットがですがそれ以上が設定されています。意図していますか？ _set_num="<<_set_num<<"。");
        }
    }
    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _pa_nMaterialListGrp = NULL;
    _paVtxBuffer_org = NULL;
    _paIdxBuffer_org = NULL;
    _papaIndexParam = NULL;
    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどのメンバー初期化は
    //void GgafDx9ModelManager::restoreMeshSetModel(GgafDx9MeshSetModel*)
    //で行うようにした。要参照。
    _TRACE_("GgafDx9MeshSetModel::GgafDx9MeshSetModel(" << _model_name << ") End");
}

//描画
HRESULT GgafDx9MeshSetModel::draw(GgafDx9DrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDx9MeshSetModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
    //対象アクター
    GgafDx9MeshSetActor* pTargetActor = (GgafDx9MeshSetActor*)prm_pActor_Target;
    //対象MeshSetActorのエフェクトラッパ
    GgafDx9MeshSetEffect* pMeshSetEffect = (GgafDx9MeshSetEffect*)prm_pActor_Target->_pEffect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;

    //モデルが同じでかつ、セット数も同じならば頂点バッファ、インデックスバッファの設定はスキップできる
    if (GgafDx9ModelManager::_pModelLastDraw  != this) {
        //頂点バッファとインデックスバッファを設定
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9,  0, _size_vertex_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9MeshSetModel::FVF);
        GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDx9MeshModel::draw() SetFloat(_h_specular_power) に失敗しました。");
    }


    //描画
    for (UINT material_grp_index = 0; material_grp_index < _pa_nMaterialListGrp[prm_draw_set_num-1]; material_grp_index++) {
        // TODO
        //モデルが同じでかつ、セット数も同じかつ、マテリアルNOが１つしかないならば、テクスチャ設定もスキップできる
        if (GgafDx9ModelManager::_pModelLastDraw  != this      ||
            //GgafDx9MeshSetModel::_draw_set_num_LastDraw != draw_set_num ||
            _pa_nMaterialListGrp[prm_draw_set_num-1] != 1)
        {
            material_no = _papaIndexParam[prm_draw_set_num-1][material_grp_index].MaterialNo;
            if (_papTextureCon[material_no]) {
                //テクスチャをs0レジスタにセット
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->refer()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDx9MeshSetModel::draw("<<prm_pActor_Target->getName()<<") テクスチャがありません。white.pngが設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
            //MaterialDiffuseはGgafDx9MeshSetActor側でマテリアルを設定する。マテリアル色は単色とする。
            //理由はGgafDx9MeshSetActorのメモ【GgafDx9MeshSetActorのマテリアルカラーについて】を参照
        }


        if (material_grp_index == 0 && (GgafDx9EffectManager::_pEffect_Active != pMeshSetEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique)) {
            if (GgafDx9EffectManager::_pEffect_Active) {
                TRACE4("EndPass("<<GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name<<"("<<GgafDx9EffectManager::_pEffect_Active<<")");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() EndPass() に失敗しました。");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() End() に失敗しました。");

#ifdef MY_DEBUG
                if (GgafDx9EffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDx9EffectManager::_pEffect_Active->_begin = false;
                }
#endif

            }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDx9MeshSetModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name<<"("<<pMeshSetEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pMeshSetEffect->_begin == true) {
                throwGgafCriticalException("End していません "<<(GgafDx9EffectManager::_pEffect_Active==NULL?"NULL":GgafDx9EffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pMeshSetEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() CommitChanges() に失敗しました。");
        }
        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
        GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                        _papaIndexParam[prm_draw_set_num-1][material_grp_index].BaseVertexIndex,
                                        _papaIndexParam[prm_draw_set_num-1][material_grp_index].MinIndex,
                                        _papaIndexParam[prm_draw_set_num-1][material_grp_index].NumVertices,
                                        _papaIndexParam[prm_draw_set_num-1][material_grp_index].StartIndex,
                                        _papaIndexParam[prm_draw_set_num-1][material_grp_index].PrimitiveCount);
        GgafGod::_num_actor_drawing++;
    }
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9MeshSetModel::_draw_set_num_LastDraw = prm_draw_set_num;
    GgafDx9EffectManager::_pEffect_Active = pMeshSetEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    return D3D_OK;
}

void GgafDx9MeshSetModel::restore() {
    TRACE3("GgafDx9MeshSetModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreMeshSetModel(this);
    TRACE3("GgafDx9MeshSetModel::restore() " << _model_name << " end");
}

void GgafDx9MeshSetModel::onDeviceLost() {
    TRACE3("GgafDx9MeshSetModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9MeshSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9MeshSetModel::release() {
    TRACE3("GgafDx9MeshSetModel::release() " << _model_name << " start");

    //テクスチャを解放
    if (_papTextureCon) {
        for (int i = 0; i < (int)_dwNumMaterials; i++) {
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

    TRACE3("GgafDx9MeshSetModel::release() " << _model_name << " end");

}
GgafDx9MeshSetModel::~GgafDx9MeshSetModel() {
    //release();
    //はGgafDx9ModelConnection::processReleaseResource(GgafDx9Model* prm_pResource) で呼び出される
}

