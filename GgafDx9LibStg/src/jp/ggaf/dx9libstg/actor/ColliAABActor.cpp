#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ColliAABActor* ColliAABActor::_pObj = NULL;

ColliAABActor::ColliAABActor(const char* prm_name) : GgafDx9AABActor(prm_name, NULL) {
    _class_name = "ColliAABActor";
    setAlpha(0.8);
}

ColliAABActor* ColliAABActor::get() {
    if (ColliAABActor::_pObj == NULL) {
        ColliAABActor::_pObj = NEW ColliAABActor("HITAREA");
    }
    return ColliAABActor::_pObj;
}

void ColliAABActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとNULLかもしれない
    DELETE_POSSIBLE_NULL(ColliAABActor::_pObj);
}

void ColliAABActor::drawHitarea(CollisionChecker* prm_pCollisionChecker) {
    if (prm_pCollisionChecker != NULL &&
        prm_pCollisionChecker->_pCollisionArea != NULL &&
        prm_pCollisionChecker->getTargetActor()->canHit() &&
        prm_pCollisionChecker->getTargetActor()->isActiveActor()) {

        GgafDx9GeometricActor* pActor = prm_pCollisionChecker->getTargetActor();
        GgafDx9CollisionArea* pCollisionArea = prm_pCollisionChecker->_pCollisionArea;
        int iAreaNum = pCollisionArea->_nColliPart;
        if (iAreaNum > 0) {
            GgafDx9CollisionPart** papColliPart = pCollisionArea->_papColliPart;
            for (int i = 0; i < iAreaNum; i++) {
                if (papColliPart[i]->_is_valid_flg && papColliPart[i]->_shape_kind == COLLI_AAB) {
                    ColliAAB* box = (ColliAAB*)papColliPart[i];
                    //_TRACE_("drawHitarea name="<<prm_pCollisionChecker->getTargetActor()->getName()<<" index="<<i);

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
