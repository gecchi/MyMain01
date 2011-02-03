#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ColliAAPrismActor* ColliAAPrismActor::_pObj = NULL;

ColliAAPrismActor::ColliAAPrismActor(const char* prm_name) : GgafDx9AAPrismActor(prm_name, NULL) {
    _class_name = "ColliAAPrismActor";
    setAlpha(0.8);
}

ColliAAPrismActor* ColliAAPrismActor::get() {
    if (ColliAAPrismActor::_pObj == NULL) {
        ColliAAPrismActor::_pObj = NEW ColliAAPrismActor("HITAREA");
    }
    return ColliAAPrismActor::_pObj;
}

void ColliAAPrismActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとNULLかもしれない
    DELETE_POSSIBLE_NULL(ColliAAPrismActor::_pObj);
}

void ColliAAPrismActor::drawHitarea(CollisionChecker* prm_pCollisionChecker) {
    if (prm_pCollisionChecker != NULL &&
        prm_pCollisionChecker->_pCollisionArea != NULL &&
        prm_pCollisionChecker->getTargetActor()->canHit() &&
        prm_pCollisionChecker->getTargetActor()->isActiveActor()) {

        GgafDx9GeometricActor* pActor = prm_pCollisionChecker->getTargetActor();
        GgafDx9CollisionArea* pCollisionArea = prm_pCollisionChecker->_pCollisionArea;
        int iAreaNum = pCollisionArea->_nColliPart;
        if (iAreaNum > 0) {
            for (int i = 0; i < iAreaNum; i++) {

                if (pCollisionArea->_papColliPart[i]->_is_valid_flg && pCollisionArea->_papColliPart[i]->_shape_kind == COLLI_AAPRISM) {
                    ColliAAPrism* prism = (ColliAAPrism*)pCollisionArea->_papColliPart[i];
                    //_TRACE_("drawHitarea name="<<prm_pCollisionChecker->getTargetActor()->getName()<<" index="<<i);

                    drawPrism(pActor->_X + prism->_x1,
                            pActor->_Y + prism->_y1,
                            pActor->_Z + prism->_z1,
                            pActor->_X + prism->_x2,
                            pActor->_Y + prism->_y2,
                            pActor->_Z + prism->_z2,
                            prism->_pos_prism);
                    GgafGod::_num_actor_drawing--; //当たり判定表示は表示オブジェクト数にカウントしない
                }
            }
        }

    }
}

ColliAAPrismActor::~ColliAAPrismActor() {
}
