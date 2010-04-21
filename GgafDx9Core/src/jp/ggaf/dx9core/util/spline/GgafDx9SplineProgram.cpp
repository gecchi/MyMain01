#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SplineProgram::GgafDx9SplineProgram() : GgafObject() {

    _sp = NULL;
    _SPframe = 0;
    _is_create_sp = false;
}

GgafDx9SplineProgram::GgafDx9SplineProgram(double prm_paaCriteriaPoints[][3],
                                            int prm_point_num,
                                            double prm_accuracy) : GgafObject() {
    _sp = NEW GgafDx9Spline3D(prm_paaCriteriaPoints, prm_point_num, prm_accuracy);
    _SPframe = 0;
    _is_create_sp = true;
}

GgafDx9SplineProgram::GgafDx9SplineProgram(GgafDx9Spline3D* prm_sp) {
    _sp = prm_sp;
    _is_create_sp = false;
}

void GgafDx9SplineProgram::setSpline(GgafDx9Spline3D* prm_sp) {
    _sp = prm_sp;
    _is_create_sp = false;
}

void GgafDx9SplineProgram::begin(GgafDx9GeometricActor* prm_pActor_target, int prm_option) {
    if (_sp != NULL) {
        _is_executing = true;
        _pActor_target = prm_pActor_target;
        _SPframe = 0;
    }
}

void GgafDx9SplineProgram::behave() {

    if (_is_executing) {
        //���݂̓_INDEX
        int SPPointIndex = _SPframe;
        if ( SPPointIndex == _sp->_rnum) {
            //�I��
            _is_executing = false;
            return;
        }

        _pActor_target->_X = (int)(_sp->_X_compute[SPPointIndex]);
        _pActor_target->_Y = (int)(_sp->_Y_compute[SPPointIndex]);
        _pActor_target->_Z = (int)(_sp->_Z_compute[SPPointIndex]);

        _SPframe++;

    }

}
GgafDx9SplineProgram::~GgafDx9SplineProgram() {
    if (_is_create_sp) {
        DELETE_IMPOSSIBLE_NULL(_sp);
    }
}