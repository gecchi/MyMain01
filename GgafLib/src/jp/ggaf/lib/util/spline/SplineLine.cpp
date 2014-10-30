#include "jp/ggaf/lib/util/spline/SplineLine.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


SplineLine::SplineLine() : GgafObject() {
    _x_basepoint = nullptr;
    _y_basepoint = nullptr;
    _z_basepoint = nullptr;
    _num_basepoint = 0;
    _x_compute = nullptr;
    _y_compute = nullptr;
    _z_compute = nullptr;
    _rnum = 0;
    _accuracy = 1.0;
}

SplineLine::SplineLine(double prm_paaEstablish[][3], int prm_num, double prm_accuracy) : GgafObject() {
    init(prm_paaEstablish, prm_num, prm_accuracy);
}

SplineLine::SplineLine(double prm_paaEstablish[][3], int prm_num, double prm_accuracy, RotMat& prm_rotmat) : GgafObject() {
    init(prm_paaEstablish, prm_num, prm_accuracy, prm_rotmat);
}

void SplineLine::init(double prm_paaEstablish[][3], int prm_num, double prm_accuracy) {
    _num_basepoint = prm_num;
    _accuracy = prm_accuracy;
    _x_basepoint = NEW double[prm_num];
    _y_basepoint = NEW double[prm_num];
    _z_basepoint = NEW double[prm_num];
    for (int i = 0; i < prm_num; i++) {
        _x_basepoint[i] = prm_paaEstablish[i][0];
        _y_basepoint[i] = prm_paaEstablish[i][1];
        _z_basepoint[i] = prm_paaEstablish[i][2];
    }
    _xs.init(_x_basepoint, prm_num);
    _ys.init(_y_basepoint, prm_num);
    _zs.init(_z_basepoint, prm_num);
    _x_compute = nullptr;
    _y_compute = nullptr;
    _z_compute = nullptr;
    compute(prm_accuracy);
}

void SplineLine::init(double prm_paaEstablish[][3], int prm_num, double prm_accuracy, RotMat& prm_rotmat) {
    _num_basepoint = prm_num;
    _accuracy = prm_accuracy;
    _x_basepoint = NEW double[prm_num];
    _y_basepoint = NEW double[prm_num];
    _z_basepoint = NEW double[prm_num];
    double x,y,z;
    for (int i = 0; i < prm_num; i++) {
        //x*_11 + y*_21 + z*_31 + _41 , x*_12 + y*_22 + z*_32 + _42, x*_13 + y*_23 + z*_33 + _43
        x = prm_paaEstablish[i][0];
        y = prm_paaEstablish[i][1];
        z = prm_paaEstablish[i][2];
        _x_basepoint[i] = x*prm_rotmat._11 + y*prm_rotmat._21 + z*prm_rotmat._31 + prm_rotmat._41;
        _y_basepoint[i] = x*prm_rotmat._12 + y*prm_rotmat._22 + z*prm_rotmat._32 + prm_rotmat._42;
        _z_basepoint[i] = x*prm_rotmat._13 + y*prm_rotmat._23 + z*prm_rotmat._33 + prm_rotmat._43;
    }
    _xs.init(_x_basepoint, prm_num);
    _ys.init(_y_basepoint, prm_num);
    _zs.init(_z_basepoint, prm_num);
    _x_compute = nullptr;
    _y_compute = nullptr;
    _z_compute = nullptr;
    compute(prm_accuracy);
}

void SplineLine::compute(double prm_accuracy) {
    _rnum = _num_basepoint/prm_accuracy;
    if (_x_compute) {
        GGAF_DELETEARR(_x_compute);
        GGAF_DELETEARR(_y_compute);
        GGAF_DELETEARR(_z_compute);
    }
    _x_compute = NEW double[_rnum];
    _y_compute = NEW double[_rnum];
    _z_compute = NEW double[_rnum];

    int index = 0;
    for (double t = 0.0; t <= (_num_basepoint+0.000001) - 1.0; t += prm_accuracy) { //0.000001 は最後を成立させるため
        _x_compute[index] = _xs.compute(t);
        _y_compute[index] = _ys.compute(t);
        _z_compute[index] = _zs.compute(t);
        index++;
    }
    _rnum = index;
}

SplineLine::~SplineLine() {
    _DTRACE_("SplineLine::~SplineLine() ");
    GGAF_DELETEARR(_x_basepoint);
    GGAF_DELETEARR(_y_basepoint);
    GGAF_DELETEARR(_z_basepoint);
    //イニシャライズされる前に解放されるかもしれない
    GGAF_DELETEARR_NULLABLE(_x_compute);
    GGAF_DELETEARR_NULLABLE(_y_compute);
    GGAF_DELETEARR_NULLABLE(_z_compute);
}
