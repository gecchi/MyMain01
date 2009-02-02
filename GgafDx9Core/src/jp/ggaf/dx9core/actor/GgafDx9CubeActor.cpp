#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CubeActor::GgafDx9CubeActor(string prm_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker) : GgafDx9MeshActor(prm_name, "M/cube", prm_pGeoMover, prm_pGeoChecker) {
	_class_name = "GgafDx9CubeActor";
}

void GgafDx9CubeActor::processDrawMain() {
	GgafDx9UntransformedActor::setWorldTransformScRzMxyz(this);
	_pMeshModel->draw(this);
}
void GgafDx9CubeActor::drawBox(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2,  int prm_z2) {
	_SX = (prm_x2 - prm_x1);
	_SY = (prm_y2 - prm_y1);
	_SZ = (prm_z2 - prm_z1);
	_RZ = 0;
	_X = prm_x1 + (prm_x2 - prm_x1)/2;
	_Y = prm_y1 + (prm_y2 - prm_y1)/2;
	_Z = prm_z1 + (prm_z2 - prm_z1)/2;
	processDrawMain();

}

GgafDx9CubeActor::~GgafDx9CubeActor() {
}
