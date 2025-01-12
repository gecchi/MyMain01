#include "jp/ggaf/dx/util/CollisionChecker.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"

using namespace GgafDx;

CollisionChecker::CollisionChecker(GeometricActor* prm_pColliActor, kind_t prm_kind) : GgafCore::Checker(prm_pColliActor, prm_kind),
_pColliActor(prm_pColliActor) {
    _pCollisionArea = nullptr;
}

void CollisionChecker::addCollisionArea(int prm_colli_part_num) {
    CollisionArea* pNewCollisionArea = NEW CollisionArea(prm_colli_part_num);
    _pCollisionArea = pNewCollisionArea;
    _pCollisionArea->_need_update_aabb = true;
    _pColliActor->setHitAble(true);
    //ストック
    _vecCollisionArea.push_back(pNewCollisionArea);
}

void CollisionChecker::changeCollisionArea(int prm_index) {
#ifdef MY_DEBUG
    if (_vecCollisionArea.size() < prm_index+1) {
        throwCriticalException("要素数が不正。prm_index="<<prm_index);
    }
#endif
    _pCollisionArea = _vecCollisionArea.at(prm_index);
}

bool CollisionChecker::processHitChkLogic(GgafCore::Checker* prm_pOppHitChecker) {
    if (_pActor->_can_hit_flg && prm_pOppHitChecker->_pActor->_can_hit_flg) {
        //_can_hit_flg のチェックは八分木登録前にもチェックしてるが
        //ここでももう一度チェックするほうがより良い。
        //なぜならば、無駄なヒットチェックを行わないため、onHit(GgafCore::Actor*) 処理中で setHitAble(false) が行われ、
        //２重ヒットチェック防止を行っているかもしれないから。
        return isHit((CollisionChecker*)prm_pOppHitChecker);
    } else {
        return false;
    }
}

CollisionChecker::~CollisionChecker() {
    for (int i = 0; i < _vecCollisionArea.size(); i++) {
        CollisionArea* pCollisionArea = _vecCollisionArea.at(i);
        GGAF_DELETE(pCollisionArea);
    }
}
