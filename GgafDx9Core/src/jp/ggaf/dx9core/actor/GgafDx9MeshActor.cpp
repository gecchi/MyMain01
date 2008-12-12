#include "stdafx.h"

GgafDx9MeshActor::GgafDx9MeshActor(string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
	_pMeshModel = GgafDx9ModelManager::getMeshModel(prm_meshmodel_name, D3DXMESH_SYSTEMMEM);
	_class_name = "GgafDx9MeshActor";
	_fAlpha = 1.0f;
}

void GgafDx9MeshActor::processDrawMain() {
	GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
	_pMeshModel->draw(this);
}

GgafDx9MeshActor::~GgafDx9MeshActor() {
}
