#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliSphereActor* ColliSphereActor::_pObj = nullptr;

ColliSphereActor::ColliSphereActor(const char* prm_name, GgafStatus* prm_pStat) : GgafDxSphereActor(prm_name, prm_pStat, nullptr) {
    _class_name = "ColliSphereActor";
    setAlpha(0.8);
}

ColliSphereActor* ColliSphereActor::get() {
    if (ColliSphereActor::_pObj == nullptr) {
        ColliSphereActor::_pObj = NEW ColliSphereActor("HITAREA", nullptr);
    }
    return ColliSphereActor::_pObj;
}

void ColliSphereActor::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとnullptrかもしれない
    GGAF_DELETE_NULLABLE(ColliSphereActor::_pObj);
}

void ColliSphereActor::drawHitarea(CollisionChecker3D* prm_pColliChecker) {
    if (prm_pColliChecker != nullptr &&
        prm_pColliChecker->_pCollisionArea != nullptr &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {
        GgafDxGeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDxCollisionArea* pCollisionArea = prm_pColliChecker->_pCollisionArea;

        int iAreaNum = pCollisionArea->_colli_part_num;
        if (iAreaNum > 0) {
            for (int i = 0; i < iAreaNum; i++) {
                if (pCollisionArea->_papColliPart[i]->_is_valid_flg && pCollisionArea->_papColliPart[i]->_shape_kind == COLLI_SPHERE) {
                    ColliSphere* sphere = (ColliSphere*)pCollisionArea->_papColliPart[i];
                    //_TRACE_("drawHitarea name="<<prm_pColliChecker->getTargetActor()->getName()<<" index="<<i);

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
