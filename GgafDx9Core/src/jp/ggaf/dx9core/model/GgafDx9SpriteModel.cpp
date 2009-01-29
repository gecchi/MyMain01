#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


DWORD GgafDx9SpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9 = NULL;

GgafDx9SpriteModel::GgafDx9SpriteModel(string prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
	TRACE("GgafDx9SpriteModel::GgafDx9SpriteModel(" <<  _model_name << ")");

	_fSize_SpriteModelWidthPx  = 32.0f;
	_fSize_SpriteModelHeightPx = 32.0f;
	_iRowNum_TextureSplit    = 1;
	_iColNum_TextureSplit    = 1;
	_iAnimationPatternNo_Max = 0;
	_pModel_Next = NULL;
	//_isChangedAlpha = false;
	_pIDirect3DVertexBuffer9 = NULL;
	_pTexture = NULL;
	//_iChangeVertexAlpha = 255;
	//デバイイスロスト対応のため、テクスチャ、頂点、マテリアルの初期化は
	//GgafDx9ModelManager::restoreSpriteModel で行っている。
}

//描画
HRESULT GgafDx9SpriteModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
	TRACE("GgafDx9SpriteModel::draw("<<prm_pActor_Target->getName()<<")");
	//対象SpriteActor
	GgafDx9SpriteActor* pSpriteActor_Target = (GgafDx9SpriteActor*)prm_pActor_Target;
	//今回描画のUV
	GgafDx9RectUV* pRectUV_Active = _paRectUV + (pSpriteActor_Target->_iAnimationPatternNo_Active);

	static HRESULT	hr;

	if (GgafDx9Model::_id_lastdraw != _id) {
		//前回描画とモデルが違う！
		GgafDx9God::_pID3DDevice9 -> SetStreamSource(0, _pIDirect3DVertexBuffer9, 0, _iSize_Vertec_unit);
		GgafDx9God::_pID3DDevice9 -> SetFVF(GgafDx9SpriteModel::FVF);
		GgafDx9God::_pID3DDevice9 -> SetTexture( 0, _pTexture->get() );
	}

	if (_pRectUV_drawlast != pRectUV_Active) {
		//前回描画UV違う！、頂点バッファの tu, tv を直接変更
		static VERTEX* paVertexBuffer;
		hr = _pIDirect3DVertexBuffer9 -> Lock(0, _iSize_Vertecs, (void**)&paVertexBuffer, 0);
		paVertexBuffer[0].tu = pRectUV_Active->_aUV[0].tu;
		paVertexBuffer[0].tv = pRectUV_Active->_aUV[0].tv;
		paVertexBuffer[1].tu = pRectUV_Active->_aUV[1].tu;
		paVertexBuffer[1].tv = pRectUV_Active->_aUV[1].tv;
		paVertexBuffer[2].tu = pRectUV_Active->_aUV[2].tu;
		paVertexBuffer[2].tv = pRectUV_Active->_aUV[2].tv;
		paVertexBuffer[3].tu = pRectUV_Active->_aUV[3].tu;
		paVertexBuffer[3].tv = pRectUV_Active->_aUV[3].tv;
//		if (_isChangedAlpha) { //Alpha変更があるならついでにする。
//			paVertexBuffer[0].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//			paVertexBuffer[1].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//			paVertexBuffer[2].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//			paVertexBuffer[3].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//			_isChangedAlpha = false;
//		}
		_pIDirect3DVertexBuffer9->Unlock();
	} else {
		//前回描画モデルもUVも同じ
		// → 何もせんでよい。こりゃはやいでっせ～！(たぶん)
	}
	GgafDx9God::_pID3DDevice9 -> SetMaterial(&(pSpriteActor_Target->_paD3DMaterial9[0]));

//	if (_isChangedAlpha) {
//		//前回描画UVが同じでもAlpha変更な場合
//		static VERTEX* paVertexBuffer;
//		hr = _pIDirect3DVertexBuffer9 -> Lock(0, _iSize_Vertecs, (void**)&paVertexBuffer, 0);
//		if(hr != D3D_OK) {
//			throw_GgafCriticalException("[GgafDx9SpriteModelManager::draw] 頂点バッファのロック取得に失敗２ model="<<_model_name<<"/hr="<<hr);
//		}
//		paVertexBuffer[0].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//		paVertexBuffer[1].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//		paVertexBuffer[2].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//		paVertexBuffer[3].color = D3DCOLOR_ARGB(_iChangeVertexAlpha,255,255,255);
//		_isChangedAlpha = false;
//		_pIDirect3DVertexBuffer9->Unlock();
//	}


	//GgafDx9God::_pID3DDevice9 -> SetRenderState(D3DRS_LIGHTING, FALSE); //ライトオフ
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, 0xffffffff);//陰影を無くすため環境光を最高にする
	GgafDx9God::_pID3DDevice9->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, GgafDx9God::_dwAmbientBrightness_default);//環境光を元通り
	//GgafDx9God::_pID3DDevice9 -> SetRenderState(D3DRS_LIGHTING, TRUE);

	//↑＜2008/10/24 の脳みそ＞
	//ライトを切らずにアンビエントを強めてスプライトらしく平面的な表示をすることにした（角度によって影がでない）。
	//ライトを切らないのは、レンダリングでマテリアルによるαブレンドを行うというもくろみのため。
	//しかし、ライトを切って、頂点αという手もある。そのほうが多分軽いし最初は頂点αだった。
	//しかし、スペキュラ反射のアニメーションとかもやりたいかもしれない。頂点カラーでスペキュラできる？のかわからないので、
	//マテリアルαでいけるようにしておく。ここはいろいろ実験すべき。
	//TODO
	//2009/1/15 プログラマブルシェーダーに目覚めた。つくりなおすっす

	//前回描画モデル名保存
	GgafDx9Model::_id_lastdraw = _id;
	//前回描画UV座標（へのポインタ）を保存
	_pRectUV_drawlast = pRectUV_Active;
	GgafGod::_iNumPlayingActor++;
	return D3D_OK;
}

void GgafDx9SpriteModel::restore() {
	TRACE("GgafDx9SpriteModel::restore() " <<  _model_name << " start");
	GgafDx9ModelManager::restoreSpriteModel(this);
	TRACE("GgafDx9SpriteModel::restore() " <<  _model_name << " end");
}

void GgafDx9SpriteModel::onDeviceLost() {
	_TRACE_("GgafDx9SpriteModel::onDeviceLost() " <<  _model_name << " start");
	release();
	_TRACE_("GgafDx9SpriteModel::onDeviceLost() " <<  _model_name << " end");
}
//
//void GgafDx9SpriteModel::changeVertexAlpha(int prm_iVertexAlpha) {
//	_isChangedAlpha = true;
//	_iChangeVertexAlpha = prm_iVertexAlpha;
//}

void GgafDx9SpriteModel::release() {
	_TRACE_("GgafDx9SpriteModel::release() " <<  _model_name << " start");
	RELEASE_IMPOSSIBLE_NULL(_pIDirect3DVertexBuffer9);
	DELETE_IMPOSSIBLE_NULL(_pD3DMaterial9_default);
	//GgafDx9ModelManager::_pTextureManager->releaseResourceConnection(_pTexture);
	RELEASE_IMPOSSIBLE_NULL(_pTexture);
	DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
	_TRACE_("GgafDx9SpriteModel::release() " <<  _model_name << " end");

}
GgafDx9SpriteModel::~GgafDx9SpriteModel() {
	_TRACE_("GgafDx9SpriteModel::~GgafDx9SpriteModel() " <<  _model_name << " start");
	_TRACE_("GgafDx9SpriteModel::~GgafDx9SpriteModel() " <<  _model_name << " end");
}

