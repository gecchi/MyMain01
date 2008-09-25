#include "stdafx.h"


DWORD GgafDx9SpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9SpriteModel::GgafDx9SpriteModel(string prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
	TRACE("GgafDx9SpriteModel::GgafDx9SpriteModel(" <<  _model_name << ")");

	_fSize_SpriteModelWidthPx  = 32.0f;
	_fSize_SpriteModelHeightPx = 32.0f;
	_iRowNum_TextureSplit    = 1;
	_iColNum_TextureSplit    = 1;
	_iAnimationPatternNo_Max = 1;
	_pModel_Next = NULL;
	_isChangedAlpha = false;
	_pIDirect3DVertexBuffer9 = NULL;
	_iChangeVertexAlpha = 255;
	//デバイイスロスト対応のため、テクスチャ、頂点、マテリアルの初期化は
	//GgafDx9ModelManager::restoreSpriteModel で行っている。
}

//描画
HRESULT GgafDx9SpriteModel::draw(GgafDx9MainActor* prm_pActor_Target) {
	TRACE("GgafDx9SpriteModel::draw("<<prm_pActor_Target->getName()<<")");

	//対象SpriteActor
	GgafDx9SpriteActor* pSpriteActor_Target = (GgafDx9SpriteActor*)prm_pActor_Target;
	//今回描画のUV
	GgafDx9RectUV* pRectUV_Active = _paRectUV + (pSpriteActor_Target->_iAnimationPatternNo_Active);

	HRESULT	hr;
	if (GgafDx9Model::_s_modelname_lastdraw != _model_name) {
		//前回描画とモデルが違う！
		GgafDx9God::_pID3DDevice9 -> SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _iSize_Vertec_unit);
		GgafDx9God::_pID3DDevice9 -> SetMaterial(_pD3DMaterial9);
		GgafDx9God::_pID3DDevice9 -> SetFVF(GgafDx9SpriteModel::FVF);
		GgafDx9God::_pID3DDevice9 -> SetTexture( 0, (_pID3DTexture9));
	}

	if (_pRectUV_drawlast != pRectUV_Active) {
		//前回描画UV違う！、頂点バッファの tu, tv を直接変更
		static VERTEX* paVertexBuffer;
		hr = _pIDirect3DVertexBuffer9 -> Lock(0, _iSize_Vertecs, (void**)&paVertexBuffer, 0);
		if(FAILED(hr)) {
			throw_GgafCriticalException("[GgafDx9SpriteModelManager::draw] 頂点バッファのロック取得に失敗１ model="<<_model_name<<"/hr="<<hr);
		}
		paVertexBuffer[0].tu = pRectUV_Active->_aUV[0].tu;
		paVertexBuffer[0].tv = pRectUV_Active->_aUV[0].tv;
		paVertexBuffer[1].tu = pRectUV_Active->_aUV[1].tu;
		paVertexBuffer[1].tv = pRectUV_Active->_aUV[1].tv;
		paVertexBuffer[2].tu = pRectUV_Active->_aUV[2].tu;
		paVertexBuffer[2].tv = pRectUV_Active->_aUV[2].tv;
		paVertexBuffer[3].tu = pRectUV_Active->_aUV[3].tu;
		paVertexBuffer[3].tv = pRectUV_Active->_aUV[3].tv;
		if (_isChangedAlpha) { //Alpha変更があるならついでにする。
			paVertexBuffer[0].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
			paVertexBuffer[1].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
			paVertexBuffer[2].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
			paVertexBuffer[3].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
			_isChangedAlpha = false;
		}
		_pIDirect3DVertexBuffer9->Unlock();
	} else {
		//前回描画モデルもUVも同じ
		// → 何もせんでよい。こりゃはやいでっせ～！(たぶん)
	}

	if (_isChangedAlpha) {
		//前回描画UVが同じでもAlpha変更な場合
		static VERTEX* paVertexBuffer;
		hr = _pIDirect3DVertexBuffer9 -> Lock(0, _iSize_Vertecs, (void**)&paVertexBuffer, 0);
		if(FAILED(hr)) {
			throw_GgafCriticalException("[GgafDx9SpriteModelManager::draw] 頂点バッファのロック取得に失敗２ model="<<_model_name<<"/hr="<<hr);
		}
		paVertexBuffer[0].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
		paVertexBuffer[1].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
		paVertexBuffer[2].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
		paVertexBuffer[3].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
		_isChangedAlpha = false;
		_pIDirect3DVertexBuffer9->Unlock();
	}



	//描画して、ライトまたつけとく
	GgafDx9God::_pID3DDevice9 -> SetRenderState(D3DRS_LIGHTING, FALSE); //ライトオフ
	GgafDx9God::_pID3DDevice9 -> DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	GgafDx9God::_pID3DDevice9 -> SetRenderState(D3DRS_LIGHTING, TRUE);

	//前回描画モデル名保存
	GgafDx9Model::_s_modelname_lastdraw = _model_name;
	//前回描画UV座標（へのポインタ）を保存
	_pRectUV_drawlast = pRectUV_Active;

	return D3D_OK;
}

void GgafDx9SpriteModel::restore() {
	TRACE("GgafDx9SpriteModel::restore() " <<  _model_name << " start");
	GgafDx9ModelManager::restoreSpriteModel(this);
	TRACE("GgafDx9SpriteModel::restore() " <<  _model_name << " end");
}

void GgafDx9SpriteModel::onDeviceLost() {
	_TRACE_("GgafDx9SpriteModel::onDeviceLost() " <<  _model_name << " start");
	_pIDirect3DVertexBuffer9->Release();
	_pIDirect3DVertexBuffer9 = NULL;

	delete _pD3DMaterial9;
	_pD3DMaterial9 = NULL;

	_pID3DTexture9 -> Release();
	_pID3DTexture9 = NULL;

	delete[] _paRectUV;
	_paRectUV = NULL;
	_TRACE_("GgafDx9SpriteModel::onDeviceLost() " <<  _model_name << " end");
}

void GgafDx9SpriteModel::changeVertexAlpha(int prm_iVertexAlpha) {
	_isChangedAlpha = true;
	_iChangeVertexAlpha = prm_iVertexAlpha;
}

GgafDx9SpriteModel::~GgafDx9SpriteModel() {
	_TRACE_("GgafDx9SpriteModel::~GgafDx9SpriteModel() " <<  _model_name << " start");
	_pIDirect3DVertexBuffer9->Release();
	_pIDirect3DVertexBuffer9 = NULL;

	delete _pD3DMaterial9;
	_pD3DMaterial9 = NULL;

	_pID3DTexture9 -> Release();
	_pID3DTexture9 = NULL;

	delete[] _paRectUV;
	_paRectUV = NULL;

	_TRACE_("GgafDx9SpriteModel::~GgafDx9SpriteModel() " <<  _model_name << " end");
}

