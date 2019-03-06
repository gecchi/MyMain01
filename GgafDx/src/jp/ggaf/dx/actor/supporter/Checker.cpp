#include "jp/ggaf/dx/actor/supporter/Checker.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"

using namespace GgafDx;

Checker::Checker(GeometricActor* prm_pActor) : GgafCore::Object(),
_pActor(prm_pActor) {
    _pCollisionArea = nullptr;
}

void Checker::createCollisionArea(int prm_colli_part_num) {
    if (_pCollisionArea == nullptr) {
        _pCollisionArea = NEW CollisionArea(prm_colli_part_num);
    } else {
        throwCriticalException("���� createCollisionArea ����Ă��܂��B");
    }
}

void Checker::enable(int prm_index) {
    CollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
    if (pPart->_is_valid_flg) {
        //���X enable
    } else {
        pPart->_is_valid_flg = true;
        _pCollisionArea->_need_update_aabb = true;
    }
}

void Checker::disable(int prm_index) {
    CollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
    if (pPart->_is_valid_flg) {
        pPart->_is_valid_flg = false;
        _pCollisionArea->_need_update_aabb = true;
    } else {
         //���X disable
    }
}

bool Checker::isEnable(int prm_index) {
    return _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg;
}

Checker::~Checker() {
    GGAF_DELETE_NULLABLE(_pCollisionArea);
}
