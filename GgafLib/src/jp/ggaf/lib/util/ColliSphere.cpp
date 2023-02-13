#include "jp/ggaf/lib/util/ColliSphere.h"

#include "jp/ggaf/lib/util/StgUtil.h"



using namespace GgafLib;

ColliSphere::ColliSphere() : GgafDx::CollisionPart() {
    _r = 0;
    _rr = 0.0;
    _shape_kind = COLLI_SPHERE;
}

void ColliSphere::set(coord x, coord y, coord z, coord r, bool rot_x, bool rot_y, bool rot_z) {
    _r = r;
    _rr = 1.0*r*r;
    //基底クラスメンバの更新
    _dx = _r*2;
    _dy = _r*2;
    _dz = _r*2;
    _hdx = _dx / 2;
    _hdy = _dy / 2;
    _hdz = _dz / 2;
    _base_cx = x;
    _base_cy = y;
    _base_cz = z;
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
    _x1 = _cx - _r;
    _y1 = _cy - _r;
    _z1 = _cz - _r;
    _x2 = _cx + _r;
    _y2 = _cy + _r;
    _z2 = _cz + _r;
}

void ColliSphere::changeR(coord r) {
    _r = r;
    _rr = 1.0*r*r;
    _dx = _r*2;
    _dy = _r*2;
    _dz = _r*2;
    _hdx = _dx / 2;
    _hdy = _dy / 2;
    _hdz = _dz / 2;
    //境界領域
    _x1 = _cx - _r;
    _y1 = _cy - _r;
    _z1 = _cz - _r;
    _x2 = _cx + _r;
    _y2 = _cy + _r;
    _z2 = _cz + _r;
}

void ColliSphere::rotateRxRzRy(angle rx, angle ry, angle rz) {
//    s_ang s_rx, s_ry, s_rz;
    int wk_cx, wk_cy, wk_cz;
    //当たり判定領域軸回転
    wk_cx = _base_cx;
    wk_cy = _base_cy;
    wk_cz = _base_cz;

    if (_rot_x) {
        _cy = (wk_cy * ANG_COS(rx)) - (wk_cz * ANG_SIN(rx));
        _cz = (wk_cy * ANG_SIN(rx)) + (wk_cz * ANG_COS(rx));
        wk_cy = _cy;
        wk_cz = _cz;
    }
    if (_rot_z) {
        _cx = (wk_cx * ANG_COS(rz)) - (wk_cy * ANG_SIN(rz));
        _cy = (wk_cx * ANG_SIN(rz)) + (wk_cy * ANG_COS(rz));
        wk_cx = _cx;
        wk_cy = _cy;
    }
    if (_rot_y) {
//            _cz = (wk_cz * ANG_COS(ry)) - (wk_cx * ANG_SIN(ry));
//            _cx = (wk_cz * ANG_SIN(ry)) + (wk_cx * ANG_COS(s_ry));
        //↑こうかと一瞬思ったが
        //RYは、(1,0,0)を０度として、Y軸の方向を向いて反時計回りなのでこうなる
        _cx = (wk_cx * ANG_COS(D360ANG-ry)) - (wk_cz * ANG_SIN(D360ANG-ry));
        _cz = (wk_cx * ANG_SIN(D360ANG-ry)) + (wk_cz * ANG_COS(D360ANG-ry));
        wk_cz = _cz;
        wk_cx = _cx;
    }

    //境界領域も更新
    _x1 = wk_cx - _r;
    _y1 = wk_cy - _r;
    _z1 = wk_cz - _r;
    _x2 = wk_cx + _r;
    _y2 = wk_cy + _r;
    _z2 = wk_cz + _r;
}

ColliSphere::~ColliSphere() {
}
