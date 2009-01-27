#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshModel::GgafDx9MeshModel(string prm_model_name, DWORD prm_dwOptions) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9MeshModel::GgafDx9MeshModel(" <<  prm_model_name << ")");
	_pID3DXMesh      = NULL;
	_paD3DMaterial9  = NULL;
	_papTexture      = NULL;
	_dwNumMaterials  = 0L;
	_pModel_Next     = NULL;
	//上記のプロパティは、GgafDx9ModelManager::restoreMeshModel() から設定されることになる。
	_dwOptions = prm_dwOptions;
}

HRESULT GgafDx9MeshModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
	static GgafDx9MeshActor* pMeshActor_Target;
	pMeshActor_Target = (GgafDx9MeshActor*)prm_pActor_Target;

	static HRESULT hr;
	for(DWORD i = 0; i < _dwNumMaterials; i++) {

		_paD3DMaterial9[i].Ambient.a = pMeshActor_Target->_fAlpha;
		_paD3DMaterial9[i].Diffuse.a = pMeshActor_Target->_fAlpha;
        //マテリアルのセット
        if(GgafDx9God::_pID3DDevice9 -> SetMaterial(&(_paD3DMaterial9[i])) != D3D_OK) {
        	throw_GgafDx9CriticalException("[GgafDx9MeshModel::draw]["<<prm_pActor_Target->getName()<<"]のSetMaterial(&(paD3DMaterial9[i].MatD3D)失敗 model="<<_model_name, hr);
		}
		if (_papTexture[i] != NULL) {
			//テクスチャのセット
 			if(GgafDx9God::_pID3DDevice9 -> SetTexture( 0, _papTexture[i]->_pIDirect3DTexture9 ) != D3D_OK) {
 				throw_GgafDx9CriticalException("[GgafDx9MeshModel::draw] ["<<prm_pActor_Target->getName()<<"]のSetTexture( 0, papID3DTexture9[i])  失敗 model="<<_model_name, hr);
			}
		} else {
			//無ければテクスチャ無し
 			if(GgafDx9God::_pID3DDevice9 -> SetTexture(0, NULL) != D3D_OK) {
 				throw_GgafDx9CriticalException("[GgafDx9MeshModel::draw] ["<<prm_pActor_Target->getName()<<"]のSetTexture( 0, NULL) 失敗 model="<<_model_name, hr);
			}
		}
		//描画
		if (pMeshActor_Target->_SX == LEN_UNIT &&
		    pMeshActor_Target->_SY == LEN_UNIT &&
		    pMeshActor_Target->_SZ == LEN_UNIT)
		{
			hr = _pID3DXMesh -> DrawSubset( i ); //なんて便利なメソッド！
		} else {
			//拡大縮小がなされているため、カメラ空間にトランスフォームされた後で頂点法線の正規化するように設定（負荷高）
			GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
			hr = _pID3DXMesh -> DrawSubset( i ); //なんて便利なメソッド！
			GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
		}

		if(hr != D3D_OK) {
			throw_GgafDx9CriticalException("[GgafDx9MeshModel::draw] ["<<prm_pActor_Target->getName()<<"]のpID3DXMesh -> DrawSubset失敗 model="<<_model_name, hr);
		}

	}

	//前回描画モデル名反映
	GgafDx9Model::_id_lastdraw = _id;
	GgafGod::_iNumPlayingActor++;
	return D3D_OK;
}

void GgafDx9MeshModel::restore() {
	TRACE("GgafDx9MeshModel::restore() " <<  _model_name << " start");
	GgafDx9ModelManager::restoreMeshModel(this);
	TRACE("GgafDx9MeshModel::restore() " <<  _model_name << " end");
}

void GgafDx9MeshModel::onDeviceLost() {
	_TRACE_("GgafDx9MeshModel::onDeviceLost() " <<  _model_name << " start");
	//デバイスロスト時は解放します。
    release();
    _TRACE_("GgafDx9MeshModel::onDeviceLost() " <<  _model_name << " end");
}

void GgafDx9MeshModel::release() {
	_TRACE_("GgafDx9MeshModel::release() " <<  _model_name << " start");
	if (_pID3DXMesh == NULL) {
		throw_GgafCriticalException("[GgafDx9MeshModel::release] Error! _pID3DXMeshが オブジェクトになっていないため release できません！");
	}
	//テクスチャを解放するかどうか
	for( DWORD i = 0; i < _dwNumMaterials; i++) {
		if (_papTexture[i] == NULL) {
			continue;
		} else {
			_papTexture[i]->_iRefModelNum--; //参照カウンタを -1
			if (_papTexture[i]->_iRefModelNum == 0) {
				//指しているモデルが無いのでテクスチャを解放
				GgafDx9TextureManager::remove(_papTexture[i]);
			}
		}
	}
	DELETEARR_IMPOSSIBLE_NULL(_papTexture); //テクスチャの配列

	DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
	RELEASE_IMPOSSIBLE_NULL(_pID3DXMesh);
	_TRACE_("GgafDx9MeshModel::release() " <<  _model_name << " end");
}

GgafDx9MeshModel::~GgafDx9MeshModel() {
    _TRACE_("GgafDx9MeshModel::~GgafDx9MeshModel() " <<  _model_name << " start");
    _TRACE_("GgafDx9MeshModel::~GgafDx9MeshModel() " <<  _model_name << " end");
}
