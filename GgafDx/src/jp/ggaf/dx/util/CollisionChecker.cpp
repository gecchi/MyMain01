#include "jp/ggaf/dx/util/CollisionChecker.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"

using namespace GgafDx;

CollisionChecker::CollisionChecker(GeometricActor* prm_pActor) : GgafCore::Object(),
_pActor(prm_pActor) {
    _pActiveCollisionArea = nullptr;
}

void CollisionChecker::addCollisionArea(int prm_colli_part_num) {
    CollisionArea* pNewCollisionArea = NEW CollisionArea(prm_colli_part_num);
    if (_pActiveCollisionArea == nullptr) {
        //初回
        _pActiveCollisionArea = pNewCollisionArea;
        _pActor->setHitAble(true);
    } else {
        //_TRACE_("CollisionChecker::addCollisionArea() ["<<getTargetActor()->getName()<<"] CollisionArea を追加しました");
    }
    //ストック
    _vecCollisionArea.push_back(pNewCollisionArea);
}

void CollisionChecker::changeActiveCollisionArea(int prm_index) {
#ifdef MY_DEBUG
    if (_vecCollisionArea.size() < prm_index+1) {
        throwCriticalException("要素数が不正。prm_index="<<prm_index);
    }
#endif
    _pActiveCollisionArea = _vecCollisionArea.at(prm_index);
}

void CollisionChecker::enable(int prm_index) {
    CollisionPart* pPart = _pActiveCollisionArea->_papColliPart[prm_index];
    if (pPart->_is_valid_flg) {
        //元々 enable
    } else {
        pPart->_is_valid_flg = true;
        _pActiveCollisionArea->_need_update_aabb = true;
    }
}

void CollisionChecker::disable(int prm_index) {
    CollisionPart* pPart = _pActiveCollisionArea->_papColliPart[prm_index];
    if (pPart->_is_valid_flg) {
        pPart->_is_valid_flg = false;
        _pActiveCollisionArea->_need_update_aabb = true;
    } else {
         //元々 disable
    }
}

bool CollisionChecker::isEnable(int prm_index) {
    return _pActiveCollisionArea->_papColliPart[prm_index]->_is_valid_flg;
}

CollisionChecker::~CollisionChecker() {
    for (int i = 0; i < _vecCollisionArea.size(); i++) {
        CollisionArea* pCollisionArea = _vecCollisionArea.at(i);
        GGAF_DELETE(pCollisionArea);
    }
}
