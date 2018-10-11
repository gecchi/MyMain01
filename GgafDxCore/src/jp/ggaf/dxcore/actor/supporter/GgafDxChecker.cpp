#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxChecker::GgafDxChecker(GgafDxGeometricActor* prm_pActor) : GgafObject(),
_pActor(prm_pActor) {
    _pCollisionArea = nullptr;
    _need_update_aabb = true;
//    _is_enable = false;
}

void GgafDxChecker::createCollisionArea(int prm_colli_part_num) {
    if (_pCollisionArea == nullptr) {
        _pCollisionArea = NEW GgafDxCollisionArea(prm_colli_part_num);
    } else {
        throwGgafCriticalException("既に createCollisionArea されています。");
    }
}

void GgafDxChecker::enable(int prm_index) {
    GgafDxCollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
    if (pPart->_is_valid_flg) {
        //元々 enable
    } else {
        pPart->_is_valid_flg = true;
        _need_update_aabb = true;
    }
}
//void GgafDxChecker::disable(int prm_index) {
//    GgafDxCollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
//    if (pPart->_is_valid_flg) {
//        pPart->_is_valid_flg = false;
//        _need_update_aabb = true;
//        _is_enable = false;
//        int colli_part_num = _pCollisionArea->_colli_part_num;
//        for (int i = 0; i < colli_part_num; i++) {
//            if (_pCollisionArea->_papColliPart[i]->_is_valid_flg) {
//                _is_enable = true;
//                break;
//            }
//        }
//    } else {
//         //元々 disable
//    }
//}
//virtual void GgafDxChecker::disable(int prm_index1, int prm_index2) {
//    GgafDxCollisionPart* pPart1 = _pCollisionArea->_papColliPart[prm_index1];
//    GgafDxCollisionPart* pPart2 = _pCollisionArea->_papColliPart[prm_index2];
//    if (pPart1->_is_valid_flg) {
//        pPart1->_is_valid_flg = false;
//        _need_update_aabb = true;
//    }
//    if (pPart2->_is_valid_flg) {
//        pPart2->_is_valid_flg = false;
//        _need_update_aabb = true;
//    }
//    if (_need_update_aabb) {
//        _is_enable = false;
//        int colli_part_num = _pCollisionArea->_colli_part_num;
//        for (int i = 0; i < colli_part_num; i++) {
//            if (_pCollisionArea->_papColliPart[i]->_is_valid_flg) {
//                _is_enable = true;
//                break;
//            }
//        }
//    } else {
//         //元々 disable
//    }
//}
//
//virtual void GgafDxChecker::disable(int prm_index1, int prm_index2, int prm_index3) {
//    GgafDxCollisionPart* pPart1 = _pCollisionArea->_papColliPart[prm_index1];
//    GgafDxCollisionPart* pPart2 = _pCollisionArea->_papColliPart[prm_index2];
//    GgafDxCollisionPart* pPart3 = _pCollisionArea->_papColliPart[prm_index3];
//    if (pPart1->_is_valid_flg) {
//        pPart1->_is_valid_flg = false;
//        _need_update_aabb = true;
//    }
//    if (pPart2->_is_valid_flg) {
//        pPart2->_is_valid_flg = false;
//        _need_update_aabb = true;
//    }
//    if (pPart3->_is_valid_flg) {
//        pPart3->_is_valid_flg = false;
//        _need_update_aabb = true;
//    }
//    if (_need_update_aabb) {
//        _is_enable = false;
//        int colli_part_num = _pCollisionArea->_colli_part_num;
//        for (int i = 0; i < colli_part_num; i++) {
//            if (_pCollisionArea->_papColliPart[i]->_is_valid_flg) {
//                _is_enable = true;
//                break;
//            }
//        }
//    } else {
//         //元々 disable
//    }
//}


void GgafDxChecker::disable(int prm_index) {
    GgafDxCollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
    if (pPart->_is_valid_flg) {
        pPart->_is_valid_flg = false;
        _need_update_aabb = true;
    } else {
         //元々 disable
    }
}

bool GgafDxChecker::isEnable(int prm_index) {
    return _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg;
}

GgafDxChecker::~GgafDxChecker() {
    GGAF_DELETE_NULLABLE(_pCollisionArea);
}
