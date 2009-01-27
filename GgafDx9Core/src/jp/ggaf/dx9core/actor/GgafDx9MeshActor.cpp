#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshActor::GgafDx9MeshActor(string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
	_pMeshModel = GgafDx9ModelManager::obtainMeshModel(prm_meshmodel_name, D3DXMESH_SYSTEMMEM);
	_class_name = "GgafDx9MeshActor";
	//マテリアルをコピー
	_paD3DMaterial9 = NEW D3DMATERIAL9[_pMeshModel->dwNumMaterials];
	for (int i = 0; i < _pMeshModel->dwNumMaterials; i++) {
		_paD3DMaterial9[i] = _pMeshModel->_paD3DMaterial9[i];
	}
	_fAlpha = 1.0f;
}

void GgafDx9MeshActor::setAlpha(float prm_fAlpha) {
	_fAlpha = prm_fAlpha;
	//α設定
	for (int i = 0; i < _pMeshModel->dwNumMaterials; i++) {
		_paD3DMaterial9[i].Ambient.a = _fAlpha;
		_paD3DMaterial9[i].Diffuse.a = _fAlpha;
	}
}

void GgafDx9MeshActor::processDrawMain() {
	GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
	_pMeshModel->draw(this);
}

GgafDx9MeshActor::~GgafDx9MeshActor() {
	DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
