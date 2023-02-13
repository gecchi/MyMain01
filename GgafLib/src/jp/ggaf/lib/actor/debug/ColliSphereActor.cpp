#include "jp/ggaf/lib/actor/debug/ColliSphereActor.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
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

void ColliSphereActor::drawHitarea(GgafDx::CollisionChecker* prm_pChecker) {
    if (prm_pChecker != nullptr &&
        prm_pChecker->_pActiveCollisionArea != nullptr &&
        prm_pChecker->getTargetActor()->canHit() &&
        prm_pChecker->getTargetActor()->isActiveInTheTree()) {
        GgafDx::GeometricActor* pActor = prm_pChecker->getTargetActor();
        GgafDx::CollisionArea* pActiveCollisionArea = prm_pChecker->_pActiveCollisionArea;

        int iAreaNum = pActiveCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            getEffect()->setAlphaMaster(1.0); //シーンに所属しないので固定値の設定が必要
            for (int i = 0; i < iAreaNum; i++) {
                if (pActiveCollisionArea->_papColliPart[i]->_shape_kind == COLLI_SPHERE) {
                    ColliSphere* sphere = (ColliSphere*)pActiveCollisionArea->_papColliPart[i];
                    drawSphere(pActor->_x + sphere->_cx,
                               pActor->_y + sphere->_cy,
                               pActor->_z + sphere->_cz,
                               sphere->_r);
#ifdef MY_DEBUG
                    GgafCore::Caretaker::_num_draw--; //当たり判定表示は表示オブジェクト数にカウントしない
#endif
                }
            }
        }

    }
}

ColliSphereActor::~ColliSphereActor() {
}
