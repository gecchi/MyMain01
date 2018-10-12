#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"

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
        throwGgafCriticalException("—v‘f”‚ª•s³Bprm_colli_part_num="<<prm_colli_part_num);
    }
    _aabb_x1=_aabb_y1=_aabb_z1=_aabb_x2=_aabb_y2=_aabb_z2 = 0;

    _hit_colli_part_index = -1;
    _need_update_aabb = true;
    _rotate_part_num = 0;
}

void GgafDxCollisionArea::updateAABB(angle prm_rx, angle prm_ry, angle prm_rz) {
    if (_need_update_aabb || _rotate_part_num > 0) {
        GgafDxCollisionPart* pColliPart0 = _papColliPart[0];
    #ifdef MY_DEBUG
        if (pColliPart0) {

        } else {
            throwGgafCriticalException("_papColliPart[0]=nullptr‚Å‚·");
        }
    #endif
        if (pColliPart0->_is_valid_flg) {
            if (pColliPart0->_rot) {
                pColliPart0->rotateRxRzRy(prm_rx, prm_ry, prm_rz);
            }
            _aabb_x1 = pColliPart0->_x1;
            _aabb_y1 = pColliPart0->_y1;
            _aabb_z1 = pColliPart0->_z1;
            _aabb_x2 = pColliPart0->_x2;
            _aabb_y2 = pColliPart0->_y2;
            _aabb_z2 = pColliPart0->_z2;
        } else {
            _aabb_x1=_aabb_y1=_aabb_z1=_aabb_x2=_aabb_y2=_aabb_z2 = 0;
        }
        if (_colli_part_num == 1) {
            return;
        } else {
            for (int i = 1; i < _colli_part_num; i++) {
                GgafDxCollisionPart* pColliPart = _papColliPart[i];
                if (pColliPart->_is_valid_flg) {
                    if (pColliPart->_rot) {
                        pColliPart->rotateRxRzRy(prm_rx, prm_ry, prm_rz);
                    }
                    if (pColliPart->_x1 < _aabb_x1) {
                        _aabb_x1 = pColliPart->_x1;
                    }
                    if (pColliPart->_y1 < _aabb_y1) {
                        _aabb_y1 = pColliPart->_y1;
                    }
                    if (pColliPart->_z1 < _aabb_z1) {
                        _aabb_z1 = pColliPart->_z1;
                    }

                    if (pColliPart->_x2 > _aabb_x2) {
                        _aabb_x2 = pColliPart->_x2;
                    }
                    if (pColliPart->_y2 > _aabb_y2) {
                        _aabb_y2 = pColliPart->_y2;
                    }
                    if (pColliPart->_z2 > _aabb_z2) {
                        _aabb_z2 = pColliPart->_z2;
                    }
                }
            }
        }
    }
    _need_update_aabb = false;
}

GgafDxCollisionArea::~GgafDxCollisionArea() {
    for (int i = 0; i < _colli_part_num; i++) {
        GGAF_DELETE_NULLABLE(_papColliPart[i]);
    }
    GGAF_DELETEARR(_papColliPart);
}
