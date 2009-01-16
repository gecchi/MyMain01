#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

DelineateActor* DelineateActor::_s_pObj = NULL;

DelineateActor::DelineateActor(string prm_name) : DefaultCubeActor(prm_name) {
	_class_name = "DelineateActor";
}

DelineateActor* DelineateActor::get() {
	if (_s_pObj == NULL) {
		_s_pObj = NEW DelineateActor("HITAREA");
	}
	return _s_pObj;
}

void DelineateActor::release() {
	DELETE_POSSIBLE_NULL(_s_pObj);
}



void DelineateActor::drawBox(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2,  int prm_z2) {
	_SX = (prm_x2 - prm_x1);
	_SY = (prm_y2 - prm_y1);
	_SZ = (prm_z2 - prm_z1);
	_RZ = 0;
	_X = prm_x1 + (prm_x2 - prm_x1)/2;
	_Y = prm_y1 + (prm_y2 - prm_y1)/2;
	_Z = prm_z1 + (prm_z2 - prm_z1)/2;
	processDrawMain();
	GgafGod::_iNumPlayingActor--; //当たり判定表示は表示オブジェクト数にカウントしない
}

void DelineateActor::drawHitarea(StgChecker* prm_pChecker) {
	if (prm_pChecker != NULL && prm_pChecker->getHitAreaBoxs() != NULL && prm_pChecker->getTargetActor()->canBump()) {
		GgafDx9UntransformedActor* pActor     = prm_pChecker->getTargetActor();
		HitAreaBoxs*                 pHitAreaBoxs = prm_pChecker->getHitAreaBoxs();

		//最前面に表示するため一時OFF
		//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

		int iBoxNum = pHitAreaBoxs->_iBoxNum;
		if (iBoxNum > 0) {
			for (int i = 0; i < iBoxNum; i++) {
				if (pHitAreaBoxs->isEnable(i)) {
					drawBox(
						pActor->_X + pHitAreaBoxs->_paHitArea[i].x1,
						pActor->_Y + pHitAreaBoxs->_paHitArea[i].y1,
						pActor->_Z + pHitAreaBoxs->_paHitArea[i].z1,
						pActor->_X + pHitAreaBoxs->_paHitArea[i].x2,
						pActor->_Y + pHitAreaBoxs->_paHitArea[i].y2,
						pActor->_Z + pHitAreaBoxs->_paHitArea[i].z2
					);
				}
			}
		}
		//元に戻す
		//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}
}

DelineateActor::~DelineateActor() {
}
