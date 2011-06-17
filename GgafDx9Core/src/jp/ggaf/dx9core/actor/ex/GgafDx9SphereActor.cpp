#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SphereActor::GgafDx9SphereActor(const char* prm_name,
                                   GgafDx9Checker* prm_pChecker) :

                                   GgafDx9MeshActor(prm_name,
                                                    "sphere",
                                                    "DefaultMeshEffect",
                                                    "DefaultMeshTechnique",
                                                    prm_pChecker) {
    _class_name = "GgafDx9SphereActor";
}

//void GgafDx9SphereActor::processDraw() {
//    GgafDx9GeometricActor::setWorldTransformScRzMxyz(this);
//    _pD3DXMeshModel->draw(this);
//}

void GgafDx9SphereActor::drawSphere(int prm_x, int prm_y, int prm_z, int prm_r) {
    //_TRACE_("drawBox ("<<prm_x1<<","<<prm_y1<<","<<prm_z1<<","<<prm_x2<<","<<prm_y2<<","<<prm_z2<<")");
    //’¼Œa‚ª1‚Ì‹…ƒ‚ƒfƒ‹‚Å‚ ‚é‚½‚ßƒXƒP[ƒ‹‚Í‚Q”{‚µ‚Ä‚¨‚­
    _SX = prm_r*2;
    _SY = prm_r*2;
    _SZ = prm_r*2;
    _RZ = 0;
    _X = prm_x;
    _Y = prm_y;
    _Z = prm_z;
    _fX = cnvCoordApp2Dx(_X);
    _fY = cnvCoordApp2Dx(_Y);
    _fZ = cnvCoordApp2Dx(_Z);
    GgafDx9Util::setWorldMatrix_ScRzMv(this, _matWorld);
    processDraw();
}

GgafDx9SphereActor::~GgafDx9SphereActor() {
}
