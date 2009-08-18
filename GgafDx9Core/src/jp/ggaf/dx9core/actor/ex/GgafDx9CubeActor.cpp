#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CubeActor::GgafDx9CubeActor(const char* prm_name,
                                   GgafDx9Checker* prm_pChecker) :

                                   GgafDx9MeshActor(prm_name,
                                                    "cube",
                                                    "DefaultMashEffect",
                                                    "DefaultMeshTechnique",
                                                    prm_pChecker) {
    _class_name = "GgafDx9CubeActor";
}

//void GgafDx9CubeActor::processDraw() {
//    GgafDx9GeometricActor::setWorldTransformScRzMxyz(this);
//    _pD3DXMeshModel->draw(this);
//}

void GgafDx9CubeActor::drawBox(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2) {
    _SX = (prm_x2 - prm_x1);
    _SY = (prm_y2 - prm_y1);
    _SZ = (prm_z2 - prm_z1);
    _RZ = 0;
    _X = prm_x1 + (prm_x2 - prm_x1) / 2;
    _Y = prm_y1 + (prm_y2 - prm_y1) / 2;
    _Z = prm_z1 + (prm_z2 - prm_z1) / 2;
    processPreJudgement();
    processDraw();
}

GgafDx9CubeActor::~GgafDx9CubeActor() {
}
