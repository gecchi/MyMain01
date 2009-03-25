#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9BoardModel::FVF = (D3DFVF_XYZ | D3DFVF_TEX1);

GgafDx9BoardModel::GgafDx9BoardModel(char* prm_platemodel_name) :
    GgafDx9Model(prm_platemodel_name) {
    TRACE3("GgafDx9BoardModel::GgafDx9BoardModel(" << _model_name << ")");
    _fSize_BoardModelWidthPx = 32.0f;
    _fSize_BoardModelHeightPx = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pattno_max = 1;
    _pIDirect3DVertexBuffer9 = NULL;
    _pTextureCon = NULL;
    _paRectUV = NULL;
    _pRectUV_drawlast = NULL;
}

HRESULT GgafDx9BoardModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE("GgafDx9BoardModel::draw("<<prm_pActor_Target->getName()<<")");
    //TODO クリアするかどうか
    //GgafDx9God::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0x000000, 1.0, 0);

    //対象Actor
    static GgafDx9BoardActor* pTargetActor;
    pTargetActor = (GgafDx9BoardActor*)prm_pActor_Target;
    //対象BoardActorのエフェクトラッパ
    static GgafDx9BoardEffect* pBoardEffect;
    pBoardEffect = pTargetActor->_pBoardEffect;
    //対象エフェクト
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = pBoardEffect->_pID3DXEffect;
    //今回描画のUV
    static GgafDx9RectUV* pRectUV_Active;
    pRectUV_Active = _paRectUV + (pTargetActor->_patteno_now);

    static HRESULT hr;
    GgafDx9God::_pID3DDevice9->SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _size_vertec_unit);
    GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9BoardModel::FVF);
    GgafDx9God::_pID3DDevice9->SetTexture(0, _pTextureCon->view());
    hr = pID3DXEffect->SetFloat(pBoardEffect->_hOffsetU, pRectUV_Active->_aUV[0].tu);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hOffsetU) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pBoardEffect->_hOffsetV, pRectUV_Active->_aUV[0].tv);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hOffsetV) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pBoardEffect->_hTransformedX, pTargetActor->_x - 0.5f);//テクセルとピクセルの関係より
    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedX) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pBoardEffect->_hTransformedY, pTargetActor->_y - 0.5f);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedY) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pBoardEffect->_hDepthZ, pTargetActor->_z);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hDepthZ) に失敗しました。");
    //α設定
    hr = pID3DXEffect->SetFloat(pBoardEffect->_hAlpha, pTargetActor->_fAlpha);
    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hAlpha) に失敗しました。");
    hr = pID3DXEffect->CommitChanges();
    potentialDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw CommitChanges() に失敗しました。");
    GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    //前回描画モデル名保存
    GgafDx9ModelManager::_id_lastdraw = _id;
    //前回描画UV座標（へのポインタ）を保存
    _pRectUV_drawlast = pRectUV_Active;
    GgafGod::_num_actor_playing++;
    return D3D_OK;

}

void GgafDx9BoardModel::restore() {
    TRACE3("GgafDx9BoardModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreBoardModel(this);
    TRACE3("GgafDx9BoardModel::restore() " << _model_name << " end");
}

void GgafDx9BoardModel::release() {
    TRACE3("GgafDx9BoardModel::release() " << _model_name << " start");
    RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
    DELETE_IMPOSSIBLE_NULL(_pD3DMaterial9_default);
    if (_pTextureCon != NULL) {
        _pTextureCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    TRACE3("GgafDx9BoardModel::release() " << _model_name << " end");
}

void GgafDx9BoardModel::onDeviceLost() {
    TRACE3("GgafDx9BoardModel::onDeviceLost() " << _model_name << " start");
    release();
    TRACE3("GgafDx9BoardModel::onDeviceLost() " << _model_name << " end");
}

GgafDx9BoardModel::~GgafDx9BoardModel() {
    TRACE3("GgafDx9BoardModel::~GgafDx9BoardModel() " << _model_name << " start");
    release();
}
