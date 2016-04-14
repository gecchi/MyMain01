#include "jp/ggaf/lib/actor/ColliAAPyramidActor.h"

#include "jp/ggaf/core/GgafGod.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliAAPyramidActor* ColliAAPyramidActor::_pObj = nullptr;

ColliAAPyramidActor::ColliAAPyramidActor(const char* prm_name, GgafStatus* prm_pStat) : GgafDxAAPyramidActor(prm_name, prm_pStat, nullptr) {
    _class_name = "ColliAAPyramidActor";
    setAlpha(0.8);
}

ColliAAPyramidActor* ColliAAPyramidActor::get() {
    if (ColliAAPyramidActor::_pObj == nullptr) {
        ColliAAPyramidActor::_pObj = NEW ColliAAPyramidActor("HITAREA", nullptr);
    }
    return ColliAAPyramidActor::_pObj;
}

void ColliAAPyramidActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとnullptrかもしれない
    GGAF_DELETE_NULLABLE(ColliAAPyramidActor::_pObj);
}

void ColliAAPyramidActor::drawHitarea(CollisionChecker3D* prm_pColliChecker) {
    if (prm_pColliChecker != nullptr &&
        prm_pColliChecker->_pCollisionArea != nullptr &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {

        GgafDxGeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDxCollisionArea* pCollisionArea = prm_pColliChecker->_pCollisionArea;
        int iAreaNum = pCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            for (int i = 0; i < iAreaNum; i++) {
                if (pCollisionArea->_papColliPart[i]->_is_valid_flg && pCollisionArea->_papColliPart[i]->_shape_kind == COLLI_AAPYRAMID) {
                    ColliAAPyramid* pyramid = (ColliAAPyramid*)pCollisionArea->_papColliPart[i];
                    //_TRACE_("drawHitarea name="<<prm_pColliChecker->getTargetActor()->getName()<<" index="<<i);

                    if (pyramid->_pos_pyramid < 0) {
                        _TRACE_("【警告】ColliAAPyramidActor::drawHitarea BADPOS i="<<i<<" Target="<<pActor->getName()<<" 要調査");
                    } else {
                        drawPyramid(pActor->_x + pyramid->_x1,
                                    pActor->_y + pyramid->_y1,
                                    pActor->_z + pyramid->_z1,
                                    pActor->_x + pyramid->_x2,
                                    pActor->_y + pyramid->_y2,
                                    pActor->_z + pyramid->_z2,
                                    pyramid->_pos_pyramid);
                    }
#ifdef MY_DEBUG
                    GgafGod::_num_drawing--; //当たり判定表示は表示オブジェクト数にカウントしない
#endif
                }
            }
        }

    }
}

ColliAAPyramidActor::~ColliAAPyramidActor() {
}
