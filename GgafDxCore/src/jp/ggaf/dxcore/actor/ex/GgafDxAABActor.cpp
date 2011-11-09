#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxAABActor::GgafDxAABActor(const char* prm_name, GgafStatus* prm_pStat,
                                   GgafDxChecker* prm_pChecker) :

                                   GgafDxMeshActor(prm_name,
                                                    "cube",
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
    //_TRACE_("drawBox ("<<prm_x1<<","<<prm_y1<<","<<prm_z1<<","<<prm_x2<<","<<prm_y2<<","<<prm_z2<<")");
    _SX = (prm_x2 - prm_x1);
    _SY = (prm_y2 - prm_y1);
    _SZ = (prm_z2 - prm_z1);
    _RZ = 0;
    _X = prm_x1 + (prm_x2 - prm_x1) / 2;
    _Y = prm_y1 + (prm_y2 - prm_y1) / 2;
    _Z = prm_z1 + (prm_z2 - prm_z1) / 2;
    _fX = CO2DX(_X);
    _fY = CO2DX(_Y);
    _fZ = CO2DX(_Z);
    GgafDxUtil::setWorldMatrix_ScRzMv(this, _matWorld);
    processDraw();
}

GgafDxAABActor::~GgafDxAABActor() {
}