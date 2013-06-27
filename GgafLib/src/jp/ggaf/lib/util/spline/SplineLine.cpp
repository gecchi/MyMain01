#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


SplineLine::SplineLine() : GgafObject() {
    _X_basepoint = nullptr;
    _Y_basepoint = nullptr;
    _Z_basepoint = nullptr;
    _num_basepoint = 0;
    _X_compute = nullptr;
    _Y_compute = nullptr;
    _Z_compute = nullptr;
    _rnum = 0;
    _accuracy = 1.0;
}

SplineLine::SplineLine(double prm_paaEstablish[][3], int prm_num, double prm_accuracy) : GgafObject() {
    init(prm_paaEstablish, prm_num, prm_accuracy);
    _accuracy = prm_accuracy;
}

void SplineLine::init(double prm_paaEstablish[][3], int prm_num, double prm_accuracy) {
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
    _X_compute = nullptr;
    _Y_compute = nullptr;
    _Z_compute = nullptr;
    compute(prm_accuracy);
}

void SplineLine::compute(double prm_accuracy) {
    _rnum = _num_basepoint/prm_accuracy;
    if (_X_compute) {
        GGAF_DELETEARR(_X_compute);
        GGAF_DELETEARR(_Y_compute);
        GGAF_DELETEARR(_Z_compute);
    }
    _X_compute = NEW double[_rnum];
    _Y_compute = NEW double[_rnum];
    _Z_compute = NEW double[_rnum];

    int index = 0;
    for (double t = 0.0; t <= (_num_basepoint+0.000001) - 1.0; t += prm_accuracy) { //0.000001 は最後を成立させるため
        _X_compute[index] = _xs.compute(t);
        _Y_compute[index] = _ys.compute(t);
        _Z_compute[index] = _zs.compute(t);
        index++;
    }
    _rnum = index;
}

SplineLine::~SplineLine() {
    _TRACE_("SplineLine::~SplineLine() ");
    GGAF_DELETEARR(_X_basepoint);
    GGAF_DELETEARR(_Y_basepoint);
    GGAF_DELETEARR(_Z_basepoint);
    //イニシャライズされる前に解放されるかもしれない
    GGAF_DELETEARR_NULLABLE(_X_compute);
    GGAF_DELETEARR_NULLABLE(_Y_compute);
    GGAF_DELETEARR_NULLABLE(_Z_compute);
}
