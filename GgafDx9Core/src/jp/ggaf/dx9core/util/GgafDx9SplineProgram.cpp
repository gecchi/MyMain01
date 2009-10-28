#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SplineProgram::GgafDx9SplineProgram() : GgafObject() {

    _sp = NULL;
    _SPframe = 0;
}

GgafDx9SplineProgram::GgafDx9SplineProgram(double prm_paaCriteriaPoints[][3],
                                            int prm_point_num,
                                            double prm_accuracy) : GgafObject() {
    _sp = NEW GgafDx9Spline3D(prm_paaCriteriaPoints, prm_point_num);
    _sp->compute(prm_accuracy); //ŒvŽZ
    _SPframe = 0;


}

void GgafDx9SplineProgram::begin(GgafDx9GeometricActor* _pActor, int prm_option) {
    if (_sp != NULL) {
        _is_executing = true;
        _pActor_executing = _pActor;
        _SPframe = 0;
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

        _pActor_executing->_X = _sp->_X_compute[SPPointIndex];
        _pActor_executing->_Y = _sp->_Y_compute[SPPointIndex];
        _pActor_executing->_Z = _sp->_Z_compute[SPPointIndex];

        _SPframe++;

    }

}
GgafDx9SplineProgram::~GgafDx9SplineProgram() {
    DELETE_IMPOSSIBLE_NULL(_sp);
}
