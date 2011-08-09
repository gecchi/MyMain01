#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


Spline3D::Spline3D() {
    _X_basepoint = NULL;
    _Y_basepoint = NULL;
    _Z_basepoint = NULL;
    _num_basepoint = 0;
    _X_compute = NULL;
    _Y_compute = NULL;
    _Z_compute = NULL;
    _rnum = 0;
    _accuracy = 1.0;
}


Spline3D::Spline3D(double prm_paaEstablish[][3], int prm_num, double prm_accuracy) {
    init(prm_paaEstablish, prm_num, prm_accuracy);
    _accuracy = prm_accuracy;
}


void Spline3D::init(double prm_paaEstablish[][3], int prm_num, double prm_accuracy) {
    _num_basepoint = prm_num;
    _X_basepoint = NEW double[prm_num];
    _Y_basepoint = NEW double[prm_num];
    _Z_basepoint = NEW double[prm_num];
    for (int i = 0; i < prm_num; i++) {
        _X_basepoint[i] = prm_paaEstablish[i][0];
        _Y_basepoint[i] = prm_paaEstablish[i][1];
        _Z_basepoint[i] = prm_paaEstablish[i][2];
    }
    _xs.init(_X_basepoint, prm_num);
    _ys.init(_Y_basepoint, prm_num);
    _zs.init(_Z_basepoint, prm_num);
    _X_compute = NULL;
    _Y_compute = NULL;
    _Z_compute = NULL;
    compute(prm_accuracy);
}

void Spline3D::compute(double prm_accuracy) {
    _rnum = _num_basepoint/prm_accuracy;
    if (_X_compute) {
        DELETEARR_IMPOSSIBLE_NULL(_X_compute);
        DELETEARR_IMPOSSIBLE_NULL(_Y_compute);
        DELETEARR_IMPOSSIBLE_NULL(_Z_compute);
    }
    _X_compute = NEW double[_rnum];
    _Y_compute = NEW double[_rnum];
    _Z_compute = NEW double[_rnum];

    int index = 0;
    for (double t = 0.0; t <= _num_basepoint-1.0; t += prm_accuracy) {
        _X_compute[index] = _xs.compute(t);
        _Y_compute[index] = _ys.compute(t);
        _Z_compute[index] = _zs.compute(t);
        index++;
    }
    _rnum = index;
}

Spline3D::~Spline3D() {
    _TRACE_("Spline3D::~Spline3D() !!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    DELETEARR_IMPOSSIBLE_NULL(_X_basepoint);
    DELETEARR_IMPOSSIBLE_NULL(_Y_basepoint);
    DELETEARR_IMPOSSIBLE_NULL(_Z_basepoint);
    //イニシャライズされる前に解放されるかもしれない
    DELETEARR_POSSIBLE_NULL(_X_compute);
    DELETEARR_POSSIBLE_NULL(_Y_compute);
    DELETEARR_POSSIBLE_NULL(_Z_compute);
}
