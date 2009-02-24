#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9PrimitiveModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9PrimitiveModel::GgafDx9PrimitiveModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE("GgafDx9PrimitiveModel::GgafDx9PrimitiveModel(" << _model_name << ")");
    _pModel3D = NULL;
    _pMeshesFront = NULL;

    _pIDirect3DVertexBuffer9 = NULL;
    _pIDirect3DIndexBuffer9 = NULL;
    _paVtxBuffer_org = NULL;
    _paIdxBuffer_org = NULL;
    _papTextureCon = NULL;
    _paIndexParam = NULL;
    //デバイイスロスト対応のため、テクスチャ、頂点、マテリアルの初期化は
    //GgafDx9God::_pModelManager->restorePrimitiveModel で行っている。
}

//描画
HRESULT GgafDx9PrimitiveModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE("GgafDx9PrimitiveModel::draw("<<prm_pActor_Target->getName()<<")");
    GgafDx9PrimitiveActor* pTargetActor = (GgafDx9PrimitiveActor*)prm_pActor_Target;

    UINT material_no;
    if (GgafDx9God::_pModelManager->_id_lastdraw != _id) {
        //前回描画とモデルが違う！
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9,  0, _size_vertec_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9PrimitiveModel::FVF);
        GgafDx9God::_pID3DDevice9->SetIndices(_pIDirect3DIndexBuffer9);
    }
    for (int i = 0; i < _nMaterialListGrp; i++) {
        material_no = _paIndexParam[i].MaterialNo;
        GgafDx9God::_pID3DDevice9->SetMaterial(&(pTargetActor->_paD3DMaterial9[material_no]));
        if (_papTextureCon[material_no] != NULL) {
            //テクスチャのセット
            GgafDx9God::_pID3DDevice9->SetTexture(0, _papTextureCon[material_no]->view());
        } else {
            //無ければテクスチャ無し
            GgafDx9God::_pID3DDevice9->SetTexture(0, NULL);
        }
        GgafDx9God::_pID3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                                        _paIndexParam[i].BaseVertexIndex,
                                                        _paIndexParam[i].MinIndex,
                                                        _paIndexParam[i].NumVertices,
                                                        _paIndexParam[i].StartIndex,
                                                        _paIndexParam[i].PrimitiveCount);
    }

    GgafDx9God::_pModelManager->_id_lastdraw = _id;
    GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9PrimitiveModel::restore() {
    _TRACE_("GgafDx9PrimitiveModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restorePrimitiveModel(this);
    _TRACE_("GgafDx9PrimitiveModel::restore() " << _model_name << " end");
}

void GgafDx9PrimitiveModel::onDeviceLost() {
    _TRACE_("GgafDx9PrimitiveModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9PrimitiveModel::onDeviceLost() " << _model_name << " end");
}

void GgafDx9PrimitiveModel::release() {
    _TRACE_("GgafDx9PrimitiveModel::release() " << _model_name << " start");

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
	//_pMeshesFront は _pModel3D をDELETEしてるのでする必要は無い
    _pMeshesFront = NULL;
    DELETEARR_IMPOSSIBLE_NULL(_paIndexParam);
    _TRACE_("GgafDx9PrimitiveModel::release() " << _model_name << " end");

}
GgafDx9PrimitiveModel::~GgafDx9PrimitiveModel() {
    _TRACE_("GgafDx9PrimitiveModel::~GgafDx9PrimitiveModel() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9PrimitiveModel::~GgafDx9PrimitiveModel() " << _model_name << " end");
}

