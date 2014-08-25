#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineKurokoLeader::SplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKuroko* const prm_pKuroko) :
        GgafObject() {
    _pManufacture = prm_pManufacture;
    _pActor_target = prm_pKuroko->_pActor;
    _option = ABSOLUTE_COORD;
    _x_start = 0;
    _y_start = 0;
    _z_start = 0;
    _offset_x = 0;
    _offset_y = 0;
    _offset_z = 0;
    _flip_x = 1;
    _flip_y = 1;
    _flip_z = 1;
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
    _is_fix_start_pos = false;
}


void SplineKurokoLeader::getPointCoord(int prm_point_index, coord &out_x, coord&out_y, coord &out_z) {
    SplineLine* pSpl = _pManufacture->_sp;
    out_x = (coord)(_flip_x*pSpl->_x_compute[prm_point_index]*_pManufacture->_rate_x + _offset_x);
    out_y = (coord)(_flip_y*pSpl->_y_compute[prm_point_index]*_pManufacture->_rate_y + _offset_y);
    out_z = (coord)(_flip_z*pSpl->_z_compute[prm_point_index]*_pManufacture->_rate_z + _offset_z);
}


void SplineKurokoLeader::setManufacture(SplineManufacture* prm_pManufacture) {
    _pManufacture = prm_pManufacture;
    _pActor_target = nullptr;
    _option = ABSOLUTE_COORD;
    _offset_x = 0;
    _offset_y = 0;
    _offset_z = 0;
    _flip_x = 1;
    _flip_y = 1;
    _flip_z = 1;
    _was_started = false;
    _is_leading = false;
}

void SplineKurokoLeader::adjustCoordOffset(coord prm_offset_x, coord prm_offset_y, coord prm_offset_z) {
    _offset_x = prm_offset_x;
    _offset_y = prm_offset_y;
    _offset_z = prm_offset_z;
}

void SplineKurokoLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pManufacture) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _leading_frames = 0;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
        SplineKurokoLeader::getPointCoord(0, _x_start, _y_start, _z_start);
        _distance_to_begin = UTIL::getDistance(
                                _pActor_target->_x,
                                _pActor_target->_y,
                                _pActor_target->_z,
                                _x_start,
                                _y_start,
                                _z_start
                             );
    } else {
        throwGgafCriticalException("SplineKurokoLeader::exec Manufactureがありません。_pActor_target="<<_pActor_target->getName());
    }
}
void SplineKurokoLeader::stop() {
    _is_leading = false;
}


void SplineKurokoLeader::setAbsoluteBeginCoord() {
    SplineKurokoLeader::getPointCoord(0, _pActor_target->_x, _pActor_target->_y, _pActor_target->_z);
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
                SplineKurokoLeader::getPointCoord(0, _x_start, _y_start, _z_start);
                _distance_to_begin = UTIL::getDistance(
                                        _pActor_target->_x,
                                        _pActor_target->_y,
                                        _pActor_target->_z,
                                        _x_start,
                                        _y_start,
                                        _z_start
                                     );
            }

        }
        SplineKurokoLeader::getPointCoord(point_index, _pActor_target->_x, _pActor_target->_y, _pActor_target->_z);
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
