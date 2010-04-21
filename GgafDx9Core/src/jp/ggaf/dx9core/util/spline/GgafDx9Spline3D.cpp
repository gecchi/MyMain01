#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9Spline3D::GgafDx9Spline3D() {
    _X_basepoint = NULL;
    _Y_basepoint = NULL;
    _Z_basepoint = NULL;
    _num_basepoint = 0;
    _X_compute = NULL;
    _Y_compute = NULL;
    _Z_compute = NULL;
    _rnum = 0;
}


GgafDx9Spline3D::GgafDx9Spline3D(double prm_paaEstablish[][3], int prm_num, double prm_accuracy) {
    init(prm_paaEstablish, prm_num, prm_accuracy);
}


void GgafDx9Spline3D::init(double prm_paaEstablish[][3], int prm_num, double prm_accuracy) {
    _num_basepoint = prm_num;
    _X_basepoint = new double[prm_num]; //�{�N���X�� static�錾�Ŏg�p����邽�߁ANEW�}�N���Ń`�F�b�N�s�BNEW�}�N���͎g��Ȃ��B
    _Y_basepoint = new double[prm_num];
    _Z_basepoint = new double[prm_num];
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

void GgafDx9Spline3D::compute(double prm_accuracy) {
    _rnum = _num_basepoint/prm_accuracy;
    if (_X_compute != NULL) {
        DELETEARR_IMPOSSIBLE_NULL(_X_compute);
        DELETEARR_IMPOSSIBLE_NULL(_Y_compute);
        DELETEARR_IMPOSSIBLE_NULL(_Z_compute);
    }
    _X_compute = new double[_rnum];
    _Y_compute = new double[_rnum];
    _Z_compute = new double[_rnum];

    int index = 0;
    for (double t = 0.0; t <= _num_basepoint-1.0; t += prm_accuracy) {
        _X_compute[index] = _xs.compute(t);
        _Y_compute[index] = _ys.compute(t);
        _Z_compute[index] = _zs.compute(t);
        index++;
    }
    _rnum = index;
}

GgafDx9Spline3D::~GgafDx9Spline3D() {
    _TRACE_("GgafDx9Spline3D::~GgafDx9Spline3D() !!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    DELETEARR_IMPOSSIBLE_NULL(_X_basepoint);
    DELETEARR_IMPOSSIBLE_NULL(_Y_basepoint);
    DELETEARR_IMPOSSIBLE_NULL(_Z_basepoint);
    //�C�j�V�����C�Y�����O�ɉ������邩������Ȃ�
    DELETEARR_POSSIBLE_NULL(_X_compute);
    DELETEARR_POSSIBLE_NULL(_Y_compute);
    DELETEARR_POSSIBLE_NULL(_Z_compute);
}