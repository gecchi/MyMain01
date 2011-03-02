#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ColliSphere::ColliSphere() : GgafDx9CollisionPart() {
    _x = 0;
    _y = 0;
    _z = 0;
    _r = 0;
    _shape_kind = COLLI_SPHERE;
}

void ColliSphere::set(int x, int y, int z, int r, bool rotX, bool rotY, bool rotZ) {
    _x = x;
    _y = y;
    _z = z;
    _r = r;

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
    _rotX = rotX;
    _rotY = rotY;
    _rotZ = rotZ;
    //境界領域
    _aab_x1 = _x - _r;
    _aab_y1 = _y - _r;
    _aab_z1 = _z - _r;
    _aab_x2 = _x + _r;
    _aab_y2 = _y + _r;
    _aab_z2 = _z + _r;

    _is_valid_flg = true;
}

void ColliSphere::rotateRxRzRy(angle rX, angle rY, angle rZ) {
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

    //
    if (_rotZ) {
        _cx = (wk_cx * GgafDx9Util::COS[s_RZ]) - (wk_cy * GgafDx9Util::SIN[s_RZ]);
        _cy = (wk_cx * GgafDx9Util::SIN[s_RZ]) + (wk_cy * GgafDx9Util::COS[s_RZ]);
        wk_cx = _cx;
        wk_cy = _cy;
    }

    if (_rotY) {
//            _cz = (wk_cz * GgafDx9Util::COS[s_RY]) - (wk_cx * GgafDx9Util::SIN[s_RY]);
//            _cx = (wk_cz * GgafDx9Util::SIN[s_RY]) + (wk_cx * GgafDx9Util::COS[s_RY]);
        //↑普通はこう考えるけど
        //RYは、(1,0,0)を０度として、Y軸の方向を向いて反時計回りなのでこうなる
        _cx = (wk_cx * GgafDx9Util::COS[S_ANG360-s_RY]) - (wk_cz * GgafDx9Util::SIN[S_ANG360-s_RY]);
        _cz = (wk_cx * GgafDx9Util::SIN[S_ANG360-s_RY]) + (wk_cz * GgafDx9Util::COS[S_ANG360-s_RY]);
        wk_cz = _cz;
        wk_cx = _cx;
    }



    _x = wk_cx;
    _y = wk_cy;
    _z = wk_cz;
    //_r = r;
    //境界領域も更新
    _aab_x1 = _x - _r;
    _aab_y1 = _y - _r;
    _aab_z1 = _z - _r;
    _aab_x2 = _x + _r;
    _aab_y2 = _y + _r;
    _aab_z2 = _z + _r;
}


ColliSphere::~ColliSphere() {
    TRACE("ColliSphere::~ColliSphere()");
}
