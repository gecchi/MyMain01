#include "jp/ggaf/dxcore/actor/ex/GgafDxAABActor.h"

#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAABActor::GgafDxAABActor(const char* prm_name,
                               GgafStatus* prm_pStat,
                               GgafDxChecker* prm_pChecker) :

                                   GgafDxMeshActor(prm_name,
                                                   PROPERTY::COLI_AAB_MODEL.c_str(),
                                                   "DefaultMeshEffect",
                                                   "DefaultMeshTechnique",
                                                   prm_pStat,
                                                   prm_pChecker) {
    //_obj_class |= Obj_GgafDxAABActor;
    _class_name = "GgafDxAABActor";
}

//void GgafDxAABActor::processDraw() {
//    GgafDxGeometricActor::setWorldTransformScRzMxyz(this);
//    _pD3DXMeshModel->draw(this);
//}

void GgafDxAABActor::drawBox(coord prm_x1, coord prm_y1, coord prm_z1, coord prm_x2, coord prm_y2, coord prm_z2) {
    //_DTRACE_("drawBox ("<<prm_x1<<","<<prm_y1<<","<<prm_z1<<","<<prm_x2<<","<<prm_y2<<","<<prm_z2<<")");
    _sx = (prm_x2 - prm_x1);
    _sy = (prm_y2 - prm_y1);
    _sz = (prm_z2 - prm_z1);
    _rz = 0;
    _x = prm_x1 + (prm_x2 - prm_x1) / 2;
    _y = prm_y1 + (prm_y2 - prm_y1) / 2;
    _z = prm_z1 + (prm_z2 - prm_z1) / 2;
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    UTIL::setWorldMatrix_ScRzMv(this, _matWorld);
    processDraw();
}

GgafDxAABActor::~GgafDxAABActor() {
}
