#include "stdafx.h"

DelineateActor* DelineateActor::_s_pObj = NULL;

DelineateActor* DelineateActor::get() {
	if (_s_pObj == NULL) {
		_s_pObj = NEW DelineateActor("HITAREA");
	}
	return _s_pObj;
}

void DelineateActor::release() {
	if (_s_pObj != NULL) {
		delete _s_pObj;
	}
}

DelineateActor::DelineateActor(string prm_name) : DefaultCubeActor(prm_name) {
	_class_name = "DelineateActor";
}

void DelineateActor::drawRect(int prm_x1, int prm_y1, int prm_x2, int prm_y2, int prm_thick_z1, int prm_thick_z2) {
	_SX = (prm_x2 - prm_x1);
	_SY = (prm_y2 - prm_y1);
	_SZ = (prm_thick_z2 - prm_thick_z1);
	_RZ = 0;
	_X = prm_x1 + (prm_x2 - prm_x1)/2;
	_Y = prm_y1 + (prm_y2 - prm_y1)/2;
	_Z = prm_thick_z1 + (prm_thick_z2 - prm_thick_z1)/2;
	processDrawMain();
}

void DelineateActor::drawLine(int prm_x1, int prm_y1, int prm_x2, int prm_y2, int prm_thick_z1, int prm_thick_z2) {
	//_SXは２点の距離になる。(x2-x1)^2 + (y2-y1)^2
	_SX = (int)((sqrt((((double)(prm_x2-prm_x1))*((double)(prm_x2-prm_x1))) + (((double)(prm_y2-prm_y1))*((double)(prm_y2-prm_y1))))));
	_SY = 1000;
	_SZ = (prm_thick_z2 - prm_thick_z1);
	_RZ = GgafDx9Util::getAngle(prm_x2 - prm_x1, prm_y2 - prm_y1);
	_X = prm_x1 + (prm_x2 - prm_x1)/2;
	_Y = prm_y1 + (prm_y2 - prm_y1)/2;
	_Z = prm_thick_z1 + (prm_thick_z2 - prm_thick_z1)/2;

	processDrawMain();
}
void DelineateActor::drawHitarea(StgChecker* prm_pChecker) {
	if (prm_pChecker != NULL && prm_pChecker->_pHitArea2D != NULL && prm_pChecker->_pActor->canBump()) {
		GgafDx9UntransformedActor* pActor     = prm_pChecker->_pActor;
		HitArea2D*                 pHitArea2D = prm_pChecker->_pHitArea2D;

		//最前面に表示するため一時OFF
		//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

		int iRectNum = pHitArea2D->_iRectNum;
		if (iRectNum > 0) {
			for (int i = 0; i < iRectNum; i++) {
				drawRect(
					pActor->_X + pHitArea2D->_paRect[i].x1,
					pActor->_Y + pHitArea2D->_paRect[i].y1,
					pActor->_X + pHitArea2D->_paRect[i].x2,
					pActor->_Y + pHitArea2D->_paRect[i].y2,
					pActor->_Z + pHitArea2D->_paRect[i].thick_z1,
					pActor->_Z + pHitArea2D->_paRect[i].thick_z2
				);
			}
		}
		int iLineNum = pHitArea2D->_iLineNum;
		if (iLineNum > 0) {
			static int x1, y1, x2, y2;
			for (int i = 0; i < iLineNum; i++) {
				if (pHitArea2D->_paLine[i].zrot) {
					GgafDx9Util::rotXY(pHitArea2D->_paLine[i].x1,
					                   pHitArea2D->_paLine[i].y1,
					                   pActor->_RZ,
					                   &x1,
					                   &y1);
					GgafDx9Util::rotXY(pHitArea2D->_paLine[i].x2,
					                   pHitArea2D->_paLine[i].y2,
					                   pActor->_RZ,
					                   &x2,
					                   &y2);
					x1 += pActor->_X;
					y1 += pActor->_Y;
					x2 += pActor->_X;
					y2 += pActor->_Y;
				} else {
					x1 = pActor->_X + pHitArea2D->_paLine[i].x1;
					y1 = pActor->_Y + pHitArea2D->_paLine[i].y1;
					x2 = pActor->_X + pHitArea2D->_paLine[i].x2;
					y2 = pActor->_Y + pHitArea2D->_paLine[i].y2;
				}

				drawLine(
					x1,
					y1,
					x2,
					y2,
					pActor->_Z + pHitArea2D->_paLine[i].thick_z1,
					pActor->_Z + pHitArea2D->_paLine[i].thick_z2
				);
			}
		}
		//元に戻す
		//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}
}

DelineateActor::~DelineateActor() {
}
