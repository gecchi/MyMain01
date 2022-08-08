#include "jp/ggaf/lib/actor/ColliSphereActor.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/ColliSphere.h"



using namespace GgafLib;

ColliSphereActor* ColliSphereActor::_pObj = nullptr;

ColliSphereActor::ColliSphereActor(const char* prm_name) : GgafDx::SphereActor(prm_name, nullptr) {
    _class_name = "ColliSphereActor";
    setAlpha(0.8);
}

ColliSphereActor* ColliSphereActor::get() {
    if (ColliSphereActor::_pObj == nullptr) {
        ColliSphereActor::_pObj = NEW ColliSphereActor("HITAREA");
    }
    return ColliSphereActor::_pObj;
}

void ColliSphereActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとnullptrかもしれない
    GGAF_DELETE_NULLABLE(ColliSphereActor::_pObj);
}

void ColliSphereActor::drawHitarea(CollisionChecker* prm_pColliChecker) {
    if (prm_pColliChecker != nullptr &&
        prm_pColliChecker->_pCollisionArea != nullptr &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {
        GgafDx::GeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDx::CollisionArea* pCollisionArea = prm_pColliChecker->_pCollisionArea;

        int iAreaNum = pCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            getEffect()->setAlphaMaster(1.0); //シーンに所属しないので固定値の設定が必要
            for (int i = 0; i < iAreaNum; i++) {
                if (pCollisionArea->_papColliPart[i]->_is_valid_flg && pCollisionArea->_papColliPart[i]->_shape_kind == COLLI_SPHERE) {
                    ColliSphere* sphere = (ColliSphere*)pCollisionArea->_papColliPart[i];
                    drawSphere(pActor->_x + sphere->_cx,
                               pActor->_y + sphere->_cy,
                               pActor->_z + sphere->_cz,
                               sphere->_r);
#ifdef MY_DEBUG
                    GgafCore::Caretaker::_num_drawing--; //当たり判定表示は表示オブジェクト数にカウントしない
#endif
                }
            }
        }

    }
}

ColliSphereActor::~ColliSphereActor() {
}
