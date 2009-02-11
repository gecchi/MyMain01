#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DelineateActor* DelineateActor::_pObj = NULL;

DelineateActor::DelineateActor(const char* prm_name) : DefaultCubeActor(prm_name) {
    _class_name = "DelineateActor";
}

DelineateActor* DelineateActor::get() {
    if (_pObj == NULL) {
        _pObj = NEW DelineateActor("HITAREA");
    }
    return _pObj;
}

void DelineateActor::release() {
    DELETE_POSSIBLE_NULL(_pObj);
}

void DelineateActor::drawHitarea(StgChecker* prm_pChecker) {
    if (prm_pChecker != NULL && prm_pChecker->getHitAreaBoxs() != NULL && prm_pChecker->getTargetActor()->canBump()
            && prm_pChecker->getTargetActor()->isPlaying()) {
        GgafDx9UntransformedActor* pActor = prm_pChecker->getTargetActor();
        HitAreaBoxs* pHitAreaBoxs = prm_pChecker->getHitAreaBoxs();

        //�őO�ʂɕ\�����邽�߈ꎞOFF
        //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

        int iBoxNum = pHitAreaBoxs->_iBoxNum;
        if (iBoxNum > 0) {
            for (int i = 0; i < iBoxNum; i++) {
                if (pHitAreaBoxs->isEnable(i)) {

                    drawBox(pActor->_X + pHitAreaBoxs->_paHitArea[i].x1, pActor->_Y + pHitAreaBoxs->_paHitArea[i].y1,
                            pActor->_Z + pHitAreaBoxs->_paHitArea[i].z1, pActor->_X + pHitAreaBoxs->_paHitArea[i].x2,
                            pActor->_Y + pHitAreaBoxs->_paHitArea[i].y2, pActor->_Z + pHitAreaBoxs->_paHitArea[i].z2);
                    GgafGod::_iNumPlayingActor--; //�����蔻��\���͕\���I�u�W�F�N�g���ɃJ�E���g���Ȃ�
                }
            }
        }
        //���ɖ߂�
        //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    }
}

DelineateActor::~DelineateActor() {
}
