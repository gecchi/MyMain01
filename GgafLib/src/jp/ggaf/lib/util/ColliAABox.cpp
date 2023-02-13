#include "jp/ggaf/lib/util/ColliAABox.h"

#include "jp/ggaf/lib/util/StgUtil.h"



using namespace GgafLib;

ColliAABox::ColliAABox() : GgafDx::CollisionPart() {
    _shape_kind = COLLI_AABOX;
    _pos_info = 0;
}

void ColliAABox::set(coord x1, coord y1, coord z1, coord x2, coord y2, coord z2, bool rot_x, bool rot_y, bool rot_z) {
    _pos_info = 0;
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
    _rot_x = rot_x;
    _rot_y = rot_y;
    _rot_z = rot_z;
    if (_rot_x || _rot_y || _rot_z) {
        _rot = true;
    } else {
        _rot = false;
    }
}

void ColliAABox::movePos(coord cx, coord cy, coord cz) {
    coord dx = cx - _base_cx;
    coord dy = cy - _base_cy;
    coord dz = cz - _base_cz;
    _x1 += dx;
    _y1 += dy;
    _z1 += dz;
    _x2 += dx;
    _y2 += dy;
    _z2 += dz;
    _cx += dx;
    _cy += dy;
    _cz += dz;
    _base_cx = cx;
    _base_cy = cy;
    _base_cz = cz;
}

void ColliAABox::rotateRxRzRy(angle rx, angle ry, angle rz) {
//    s_ang s_rx = rx * (1.0 / SANG_RATE);
//    s_ang s_ry = ry * (1.0 / SANG_RATE);
//    s_ang s_rz = rz * (1.0 / SANG_RATE);
    //当たり判定領域軸回転
    coord wk_cx = _base_cx;
    coord wk_cy = _base_cy;
    coord wk_cz = _base_cz;

    if (_rot_x) {
        _cy = (wk_cy * ANG_COS(rx)) - (wk_cz * ANG_SIN(rx));
        _cz = (wk_cy * ANG_SIN(rx)) + (wk_cz * ANG_COS(rx));
        wk_cy = _cy;
        wk_cz = _cz;
    }

    //
    if (_rot_z) {
        _cx = (wk_cx * ANG_COS(rz)) - (wk_cy * ANG_SIN(rz));
        _cy = (wk_cx * ANG_SIN(rz)) + (wk_cy * ANG_COS(rz));
        wk_cx = _cx;
        wk_cy = _cy;
    }

    if (_rot_y) {
//            _cz = (wk_cz * UTIL::COS[s_ry]) - (wk_cx * UTIL::SIN[s_ry]);
//            _cx = (wk_cz * UTIL::SIN[s_ry]) + (wk_cx * UTIL::COS[s_ry]);
        //↑こうかと一瞬思ったが
        //RYは、(1,0,0)を０度として、Y軸の方向を向いて反時計回りなのでこうなる
        _cx = (wk_cx * ANG_COS(D360ANG-ry)) - (wk_cz * ANG_SIN(D360ANG-ry));
        _cz = (wk_cx * ANG_SIN(D360ANG-ry)) + (wk_cz * ANG_COS(D360ANG-ry));
        wk_cz = _cz;
        wk_cx = _cx;
    }

    //境界領域も更新
    _x1 = wk_cx - _hdx;
    _y1 = wk_cy - _hdy;
    _z1 = wk_cz - _hdz;
    _x2 = wk_cx + _hdx;
    _y2 = wk_cy + _hdy;
    _z2 = wk_cz + _hdz;
}

ColliAABox::~ColliAABox() {
}
