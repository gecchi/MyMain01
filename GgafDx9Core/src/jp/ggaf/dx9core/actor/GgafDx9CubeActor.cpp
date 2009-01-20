#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CubeActor::GgafDx9CubeActor(string prm_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9MeshActor(prm_name, "cube", prm_pGeoMover, prm_pGeoChecker) {
	_class_name = "GgafDx9CubeActor";
}

void GgafDx9CubeActor::processDrawMain() {
	GgafDx9UntransformedActor::setWorldTransformScRzMxyz(this);
	_pMeshModel->draw(this);
}

GgafDx9CubeActor::~GgafDx9CubeActor() {
}
