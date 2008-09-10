#include "stdafx.h"


DWORD GgafDx9PlateModel::FVF =  (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);

GgafDx9PlateModel::GgafDx9PlateModel(string prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE("GgafDx9PlateModel::GgafDx9PlateModel(" <<  _model_name << ")");
	_fSize_PlateModelWidth  = 32.0f;
	_fSize_PlateModelHeight = 32.0f;
	_iRowNum_TextureSplit    = 1;
	_iColNum_TextureSplit    = 1;
	_iPatternNo_Max = 1;
	_pID3DTexture9 = NULL;
	_pModel_Next = NULL;

	_pRectUV_drawlast = NULL;
}



//描画

HRESULT GgafDx9PlateModel::draw(GgafDx9MainActor* prm_pActor_Target) {
	TRACE("GgafDx9PlateModel::draw("<<prm_pActor_Target->getName()<<")");
	//GgafDx9God::_pID3DDevice9 ->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0x000000, 1.0, 0);
	GgafDx9PlateActor* pPlateActor_Target = (GgafDx9PlateActor*)prm_pActor_Target;
	if (GgafDx9Model::_s_modelname_lastdraw != _model_name) {
		GgafDx9God::_pID3DDevice9 -> SetMaterial(_pD3DMaterial9);
		GgafDx9God::_pID3DDevice9 -> SetFVF(GgafDx9PlateModel::FVF);
		GgafDx9God::_pID3DDevice9 -> SetTexture( 0, (_pID3DTexture9));
	} else {
		//ちょっとだけ早いのよ！
		GgafDx9God::_pID3DDevice9 -> SetMaterial(_pD3DMaterial9);
	}
	GgafDx9God::_pID3DDevice9 -> SetRenderState(D3DRS_LIGHTING, FALSE); //ライトオフ
	GgafDx9God::_pID3DDevice9 -> DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pPlateActor_Target->_paVertex, pPlateActor_Target->_iSize_Verte_unit);
	GgafDx9God::_pID3DDevice9 -> SetRenderState(D3DRS_LIGHTING, TRUE);

	GgafDx9Model::_s_modelname_lastdraw = _model_name; //前回描画モデル名保存
	return D3D_OK;
}


void GgafDx9PlateModel::restore() {
	TRACE("GgafDx9PlateModel::restore() " <<  _model_name << " start");
	GgafDx9ModelManager::restorePlateModel(this);
	TRACE("GgafDx9PlateModel::restore() " <<  _model_name << " end");
}


void GgafDx9PlateModel::onDeviceLost() {
	_TRACE_("GgafDx9PlateModel::onDeviceLost() " <<  _model_name << " start");
    _pID3DTexture9 -> Release();
	_pID3DTexture9 = NULL;
	delete _pD3DMaterial9;
	_pD3DMaterial9 = NULL;
	_TRACE_("GgafDx9PlateModel::onDeviceLost() " <<  _model_name << " end");
}

GgafDx9PlateModel::~GgafDx9PlateModel() {
    _TRACE_("GgafDx9PlateModel::~GgafDx9PlateModel() " <<  _model_name << " start");
    _pID3DTexture9 -> Release();
	_pID3DTexture9 = NULL;
	delete _pD3DMaterial9;
	_pD3DMaterial9 = NULL;
	delete[] _paRectUV;
	_paRectUV = NULL;
    _TRACE_("GgafDx9PlateModel::~GgafDx9PlateModel() " <<  _model_name << " end");
}
