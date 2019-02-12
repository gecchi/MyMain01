#include "jp/ggaf/dx/actor/supporter/Checker.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"


using namespace GgafDx;

Checker::Checker(GeometricActor* prm_pActor) : GgafCore::Object(),
_pActor(prm_pActor) {
    _pCollisionArea = nullptr;
//    _need_update_aabb = true;
//    _is_enable = false;
}

void Checker::createCollisionArea(int prm_colli_part_num) {
    if (_pCollisionArea == nullptr) {
        _pCollisionArea = NEW CollisionArea(prm_colli_part_num);
    } else {
        throwCriticalException("既に createCollisionArea されています。");
    }
}

void Checker::enable(int prm_index) {
    CollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
    if (pPart->_is_valid_flg) {
        //元々 enable
    } else {
        pPart->_is_valid_flg = true;
        _pCollisionArea->_need_update_aabb = true;
    }
}
//void Checker::disable(int prm_index) {
//    CollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
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
//virtual void Checker::disable(int prm_index1, int prm_index2) {
//    CollisionPart* pPart1 = _pCollisionArea->_papColliPart[prm_index1];
//    CollisionPart* pPart2 = _pCollisionArea->_papColliPart[prm_index2];
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
//virtual void Checker::disable(int prm_index1, int prm_index2, int prm_index3) {
//    CollisionPart* pPart1 = _pCollisionArea->_papColliPart[prm_index1];
//    CollisionPart* pPart2 = _pCollisionArea->_papColliPart[prm_index2];
//    CollisionPart* pPart3 = _pCollisionArea->_papColliPart[prm_index3];
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


void Checker::disable(int prm_index) {
    CollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
    if (pPart->_is_valid_flg) {
        pPart->_is_valid_flg = false;
        _pCollisionArea->_need_update_aabb = true;
    } else {
         //元々 disable
    }
}

bool Checker::isEnable(int prm_index) {
    return _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg;
}

Checker::~Checker() {
    GGAF_DELETE_NULLABLE(_pCollisionArea);
}
