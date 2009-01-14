#include "stdafx.h"

GgafDx9CubeActor::GgafDx9CubeActor(int prm_type, string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker)
: GgafDx9UntransformedActor(prm_type, prm_name, prm_pGeoMover, prm_pGeoChecker) {
	if (_type == ACTORTYPE_CUBE) {
		_pModel = (GgafDx9Model*)GgafDx9ModelManager::getMeshModel(prm_meshmodel_name, D3DXMESH_SYSTEMMEM);
		_pMeshModel = (GgafDx9MeshModel*)_pModel;
		_class_name = "GgafDx9CubeActor";
		_fAlpha = 1.0f;
	}
}

void GgafDx9CubeActor::processDrawMain() {
	GgafDx9UntransformedActor::setWorldTransformScRzMxyz(this);
	_pMeshModel->draw(this);
}

GgafDx9CubeActor::~GgafDx9CubeActor() {
}
