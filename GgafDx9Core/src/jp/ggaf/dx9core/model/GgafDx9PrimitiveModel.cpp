#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9PrimitiveModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9PrimitiveModel::GgafDx9PrimitiveModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE("GgafDx9PrimitiveModel::GgafDx9PrimitiveModel(" << _model_name << ")");

    _pIDirect3DVertexBuffer9 = NULL;
    _pTextureCon = NULL;
    //デバイイスロスト対応のため、テクスチャ、頂点、マテリアルの初期化は
    //GgafDx9God::_pModelManager->restorePrimitiveModel で行っている。
}

//描画
HRESULT GgafDx9PrimitiveModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE("GgafDx9PrimitiveModel::draw("<<prm_pActor_Target->getName()<<")");
    //対象PrimitiveActor
    GgafDx9PrimitiveActor* pPrimitiveActor_Target = (GgafDx9PrimitiveActor*)prm_pActor_Target;
    //今回描画のUV
    GgafDx9RectUV* pRectUV_Active = _paRectUV + (pPrimitiveActor_Target->_iAnimationPatternNo_Active);

    static HRESULT hr;

    if (GgafDx9God::_pModelManager->_id_lastdraw != _id) {
        //前回描画とモデルが違う！
        GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _iSize_Vertec_unit);
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9PrimitiveModel::FVF);
        GgafDx9God::_pID3DDevice9->SetTexture(0, _pTextureCon->take());
    }

    GgafDx9God::_pID3DDevice9->SetMaterial(&(pPrimitiveActor_Target->_paD3DMaterial9[0]));

    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, 0xffffffff);//陰影を無くすため環境光を最高にする
    GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, GgafDx9God::_dwAmbientBrightness_default);//環境光を元通り
    //前回描画モデル名保存
    GgafDx9God::_pModelManager->_id_lastdraw = _id;
    //前回描画UV座標（へのポインタ）を保存
    _pRectUV_drawlast = pRectUV_Active;
    GgafGod::_iNumPlayingActor++;
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
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    DELETE_IMPOSSIBLE_NULL(_pD3DMaterial9_default);
    if (_pTextureCon != NULL) {
        _pTextureCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    _TRACE_("GgafDx9PrimitiveModel::release() " << _model_name << " end");

}
GgafDx9PrimitiveModel::~GgafDx9PrimitiveModel() {
    _TRACE_("GgafDx9PrimitiveModel::~GgafDx9PrimitiveModel() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9PrimitiveModel::~GgafDx9PrimitiveModel() " << _model_name << " end");
}

