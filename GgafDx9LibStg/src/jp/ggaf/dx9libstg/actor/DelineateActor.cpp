#include "stdafx.h"

DelineateActor* DelineateActor::_pObj = NULL;

DelineateActor* DelineateActor::get() {
	if (_pObj == NULL) {
		_pObj = NEW DelineateActor("HITAREA", "DelineateSprite");
	}
	return _pObj;
}

void DelineateActor::release() {
	if (_pObj != NULL) {
		delete _pObj;
	}
}

DelineateActor::DelineateActor(string prm_name, string prm_xname) : DefaultSquareActor(prm_name, prm_xname) {
	_class_name = "DelineateActor";
}

void DelineateActor::drawRect(int prm_x1, int prm_y1, int prm_x2, int prm_y2) {
	_SX = (prm_x2 - prm_x1);
	_SY = (prm_y2 - prm_y1);
	_RZ = 0;
	_X = prm_x1 + (prm_x2 - prm_x1)/2;
	_Y = prm_y1 + (prm_y2 - prm_y1)/2;
	drawMain();
}

void DelineateActor::drawLine(int prm_x1, int prm_y1, int prm_x2, int prm_y2) {
	//_SXは２点の距離になる。(x2-x1)^2 + (y2-y1)^2
	_SX = (int)((sqrt((((double)(prm_x2-prm_x1))*((double)(prm_x2-prm_x1))) + (((double)(prm_y2-prm_y1))*((double)(prm_y2-prm_y1))))));
	_SY = 1000;
	_RZ = GgafDx9Util::getAngle(prm_x2 - prm_x1, prm_y2 - prm_y1);
	_X = prm_x1 + (prm_x2 - prm_x1)/2;
	_Y = prm_y1 + (prm_y2 - prm_y1)/2;
	drawMain();
}
void DelineateActor::drawHitarea(StgChecker* prm_pChecker) {
	if (prm_pChecker != NULL && prm_pChecker->_pHitArea2D != NULL) {
		//最前面に表示するため一時OFF
		GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

		int iRectNum = prm_pChecker->_pHitArea2D->_iRectNum;
		if (iRectNum > 0) {
			int x1, y1, x2, y2;
			for (int i = 0; i < iRectNum; i++) {
				x1 = prm_pChecker->_pActor->_X + prm_pChecker->_pHitArea2D->_paRect[i].x1;
				y1 = prm_pChecker->_pActor->_Y + prm_pChecker->_pHitArea2D->_paRect[i].y1;
				x2 = prm_pChecker->_pActor->_X + prm_pChecker->_pHitArea2D->_paRect[i].x2;
				y2 = prm_pChecker->_pActor->_Y + prm_pChecker->_pHitArea2D->_paRect[i].y2;
				drawRect(x1, y1, x2, y2);
			}
		}
		int iLineNum = prm_pChecker->_pHitArea2D->_iLineNum;
		if (iLineNum > 0) {
			int x1, y1, x2, y2;
			for (int i = 0; i < iLineNum; i++) {
				if (prm_pChecker->_pHitArea2D->_paLine[i].zrot) {
					GgafDx9Util::rotXY(prm_pChecker->_pHitArea2D->_paLine[i].x1,
					                   prm_pChecker->_pHitArea2D->_paLine[i].y1,
					                   prm_pChecker->_pActor->_RZ,
					                   &x1,
					                   &y1);
					GgafDx9Util::rotXY(prm_pChecker->_pHitArea2D->_paLine[i].x2,
					                   prm_pChecker->_pHitArea2D->_paLine[i].y2,
					                   prm_pChecker->_pActor->_RZ,
					                   &x2,
					                   &y2);
					x1 += prm_pChecker->_pActor->_X;
					y1 += prm_pChecker->_pActor->_Y;
					x2 += prm_pChecker->_pActor->_X;
					y2 += prm_pChecker->_pActor->_Y;
				} else {
					x1 = prm_pChecker->_pActor->_X + prm_pChecker->_pHitArea2D->_paLine[i].x1;
					y1 = prm_pChecker->_pActor->_Y + prm_pChecker->_pHitArea2D->_paLine[i].y1;
					x2 = prm_pChecker->_pActor->_X + prm_pChecker->_pHitArea2D->_paLine[i].x2;
					y2 = prm_pChecker->_pActor->_Y + prm_pChecker->_pHitArea2D->_paLine[i].y2;
				}
				drawLine(x1, y1, x2, y2);
			}
		}
		//元に戻す
		GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}
}

DelineateActor::~DelineateActor() {
}
