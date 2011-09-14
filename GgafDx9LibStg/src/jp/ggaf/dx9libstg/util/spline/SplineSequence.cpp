#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

SplineSequence::SplineSequence(SplineManufacture* prm_pManufacture, GgafDx9KurokoA* prm_pKurokoA) :
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
}

void SplineSequence::setManufacture(SplineManufacture* prm_pManufacture) {
    _pManufacture = prm_pManufacture;
    _pActor_target = NULL;
    _option = ABSOLUTE_COORD;
    _offset_X = 0;
    _offset_Y = 0;
    _offset_Z = 0;
    _flip_X = 1;
    _flip_Y = 1;
    _flip_Z = 1;
    _is_executing = false;
}

void SplineSequence::adjustCoodOffset(coord prm_offset_X, coord prm_offset_Y, coord prm_offset_Z) {
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
    } else {
        throwGgafCriticalException("SplineSequence::exec ManufactureÇ™Ç†ÇËÇ‹ÇπÇÒÅB_pActor_target="<<_pActor_target->getName());
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
        //åªç›ÇÃì_INDEX
        int point_index = _execute_frames;
        SplineLine* pSpl = _pManufacture->_sp;
        if ( point_index == pSpl->_rnum) {
            //èIóπ
            _is_executing = false;
            return;
        }

        _pActor_target->_X = (coord)(_flip_X*pSpl->_X_compute[point_index]*_pManufacture->_rate_X + _offset_X);
        _pActor_target->_Y = (coord)(_flip_Y*pSpl->_Y_compute[point_index]*_pManufacture->_rate_Y + _offset_Y);
        _pActor_target->_Z = (coord)(_flip_Z*pSpl->_Z_compute[point_index]*_pManufacture->_rate_Z + _offset_Z);

        _execute_frames++;

    }

}

SplineSequence::~SplineSequence() {
    if (_is_created_pManufacture) {
        SplineSource* pSplSrc = _pManufacture->_pSplSrc;
        DELETE_IMPOSSIBLE_NULL(pSplSrc);
        DELETE_IMPOSSIBLE_NULL(_pManufacture);
    }
//    if (_pManufacture->_pSplSrcCon) {
//
//    } else {
//        SplineSource* pSplSrc = _pManufacture->_pSplSrc;
//        DELETE_IMPOSSIBLE_NULL(pSplSrc);
//        DELETE_IMPOSSIBLE_NULL(_pManufacture);
//    }

//    if (_is_create_pManufacture) {
//        DELETE_IMPOSSIBLE_NULL(_pManufacture);
//    }
}
