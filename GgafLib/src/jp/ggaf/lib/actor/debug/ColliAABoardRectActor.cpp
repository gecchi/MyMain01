#include "jp/ggaf/lib/actor/debug/ColliAABoardRectActor.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAABox.h"



using namespace GgafLib;

ColliAABoardRectActor* ColliAABoardRectActor::_pObj = nullptr;

ColliAABoardRectActor::ColliAABoardRectActor(const char* prm_name) : GgafDx::AABoardRectActor(prm_name, nullptr) {
    _class_name = "ColliAABoardRectActor";
    setAlpha(0.7);
}

ColliAABoardRectActor* ColliAABoardRectActor::get() {
    if (ColliAABoardRectActor::_pObj == nullptr) {
        ColliAABoardRectActor::_pObj = NEW ColliAABoardRectActor("HITAREA");
    }
    return (ColliAABoardRectActor::_pObj);
}

void ColliAABoardRectActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとnullptrかもしれない
    GGAF_DELETE_NULLABLE(ColliAABoardRectActor::_pObj);
}

void ColliAABoardRectActor::drawHitarea(GgafDx::Checker* prm_pChecker) {
    if (prm_pChecker != nullptr &&
        prm_pChecker->_pCollisionArea != nullptr &&
        prm_pChecker->getTargetActor()->canHit() &&
        prm_pChecker->getTargetActor()->isActiveInTheTree()) {

        GgafDx::GeometricActor* pActor = prm_pChecker->getTargetActor();
        GgafDx::CollisionArea* pCollisionArea = prm_pChecker->_pCollisionArea;

        if (pActor->_is_fix_2D) {
            drawRect(pActor->_x + pCollisionArea->_aabb_x1,
                     pActor->_y + pCollisionArea->_aabb_y1,
                     pActor->_x + pCollisionArea->_aabb_x2,
                     pActor->_y + pCollisionArea->_aabb_y2);
        }
    }
}

ColliAABoardRectActor::~ColliAABoardRectActor() {
}
