#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Spline3D::GgafDx9Spline3D(double prm_paaEstablish[][3], int prm_num) {
    _TRACE_("prm_num="<<prm_num);
    _num_establish = prm_num;
    _X_establish = NEW double[prm_num];
    _Y_establish = NEW double[prm_num];
    _Z_establish = NEW double[prm_num];
    for (int i = 0; i < prm_num; i++) {
        _X_establish[i] = prm_paaEstablish[i][0];
        _Y_establish[i] = prm_paaEstablish[i][1];
        _Z_establish[i] = prm_paaEstablish[i][2];
    }
    _xs.init(_X_establish, prm_num);
    _ys.init(_Y_establish, prm_num);
    _zs.init(_Z_establish, prm_num);

    _X_compute = NULL;
    _Y_compute = NULL;
    _Z_compute = NULL;
}

void GgafDx9Spline3D::compute(double prm_accuracy) {
    _rnum = _num_establish/prm_accuracy;
    if (_X_compute != NULL) {
        DELETEARR_IMPOSSIBLE_NULL(_X_compute);
        DELETEARR_IMPOSSIBLE_NULL(_Y_compute);
        DELETEARR_IMPOSSIBLE_NULL(_Z_compute);
    }
    _X_compute = NEW double[_rnum];
    _Y_compute = NEW double[_rnum];
    _Z_compute = NEW double[_rnum];

    int index = 0;
    for (double t = 0.0; t <= _num_establish-1.0; t += prm_accuracy) {
        _X_compute[index] = _xs.compute(t);
        _Y_compute[index] = _ys.compute(t);
        _Z_compute[index] = _zs.compute(t);
        index++;
    }
    _rnum = index;
}

GgafDx9Spline3D::~GgafDx9Spline3D() {
    DELETEARR_IMPOSSIBLE_NULL(_X_establish);
    DELETEARR_IMPOSSIBLE_NULL(_Y_establish);
    DELETEARR_IMPOSSIBLE_NULL(_Z_establish);
    DELETEARR_POSSIBLE_NULL(_X_compute);
    DELETEARR_POSSIBLE_NULL(_Y_compute);
    DELETEARR_POSSIBLE_NULL(_Z_compute);
}
