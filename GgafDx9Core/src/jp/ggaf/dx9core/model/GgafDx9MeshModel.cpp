#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshModel::GgafDx9MeshModel(string prm_model_name, DWORD prm_dwOptions) : GgafDx9Model(prm_model_name) {
    TRACE("GgafDx9MeshModel::GgafDx9MeshModel(" <<  prm_model_name << ")");
	_pID3DXMesh      = NULL;
	_paD3DMaterial9_default  = NULL;
	_papTexture      = NULL;
	_dwNumMaterials  = 0L;
	_pModel_Next     = NULL;
	//上記のプロパティは、GgafDx9ModelManager::restoreMeshModel() から設定されることになる。
	_dwOptions = prm_dwOptions;
}

HRESULT GgafDx9MeshModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
	static GgafDx9UntransformedActor* pMeshActor_Target;
	//ここをどうやって振り分けるGgafDx9MeshActor と GgafDx9DynaMeshActor
	pMeshActor_Target = (GgafDx9UntransformedActor*)prm_pActor_Target;

	static HRESULT hr;
	for(DWORD i = 0; i < _dwNumMaterials; i++) {
        //マテリアルのセット
        GgafDx9God::_pID3DDevice9 -> SetMaterial(&(pMeshActor_Target->_paD3DMaterial9[i]));
		if (_papTexture[i] != NULL) {
			//テクスチャのセット
 			GgafDx9God::_pID3DDevice9 -> SetTexture( 0, _papTexture[i]->_pResource );
		} else {
			//無ければテクスチャ無し
 			GgafDx9God::_pID3DDevice9 -> SetTexture(0, NULL);
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
	GgafDx9ModelManager::_pTextureManager->releaseResource(_papTexture[i]);

	DELETEARR_IMPOSSIBLE_NULL(_papTexture); //テクスチャの配列
	RELEASE_IMPOSSIBLE_NULL(_pID3DXMesh);
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9_default);
	_TRACE_("GgafDx9MeshModel::release() " <<  _model_name << " end");
}

GgafDx9MeshModel::~GgafDx9MeshModel() {
    _TRACE_("GgafDx9MeshModel::~GgafDx9MeshModel() " <<  _model_name << " start");


    _TRACE_("GgafDx9MeshModel::~GgafDx9MeshModel() " <<  _model_name << " end");
}
