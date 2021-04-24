#include "jp/ggaf/dx/util/curve/FixedVelocityCurveVecDriverLeader.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/VecDriverMvAngAssistant.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/util/curve/CurveSource.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveManufacture.h"

using namespace GgafDx;

FixedVelocityCurveVecDriverLeader::FixedVelocityCurveVecDriverLeader(CurveManufacture* prm_pManufacture, GgafDx::VecDriver* prm_pVecDriver_target) :
        DriverLeader(prm_pManufacture, prm_pVecDriver_target->_pActor) {
    _pVecDriver_target = prm_pVecDriver_target;
    _pFixedVeloSplManuf = (FixedVelocityCurveManufacture*)prm_pManufacture;
    _leadning_float_frames = 0.0f;
    _float_frame_of_next = -0.00001f;
    _point_index = -1;//�ŏ��͎n�_[0]�Ɍ������̂ŁA�n�_�O��-1�ɂȂ�B
}

void FixedVelocityCurveVecDriverLeader::restart() {
    DriverLeader::restart();
    _leadning_float_frames = 0.0f;
    _float_frame_of_next = -0.00001f;
    _point_index = -1;//�ŏ��͎n�_[0]�Ɍ������̂ŁA�n�_�O��-1�ɂȂ�B
}

void FixedVelocityCurveVecDriverLeader::behave() {
    if (_is_leading) {
        GgafDx::VecDriver* pVecDriver_target = _pVecDriver_target;
        //�ς���
        const int sp_rnum = _pFixedVeloSplManuf->_pCurve->_rnum;
        if (_leadning_float_frames >= _float_frame_of_next) {
again:
            _point_index++;
            if (_point_index == sp_rnum) {
                if (_cnt_loop == _max_loop) {
                    //�I��
                    _is_leading = false;
                    pVecDriver_target->stopTurningMvAng();
                    return;
                } else {
                    //���[�v
                    _cnt_loop++;
                    restart();
                    _point_index++;
                }
            }
            if (_point_index == 0) {
                //�ŏ��̕K�R�u���C�N�A�n�_�֍s��
                //�n�_�܂łɕK�v�ȃt���[�����擾
                _float_frame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit);
            } else {
                //�n�_�ȊO�̏ꍇ���̕⊮�_�܂łɕK�v�ȃt���[�������X�V
                _float_frame_of_next = (1.0*_distance_to_begin / _pFixedVeloSplManuf->_velo_mvUnit) +
                                     _pFixedVeloSplManuf->_paFrame_need_at[_point_index];
            }
            if (_leadning_float_frames >= _float_frame_of_next) {
                //_float_frame_of_next�����ɐi�߂Ă�����Ȃ��ꍇ�A�������_point_index��i�߂�
                goto again;
            }
            coord x, y, z;
            getPointCoord(_point_index, x, y, z);
            if (_turn_smooth) {
                pVecDriver_target->asstMvAng()->turnByVdTwd(
                        _pFixedVeloSplManuf->_angvelo_rzry_mv,
                        x, y, z, _pFixedVeloSplManuf->_turn_way, _pFixedVeloSplManuf->_turn_optimize,
                        0.3, 0.7, 0,
                        true);
            } else {
                pVecDriver_target->turnMvAngTwd(x, y, z,
                                             _pFixedVeloSplManuf->_angvelo_rzry_mv, 0,
                                             _pFixedVeloSplManuf->_turn_way,
                                             _pFixedVeloSplManuf->_turn_optimize);
            }
        }
        //�L�����̑��x��1000�Ȃ�΁A_leadning_float_frames ++;
        //�L�����̑��x��2000�Ȃ��  _leadning_float_frames += 2.0;
        //�L�����̑��x��500�Ȃ�΁A _leadning_float_frames += 0.5
        _leadning_float_frames += (pVecDriver_target->_velo_mv * (1.0 / LEN_UNIT));
    }
}

FixedVelocityCurveVecDriverLeader::~FixedVelocityCurveVecDriverLeader() {
}
