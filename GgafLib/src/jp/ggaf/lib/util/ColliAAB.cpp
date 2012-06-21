#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliAAB::ColliAAB() : GgafDxCollisionPart() {
    _x1 = 0;
    _y1 = 0;
    _z1 = 0;
    _x2 = 0;
    _y2 = 0;
    _z2 = 0;
    _shape_kind = COLLI_AAB;
}

void ColliAAB::set(coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, bool rotX, bool rotY, bool rotZ) {
    if (x1 < x2) {
        _x1 = x1;
        _x2 = x2;
    } else {
        _x1 = x2;
        _x2 = x1;
    }
    if (y1 < y2) {
        _y1 = y1;
        _y2 = y2;
    } else {
        _y1 = y2;
        _y2 = y1;
    }
    if (z1 < z2) {
        _z1 = z1;
        _z2 = z2;
    } else {
        _z1 = z2;
        _z2 = z1;
    }

    //基底クラスメンバの更新
    _dx = (_x2 - _x1);
    _dy = (_y2 - _y1);
    _dz = (_z2 - _z1);
    _hdx = _dx / 2;
    _hdy = _dy / 2;
    _hdz = _dz / 2;
    _base_cx = _x1 + _hdx;
    _base_cy = _y1 + _hdy;
    _base_cz = _z1 + _hdz;
    _cx = _base_cx;
    _cy = _base_cy;
    _cz = _base_cz;
    _rotX = rotX;
    _rotY = rotY;
    _rotZ = rotZ;
    //境界領域は全く同じ
    _aab_x1 = _x1;
    _aab_y1 = _y1;
    _aab_z1 = _z1;
    _aab_x2 = _x2;
    _aab_y2 = _y2;
    _aab_z2 = _z2;

    _is_valid_flg = true;
}

void ColliAAB::rotateRxRzRy(angle rX, angle rY, angle rZ) {
    s_ang s_RX, s_RY, s_RZ;
    coord wk_cx, wk_cy, wk_cz;
    //当たり判定領域軸回転
    s_RX = rX / SANG_RATE;
    s_RY = rY / SANG_RATE;
    s_RZ = rZ / SANG_RATE;
    wk_cx = _base_cx;
    wk_cy = _base_cy;
    wk_cz = _base_cz;

    if (_rotX) {
        _cy = (wk_cy * UTIL::COS[s_RX]) - (wk_cz * UTIL::SIN[s_RX]);
        _cz = (wk_cy * UTIL::SIN[s_RX]) + (wk_cz * UTIL::COS[s_RX]);
        wk_cy = _cy;
        wk_cz = _cz;
    }

    //
    if (_rotZ) {
        _cx = (wk_cx * UTIL::COS[s_RZ]) - (wk_cy * UTIL::SIN[s_RZ]);
        _cy = (wk_cx * UTIL::SIN[s_RZ]) + (wk_cy * UTIL::COS[s_RZ]);
        wk_cx = _cx;
        wk_cy = _cy;
    }

    if (_rotY) {
//            _cz = (wk_cz * UTIL::COS[s_RY]) - (wk_cx * UTIL::SIN[s_RY]);
//            _cx = (wk_cz * UTIL::SIN[s_RY]) + (wk_cx * UTIL::COS[s_RY]);
        //↑普通はこう考えるけど
        //RYは、(1,0,0)を０度として、Y軸の方向を向いて反時計回りなのでこうなる
        _cx = (wk_cx * UTIL::COS[D360SANG-s_RY]) - (wk_cz * UTIL::SIN[D360SANG-s_RY]);
        _cz = (wk_cx * UTIL::SIN[D360SANG-s_RY]) + (wk_cz * UTIL::COS[D360SANG-s_RY]);
        wk_cz = _cz;
        wk_cx = _cx;
    }

    _x1 = wk_cx - _hdx;
    _y1 = wk_cy - _hdy;
    _z1 = wk_cz - _hdz;
    _x2 = wk_cx + _hdx;
    _y2 = wk_cy + _hdy;
    _z2 = wk_cz + _hdz;
    //境界領域も更新
    _aab_x1 = _x1;
    _aab_y1 = _y1;
    _aab_z1 = _z1;
    _aab_x2 = _x2;
    _aab_y2 = _y2;
    _aab_z2 = _z2;
}


ColliAAB::~ColliAAB() {
    TRACE("ColliAAB::~ColliAAB()");
}
