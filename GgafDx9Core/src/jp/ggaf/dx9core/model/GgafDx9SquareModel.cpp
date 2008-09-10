#include "stdafx.h"


DWORD GgafDx9SquareModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE);


GgafDx9SquareModel::GgafDx9SquareModel(string prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
	TRACE("GgafDx9SquareModel::GgafDx9SquareModel(" <<  _model_name << ")");
	_pD3DMaterial9 = NULL;
	_pIDirect3DVertexBuffer9 = NULL;
	_pModel_Next = NULL;
	_iSize_Vertecs = 0;
	_iSize_Verte_unit = 0;
	//デバイイスロスト対応のため、テクスチャ、頂点、マテリアルの初期化は
	//GgafDx9ModelManager::restoreSquareModel で行っている。
}


//描画
HRESULT GgafDx9SquareModel::draw(GgafDx9MainActor* prm_pActor_Target) {
	TRACE("GgafDx9SquareModel::draw("<<prm_pActor_Target->getName()<<")");
	//GgafDx9SquareActor* pSquareActor_Target = (GgafDx9SquareActor*)prm_pActor_Target;
	//HRESULT	hr;
	if (GgafDx9Model::_modelname_lastdraw != _model_name) { //前回と描画モデルが違う
		GgafDx9God::_pID3DDevice9 -> SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _iSize_Verte_unit);
		GgafDx9God::_pID3DDevice9 -> SetMaterial(_pD3DMaterial9);
		GgafDx9God::_pID3DDevice9 -> SetFVF(GgafDx9SquareModel::FVF);
		GgafDx9God::_pID3DDevice9 -> SetTexture(0, NULL);
	} else { //前回と描画モデルが同じ
		// → 何もせんでよい。こりゃはやいでっせ～！(たぶん)
	}

	//2D故描画して、ライトまたつけとく
	GgafDx9God::_pID3DDevice9 -> SetRenderState(D3DRS_LIGHTING, FALSE); //ライトオフ
	GgafDx9God::_pID3DDevice9 -> DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	GgafDx9God::_pID3DDevice9 -> SetRenderState(D3DRS_LIGHTING, TRUE);

	//前回描画モデル名保存
	GgafDx9Model::_modelname_lastdraw = _model_name;

	return D3D_OK;
}

void GgafDx9SquareModel::restore() {
	TRACE("GgafDx9SquareModel::restore() " <<  _model_name << " start");
	GgafDx9ModelManager::restoreSquareModel(this);
	TRACE("GgafDx9SquareModel::restore() " <<  _model_name << " end");
}

void GgafDx9SquareModel::onDeviceLost() {
	_TRACE_("GgafDx9SquareModel::onDeviceLost() " <<  _model_name << " start");

	_pIDirect3DVertexBuffer9->Release();
	_pIDirect3DVertexBuffer9 = NULL;

	delete _pD3DMaterial9;
	_pD3DMaterial9 = NULL;

	_TRACE_("GgafDx9SquareModel::onDeviceLost() " <<  _model_name << " end");
}


GgafDx9SquareModel::~GgafDx9SquareModel() {
	TRACE("GgafDx9SquareModel::~GgafDx9SquareModel() " <<  _model_name << " start");

	_pIDirect3DVertexBuffer9->Release();
	_pIDirect3DVertexBuffer9 = NULL;

	delete _pD3DMaterial9;
	_pD3DMaterial9 = NULL;

	_TRACE_("GgafDx9SquareModel::~GgafDx9SquareModel() " <<  _model_name << " end");
}
