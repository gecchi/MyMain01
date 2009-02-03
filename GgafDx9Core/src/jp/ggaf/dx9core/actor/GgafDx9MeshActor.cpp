#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9MeshActor::GgafDx9MeshActor(string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
	_pModelLead = (GgafDx9ModelLead*)GgafDx9God::_pModelManager->lead(prm_meshmodel_name.c_str());
	_pMeshModel = (GgafDx9MeshModel*)_pModelLead->getResource();
	_class_name = "GgafDx9MeshActor";
	//マテリアルをコピー
	_paD3DMaterial9 = NEW D3DMATERIAL9[_pMeshModel->_dwNumMaterials];
	for (DWORD i = 0; i < _pMeshModel->_dwNumMaterials; i++) {
		_paD3DMaterial9[i] = _pMeshModel->_paD3DMaterial9_default[i];
	}

}

void GgafDx9MeshActor::setAlpha(float prm_fAlpha) {
	_fAlpha = prm_fAlpha;
	//α設定
	for (DWORD i = 0; i < _pMeshModel->_dwNumMaterials; i++) {
		_paD3DMaterial9[i].Ambient.a = _fAlpha;
		_paD3DMaterial9[i].Diffuse.a = _fAlpha;
	}
}


void GgafDx9MeshActor::processDrawMain() {
	GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
	_pMeshModel->draw(this);
}

GgafDx9MeshActor::~GgafDx9MeshActor() {
	RELEASE_SAFE(_pModelLead);
	DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
