#include "jp/ggaf/dxcore/actor/ex/GgafDxSphereActor.h"

#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSphereActor::GgafDxSphereActor(const char* prm_name,
                                     GgafStatus* prm_pStat,
                                     GgafDxChecker* prm_pChecker) :

                                     GgafDxMeshActor(prm_name,
                                                     PROPERTY::COLI_SPHERE_MODEL.c_str(),
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
    //_DTRACE_("drawBox ("<<prm_x1<<","<<prm_y1<<","<<prm_z1<<","<<prm_x2<<","<<prm_y2<<","<<prm_z2<<")");
    //’¼Œa‚ª1‚Ì‹…ƒ‚ƒfƒ‹‚Å‚ ‚é‚½‚ßƒXƒP[ƒ‹‚Í‚Q”{‚µ‚Ä‚¨‚­
    _sx = prm_r*2;
    _sy = prm_r*2;
    _sz = prm_r*2;
    _rz = 0;
    _x = prm_x;
    _y = prm_y;
    _z = prm_z;
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    UTIL::setWorldMatrix_ScRzMv(this, _matWorld);
    processDraw();
}

GgafDxSphereActor::~GgafDxSphereActor() {
}
