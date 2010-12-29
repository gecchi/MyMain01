#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ColliSphereActor* ColliSphereActor::_pObj = NULL;

ColliSphereActor::ColliSphereActor(const char* prm_name) : GgafDx9SphereActor(prm_name, NULL) {
    _class_name = "ColliSphereActor";
}

ColliSphereActor* ColliSphereActor::get() {
    if (ColliSphereActor::_pObj == NULL) {
        ColliSphereActor::_pObj = NEW ColliSphereActor("HITAREA");
    }
    return ColliSphereActor::_pObj;
}

void ColliSphereActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとNULLかもしれない
    DELETE_POSSIBLE_NULL(ColliSphereActor::_pObj);
}

void ColliSphereActor::drawHitarea(CollisionChecker* prm_pCollisionChecker) {
    if (prm_pCollisionChecker != NULL &&
        prm_pCollisionChecker->_pCollisionArea != NULL &&
        prm_pCollisionChecker->getTargetActor()->canHit() &&
        prm_pCollisionChecker->getTargetActor()->isActive()) {
        GgafDx9GeometricActor* pActor = prm_pCollisionChecker->getTargetActor();
        GgafDx9CollisionArea* pCollisionArea = prm_pCollisionChecker->_pCollisionArea;

        int iAreaNum = pCollisionArea->_nColliPart;
        if (iAreaNum > 0) {
            for (int i = 0; i < iAreaNum; i++) {
                if (pCollisionArea->_papColliPart[i]->_is_valid_flg && pCollisionArea->_papColliPart[i]->_shape_kind == COLLI_SPHERE) {
                    ColliSphere* sphere = (ColliSphere*)pCollisionArea->_papColliPart[i];
                    //_TRACE_("drawHitarea name="<<prm_pCollisionChecker->getTargetActor()->getName()<<" index="<<i);

                    drawSphere(pActor->_X + sphere->_x,
                                pActor->_Y + sphere->_y,
                                pActor->_Z + sphere->_z,
                                sphere->_r);
                    GgafGod::_num_actor_drawing--; //当たり判定表示は表示オブジェクト数にカウントしない
                }
            }
        }

    }
}

ColliSphereActor::~ColliSphereActor() {
}
