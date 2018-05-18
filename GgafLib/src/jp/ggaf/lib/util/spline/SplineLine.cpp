#include "jp/ggaf/lib/util/spline/SplineLine.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/lib/util/StgUtil.h"

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
    _rotmat = prm_rotmat;
    init(prm_paaEstablish, prm_num, prm_accuracy);
}

void SplineLine::init(double prm_paaEstablish[][3], int prm_num, double prm_accuracy) {
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
        _x_basepoint[i] = x*_rotmat._11 + y*_rotmat._21 + z*_rotmat._31 + _rotmat._41;
        _y_basepoint[i] = x*_rotmat._12 + y*_rotmat._22 + z*_rotmat._32 + _rotmat._42;
        _z_basepoint[i] = x*_rotmat._13 + y*_rotmat._23 + z*_rotmat._33 + _rotmat._43;
    }
    _xs.init(_x_basepoint, prm_num);
    _ys.init(_y_basepoint, prm_num);
    _zs.init(_z_basepoint, prm_num);
    _x_compute = nullptr;
    _y_compute = nullptr;
    _z_compute = nullptr;
    compute();
}

void SplineLine::compute() {
    _rnum = _num_basepoint/_accuracy;
    if (_x_compute) {
        GGAF_DELETEARR(_x_compute);
        GGAF_DELETEARR(_y_compute);
        GGAF_DELETEARR(_z_compute);
    }
    _x_compute = NEW double[_rnum];
    _y_compute = NEW double[_rnum];
    _z_compute = NEW double[_rnum];

    int index = 0;
    for (double t = 0.0; t <= (_num_basepoint+0.000001) - 1.0; t += _accuracy) { //0.000001 は最後を成立させるため
#ifdef MY_DEBUG
        if (_rnum < index+1) {
            throwGgafCriticalException("補間点配列の要素数の範囲外指定です。_rnum="<<_rnum<<" index="<<index<<" t="<<t);
        }
#endif
        _x_compute[index] = _xs.compute(t);
        _y_compute[index] = _ys.compute(t);
        _z_compute[index] = _zs.compute(t);
        index++;
    }
    _rnum = index;
}

void SplineLine::rotation(angle prm_rx, angle prm_ry, angle prm_rz) {
    const double sinRx = ANG_SIN(prm_rx);
    const double cosRx = ANG_COS(prm_rx);
    const double sinRy = ANG_SIN(prm_ry);
    const double cosRy = ANG_COS(prm_ry);
    const double sinRz = ANG_SIN(prm_rz);
    const double cosRz = ANG_COS(prm_rz);
    for (int t = 0; t < _rnum; t ++) {
        double x = _x_compute[t];
        double y = _y_compute[t];
        double z = _z_compute[t];
        _x_compute[t] = x*cosRz*cosRy + y*(cosRx*-sinRz*cosRy + sinRx*sinRy) + z*(-sinRx*-sinRz*cosRy + cosRx*sinRy);
        _y_compute[t] = x*sinRz + y*cosRx*cosRz + z*-sinRx*cosRz;
        _z_compute[t] = x*cosRz*-sinRy + y*(cosRx*-sinRz*-sinRy + sinRx*cosRy) + z*(-sinRx*-sinRz*-sinRy + cosRx*cosRy);
    }
}

SplineLine::~SplineLine() {
    _TRACE_("SplineLine::~SplineLine() ");
    GGAF_DELETEARR(_x_basepoint);
    GGAF_DELETEARR(_y_basepoint);
    GGAF_DELETEARR(_z_basepoint);
    //イニシャライズされる前に解放されるかもしれない
    GGAF_DELETEARR_NULLABLE(_x_compute);
    GGAF_DELETEARR_NULLABLE(_y_compute);
    GGAF_DELETEARR_NULLABLE(_z_compute);
}
