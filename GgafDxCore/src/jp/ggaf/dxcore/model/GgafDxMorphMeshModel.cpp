#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

//DWORD GgafDxMorphMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDxMorphMeshModel::GgafDxMorphMeshModel(char* prm_model_name) : GgafDxModel(prm_model_name) {
    TRACE3("GgafDxMorphMeshModel::GgafDxMorphMeshModel(" << _model_name << ")");
    _TRACE_("GgafDxMorphMeshModel::GgafDxMorphMeshModel(" << _model_name << ") Begin");
    // 下位実装クラスが指定するモデル名は"M/4/xxxxx"という形式で、GgafDxModelManagerは
    // "M"からGgafDxMorphMeshModelと判断し、"M"を取り除いた"4/XXXX"をモデル名として扱う。
    // prm_model_name には "4/XXXX" が、渡ってくる。
    // プライマリのメッシュが1、モーフターゲットのメッシュが4つという意味
    // モーフターゲット数が違うモデルは、別モデルという扱いにするため、モデル名に数値を残そう
    // モデル名からフターゲット数を取得
    _TRACE_("GgafDxMorphMeshModel prm_model_name="<<prm_model_name);
    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, NULL, 10);
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        throwGgafCriticalException("GgafDxMorphMeshModel::GgafDxMorphMeshModel モデルIDにモーフターゲット数が指定されてません。prm_model_name="<<prm_model_name);
    } else {
        _morph_target_num = num;
        _TRACE_("GgafDxMorphMeshModel モーフターゲット数は指定あり、_morph_target_num="<<_morph_target_num);
    }
    //_morph_target_num = (int)(*prm_model_name - '0'); //頭一文字の半角数字文字を数値に
    if (_morph_target_num > 6) {
        _TRACE_("GgafDxMorphMeshModel::GgafDxMorphMeshModel モーフターゲット数が最大6個以上指定されてます。意図していますか？ _morph_target_num="<<_morph_target_num<<"/_model_name="<<_model_name);
    }
    _papModel3D = NULL;
    _papMeshesFront = NULL;

    _pIDirect3DVertexDeclaration9 = NULL;
    _pIDirect3DVertexBuffer9_primary = NULL;
    _paIDirect3DVertexBuffer9_morph = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _paVtxBuffer_org_primary = NULL;
    _papaVtxBuffer_org_morph = NULL;
    _paIdxBuffer_org = NULL;
    _paIndexParam = NULL;
    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreMorphMeshModel(GgafDxMorphMeshModel*)
    //で行うようにした。要参照。
    _TRACE_("GgafDxMorphMeshModel::GgafDxMorphMeshModel(" << _model_name << ") End");
}

HRESULT GgafDxMorphMeshModel::draw(GgafDxDrawableActor* prm_pActor_Target, int prm_draw_set_num) {
    TRACE4("GgafDxMorphMeshModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());

    //対象アクター
    GgafDxMorphMeshActor* pTargetActor = (GgafDxMorphMeshActor*)prm_pActor_Target;
    //対象アクターのエフェクトラッパ
    GgafDxMorphMeshEffect* pMorphMeshEffect = (GgafDxMorphMeshEffect*)prm_pActor_Target->_pEffect;
    //対象エフェクト
    ID3DXEffect* pID3DXEffect = pMorphMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    //頂点バッファ設定
    if (GgafDxModelManager::_pModelLastDraw != this) {
        GgafDxGod::_pID3DDevice9->SetVertexDeclaration( _pIDirect3DVertexDeclaration9); //頂点フォーマット
        GgafDxGod::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            GgafDxGod::_pID3DDevice9->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //インデックスバッファ設定
        GgafDxGod::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() SetFloat(_h_specular_power) に失敗しました。");
    }

    //描画
    for (UINT i = 0; i < _nMaterialListGrp; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        if (GgafDxModelManager::_pModelLastDraw != this || _nMaterialListGrp != 1) {
            if (_papTextureCon[material_no]) {
                //テクスチャをs0レジスタにセット
                GgafDxGod::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->use()->_pIDirect3DBaseTexture9);
            } else {
                _TRACE_("GgafDxMorphMeshModel::draw("<<prm_pActor_Target->getName()<<") テクスチャがありません。white.pngが設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                GgafDxGod::_pID3DDevice9->SetTexture(0, NULL);
            }
        }
        hr = pID3DXEffect->SetValue(pMorphMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw()SetValue(g_colMaterialDiffuse) に失敗しました。");

        if ((GgafDxEffectManager::_pEffect_Active != pMorphMeshEffect || GgafDxDrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            if (GgafDxEffectManager::_pEffect_Active) {
               TRACE4("EndPass("<<GgafDxEffectManager::_pEffect_Active->_pID3DXEffect<<"): /_pEffect_Active="<<GgafDxEffectManager::_pEffect_Active->_effect_name<<"("<<GgafDxEffectManager::_pEffect_Active<<")");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() EndPass() に失敗しました。");
                hr = GgafDxEffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() End() に失敗しました。");

#ifdef MY_DEBUG
                if (GgafDxEffectManager::_pEffect_Active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
                } else {
                    GgafDxEffectManager::_pEffect_Active->_begin = false;
                }
#endif

             }
            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxMorphMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");


            TRACE4("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name<<"("<<pMorphMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() Begin() に失敗しました。");
            //モーフターゲットの数により pass を切り替えている
            //プリマリメッシュのみ                             = pass0
            //プライマリメッシュ＋モーフターゲットメッシュ１つ = pass1
            //プライマリメッシュ＋モーフターゲットメッシュ２つ = pass2
            //以下最大９まで
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw() BeginPass("<<_morph_target_num<<") に失敗しました。");

#ifdef MY_DEBUG
            if (pMorphMeshEffect->_begin == true) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_Active==NULL?"NULL":GgafDxEffectManager::_pEffect_Active->_effect_name)<<"");
            } else {
                pMorphMeshEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDxMorphMeshModel::draw()CommitChanges() に失敗しました。");
        }

        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name);
        GgafDxGod::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _paIndexParam[i].BaseVertexIndex,
                                                        _paIndexParam[i].MinIndex,
                                                        _paIndexParam[i].NumVertices,
                                                        _paIndexParam[i].StartIndex,
                                                        _paIndexParam[i].PrimitiveCount);
        GgafGod::_num_actor_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_Active = pMorphMeshEffect;
    GgafDxDrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;

    return D3D_OK;
}

void GgafDxMorphMeshModel::restore() {
    TRACE3("GgafDxMorphMeshModel::restore() " << _model_name << " start");
    GgafDxGod::_pModelManager->restoreMorphMeshModel(this);
    TRACE3("GgafDxMorphMeshModel::restore() " << _model_name << " end");
}

void GgafDxMorphMeshModel::onDeviceLost() {
    TRACE3("GgafDxMorphMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDxMorphMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMorphMeshModel::release() {
    TRACE3("GgafDxMorphMeshModel::release() " << _model_name << " start");

    //テクスチャを解放
    if (_papTextureCon) {
        for (DWORD i = 0; i < _dwNumMaterials; i++) {
            if (_papTextureCon[i]) {
                _papTextureCon[i]->close();
            }
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //テクスチャの配列

    for (int pattern = 0; pattern <= _morph_target_num; pattern++) {
        if (pattern == 0) {
            RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9_primary);
            DELETEARR_IMPOSSIBLE_NULL(_paVtxBuffer_org_primary);
        } else {
            RELEASE_IMPOSSIBLE_NULL(_paIDirect3DVertexBuffer9_morph[pattern-1]);
            DELETEARR_IMPOSSIBLE_NULL(_papaVtxBuffer_org_morph[pattern-1]);
        }
        DELETE_IMPOSSIBLE_NULL(_papModel3D[pattern]);
    }


    DELETEARR_IMPOSSIBLE_NULL(_paIDirect3DVertexBuffer9_morph);
    DELETEARR_IMPOSSIBLE_NULL(_papaVtxBuffer_org_morph);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexDeclaration9);

    DELETEARR_IMPOSSIBLE_NULL(_papModel3D);
    //_papMeshesFront[0],_papMeshesFront[1] は _papModel3D をDELETEしているのでする必要は無い
    DELETEARR_IMPOSSIBLE_NULL(_papMeshesFront);
    _papMeshesFront = NULL;
    DELETEARR_IMPOSSIBLE_NULL(_paIdxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    DELETEARR_IMPOSSIBLE_NULL(_paMaterial_default);
    TRACE3("GgafDxMorphMeshModel::release() " << _model_name << " end");

}
GgafDxMorphMeshModel::~GgafDxMorphMeshModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

