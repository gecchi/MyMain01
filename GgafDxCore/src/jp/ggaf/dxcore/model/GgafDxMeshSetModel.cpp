#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxMeshSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer = nullptr;

GgafDxMeshSetModel::GgafDxMeshSetModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxMeshSetModel::GgafDxMeshSetModel(" << _model_name << ")");
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;
    // prm_model_name には "xxxxxx" or "8/xxxxx" が、渡ってくる。
    // 同時描画セット数が8という意味です。
    // モーフターゲット数が違うモデルは、別モデルという扱いにするため、モデル名に数値を残そうかな。
    // モデル名から同時描画セット数指定があれば取り出す。無ければ8
    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
    if (names.size() > 2) {
        throwGgafCriticalException("GgafDxMeshSetModel::GgafDxMeshSetModel "<<
                "prm_model_name には \"xxxxxx\" or \"8/xxxxx\" 形式を指定してください。 \n"<<
                "実際の引数は、prm_idstr="<<prm_model_name);
    }
    if (names.size() == 2) {
        _set_num = STOI(names[0]);
        if (_set_num > 15) {
            _TRACE_("GgafDxMeshSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大は15セットがですがそれ以上が設定されています。意図していますか？ _set_num="<<_set_num<<"。");
        }
    } else {
        _TRACE_("GgafDxMeshSetModel("<<prm_model_name<<") のセット数省略のため、標準の最大の15セットが設定されます。");
        _set_num = 15;
    }
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _paUint_material_list_grp_num = nullptr;
    _paVtxBuffer_org = nullptr;
    _paIdxBuffer_org = nullptr;
    _papaIndexParam = nullptr;
    _size_vertex_unit= 0;
    _size_vertices = 0;
    _nVertices = 0;
    _nFaces= 0;

    _obj_model |= Obj_GgafDxMeshSetModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどのメンバー初期化は
    //void GgafDxModelManager::restoreMeshSetModel(GgafDxMeshSetModel*)
    //で行うようにした。要参照。
    _TRACE_("GgafDxMeshSetModel::GgafDxMeshSetModel(" << _model_name << ") End");
}

//描画
HRESULT GgafDxMeshSetModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxMeshSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_("GgafDxMeshSetModel::draw() "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //対象アクター
    const GgafDxMeshSetActor* const pTargetActor = (GgafDxMeshSetActor*)prm_pActor_target;
    //対象MeshSetActorのエフェクトラッパ
    GgafDxMeshSetEffect* const pMeshSetEffect = (GgafDxMeshSetEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;
    //モデルが同じでかつ、セット数も同じならば頂点バッファ、インデックスバッファの設定はスキップできる
    if (GgafDxModelManager::_pModelLastDraw  != this) {
        //頂点バッファとインデックスバッファを設定
        pDevice->SetStreamSource(0, _pVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxMeshSetModel::FVF);
        pDevice->SetIndices(_pIndexBuffer);

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
    const UINT material_list_grp_num = _paUint_material_list_grp_num[prm_draw_set_num-1];
    for (UINT material_grp_index = 0; material_grp_index < material_list_grp_num; material_grp_index++) {
        const INDEXPARAM& idxparam = _papaIndexParam[prm_draw_set_num-1][material_grp_index];
        //モデルが同じでかつ、セット数も同じかつ、マテリアルNOが１つしかないならば、テクスチャ設定もスキップできる
        if (GgafDxModelManager::_pModelLastDraw  != this || material_list_grp_num != 1) {
            const UINT material_no = idxparam.MaterialNo;
            if (_papTextureConnection[material_no]) {
                //テクスチャをs0レジスタにセット
                pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDxMeshSetModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(PROPERTY::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                pDevice->SetTexture(0, nullptr);
            }
            //MaterialDiffuseはGgafDxMeshSetActor側でマテリアルを設定する。マテリアル色は単色とする。
            //理由はGgafDxMeshSetActorのメモ【GgafDxMeshSetActorのマテリアルカラーについて】を参照
        }

        if (material_grp_index == 0 && (GgafDxEffectManager::_pEffect_active != pMeshSetEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)) {
            if (GgafDxEffectManager::_pEffect_active) {
                _TRACE4_("EndPass("<<GgafDxEffectManager::_pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<GgafDxEffectManager::_pEffect_active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_active<<")");
                hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() EndPass() に失敗しました。");
                hr = GgafDxEffectManager::_pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() End() に失敗しました。");
#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxMeshSetModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name<<"("<<pMeshSetEffect<<")");
            //UINT numPass;
            hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pMeshSetEffect->_begin) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMeshSetEffect->_begin = true;
            }
#endif
        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() CommitChanges() に失敗しました。");
        }
        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);

        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      idxparam.BaseVertexIndex,
                                      idxparam.MinIndex,
                                      idxparam.NumVertices,
                                      idxparam.StartIndex,
                                      idxparam.PrimitiveCount);
        if (_num_pass >= 2) { //２パス目以降が存在
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() １パス目 EndPass() に失敗しました。");
            for (UINT i = 1; i < _num_pass; i++) {
                hr = pID3DXEffect->BeginPass(i);
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() "<<i+1<<"パス目 BeginPass("<<i<<") に失敗しました。");
                pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                              idxparam.BaseVertexIndex,
                                              idxparam.MinIndex,
                                              idxparam.NumVertices,
                                              idxparam.StartIndex,
                                              idxparam.PrimitiveCount);
                hr = pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() "<<i+1<<"パス目 EndPass() に失敗しました。");
            }
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshSetModel::draw() １パス目 BeginPass(0) に失敗しました。");
        }
        GgafGod::_num_actor_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMeshSetEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxMeshSetModel::restore() {
    _TRACE3_("GgafDxMeshSetModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreMeshSetModel(this);
    _TRACE3_("GgafDxMeshSetModel::restore() " << _model_name << " end");
}

void GgafDxMeshSetModel::onDeviceLost() {
    _TRACE3_("GgafDxMeshSetModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxMeshSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMeshSetModel::release() {
    _TRACE3_("GgafDxMeshSetModel::release() " << _model_name << " start");

    //テクスチャを解放
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //テクスチャの配列
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);

    GGAF_DELETEARR(_paVtxBuffer_org);
    GGAF_DELETEARR(_paIdxBuffer_org);

    GGAF_DELETE(_pModel3D);
    //_pMeshesFront は _pModel3D をDELETEしているのでする必要は無い
    _pMeshesFront = nullptr;
    if (_papaIndexParam) {
        for (int i = 0; i < _set_num; i++) {
            GGAF_DELETEARR(_papaIndexParam[i]);
        }
    }
    GGAF_DELETEARR(_papaIndexParam);
    GGAF_DELETEARR(_paUint_material_list_grp_num);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);

    _TRACE3_("GgafDxMeshSetModel::release() " << _model_name << " end");

}
GgafDxMeshSetModel::~GgafDxMeshSetModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

