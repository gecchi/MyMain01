#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliAABActor* ColliAABActor::_pObj = NULL;

ColliAABActor::ColliAABActor(const char* prm_name, GgafStatus* prm_pStat) : GgafDxAABActor(prm_name, prm_pStat, NULL) {
    _class_name = "ColliAABActor";
    setAlpha(0.8);
}

ColliAABActor* ColliAABActor::get() {
    if (ColliAABActor::_pObj == NULL) {
        ColliAABActor::_pObj = NEW ColliAABActor("HITAREA", NULL);
    }
    return (ColliAABActor::_pObj);
}

void ColliAABActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとNULLかもしれない
    DELETE_POSSIBLE_NULL(ColliAABActor::_pObj);
}

void ColliAABActor::drawHitarea(CollisionChecker* prm_pColliChecker) {
    if (prm_pColliChecker != NULL &&
        prm_pColliChecker->_pCollisionArea != NULL &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {

        GgafDxGeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDxCollisionArea* pCollisionArea = prm_pColliChecker->_pCollisionArea;
        int iAreaNum = pCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            GgafDxCollisionPart** papColliPart = pCollisionArea->_papColliPart;
            for (int i = 0; i < iAreaNum; i++) {
                if (papColliPart[i]->_is_valid_flg && papColliPart[i]->_shape_kind == COLLI_AAB) {
                    ColliAAB* box = (ColliAAB*)papColliPart[i];
                    //_TRACE_("drawHitarea name="<<prm_pColliChecker->getTargetActor()->getName()<<" index="<<i);

                    drawBox(pActor->_X + box->_x1,
                            pActor->_Y + box->_y1,
                            pActor->_Z + box->_z1,
                            pActor->_X + box->_x2,
                            pActor->_Y + box->_y2,
                            pActor->_Z + box->_z2);
                    GgafGod::_num_actor_drawing--; //当たり判定表示は表示オブジェクト数にカウントしない
                }
            }
        }

    }
}

ColliAABActor::~ColliAABActor() {
}
