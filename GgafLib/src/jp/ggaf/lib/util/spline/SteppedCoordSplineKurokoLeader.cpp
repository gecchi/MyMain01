#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineKurokoLeader.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SteppedCoordSplineKurokoLeader::SteppedCoordSplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKuroko* const prm_pKuroko_target) :
        SplineKurokoLeader(prm_pManufacture, prm_pKuroko_target) {
    _pSteppedSplManuf = (SteppedCoordSplineManufacture*)prm_pManufacture;
    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = 0;
    _sinRzMv_begin = 0.0f;
    _cosRzMv_begin = 0.0f;
    _sinRyMv_begin = 0.0f;
    _cosRyMv_begin = 0.0f;
}

SteppedCoordSplineKurokoLeader::SteppedCoordSplineKurokoLeader(GgafDxKuroko* const prm_pKuroko_target,
                                                                 SplineLine* prmpSpl,
                                                                 angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prm_pKuroko_target) { //nullptrで渡す事により、_is_created_pManufacture が falseになる
    _pSteppedSplManuf = NEW SteppedCoordSplineManufacture(NEW SplineSource(prmpSpl), prm_angveloRzRyMv);
    _pSteppedSplManuf->calculate(); //忘れないように。いずれこのタイプは消す
    _pManufacture = _pSteppedSplManuf; //基底メンバーセット。忘れないように。いずれこのタイプは消す

    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = 0;
    _sinRzMv_begin = 0.0f;
    _cosRzMv_begin = 0.0f;
    _sinRyMv_begin = 0.0f;
    _cosRyMv_begin = 0.0f;
}

void SteppedCoordSplineKurokoLeader::start(SplinTraceOption prm_option, int prm_max_loop) {
    if (_pSteppedSplManuf) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _max_loop = prm_max_loop;
        _cnt_loop = 1;
        restart();
    } else {
        throwGgafCriticalException("SplineKurokoLeader::exec Manufactureがありません。_pActor_target="<<_pActor_target->getName());
    }
}

void SteppedCoordSplineKurokoLeader::restart() {
    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = 0;
    SplineLine* pSpl = _pSteppedSplManuf->_sp;
    if (_option == RELATIVE_DIRECTION) {
        if (!_is_fix_start_pos) {
            _x_start = (_flip_x * pSpl->_x_compute[0] * _pSteppedSplManuf->_rate_x) + _offset_x - _pActor_target->_x;
            _y_start = (_flip_y * pSpl->_y_compute[0] * _pSteppedSplManuf->_rate_y) + _offset_y - _pActor_target->_y;
            _z_start = (_flip_z * pSpl->_z_compute[0] * _pSteppedSplManuf->_rate_z) + _offset_z - _pActor_target->_z;
        }
        GgafDxKuroko* const pKuroko_target = _pActor_target->getKuroko();
        _sinRzMv_begin = ANG_SIN(pKuroko_target->_angRzMv);
        _cosRzMv_begin = ANG_COS(pKuroko_target->_angRzMv);
        _sinRyMv_begin = ANG_SIN(pKuroko_target->_angRyMv);
        _cosRyMv_begin = ANG_COS(pKuroko_target->_angRyMv);
    } else if (_option == RELATIVE_COORD) {
        if (!_is_fix_start_pos) {
            _x_start = (_flip_x * pSpl->_x_compute[0] * _pSteppedSplManuf->_rate_x) + _offset_x - _pActor_target->_x;
            _y_start = (_flip_y * pSpl->_y_compute[0] * _pSteppedSplManuf->_rate_y) + _offset_y - _pActor_target->_y;
            _z_start = (_flip_z * pSpl->_z_compute[0] * _pSteppedSplManuf->_rate_z) + _offset_z - _pActor_target->_z;
        }
    } else { //ABSOLUTE_COORD
        if (!_is_fix_start_pos) {
            _x_start = (_flip_x * pSpl->_x_compute[0] * _pSteppedSplManuf->_rate_x) + _offset_x;
            _y_start = (_flip_y * pSpl->_y_compute[0] * _pSteppedSplManuf->_rate_y) + _offset_y;
            _z_start = (_flip_z * pSpl->_z_compute[0] * _pSteppedSplManuf->_rate_z) + _offset_z;
        }
   }
}

void SteppedCoordSplineKurokoLeader::behave() {
    //TODO:未実装！早く作ろう
}

SteppedCoordSplineKurokoLeader::~SteppedCoordSplineKurokoLeader() {
}
