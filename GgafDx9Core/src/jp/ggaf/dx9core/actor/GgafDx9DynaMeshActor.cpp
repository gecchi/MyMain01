#include "stdafx.h"

GgafDx9DynaMeshActor::GgafDx9DynaMeshActor(int prm_type, string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker)
: GgafDx9UntransformedActor(prm_type, prm_name, prm_pGeoMover, prm_pGeoChecker) {
	if (_type == ACTORTYPE_DYNAMESH) {
		_pModel = (GgafDx9Model*)GgafDx9ModelManager::getMeshModel(prm_meshmodel_name, D3DXMESH_DYNAMIC);
		_pMeshModel = (GgafDx9MeshModel*)_pModel;
		_class_name = "GgafDx9DynaMeshActor";
		_fAlpha = 1.0f;
	}
}

void GgafDx9DynaMeshActor::processDrawMain() {
	GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
	_pMeshModel->draw(this);
}

GgafDx9DynaMeshActor::~GgafDx9DynaMeshActor() {
}
