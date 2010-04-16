#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9CollisionArea::GgafDx9CollisionArea(int prm_nColliPart) : GgafObject() {
    if (prm_nColliPart > 0) {
        _nColliPart = prm_nColliPart;
        _papColliPart = NEW GgafDx9CollisionPart*[_nColliPart];
        for (int i = 0; i < _nColliPart; i++) {
            _papColliPart[i] = NULL;
        }
    } else {
        throwGgafCriticalException("GgafDx9CollisionArea::GgafDx9CollisionArea 要素数が不正。prm_nColliPart="<<prm_nColliPart);
    }
    _AABB_X1=_AABB_Y1=_AABB_Z1=_AABB_X2=_AABB_Y2=_AABB_Z2 = 0;
}

void GgafDx9CollisionArea::updateAABB() {
    _AABB_X1 = _AABB_Y1 = _AABB_Z1 = _AABB_X2 = _AABB_Y2 = _AABB_Z2 = 0;
    GgafDx9CollisionPart* pColliPart = NULL;
    for (int i = 0; i < _nColliPart; i++) {
        pColliPart = _papColliPart[i];
        if (pColliPart->_is_valid_flg) {
            if (pColliPart->_aabb_x1 < _AABB_X1) {
                _AABB_X1 = pColliPart->_aabb_x1;
            }
            if (pColliPart->_aabb_y1 < _AABB_Y1) {
                _AABB_Y1 = pColliPart->_aabb_y1;
            }
            if (pColliPart->_aabb_z1 < _AABB_Z1) {
                _AABB_Z1 = pColliPart->_aabb_z1;
            }

            if (pColliPart->_aabb_x2 > _AABB_X2) {
                _AABB_X2 = pColliPart->_aabb_x2;
            }
            if (pColliPart->_aabb_y2 > _AABB_Y2) {
                _AABB_Y2 = pColliPart->_aabb_y2;
            }
            if (pColliPart->_aabb_z2 > _AABB_Z2) {
                _AABB_Z2 = pColliPart->_aabb_z2;
            }
        }
    }
}

GgafDx9CollisionArea::~GgafDx9CollisionArea() {
    for (int i = 0; i < _nColliPart; i++) {
        DELETE_POSSIBLE_NULL(_papColliPart[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papColliPart);

    TRACE("GgafDx9CollisionArea::~GgafDx9CollisionArea()");
}
