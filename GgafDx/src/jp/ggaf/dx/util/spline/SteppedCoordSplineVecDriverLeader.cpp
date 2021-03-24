#include "jp/ggaf/dx/util/spline/SteppedCoordSplineVecDriverLeader.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/util/spline/SplineSource.h"
#include "jp/ggaf/dx/util/spline/SteppedCoordSplineManufacture.h"

using namespace GgafDx;

SteppedCoordSplineVecDriverLeader::SteppedCoordSplineVecDriverLeader(SplineManufacture* prm_pManufacture, GgafDx::VecDriver* prm_pVecDriver_target) :
        SplineLeader(prm_pManufacture, prm_pVecDriver_target->_pActor) {
    _pVecDriver_target = prm_pVecDriver_target;
    _pSteppedSplManuf = (SteppedCoordSplineManufacture*)prm_pManufacture;
    _leading_frames = 0;
    _point_index = -1;
}

void SteppedCoordSplineVecDriverLeader::restart() {
    SplineLeader::restart();
    _leading_frames = 0;
    //�n�_�֍s�����ʏ����B
//    if (ABS(_distance_to_begin) <= PX_C(1)) {
    if ( (ucoord)(_distance_to_begin + PX_C(1)) <= (ucoord)(PX_C(2)) ) {
        //�n�_�Ƃ̋����������ꍇ(PX_C(1)�ȉ�)�̏ꍇ�A
        //�X�v���C����ԓ_�̑�P�_�ڂ��Ԉ����āA�n�_�̎��̕�ԓ_����X�^�[�g
        _point_index = 0;
    } else {
        //�n�_�Ƃ̋���������Ă���΁A�P�t���[����₵�n�_��
        _point_index = -1;
    }
}

void SteppedCoordSplineVecDriverLeader::behave() {
    if (_is_leading) {
        GgafDx::VecDriver* const pVecDriver_target = _pActor_target->callVecDriver();
        _point_index++;
        if (_point_index == _pSteppedSplManuf->_pSpl->_rnum) {
            if (_cnt_loop == _max_loop) {
                //�I��
                _is_leading = false;
                return;
            } else {
                //���[�v
                _cnt_loop++;
                restart();
                _point_index++;
            }
        }
        coord x, y, z;
        getPointCoord(_point_index, x, y, z);
        coord d = UTIL::getDistance(_pActor_target->_x, _pActor_target->_y, _pActor_target->_z, x, y, z);
        pVecDriver_target->setMvAngTwd(x, y, z);
        pVecDriver_target->setMvVelo(d);
        _leading_frames++;
    }
}

SteppedCoordSplineVecDriverLeader::~SteppedCoordSplineVecDriverLeader() {
}
