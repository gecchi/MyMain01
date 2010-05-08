#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

CubeEx* CubeEx::_pObj = NULL;

CubeEx::CubeEx(const char* prm_name) : GgafDx9CubeEx(prm_name) {
    _class_name = "CubeEx";
}

CubeEx* CubeEx::get() {
    if (CubeEx::_pObj == NULL) {
        CubeEx::_pObj = NEW CubeEx("HITAREA");
    }
    return CubeEx::_pObj;
}

void CubeEx::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとNULLかもしれない
    DELETE_POSSIBLE_NULL(CubeEx::_pObj);
}

void CubeEx::drawHitarea(CollisionChecker* prm_pCollisionChecker) {
    if (prm_pCollisionChecker != NULL &&
        prm_pCollisionChecker->_pCollisionArea != NULL &&
        prm_pCollisionChecker->getTargetActor()->canHit() &&
        prm_pCollisionChecker->getTargetActor()->isActive()) {

        GgafDx9GeometricActor* pActor = prm_pCollisionChecker->getTargetActor();
        GgafDx9CollisionArea* pCollisionArea = prm_pCollisionChecker->_pCollisionArea;
        int iAreaNum = pCollisionArea->_nColliPart;
        if (iAreaNum > 0) {
            for (int i = 0; i < iAreaNum; i++) {

                if (pCollisionArea->_papColliPart[i]->_is_valid_flg && pCollisionArea->_papColliPart[i]->_shape_kind == COLLI_AABB) {
                    ColliAAB* box = (ColliAAB*)pCollisionArea->_papColliPart[i];
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

CubeEx::~CubeEx() {
}
