#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Spline3D::GgafDx9Spline3D(double prm_paaBase[][3], int num) {
    _bx = NEW double[num];
    _by = NEW double[num];
    _bz = NEW double[num];
    for (int i = 0; i < num; i++) {
        _bx[i] = prm_paaBase[i][0];
        _by[i] = prm_paaBase[i][1];
        _bz[i] = prm_paaBase[i][2];
    }

    _xs.init(_bx, num);
    _ys.init(_by, num);
    _zs.init(_bz, num);
    _num = num;
    _rx = NULL;
    _ry = NULL;
    _rz = NULL;
}

void GgafDx9Spline3D::culc(double prm_accuracy) {
    _rnum = _num/prm_accuracy;
    if (_rx != NULL) {
        DELETEARR_IMPOSSIBLE_NULL(_rx);
        DELETEARR_IMPOSSIBLE_NULL(_ry);
        DELETEARR_IMPOSSIBLE_NULL(_rz);
    }
    _rx = NEW double[_rnum];
    _ry = NEW double[_rnum];
    _rz = NEW double[_rnum];

    int index = 0;
    for (double t = 0.0; t <= _num; t += prm_accuracy) {
        _rx[index] = _xs.culc(t);
        _ry[index] = _ys.culc(t);
        _rz[index] = _zs.culc(t);
        index++;
    }
}

GgafDx9Spline3D::~GgafDx9Spline3D() {
    DELETEARR_IMPOSSIBLE_NULL(_bx);
    DELETEARR_IMPOSSIBLE_NULL(_by);
    DELETEARR_IMPOSSIBLE_NULL(_bz);
    DELETEARR_IMPOSSIBLE_NULL(_rx);
    DELETEARR_IMPOSSIBLE_NULL(_ry);
    DELETEARR_IMPOSSIBLE_NULL(_rz);
}
