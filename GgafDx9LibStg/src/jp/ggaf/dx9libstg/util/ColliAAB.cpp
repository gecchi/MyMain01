#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ColliAAB::ColliAAB() : GgafDx9CollisionPart() {
    _x1 = 0;
    _y1 = 0;
    _z1 = 0;
    _x2 = 0;
    _y2 = 0;
    _z2 = 0;
    _shape_kind = COLLI_AABB;
}

void ColliAAB::set(int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ) {
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
    _aabb_x1 = _x1;
    _aabb_y1 = _y1;
    _aabb_z1 = _z1;
    _aabb_x2 = _x2;
    _aabb_y2 = _y2;
    _aabb_z2 = _z2;

    _is_valid_flg = true;
}

bool ColliAAB::rotate(angle rX, angle rY, angle rZ) {
    if (_rotX || _rotY || _rotZ) {
        s_ang s_RX, s_RY, s_RZ;
        int wk_cx, wk_cy, wk_cz;
        //当たり判定領域軸回転
        s_RX = rX / ANGLE_RATE;
        s_RY = rY / ANGLE_RATE;
        s_RZ = rZ / ANGLE_RATE;
        wk_cx = _base_cx;
        wk_cy = _base_cy;
        wk_cz = _base_cz;

        if (_rotX) {
            _cy = (wk_cy * GgafDx9Util::COS[s_RX]) - (wk_cz * GgafDx9Util::SIN[s_RX]);
            _cz = (wk_cy * GgafDx9Util::SIN[s_RX]) + (wk_cz * GgafDx9Util::COS[s_RX]);
            wk_cy = _cy;
            wk_cz = _cz;
        }

        if (_rotY) {
            _cz = (wk_cz * GgafDx9Util::COS[s_RY]) - (wk_cx * GgafDx9Util::SIN[s_RY]);
            _cx = (wk_cz * GgafDx9Util::SIN[s_RY]) + (wk_cx * GgafDx9Util::COS[s_RY]);
            wk_cz = _cz;
            wk_cx = _cx;
        }

        if (_rotZ) {
            _cx = (wk_cx * GgafDx9Util::COS[s_RZ]) - (wk_cy * GgafDx9Util::SIN[s_RZ]);
            _cy = (wk_cx * GgafDx9Util::SIN[s_RZ]) + (wk_cy * GgafDx9Util::COS[s_RZ]);
            wk_cx = _cx;
            wk_cy = _cy;
        }

        _x1 = wk_cx - _hdx;
        _y1 = wk_cy - _hdy;
        _z1 = wk_cz - _hdz;
        _x2 = wk_cx + _hdx;
        _y2 = wk_cy + _hdy;
        _z2 = wk_cz + _hdz;
        //境界領域も更新
        _aabb_x1 = _x1;
        _aabb_y1 = _y1;
        _aabb_z1 = _z1;
        _aabb_x2 = _x2;
        _aabb_y2 = _y2;
        _aabb_z2 = _z2;
        return true;
    } else {
        return false;
    }
}


ColliAAB::~ColliAAB() {
    TRACE("ColliAAB::~ColliAAB()");
}
