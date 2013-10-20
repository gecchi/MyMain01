#include "stdafx.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxGeoElem::GgafDxGeoElem() : GgafObject() {
    X = 0;
    Y = 0;
    Z = 0;
    RX = 0;
    RY = 0;
    RZ = 0;
    _next = nullptr;
}

GgafDxGeoElem::GgafDxGeoElem(coord prm_X, coord prm_Y, coord prm_Z) : GgafObject() {
    X = prm_X;
    Y = prm_Y;
    Z = prm_Z;
    RX = 0;
    RY = 0;
    RZ = 0;
    _next = nullptr;
}

GgafDxGeoElem::GgafDxGeoElem(coord prm_X, coord prm_Y, coord prm_Z, angle prm_RX, angle prm_RY, angle prm_RZ) : GgafObject() {
    X = prm_X;
    Y = prm_Y;
    Z = prm_Z;
    RX = prm_RX;
    RY = prm_RY;
    RZ = prm_RZ;
    _next = nullptr;
}

GgafDxGeoElem::GgafDxGeoElem(GgafDxGeometricActor* prm_pActor) : GgafObject() {
    X = prm_pActor->_X;
    Y = prm_pActor->_Y;
    Z = prm_pActor->_Z;
    RX = prm_pActor->_RX;
    RY = prm_pActor->_RY;
    RZ = prm_pActor->_RZ;
    _next = nullptr;
}

void GgafDxGeoElem::set(coord prm_X, coord prm_Y, coord prm_Z, angle prm_RX, angle prm_RY, angle prm_RZ) {
    X = prm_X;
    Y = prm_Y;
    Z = prm_Z;
    RX = prm_RX;
    RY = prm_RY;
    RZ = prm_RZ;
}

void GgafDxGeoElem::set(coord prm_X, coord prm_Y, coord prm_Z) {
    X = prm_X;
    Y = prm_Y;
    Z = prm_Z;
}

void GgafDxGeoElem::set(GgafDxGeometricActor* prm_pActor) {
    X = prm_pActor->_X;
    Y = prm_pActor->_Y;
    Z = prm_pActor->_Z;
    RX = prm_pActor->_RX;
    RY = prm_pActor->_RY;
    RZ = prm_pActor->_RZ;
}

void GgafDxGeoElem::set(GgafDxGeoElem* prm_pGeoElem) {
    X = prm_pGeoElem->X;
    Y = prm_pGeoElem->Y;
    Z = prm_pGeoElem->Z;
    RX = prm_pGeoElem->RX;
    RY = prm_pGeoElem->RY;
    RZ = prm_pGeoElem->RZ;

}
GgafDxGeoElem::~GgafDxGeoElem() {
    _next = nullptr;
}

