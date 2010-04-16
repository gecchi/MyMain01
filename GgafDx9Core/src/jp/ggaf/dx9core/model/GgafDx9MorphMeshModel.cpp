#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

//DWORD GgafDx9MorphMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9MorphMeshModel::GgafDx9MorphMeshModel(char* prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE3("GgafDx9MorphMeshModel::GgafDx9MorphMeshModel(" << _model_name << ")");
    _TRACE_("GgafDx9MorphMeshModel::GgafDx9MorphMeshModel(" << _model_name << ") Begin");
    // 下位実装クラスが指定するモデル名は"M/4/xxxxx"という形式で、GgafDx9ModelManagerは
    // "M"からGgafDx9MorphMeshModelと判断し、"M"を取り除いた"4/XXXX"をモデル名として扱う。
    // prm_model_name には "4/XXXX" が、渡ってくる。
    // プライマリのメッシュが1、モーフターゲットのメッシュが4つという意味
    // モーフターゲット数が違うモデルは、別モデルという扱いにするため、モデル名に数値を残そう
    // モデル名からフターゲット数を取得
    _TRACE_("GgafDx9MorphMeshModel prm_model_name="<<prm_model_name);
    char nm[51];
    strcpy(nm, prm_model_name);
    const char* pT = strtok(nm, "/" );
    int num = (int)strtol(pT, NULL, 10);
    pT = strtok(NULL, "/");
    if (pT == NULL) {
        _TRACE_("GgafDx9MorphMeshModel モーフターゲット数は指定なし、よって0個とします");
        _morph_target_num = 0;
    } else {
        _morph_target_num = num;
        _TRACE_("GgafDx9MorphMeshModel モーフターゲット数は指定あり、_morph_target_num="<<_morph_target_num);
    }
    //_morph_target_num = (int)(*prm_model_name - '0'); //頭一文字の半角数字文字を数値に
    if (_morph_target_num > 6) {
        _TRACE_("GgafDx9MorphMeshModel::GgafDx9MorphMeshModel モーフターゲット数は最大6個までです。_morph_target_num="<<_morph_target_num<<"/_model_name="<<_model_name);
        _morph_target_num = 6;
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
    //void GgafDx9ModelManager::restoreMorphMeshModel(GgafDx9MorphMeshModel*)
    //で行うようにした。
    _TRACE_("GgafDx9MorphMeshModel::GgafDx9MorphMeshModel(" << _model_name << ") End");
}

HRESULT GgafDx9MorphMeshModel::draw(GgafDx9DrawableActor* prm_pActor_Target) {
    TRACE4("GgafDx9MorphMeshModel::draw("<<prm_pActor_Target->getName()<<") this="<<getName());
    if (_is_init_model == false) {
        prm_pActor_Target->onCreateModel(); //モデル作成時の初期処理
        _is_init_model = true;
    }
    //対象アクター
    static GgafDx9MorphMeshActor* pTargetActor;
    pTargetActor = (GgafDx9MorphMeshActor*)prm_pActor_Target;
    //対象アクターのエフェクトラッパ
    static GgafDx9MorphMeshEffect* pMorphMeshEffect;
    pMorphMeshEffect = pTargetActor->_pMorphMeshEffect;
    //対象エフェクト
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pMorphMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    //頂点バッファ設定
    if (GgafDx9ModelManager::_pModelLastDraw != this) {
        GgafDx9God::_pID3DDevice9->SetVertexDeclaration( _pIDirect3DVertexDeclaration9); //頂点フォーマット
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9_primary, 0, _size_vertex_unit_primary);
        for (int i = 1; i <= _morph_target_num; i++) {
            GgafDx9God::_pID3DDevice9->SetStreamSource(i, _paIDirect3DVertexBuffer9_morph[i-1], 0, _size_vertex_unit_morph);
        }
        //インデックスバッファ設定
        GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_hPowerBlink, _fPowerBlink);
        checkDxException(hr, D3D_OK, "GgafDx9MorphMeshModel::draw() SetFloat(_hPowerBlink) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMorphMeshEffect->_hBlinkThreshold, _fBlinkThreshold);
        checkDxException(hr, D3D_OK, "GgafDx9MorphMeshModel::draw() SetFloat(_hBlinkThreshold) に失敗しました。");
    }

    //描画
    for (UINT i = 0; i < _nMaterialListGrp; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        if (GgafDx9ModelManager::_pModelLastDraw != this || _nMaterialListGrp != 1) {
            if (_papTextureCon[material_no] != NULL) {
                //テクスチャをs0レジスタにセット
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->view()->_pIDirect3DTexture9);
            } else {
                _TRACE_("GgafDx9MorphMeshModel::draw("<<prm_pActor_Target->getName()<<") テクスチャがありません。white.pngが設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
        }
        hr = pID3DXEffect->SetValue(pMorphMeshEffect->_hMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDx9MorphMeshModel::draw()SetValue(g_MaterialDiffuse) に失敗しました。");

        if ((GgafDx9EffectManager::_pEffect_Active != pMorphMeshEffect || GgafDx9DrawableActor::_hash_technique_last_draw != prm_pActor_Target->_hash_technique) && i == 0) {
            if (GgafDx9EffectManager::_pEffect_Active != NULL) {
                TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDx9MorphMeshModel::draw() EndPass() に失敗しました。");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDx9MorphMeshModel::draw() End() に失敗しました。");
            }

            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDx9MorphMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");


            TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name);
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDx9MorphMeshModel::draw() Begin() に失敗しました。");
            //モーフターゲットの数により pass を切り替えている
            //プリマリメッシュのみ                             = pass0
            //プライマリメッシュ＋モーフターゲットメッシュ１つ = pass1
            //プライマリメッシュ＋モーフターゲットメッシュ２つ = pass2
            //以下最大９まで
            hr = pID3DXEffect->BeginPass(_morph_target_num);
            checkDxException(hr, D3D_OK, "GgafDx9MorphMeshModel::draw() BeginPass("<<_morph_target_num<<") に失敗しました。");
        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "GgafDx9MorphMeshModel::draw()CommitChanges() に失敗しました。");
        }

        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMorphMeshEffect->_effect_name);
        GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _paIndexParam[i].BaseVertexIndex,
                                                        _paIndexParam[i].MinIndex,
                                                        _paIndexParam[i].NumVertices,
                                                        _paIndexParam[i].StartIndex,
                                                        _paIndexParam[i].PrimitiveCount);
    }
    GgafDx9ModelManager::_pModelLastDraw = this;
    GgafDx9EffectManager::_pEffect_Active = pMorphMeshEffect;
    GgafDx9DrawableActor::_hash_technique_last_draw = prm_pActor_Target->_hash_technique;
    GgafGod::_num_actor_drawing++;
    return D3D_OK;
}

void GgafDx9MorphMeshModel::restore() {
    TRACE3("GgafDx9MorphMeshModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreMorphMeshModel(this);
    TRACE3("GgafDx9MorphMeshModel::restore() " << _model_name << " end");
}

void GgafDx9MorphMeshModel::onDeviceLost() {
    TRACE3("GgafDx9MorphMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9MorphMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9MorphMeshModel::release() {
    TRACE3("GgafDx9MorphMeshModel::release() " << _model_name << " start");

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
    DELETEARR_IMPOSSIBLE_NULL(_papModel3D);
    //_papMeshesFront[0],_papMeshesFront[1] は _papModel3D をDELETEしているのでする必要は無い
    DELETEARR_IMPOSSIBLE_NULL(_papMeshesFront);
    _papMeshesFront = NULL;


    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);
    DELETEARR_IMPOSSIBLE_NULL(_paIdxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    TRACE3("GgafDx9MorphMeshModel::release() " << _model_name << " end");

}
GgafDx9MorphMeshModel::~GgafDx9MorphMeshModel() {
    TRACE3("GgafDx9MorphMeshModel::~GgafDx9MorphMeshModel() " << _model_name << " start");
    release();
}

