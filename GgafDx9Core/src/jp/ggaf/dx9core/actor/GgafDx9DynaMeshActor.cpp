#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9DynaMeshActor::GgafDx9DynaMeshActor(string prm_name, string prm_meshmodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9UntransformedActor(prm_name, prm_pGeoMover, prm_pGeoChecker) {
	_pMeshModel = GgafDx9ModelManager::getMeshModel(prm_meshmodel_name, D3DXMESH_DYNAMIC);
	_class_name = "GgafDx9DynaMeshActor";
	_fAlpha = 1.0f;
}

void GgafDx9DynaMeshActor::processDrawMain() {
	GgafDx9UntransformedActor::setWorldTransformRxRzRyScMv(this);
	_pMeshModel->draw(this);
}

GgafDx9DynaMeshActor::~GgafDx9DynaMeshActor() {
}
