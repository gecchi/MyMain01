#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

HitAreaBoxs::HitAreaBoxs(int prm_iAreaNum) : GgafDx9HitArea(prm_iAreaNum) {
    if (prm_iAreaNum > 0) {
        _paBaseBox = NEW Box[prm_iAreaNum];
        _paHitAreaBox = NEW Box[prm_iAreaNum];
    } else {
        throwGgafCriticalException("HitAreaBoxs::HitAreaBoxs Box数が不正。prm_iAreaNum="<<prm_iAreaNum);
    }
}

void HitAreaBoxs::setBox(int prm_iArea, int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ) {
    if (_iAreaNum < prm_iArea) {
        throwGgafCriticalException("HitAreaBoxs::setBox() 要素オーバー。_iAreaNum="<<_iAreaNum<<"/prm_iArea="<<prm_iArea);
    }
    if (x1 < x2) {
        _paBaseBox[prm_iArea].x1 = x1;
        _paBaseBox[prm_iArea].x2 = x2;
    } else {
        _paBaseBox[prm_iArea].x1 = x2;
        _paBaseBox[prm_iArea].x2 = x1;
    }

    if (y1 < y2) {
        _paBaseBox[prm_iArea].y1 = y1;
        _paBaseBox[prm_iArea].y2 = y2;
    } else {
        _paBaseBox[prm_iArea].y1 = y2;
        _paBaseBox[prm_iArea].y2 = y1;
    }

    if (z1 < z2) {
        _paBaseBox[prm_iArea].z1 = z1;
        _paBaseBox[prm_iArea].z2 = z2;
    } else {
        _paBaseBox[prm_iArea].z1 = z2;
        _paBaseBox[prm_iArea].z2 = z1;
    }

    _paBaseBox[prm_iArea].hdx = (_paBaseBox[prm_iArea].x2 - _paBaseBox[prm_iArea].x1) / 2;
    _paBaseBox[prm_iArea].hdy = (_paBaseBox[prm_iArea].y2 - _paBaseBox[prm_iArea].y1) / 2;
    _paBaseBox[prm_iArea].hdz = (_paBaseBox[prm_iArea].z2 - _paBaseBox[prm_iArea].z1) / 2;

    _paBaseBox[prm_iArea].cx = _paBaseBox[prm_iArea].x1 + _paBaseBox[prm_iArea].hdx;
    _paBaseBox[prm_iArea].cy = _paBaseBox[prm_iArea].y1 + _paBaseBox[prm_iArea].hdy;
    _paBaseBox[prm_iArea].cz = _paBaseBox[prm_iArea].z1 + _paBaseBox[prm_iArea].hdz;

    _paBaseBox[prm_iArea].rotX = rotX;
    _paBaseBox[prm_iArea].rotY = rotY;
    _paBaseBox[prm_iArea].rotZ = rotZ;

    _paBaseBox[prm_iArea].is_valid_flg = true;
    _paHitAreaBox[prm_iArea] = _paBaseBox[prm_iArea];
}



HitAreaBoxs::~HitAreaBoxs() {
    TRACE("HitAreaBoxs::~HitAreaBoxs()");
    //キャラはあっても判定はないかもしれない
    DELETEARR_POSSIBLE_NULL(_paBaseBox);
    DELETEARR_POSSIBLE_NULL(_paHitAreaBox)
}
