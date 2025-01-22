#include "jp/ggaf/lib/actor/debug/ColliAABoardRectActor.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAABox.h"

using namespace GgafLib;

ColliAABoardRectActor* ColliAABoardRectActor::_pObj = nullptr;

ColliAABoardRectActor::ColliAABoardRectActor(const char* prm_name) : GgafDx::AABoardRectActor(prm_name) {
    _class_name = "ColliAABoardRectActor";
    setAlpha(0.8);
    useZBufferDrawing(true);    //�`�掞�AZ�o�b�t�@�l�͍l�������
    setZBufferWriteEnable(false);  //���g��Z�o�b�t�@���������݂��Ȃ�
    setCullingDraw(false);
}

ColliAABoardRectActor* ColliAABoardRectActor::get() {
    if (ColliAABoardRectActor::_pObj == nullptr) {
        ColliAABoardRectActor::_pObj = NEW ColliAABoardRectActor("HITAREA");
    }
    return (ColliAABoardRectActor::_pObj);
}

void ColliAABoardRectActor::release() {
    //�����蔻������I�u�W�F�N�g����x���g�p����Ȃ���nullptr��������Ȃ�
    GGAF_DELETE_NULLABLE(ColliAABoardRectActor::_pObj);
}

void ColliAABoardRectActor::drawHitarea(GgafDx::CollisionChecker* prm_pColliChecker) {
    if (prm_pColliChecker != nullptr &&
        prm_pColliChecker->_pCollisionArea != nullptr &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {

        GgafDx::GeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDx::CollisionArea* pActiveCollisionArea = prm_pColliChecker->_pCollisionArea;

        if (pActor->_is_fix_2D) {
            drawRect(pActor->_x + pActiveCollisionArea->_aabb_x1,
                     pActor->_y + pActiveCollisionArea->_aabb_y1,
                     pActor->_x + pActiveCollisionArea->_aabb_x2,
                     pActor->_y + pActiveCollisionArea->_aabb_y2);
        }
    }
}

ColliAABoardRectActor::~ColliAABoardRectActor() {
}
