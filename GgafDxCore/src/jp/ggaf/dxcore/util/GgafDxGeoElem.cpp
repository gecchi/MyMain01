#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxGeoElem::GgafDxGeoElem() : GgafObject() {
    x = 0;
    y = 0;
    z = 0;
    rx = 0;
    ry = 0;
    rz = 0;
    _next = nullptr;
}

GgafDxGeoElem::GgafDxGeoElem(coord prm_x, coord prm_y, coord prm_z) : GgafObject() {
    x = prm_x;
    y = prm_y;
    z = prm_z;
    rx = 0;
    ry = 0;
    rz = 0;
    _next = nullptr;
}

GgafDxGeoElem::GgafDxGeoElem(coord prm_x, coord prm_y, coord prm_z, angle prm_rx, angle prm_ry, angle prm_rz) : GgafObject() {
    x = prm_x;
    y = prm_y;
    z = prm_z;
    rx = prm_rx;
    ry = prm_ry;
    rz = prm_rz;
    _next = nullptr;
}

GgafDxGeoElem::GgafDxGeoElem(const GgafDxGeometricActor* prm_pActor) : GgafObject() {
    x = prm_pActor->_x;
    y = prm_pActor->_y;
    z = prm_pActor->_z;
    rx = prm_pActor->_rx;
    ry = prm_pActor->_ry;
    rz = prm_pActor->_rz;
    _next = nullptr;
}

void GgafDxGeoElem::set(coord prm_x, coord prm_y, coord prm_z, angle prm_rx, angle prm_ry, angle prm_rz) {
    x = prm_x;
    y = prm_y;
    z = prm_z;
    rx = prm_rx;
    ry = prm_ry;
    rz = prm_rz;
}

void GgafDxGeoElem::set(coord prm_x, coord prm_y, coord prm_z) {
    x = prm_x;
    y = prm_y;
    z = prm_z;
}

void GgafDxGeoElem::set(const GgafDxGeometricActor* prm_pActor) {
    x = prm_pActor->_x;
    y = prm_pActor->_y;
    z = prm_pActor->_z;
    rx = prm_pActor->_rx;
    ry = prm_pActor->_ry;
    rz = prm_pActor->_rz;
}

void GgafDxGeoElem::set(const GgafDxGeoElem* prm_pGeoElem) {
    x = prm_pGeoElem->x;
    y = prm_pGeoElem->y;
    z = prm_pGeoElem->z;
    rx = prm_pGeoElem->rx;
    ry = prm_pGeoElem->ry;
    rz = prm_pGeoElem->rz;

}
GgafDxGeoElem::~GgafDxGeoElem() {
    _next = nullptr;
}

