#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9MeshSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9MeshSetModel::GgafDx9MeshSetModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE3("GgafDx9MeshSetModel::GgafDx9MeshSetModel(" << _model_name << ")");
    _pModel3D = NULL;
    _pMeshesFront = NULL;

    _setnum = 6;
    _paIDirect3DVertexBuffer9 = NULL;
    _paIDirect3DIndexBuffer9 = NULL;
    _pa_nMaterialListGrp = NULL;
    _papaVtxBuffer_org = NULL;
    _papaIdxBuffer_org = NULL;
    _papaIndexParam = NULL;
    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshSetModel*)
    //で行っている。
}

//描画
HRESULT GgafDx9MeshSetModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE3("GgafDx9MeshSetModel::draw("<<prm_pActor_Target->getName()<<")");
    //対象アクター
    static GgafDx9MeshSetActor* pTargetActor;
    pTargetActor = (GgafDx9MeshSetActor*)prm_pActor_Target;
    //対象MeshSetActorのエフェクトラッパ
    static GgafDx9MeshSetEffect* pMeshSetEffect;
    pMeshSetEffect = pTargetActor->_pMeshSetEffect;
    //対象エフェクト
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pMeshSetEffect->_pID3DXEffect;

	HRESULT hr;
    UINT material_no;
    if (GgafDx9ModelManager::_pModelLastDraw != this) {
        //頂点バッファとインデックスバッファを設定
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _paIDirect3DVertexBuffer9[0],  0, _size_vertec_unit * 1);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9MeshSetModel::FVF);
        GgafDx9God::_pID3DDevice9->SetIndices(_paIDirect3DIndexBuffer9[0]);
    }

    //描画
    for (UINT i = 0; i < _pa_nMaterialListGrp[0]; i++) {
        if (GgafDx9ModelManager::_pModelLastDraw != this || _pa_nMaterialListGrp[0] != 1) {
            material_no = _papaIndexParam[0][i].MaterialNo;
            if (_papTextureCon[material_no] != NULL) {
                //テクスチャをs0レジスタにセット
                GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->view());
            } else {
                _TRACE_("GgafDx9MeshSetModel::draw("<<prm_pActor_Target->getName()<<") テクスチャがありません。white.pngが設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
            }
            hr = pID3DXEffect->SetValue(pMeshSetEffect->_hMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
            mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetValue(g_MaterialDiffuse) に失敗しました。");
        }


        if (GgafDx9EffectManager::_pEffect_Active != pMeshSetEffect) {
            if (GgafDx9EffectManager::_pEffect_Active != NULL) {
                TRACE4("EndPass: /_pEffect_Active="<<GgafDx9EffectManager::_pEffect_Active->_effect_name);
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->EndPass();
                mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() EndPass() に失敗しました。");
                hr = GgafDx9EffectManager::_pEffect_Active->_pID3DXEffect->End();
                mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() End() に失敗しました。");
            }

            TRACE4("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            mightDx9Exception(hr, S_OK, "GgafDx9MeshSetModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");
            TRACE4("BeginPass: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() BeginPass(0) に失敗しました。");
        } else {
            hr = pID3DXEffect->CommitChanges();
            mightDx9Exception(hr, D3D_OK, "GgafDx9MeshSetModel::draw() CommitChanges() に失敗しました。");
        }
        TRACE4("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
        GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _papaIndexParam[0][i].BaseVertexIndex,
                                                        _papaIndexParam[0][i].MinIndex,
                                                        _papaIndexParam[0][i].NumVertices,
                                                        _papaIndexParam[0][i].StartIndex,
                                                        _papaIndexParam[0][i].PrimitiveCount);
    }
//    if (_nMaterialListGrp > 0) {
        GgafDx9ModelManager::_pModelLastDraw = this;
        GgafDx9EffectManager::_pEffect_Active = pMeshSetEffect;
        GgafGod::_num_actor_playing++;
//    }
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
	for (DWORD i = 0; i < _dwNumMaterials; i++) {
		if (_papTextureCon[i] != NULL) {
			_papTextureCon[i]->close();
		}
	}
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //テクスチャの配列
    for (int i = 0; i < _setnum; i++) {
        RELEASE_IMPOSSIBLE_NULL(_paIDirect3DVertexBuffer9[i]);
        RELEASE_IMPOSSIBLE_NULL(_paIDirect3DIndexBuffer9[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_paIDirect3DVertexBuffer9);
    DELETEARR_IMPOSSIBLE_NULL(_paIDirect3DIndexBuffer9);

    for (int i = 0; i < _setnum; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaVtxBuffer_org[i]);
        DELETEARR_IMPOSSIBLE_NULL(_papaIdxBuffer_org[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaVtxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_papaIdxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_pa_nMaterialListGrp);
    DELETE_IMPOSSIBLE_NULL(_pModel3D);
	//_pMeshesFront は _pModel3D をDELETEしているのでする必要は無い
    _pMeshesFront = NULL;
    for (int i = 0; i < _setnum; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaIndexParam[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaIndexParam);
    TRACE3("GgafDx9MeshSetModel::release() " << _model_name << " end");

}
GgafDx9MeshSetModel::~GgafDx9MeshSetModel() {
    TRACE3("GgafDx9MeshSetModel::~GgafDx9MeshSetModel() " << _model_name << " start");
    release();
}

