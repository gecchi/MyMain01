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
    if (_pObj == NULL) {
        _pObj = NEW CubeEx("HITAREA");
    }
    return _pObj;
}

void CubeEx::release() {
    DELETE_POSSIBLE_NULL(_pObj);
}

void CubeEx::drawHitarea(StgChecker* prm_pStgChecker) {
    if (prm_pStgChecker != NULL && prm_pStgChecker->getHitAreaBoxs() != NULL && prm_pStgChecker->getTargetActor()->canBump()
            && prm_pStgChecker->getTargetActor()->isActive()) {
        GgafDx9GeometricActor* pActor = prm_pStgChecker->getTargetActor();
        HitAreaBoxs* pHitAreaBoxs = prm_pStgChecker->getHitAreaBoxs();

        //最前面に表示するため一時OFF
        //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

        int iAreaNum = pHitAreaBoxs->_iAreaNum;
        if (iAreaNum > 0) {
            for (int i = 0; i < iAreaNum; i++) {
                //if (pHitAreaBoxs->isEnable(i)) {
                    drawBox(pActor->_X + pHitAreaBoxs->_paHitArea[i].x1, pActor->_Y + pHitAreaBoxs->_paHitArea[i].y1,
                            pActor->_Z + pHitAreaBoxs->_paHitArea[i].z1, pActor->_X + pHitAreaBoxs->_paHitArea[i].x2,
                            pActor->_Y + pHitAreaBoxs->_paHitArea[i].y2, pActor->_Z + pHitAreaBoxs->_paHitArea[i].z2);
                    GgafGod::_num_actor_playing--; //当たり判定表示は表示オブジェクト数にカウントしない
                //}
            }
        }
        //元に戻す
        //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    }
}

CubeEx::~CubeEx() {
}
