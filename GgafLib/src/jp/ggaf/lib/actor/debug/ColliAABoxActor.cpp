#include "jp/ggaf/lib/actor/debug/ColliAABoxActor.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAABox.h"

using namespace GgafLib;

ColliAABoxActor* ColliAABoxActor::_pObj = nullptr;

ColliAABoxActor::ColliAABoxActor(const char* prm_name) : GgafDx::AABActor(prm_name) {
    _class_name = "ColliAABoxActor";
    setAlpha(0.8);
    useZBufferDrawing(true);    //描画時、Zバッファ値は考慮される
    setZBufferWriteEnable(false);  //自身のZバッファを書き込みしない
    setCullingDraw(false);
}

ColliAABoxActor* ColliAABoxActor::get() {
    if (ColliAABoxActor::_pObj == nullptr) {
        ColliAABoxActor::_pObj = NEW ColliAABoxActor("HITAREA");
    }
    return (ColliAABoxActor::_pObj);
}

void ColliAABoxActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとnullptrかもしれない
    GGAF_DELETE_NULLABLE(ColliAABoxActor::_pObj);
}

void ColliAABoxActor::drawHitarea(GgafDx::CollisionChecker* prm_pColliChecker) {
    if (prm_pColliChecker != nullptr &&
        prm_pColliChecker->_pCollisionArea != nullptr &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {

        GgafDx::GeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDx::CollisionArea* pActiveCollisionArea = prm_pColliChecker->_pCollisionArea;
        int iAreaNum = pActiveCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            getEffect()->setAlphaMaster(1.0); //シーンに所属しないので固定値の設定が必要
            GgafDx::CollisionPart** papColliPart = pActiveCollisionArea->_papColliPart;
            for (int i = 0; i < iAreaNum; i++) {
                if (papColliPart[i]->_shape_kind == COLLI_AABOX) {
                    ColliAABox* box = (ColliAABox*)papColliPart[i];
                    drawBox(pActor->_x + box->_x1,
                            pActor->_y + box->_y1,
                            pActor->_z + box->_z1,
                            pActor->_x + box->_x2,
                            pActor->_y + box->_y2,
                            pActor->_z + box->_z2);
#ifdef MY_DEBUG
                    GgafCore::Caretaker::_num_draw--; //当たり判定表示は表示オブジェクト数にカウントしない
#endif
                }
            }
        }

    }
}

ColliAABoxActor::~ColliAABoxActor() {
}
