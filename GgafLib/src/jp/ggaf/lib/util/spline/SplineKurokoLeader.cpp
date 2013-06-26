#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineKurokoLeader::SplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKurokoA* prm_pKurokoA) :
        GgafObject() {
    _pManufacture = prm_pManufacture;
    _pActor_target = prm_pKurokoA->_pActor;
    _option = ABSOLUTE_COORD;
    _X_begin = 0;
    _Y_begin = 0;
    _Z_begin = 0;
    _offset_X = 0;
    _offset_Y = 0;
    _offset_Z = 0;
    _flip_X = 1;
    _flip_Y = 1;
    _flip_Z = 1;
    _was_started = false;
    _is_leading = false;
    if (prm_pManufacture) {
        _is_created_pManufacture = false;
    } else {
        _is_created_pManufacture = true;
    }
    _distance_to_begin = 0;
    _point_index = 0;
    _leading_frames = 0;
    _cnt_loop = 0;
    _max_loop = 1;
}


void SplineKurokoLeader::getPointCoord(int prm_point_index, coord &out_X, coord&out_Y, coord &out_Z) {
    SplineLine* pSpl = _pManufacture->_sp;
    out_X = (coord)(_flip_X*pSpl->_X_compute[prm_point_index]*_pManufacture->_rate_X + _offset_X);
    out_Y = (coord)(_flip_Y*pSpl->_Y_compute[prm_point_index]*_pManufacture->_rate_Y + _offset_Y);
    out_Z = (coord)(_flip_Z*pSpl->_Z_compute[prm_point_index]*_pManufacture->_rate_Z + _offset_Z);
}


void SplineKurokoLeader::setManufacture(SplineManufacture* prm_pManufacture) {
    _pManufacture = prm_pManufacture;
    _pActor_target = nullptr;
    _option = ABSOLUTE_COORD;
    _offset_X = 0;
    _offset_Y = 0;
    _offset_Z = 0;
    _flip_X = 1;
    _flip_Y = 1;
    _flip_Z = 1;
    _was_started = false;
    _is_leading = false;
}

void SplineKurokoLeader::adjustCoordOffset(coord prm_offset_X, coord prm_offset_Y, coord prm_offset_Z) {
    _offset_X = prm_offset_X;
    _offset_Y = prm_offset_Y;
    _offset_Z = prm_offset_Z;
}

void SplineKurokoLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pManufacture) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _leading_frames = 0;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
        SplineKurokoLeader::getPointCoord(0, _X_begin, _Y_begin, _Z_begin);
        _distance_to_begin = UTIL::getDistance(
                                _pActor_target->_X,
                                _pActor_target->_Y,
                                _pActor_target->_Z,
                                _X_begin,
                                _Y_begin,
                                _Z_begin
                             );
    } else {
        throwGgafCriticalException("SplineKurokoLeader::exec Manufactureがありません。_pActor_target="<<_pActor_target->getName());
    }
}
void SplineKurokoLeader::stop() {
    _is_leading = false;
}


void SplineKurokoLeader::setAbsoluteBeginCoord() {
    SplineKurokoLeader::getPointCoord(0, _pActor_target->_X, _pActor_target->_Y, _pActor_target->_Z);
}
void SplineKurokoLeader::behave() {

    if (_is_leading) {
        //現在の点INDEX
        int point_index = _leading_frames;
        SplineLine* pSpl = _pManufacture->_sp;
        if ( point_index == pSpl->_rnum) {
            if (_cnt_loop == _max_loop) {
                //終了
                _is_leading = false;
                return;
            } else {
                _cnt_loop++;

                _leading_frames = 0;
                SplineKurokoLeader::getPointCoord(0, _X_begin, _Y_begin, _Z_begin);
                _distance_to_begin = UTIL::getDistance(
                                        _pActor_target->_X,
                                        _pActor_target->_Y,
                                        _pActor_target->_Z,
                                        _X_begin,
                                        _Y_begin,
                                        _Z_begin
                                     );
            }

        }
        SplineKurokoLeader::getPointCoord(point_index, _pActor_target->_X, _pActor_target->_Y, _pActor_target->_Z);
        _leading_frames++;
    }
}

coord SplineKurokoLeader::getSegmentDistance(int prm_index) {
#ifdef MY_DEBUG
    if (prm_index < 0 || prm_index > (_pManufacture->_sp->_rnum -1)) {
        throwGgafCriticalException("SplineKurokoLeader::getSegmentDistance("<<prm_index<<") は、範囲外です._pActor_target="<< _pActor_target <<"["<< _pActor_target->getName() <<"]");
    }
#endif
    if (prm_index == 0) {
        return _distance_to_begin;
    } else {
        return _pManufacture->_paDistance_to[prm_index];
    }
}

coord SplineKurokoLeader::getTotalDistance() {
    return _pManufacture->_total_distance + _distance_to_begin;
}

int SplineKurokoLeader::getPointNum() {
    return _pManufacture->_sp->_rnum;
}
SplineKurokoLeader::~SplineKurokoLeader() {
    if (_is_created_pManufacture) {
        SplineSource* pSplSrc = _pManufacture->_pSplSrc;
        GGAF_DELETE(pSplSrc);
        GGAF_DELETE(_pManufacture);
    }
}
