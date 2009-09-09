#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

HitAreaBoxs::HitAreaBoxs(int prm_iAreaNum) : GgafDx9HitArea(prm_iAreaNum) {
    if (prm_iAreaNum > 0) {
        _paBase = NEW Box[prm_iAreaNum];
        _paHitArea = NEW Box[prm_iAreaNum];
    } else {
        throwGgafCriticalException("HitAreaBoxs::HitAreaBoxs Box数が不正。prm_iAreaNum="<<prm_iAreaNum);
    }
}

void HitAreaBoxs::setBox(int prm_iArea, int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ) {
    if (_iAreaNum < prm_iArea) {
        throwGgafCriticalException("HitAreaBoxs::setBox() 要素オーバー。_iAreaNum="<<_iAreaNum<<"/prm_iArea="<<prm_iArea);
    }
    if (x1 < x2) {
        _paBase[prm_iArea].x1 = x1;
        _paBase[prm_iArea].x2 = x2;
    } else {
        _paBase[prm_iArea].x1 = x2;
        _paBase[prm_iArea].x2 = x1;
    }

    if (y1 < y2) {
        _paBase[prm_iArea].y1 = y1;
        _paBase[prm_iArea].y2 = y2;
    } else {
        _paBase[prm_iArea].y1 = y2;
        _paBase[prm_iArea].y2 = y1;
    }

    if (z1 < z2) {
        _paBase[prm_iArea].z1 = z1;
        _paBase[prm_iArea].z2 = z2;
    } else {
        _paBase[prm_iArea].z1 = z2;
        _paBase[prm_iArea].z2 = z1;
    }

    _paBase[prm_iArea].hdx = (_paBase[prm_iArea].x2 - _paBase[prm_iArea].x1) / 2;
    _paBase[prm_iArea].hdy = (_paBase[prm_iArea].y2 - _paBase[prm_iArea].y1) / 2;
    _paBase[prm_iArea].hdz = (_paBase[prm_iArea].z2 - _paBase[prm_iArea].z1) / 2;

    _paBase[prm_iArea].cx = _paBase[prm_iArea].x1 + _paBase[prm_iArea].hdx;
    _paBase[prm_iArea].cy = _paBase[prm_iArea].y1 + _paBase[prm_iArea].hdy;
    _paBase[prm_iArea].cz = _paBase[prm_iArea].z1 + _paBase[prm_iArea].hdz;

    _paBase[prm_iArea].rotX = rotX;
    _paBase[prm_iArea].rotY = rotY;
    _paBase[prm_iArea].rotZ = rotZ;

    //_paBase[prm_iArea].active = true;
    _paHitArea[prm_iArea] = _paBase[prm_iArea];
}
//
//void HitAreaBoxs::enable(int prm_iArea) {
//    _paBase[prm_iArea].active = true;
//    _paHitArea[prm_iArea].active = true;
//}
//
//void HitAreaBoxs::disable(int prm_iArea) {
//    _paBase[prm_iArea].active = false;
//    _paHitArea[prm_iArea].active = false;
//}
//
//bool HitAreaBoxs::isEnable(int prm_iArea) {
//    return _paHitArea[prm_iArea].active;
//}

HitAreaBoxs::~HitAreaBoxs() {
    TRACE("HitAreaBoxs::~HitAreaBoxs()");
    DELETEARR_POSSIBLE_NULL(_paBase);
    DELETEARR_POSSIBLE_NULL(_paHitArea)
}
