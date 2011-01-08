#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9AABActor::GgafDx9AABActor(const char* prm_name,
                                   GgafDx9Checker* prm_pChecker) :

                                   GgafDx9MeshActor(prm_name,
                                                    "cube",
                                                    "DefaultMeshEffect",
                                                    "DefaultMeshTechnique",
                                                    prm_pChecker) {
    //_obj_class |= Obj_GgafDx9AABActor;
    _class_name = "GgafDx9AABActor";
}

//void GgafDx9AABActor::processDraw() {
//    GgafDx9GeometricActor::setWorldTransformScRzMxyz(this);
//    _pD3DXMeshModel->draw(this);
//}

void GgafDx9AABActor::drawBox(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2) {
    //_TRACE_("drawBox ("<<prm_x1<<","<<prm_y1<<","<<prm_z1<<","<<prm_x2<<","<<prm_y2<<","<<prm_z2<<")");
    _SX = (prm_x2 - prm_x1);
    _SY = (prm_y2 - prm_y1);
    _SZ = (prm_z2 - prm_z1);
    _RZ = 0;
    _X = prm_x1 + (prm_x2 - prm_x1) / 2;
    _Y = prm_y1 + (prm_y2 - prm_y1) / 2;
    _Z = prm_z1 + (prm_z2 - prm_z1) / 2;
    _fX = (FLOAT)(1.0f * _X / LEN_UNIT / PX_UNIT);
    _fY = (FLOAT)(1.0f * _Y / LEN_UNIT / PX_UNIT);
    _fZ = (FLOAT)(1.0f * _Z / LEN_UNIT / PX_UNIT);
    GgafDx9Util::setWorldMatrix_ScRzMv(this, _matWorld);
    processDraw();
}

GgafDx9AABActor::~GgafDx9AABActor() {
}