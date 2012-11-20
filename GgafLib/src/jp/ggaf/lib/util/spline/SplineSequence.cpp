#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineSequence::SplineSequence(SplineManufacture* prm_pManufacture, GgafDxKurokoA* prm_pKurokoA) :
        GgafObject() {
    _pManufacture = prm_pManufacture;
    _pActor_target = prm_pKurokoA->_pActor;
    _option = ABSOLUTE_COORD;
    _offset_X = 0;
    _offset_Y = 0;
    _offset_Z = 0;
    _flip_X = 1;
    _flip_Y = 1;
    _flip_Z = 1;
    _is_executing = false;
    if (prm_pManufacture) {
        _is_created_pManufacture = false;
    } else {
        _is_created_pManufacture = true;
    }
    _distance_to_begin = 0;
    _point_index = 0;
}

void SplineSequence::setManufacture(SplineManufacture* prm_pManufacture) {
    _pManufacture = prm_pManufacture;
    _pActor_target = nullptr;
    _option = ABSOLUTE_COORD;
    _offset_X = 0;
    _offset_Y = 0;
    _offset_Z = 0;
    _flip_X = 1;
    _flip_Y = 1;
    _flip_Z = 1;
    _is_executing = false;
}

void SplineSequence::adjustCoordOffset(coord prm_offset_X, coord prm_offset_Y, coord prm_offset_Z) {
    _offset_X = prm_offset_X;
    _offset_Y = prm_offset_Y;
    _offset_Z = prm_offset_Z;
}

void SplineSequence::exec(SplinTraceOption prm_option) {
    if (_pManufacture) {
        _is_executing = true;
        _option = prm_option;
        _execute_frames = 0;
        SplineLine* pSpl = _pManufacture->_sp;
        _X_begin = _flip_X*pSpl->_X_compute[0]*_pManufacture->_rate_X + _offset_X;
        _Y_begin = _flip_Y*pSpl->_Y_compute[0]*_pManufacture->_rate_Y + _offset_Y;
        _Z_begin = _flip_Z*pSpl->_Z_compute[0]*_pManufacture->_rate_Z + _offset_Z;
        _distance_to_begin = UTIL::getDistance(
                                _pActor_target->_X,
                                _pActor_target->_Y,
                                _pActor_target->_Z,
                                _X_begin,
                                _Y_begin,
                                _Z_begin
                             );
    } else {
        throwGgafCriticalException("SplineSequence::exec Manufactureがありません。_pActor_target="<<_pActor_target->getName());
    }
}
void SplineSequence::stop() {
    _is_executing = false;
}


void SplineSequence::setAbsoluteBeginCoordinate() {
    SplineLine* pSpl = _pManufacture->_sp;
    _pActor_target->_X = _flip_X*pSpl->_X_compute[0]*_pManufacture->_rate_X + _offset_X;
    _pActor_target->_Y = _flip_Y*pSpl->_Y_compute[0]*_pManufacture->_rate_Y + _offset_Y;
    _pActor_target->_Z = _flip_Z*pSpl->_Z_compute[0]*_pManufacture->_rate_Z + _offset_Z;
}
void SplineSequence::behave() {

    if (_is_executing) {
        //現在の点INDEX
        int point_index = _execute_frames;
        SplineLine* pSpl = _pManufacture->_sp;
        if ( point_index == pSpl->_rnum) {
            //終了
            _is_executing = false;
            return;
        }

        _pActor_target->_X = (coord)(_flip_X*pSpl->_X_compute[point_index]*_pManufacture->_rate_X + _offset_X);
        _pActor_target->_Y = (coord)(_flip_Y*pSpl->_Y_compute[point_index]*_pManufacture->_rate_Y + _offset_Y);
        _pActor_target->_Z = (coord)(_flip_Z*pSpl->_Z_compute[point_index]*_pManufacture->_rate_Z + _offset_Z);
        _execute_frames++;
    }
}

coord SplineSequence::getSegmentDistance(int prm_index) {
#ifdef MY_DEBUG
    if (prm_index < 0 || prm_index > (_pManufacture->_sp->_rnum -1)) {
        throwGgafCriticalException("SplineSequence::getSegmentDistance("<<prm_index<<") は、範囲外です._pActor_target="<< _pActor_target <<"["<< _pActor_target->getName() <<"]");
    }
#endif
    if (prm_index == 0) {
        return _distance_to_begin;
    } else {
        return _pManufacture->_paDistance_to[prm_index];
    }
}
int SplineSequence::getPointNum() {
    return _pManufacture->_sp->_rnum;
}
SplineSequence::~SplineSequence() {
    if (_is_created_pManufacture) {
        SplineSource* pSplSrc = _pManufacture->_pSplSrc;
        DELETE_IMPOSSIBLE_NULL(pSplSrc);
        DELETE_IMPOSSIBLE_NULL(_pManufacture);
    }
}
