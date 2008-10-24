#include "stdafx.h"


HitAreaBoxs::HitAreaBoxs(int prm_iBoxNum) : GgafObject() {
	if (prm_iBoxNum > 0) {
		_paBox = NEW Box[prm_iBoxNum];
		_iBoxNum = prm_iBoxNum;
	} else {
		throw_GgafCriticalException("HitAreaBoxs::HitAreaBoxs Box数が不正。prm_iBoxNum="<<prm_iBoxNum);
	}
}

void HitAreaBoxs::setBox(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2) {
	if (_iBoxNum < prm_index) {
		throw_GgafCriticalException("HitAreaBoxs::setBox() 要素オーバー。_iBoxNum="<<_iBoxNum<<"/prm_index="<<prm_index);
	}
	_paBox[prm_index].x1 = x1;
	_paBox[prm_index].y1 = y1;
	_paBox[prm_index].z1 = z1;
	_paBox[prm_index].x2 = x2;
	_paBox[prm_index].y2 = y2;
	_paBox[prm_index].z2 = z2;

}

void HitAreaBoxs::setBox(int prm_index, int x1, int y1, int x2, int y2) {
	if (_iBoxNum < prm_index) {
		throw_GgafCriticalException("HitAreaBoxs::setBox() 要素オーバー2。_iBoxNum="<<_iBoxNum<<"/prm_index="<<prm_index);
	}
	_paBox[prm_index].x1 = x1;
	_paBox[prm_index].y1 = y1;
	_paBox[prm_index].z1 = -5000; //-5px～+5px で厚み10px
	_paBox[prm_index].x2 = x2;
	_paBox[prm_index].y2 = y2;
	_paBox[prm_index].z2 = 5000;

}


HitAreaBoxs::~HitAreaBoxs() {
	TRACE("HitAreaBoxs::~HitAreaBoxs() start--->");
	if (_paBox != NULL) {
		delete[] _paBox;
	}
	TRACE("HitAreaBoxs::~HitAreaBoxs() <---end");
}
