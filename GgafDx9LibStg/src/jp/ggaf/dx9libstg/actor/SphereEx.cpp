#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

SphereEx* SphereEx::_pObj = NULL;

SphereEx::SphereEx(const char* prm_name) : GgafDx9SphereEx(prm_name) {
    _class_name = "SphereEx";
}

SphereEx* SphereEx::get() {
    if (_pObj == NULL) {
        _pObj = NEW SphereEx("HITAREA");
    }
    return _pObj;
}

void SphereEx::release() {
    //あたり判定を持つオブジェクトが一度も使用されないとNULLかもしれない
    DELETE_POSSIBLE_NULL(_pObj);
}

void SphereEx::drawHitarea(CollisionChecker* prm_pCollisionChecker) {
    if (prm_pCollisionChecker != NULL &&
        prm_pCollisionChecker->_pCollisionArea != NULL &&
        prm_pCollisionChecker->getTargetActor()->canBump() &&
        prm_pCollisionChecker->getTargetActor()->isActive()) {
        GgafDx9GeometricActor* pActor = prm_pCollisionChecker->getTargetActor();
        GgafDx9CollisionArea* pCollisionArea = prm_pCollisionChecker->_pCollisionArea;

        //最前面に表示するため一時OFF
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

        int iAreaNum = pCollisionArea->_nColliPart;
        if (iAreaNum > 0) {
            for (int i = 0; i < iAreaNum; i++) {
                if (pCollisionArea->_papColliPart[i]->_is_valid_flg) {
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
        //元に戻す
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    }
}

SphereEx::~SphereEx() {
}
