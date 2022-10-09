#include "jp/ggaf/dx/actor/debug/AABActor.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

AABActor::AABActor(const char* prm_name,
                   Checker* prm_pChecker) :
                           MeshActor(prm_name,
                                     CONFIG::COLI_AABOX_MODEL.c_str(),
                                     "DefaultMeshEffect",
                                     "DefaultMeshTechnique",
                                     prm_pChecker) {
    //_obj_class |= Obj_GgafDx_AABActor;
    _class_name = "AABActor";
}

//void AABActor::processDraw() {
//    GeometricActor::setWorldTransformScRzMxyz(this);
//    _pD3DXMeshModel->draw(this);
//}

void AABActor::drawBox(coord prm_x1, coord prm_y1, coord prm_z1, coord prm_x2, coord prm_y2, coord prm_z2) {
    //_TRACE_("drawBox ("<<prm_x1<<","<<prm_y1<<","<<prm_z1<<","<<prm_x2<<","<<prm_y2<<","<<prm_z2<<")");
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

AABActor::~AABActor() {
}
