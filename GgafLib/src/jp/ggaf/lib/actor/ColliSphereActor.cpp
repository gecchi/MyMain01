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
    //�����蔻������I�u�W�F�N�g����x���g�p����Ȃ���NULL��������Ȃ�
    DELETE_POSSIBLE_NULL(ColliSphereActor::_pObj);
}

void ColliSphereActor::drawHitarea(CollisionChecker* prm_pColliChecker) {
    if (prm_pColliChecker != NULL &&
        prm_pColliChecker->_pCollisionArea != NULL &&
        prm_pColliChecker->getTargetActor()->canHit() &&
        prm_pColliChecker->getTargetActor()->isActiveInTheTree()) {
        GgafDxGeometricActor* pActor = prm_pColliChecker->getTargetActor();
        GgafDxCollisionArea* pCollisionArea = prm_pColliChecker->_pCollisionArea;

        int iAreaNum = pCollisionArea->_nColliPart;
        if (iAreaNum > 0) {
            for (int i = 0; i < iAreaNum; i++) {
                if (pCollisionArea->_papColliPart[i]->_is_valid_flg && pCollisionArea->_papColliPart[i]->_shape_kind == COLLI_SPHERE) {
                    ColliSphere* sphere = (ColliSphere*)pCollisionArea->_papColliPart[i];
                    //_TRACE_("drawHitarea name="<<prm_pColliChecker->getTargetActor()->getName()<<" index="<<i);

                    drawSphere(pActor->_X + sphere->_x,
                                pActor->_Y + sphere->_y,
                                pActor->_Z + sphere->_z,
                                sphere->_r);
                    GgafGod::_num_actor_drawing--; //�����蔻��\���͕\���I�u�W�F�N�g���ɃJ�E���g���Ȃ�
                }
            }
        }

    }
}

ColliSphereActor::~ColliSphereActor() {
}
