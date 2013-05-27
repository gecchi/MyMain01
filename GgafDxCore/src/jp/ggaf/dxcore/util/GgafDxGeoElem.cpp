#include "stdafx.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxGeoElem::GgafDxGeoElem() : GgafObject() {
    _X = 0;
    _Y = 0;
    _Z = 0;
    _RX = 0;
    _RY = 0;
    _RZ = 0;
    _next = nullptr;
}

GgafDxGeoElem::GgafDxGeoElem(coord prm_X, coord prm_Y, coord prm_Z) : GgafObject() {
    _X = prm_X;
    _Y = prm_Y;
    _Z = prm_Z;
    _RX = 0;
    _RY = 0;
    _RZ = 0;
    _next = nullptr;
}

GgafDxGeoElem::GgafDxGeoElem(coord prm_X, coord prm_Y, coord prm_Z, angle prm_RX, angle prm_RY, angle prm_RZ) : GgafObject() {
    _X = prm_X;
    _Y = prm_Y;
    _Z = prm_Z;
    _RX = prm_RX;
    _RY = prm_RY;
    _RZ = prm_RZ;
    _next = nullptr;
}

GgafDxGeoElem::GgafDxGeoElem(GgafDxGeometricActor* prm_pActor) : GgafObject() {
    _X = prm_pActor->_X;
    _Y = prm_pActor->_Y;
    _Z = prm_pActor->_Z;
    _RX = prm_pActor->_RX;
    _RY = prm_pActor->_RY;
    _RZ = prm_pActor->_RZ;
    _next = nullptr;
}

void GgafDxGeoElem::set(coord prm_X, coord prm_Y, coord prm_Z, angle prm_RX, angle prm_RY, angle prm_RZ) {
    _X = prm_X;
    _Y = prm_Y;
    _Z = prm_Z;
    _RX = prm_RX;
    _RY = prm_RY;
    _RZ = prm_RZ;
}

void GgafDxGeoElem::set(coord prm_X, coord prm_Y, coord prm_Z) {
    _X = prm_X;
    _Y = prm_Y;
    _Z = prm_Z;
}

void GgafDxGeoElem::set(GgafDxGeometricActor* prm_pActor) {
    _X = prm_pActor->_X;
    _Y = prm_pActor->_Y;
    _Z = prm_pActor->_Z;
    _RX = prm_pActor->_RX;
    _RY = prm_pActor->_RY;
    _RZ = prm_pActor->_RZ;
}

void GgafDxGeoElem::set(GgafDxGeoElem* prm_pGeoElem) {
    _X = prm_pGeoElem->_X;
    _Y = prm_pGeoElem->_Y;
    _Z = prm_pGeoElem->_Z;
    _RX = prm_pGeoElem->_RX;
    _RY = prm_pGeoElem->_RY;
    _RZ = prm_pGeoElem->_RZ;

}
GgafDxGeoElem::~GgafDxGeoElem() {
    _next = nullptr;
}

