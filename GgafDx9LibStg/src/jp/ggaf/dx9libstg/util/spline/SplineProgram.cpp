#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


SplineProgram::SplineProgram(GgafDx9GeometricActor* prm_pActor_target) : GgafObject() {
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

SplineProgram::SplineProgram(GgafDx9GeometricActor* prm_pActor_target,
                                           double prm_paaCriteriaPoints[][3],
                                           int prm_point_num,
                                           double prm_accuracy) : GgafObject() {
    _pActor_target = prm_pActor_target;
    _sp = NEW Spline3D(prm_paaCriteriaPoints, prm_point_num, prm_accuracy);
    _SPframe = 0;
    _is_create_sp = true;
    _rate_X = 1.0;
    _rate_Y = 1.0;
    _rate_Z = 1.0;
    _X_begin = 0;
    _Y_begin = 0;
    _Z_begin = 0;
    _offset_X = 0;
    _offset_Y = 0;
    _offset_Z = 0;
}

SplineProgram::SplineProgram(GgafDx9GeometricActor* prm_pActor_target, Spline3D* prm_sp) {
    _pActor_target = prm_pActor_target;
    _sp = prm_sp;
    _is_create_sp = false;
    _rate_X = 1.0;
    _rate_Y = 1.0;
    _rate_Z = 1.0;
    _X_begin = 0;
    _Y_begin = 0;
    _Z_begin = 0;
    _offset_X = 0;
    _offset_Y = 0;
    _offset_Z = 0;
}

void SplineProgram::setSpline(Spline3D* prm_sp) {
    _sp = prm_sp;
    _is_create_sp = false;
}

void SplineProgram::begin(int prm_option) {
    if (_sp) {
        _is_executing = true;

        _SPframe = 0;

        _X_begin = _sp->_X_compute[0]*_rate_X + _offset_X;
        _Y_begin = _sp->_Y_compute[0]*_rate_Y + _offset_Y;
        _Z_begin = _sp->_Z_compute[0]*_rate_Z + _offset_Z;
    }
}

void SplineProgram::setAbsoluteBeginCoordinate() {
    _pActor_target->_X = _sp->_X_compute[0]*_rate_X + _offset_X;
    _pActor_target->_Y = _sp->_Y_compute[0]*_rate_Y + _offset_Y;
    _pActor_target->_Z = _sp->_Z_compute[0]*_rate_Z + _offset_Z;
}
void SplineProgram::behave() {

    if (_is_executing) {
        //Œ»Ý‚Ì“_INDEX
        int SPPointIndex = _SPframe;
        if ( SPPointIndex == _sp->_rnum) {
            //I—¹
            _is_executing = false;
            return;
        }

        _pActor_target->_X = (coord)(_sp->_X_compute[SPPointIndex]*_rate_X + _offset_X);
        _pActor_target->_Y = (coord)(_sp->_Y_compute[SPPointIndex]*_rate_Y + _offset_Y);
        _pActor_target->_Z = (coord)(_sp->_Z_compute[SPPointIndex]*_rate_Z + _offset_Z);

        _SPframe++;

    }

}
void SplineProgram::adjustAxisOffset(coord prm_offset_X, coord prm_offset_Y, coord prm_offset_Z) {
    _offset_X = prm_offset_X;
    _offset_Y = prm_offset_Y;
    _offset_Z = prm_offset_Z;
}

void SplineProgram::adjustAxisRate(float prm_rate_X, float prm_rate_Y, float prm_rate_Z) {
    _rate_X = prm_rate_X;
    _rate_Y = prm_rate_Y;
    _rate_Z = prm_rate_Z;
}

SplineProgram::~SplineProgram() {
    if (_is_create_sp) {
        DELETE_IMPOSSIBLE_NULL(_sp);
    }
}
