#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCollisionArea::GgafDxCollisionArea(int prm_colli_part_num) : GgafObject() {
    if (prm_colli_part_num > 0) {
        _colli_part_num = prm_colli_part_num;
        _papColliPart = NEW GgafDxCollisionPart*[_colli_part_num];
        for (int i = 0; i < _colli_part_num; i++) {
            _papColliPart[i] = nullptr;
        }
    } else {
        throwGgafCriticalException("GgafDxCollisionArea::GgafDxCollisionArea 要素数が不正。prm_colli_part_num="<<prm_colli_part_num);
    }
    _AABB_X1=_AABB_Y1=_AABB_Z1=_AABB_X2=_AABB_Y2=_AABB_Z2 = 0;
    _hit_colli_part_index = -1;
}

void GgafDxCollisionArea::updateAABB() {
    _AABB_X1 = _AABB_Y1 = _AABB_Z1 = _AABB_X2 = _AABB_Y2 = _AABB_Z2 = 0;
    GgafDxCollisionPart* pColliPart = nullptr;
    for (int i = 0; i < _colli_part_num; i++) {
        pColliPart = _papColliPart[i];
        if (pColliPart->_is_valid_flg) {
            if (pColliPart->_aab_x1 < _AABB_X1) {
                _AABB_X1 = pColliPart->_aab_x1;
            }
            if (pColliPart->_aab_y1 < _AABB_Y1) {
                _AABB_Y1 = pColliPart->_aab_y1;
            }
            if (pColliPart->_aab_z1 < _AABB_Z1) {
                _AABB_Z1 = pColliPart->_aab_z1;
            }

            if (pColliPart->_aab_x2 > _AABB_X2) {
                _AABB_X2 = pColliPart->_aab_x2;
            }
            if (pColliPart->_aab_y2 > _AABB_Y2) {
                _AABB_Y2 = pColliPart->_aab_y2;
            }
            if (pColliPart->_aab_z2 > _AABB_Z2) {
                _AABB_Z2 = pColliPart->_aab_z2;
            }
        }
    }
}

GgafDxCollisionArea::~GgafDxCollisionArea() {
    for (int i = 0; i < _colli_part_num; i++) {
        DELETE_POSSIBLE_NULL(_papColliPart[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papColliPart);

    TRACE("GgafDxCollisionArea::~GgafDxCollisionArea()");
}
