#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9MeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9MeshModel::GgafDx9MeshModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE3("GgafDx9MeshModel::GgafDx9MeshModel(" << _model_name << ")");
    _pModel3D = NULL;
    _pMeshesFront = NULL;

    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _paD3DMaterial9_default = NULL;
    _paVtxBuffer_org = NULL;
    _paIdxBuffer_org = NULL;
    _papTextureCon = NULL;
    _paIndexParam = NULL;
    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshModel*)
    //で行っている。
}

//描画
HRESULT GgafDx9MeshModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE3("GgafDx9MeshModel::draw("<<prm_pActor_Target->getName()<<")");
    //対象アクター
    static GgafDx9MeshActor* pTargetActor;
    pTargetActor = (GgafDx9MeshActor*)prm_pActor_Target;
    //対象MeshActorのエフェクトラッパ
    static GgafDx9MeshEffect* pMeshEffect;
    pMeshEffect = pTargetActor->_pMeshEffect;
    //対象エフェクト
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pMeshEffect->_pID3DXEffect;

	HRESULT hr;
    UINT material_no;
    //頂点バッファとインデックスバッファを設定
    GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9,  0, _size_vertec_unit);
    GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9MeshModel::FVF);
    GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);

    //描画
    for (UINT i = 0; i < _nMaterialListGrp; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        if (_papTextureCon[material_no] != NULL) {
            //テクスチャをs0レジスタにセット
            GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->view());
        } else {
            _TRACE_("GgafDx9MeshModel::draw("<<prm_pActor_Target->getName()<<") テクスチャがありません。white.pngが設定されるべきです。おかしいです");
            //無ければテクスチャ無し
            GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
        }
        hr = pID3DXEffect->SetValue(pMeshEffect->_hMaterialDiffuse, &(pTargetActor->_paD3DMaterial9[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshModel::draw SetValue(g_MaterialDiffuse) に失敗しました。");
        hr = pID3DXEffect->CommitChanges();
        potentialDx9Exception(hr, D3D_OK, "GgafDx9MeshModel::draw CommitChanges() に失敗しました。");
        GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _paIndexParam[i].BaseVertexIndex,
                                                        _paIndexParam[i].MinIndex,
                                                        _paIndexParam[i].NumVertices,
                                                        _paIndexParam[i].StartIndex,
                                                        _paIndexParam[i].PrimitiveCount);
    }
    GgafDx9ModelManager::_id_lastdraw = _id;
    GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9MeshModel::restore() {
    TRACE3("GgafDx9MeshModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreMeshModel(this);
    TRACE3("GgafDx9MeshModel::restore() " << _model_name << " end");
}

void GgafDx9MeshModel::onDeviceLost() {
    TRACE3("GgafDx9MeshModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9MeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9MeshModel::release() {
    TRACE3("GgafDx9MeshModel::release() " << _model_name << " start");

    //テクスチャを解放
    for (DWORD i = 0; i < _dwNumMaterials; i++) {
        if (_papTextureCon[i] != NULL) {
            _papTextureCon[i]->close();
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_papTextureCon); //テクスチャの配列

    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DIndexBuffer9);

    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
    DELETEARR_IMPOSSIBLE_NULL(_paVtxBuffer_org);
    DELETEARR_IMPOSSIBLE_NULL(_paIdxBuffer_org);
    DELETE_IMPOSSIBLE_NULL(_pModel3D);
	//_pMeshesFront は _pModel3D をDELETEしているのでする必要は無い
    _pMeshesFront = NULL;
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);
    TRACE3("GgafDx9MeshModel::release() " << _model_name << " end");

}
GgafDx9MeshModel::~GgafDx9MeshModel() {
    TRACE3("GgafDx9MeshModel::~GgafDx9MeshModel() " << _model_name << " start");
    release();
}

