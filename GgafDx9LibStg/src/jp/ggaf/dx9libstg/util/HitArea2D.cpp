#include "stdafx.h"


HitArea2D::HitArea2D(int prm_iRectNum, int prm_iLineNum) : GgafObject() {
	if (prm_iRectNum > 0) {
		_paRect = NEW HitRect2D[prm_iRectNum];
		_iRectNum = prm_iRectNum;
	} else {
		_paRect = NULL;
		_iRectNum = 0;
	}
	if (prm_iLineNum > 0) {
		_paLine = NEW HitLine2D[prm_iLineNum];
		_iLineNum = prm_iLineNum;
	} else {
		_paLine = NULL;
		_iLineNum = 0;
	}
}

void HitArea2D::setRect(int prm_index, int prm_x1, int prm_y1, int prm_x2, int prm_y2, int prm_thick_z1, int prm_thick_z2) {
	if (_iRectNum < prm_index) {
		_TRACE_("HitArea2D::setRect() 要素オーバー。_iRectNum="<<_iRectNum<<"/prm_index="<<prm_index);
		throw_GgafCriticalException("HitArea2D::setRect() 要素オーバー。_iRectNum="<<_iRectNum<<"/prm_index="<<prm_index);
	}
	_paRect[prm_index].x1 = prm_x1;
	_paRect[prm_index].y1 = prm_y1;
	_paRect[prm_index].x2 = prm_x2;
	_paRect[prm_index].y2 = prm_y2;
	_paRect[prm_index].thick_z1 = prm_thick_z1;
	_paRect[prm_index].thick_z2 = prm_thick_z2;

}

void HitArea2D::setLine(int prm_index, int prm_x1, int prm_y1, int prm_x2, int prm_y2, bool zrot, int prm_thick_z1, int prm_thick_z2) {
	if (_iLineNum < prm_index) {
		_TRACE_("HitArea2D::setLine() 要素オーバー。_iLineNum="<<_iLineNum<<"/prm_index="<<prm_index);
		throw_GgafCriticalException("HitArea2D::setLine() 要素オーバー。_iLineNum="<<_iLineNum<<"/prm_index="<<prm_index);
	}
	_paLine[prm_index].x1 = prm_x1;
	_paLine[prm_index].y1 = prm_y1;
	_paLine[prm_index].x2 = prm_x2;
	_paLine[prm_index].y2 = prm_y2;
	_paLine[prm_index].zrot = zrot;
	_paLine[prm_index].thick_z1 = prm_thick_z1;
	_paLine[prm_index].thick_z2 = prm_thick_z2;

}



HitArea2D::~HitArea2D() {
	TRACE("HitArea2D::~HitArea2D() start--->");
	if (_paRect != NULL) {
		delete[] _paRect;
	}
	if (_paLine != NULL) {
		delete[] _paLine;
	}
	TRACE("HitArea2D::~HitArea2D() <---end");
}
