#include "jp/ggaf/dxcore/model/GgafDxMassMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMeshEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

//DWORD GgafDxMassMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer = nullptr;

GgafDxMassMeshModel::GgafDxMassMeshModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxMassMeshModel::GgafDxMassMeshModel(" << _model_name << ")");
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;
    // prm_model_name には "xxxxxx" or "8/xxxxx" が、渡ってくる。
    // 同時描画セット数が8という意味です。
    // モーフターゲット数が違うモデルは、別モデルという扱いにするため、モデル名に数値を残そうかな。
    // モデル名から同時描画セット数指定があれば取り出す。無ければ8
    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
    if (names.size() > 2) {
        throwGgafCriticalException("GgafDxMassMeshModel::GgafDxMassMeshModel "<<
                "prm_model_name には \"xxxxxx\" or \"8/xxxxx\" 形式を指定してください。 \n"<<
                "実際の引数は、prm_idstr="<<prm_model_name);
    }
    if (names.size() == 2) {
        _set_num = STOI(names[0]);
        if (_set_num > MAX_INSTACE) {
            _TRACE_("GgafDxMassMeshModel("<<prm_model_name<<") の同時描画セット数オーバー。最大は"<<MAX_INSTACE<<"セットがですがそれ以上が設定されています。意図していますか？ _set_num="<<_set_num<<"。");
        }
    } else {
        _TRACE_("GgafDxMassMeshModel("<<prm_model_name<<") のセット数省略のため、標準の最大の"<<MAX_INSTACE<<"セットが設定されます。");
        _set_num = MAX_INSTACE;
    }
    _pVertexBuffer_model = nullptr;
    _pVertexBuffer_instacedata = nullptr;
    _pIndexBuffer = nullptr;
    _pIDirect3DVertexDeclaration9 = nullptr;
    _paUint_material_list_grp_num = nullptr;
    _paVtxBuffer_org_model = nullptr;
    _paIdxBuffer_org = nullptr;
    _size_vertex_unit_instacedata = 0;
    _size_vertex_unit_model = 0;
    _size_vertices_model = 0;
    _nVertices = 0;
    _nFaces= 0;

    _obj_model |= Obj_GgafDxMassMeshModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどのメンバー初期化は
    //void GgafDxModelManager::restoreMassMeshModel(GgafDxMassMeshModel*)
    //で行うようにした。要参照。
    _TRACE_("GgafDxMassMeshModel::GgafDxMassMeshModel(" << _model_name << ") End");
}

//描画
HRESULT GgafDxMassMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxMassMeshModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_("GgafDxMassMeshModel::draw() "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //対象アクター
    const GgafDxMassMeshActor* const pTargetActor = (GgafDxMassMeshActor*)prm_pActor_target;
    //対象MassMeshActorのエフェクトラッパ
    GgafDxMassMeshEffect* const pMassMeshEffect = (GgafDxMassMeshEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMassMeshEffect->_pID3DXEffect;

    HRESULT hr;

    //頂点バッファ(インスタンスデータ)書き換え
    UINT update_vertex_instacedata_size = _size_vertex_unit_instacedata * prm_draw_set_num;
    void* pVertexBuffer_instacedata;
    hr = _pVertexBuffer_instacedata->Lock(
                                  0,
                                  update_vertex_instacedata_size,
                                  (void**)&pVertexBuffer_instacedata,
                                  D3DLOCK_DISCARD
                                );
    checkDxException(hr, D3D_OK, "[GgafDxMassMeshModel::draw] 頂点バッファのロック取得に失敗 model="<<_model_name);
    memcpy(
      pVertexBuffer_instacedata,
      _aInstancedata,
      update_vertex_instacedata_size
    );
    _pVertexBuffer_instacedata->Unlock();

    //モデルが同じでかつ、セット数も同じならば頂点バッファ、インデックスバッファの設定はスキップできる
    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
    checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSourceFreq 0 に失敗しました。prm_draw_set_num="<<prm_draw_set_num);

    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSourceFreq 1 に失敗しました。");
        //頂点バッファとインデックスバッファを設定
        hr = pDevice->SetVertexDeclaration(_pIDirect3DVertexDeclaration9); //頂点フォーマット
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetVertexDeclaration に失敗しました。");
        hr = pDevice->SetStreamSource(0, _pVertexBuffer_model      , 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSource 0 に失敗しました。");
        hr = pDevice->SetStreamSource(1, _pVertexBuffer_instacedata, 0, _size_vertex_unit_instacedata);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSource 1 に失敗しました。");
        hr = pDevice->SetIndices(_pIndexBuffer);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetIndices に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) に失敗しました。");
        if (_papTextureConnection[0]) {
            pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("GgafDxMassMeshModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(PROPERTY::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
            //無ければテクスチャ無し
            pDevice->SetTexture(0, nullptr);
        }
    }
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (pEffect_active != pMassMeshEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
        if (pEffect_active) {
            _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() EndPass() に失敗しました。");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() End() に失敗しました。");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwGgafCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxMassMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name<<"("<<pMassMeshEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pMassMeshEffect->_begin) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassMeshEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name);

    hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                  0,
                                  0,
                                  _nVertices,
                                  0,
                                  _nFaces);
    //checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() DrawIndexedPrimitive()  pass=1 に失敗しました。");
    if (_num_pass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() １パス目 EndPass() に失敗しました。");
        for (UINT i = 1; i < _num_pass; i++) {
            hr = pID3DXEffect->BeginPass(i);
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() "<<i+1<<"パス目 BeginPass("<<i<<") に失敗しました。");
            hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                          0,
                                          0,
                                          _nVertices,
                                          0,
                                          _nFaces);
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() DrawIndexedPrimitive()  pass="<<(i+1)<<" に失敗しました。");
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() "<<i+1<<"パス目 EndPass() に失敗しました。");
        }
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() １パス目 BeginPass(0) に失敗しました。");
    }

//    pDevice->SetStreamSourceFreq( 0, 1 );
//    pDevice->SetStreamSourceFreq( 1, 1 );

    GgafGod::_num_drawing++;
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMassMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxMassMeshModel::restore() {
    _TRACE3_("GgafDxMassMeshModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreMassMeshModel(this);
    _TRACE3_("GgafDxMassMeshModel::restore() " << _model_name << " end");
}

void GgafDxMassMeshModel::onDeviceLost() {
    _TRACE3_("GgafDxMassMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxMassMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMassMeshModel::release() {
    _TRACE3_("GgafDxMassMeshModel::release() " << _model_name << " start");

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
    GGAF_RELEASE(_pVertexBuffer_instacedata);
    GGAF_RELEASE(_pVertexBuffer_model);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_RELEASE(_pIDirect3DVertexDeclaration9);

    GGAF_DELETEARR(_paVtxBuffer_org_model);
    GGAF_DELETEARR(_paIdxBuffer_org);

    GGAF_DELETE(_pModel3D);
    //_pMeshesFront は _pModel3D をDELETEしているのでする必要は無い
    _pMeshesFront = nullptr;
    GGAF_DELETEARR(_paUint_material_list_grp_num);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);

    _TRACE3_("GgafDxMassMeshModel::release() " << _model_name << " end");

}
GgafDxMassMeshModel::~GgafDxMassMeshModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

