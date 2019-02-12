#include "jp/ggaf/dx/util/GeoElem.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"


using namespace GgafDx;

GeoElem::GeoElem() : GgafCore::Object() {
    x = 0;
    y = 0;
    z = 0;
    rx = 0;
    ry = 0;
    rz = 0;
    _next = nullptr;
}

GeoElem::GeoElem(coord prm_x, coord prm_y, coord prm_z) : GgafCore::Object() {
    x = prm_x;
    y = prm_y;
    z = prm_z;
    rx = 0;
    ry = 0;
    rz = 0;
    _next = nullptr;
}

GeoElem::GeoElem(coord prm_x, coord prm_y, coord prm_z, angle prm_rx, angle prm_ry, angle prm_rz) : GgafCore::Object() {
    x = prm_x;
    y = prm_y;
    z = prm_z;
    rx = prm_rx;
    ry = prm_ry;
    rz = prm_rz;
    _next = nullptr;
}

GeoElem::GeoElem(const GeometricActor* prm_pActor) : GgafCore::Object() {
    x = prm_pActor->_x;
    y = prm_pActor->_y;
    z = prm_pActor->_z;
    rx = prm_pActor->_rx;
    ry = prm_pActor->_ry;
    rz = prm_pActor->_rz;
    _next = nullptr;
}

void GeoElem::set(coord prm_x, coord prm_y, coord prm_z, angle prm_rx, angle prm_ry, angle prm_rz) {
    x = prm_x;
    y = prm_y;
    z = prm_z;
    rx = prm_rx;
    ry = prm_ry;
    rz = prm_rz;
}

void GeoElem::set(coord prm_x, coord prm_y, coord prm_z) {
    x = prm_x;
    y = prm_y;
    z = prm_z;
}

void GeoElem::set(const GeometricActor* prm_pActor) {
    x = prm_pActor->_x;
    y = prm_pActor->_y;
    z = prm_pActor->_z;
    rx = prm_pActor->_rx;
    ry = prm_pActor->_ry;
    rz = prm_pActor->_rz;
}

void GeoElem::set(const GeoElem* prm_pGeoElem) {
    x = prm_pGeoElem->x;
    y = prm_pGeoElem->y;
    z = prm_pGeoElem->z;
    rx = prm_pGeoElem->rx;
    ry = prm_pGeoElem->ry;
    rz = prm_pGeoElem->rz;

}
GeoElem::~GeoElem() {
    _next = nullptr;
}

