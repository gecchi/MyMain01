#include "stdafx.h"

GgafDx9MeshModel::GgafDx9MeshModel(string prm_model_name) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9MeshModel::GgafDx9MeshModel(" <<  prm_model_name << ")");
	_pID3DXMesh      = NULL;
	_paD3DMaterial9  = NULL;
	_papID3DTexture9 = NULL;
	_dwNumMaterials  = 0L;
	_pModel_Next     = NULL;
}



HRESULT GgafDx9MeshModel::draw(GgafDx9MainActor* prm_pActor_Target) {
	GgafDx9MeshActor* pMeshActor_Target = (GgafDx9MeshActor*)prm_pActor_Target;

	HRESULT hr;
	for(DWORD i = 0; i < _dwNumMaterials; i++ ) {

        hr = GgafDx9God::_pID3DDevice9 -> SetMaterial(&(_paD3DMaterial9[i]));	//マテリアルのセット
		if(FAILED(hr)) {
			throw_GgafCriticalException("[GgafDx9MeshModel::draw]["<<prm_pActor_Target->getName()<<"]のSetMaterial(&(paD3DMaterial9[i].MatD3D)失敗 model="<<_model_name<<"/hr="<<hr);
		}
		if (_papID3DTexture9[i] != NULL) {
			hr = GgafDx9God::_pID3DDevice9 -> SetTexture( 0, _papID3DTexture9[i] );	//テクスチャのセット
 			if(FAILED(hr)) {
				throw_GgafCriticalException("[GgafDx9MeshModel::draw] ["<<prm_pActor_Target->getName()<<"]のSetTexture( 0, papID3DTexture9[i])  失敗 model="<<_model_name<<"/hr="<<hr);
			}
		} else {
			hr = GgafDx9God::_pID3DDevice9 -> SetTexture(0, NULL); //無ければテクスチャ無し
 			if(FAILED(hr)) {
				throw_GgafCriticalException("[GgafDx9MeshModel::draw] ["<<prm_pActor_Target->getName()<<"]のSetTexture( 0, NULL) 失敗 model="<<_model_name<<"/hr="<<hr);
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

		if(FAILED(hr)) {
			throw_GgafCriticalException("[GgafDx9MeshModel::draw] ["<<prm_pActor_Target->getName()<<"]のpID3DXMesh -> DrawSubset失敗 model="<<_model_name<<"/hr="<<hr);
		}
	}

	//前回描画モデル名反映
	GgafDx9Model::_modelname_lastdraw = _model_name;
	return D3D_OK;
}

void GgafDx9MeshModel::restore() {
	TRACE("GgafDx9MeshModel::restore() " <<  _model_name << " start");
	GgafDx9ModelManager::restoreMeshModel(this);
	TRACE("GgafDx9MeshModel::restore() " <<  _model_name << " end");
}

void GgafDx9MeshModel::onDeviceLost() {
	_TRACE_("GgafDx9MeshModel::onDeviceLost() " <<  _model_name << " start");
	if (_pID3DXMesh == NULL) {
		throw_GgafCriticalException("[GgafDx9MeshModel::onDeviceLost] Error! オブジェクトになっていないため remove できません！");
	}
	for( DWORD i = 0; i < _dwNumMaterials; i++ ) {
		if (_papID3DTexture9[i] != NULL) { //テクスチャが無い場合もあるため
			_papID3DTexture9[i] -> Release();
			_papID3DTexture9[i] = NULL;
		}
	}
	delete [] _papID3DTexture9;
	_papID3DTexture9 = NULL;
	delete [] _paD3DMaterial9;
	_paD3DMaterial9 = NULL;
	//_pAdjacency -> Release();
	//_pAdjacency = NULL;
	_pID3DXMesh -> Release();
	_pID3DXMesh = NULL;
	_TRACE_("GgafDx9MeshModel::onDeviceLost() " <<  _model_name << " end");
}

GgafDx9MeshModel::~GgafDx9MeshModel() {
    _TRACE_("GgafDx9MeshModel::~GgafDx9MeshModel() " <<  _model_name << " start");
	if (_pID3DXMesh == NULL) {
		throw_GgafCriticalException("[GgafDx9MeshModel::remove] Error! オブジェクトになっていないため remove できません！");
	}
	for( DWORD i = 0; i < _dwNumMaterials; i++ ) {
		if (_papID3DTexture9[i] != NULL) { //テクスチャが無い場合もあるため
			_papID3DTexture9[i] -> Release();
			_papID3DTexture9[i] = NULL;
		}
	}
	delete [] _papID3DTexture9;
	_papID3DTexture9 = NULL;
	delete [] _paD3DMaterial9;
	_paD3DMaterial9 = NULL;
	//_pAdjacency -> Release();
	//_pAdjacency = NULL;
	_pID3DXMesh -> Release();
	_pID3DXMesh = NULL;
    _TRACE_("GgafDx9MeshModel::~GgafDx9MeshModel() " <<  _model_name << " end");
}
