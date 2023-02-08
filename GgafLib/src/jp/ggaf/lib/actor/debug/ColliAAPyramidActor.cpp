#include "jp/ggaf/lib/actor/debug/ColliAAPyramidActor.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/effect/Effect.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"



using namespace GgafLib;

ColliAAPyramidActor* ColliAAPyramidActor::_pObj = nullptr;

ColliAAPyramidActor::ColliAAPyramidActor(const char* prm_name) : GgafDx::AAPyramidActor(prm_name, nullptr) {
    _class_name = "ColliAAPyramidActor";
    setAlpha(0.98);
}

ColliAAPyramidActor* ColliAAPyramidActor::get() {
    if (ColliAAPyramidActor::_pObj == nullptr) {
        ColliAAPyramidActor::_pObj = NEW ColliAAPyramidActor("HITAREA");
    }
    return ColliAAPyramidActor::_pObj;
}

void ColliAAPyramidActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとnullptrかもしれない
    GGAF_DELETE_NULLABLE(ColliAAPyramidActor::_pObj);
}

void ColliAAPyramidActor::drawHitarea(GgafDx::CollisionChecker* prm_pChecker) {
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
                if (pActiveCollisionArea->_papColliPart[i]->_is_valid_flg && pActiveCollisionArea->_papColliPart[i]->_shape_kind == COLLI_AAPYRAMID) {
                    ColliAAPyramid* pyramid = (ColliAAPyramid*)pActiveCollisionArea->_papColliPart[i];
                    if (pyramid->_pos_info < 0) {
                        _TRACE_("【警告】ColliAAPyramidActor::drawHitarea BADPOS i="<<i<<" Target="<<pActor->getName()<<" 要調査");
                    } else {
                        drawPyramid(pActor->_x + pyramid->_x1,
                                    pActor->_y + pyramid->_y1,
                                    pActor->_z + pyramid->_z1,
                                    pActor->_x + pyramid->_x2,
                                    pActor->_y + pyramid->_y2,
                                    pActor->_z + pyramid->_z2,
                                    pyramid->_pos_info);
                    }
#ifdef MY_DEBUG
                    GgafCore::Caretaker::_num_draw--; //当たり判定表示は表示オブジェクト数にカウントしない
#endif
                }
            }
        }

    }
}

ColliAAPyramidActor::~ColliAAPyramidActor() {
}
