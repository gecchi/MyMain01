#include "jp/ggaf/dx/actor/debug/SphereActor.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

SphereActor::SphereActor(const char* prm_name) :

                             MeshActor(prm_name,
                                       CONFIG::COLI_SPHERE_MODEL.c_str(),
                                       "DefaultMeshEffect",
                                       "DefaultMeshTechnique") {
    _class_name = "SphereActor";
}

void SphereActor::drawSphere(coord prm_x, coord prm_y, coord prm_z, coord prm_r) {
    //_TRACE_("drawBox ("<<prm_x1<<","<<prm_y1<<","<<prm_z1<<","<<prm_x2<<","<<prm_y2<<","<<prm_z2<<")");
    //直径が1の球モデルであるためスケールは２倍しておく
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

SphereActor::~SphereActor() {
}
