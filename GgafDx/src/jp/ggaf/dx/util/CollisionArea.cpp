#include "jp/ggaf/dx/util/CollisionArea.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/dx/util/CollisionPart.h"


using namespace GgafDx;

CollisionArea::CollisionArea(int prm_colli_part_num) : GgafCore::Object() {
    if (prm_colli_part_num > 0) {
        _colli_part_num = prm_colli_part_num;

        _papColliPart = NEW CollisionPart*[_colli_part_num];
        for (int i = 0; i < _colli_part_num; i++) {
            _papColliPart[i] = nullptr;
        }
    } else {
        throwCriticalException("CollisionArea::CollisionArea() ‚Ç‚È‚¢‚â‚Ë‚ñBprm_colli_part_num="<<prm_colli_part_num);
    }
    _aabb_x1=_aabb_y1=_aabb_z1=_aabb_x2=_aabb_y2=_aabb_z2 = 0;

    _hit_colli_part_index = -1;
    _need_update_aabb = true;
    _rotate_part_num = 0;
}

void CollisionArea::updateAABB(angle prm_rx, angle prm_ry, angle prm_rz) {
    if (_need_update_aabb || _rotate_part_num > 0) {
        CollisionPart** papBegin = _papColliPart;
        CollisionPart** papEnd = papBegin + _colli_part_num;
        for (CollisionPart** papPart = papBegin; papPart < papEnd; ++papPart) {
            CollisionPart* pPart = (*papPart);
            if (pPart->_rot) {
                pPart->rotateRxRzRy(prm_rx, prm_ry, prm_rz);
            }
            if (papPart == papBegin) {
                _aabb_x1 = pPart->_x1;
                _aabb_y1 = pPart->_y1;
                _aabb_z1 = pPart->_z1;
                _aabb_x2 = pPart->_x2;
                _aabb_y2 = pPart->_y2;
                _aabb_z2 = pPart->_z2;
            } else {
                if (pPart->_x1 < _aabb_x1) {
                    _aabb_x1 = pPart->_x1;
                }
                if (pPart->_y1 < _aabb_y1) {
                    _aabb_y1 = pPart->_y1;
                }
                if (pPart->_z1 < _aabb_z1) {
                    _aabb_z1 = pPart->_z1;
                }

                if (pPart->_x2 > _aabb_x2) {
                    _aabb_x2 = pPart->_x2;
                }
                if (pPart->_y2 > _aabb_y2) {
                    _aabb_y2 = pPart->_y2;
                }
                if (pPart->_z2 > _aabb_z2) {
                    _aabb_z2 = pPart->_z2;
                }
            }
        }
    }
    _need_update_aabb = false;
}

CollisionArea::~CollisionArea() {
    for (int i = 0; i < _colli_part_num; i++) {
        GGAF_DELETE_NULLABLE(_papColliPart[i]);
    }
    GGAF_DELETEARR(_papColliPart);
}
