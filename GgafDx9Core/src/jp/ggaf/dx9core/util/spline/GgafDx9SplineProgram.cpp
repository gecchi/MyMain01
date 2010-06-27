#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SplineProgram::GgafDx9SplineProgram(GgafDx9GeometricActor* prm_pActor_target) : GgafObject() {
    _pActor_target = prm_pActor_target;
    _sp = NULL;
    _SPframe = 0;
    _is_create_sp = false;
    _rate_X = 1.0;
    _rate_Y = 1.0;
    _rate_Z = 1.0;
    _X_begin = 0;
    _Y_begin = 0;
    _Z_begin = 0;
}

GgafDx9SplineProgram::GgafDx9SplineProgram(GgafDx9GeometricActor* prm_pActor_target,
                                           double prm_paaCriteriaPoints[][3],
                                           int prm_point_num,
                                           double prm_accuracy) : GgafObject() {
    _pActor_target = prm_pActor_target;
    _sp = NEW GgafDx9Spline3D(prm_paaCriteriaPoints, prm_point_num, prm_accuracy);
    _SPframe = 0;
    _is_create_sp = true;
    _rate_X = 1.0;
    _rate_Y = 1.0;
    _rate_Z = 1.0;
    _X_begin = 0;
    _Y_begin = 0;
    _Z_begin = 0;
}

GgafDx9SplineProgram::GgafDx9SplineProgram(GgafDx9GeometricActor* prm_pActor_target, GgafDx9Spline3D* prm_sp) {
    _pActor_target = prm_pActor_target;
    _sp = prm_sp;
    _is_create_sp = false;
    _rate_X = 1.0;
    _rate_Y = 1.0;
    _rate_Z = 1.0;
    _X_begin = 0;
    _Y_begin = 0;
    _Z_begin = 0;
}

void GgafDx9SplineProgram::setSpline(GgafDx9Spline3D* prm_sp) {
    _sp = prm_sp;
    _is_create_sp = false;
}

void GgafDx9SplineProgram::begin(int prm_option) {
    if (_sp != NULL) {
        _is_executing = true;

        _SPframe = 0;

        _X_begin = _sp->_X_compute[0]*_rate_X;
        _Y_begin = _sp->_Y_compute[0]*_rate_Y;
        _Z_begin = _sp->_Z_compute[0]*_rate_Z;
    }
}

void GgafDx9SplineProgram::behave() {

    if (_is_executing) {
        //Œ»Ý‚Ì“_INDEX
        int SPPointIndex = _SPframe;
        if ( SPPointIndex == _sp->_rnum) {
            //I—¹
            _is_executing = false;
            return;
        }

        _pActor_target->_X = (int)(_sp->_X_compute[SPPointIndex]*_rate_X);
        _pActor_target->_Y = (int)(_sp->_Y_compute[SPPointIndex]*_rate_Y);
        _pActor_target->_Z = (int)(_sp->_Z_compute[SPPointIndex]*_rate_Z);

        _SPframe++;

    }

}
GgafDx9SplineProgram::~GgafDx9SplineProgram() {
    if (_is_create_sp) {
        DELETE_IMPOSSIBLE_NULL(_sp);
    }
}
