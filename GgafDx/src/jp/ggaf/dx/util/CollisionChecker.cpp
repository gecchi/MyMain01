#include "jp/ggaf/dx/util/CollisionChecker.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"

using namespace GgafDx;

CollisionChecker::CollisionChecker(GeometricActor* prm_pColliActor) : GgafCore::Checker(prm_pColliActor),
_pColliActor(prm_pColliActor) {
    _pCollisionArea = nullptr;
}

void CollisionChecker::addCollisionArea(int prm_colli_part_num) {
    _kind = _pActor->getDefaultKind(); //TODO:ここでいいのか

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

bool CollisionChecker::processHitChkLogic(GgafCore::Checker* prm_pOtherChecker) {
    if (_pActor->_can_hit_flg && prm_pOtherChecker->_pActor->_can_hit_flg) {
        //&& prm_pOtherActor->instanceOf(Obj_GgafDx_GeometricActor)) { 当たり判定があるのでGeometricActor以上と判断
        //_can_hit_flg && prm_pOtherActor->_can_hit_flg のチェックは八分木登録前にもチェックしてるが
        //ここでももう一度チェックするほうがより良い。
        //なぜならば、無駄なヒットチェックを行わないため、onHit(GgafCore::Actor*) 処理中で setHitAble(false) が行われ、
        //２重ヒットチェック防止を行っているかもしれないから。
        return isHit((CollisionChecker*)prm_pOtherChecker);
    } else {
        return false;
    }
}

//void CollisionChecker::enable(int prm_index) {
//    CollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
//    if (pPart->_is_valid_flg) {
//        //元々 enable
//    } else {
//        pPart->_is_valid_flg = true;
//        _pCollisionArea->_need_update_aabb = true;
//    }
//}
//
//void CollisionChecker::disable(int prm_index) {
//    CollisionPart* pPart = _pCollisionArea->_papColliPart[prm_index];
//    if (pPart->_is_valid_flg) {
//        pPart->_is_valid_flg = false;
//        _pCollisionArea->_need_update_aabb = true;
//    } else {
//         //元々 disable
//    }
//}
//
//bool CollisionChecker::isEnable(int prm_index) {
//    return _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg;
//}

CollisionChecker::~CollisionChecker() {
    for (int i = 0; i < _vecCollisionArea.size(); i++) {
        CollisionArea* pCollisionArea = _vecCollisionArea.at(i);
        GGAF_DELETE(pCollisionArea);
    }
}
