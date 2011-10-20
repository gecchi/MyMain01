#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliSphereActor* ColliSphereActor::_pObj = NULL;

ColliSphereActor::ColliSphereActor(const char* prm_name, GgafStatus* prm_pStat) : GgafDxSphereActor(prm_name, prm_pStat, NULL) {
    _class_name = "ColliSphereActor";
    setAlpha(0.8);
}

ColliSphereActor* ColliSphereActor::get() {
    if (ColliSphereActor::_pObj == NULL) {
        ColliSphereActor::_pObj = NEW ColliSphereActor("HITAREA", NULL);
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
        prm_pCollisionChecker->getTargetActor()->isActiveInTheWorld()) {
        GgafDxGeometricActor* pActor = prm_pCollisionChecker->getTargetActor();
        GgafDxCollisionArea* pCollisionArea = prm_pCollisionChecker->_pCollisionArea;

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
