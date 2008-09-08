#include "stdafx.h"

StgChecker::StgChecker(GgafDx9UntransformedActor* prm_pActor) : GgafDx9GeometryChecker(prm_pActor) {
	_pHitArea2D = NULL;
	_iStaminaPointOriginally = 1;//元来の耐久力
	_iScorePointOriginally = 0;  //元来の得点
	_iStaminaPoint = 1;          //耐久力
	_iScorePoint = 0;            //得点
	_iAttackPoint = 0; //攻撃力
	_iDefensePoint = 0; //防御力
}


void StgChecker::behave() {
}


bool StgChecker::isBump(GgafDx9GeometryChecker* prm_pOppChecker) {
	GgafDx9UntransformedActor* pOppActor     = prm_pOppChecker->_pActor;
	HitArea2D*                 pOppHitArea2D = ((StgChecker*)prm_pOppChecker)->_pHitArea2D;
	if (_pHitArea2D == NULL || pOppHitArea2D == NULL) {
		return false;
	}

	//自分の矩形と相手の矩形
	if (_pHitArea2D->_paRect != NULL && pOppHitArea2D->_paRect != NULL) {
		for (int i = 0; i < _pHitArea2D->_iRectNum; i++) {
			for (int j = 0; j < pOppHitArea2D->_iRectNum; j++) {
				if (_pActor->_X+_pHitArea2D->_paRect[i].x2 >= pOppActor->_X + pOppHitArea2D->_paRect[j].x1) {
					if (_pActor->_X+_pHitArea2D->_paRect[i].x1 <= pOppActor->_X + pOppHitArea2D->_paRect[j].x2) {
						if (_pActor->_Y+_pHitArea2D->_paRect[i].y2 >= pOppActor->_Y + pOppHitArea2D->_paRect[j].y1) {
							if (_pActor->_Y+_pHitArea2D->_paRect[i].y1 <= pOppActor->_Y + pOppHitArea2D->_paRect[j].y2) {

//_TRACE_(_pActor->getName()<<"の矩形と"<<pOppActor->getName()<<"の矩形でヒット");
//_TRACE_("("
//   <<(_pActor->_X+_pHitArea2D->_paRect[i].x1)<<","
//   <<(_pActor->_Y+_pHitArea2D->_paRect[i].y1)<<","
//   <<(_pActor->_X+_pHitArea2D->_paRect[i].x2)<<","
//   <<(_pActor->_Y+_pHitArea2D->_paRect[i].y2)<<","
// << ") と ("
//   <<(pOppActor->_X+_pHitArea2D->_paRect[j].x1)<<","
//   <<(pOppActor->_Y+_pHitArea2D->_paRect[j].y1)<<","
//   <<(pOppActor->_X+_pHitArea2D->_paRect[j].x2)<<","
//   <<(pOppActor->_Y+_pHitArea2D->_paRect[j].y2)<<","
// << ")");

								return true;
							}
						}
					}
				}
			}
		}
	}


	//自分の線分と相手の線分
	static int x11, y11, x12, y12, x21, y21, x22, y22;//一時変数
	if (_pHitArea2D->_paLine != NULL && pOppHitArea2D->_paLine != NULL) {
		for (int i = 0; i < _pHitArea2D->_iLineNum; i++) {
			if (_pHitArea2D->_paLine[i].zrot) {
				GgafDx9Util::rotXY(_pHitArea2D->_paLine[i].x1, _pHitArea2D->_paLine[i].y1,
				                   _pActor->_RZ,
				                   &x11, &y11);
				GgafDx9Util::rotXY(_pHitArea2D->_paLine[i].x2, _pHitArea2D->_paLine[i].y2,
				                   _pActor->_RZ,
				                   &x12, &y12);
				x11 += _pActor->_X;
				y11 += _pActor->_Y;
				x12 += _pActor->_X;
				y12 += _pActor->_Y;
			} else {
				x11 = _pActor->_X + _pHitArea2D->_paLine[i].x1;
				y11 = _pActor->_Y + _pHitArea2D->_paLine[i].y1;
				x12 = _pActor->_X + _pHitArea2D->_paLine[i].x2;
				y12 = _pActor->_Y + _pHitArea2D->_paLine[i].y2;
			}

			for (int j = 0; j < pOppHitArea2D->_iLineNum; j++) {
				if (pOppHitArea2D->_paLine[j].zrot) {
					GgafDx9Util::rotXY(pOppHitArea2D->_paLine[j].x1, pOppHitArea2D->_paLine[j].y1,
					                   _pActor->_RZ,
					                   &x21, &y21);
					GgafDx9Util::rotXY(pOppHitArea2D->_paLine[j].x2, pOppHitArea2D->_paLine[j].y2,
					                   _pActor->_RZ,
					                   &x22, &y22);
					x21 += pOppActor->_X;
					y21 += pOppActor->_Y;
					x22 += pOppActor->_X;
					y22 += pOppActor->_Y;
				} else {
					x21 = pOppActor->_X + pOppHitArea2D->_paLine[j].x1;
					y21 = pOppActor->_Y + pOppHitArea2D->_paLine[j].y1;
					x22 = pOppActor->_X + pOppHitArea2D->_paLine[j].x2;
					y22 = pOppActor->_Y + pOppHitArea2D->_paLine[j].y2;
				}

				if (GgafDx9Util::chk2DLineCrossing(x11, y11, x12, y12, x21, y21, x22, y22)) {

//_TRACE_(_pActor->getName()<<"の線分と"<<pOppActor->getName()<<"の線分でヒット");
//_TRACE_("("
//   <<x11<<","
//   <<y11<<""
// << ")-("
//   <<x12<<","
//   <<y12<<""
// << ") と ("
//   <<x21<<","
//   <<y21<<""
// << ")-("
//   <<x22<<","
//   <<y22<<""
// << ")");
					return true;
				}
			}
		}
	}


	//自分の矩形と相手の線分
	if (_pHitArea2D->_paRect != NULL && pOppHitArea2D->_paLine != NULL) {

		//自分の矩形を線分に置き換える
		static int x11[4], y11[4], x12[4], y12[4];
		for (int i = 0; i < _pHitArea2D->_iRectNum; i++) {

			x11[0] = _pHitArea2D->_paRect[i].x1;
			y11[0] = _pHitArea2D->_paRect[i].y1;
			x12[0] = _pHitArea2D->_paRect[i].x2;
			y12[0] = _pHitArea2D->_paRect[i].y1;

			x11[1] = _pHitArea2D->_paRect[i].x2;
			y11[1] = _pHitArea2D->_paRect[i].y1;
			x12[1] = _pHitArea2D->_paRect[i].x2;
			y12[1] = _pHitArea2D->_paRect[i].y2;

			x11[2] = _pHitArea2D->_paRect[i].x2;
			y11[2] = _pHitArea2D->_paRect[i].y2;
			x12[2] = _pHitArea2D->_paRect[i].x1;
			y12[2] = _pHitArea2D->_paRect[i].y2;

			x11[3] = _pHitArea2D->_paRect[i].x1;
			y11[3] = _pHitArea2D->_paRect[i].y2;
			x12[3] = _pHitArea2D->_paRect[i].x1;
			y12[3] = _pHitArea2D->_paRect[i].y1;

			//線分同士の当たり判定
			for (int ir = 0; ir < 4; ir++) {
				for (int j = 0; j < pOppHitArea2D->_iLineNum; j++) {

					if (pOppHitArea2D->_paLine[j].zrot) {
						GgafDx9Util::rotXY(pOppHitArea2D->_paLine[j].x1, pOppHitArea2D->_paLine[j].y1,
						                   _pActor->_RZ,
						                   &x21, &y21);
						GgafDx9Util::rotXY(pOppHitArea2D->_paLine[j].x2, pOppHitArea2D->_paLine[j].y2,
						                   _pActor->_RZ,
						                   &x22, &y22);
						x21 += pOppActor->_X;
						y21 += pOppActor->_Y;
						x22 += pOppActor->_X;
						y22 += pOppActor->_Y;
					} else {
						x21 = pOppActor->_X + pOppHitArea2D->_paLine[j].x1;
						y21 = pOppActor->_Y + pOppHitArea2D->_paLine[j].y1;
						x22 = pOppActor->_X + pOppHitArea2D->_paLine[j].x2;
						y22 = pOppActor->_Y + pOppHitArea2D->_paLine[j].y2;
					}

					if (GgafDx9Util::chk2DLineCrossing(
							_pActor->_X + x11[ir],
							_pActor->_Y + y11[ir],
							_pActor->_X + x12[ir],
							_pActor->_Y + y12[ir],
							x21,
							y21,
							x22,
							y22 ) )
					{
//_TRACE_(_pActor->getName()<<"の矩形線分と"<<pOppActor->getName()<<"の線分でヒット");
//_TRACE_("("
//   <<(_pActor->_X + x11[ir])<<","
//   <<(_pActor->_Y + y11[ir])<<""
// << ")-("
//   <<(_pActor->_X + x12[ir])<<","
//   <<(_pActor->_Y + y12[ir])<<""
// << ") と ("
//   <<x21<<","
//   <<y21<<""
// << ")-("
//   <<x22<<","
//   <<y22<<""
// << ")");
 						return true;
					}
				}
			}
		}
	}

	//自分の線分と相手の矩形
	if (_pHitArea2D->_paLine != NULL && pOppHitArea2D->_paRect != NULL) {
		static int x21[4], y21[4], x22[4], y22[4];
		for (int i = 0; i < _pHitArea2D->_iLineNum; i++) {
			if (_pHitArea2D->_paLine[i].zrot) {
				GgafDx9Util::rotXY(_pHitArea2D->_paLine[i].x1, _pHitArea2D->_paLine[i].y1,
				                   _pActor->_RZ,
				                   &x11, &y11);
				GgafDx9Util::rotXY(_pHitArea2D->_paLine[i].x2, _pHitArea2D->_paLine[i].y2,
				                   _pActor->_RZ,
				                   &x12, &y12);
				x11 += _pActor->_X;
				y11 += _pActor->_Y;
				x12 += _pActor->_X;
				y12 += _pActor->_Y;
			} else {
				x11 = _pActor->_X + _pHitArea2D->_paLine[i].x1;
				y11 = _pActor->_Y + _pHitArea2D->_paLine[i].y1;
				x12 = _pActor->_X + _pHitArea2D->_paLine[i].x2;
				y12 = _pActor->_Y + _pHitArea2D->_paLine[i].y2;
			}

			//相手の矩形を線分に置き換える
			for (int j = 0; j < pOppHitArea2D->_iRectNum; j++) {
				x21[0] = pOppHitArea2D->_paRect[j].x1;
				y21[0] = pOppHitArea2D->_paRect[j].y1;
				x22[0] = pOppHitArea2D->_paRect[j].x2;
				y22[0] = pOppHitArea2D->_paRect[j].y1;

				x21[1] = pOppHitArea2D->_paRect[j].x2;
				y21[1] = pOppHitArea2D->_paRect[j].y1;
				x22[1] = pOppHitArea2D->_paRect[j].x2;
				y22[1] = pOppHitArea2D->_paRect[j].y2;

				x21[2] = pOppHitArea2D->_paRect[j].x2;
				y21[2] = pOppHitArea2D->_paRect[j].y2;
				x22[2] = pOppHitArea2D->_paRect[j].x1;
				y22[2] = pOppHitArea2D->_paRect[j].y2;

				x21[3] = pOppHitArea2D->_paRect[j].x1;
				y21[3] = pOppHitArea2D->_paRect[j].y2;
				x22[3] = pOppHitArea2D->_paRect[j].x1;
				y22[3] = pOppHitArea2D->_paRect[j].y1;

				//線分同士の当たり判定
				for (int jr = 0; jr < 4; jr++) {
					if (GgafDx9Util::chk2DLineCrossing(
							x11,
							y11,
							x12,
							y12,
							pOppActor->_X + x21[jr],
							pOppActor->_Y + y21[jr],
							pOppActor->_X + x22[jr],
							pOppActor->_Y + y22[jr]  ) )
					{
//_TRACE_(_pActor->getName()<<"の線分と"<<pOppActor->getName()<<"の矩形線分でヒット");
//_TRACE_("("
//   <<x11<<","
//   <<y11<<""
// << ")-("
//   <<x12<<","
//   <<y12<<""
// << ") と ("
//   <<(pOppActor->_X + x21[jr])<<","
//   <<(pOppActor->_Y + y21[jr])<<""
// << ")-("
//   <<(pOppActor->_X + x22[jr])<<","
//   <<(pOppActor->_Y + y22[jr])<<""
// << ")");
						return true;
					}
				}
			}
		}
	}
	return false;
}

StgChecker::~StgChecker() {
	TRACE("StgChecker::~StgChecker() _pActor="<<_pActor->getName()<<" start--->");
	if (_pHitArea2D != NULL) {
		delete _pHitArea2D;
	}
	TRACE("StgChecker::~StgChecker() _pActor="<<_pActor->getName()<<" <---end");
}
