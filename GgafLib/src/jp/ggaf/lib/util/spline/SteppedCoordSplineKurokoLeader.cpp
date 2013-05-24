#include "stdafx.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineKurokoLeader.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineLine.h"
#include "jp/ggaf/lib/util/spline/SplineSource.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SteppedCoordSplineKurokoLeader::SteppedCoordSplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKurokoA* prm_pKurokoA_target) :
        SplineKurokoLeader(prm_pManufacture, prm_pKurokoA_target) {
    _pSteppedSplManuf = (SteppedCoordSplineManufacture*)prm_pManufacture;
    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = 0;
    _SIN_RzMv_begin = 0.0f;
    _COS_RzMv_begin = 0.0f;
    _SIN_RyMv_begin = 0.0f;
    _COS_RyMv_begin = 0.0f;
}

SteppedCoordSplineKurokoLeader::SteppedCoordSplineKurokoLeader(GgafDxKurokoA* prm_pKurokoA_target,
                                                                 SplineLine* prmpSpl,
                                                                 angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prm_pKurokoA_target) { //nullptrで渡す事により、_is_created_pManufacture が falseになる
    _pSteppedSplManuf = NEW SteppedCoordSplineManufacture(NEW SplineSource(prmpSpl), prm_angveloRzRyMv);
    _pSteppedSplManuf->calculate(); //忘れないように。いずれこのタイプは消す
    _pManufacture = _pSteppedSplManuf; //基底メンバーセット。忘れないように。いずれこのタイプは消す

    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = 0;
    _SIN_RzMv_begin = 0.0f;
    _COS_RzMv_begin = 0.0f;
    _SIN_RyMv_begin = 0.0f;
    _COS_RyMv_begin = 0.0f;
}

void SteppedCoordSplineKurokoLeader::start(SplinTraceOption prm_option) {
    if (_pSteppedSplManuf) {
        _was_started = true;
        _is_leading = true;
        _option = prm_option;
        _leadning_fFrames = 0.0f;
        _fFrame_of_next = -0.00001f;
        _point_index = 0;
        SplineLine* pSpl = _pSteppedSplManuf->_sp;
        if (_option == RELATIVE_DIRECTION) {
            _X_begin = (_flip_X * pSpl->_X_compute[0] * _pSteppedSplManuf->_rate_X) + _offset_X - _pActor_target->_X;
            _Y_begin = (_flip_Y * pSpl->_Y_compute[0] * _pSteppedSplManuf->_rate_Y) + _offset_Y - _pActor_target->_Y;
            _Z_begin = (_flip_Z * pSpl->_Z_compute[0] * _pSteppedSplManuf->_rate_Z) + _offset_Z - _pActor_target->_Z;
            GgafDxKurokoA* pKurokoA_target = _pActor_target->_pKurokoA;
            _SIN_RzMv_begin = ANG_SIN(pKurokoA_target->_angRzMv);
            _COS_RzMv_begin = ANG_COS(pKurokoA_target->_angRzMv);
            _SIN_RyMv_begin = ANG_SIN(pKurokoA_target->_angRyMv);
            _COS_RyMv_begin = ANG_COS(pKurokoA_target->_angRyMv);
        } else if (_option == RELATIVE_COORD) {
            _X_begin = (_flip_X * pSpl->_X_compute[0] * _pSteppedSplManuf->_rate_X) + _offset_X - _pActor_target->_X;
            _Y_begin = (_flip_Y * pSpl->_Y_compute[0] * _pSteppedSplManuf->_rate_Y) + _offset_Y - _pActor_target->_Y;
            _Z_begin = (_flip_Z * pSpl->_Z_compute[0] * _pSteppedSplManuf->_rate_Z) + _offset_Z - _pActor_target->_Z;
        } else { //ABSOLUTE_COORD
            _X_begin = (_flip_X * pSpl->_X_compute[0] * _pSteppedSplManuf->_rate_X) + _offset_X;
            _Y_begin = (_flip_Y * pSpl->_Y_compute[0] * _pSteppedSplManuf->_rate_Y) + _offset_Y;
            _Z_begin = (_flip_Z * pSpl->_Z_compute[0] * _pSteppedSplManuf->_rate_Z) + _offset_Z;
       }
    } else {
        throwGgafCriticalException("SplineKurokoLeader::exec Manufactureがありません。_pActor_target="<<_pActor_target->getName());
    }
}

void SteppedCoordSplineKurokoLeader::behave() {
    //TODO:未実装！早く作ろう
}
SteppedCoordSplineKurokoLeader::~SteppedCoordSplineKurokoLeader() {
}
