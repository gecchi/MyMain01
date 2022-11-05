#include "jp/ggaf/dx/util/CollisionChecker.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"

using namespace GgafDx;

CollisionChecker::CollisionChecker(GeometricActor* prm_pActor) : GgafCore::Object(),
_pActor(prm_pActor) {
    _pCollisionArea = nullptr;
}

void CollisionChecker::createCollisionArea(int prm_colli_part_num) {
    if (_pCollisionArea == nullptr) {
        _pCollisionArea = NEW CollisionArea(prm_colli_part_num);
    } else {
        throwCriticalException("Šù‚É createCollisionArea ‚³‚ê‚Ä‚¢‚Ü‚·B");
    }
}

void CollisionChecker::enable(int prm_index) {
    CollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
    if (pPart->_is_valid_flg) {
        //Œ³X enable
    } else {
        pPart->_is_valid_flg = true;
        _pCollisionArea->_need_update_aabb = true;
    }
}

void CollisionChecker::disable(int prm_index) {
    CollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
    if (pPart->_is_valid_flg) {
        pPart->_is_valid_flg = false;
        _pCollisionArea->_need_update_aabb = true;
    } else {
         //Œ³X disable
    }
}

bool CollisionChecker::isEnable(int prm_index) {
    return _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg;
}

CollisionChecker::~CollisionChecker() {
    GGAF_DELETE_NULLABLE(_pCollisionArea);
}
