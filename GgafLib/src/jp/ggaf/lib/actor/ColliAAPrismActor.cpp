#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliAAPrismActor* ColliAAPrismActor::_pObj = NULL;

ColliAAPrismActor::ColliAAPrismActor(const char* prm_name, GgafStatus* prm_pStat) : GgafDxAAPrismActor(prm_name, prm_pStat, NULL) {
    _class_name = "ColliAAPrismActor";
    setAlpha(0.8);
}

ColliAAPrismActor* ColliAAPrismActor::get() {
    if (ColliAAPrismActor::_pObj == NULL) {
        ColliAAPrismActor::_pObj = NEW ColliAAPrismActor("HITAREA", NULL);
    }
    return ColliAAPrismActor::_pObj;
}

void ColliAAPrismActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとNULLかもしれない
    DELETE_POSSIBLE_NULL(ColliAAPrismActor::_pObj);
}

void ColliAAPrismActor::drawHitarea(CollisionChecker* prm_pColliChecker) {
    if (prm_pColliChecker != NULL &&
        prm_pColliChecker->_pCollisionArea != NULL &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {

        GgafDxGeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDxCollisionArea* pCollisionArea = prm_pColliChecker->_pCollisionArea;
        int iAreaNum = pCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            for (int i = 0; i < iAreaNum; i++) {
                if (pCollisionArea->_papColliPart[i]->_is_valid_flg && pCollisionArea->_papColliPart[i]->_shape_kind == COLLI_AAPRISM) {
                    ColliAAPrism* prism = (ColliAAPrism*)pCollisionArea->_papColliPart[i];
                    //_TRACE_("drawHitarea name="<<prm_pColliChecker->getTargetActor()->getName()<<" index="<<i);

                    if (prism->_pos_prism == 0) {
                        _TRACE_("【警告】ColliAAPrismActor::drawHitarea BADPOS i="<<i<<" Target="<<pActor->getName()<<" 要調査");
                    } else {
                        drawPrism(pActor->_X + prism->_x1,
                                pActor->_Y + prism->_y1,
                                pActor->_Z + prism->_z1,
                                pActor->_X + prism->_x2,
                                pActor->_Y + prism->_y2,
                                pActor->_Z + prism->_z2,
                                prism->_pos_prism); //TODO:prism->_pos_prism が 0 で pos2r[pos_prism]._ry がおかしな値で落ちる
                    }
                    GgafGod::_num_actor_drawing--; //当たり判定表示は表示オブジェクト数にカウントしない
                }
            }
        }

    }
}

ColliAAPrismActor::~ColliAAPrismActor() {
}
