#include "stdafx.h"
#include "jp/ggaf/lib/util/ColliSphere.h"

#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliSphere::ColliSphere() : GgafDxCollisionPart() {
    _x = 0;
    _y = 0;
    _z = 0;
    _r = 0;
    _rr = 0.0;
    _shape_kind = COLLI_SPHERE;
}

void ColliSphere::set(coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z) {
    _x = x;
    _y = y;
    _z = z;
    _r = r;
    _rr = 1.0*r*r;
    //基底クラスメンバの更新
    _dx = _r*2;
    _dy = _r*2;
    _dz = _r*2;
    _hdx = _dx / 2;
    _hdy = _dy / 2;
    _hdz = _dz / 2;
    _base_cx = _x;
    _base_cy = _y;
    _base_cz = _z;
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
    //境界領域
    _aab_x1 = _x - _r;
    _aab_y1 = _y - _r;
    _aab_z1 = _z - _r;
    _aab_x2 = _x + _r;
    _aab_y2 = _y + _r;
    _aab_z2 = _z + _r;

    _is_valid_flg = true;
}

void ColliSphere::rotateRxRzRy(angle rx, angle ry, angle rz) {
    s_ang s_rx, s_ry, s_rz;
    int wk_cx, wk_cy, wk_cz;
    //当たり判定領域軸回転
    s_rx = rx * (1.0 / SANG_RATE);
    s_ry = ry * (1.0 / SANG_RATE);
    s_rz = rz * (1.0 / SANG_RATE);
    wk_cx = _base_cx;
    wk_cy = _base_cy;
    wk_cz = _base_cz;

    if (_rot_x) {
        _cy = (wk_cy * UTIL::COS[s_rx]) - (wk_cz * UTIL::SIN[s_rx]);
        _cz = (wk_cy * UTIL::SIN[s_rx]) + (wk_cz * UTIL::COS[s_rx]);
        wk_cy = _cy;
        wk_cz = _cz;
    }

    //
    if (_rot_z) {
        _cx = (wk_cx * UTIL::COS[s_rz]) - (wk_cy * UTIL::SIN[s_rz]);
        _cy = (wk_cx * UTIL::SIN[s_rz]) + (wk_cy * UTIL::COS[s_rz]);
        wk_cx = _cx;
        wk_cy = _cy;
    }

    if (_rot_y) {
//            _cz = (wk_cz * UTIL::COS[s_ry]) - (wk_cx * UTIL::SIN[s_ry]);
//            _cx = (wk_cz * UTIL::SIN[s_ry]) + (wk_cx * UTIL::COS[s_ry]);
        //↑こうかと一瞬思ったが
        //RYは、(1,0,0)を０度として、Y軸の方向を向いて反時計回りなのでこうなる
        _cx = (wk_cx * UTIL::COS[D360SANG-s_ry]) - (wk_cz * UTIL::SIN[D360SANG-s_ry]);
        _cz = (wk_cx * UTIL::SIN[D360SANG-s_ry]) + (wk_cz * UTIL::COS[D360SANG-s_ry]);
        wk_cz = _cz;
        wk_cx = _cx;
    }

    _x = wk_cx;
    _y = wk_cy;
    _z = wk_cz;
    //境界領域も更新
    _aab_x1 = _x - _r;
    _aab_y1 = _y - _r;
    _aab_z1 = _z - _r;
    _aab_x2 = _x + _r;
    _aab_y2 = _y + _r;
    _aab_z2 = _z + _r;
}


ColliSphere::~ColliSphere() {
}
