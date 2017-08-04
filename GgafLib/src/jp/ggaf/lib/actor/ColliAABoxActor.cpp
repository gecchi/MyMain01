#include "jp/ggaf/lib/actor/ColliAABoxActor.h"

#include "jp/ggaf/core/GgafGod.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionPart.h"
#include "jp/ggaf/lib/util/ColliAABox.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliAABoxActor* ColliAABoxActor::_pObj = nullptr;

ColliAABoxActor::ColliAABoxActor(const char* prm_name, GgafStatus* prm_pStat) : GgafDxAABActor(prm_name, prm_pStat, nullptr) {
    _class_name = "ColliAABoxActor";
    setAlpha(0.8);
}

ColliAABoxActor* ColliAABoxActor::get() {
    if (ColliAABoxActor::_pObj == nullptr) {
        ColliAABoxActor::_pObj = NEW ColliAABoxActor("HITAREA", nullptr);
    }
    return (ColliAABoxActor::_pObj);
}

void ColliAABoxActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとnullptrかもしれない
    GGAF_DELETE_NULLABLE(ColliAABoxActor::_pObj);
}

void ColliAABoxActor::drawHitarea(CollisionChecker* prm_pColliChecker) {
    if (prm_pColliChecker != nullptr &&
        prm_pColliChecker->_pCollisionArea != nullptr &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {

        GgafDxGeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDxCollisionArea* pCollisionArea = prm_pColliChecker->_pCollisionArea;
        int iAreaNum = pCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            GgafDxCollisionPart** papColliPart = pCollisionArea->_papColliPart;
            for (int i = 0; i < iAreaNum; i++) {
                if (papColliPart[i]->_is_valid_flg && papColliPart[i]->_shape_kind == COLLI_AABOX) {
                    ColliAABox* box = (ColliAABox*)papColliPart[i];
                    //_TRACE_("drawHitarea name="<<prm_pColliChecker->getTargetActor()->getName()<<" index="<<i);

                    drawBox(pActor->_x + box->_x1,
                            pActor->_y + box->_y1,
                            pActor->_z + box->_z1,
                            pActor->_x + box->_x2,
                            pActor->_y + box->_y2,
                            pActor->_z + box->_z2);
#ifdef MY_DEBUG
                    GgafGod::_num_drawing--; //当たり判定表示は表示オブジェクト数にカウントしない
#endif
                }
            }
        }

    }
}

ColliAABoxActor::~ColliAABoxActor() {
}
