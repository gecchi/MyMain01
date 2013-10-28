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

SteppedCoordSplineKurokoLeader::SteppedCoordSplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxKurokoA* const prm_pKurokoA_target) :
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

SteppedCoordSplineKurokoLeader::SteppedCoordSplineKurokoLeader(GgafDxKurokoA* const prm_pKurokoA_target,
                                                                 SplineLine* prmpSpl,
                                                                 angvelo prm_angveloRzRyMv):
        SplineKurokoLeader(nullptr, prm_pKurokoA_target) { //nullptr�œn�����ɂ��A_is_created_pManufacture �� false�ɂȂ�
    _pSteppedSplManuf = NEW SteppedCoordSplineManufacture(NEW SplineSource(prmpSpl), prm_angveloRzRyMv);
    _pSteppedSplManuf->calculate(); //�Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���
    _pManufacture = _pSteppedSplManuf; //��ꃁ���o�[�Z�b�g�B�Y��Ȃ��悤�ɁB�����ꂱ�̃^�C�v�͏���

    _leadning_fFrames = 0.0f;
    _fFrame_of_next = -0.00001f;
    _point_index = 0;
    _SIN_RzMv_begin = 0.0f;
    _COS_RzMv_begin = 0.0f;
    _SIN_RyMv_begin = 0.0f;
    _COS_RyMv_begin = 0.0f;
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
        throwGgafCriticalException("SplineKurokoLeader::exec Manufacture������܂���B_pActor_target="<<_pActor_target->getName());
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
        GgafDxKurokoA* const pKurokoA_target = _pActor_target->_pKurokoA;
        _SIN_RzMv_begin = ANG_SIN(pKurokoA_target->_angRzMv);
        _COS_RzMv_begin = ANG_COS(pKurokoA_target->_angRzMv);
        _SIN_RyMv_begin = ANG_SIN(pKurokoA_target->_angRyMv);
        _COS_RyMv_begin = ANG_COS(pKurokoA_target->_angRyMv);
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
    //TODO:�������I������낤
}

SteppedCoordSplineKurokoLeader::~SteppedCoordSplineKurokoLeader() {
}
