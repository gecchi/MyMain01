#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSphereActor::GgafDxSphereActor(const char* prm_name,
                                       GgafStatus* prm_pStat,
                                       GgafDxChecker* prm_pChecker) :

                                   GgafDxMeshActor(prm_name,
                                                    "sphere",
                                                    "DefaultMeshEffect",
                                                    "DefaultMeshTechnique",
                                                    prm_pStat,
                                                    prm_pChecker) {
    _class_name = "GgafDxSphereActor";
}

//void GgafDxSphereActor::processDraw() {
//    GgafDxGeometricActor::setWorldTransformScRzMxyz(this);
//    _pD3DXMeshModel->draw(this);
//}

void GgafDxSphereActor::drawSphere(coord prm_x, coord prm_y, coord prm_z, coord prm_r) {
    //_TRACE_("drawBox ("<<prm_x1<<","<<prm_y1<<","<<prm_z1<<","<<prm_x2<<","<<prm_y2<<","<<prm_z2<<")");
    //’¼Œa‚ª1‚Ì‹…ƒ‚ƒfƒ‹‚Å‚ ‚é‚½‚ßƒXƒP[ƒ‹‚Í‚Q”{‚µ‚Ä‚¨‚­
    _SX = prm_r*2;
    _SY = prm_r*2;
    _SZ = prm_r*2;
    _RZ = 0;
    _X = prm_x;
    _Y = prm_y;
    _Z = prm_z;
    _fX = Co2Dx(_X);
    _fY = Co2Dx(_Y);
    _fZ = Co2Dx(_Z);
    GgafDxUtil::setWorldMatrix_ScRzMv(this, _matWorld);
    processDraw();
}

GgafDxSphereActor::~GgafDxSphereActor() {
}
