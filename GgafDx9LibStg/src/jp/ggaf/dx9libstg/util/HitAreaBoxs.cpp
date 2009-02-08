#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

HitAreaBoxs::HitAreaBoxs(int prm_iBoxNum) : GgafObject() {
    if (prm_iBoxNum > 0) {
        _paBase = NEW Box[prm_iBoxNum];
        _paHitArea = NEW Box[prm_iBoxNum];
        _iBoxNum = prm_iBoxNum;
    } else {
        throwGgafCriticalException("HitAreaBoxs::HitAreaBoxs Box数が不正。prm_iBoxNum="<<prm_iBoxNum);
    }
}

void HitAreaBoxs::setBox(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ) {
    if (_iBoxNum < prm_index) {
        throwGgafCriticalException("HitAreaBoxs::setBox() 要素オーバー。_iBoxNum="<<_iBoxNum<<"/prm_index="<<prm_index);
    }
    if (x1 < x2) {
        _paBase[prm_index].x1 = x1;
        _paBase[prm_index].x2 = x2;
    } else {
        _paBase[prm_index].x1 = x2;
        _paBase[prm_index].x2 = x1;
    }

    if (y1 < y2) {
        _paBase[prm_index].y1 = y1;
        _paBase[prm_index].y2 = y2;
    } else {
        _paBase[prm_index].y1 = y2;
        _paBase[prm_index].y2 = y1;
    }

    if (z1 < z2) {
        _paBase[prm_index].z1 = z1;
        _paBase[prm_index].z2 = z2;
    } else {
        _paBase[prm_index].z1 = z2;
        _paBase[prm_index].z2 = z1;
    }

    _paBase[prm_index].hdx = (_paBase[prm_index].x2 - _paBase[prm_index].x1) / 2;
    _paBase[prm_index].hdy = (_paBase[prm_index].y2 - _paBase[prm_index].y1) / 2;
    _paBase[prm_index].hdz = (_paBase[prm_index].z2 - _paBase[prm_index].z1) / 2;

    _paBase[prm_index].cx = _paBase[prm_index].x1 + _paBase[prm_index].hdx;
    _paBase[prm_index].cy = _paBase[prm_index].y1 + _paBase[prm_index].hdy;
    _paBase[prm_index].cz = _paBase[prm_index].z1 + _paBase[prm_index].hdz;

    _paBase[prm_index].rotX = rotX;
    _paBase[prm_index].rotY = rotY;
    _paBase[prm_index].rotZ = rotZ;

    _paBase[prm_index].active = true;
    _paHitArea[prm_index] = _paBase[prm_index];
}

void HitAreaBoxs::enable(int prm_index) {
    _paBase[prm_index].active = true;
    _paHitArea[prm_index].active = true;
}

void HitAreaBoxs::disable(int prm_index) {
    _paBase[prm_index].active = false;
    _paHitArea[prm_index].active = false;
}

bool HitAreaBoxs::isEnable(int prm_index) {
    return _paHitArea[prm_index].active;
}

HitAreaBoxs::~HitAreaBoxs() {
    TRACE("HitAreaBoxs::~HitAreaBoxs() start--->");
    DELETEARR_POSSIBLE_NULL(_paBase);
    DELETEARR_POSSIBLE_NULL(_paHitArea);TRACE("HitAreaBoxs::~HitAreaBoxs() <---end");
}
