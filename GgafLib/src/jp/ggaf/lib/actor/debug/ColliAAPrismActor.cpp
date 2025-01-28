#include "jp/ggaf/lib/actor/debug/ColliAAPrismActor.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"



using namespace GgafLib;

ColliAAPrismActor* ColliAAPrismActor::_pObj = nullptr;

ColliAAPrismActor::ColliAAPrismActor(const char* prm_name) : GgafDx::AAPrismActor(prm_name) {
    _class_name = "ColliAAPrismActor";
    setAlpha(0.8);
    useZBufferDrawing(false);      //描画時、Zバッファ値は考慮しない
    setZBufferWriteEnable(false);  //自身のZバッファを書き込みしない
    setCullingDraw(false);
}

ColliAAPrismActor* ColliAAPrismActor::get() {
    if (ColliAAPrismActor::_pObj == nullptr) {
        ColliAAPrismActor::_pObj = NEW ColliAAPrismActor("HITAREA");
    }
    return ColliAAPrismActor::_pObj;
}

void ColliAAPrismActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとnullptrかもしれない
    GGAF_DELETE_NULLABLE(ColliAAPrismActor::_pObj);
}

void ColliAAPrismActor::drawHitarea(GgafDx::CollisionChecker* prm_pColliChecker) {
    if (prm_pColliChecker != nullptr &&
        prm_pColliChecker->_pCollisionArea != nullptr &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {

        GgafDx::GeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDx::CollisionArea* pActiveCollisionArea = prm_pColliChecker->_pCollisionArea;
        int iAreaNum = pActiveCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            getEffect()->setAlphaMaster(1.0); //シーンに所属しないので固定値の設定が必要
            for (int i = 0; i < iAreaNum; i++) {
                if (pActiveCollisionArea->_papColliPart[i]->_shape_kind == COLLI_AAPRISM) {
                    ColliAAPrism* prism = (ColliAAPrism*)pActiveCollisionArea->_papColliPart[i];
                    if (prism->_pos_info == 0) {
                        _TRACE_("【警告】ColliAAPrismActor::drawHitarea BADPOS i="<<i<<" Target="<<pActor->getName()<<" 要調査");
                    } else {
                        drawPrism(pActor->_x + prism->_x1,
                                  pActor->_y + prism->_y1,
                                  pActor->_z + prism->_z1,
                                  pActor->_x + prism->_x2,
                                  pActor->_y + prism->_y2,
                                  pActor->_z + prism->_z2,
                                  prism->_pos_info); //TODO:prism->_pos_info が 0 で pos2r[pos_info]._ry がおかしな値で落ちる
                    }
#ifdef MY_DEBUG
                    GgafCore::Caretaker::_num_draw--; //当たり判定表示は表示オブジェクト数にカウントしない
#endif
                }
            }
        }

    }
}

ColliAAPrismActor::~ColliAAPrismActor() {
}
